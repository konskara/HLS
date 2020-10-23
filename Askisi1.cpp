#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int a[32],i;
unsigned short int c;
int convert(unsigned int y){
	for(i=0; y>0 && i<32; i++){
		a[i]=y%2;
		y=y/2;
	};
	return a[32];
}

unsigned short int counter(){
	for(i=0; i<32; i++){
	    if(a[i]==1) c++;
	    else c=c;
	    a[i]=0;
	}
	return c;
}

int main(){
	unsigned int j;
	std::srand(std::time(0));
	for (int i=0; i<10; i++){
		j = std::rand();
		convert(j);
		std::cout << j << std::endl;
		std::cout << counter() << std::endl;
		c=0;
	}
	return 0;
}



