#pragma once
#include "pakli.hpp"
#include<iostream>
#include<string>

/**
 * A legjobb kéz meghatározásához szükséges
*/
struct Hand{
	size_t highs[2];
	size_t handtype;
	Hand(){highs[0]=0;highs[1]=0;handtype=0;}
	~Hand(){}
};

/**
 * Pókerjátékos.
 * név, pénz, kéz
 * contribution - az adott körben mennyi pézt tett eddig bele
 * handeval - milyen a legjobb keze a játékosnak
*/
class Player{
	std::string name;
	size_t money;
	size_t contribution;
	bool ig;
	Pakli& hand;
	Hand handeval;
public:
	Player(const char* nev, size_t money=4000) :name(nev), money(money), hand(empty()) {}
	//Kártyák megtekintése
	void const peek() { hand.peek();}
	//megkapja a neki osztott lapokat
	void getDealtto(Pakli& p){
		hand+=p;
		delete& p;
	}
	//megkapja a nyereményét
	void win(size_t m){money+=m;}
	//visszaadja a kezének az értékét
	Hand getHand(){return handeval;}
	//kiértékeli a legjobb kezet
	void eval(Pakli&);

	bool continueGame();
	std::string getName() { return name; }
	//játékban van-e épp (bedobta-e a lapjait)
	bool isIG() const{return ig;}
	void setIG(bool b){ig=b;}
	//licitkör
	int holdnbet(size_t b);
	//vak befizetése (kis/nagy, összeget az asztalnál állítom be)
	void blind(size_t x){money-=x;contribution+=x;}
	size_t getCon() const {return contribution;}
	//új játék kezdése; kártyák törlése
	void reset(){
		hand.clean();
		setIG(true);
		contribution=0;
	}

	~Player(){
		delete& hand;
	}
};

/**
 * Póker játszmakezelő
 * Tárolja a téteket, a játékosokat, a paklit, közös lapokat, és az égetett lapokat.
 * highestBet - a legmagasabb összlicit egy játékostól
 * currentDealer - az osztó játékos indexe. Az osztó fizeti a nagyvakot, az után következő a kisvakot
*/
template<size_t maxplayers=6>
class PokerAsztal {
	size_t pot;
	size_t highestBet;
	Pakli& deck;
	Pakli& burnt;
	Pakli& community;
	size_t playercount;
	size_t currentDealer;
	Player* players[maxplayers];
	enum state{Begin, Flop, Turn, River} currentstate;
public:
	PokerAsztal():pot(0), highestBet(0), playercount(0), deck(empty()), burnt(empty()), community(empty()){deck.franciapakli();}
	PokerAsztal(Player** player, size_t playercount):playercount(playercount), pot(0), highestBet(0), deck(empty()), burnt(empty()), community(empty()){
		deck.franciapakli();
		for(size_t i=0;i<playercount;++i)
			players[i]=player[i];
	}
	//licitkör. Addig licitálnak, amíg vissza nem ér a kör az utolsó emelőhöz
	void bettingRound(size_t starter, bool first);
	//osztás. Az elején a játékosoknak 2-2 lapot, majd később a közös lapokat osztja le
	void deal();
	void newPlayer(const Player* p) {
		if (playercount >= maxplayers) throw "tele az asztal";
		players[playercount++] = p;
	}
	//Kör vége. Megállapítja a győztest
	void eval();
	//Kilép a játékos
	void sitout(size_t);
	friend int pokerMain(PokerAsztal<>& asztal);

	~PokerAsztal(){
		for(size_t i=0;i<playercount;++i) delete players[i];
		delete& deck;
		delete& burnt;
		delete& community;
	}
};

