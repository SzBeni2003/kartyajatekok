#ifndef PAKLI_H
#define PAKLI_H
#include "kartya.h"
#include <cstdlib>
#include <algorithm>
#include <ctime>
#define MAXSIZE 104


/**
 * Pakli osztály.
 * Kártyákat tároló tömb.
*/
class Pakli {
	size_t n;
	Kartya *kartyak[MAXSIZE];
public:
	Pakli() :n(0) {}
	Pakli(Kartya** pakli, size_t n /*,enum mode mode = Down*/) :n(n)/*, mode(mode)*/ {
		for (size_t i = 0; i < n; ++i) kartyak[i] = pakli[i];
	}
	Pakli(const Pakli& old):n(old.size()) {
		for (size_t i = 0; i < n; ++i){
			kartyak[i] = old.kartyak[i]->clone();
		}
	}
	~Pakli() {
		//std::cout<<"dtor Pakli"<<std::endl;
		for (size_t i=0;i<n;++i) delete kartyak[i];
	}
	void clean(){
		for(size_t i=0;i<n;++i) delete kartyak[i];
		n=0;
	}
	size_t size() const { return n; }
	//kiírja az összes lapot, amit tárol a Pakli
	void peek() const {
		//if (mode != Restricted)throw "Not allowed!";
		for (size_t i = 0; i < n; ++i) {
			kartyak[i]->display();
			std::cout << std::endl;
		}
	}
	//pakli tetejéről lévő lapo(ka)t leveszi
	Kartya** takeTop(size_t x = 1) {
		if (x > n) throw "Out of range";
		Kartya** kartyakk = new Kartya * [x];
		for (int i = x; i > 0; --i){
			kartyakk[x - i] = kartyak[n - i];
			kartyak[n-i]=nullptr;
		}
		n -= x;
		return kartyakk;
	}
	//kijátssza az i. helyen lévő lapot
	Kartya* play(size_t i) {
		//if (mode != Restricted) throw "Not allowed!";
		if (i >= n) throw "Out of range";
		Kartya* card = kartyak[i];
		for (size_t j = i + 1; j < n; ++j)
			kartyak[j - 1] = kartyak[j];
		kartyak[--n]=nullptr;
		return card;
	}
	//új kártya kerül a pakli tetejére
	//az eredeti kártya lemásolódik
	void newcard(const Kartya& card) {
		if (n >= MAXSIZE)throw "Out of space!";
		kartyak[n++] = card.clone();
	}
	void newcard(const Kartya* card) {
		if (n >= MAXSIZE)throw "Out of space!";
		kartyak[n++] = card->clone();
	}
	//megkeveri a paklit
	void shuffle() {
		std::srand(std::time(0));
		std::random_shuffle(kartyak, kartyak + n);
	}
	//két pakli összevonása
	friend Pakli& operator+(const Pakli& lhs,const Pakli& rhs);
	Kartya* operator[](size_t i){ return kartyak[i]; }
	const Kartya* operator[](size_t i) const {return kartyak[i];}
	Pakli& operator=(Pakli& rhs){
		for (size_t i=0;i<n;++i) delete kartyak[i];
		n=rhs.size();
		for (size_t i=0;i<n;++i){
			kartyak[i]=rhs[i];
		}
		return *this;
	}
	Pakli& operator+=(const Pakli& rhs);
	void resize(size_t x){n=x;}
	void magyarpakli();
	void franciapakli();
};


Pakli& empty();

#endif