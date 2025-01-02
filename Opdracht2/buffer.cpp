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
#include <thread>


using namespace std;


void Buffer::zetInBuf(int d) {
    //while(teller == GROOTTE);
    if(!leeg.try_acquire()){
        cout << "Geen plek.... opnieuw proberen" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    sensor.acquire();
    opslag[in++]=d;
    in %=GROOTTE;
    //teller++;
    sensor.release();
    vol.release();
    std::lock_guard<mutex> lck(m1);
    cout << "Zet in buf ThreadID: " << std::this_thread::get_id() << " Waarde: " << d << endl;
    }
//}

int Buffer::haalUitBuf() {
    int waarde;
    if(!vol.try_acquire()){
        cout<< "Buffer vol... opnieuw proberen " << endl;
         std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    verwerken.acquire();
    waarde=opslag[out++];
    out %=GROOTTE;
    //teller++;
    verwerken.release();
    leeg.release();
    std::lock_guard<mutex> lck(m1);
    cout << "haal uit buf ThreadID: " << std::this_thread::get_id() << " Waarde: " << waarde << endl;
    return waarde;
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
