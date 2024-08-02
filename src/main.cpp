#include <SPI.h>
#include <vaisala_rs41.h>

void setup() {
  uint16_t leitura;   
  rs41_config_pinos_io(); 
  rs41_green_led (0);
  rs41_red_led (0); 
  
  Serial1.begin(9600); //GPS
  Serial3.begin(9600); 

  rs41_reset_gps ();
  
  radio_soft_reset();
  
  // configura frequencia de TX  
  radio_set_tx_frequency(403.0);
  
  //configura potencia de TX 
  radio_set_tx_power(1);
     
  radio_config_sensor_temp();  
  
  radio_enable_tx(); 
   
  delay(1000);  
}

void loop() {     
   while (Serial1.available() > 0)
  {
    Serial3.write(Serial1.read());
  }

    
}