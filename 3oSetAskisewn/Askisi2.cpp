#include <iostream>
#include <ac_int.h>
#include <ac_fixed.h>
#include <ac_channel.h>
#include <cstdlib>
#include <ctime>

typedef ac_int<4,false> dtype;
typedef ac_channel<dtype> channel;

class BlackJack {
	private:
		ac_int<6, false> counter;
		dtype card;
		dtype ace;
		dtype total;
	public:
		BlackJack(){
			reset();
		}
		void reset(){
			counter = 0;
			card = 0;
			ace = 0;
			total = 0;
		}
	    void run (channel &in_card, bool &end_round, bool &win){
	    	if(in_card.available(1)){
	    		total = total + 1;
	    		card = in_card.read();
	    		if(card == 1) {
				    counter = counter + 11;
				    if (total < 3) ace = ace + 1;
			    }
	    	    else counter = counter + card;
	    	    if ((ace == 2 )|| (counter == 21 && total == 4) || (counter < 21 && total == 5)){
	    	    	win = 1; 
					end_round = 1;
				}
				if ((counter > 21 && total > 3) || (counter == 21 && total == 5)) {
					win = 0; 
					end_round = 1;
				}
				if (end_round == 1) reset();
	        }
	    }
};
			

int main(){
	channel in_card;
	dtype x;
	bool win;
	bool end_round;
    BlackJack Q;
	std::srand(std::time(0));
	for (int i = 0; i<10;i++){
	win = 0;
	end_round = 0;
	while(end_round != 1){ 
	    x = std::rand()%10+1;
	    in_card.write(x);
	    std::cout << x << " ";
	    Q.run(in_card, end_round, win);
	};
	std::cout << std::endl << "win: " << win << " end_round: " << end_round <<std::endl;
}
}
