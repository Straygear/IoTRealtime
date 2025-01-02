
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
    unsigned int rd=(rand() % 2000) + 1;
    while(h-- && status) {
      std::this_thread::sleep_for(std::chrono::nanoseconds(rd));
      int temp;
      temp=buf->haalUitBuf();
      result += temp;
    }
    tussenstanden.push_back(result);

}

