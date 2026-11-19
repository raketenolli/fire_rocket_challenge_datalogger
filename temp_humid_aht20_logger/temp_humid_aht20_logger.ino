#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_AHTX0.h>
#include <SPI.h>
#include "SdFat.h"


#define NUM_PIXELS 1
#define SD_CS_PIN 23


Adafruit_NeoPixel status_px(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
int status_px_on = 255;
SdFat SD;
SdSpiConfig config(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(16), &SPI1);
const int LOG_NUMBER_WIDTH = 4;

Adafruit_AHTX0 aht20;
sensors_event_t temp, humidity;

unsigned long timestamp_ms;
unsigned long written_lines = 0;

FsFile log_file;


void initializeAht20();
bool parseLogFilename(const char* name, uint32_t& outValue);
String getNextLogFilename(FsFile& dir, int width = LOG_NUMBER_WIDTH);


void setup() {
  status_px.begin();
  status_px.show();

  Serial.begin(115200);
  while (!Serial && millis() < 5000) {
    delay(10); 
  }
  if (Serial) { Serial.println("Adafruit Feather RP2040 Adalogger Serial Initialized!"); }

  if (!SD.begin(config)) {
    if (Serial) { Serial.println("SD initialization failed!"); }
    status_px.setPixelColor(0, status_px.Color(255, 0, 0));
    status_px.show();
    return;
  }

  FsFile root;
  if (!root.open("/")) {
    if (Serial) { Serial.println("Failed to open root directory!"); }
    status_px.setPixelColor(0, status_px.Color(255, 128, 0));
    status_px.show();
    return;
  }

  String newFilename = getNextLogFilename(root);
  root.close();

  if (Serial) {
    Serial.print("New log filename: ");
    Serial.println(newFilename);  
  }

  if (log_file.open(newFilename.c_str(), O_WRITE | O_CREAT)) {
    if (Serial) { Serial.println("Log file created successfully."); }
  } else {
    if (Serial) { Serial.println("Failed to create log file!"); }
  }
  
  initializeAht20();
}

void loop() {
  aht20.getEvent(&humidity, &temp);
  timestamp_ms = millis();

  log_file.print(timestamp_ms);
  log_file.print(",");
  log_file.println(temp.temperature, 2);
  log_file.print(",");
  log_file.println(humidity.relative_humidity, 2);
  log_file.flush();

  written_lines++;
  if(written_lines % 100 == 0) {
    if (Serial) {
      Serial.print(written_lines);
      Serial.println(" lines written to log file");
    }
    status_px.setPixelColor(0, status_px.Color(0, status_px_on, 0));
    status_px.show();
    status_px_on = 255 - status_px_on;
  }

  delay(10);
}

void initializeAht20() {
  if (!aht20.begin()) {
    if (Serial) { Serial.println(F("Failed to find AHT20 chip")); }
    status_px.setPixelColor(0, status_px.Color(255, 255, 0));
    status_px.show();
    while (1) {
      delay(10);
    }
  }
  if (Serial) { Serial.println(F("AHT20 Found!")); }
}

// Returns true if 'name' matches ^[0-9]+\.csv$ (case-insensitive extension),
// and writes the parsed integer to 'outValue'.
bool parseLogFilename(const char* name, uint32_t& outValue) {
  int len = strlen(name);
  const char* ext = ".csv";
  int extLen = strlen(ext);

  if (len <= extLen) return false; // must have at least 1 digit + ".csv"

  int digitsLen = len - extLen;

  // Check extension (case-insensitive)
  for (int i = 0; i < extLen; i++) {
    if (tolower(name[digitsLen + i]) != ext[i]) return false;
  }

  // Check that everything before the extension is digits
  for (int i = 0; i < digitsLen; i++) {
    if (!isdigit((unsigned char)name[i])) return false;
  }

  // Parse the integer
  outValue = (uint32_t)strtoul(name, nullptr, 10);
  return true;
}

// Scans the given directory for files matching the pattern and returns
// the next available filename (highest found + 1), zero-padded.
// If no matching files exist, returns "00000001.csv" (or width equivalent).
String getNextLogFilename(FsFile& dir, int width) {
  uint32_t highest = 0;
  bool found = false;

  dir.rewindDirectory();

  FsFile entry;
  char name[64];

  while (entry.openNext(&dir, O_RDONLY)) {
    if (!entry.isDirectory()) {
      entry.getName(name, sizeof(name));

      uint32_t value;
      if (parseLogFilename(name, value)) {
        found = true;
        if (value > highest) {
          highest = value;
        }
      }
    }
    entry.close();
  }

  uint32_t next = found ? (highest + 1) : 1;

  char buf[32];
  snprintf(buf, sizeof(buf), "%0*lu.csv", width, (unsigned long)next);
  return String(buf);
}