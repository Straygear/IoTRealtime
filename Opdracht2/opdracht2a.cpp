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
    Sensor s1(1,10,10,&opslag);
    Sensor s2(101,110,10,&opslag);
    Sensor s3(1001,1010,10,&opslag);
     //te genereren data tssen de 1 en de 9 aantal 10
    Verwerker vw1(&opslag,15);
    Verwerker vw2(&opslag,15);


    vector<future<void>> futures;
    srand((unsigned) time(0));
    
    cout<<"start" <<endl;
    srand((unsigned) time(0));
    for(int n=0;n<1;n++) {
     /*futures.clear(); // Clear previous futures

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
        }*/
       thread t1(&Sensor::genereerdData,&s1);
       thread t2(&Sensor::genereerdData,&s2);
       thread t3(&Sensor::genereerdData,&s3);

       thread t4(&Verwerker::verwerkData,&vw1);
       thread t5(&Verwerker::verwerkData,&vw2);

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
      
    }
    int results = Verwerker::hetResultaat();
    std::cout << "Hello, IoT "<< results <<endl;

    auto tussenstanden = Verwerker::deTussenstanden();

    for(const auto& i: tussenstanden) {
        cout<<i <<" ";
    }
    cout<<endl;

    return 0;
}

