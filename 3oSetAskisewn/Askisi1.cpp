#include <iostream>
#include <ac_int.h>
#include <ac_fixed.h>
#include <ac_channel.h>
#include <cstdlib>
#include <ctime>

static const int n = 10;

typedef ac_int<4,false> dtype;
typedef ac_channel<dtype> channel;

class RunLengthEncoder{
	private: 
		dtype counter;
		dtype ifcounter;
		dtype elsecounter;
		dtype a[n];
		dtype b[n];
		dtype c[2*n];
    public:
	    RunLengthEncoder() {
	    	reset();
		}
		void reset(){
			b[n] = 0;
	    	a[n] = 0;
	    	c[2*n]=0;
	    	counter = 1;
	    	elsecounter =0;
	    	ifcounter = 0;
		}
        void run (channel &in, channel &out) {
            reset();
        	if(in.available(1)) for(int i=0;i<n;i++) a[i] = in.read();
        	for (int i=0;i<10;i++){
		if(a[i] == a[i+1]){
			counter = counter + 1;
			ifcounter = ifcounter + 1;
     	}
	    else{
	    	ac_int<5, false> fail = 2*(i-ifcounter);
	    	c[fail] = a[i];
	        b[i-ifcounter] = counter;
	        elsecounter = elsecounter + 1;
		    counter = 1;
	    }
	}   
  	for (int i=0; i<elsecounter; i++){
		c[2*i+1] = b[i];
	}
    for (int i=0;i<2*elsecounter;i++) out.write(c[i]);
	    }
};

int main(){
	RunLengthEncoder Q;
    channel in;
	channel out;
	dtype a[n];
	std::srand(std::time(0));
	for (int i=0;i<10;i++){
	for(int i=0;i<n;i++) {
		a[i]=std::rand();
		in.write(a[i]);
	};
	Q.run(in, out);
    std::cout << "input: ";
    for(int i=0; i<10;i++) std::cout<< a[i] << " ";
    std::cout<<std::endl<<"output: ";
    while(out.available(1)) std::cout << out.read() << " ";
    std::cout<<std::endl;
}
}
