#include "../headers/zsir.h"

Kartya* Jatekos::play(size_t which) {
	//if (which >= kezSize())throw "Out of range";
	Kartya* played = kez.play(which);
	return played;
}

void Zsir::draw() {
	while (jatekosok[0]->kezSize() < 4&&huzo.size()>=2) {
		Kartya** ujlapok=huzo.takeTop(2);
		jatekosok[kov]->get(ujlapok[0]);
		jatekosok[(kov + 1) % 2]->get(ujlapok[1]);
		delete[] ujlapok;
	}
}

size_t Jatekos::count(){
	size_t sum=0;
	for(size_t i=0;i<vitt.size();++i){
		//vitt[i]->display();
		if(vitt[i]->getNum()==10||vitt[i]->getNum()==14){
			sum++;
			//std::cout<<" zsir";
		}
		//std::cout<<std::endl;
	}
	return sum;
}

#define p1 game.jatekosok[game.kov]
#define p2 game.jatekosok[(game.kov+1)%2]
#define c2 game.lerakott[game.lerakott.size() - 1]->getNum()
#define c1 game.lerakott[game.lerakott.size() - 2]->getNum()


bool isCardValid(size_t a, size_t x){
	return (x==a)||(x==7);
}

int playing(Jatekos* p, Zsir& game, bool b, size_t cardToPlay) {
	std::cout << "\tEzek vannak epp jatekban:" << std::endl; game.lerakott.peek(); std::cout << std::endl << std::flush;
	size_t x;
	char s[100];
	std::cout << p->getName() << ", te jossz!" << std::endl 
			  << "Press Enter to continue..." << std::flush;
	#ifndef JPORTA
	std::cin.getline(s, 100);
	#endif
	std::cout << "\tA kartyaid:\n";
	p->show();
	std::cout << "Valaszd ki a kartyat, amit kijatszanal: (0-" << p->kezSize() - 1 << ")" << std::endl;
	#ifndef JPORTA
	(std::cin >> x).ignore(1);
	#else
	x=0;
	#endif
	Kartya* c;
	if(b||isCardValid(cardToPlay, p->operator[](x)->getNum())){
		c=p->play(x);
		game.lerakott.newcard(c);
		delete c;
	}else{
		do{
			std::cout << "Nem megfelelo a kartya, valassz megfelelot!"<<std::endl;
			std::cout << "Valaszd ki a kartyat, amit kijatszanal: (0-" << p->kezSize() - 1 << ")" << std::endl;
			(std::cin >> x).ignore(1);
		}while(!isCardValid(cardToPlay, p->operator[](x)->getNum()));
		c=p->play(x);
		game.lerakott.newcard(c);
		delete c;
	}
	system("clear");

	return 0;
}





int zsirMain(Zsir& game) {
	//game.huzo.peek();
	game.draw();


	char c;
	while (game.jatekosok[0]->kezSize() > 0) {
		
		///player1
		playing(p1, game, true, 0);

		///player2
		size_t n = c2;
		playing(p2, game, true, n);

		
		while ((c2==n||c2==7)&&(c1==n||c1==7)&&game.lerakott.size()<8) {
			std::cout << "\tEzek vannak epp jatekban:" << std::endl; game.lerakott.peek(); std::cout << std::endl << std::flush;
			std::cout << p2->getName() << " utott, szeretnel visszautni, " << p1->getName() << "? (y/n)\n";
			#ifdef JPORTA
			c='n';
			#else
			(std::cin >> c).ignore(1);
			#endif
			c = toupper(c);
			system("clear");
			if (c == 'Y'&&(p1->haveNum(n)||p1->haveNum(7))) {
				///player1
				playing(p1, game, false, n);

				///player2
				playing(p2, game, true, n);

			}
			else {
				game.kov = (game.kov + 1) % 2;
				break;
			}
		}
		p1->elvisz(game.lerakott);
		game.lerakott.clean();
		game.draw();
	}

	size_t z1, z2;
	z1=game.jatekosok[0]->count();
	z2=game.jatekosok[1]->count();

	/*game.jatekosok[0]->showVitt();
	std::cout<<std::endl;
	game.jatekosok[1]->showVitt();
	std::cout<<std::endl;*/
	
	std::cout<<game.jatekosok[0]->getName()<<": "<<z1<<" zsir"<<std::endl
			 <<game.jatekosok[1]->getName()<<": "<<z2<<" zsir"<<std::endl
			 <<(z1>z2?game.jatekosok[0]->getName()+" nyert!":(z2>z1?game.jatekosok[1]->getName()+" nyert!":"Dontetlen!"))<<std::endl;


	//game.huzo.resize(32);
	//game.huzo.peek();

	return (z1>z2?0:(z2>z1?1:2));
}