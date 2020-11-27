#include <iostream>
#include <ac_int.h>
#include <ac_fixed.h>
#include <ac_channel.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream> 


static const int N = 3;


void graphcolor(bool adj_G[N][N], unsigned int color_G[N], unsigned int &chnumber){
	int j;
	for (int i=0; i<N; i++){
		color_G[i] = 1;
		j = i - 1;
    	while(j>-1) {
    		if (adj_G[i][j] == 1 && color_G[i] == color_G[j]){
    			color_G[i] += 1;
    			j = i - 1;
			}else j -= 1;
		}
	}
	chnumber = *std::max_element(color_G, color_G + N);	
}


int main(){
	std::srand(std::time(0));
	unsigned int color_G[N];
	unsigned int chnumber;
	bool adj_G[N][N];
	bool x;
	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			x = std::rand()%2;
			adj_G[i][j] = x;
			adj_G[j][i] = x;
		}
	}
	graphcolor(adj_G, color_G, chnumber);
	std::cout<<"graph: ";
	for (int i=0;i<N;i++){
		std::cout<<std::endl;
		for(int j=0;j<N;j++){
			std::cout<<adj_G[i][j]<<" ";
		}
	}
	std::cout<<std::endl<<"color: ";
	for (int i=0;i<N;i++) std::cout<<color_G[i]<<" ";
	std::cout<<std::endl<<"chromatic number: "<< chnumber;
}
