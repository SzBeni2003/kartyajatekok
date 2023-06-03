#include "../headers/poker.hpp"


int Player::holdnbet(size_t b){
    #ifndef JPORTA
    char s[100];
    std::cout<<"Press Enter to continue..."<<std::endl;
    std::cin.getline(s, 100);
    #endif
    std::cout<<"A kartyaid:"<<std::endl;
    peek();
    std::cout<<"A jelenlegi tet: "<<b<<std::endl
             <<"Ennyi penzed van: "<<money<<std::endl;
    int choice;
    std::cout<<"0: nem adom meg a tétet\n1:megadom a tétet\n2:megadom a tétet és emelek rajta\n";
    #ifndef JPORTA
    (std::cin>>choice).ignore(1);
    #else
    choice=1;
    #endif
    //if(choice<0||choice>2)throw "Invalid input";
    if(choice<=0){
        if(b>=0) return -1;
        else return 0;
    }
    if(money<=b){
        contribution+=money;
        money=0;
        return 0;
    }else{
        contribution+=b;
        money-=b;
    }
    if(choice==1) return 0;

    std::cout<<"Ennyivel emelem a tetet: "<<std::endl;
    (std::cin>>choice).ignore(1);
    while(choice<0){ //throw "Negatív tétet nem lehet megadni!";
        std::cout<<"Pozitiv szamot adj meg tetnek:\n";
        std::cout<<"Ennyivel emelem a tetet: "<<std::endl;
        (std::cin>>choice).ignore(1);
    }
    contribution+=choice;
    money-=choice;
    return choice;
}


bool Player::continueGame(){
    if(money<200) return false;
    std::cout<<"Ennyi penzed van: "<<money<<std::endl<<name<<", szeretned folytatni? (I/n)\n";
    //#ifndef JPORTA
    char c;
    (std::cin >> c).ignore(1);
    if(toupper(c)=='N') return false;
    //#endif
    return true;
}


template<size_t playercount>
void PokerAsztal<playercount>::eval(){
    Hand best;
    size_t p1=0,p2=0, p3=0;
    for (size_t i=0;i<playercount;++i){
        if(players[i]->isIG()){
            players[i]->eval(community);
            Hand h=players[i]->getHand();
            if((h.handtype>best.handtype)||
            (h.handtype==best.handtype&&h.highs[0]>best.highs[0])||
            (h.handtype==best.handtype&&h.highs[0]==best.highs[0]&&h.highs[1]>best.highs[1])){
                best=h;
                p1=p2=p3=i;
            } else if((h.handtype==best.handtype)&&(h.highs[0]==best.highs[0])&&(h.highs[1]==best.highs[1])){
                if(p2==p1) p2=i;
                else if(p3==p1)p3=i;
            }
        }
    }
    for (size_t i=0;i<playercount;++i){
        std::cout<<players[i]->getName()<<"\t"<<players[i]->getHand().handtype<<"\t"<<players[i]->getHand().highs[0]<<"\t"<<players[i]->getHand().highs[1]<<std::endl;
    }
    size_t winning=pot/(p2==p1?1:(p3==p1?2:3));
    std::cout<<players[p1]->getName()<<" won "<<winning<<"!\n";
    if(p2!=p1) std::cout<<players[p2]->getName()<<" won "<<winning<<"!\n";
    if(p3!=p1) std::cout<<players[p3]->getName()<<" won "<<winning<<"!\n";
    players[p1]->win(winning);
    if(p2!=p1)players[p2]->win(winning);
    if(p3!=p1)players[p3]->win(winning);
}

template<size_t playercount>
void PokerAsztal<playercount>::sitout(size_t idx){
    if(idx>=playercount)throw std::out_of_range("tulindexeles");
    std::cout<<players[idx]->getName()<<" kilépett a játékból!\n";
    delete players[idx];
    for (size_t j = idx + 1; j < playercount; ++j)
		players[j - 1] = players[j];
	players[--playercount]=nullptr;
    return;
}


template<size_t playercount>
void PokerAsztal<playercount>::deal(){
    Pakli c;
    switch(currentstate){
    case Begin:
        for(size_t i=0;i<playercount;++i){
            Pakli* p=new Pakli(deck.takeTop(2),2);
            players[i]->getDealtto(*p);
            players[i]->peek();
        }
        break;
    case Flop:
        burnt.newcard(deck.play(deck.size()-1));
        c.newcard(deck.play(deck.size()-1));
        c.newcard(deck.play(deck.size()-1));
        c.newcard(deck.play(deck.size()-1));
        community+=c;
        break;
    case Turn:
        burnt.newcard(deck.play(deck.size()-1));
        c.newcard(deck.play(deck.size()-1));
        community+=c;
        break;
    case River:
        burnt.newcard(deck.play(deck.size()-1));
        c.newcard(deck.play(deck.size()-1));
        community+=c;
        break;
    }
}



template<size_t playercount>
void PokerAsztal<playercount>::bettingRound(size_t starter, bool first){
    for(size_t i=starter;i<(first?starter+playercount:starter+playercount-1);++i){
        Player* p=players[i%playercount];
        if(p->isIG()){
            system("clear");
            std::cout<<"\tKozos lapok: \n";
            community.peek();std::cout<<std::endl;

            std::cout<<"Legmagasabb hozzájárulás: "<<highestBet<<std::endl;
            std::cout<<p->getName()<<"\t"<<p->getCon()<<std::endl;
            int x=highestBet-p->getCon();
            int b=p->holdnbet(x);
            if(b==-1){
                p->setIG(false);
            }else if(b==0){
                pot+=x;
            }else{
                pot+=x+b;
                highestBet+=b;
                bettingRound((i+1)%playercount, false);
                return;
            }
        }
    }
}

