#include "verwerker.hpp"
#include "Buffer.hpp"
#include <iostream>
using namespace std;

int Verwerker::result = 0;
vector<int> Verwerker::tussenstanden;

Verwerker::Verwerker(Buffer* b,int h): buf(b), status(true),hoeveel(h) {

}

void Verwerker::zetUit() {
    status=false;
}

int Verwerker::hetResultaat() {
    return result;
}
void Verwerker::aantalTeLezenData(int d) {
    hoeveel=d;
}
vector<int> Verwerker::deTussenstanden() {
    return tussenstanden;
}
void Verwerker::verwerkData() {
    status=true;
    int h=hoeveel;
    unsigned int rd=(rand() % 2000) + 1;
    while(h-- && status) {
      int temp;
      temp=buf->haalUitBuf();
      result += temp;
      std::this_thread::sleep_for(std::chrono::nanoseconds(rd));
    }
    tussenstanden.push_back(result);
}
