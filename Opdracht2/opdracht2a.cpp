//
//  main.cpp
//  sensoren
//
//  Created by John Vi on 4/26/19.
//  Copyright © 2019 John Vi. All rights reserved.
//

#include "Buffer.hpp"
#include "Sensor.hpp"
#include "verwerker.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <future>

using namespace std;




int main(int argc, const char * argv[]) {
    Buffer opslag;
    Sensor s1(1,10,100,&opslag);
    Sensor s2(100,110,100,&opslag);
    Sensor s3(1000,1010,100,&opslag);
     //te genereren data tssen de 1 en de 9 aantal 10
    Verwerker vw1(&opslag,100);
    Verwerker vw2(&opslag,100);

    vector<future<void>> futures;
    
    cout<<"start" <<endl;
    srand((unsigned) time(0));
    for(int n=0;n<1;n++) {
      futures.clear(); // Clear previous futures

        // Start sensor threads
        futures.push_back(async(launch::async, &Sensor::genereerdData, &s1));
        futures.push_back(async(launch::async, &Sensor::genereerdData, &s2));
        futures.push_back(async(launch::async, &Sensor::genereerdData, &s3));

        // Start worker threads
        futures.push_back(async(launch::async, &Verwerker::verwerkData, &vw1));
        futures.push_back(async(launch::async, &Verwerker::verwerkData, &vw2));

        // Wait for all threads to finish
        for (auto& f : futures) {
            f.get(); 
        }

      
    }
    std::cout << "Hello, IoT "<<vw1.hetResultaat()<<endl;
    vector<int> ts=vw1.deTussenstanden();

    for(auto i:ts) {
        cout<<i <<" tussenstanden ";
    }
    cout<<endl;

    return 0;
}

