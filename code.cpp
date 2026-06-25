#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Custom I2C Pin Definitions
const int I2C_SDA = 21;
const int I2C_SCL = 20;

// Hardware Pin Definition for Status LED
const int LED_PIN = 2; // Onboard LED

// Define GPIO pins for the 8-Position DIP Switch (Avoiding restricted pins)
const int dipPins[8] = {14, 13, 12, 11, 10, 9, 46, 3};

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  // Initialize all DIP switch pins with internal pull-up resistors
  // Switches tied to GND will read LOW (binary 0), open switches read HIGH (binary 1)
  for (int i = 0; i < 8; i++) {
    pinMode(dipPins[i], INPUT_PULLUP);
  }

  // Force ESP32 to route the I2C bus through Pins 21 and 20
  Wire.begin(I2C_SDA, I2C_SCL);

  // Initialize and turn on backlight for the 16x2 LCD
  lcd.init();
  lcd.backlight();

  // Display Boot Splash Screen
  lcd.setCursor(0, 0);
  lcd.print("Config System");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  int decimalValue = 0;
  String binaryString = "";

  // Read each DIP switch position and compile binary/decimal value
  for (int i = 0; i < 8; i++) {
    // Invert the read state because we use INPUT_PULLUP (Switch ON = LOW = 1)
    int switchState = !digitalRead(dipPins[i]); 
    
    binaryString += String(switchState);
    
    // Binary weight shifting calculation
    if (switchState == 1) {
      decimalValue |= (1 << (7 - i));
    }
  }

  // Print diagnostics to Serial Monitor
  Serial.print("Bin: "); Serial.print(binaryString);
  Serial.print(" | Dec: "); Serial.println(decimalValue);

  // Update LCD Screen row 1 (Binary String)
  lcd.setCursor(0, 0);
  lcd.print("BIN: ");
  lcd.print(binaryString);

  // Update LCD Screen row 2 (Decimal and Hex address settings)
  lcd.setCursor(0, 1);
  lcd.print("DEC: ");
  lcd.print(decimalValue);
  lcd.print("   HEX: 0x");
  if(decimalValue < 16) lcd.print("0");
  lcd.print(decimalValue, HEX);
  lcd.print("   "); // Extra spaces erase old character remnants

  // Simple status blink to indicate loop execution
  digitalWrite(LED_PIN, HIGH);
  delay(250);
  digitalWrite(LED_PIN, LOW);
  delay(250);
}
