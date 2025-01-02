#include "Buffer.hpp"
#include "Sensor.hpp"
#include <thread>
#include <chrono>
#include <iostream>

void Sensor::genereerdData() {
    stand = 0;
    int h=hoeveel;
    unsigned int rd=(rand() % 2000) + 1;
    while(h--) {
       //cout<<"timer genereer data "<<rd<<endl;
       std::this_thread::sleep_for(std::chrono::nanoseconds(rd));
       int x=stand++;
       if (stand > eind) stand=begin;
      //buf->checkBuffer("genereerData");
       buf -> zetInBuf(x);
       buf->notifyAll();
       //cout << "Werker Notified...: " << this_thread::get_id() << endl;
    }
   // buf->notifyAll();
}
void Sensor::aantalTeGenererenData(int d) {
    hoeveel=d;
}

Sensor::Sensor(int b,int e,int h,Buffer* bf): begin(b),eind(e),hoeveel(h),stand(0),buf(bf) {
}


