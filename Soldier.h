#include "dsexceptions.h"
#include <iostream>

class Soldier{
	enum side { SPARTAN, PERSIAN, NONE };
	int id; //key in Hash Table (value in PQ)
	int life;
	bool dead;
	int turn; //key in BinHeap
	side mySide; //which side the soldier belongs to

public:
	bool operator<(const Soldier& rhs) const {
		if (turn < rhs.turn){
			return true;
		}
		return false;
	}

	int returnSide() const {
		if (mySide == SPARTAN)
			return 0;
		return 1;
	}

	int returnID() const { return id; }

	void setTurn(int turn){ this->turn = turn; }

	int returnTurn() const { return turn; }

	bool getStatus(){
		return (dead);
	}

	Soldier(int id, int turn, int side){
		this->id = id;
		this->turn = turn;
		if (side == 0){
			mySide = SPARTAN;
		}
		if (side == 1){
			mySide = PERSIAN;
		}
		dead = false;
		life = 0;
	}

	Soldier(){
		id = 0;
		turn = 0;
		life = 0;
		dead = false;
		mySide = NONE;
	}

	void soldierAttacked(){
		if(life < 3){ 
			life++; 
		}
		if(life == 3){ 
			dead = true; 
		}
	}

	void woundCount(){
		std::cout << life;
	}

};