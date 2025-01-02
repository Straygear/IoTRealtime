//
//  Buffer.hpp
//  sensoren
//
//  Created by John Vi on 4/26/19.
//  Copyright © 2019 John Vi. All rights reserved.
//

#ifndef Buffer_hpp
#define Buffer_hpp

#include <stdio.h>
#include <mutex>
#include <condition_variable>
#include <atomic>
//#include <semaphore>


using namespace std;


#define GROOTTE 2
class Buffer {
    
public:
    void zetInBuf(int);
    int haalUitBuf();
    void notifyAll();
    int hoeveel() const;
    void tellerPlusPlus();
    void tellerMinMin();
    void checkBuffer(string);
private:
    int in=0;
    int out=0;
    atomic<int> teller=0;
    int opslag[GROOTTE];
    //std::counting_semaphore<1> sem{1},tel{teller};
    mutex m1, m2;
    condition_variable cv;

 
};
#endif /* Buffer_hpp */

