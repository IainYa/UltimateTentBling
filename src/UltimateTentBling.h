
HardwareSerial Serial3(PIN_DEBUG_RX, PIN_DEBUG_TX); //USART 3
HardwareSerial Serial1(PIN_GPS_RX, PIN_GPS_TX); //GPS

void setupPins(){
    if(PIN_LED_RED > 0)
    {
        pinMode(PIN_LED_RED, OUTPUT);  // Red LED
    }
    if(PIN_LED_GREEN > 0)
    {
        pinMode(PIN_LED_GREEN, OUTPUT);  // Green LED
    }
    pinMode(PIN_GPS_RESET, OUTPUT);  //Reset GPS
}

void status_green_led (uint8_t val )
{
    if(PIN_LED_RED > 0)
    {
        digitalWrite(PIN_LED_GREEN, !val);
    }
}

void status_red_led (uint8_t val )
{
    if(PIN_LED_RED > 0)
    {
        digitalWrite(PIN_LED_RED, !val);
    }
}

void reset_gps() {   
    digitalWrite(PIN_GPS_RESET, LOW);
    delay(1);
    digitalWrite(PIN_GPS_RESET, HIGH);
}