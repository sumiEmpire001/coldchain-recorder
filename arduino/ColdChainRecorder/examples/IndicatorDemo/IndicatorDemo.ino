#include <Arduino.h>
#include <ColdChainRecorder.h>
// Potentiometer provides SYNTHETIC temperature; this is NOT a medical or food-grade logger.
#if defined(ARDUINO_ARCH_ESP32)
const int TEMP_POT=34,ALARM_LED=18;
const double ADC_MAX=4095.0;
#else
const int TEMP_POT=A0,ALARM_LED=8;
const double ADC_MAX=1023.0;
#endif
coldchain::Recorder recorder;
void setup(){Serial.begin(115200);pinMode(ALARM_LED,OUTPUT);digitalWrite(ALARM_LED,LOW);}
void loop(){
 double fake_c=-10.0+analogRead(TEMP_POT)*30.0/ADC_MAX;
 uint32_t seconds=millis()/1000UL;
 coldchain::Report r=recorder.record(seconds,fake_c);
 digitalWrite(ALARM_LED,r.alarm?HIGH:LOW);
 Serial.print("synthetic_temp_C=");Serial.print(fake_c);
 Serial.print(" valid=");Serial.print(r.valid);
 Serial.print(" excursion_seconds=");Serial.print(r.excursion_seconds);
 Serial.print(" alarm_LED=");Serial.println(r.alarm);
 delay(1000);
}
