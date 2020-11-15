#include <iostream>
#include <ac_int.h>
#include <ac_fixed.h>
#include <ac_channel.h>
#include <cstdlib>
#include <ctime>

typedef ac_channel<ac_int<4,false> > channel;

void runlegth_encode(channel &in, channel &out){
	ac_int<4, false> counter = 1;
	ac_int<4, false> ifcounter = 0;
	ac_int<4, false> elsecounter = 0;
	ac_int<4, false> a[10] = 0;
	ac_int<4, false> b[10] = 0;
	ac_int<4, false> c[20] = 0;
	if(in.available(10)) for (int i=0; i<10; i++) a[i] = in.read();
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

int main(){
    channel in;
    channel out;
    ac_int<4, false> a[10] = 0;
    std::srand(std::time(0));
    for (int i=0;i<10;i++){
    for (int i=0;i<10;i++){
    	a[i] = std::rand();
        in.write(a[i]);
	};
    runlegth_encode(in, out);
    std::cout << "input: ";
    for(int i=0; i<10;i++) std::cout<<a[i] << " ";
    std::cout<<std::endl<<"output: ";
    while(out.available(1)) std::cout << out.read() << " ";
    std::cout<<std::endl;
}
}