/**
 * Póker játékkezelője.
 * Ő hívja meg a különböző tagfüggvényeket, amikor kell
*/
int pokerMain(PokerAsztal<>& asztal){
    while(asztal.playercount>=2){
        std::cout<<"Press enter to start game\n";
        char s[100];
        std::cin.getline(s, 100);
        //start game
        asztal.highestBet=0;
        for(size_t i=0;i<asztal.playercount;++i){
            asztal.players[i]->reset();
        }
        asztal.pot=0;
        asztal.deck.clean();
        asztal.deck.franciapakli();
        asztal.burnt.clean();
        asztal.community.clean();
        asztal.deck.shuffle();
        asztal.currentstate=(PokerAsztal<>::state)0;
        asztal.deal();
        //blinds
        asztal.players[asztal.currentDealer]->blind(200);
        asztal.pot+=200;
        asztal.players[(asztal.currentDealer+1)%asztal.playercount]->blind(100);
        asztal.pot+=100;
        asztal.highestBet=200;
        //first betting
        asztal.bettingRound((asztal.currentDealer+1)%asztal.playercount, true);
        asztal.currentstate=(PokerAsztal<>::state)1;
        asztal.deal(); //flop

        asztal.bettingRound(asztal.currentDealer, true);
        asztal.currentstate=(PokerAsztal<>::state)2;
        asztal.deal(); //turn

        asztal.bettingRound(asztal.currentDealer, true);
        asztal.currentstate=(PokerAsztal<>::state)3;
        asztal.deal(); //river

        asztal.bettingRound(asztal.currentDealer, true);
        asztal.eval();

        for (size_t i=0;i<asztal.playercount;++i){
            while(i<asztal.playercount&&!asztal.players[i]->continueGame())
                asztal.sitout(i);
        }
    }
    std::cout<<"Too few players, ending game\n";
    return 0;
}

/**Színt keres (5 egyforma színt)
 * @return a szín sorszáma, vagy -1, ha nincs 5 azonos színű lap
*/
int flush(Pakli& p){
    size_t c[4]={0, 0, 0, 0};
    for (size_t i=0;i<p.size();++i)
        c[p[i]->getCol()]++;
    if(c[0]>4)return 0;
    if(c[1]>4)return 1;
    if(c[2]>4)return 2;
    if(c[3]>4)return 3;
    return -1;
}

//visszaadja a legmagasabb sor legmagasabb elemét, vagy -1-et, ha nincs 5 hosszú sor
int straight(Pakli& p){
    size_t start=p[p.size()-1]->getNum(), last=p[p.size()-1]->getNum();
    for (int i=p.size()-2;i>=0;--i){
        if(p[i]->getNum()<last-1){
            start=p[i]->getNum();
        }
        last=p[i]->getNum();
        if(last==start-4){
            return start;
        }
    }
    if(p[p.size()-1]->getNum()==14&&start==5)return 5;
    return -1;
}

//Visszaadja a legjobb olyan kéz értékelését, melyben nincs se sor, se szín
Hand nofakinds(Pakli& p){
    size_t occur[13]={0};
    Hand h;
    for (size_t i=0;i<p.size();++i){
        occur[p[i]->getNum()-2]++;
    }
    size_t v=occur[0], n=0;
    for (size_t i=1;i<13;++i){
        if(occur[i]>=v){
            v=occur[i];
            n=i;
        }
    }
    size_t n2=0;
    if(v==4){
        h.handtype=7;
        h.highs[0]=n+2;
    }else if(v==3){
        h.highs[0]=n+2;
        v=occur[0];
        for (size_t i=1;i<13;++i){
            if(occur[i]>=v&&i!=n){
                v=occur[i];
                n2=i;
            }
        }
        if(v>1){
            h.highs[1]=n2+2;
            h.handtype=6;
        }else{
            h.highs[1]=n2+2;
            h.handtype=3;
        }
    }else if(v==2){
        h.highs[0]=n+2;
        if(n!=0){
            v=occur[0];
        }else{
            v=occur[1];
            n2=1;
        }
        for (size_t i=1;i<13;++i){
            if(occur[i]>=v&&i!=n){
                v=occur[i];
                n2=i;
            }
        }
        if(v>1){
            h.highs[1]=n2+2;
            h.handtype=2;
        }else{
            h.highs[1]=n2+2;
            h.handtype=1;
        }
    }else{
        h.handtype=0;
        h.highs[0]=n+2;
    }
    return h;
}


void Player::eval(Pakli& com){
    //sort
    hand+=com;
    for(size_t i=0;i<hand.size();++i){
        size_t min=0;
        for (size_t j=1;j<hand.size()-i;++j)
            if(hand[min]->getNum()>hand[j]->getNum()) min=j;
        hand.newcard(hand.play(min));
    }
    //check for flush
    int f=flush(hand); 
    if(f>=0){
        for(size_t i=0;i<hand.size();++i){
            while(hand[i]->getCol()!=f) hand.play(i);
        }
        if(hand[0]->getNum()+4==hand[4]->getNum()||((hand[3]->getNum()==5)&&(hand[4]->getNum()==14))){
            handeval.handtype=8; //straight flush (/royal flush)
            handeval.highs[0]=(hand[3]->getNum()==5?5:hand[4]->getNum());
            return;
        } else{
            handeval.handtype=5; //flush
            handeval.highs[0]=hand[4]->getNum();
            handeval.highs[1]=hand[3]->getNum();
            return;
        }
    }
    //check for straight
    int s=straight(hand);
    if(s>=5){
        handeval.handtype=4;
        handeval.highs[0]=s;
        return;
    }
    handeval=nofakinds(hand);
    return;
}