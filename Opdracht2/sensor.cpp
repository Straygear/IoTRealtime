
#include "Buffer.hpp"
#include "Sensor.hpp"

void Sensor::genereerdData() {
    stand = begin;
    int h=hoeveel;
    unsigned int rd=(rand() % 2000) + 1;
    while(h--) {
       int x=stand++;
       if (stand > eind) stand=begin;
       buf -> zetInBuf(x);
       std::this_thread::sleep_for(std::chrono::nanoseconds(rd));
    }
}
void Sensor::aantalTeGenererenData(int d) {
    hoeveel=d;
}

Sensor::Sensor(int b,int e,int h,Buffer* bf): begin(b),eind(e),hoeveel(h),stand(0),buf(bf) {
}

