#include <Arduino.h>
#include <SPI.h>
#include "config.h"
#include <U8g2lib.h>
#include <RadioLib.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, OLED_SCL, OLED_SDA, OLED_RST);

SX1278 radio = new Module(LORA_SS, LORA_DIO0, LORA_RST, LORA_DIO1);
PagerClient pager(&radio);

void pocsagInit() {

	Serial.println("Start POCSAG init");
	int state = radio.beginFSK();
  	if (state == RADIOLIB_ERR_NONE) {
    	Serial.println(F("success!"));
  	} else {
    	Serial.print(F("failed, code "));
    	Serial.println(state);
    while (true)
      ;
  }

 // initialize Pager client
   Serial.print(F("[Pager] Initializing ... "));
   state = pager.begin(POCSAG_QRG + POCSAG_OFFSET , POCSAG_BAUD);
   if (state == RADIOLIB_ERR_NONE) {
     Serial.println(F("success!"));
   } else {
     Serial.print(F("failed, code "));
     Serial.println(state);
     while (true)
       ;
   }
}

void displayInit() {
	u8g2.begin();
	u8g2.enableUTF8Print();
	u8g2.setFontDirection(0);
	u8g2.setFont(u8g2_font_calibration_gothic_nbp_tr );
	u8g2.setCursor(0,25);
	u8g2.print("PE2KMV");
	u8g2.setCursor(0,50);
	u8g2.print("Switching pager");
	u8g2.sendBuffer();
}

void pocsagStartRx() {
  // start receiving POCSAG messages
  Serial.print(F("[Pager] Starting to listen ... "));
  // address of this "pager":     1234567
  int state = pager.startReceive(LORA_DIO2, 200, 0);
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true)
      ;
  }
}

void displayPage(String address, String text) {
	u8g2.firstPage();
	u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_12x6LED_tf);
	u8g2.setCursor(0,15);
	u8g2.print(address);
	u8g2.setCursor(0,45);
	u8g2.print(text);
	u8g2.sendBuffer();
}

void switchGPIO(int gpioPin, int switchTime, String switchCode, String msgText) {
	if (gpioPin > 0 && switchCode == msgText) { // very, very basic security: continue if message text exactly matches predefined code
		Serial.println("Start GPIO switching");
		pinMode(gpioPin,OUTPUT);
		if (switchTime > 0) { // non latching switch from low to high to low
			digitalWrite(gpioPin,HIGH);
			delay(switchTime*1000); // predefined delay time before GPIO pin goes back low
			digitalWrite(gpioPin,LOW);
		}

		if (switchTime == 0){ // latching switch from low to high
			digitalWrite(gpioPin,HIGH);
		}
		if (switchTime == -1) { // latching switch from high to low
			digitalWrite(gpioPin,LOW);
		}
		Serial.println("End GPIO switching");
	}
}

void setup() {
	Serial.begin(115200);
	displayInit();
	Serial.println("Start init display");

	pocsagInit();
	pocsagStartRx();
}

void loop() {
  // the number of batches to wait for
  // 2 batches will usually be enough to fit short and medium messages
  if (pager.available() >= 2) {
    Serial.print(F("[Pager] Received pager data, decoding ... "));
    // you can read the data as an Arduino String
    String str;
    uint32_t addr = 0;
    int state = pager.readData(str, 0, &addr);
    if (state == RADIOLIB_ERR_NONE) {
      Serial.println(F("success!"));

      // print the received data
      Serial.print(F("[Pager] Address:\t"));
      Serial.print(String(addr));
      Serial.print(F("[Pager] Data:\t"));
      Serial.println(str);

      for (int i = 0; i < RICNUMBER; i++) {
        if (addr == ric[i].ricvalue && str == String(ric[i].switchcode)) {
          	displayPage(ric[i].name, str);
			switchGPIO(ric[i].gpiopin,ric[i].switchtime,String(ric[i].switchcode),str);		
        }
      }

    } else {
      // some error occurred
      Serial.print(F("failed, code "));
      Serial.println(state);
    }
  }
}

