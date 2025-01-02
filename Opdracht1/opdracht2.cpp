#include <iostream>
#include <unistd.h>
#include <iostream>
#include "Timer.h"
#include <thread>

using namespace std;

class Werker {
	public:
		Werker(char c, unsigned int t, unsigned int a) :character (c), tijd(t), aantal(a){}
		void doeIets(){
			for(int i=0;i<aantal;++i) {
        			cout<<character<<flush;       //flush leeg output buffer (print direct)
        			usleep(100000*tijd);
   			 }
        			cout<<endl;
		}
	private:
	        char character;
		unsigned int tijd;
		unsigned int aantal;
};

void doeIets(char c,unsigned int tijd,unsigned int aantal);
int main() {
   
   Werker p('p',5,8);   //print a wacht 0.5 sec doe het 8 keer
   Werker a('a',10,8);
   Werker b('b',15,8);
   Werker c('c',20,8);

  Timer tm1;
  tm1.Reset();
   thread t1(&Werker::doeIets,p);
   thread t2(&Werker::doeIets,a);
   thread t3(&Werker::doeIets,b);
   thread t4(&Werker::doeIets,c);
   t1.join(); t2.join(); t3.join(); t4.join();
  tm1.Stop();
  cout<<tm1.deTijd()<<"  "<<tm1.deNtijd()<<endl;
 
   return 0;
}



