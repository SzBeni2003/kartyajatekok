#pragma once
#include <iostream>
#include <string>
#define JPORTA

/**
 * Absztrakt kártya osztály
*/
class Kartya {
	size_t col, num;
public:
	Kartya(size_t c=0,size_t n=1):col(c),num(n) {}
	Kartya(Kartya& c):col(c.col), num(c.num){}
	virtual Kartya* clone() const=0;

	size_t getCol() const { return col; }
	size_t getNum() const { return num; }
	virtual void display(std::ostream& os=std::cout) = 0;
	virtual ~Kartya() {}
};

/**
 * Francia kártyalap
*/
class Francia :public Kartya {
public:
	Francia(size_t c = 0, size_t n = 1) :Kartya(c, n) {/*std::cout<<"ctor Francia: ";display();*/}
	Francia(const Kartya& c):Kartya(c.getCol(), c.getNum()){}
	Francia(const Kartya* c):Kartya(c->getCol(), c->getNum()){}
	Francia* clone() const {return new Francia(this);}

	void display(std::ostream& os = std::cout) {
		if (getCol() > 3 || getNum() <= 1 || getNum() > 14)throw "Invalid card";
		std::string c;
		switch(getCol()){
			case 0:c="Kor ";break;
			case 1:c="Treff ";break;
			case 2:c="Karo ";break;
			case 3:c="Pikk ";break;
		}
		size_t nu = getNum();
		std::string n;
		switch(nu){
			case 14:n="A";break;
			case 13:n="K";break;
			case 12:n="Q";break;
			case 11:n="J";break;
			default:n=std::to_string(nu);
		}
		os << c << n;
	}
	~Francia(){/*std::cout<<"dtor Francia: ";display();*/}
};

/**
 * Magyar kártyalap
*/
class Magyar :public Kartya {
public:
	Magyar(size_t c = 0, size_t n = 7) :Kartya(c, n) {}
	Magyar(Kartya& c):Kartya(c.getCol(), c.getNum()){}
	Magyar(const Kartya* c):Kartya(c->getCol(), c->getNum()){}
	Magyar* clone() const {return new Magyar(this);}
	void display(std::ostream& os=std::cout) {
		if (getCol() > 3 || getNum() <7 || getNum() > 14)throw "Invalid card";
		std::string c;
		switch (getCol()) {
		case 0:
			c = "Piros"; break;
		case 1:
			c = "Tok"; break;
		case 2:
			c = "Makk"; break;
		case 3:
			c = "Zold"; break;
		}
		std::string n;
		switch (getNum()) {
		case 14:
			n = "Asz"; break;
		case 13:
			n = "Kiraly"; break;
		case 12:
			n = "Felso"; break;
		case 11:
			n = "Also"; break;
		case 10:
			n = "10"; break;
		case 9:
			n = "9"; break;
		case 8:
			n = "8"; break;
		case 7:
			n = "7"; break;
		}
		os << c << " " << n;
	}
	~Magyar(){/*std::cout<<"dtor Magyar: ";display();*/}
};




///nem tudom mit kezdjek ezzel, ez �gy nem j�, az biztos
/*enum fCol { Kor, Treff, Karo, Pikk };
enum fVal{Asz=1, Ketto, Harom, Negy, Ot, Hat, Het, Nyolc, Kilenc, Tiz, Bubi, Dama, Kiraly};
enum mCol{Piros, Tok, Makk, Zold};
enum mVal{Het=7, Nyolc, Kilenc, Tiz, Also, Felso, Kiraly, Asz};

class Francia :public Kartya {
	fCol color;
	fVal value;
public:
	Francia(enum fCol c, enum fVal v) :color(c), value(v) {}
	fCol getCol() const { return color; }
	fVal getVal() const { return value; }
};
std::ostream& operator<<(std::ostream& os, const Francia& k) { return os << k.getCol() << " " << k.getVal(); }

class Magyar :public Kartya {
	mCol color;
	mVal value;
public:
	Magyar(enum mCol c, enum mVal v) :color(c), value(v) {}
	mCol getCol() const { return color; }
	mVal getVal() const { return value; }
};
std::ostream& operator<<(std::ostream& os, const Magyar& k) { return os << k.getCol() << " " << k.getVal(); }
*/
