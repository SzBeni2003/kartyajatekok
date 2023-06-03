#include "../headers/pakli.hpp"

void Pakli::magyarpakli()
{
    for(size_t i=0;i<n;++i)delete kartyak[i];
	n=0;
	Magyar m;
	for (size_t c = 0; c < 4; ++c)
		for (size_t n = 7; n < 15; ++n){
			m=Magyar(c, n);
			newcard(m);
		}
	shuffle();
}

void Pakli::franciapakli() {
	for(size_t i=0;i<n;++i)delete kartyak[i];
	n=0;
	Francia f;
	for (size_t c = 0; c < 4; ++c)
		for (size_t n = 2; n < 15; ++n){
			f=Francia(c, n);
			newcard(f);
		}
	shuffle();
}

Pakli& empty() {
	Pakli* p = new Pakli();
	return *p;
}

Pakli& Pakli::operator+=(const Pakli& rhs){
	for (size_t i=0;i<rhs.size();++i){
		newcard(rhs[i]);
	}
	return *this;
}