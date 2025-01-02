//
//  Buffer.cpp
//  sensoren
//
//  Created by John Vi on 4/26/19.
//  Copyright © 2019 John Vi. All rights reserved.
//

#include "Buffer.hpp"
#include <iostream>
#include <unistd.h>


using namespace std;


void Buffer::zetInBuf(int d) {
    //while(teller == GROOTTE);
    std::unique_lock<std::mutex> lck(m1);
    cout<<"zetIn Lock "<<hoeveel()<<endl;
    cv.wait(lck, [this]{return hoeveel() <= GROOTTE;});
    opslag[in++]=d;
    in %=GROOTTE;
    teller++;
    cout<<"Unlocked "<<hoeveel()<<endl;
    }
//}

int Buffer::haalUitBuf() {
    int waarde;
    //while(teller==0);
    std::unique_lock<std::mutex> lck(m1);
    cout<<"Haaluit Lock "<<hoeveel()<<endl;
    cv.wait(lck, [this]{return !hoeveel() >= 0;});
   // cout<<"hier in haalUitBuf"<<endl;
    waarde=opslag[out++];
    out %=GROOTTE;
    teller++;
    cout<<"Unlocked "<<hoeveel()<<endl;
    return waarde;
}

void Buffer::notifyAll() {
    std::lock_guard<std::mutex> lck(m1);
    cv.notify_one();
}

int Buffer::hoeveel() const {
    return teller;
}

void Buffer::tellerPlusPlus(){
    teller++;
}

void Buffer::tellerMinMin(){
    teller--;
}

void Buffer::checkBuffer(string func){
    int aantal = 0;
    if(hoeveel() == GROOTTE){
        cout << "Buffer is vol in " << func << " teller is: " << hoeveel() << endl;
    }else {
        aantal = GROOTTE - hoeveel();
        cout << "Aantal plekken nog in de buffer bij " << func << ": " << aantal << endl;
    }
}
