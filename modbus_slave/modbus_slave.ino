
#include "ModbusRtu.h"

#define ID       1   // адрес ведомого
#define DE485Pin 10  //Pin control driver RS485
#define btnPin   2   // номер входа, подключенный к кнопке
#define ledPin   19  // номер выхода светодиода


//Задаём ведомому адрес, последовательный порт, выход управления TX
Modbus slave(ID, 0, DE485Pin); 
boolean led;
int8_t state = 0;
unsigned long tempus;

// массив данных modbus
uint16_t au16data[11];

void setup() {
  io_setup();
  slave.begin( 19200 ); 
}

void io_setup() {  
  pinMode(ledPin, OUTPUT);   
  pinMode(btnPin, INPUT);  
  digitalWrite(ledPin, LOW ); 
}

void loop() {
  state = slave.poll_slave( );    
  if (0 == slave.getLastError()) 
  {
	  io_poll();
  }
} 

void io_poll() {
  uint8_t state_of_led = 0;

  if (0 == slave.GetRwBit(0, &state_of_led))
  {
    if(state_of_led)
    {
      digitalWrite( ledPin, HIGH );
    }
    else
    {
      digitalWrite( ledPin, LOW );
    }
  } 
}

