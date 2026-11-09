#ifndef LORD_SUMI_COLDCHAIN_RECORDER_H
#define LORD_SUMI_COLDCHAIN_RECORDER_H
#include <math.h>
#include <stdint.h>
namespace coldchain {
struct Settings {
 double min_c,max_c;uint32_t alarm_after_seconds;
 Settings(double minimum=2,double maximum=8,uint32_t delay=300):
  min_c(minimum),max_c(maximum),alarm_after_seconds(delay){}
};
struct Report {
 bool valid,out_of_range,alarm;uint32_t excursion_seconds;
 Report(bool v,bool out,bool a,uint32_t t):
  valid(v),out_of_range(out),alarm(a),excursion_seconds(t){}
};
inline bool valid_settings(const Settings&s){
 return isfinite(s.min_c)&&isfinite(s.max_c)&&s.min_c<s.max_c;
}
class Recorder {
 public:
 explicit Recorder(Settings settings=Settings()):
  settings_(settings),has_last_(false),has_start_(false),last_(0),excursion_start_(0){}
 Report record(uint32_t timestamp,double temperature_c){
  if(!valid_settings(settings_)||(has_last_&&timestamp<=last_)||!isfinite(temperature_c))
   return Report(false,true,true,0);
  bool outside=temperature_c<settings_.min_c||temperature_c>settings_.max_c;
  if(outside&&!has_start_){has_start_=true;excursion_start_=timestamp;}
  uint32_t duration=outside?timestamp-excursion_start_:0;
  bool alarm=outside&&duration>=settings_.alarm_after_seconds;
  if(!outside)has_start_=false;
  last_=timestamp;has_last_=true;
  return Report(true,outside,alarm,duration);
 }
 private:
 Settings settings_;bool has_last_,has_start_;uint32_t last_,excursion_start_;
};
}
#endif
