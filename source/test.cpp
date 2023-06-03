#include "../headers/zsir.h"
#include "../headers/poker.hpp"
#include "../headers/gtest_lite.h"
#include "../headers/kartya.h"
#include <iostream>
#include <sstream>

/*int main() {
	
	TEST(Pakli, Kartya){
		Francia f(1, 12);
		EXPECT_EQ((size_t)1, f.getCol());
		EXPECT_EQ((size_t)12, f.getNum());
		Magyar m(2, 10);
		Pakli p;
		p.newcard(f);
		p.newcard(m);
		EXPECT_EQ((size_t)2, p.size());
		Kartya** m1=p.takeTop(1);
		EXPECT_EQ((size_t)10, m1[0]->getNum());
		delete m1[0];
		delete[] m1;
		std::stringstream ss;
		Francia f1(5, 4);
		EXPECT_THROW(f1.display(ss), char const*);
	}END
	TEST(Pakli, Sum){
		Pakli p1;
		Magyar m1(2, 7);
		p1.newcard(m1);
		Magyar m2(4, 11);
		p1.newcard(m2);
		Pakli p2;p2.magyarpakli();
		EXPECT_EQ((size_t)32, p2.size());
		EXPECT_EQ((size_t)2, p1.size());
		p2+=p1;
		EXPECT_EQ((size_t)34, p2.size());
		EXPECT_EQ((size_t)7, p2[32]->getNum());
	}END

	return 0;
}*/