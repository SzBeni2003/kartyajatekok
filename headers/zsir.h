#pragma once
#include "pakli.hpp"

class Jatekos {
	std::string nev;
	Pakli& kez;
	Pakli& vitt;
public:
	Jatekos(std::string nev) :nev(nev), kez(empty()), vitt(empty()){}
	Kartya* play(size_t which);
	size_t count();
	size_t kezSize() const { return kez.size(); }
	void get(Kartya* k) { kez.newcard(k); delete k;}
	void elvisz(Kartya** k, size_t n) {
		for (size_t i = 0; i < n; ++i)
			vitt.newcard(*k[i]);
	}
	void elvisz(Pakli& p){
		vitt+=p;
	}
	std::string getName() const { return nev; }
	void show() const {
		kez.peek();
	}
	bool haveNum(size_t n) {
		for (size_t i = 0; i < kez.size(); ++i)
			if (kez[i]->getNum() == n) return true;
		return false;
	}
	Kartya* operator[](size_t i)const {return kez[i];}
	void showVitt() const{
		vitt.peek();
	}
	~Jatekos(){
		//std::cout<<"dtor Jatekos"<<std::endl;
		delete& kez;
		delete& vitt;
	}
};

class Zsir {
	Jatekos* jatekosok[2];
	Pakli& huzo;
	Pakli& lerakott;
	size_t kov;
public:
	Zsir(std::string nev1, std::string nev2):huzo(empty()), lerakott(empty()), kov(0){
		huzo.magyarpakli();
		jatekosok[0]= new Jatekos(nev1);
		jatekosok[1]= new Jatekos(nev2);
	}
	void draw();
	std::string getName(size_t idx){
		if(idx>2)throw std::out_of_range("tulindexeles");
		return jatekosok[idx]->getName();
	}
	int zsirCount(size_t idx){
		if(idx>2)throw std::out_of_range("tulindexeles");
		return jatekosok[idx]->count();
	}
	friend int zsirMain(Zsir&);
	friend int playing(Jatekos*, Zsir&, bool, size_t);
	~Zsir(){
		//std::cout<<"dtor Zsir"<<std::endl;
		delete& huzo;
		delete& lerakott;
		delete jatekosok[0];
		delete jatekosok[1];
	}
};

int zsirMain(Zsir& game);