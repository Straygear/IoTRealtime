
#include "verwerker.hpp"
#include "Buffer.hpp"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

Verwerker::Verwerker(Buffer* b,int h): buf(b), result(0), status(true),hoeveel(h) {
    
}

void Verwerker::zetUit() {
    status=false;
}

int Verwerker::hetResultaat()const {
    return result;
}
void Verwerker::aantalTeLezenData(int d) {
    hoeveel=d;
}
vector<int> Verwerker::deTussenstanden() const {
    return tussenstanden;
}
void Verwerker::verwerkData() {
    status=true;
    int h=hoeveel;
    //cout<<"timer "<<rd<<endl;
    unsigned int rd=(rand() % 2000) + 1;
    while(h-- && status) {
      //cout<<"timer verwerk data "<<rd<<endl;
      std::this_thread::sleep_for(std::chrono::nanoseconds(rd));
      int temp;
     // buf->checkBuffer("verwerkData");
      temp=buf->haalUitBuf();
      result += temp;
      buf->notifyAll();
      //cout << "Verwerker Notified: " << this_thread::get_id() << endl;
    }
    tussenstanden.push_back(result);

}

