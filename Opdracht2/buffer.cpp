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
    leeg.acquire(); //aantal lege plekken
    sensor.acquire(); //Toegang tot maximaal 3 threads
    opslag[in++]=d;
    in %=GROOTTE;
    std::lock_guard<mutex> telck(teller_mutex);
    teller++;
    verwerken.release();
    vol.release();
    std::lock_guard<mutex> lck(m1);
    cout << "Zet in buf ThreadID: " << std::this_thread::get_id() <<" Teller: " << teller-1 << " Waarde: " << d << endl;// niet thread safe
    }
//}

int Buffer::haalUitBuf() {
    int waarde;
    vol.acquire(); //Controleer als buffer vol is
    verwerken.acquire(); //Toegang tot maximaal 2 threads
    waarde=opslag[out++];
    out %=GROOTTE;
    std::lock_guard<mutex> telck(teller_mutex);
    teller--;
    sensor.release();
    leeg.release();
    std::lock_guard<mutex> lck(m1);
    cout << "haal uit buf ThreadID: " << std::this_thread::get_id() <<" Teller: " << teller <<endl;
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
