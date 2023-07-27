#define OLED_SCL 15
#define OLED_SDA 4
#define OLED_RST 16
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define LORA_SS 18
#define LORA_DIO0 26
#define LORA_DIO1 35
#define LORA_DIO2 34
#define LORA_RST 14
#define LORA_MISO 19
#define LORA_MOSI 27
#define LORA_SCK 5

#define RICNUMBER 8 //Maximum number of RIC usable

float POCSAG_QRG = 439.9875;
int POCSAG_BAUD = 1200;
float POCSAG_OFFSET = 0.0000;


struct ric{
  long ricvalue; //RIC adress itself
  char* name; //"Nickname"
  int gpiopin; //GPIO pin to switch
  int switchtime;
  int switchcode;
}

ric[RICNUMBER]={
  {123456, "HORN",23,03,112}, // GPIO 23 goes high for 3 seconds when receiving message 112
  {123456, "TX Reset",12,5,1010}, // GPIO 12 goes high for 5 seconds when receiving message 1010
  {123456, "Link Reset",13,5,2020}, // GPIO 13 goes high for 5 seconds when receiving message 2020
  {123456, "Light on",32,0,3031}, // 0 switches GPIO 32 high with latching when receiving message 3031
  {123456,"Light off",32,-1,3030} // -1 switches GPIO 32 low with latching when receiving message 3030
};