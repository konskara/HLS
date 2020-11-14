#include <iostream>
#include <ac_int.h>
#include <ac_fixed.h>
#include <ac_channel.h>
#include <cstdlib>
#include <ctime>

static const int W = 5;
static const int Wout = 2*W;

template<int W>
void csd_encode (ac_int<W,true> &num, ac_int<W,false> &x_p, ac_int<W,false> &x_m){
	int carry = 0;
	ac_int<W+1,false> x = num;
	x[W] = x[W-1];
	for (int i = 0; i < W; i++){
		if(carry == 0){
			if(x[i+1] == 0 && x[i] == 0 || x[i+1] == 1 && x[i] == 0){
				x_m[i] = 0;
                x_p[i] = 0;
			}
			if(x[i+1] == 0 && x[i] == 1){
				x_m[i] = 0;
				x_p[i] = 1;
			}
			if(x[i+1] == 1 && x[i] == 1){
				x_m[i] = 1;
				x_p[i] = 0;
				carry = 1;
			}
		}
		else if(carry == 1){
			if(x[i+1] == 1 && x[i] == 0){
				x_m[i] = 1;
				x_p[i] = 0;
		    }
		    if(x[i+1] == 0 && x[i] == 0){
		    	x_m[i] = 0;
		    	x_p[i] = 1;
		    	carry = 0;
			}
			if(x[i+1] == 0 && x[i] == 1 || x[i+1] == 1 && x[i] == 1){
				x_m[i] = 0;
				x_p[i] = 0;
			}
		}
	}
}



ac_int<Wout,true> csd_mult (ac_int<W,true> &in, ac_int<W,false> &x_p, ac_int<W,false> &x_m){
	ac_int<Wout, true> sum = 0;
	for (int i = 0; i < W; i++){
		if(x_p[i] == 1)  sum = sum + ((ac_int<Wout-1, true>) in << i);
		else if(x_m[i] == 1) sum = sum - ((ac_int<Wout-1, true>) in <<i);
	}
	return sum;
}

int main(){
	ac_int<W,true> in;
	ac_int<W,true> num;
	ac_int<W,false> x_p;
	ac_int<W,false> x_m;
	for(int i=0; i<10; i++){
	num = std::rand();
	in = std::rand();
	csd_encode(num, x_p, x_m);
	std::cout << "CSD of num = " << num << " is x_p = " << x_p <<" and x_m = " << x_m << std::endl; 
	std::cout << num << " * " << in << " = " << csd_mult (in, x_p, x_m) << std::endl;
	}
}


