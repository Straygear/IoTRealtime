
//
//  verwerker.hpp
//  sensoren
//
//  Created by John Vi on 4/26/19.
//  Copyright © 2019 John Vi. All rights reserved.
//
#ifndef verwerker_hpp
#define verwerker_hpp

#include <stdio.h>
#include <vector>
using namespace std;

class Buffer;
class Verwerker {
public:
    Verwerker(Buffer*,int);
    void verwerkData();
    void zetUit();
    static int hetResultaat();
    void aantalTeLezenData(int);
    static vector<int> deTussenstanden();
private:
    static vector<int> tussenstanden;
    int hoeveel;
    Buffer *buf;
    static int result;
    bool status;
};
#endif /* verwerker_hpp */
