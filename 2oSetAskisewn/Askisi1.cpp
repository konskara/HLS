#include <iostream>
#include <string>
#include <ac_int.h>
#include <ac_channel.h>
#include <ac_fixed.h>

ac_int<18,true> e(ac_int<8,false> a, ac_int<8,false> b, ac_int<9,true> c, ac_int<9,true> d){
	return a*b+c*d;
}

ac_fixed<10,6,true> h(ac_fixed<5,2,false> f, ac_fixed<5,4,true> g){
	return f*g;
}

int main(){
    std::cout << e(255,255,255,255) <<std::endl; //largest positive: 13050, a,b = 8'b11111111 , c,d = 9'b011111111
    std::cout << e(0,0,-255,255) <<std::endl; //smallest negative: -65025, a,b > 0  => a=b=0 , c = 9'b111111111, d = 9'b01111111
    std::cout << h(3.875, 7.5) <<std::endl; //largest positive: 290625, f = 11.111 , g = 0111.1
    std::cout << h(3.875, -7.5) <<std::endl; //smallest negative: -29.0625 , f = 11.111, g = 1111.1
    std::cout << "0" << h(0.125, 0.5) <<std::endl; //testing the fixed point: smallest decimal part = 0.0625 = 2^(-4)
}
