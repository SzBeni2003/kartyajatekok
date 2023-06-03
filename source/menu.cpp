#include "../headers/zsir.h"
#include "../headers/poker.hpp"
#include "../headers/gtest_lite.h"
#include <iostream>
#include <sstream>

//#define CPORTA


int main() {
	#ifdef CPORTA
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
		Francia f1(2, 7);
		p1.newcard(f1);
		Magyar f2(3, 11);
		p1.newcard(f2);
		Pakli p2;p2.franciapakli();
		EXPECT_EQ((size_t)52, p2.size());
		EXPECT_EQ((size_t)2, p1.size());
		p2+=p1;
		EXPECT_EQ((size_t)54, p2.size());
		EXPECT_EQ((size_t)7, p2[52]->getNum());
		//p2.peek();
	}END
	TEST(Zsir, GameMain){
		Zsir game=Zsir("Beni", "Rego");
		std::cout<<"here I am!\n";
		EXPECT_EQ(std::string("Rego"), game.getName(1));
		EXPECT_THROW(game.getName(3), std::out_of_range);
		int w;
		EXPECT_NO_THROW(w=zsirMain(game));
		switch(w){
		case 0:
			EXPECT_LT(0, game.zsirCount(0)-game.zsirCount(1));
			break;
		case 1:
			EXPECT_GT(0, game.zsirCount(0)-game.zsirCount(1));
			break;
		case 2:
			EXPECT_EQ(0, game.zsirCount(0)-game.zsirCount(1));
			break;
		}
	}END
	#else
	/*{
		Zsir game("Beni", "Rego");
		zsirMain(game);
	}*/
	{
		Player *players[6];
		players[0]=new Player("Beni");
		players[1]=new Player("Rego");
		players[2]=new Player("Zille");
		PokerAsztal<6> asztal(players, 3);
		pokerMain(asztal);
	}
	#endif
	return 0;
}