#include <cassert>
#include <limits>
#include "ColdChainRecorder.h"
int main(){
 using namespace coldchain;
 Recorder r(Settings(2,8,30));
 Report first=r.record(0,10);
 assert(first.valid&&first.out_of_range&&!first.alarm);
 Report alarm=r.record(30,10);
 assert(alarm.valid&&alarm.alarm&&alarm.excursion_seconds==30);
 Report recovered=r.record(31,5);
 assert(recovered.valid&&!recovered.alarm&&!recovered.out_of_range);
 assert(r.record(32,10).excursion_seconds==0);
 Report invalid=r.record(32,10);
 assert(!invalid.valid&&invalid.alarm);
 assert(!r.record(33,std::numeric_limits<double>::quiet_NaN()).valid);
 assert(r.record(34,10).valid);
 Recorder immediate(Settings(2,8,0));
 assert(immediate.record(1,9).alarm);
 Recorder bad(Settings(10,2));
 assert(!bad.record(1,5).valid);
}
