#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

unsigned short int checksum(unsigned int x){
	unsigned short int result;
	if (x!=0){
		int length = (int)log10 (x) + 1;
		unsigned short int array[length];
		int i = 0;
		while (x >= 10){
			array[i] = x%10;
			x = (int)x/10;
			i++;
		}
		array[length - 1] = x;
		bool doublee = 0;
		for(int j=0; j<length; j++){
			if(doublee) {
				if(2*array[j]<10) result = result + 2*array[j];
				else result = result + (2*array[j])%10 + (int)(2*array[j])/10;
			}
			else result = result + array[j];
			doublee = !doublee;
		}
	}
	else result = 0;
	return result;
}

int main(){
	unsigned int x;
	std::srand(std::time(0));
	for (int i=0; i<10; i++){
		x = std::rand();
		std::cout << x << std::endl;
		std::cout << checksum(x) << std::endl;
	}
	return 0;
}

