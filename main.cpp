#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <cstring>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#define culoare_chenar sf::Color(52,64,85)
#define culoare_text sf::Color(251,251,251)
#define culoare_text_selectat sf::Color(255,193,69)
#define culoare_X sf::Color(126,168,190)
#define culoare_O sf::Color(255,193,69)
#define culoare_fundal sf::Color(40,41,39)
#define culoare_bara_win sf::Color(239,121,138)

using namespace std;

struct elementar
{
    int a[3][3];
    int scor_X;
    int scor_O;
} elementare[12000];

struct neelementar
{
    int a[3][3];
    int indice_elementar;
} neelementare[12000];

int numar_total;
int win_state;
float width=500;
float hight=500;
int optiune_curenta=1;
long long mps=1;
int numar_mps=1;
int timp;
int numar_neelementare;
int numar_elementare;
bool game_on=1;
int tabla[3][3];
int scena_curenta=0;
int wins,losts,draws;
int decizii_1[100],decizii_2[100];
int numar_decizii_1,numar_decizii_2;
sf::RectangleShape orizontal_1;
sf::RectangleShape orizontal_2;
sf::RectangleShape vertical_2;
sf::RectangleShape vertical_1;
sf::Text optiuni[10];
int numar_optiuni;

sf::Font DejaVuSans;
sf::RenderWindow window(sf::VideoMode(500,500),"",sf::Style::None);
void inits()
{
    DejaVuSans.loadFromFile("DejaVuSans.ttf");
    vertical_1.setPosition(sf::Vector2f((float)width*(1.f/3),0));
    vertical_1.setSize(sf::Vector2f(10,hight));
    vertical_1.setFillColor(culoare_chenar);

    vertical_2.setPosition(sf::Vector2f((float)width*(2.f/3),0));
    vertical_2.setSize(sf::Vector2f(10,hight));
    vertical_2.setFillColor(culoare_chenar);

    orizontal_1.setPosition(sf::Vector2f(0,(float)hight*(1.f/3)));
    orizontal_1.setSize(sf::Vector2f(width,10));
    orizontal_1.setFillColor(culoare_chenar);

    orizontal_2.setPosition(sf::Vector2f(0,(float)hight*(2.f/3)));
    orizontal_2.setSize(sf::Vector2f(width,10));
    orizontal_2.setFillColor(culoare_chenar);

    optiuni[1].setString("Learn");
    optiuni[1].setPosition(sf::Vector2f(0+(float)width/3.f/2.f-50,(float)hight/3.f/2.f-20));
    optiuni[1].setCharacterSize(40);
    optiuni[1].setFillColor(culoare_text);
    optiuni[1].setFont(DejaVuSans);

    optiuni[2].setString("Play");
    optiuni[2].setPosition(sf::Vector2f((float)width*(1.f/3)+(float)width/3.f/2.f-50,(float)hight/3.f/2.f-20));
    optiuni[2].setCharacterSize(40);
    optiuni[2].setFillColor(culoare_text);
    optiuni[2].setFont(DejaVuSans);

    optiuni[3].setString("Exit");
    optiuni[3].setPosition(sf::Vector2f((float)width*(2.f/3)+(float)width/3.f/2.f-50,(float)hight/3.f/2.f-20));
    optiuni[3].setCharacterSize(40);
    optiuni[3].setFillColor(culoare_text);
    optiuni[3].setFont(DejaVuSans);
    numar_optiuni=3;

}

void citire()
{
    ifstream fin_elementare("elementare.txt");

    numar_elementare=1;
    while (fin_elementare >>
            elementare[numar_elementare].a[0][0] >>
            elementare[numar_elementare].a[0][1] >>
            elementare[numar_elementare].a[0][2] >>
            elementare[numar_elementare].a[1][0] >>
            elementare[numar_elementare].a[1][1] >>
            elementare[numar_elementare].a[1][2] >>
            elementare[numar_elementare].a[2][0] >>
            elementare[numar_elementare].a[2][1] >>
            elementare[numar_elementare].a[2][2] >>
            elementare[numar_elementare].scor_X >>
            elementare[numar_elementare].scor_O)
    {
        numar_elementare++;
    }
    ifstream fin_neelementare("neelementare.txt");
    numar_neelementare=1;
    while (fin_neelementare >>
            neelementare[numar_neelementare].a[0][0] >>
            neelementare[numar_neelementare].a[0][1] >>
            neelementare[numar_neelementare].a[0][2] >>
            neelementare[numar_neelementare].a[1][0] >>
            neelementare[numar_neelementare].a[1][1] >>
            neelementare[numar_neelementare].a[1][2] >>
            neelementare[numar_neelementare].a[2][0] >>
            neelementare[numar_neelementare].a[2][1] >>
            neelementare[numar_neelementare].a[2][2] >>
            neelementare[numar_neelementare].indice_elementar)
    {
        numar_neelementare++;
    }
    ifstream fin_info("info.txt");
    fin_info >>mps;
    fin_info >>numar_mps;
    fin_info >>numar_total;
}

void afisare_optiuni()
{
    for (int i=1; i<=numar_optiuni; i++)
    {
        window.draw(optiuni[i]);
    }
}
void afisare_background()
{
    sf::RectangleShape fundal;
    fundal.setSize(sf::Vector2f(width,hight));
    fundal.setFillColor(culoare_fundal);
    window.draw(fundal);
}
void scriere()
{
    ofstream fout_elementare("elementare.txt");
    for (int q=1; q<=numar_elementare; q++)
    {
        for (int i=0; i<=2; i++)
        {
            for (int j=0; j<=2; j++)
            {
                fout_elementare << elementare[q].a[i][j] << " ";
            }
            fout_elementare <<endl;
        }
        fout_elementare <<
        //1
        elementare[q].scor_X
        << " " <<
        //1
        elementare[q].scor_O
        <<"\n\n";
    }
    ofstream fout_neelementare("neelementare.txt");
    for (int q=1; q<=numar_neelementare; q++)
    {
        for (int i=0; i<=2; i++)
        {
            for (int j=0; j<=2; j++)
            {
                fout_neelementare << neelementare[q].a[i][j] << " ";
            }
            fout_neelementare <<endl;
        }
        fout_neelementare <<neelementare[q].indice_elementar<<endl <<endl;
    }
    ofstream fout_info("info.txt");
    fout_info <<mps << " " << numar_mps<<" ";
    fout_info <<numar_total;
}
int win()
{
    for (int i=0; i<=2; i++)
    {
        if (tabla[i][0]==tabla[i][1]&&tabla[i][1]==tabla[i][2]&&tabla[i][0]!=0)
        {
            win_state=i;
            return tabla[i][0];
        }
    }
    for (int i=0; i<=2; i++)
    {
        if (tabla[0][i]==tabla[1][i]&&tabla[1][i]==tabla[2][i]&&tabla[0][i]!=0)
        {
            win_state=3+i;
            return tabla[0][i];
        }
    }
    if (tabla[0][0]==tabla[1][1]&&tabla[1][1]==tabla[2][2]&&tabla[0][0]!=0)
    {
        win_state=6;
        return tabla[0][0];
    }
    if (tabla[0][2]==tabla[1][1]&&tabla[1][1]==tabla[2][0]&&tabla[0][2]!=0)
    {
        win_state=7;
        return tabla[1][1];
    }
    int nr0=0;
    for (int i=0; i<=2; i++)
        for (int j=0; j<=2; j++)
            if (tabla[i][j]==0)
                nr0++;
    win_state=-1;
    if (nr0==0)
        return -1;
    return 0;

}

bool comp(int a[3][3],int b[3][3])
{
    for (int i=0; i<=2; i++)
        for (int j=0; j<=2; j++)
            if (a[i][j]!=b[i][j])
                return 0;
    return 1;
}

void reset_tabla()
{
    for (int i=0; i<=2; i++)
        for (int j=0; j<=2; j++)
            tabla[i][j]=0;
}

int cautare_neelementare(int a[3][3])
{
    for (int i=1; i<=numar_neelementare; i++)
    {
        if (comp(a,neelementare[i].a)==1)
            return i;
    }
    cout << "\nnu s-a gasit in neelementare\n";
    for (int i=0; i<=2; i++)
    {
        for (int j=0; j<=2; j++)
        {
            cout << a[i][j] << " ";

        }
        cout <<endl;
    }
    while (true);
    return 0;
}
void afisare_chenar()
{
    window.draw(vertical_1);
    window.draw(vertical_2);
    window.draw(orizontal_1);
    window.draw(orizontal_2);
}
void update_culori_text()
{
    for (int i=1; i<=numar_optiuni; i++)
    {
        if (i==optiune_curenta)
            optiuni[i].setFillColor(culoare_text_selectat);
        else
            optiuni[i].setFillColor(culoare_text);
    }
}
void update_input()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type==sf::Event::Closed)
            game_on=0;
        if (event.type==sf::Event::KeyPressed)
        {
            if (event.key.code==sf::Keyboard::Right)
            {
                optiune_curenta++;
                if (optiune_curenta>numar_optiuni)
                    optiune_curenta=numar_optiuni;
            }
            if (event.key.code==sf::Keyboard::Left)
            {
                optiune_curenta--;
                if (optiune_curenta<1)
                    optiune_curenta=1;
            }
            if (event.key.code==sf::Keyboard::Enter)
            {
                scena_curenta=optiune_curenta;
            }
        }
        if (event.type==sf::Event::MouseMoved)
        {
            sf::Mouse mouse;
            sf::Vector2i pozitie=mouse.getPosition(window);
            if (pozitie.x>=0&&pozitie.x<=width&&pozitie.y>=0&&pozitie.y<=hight)
            {
                int x=pozitie.x/(width/3);
                int y=pozitie.y/(hight/3);
                int optiune=y*3+x+1;
                if (optiune<=numar_optiuni)
                    optiune_curenta=optiune;
            }
        }
        if (event.type==sf::Event::MouseButtonReleased)
        {
            sf::Mouse mouse;
            sf::Vector2i pozitie=mouse.getPosition(window);
            if (pozitie.x>=0&&pozitie.x<=width&&pozitie.y>=0&&pozitie.y<=hight)
            {
                int x=pozitie.x/(width/3);
                int y=pozitie.y/(hight/3);
                int optiune=y*3+x+1;
                if (optiune<=numar_optiuni)
                {
                    optiune_curenta=optiune;
                    scena_curenta=optiune_curenta;
                }
            }
        }

    }
}
void scena_0()
{
    window.clear();
    afisare_background();
    afisare_chenar();
    update_input();
    update_culori_text();
    afisare_optiuni();

    window.display();
}
void actiune (int &turn)
{
    int indice_neelementar_ales=0;
    int a[3][3];

    for (int i=0; i<=2; i++)
        for (int j=0; j<=2; j++)
            a[i][j]=tabla[i][j];

    int suma=0;
    for (int i=0; i<=2; i++)
    {
        for (int j=0; j<=2; j++)
        {
            if (a[i][j]==0)
            {

                a[i][j]=turn;
                int q=cautare_neelementare(a);
                if (turn==1)
                    suma+=elementare[neelementare[q].indice_elementar].scor_O;
                if (turn==2)
                    suma+=elementare[neelementare[q].indice_elementar].scor_X;
                a[i][j]=0;
            }
        }
    }
    //cout <<endl <<endl;
    for (int i=0; i<=2; i++)
        for (int j=0; j<=2; j++)
            a[i][j]=tabla[i][j];

    if (suma<=0)
    {
        while (indice_neelementar_ales==0)
        {
            int x=rand()%3;
            int y=rand()%3;
            if (tabla[x][y]==0)
            {
                tabla[x][y]=turn;
                indice_neelementar_ales=cautare_neelementare(tabla);
            }
        }
    }
    else
    {
        //cout <<"suma!=0\n";
        int probabilitate=rand()%suma+1;
        //cout << probabilitate << " " << suma<<endl;
        suma=0;
        for (int i=0; i<=2; i++)
        {
            for (int j=0; j<=2; j++)
            {
                if (a[i][j]==0)
                {
                    a[i][j]=turn;
                    int q=cautare_neelementare(a);
                    if (turn==1)
                        suma+=elementare[neelementare[q].indice_elementar].scor_O;
                    if (turn==2)
                        suma+=elementare[neelementare[q].indice_elementar].scor_X;
                    a[i][j]=0;
                    if (probabilitate<=suma)
                    {
                        indice_neelementar_ales=q;
                        tabla[i][j]=turn;
                        i=j=3;
                    }
                }
            }
        }
    }
    if (indice_neelementar_ales==0)
    {
        //cout << "indice neelementar neales!!! nu s-a schimbat nimic pe harta!!!\n";
    }
    if (turn==1)
        decizii_1[++numar_decizii_1]=indice_neelementar_ales;
    else
        decizii_2[++numar_decizii_2]=indice_neelementar_ales;
    turn=3-turn;
}

void invatare(int tura_curenta,int numar_ture)
{
    int turn=rand()%2+1;
    numar_decizii_1=0;
    numar_decizii_2=0;

    reset_tabla();
    while (win()==0)
    {
        if (clock()-timp>CLOCKS_PER_SEC)
        {
            sf::Text text;
            int x=20,y=20;
            text.setCharacterSize(40);
            text.setPosition(sf::Vector2f(x,y));
            text.setFont(DejaVuSans);
            text.setFillColor(culoare_text);
            text.setString("How many matches?");

            y+=40;
            sf::Text text2;
            text2.setCharacterSize(40);
            text2.setPosition(sf::Vector2f(x,y));
            text2.setFont(DejaVuSans);
            text2.setFillColor(culoare_text);

            y+=40;
            sf::Text W;
            sf::Text D;
            sf::Text L;
            W.setCharacterSize(40);
            W.setPosition(sf::Vector2f(x,y));
            W.setFont(DejaVuSans);
            W.setFillColor(culoare_text);
            y+=40;
            D.setCharacterSize(40);
            D.setPosition(sf::Vector2f(x,y));
            D.setFont(DejaVuSans);
            D.setFillColor(culoare_text);
            y+=40;
            L.setCharacterSize(40);
            L.setPosition(sf::Vector2f(x,y));
            L.setFont(DejaVuSans);
            L.setFillColor(culoare_text);

            window.clear();


            afisare_background();
            char s[15]= {0};

            int aux=wins;
            int i=13;
            while (aux!=0)
            {
                s[i]=aux%10+'0';
                aux/=10;
                i--;
            }
            s[14]=(char)NULL;
            s[i]=' ';
            i--;
            s[i]=':';
            i--;
            s[i]='W';
            i--;
            strcpy(s,s+i+1);
            W.setString(s);

            aux=draws;
            i=13;
            while (aux!=0)
            {
                s[i]=aux%10+'0';
                aux/=10;
                i--;
            }
            s[14]=(char)NULL;
            s[i]=' ';
            i--;
            s[i]=':';
            i--;
            s[i]='D';
            i--;
            strcpy(s,s+i+1);
            D.setString(s);

            aux=losts;
            i=13;
            while (aux!=0)
            {
                s[i]=aux%10+'0';
                aux/=10;
                i--;
            }
            s[14]=(char)NULL;
            s[i]=' ';
            i--;
            s[i]=':';
            i--;
            s[i]='L';
            i--;
            strcpy(s,s+i+1);
            L.setString(s);

            aux=numar_ture;
            i=13;
            while (aux!=0)
            {
                s[i]=aux%10+'0';
                aux/=10;
                i--;
            }
            s[14]=(char)NULL;

            strcpy(s,s+i+1);
            text2.setString(s);

            y+=80;
            sf::Text total;
            total.setPosition(sf::Vector2f(x,y));
            total.setFillColor(culoare_text);
            total.setFont(DejaVuSans);
            total.setCharacterSize(40);

            aux=mps;
            i=13;
            while (aux!=0)
            {
                s[i]=aux%10+'0';
                aux/=10;
                i--;
            }
            s[14]=(char)NULL;
            s[i]=' ';
            i--;
            s[i]=':';
            i--;
            s[i]='T';
            i--;
            strcpy(s,s+i+1);
            total.setString(s);

            window.draw(W);
            window.draw(D);
            window.draw(L);

            window.draw(total);
            window.draw(text);
            window.draw(text2);

            window.display();

            timp=clock();
        }
        actiune(turn);
    }
    int castigator=win();
    if (castigator==1)
    {
        losts++;
        for (int i=1; i<=numar_decizii_1; i++)
        {
            elementare[neelementare[decizii_1[i]].indice_elementar].scor_O+=3;
        }
        for (int i=1; i<=numar_decizii_2; i++)
        {
            elementare[neelementare[decizii_2[i]].indice_elementar].scor_X-=1;
            if (elementare[neelementare[decizii_2[i]].indice_elementar].scor_X<0)
                elementare[neelementare[decizii_2[i]].indice_elementar].scor_X=0;
        }
    }
    if (castigator==2)
    {
        wins++;
        for (int i=1; i<=numar_decizii_1; i++)
        {
            elementare[neelementare[decizii_1[i]].indice_elementar].scor_O-=1;
            if (elementare[neelementare[decizii_1[i]].indice_elementar].scor_O<0)
                elementare[neelementare[decizii_1[i]].indice_elementar].scor_O=0;
        }
        for (int i=1; i<=numar_decizii_2; i++)
        {
            elementare[neelementare[decizii_2[i]].indice_elementar].scor_X+=3;
        }
    }
    if (castigator==-1)
    {
        draws++;
    }
}


void scena_1()
{
    bool enter=0;
    sf::Text text;
    int x=20,y=20;
    text.setCharacterSize(40);
    text.setPosition(sf::Vector2f(x,y));
    text.setFont(DejaVuSans);
    text.setFillColor(culoare_text);
    text.setString("How many matches?");

    y+=40;
    sf::Text text2;
    text2.setCharacterSize(40);
    text2.setPosition(sf::Vector2f(x,y));
    text2.setFont(DejaVuSans);
    text2.setFillColor(culoare_text);

    y+=40;
    sf::Text W;
    sf::Text D;
    sf::Text L;
    W.setCharacterSize(40);
    W.setPosition(sf::Vector2f(x,y));
    W.setFont(DejaVuSans);
    W.setFillColor(culoare_text);
    y+=40;
    D.setCharacterSize(40);
    D.setPosition(sf::Vector2f(x,y));
    D.setFont(DejaVuSans);
    D.setFillColor(culoare_text);
    y+=40;
    L.setCharacterSize(40);
    L.setPosition(sf::Vector2f(x,y));
    L.setFont(DejaVuSans);
    L.setFillColor(culoare_text);

    y+=80;
    sf::Text total;
    total.setPosition(sf::Vector2f(x,y));
    total.setFillColor(culoare_text);
    total.setFont(DejaVuSans);
    total.setCharacterSize(40);

    char s[15]= {0};
    int aux=mps;
    int i=13;
    while (aux!=0)
    {
        s[i]=aux%10+'0';
        aux/=10;
        i--;
    }
    s[14]=(char)NULL;
    s[i]=' ';
    i--;
    s[i]=':';
    i--;
    s[i]='T';
    i--;
    strcpy(s,s+i+1);
    total.setString(s);

    char numarul[9]= {0};
    int numar_caractere=0;
    int numar=0;
    while (enter==0)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type==sf::Event::KeyPressed)
            {
                if (event.key.code>=sf::Keyboard::Num0&&event.key.code<=sf::Keyboard::Num9&&numar_caractere<7)
                {
                    int n=event.key.code-sf::Keyboard::Num0;
                    numar=numar*10+n;
                    numar_caractere++;
                    numarul[numar_caractere-1]=(char)(n+'0');
                }
                switch (event.key.code)
                {
                case sf::Keyboard::Backspace:
                {
                    if (numar!=0)
                    {
                        numar/=10;
                        numar_caractere--;
                        numarul[numar_caractere]=(char)NULL;
                    }
                    break;
                }
                case sf::Keyboard::Enter:
                {
                    if (numar!=0)
                    {
                        enter=1;
                    }
                    break;
                }
                case sf::Keyboard::Escape:
                {
                    scena_curenta=0;
                    return;
                    break;
                }
                default :
                {
                    break;
                }
                }
            }

            if (event.type==sf::Event::MouseButtonReleased)
            {

                scena_curenta=0;
                return;
            }
        }


        window.clear();

        afisare_background();

        if (wins!=0||draws!=0||losts!=0)
        {
            char s[15]= {0};

            int aux=wins;
            int i=13;
            while (aux!=0)
            {
                s[i]=aux%10+'0';
                aux/=10;
                i--;
            }
            s[14]=(char)NULL;
            s[i]=' ';
            i--;
            s[i]=':';
            i--;
            s[i]='W';
            i--;
            strcpy(s,s+i+1);
            W.setString(s);

            aux=draws;
            i=13;
            while (aux!=0)
            {
                s[i]=aux%10+'0';
                aux/=10;
                i--;
            }
            s[14]=(char)NULL;
            s[i]=' ';
            i--;
            s[i]=':';
            i--;
            s[i]='D';
            i--;
            strcpy(s,s+i+1);
            D.setString(s);

            aux=losts;
            i=13;
            while (aux!=0)
            {
                s[i]=aux%10+'0';
                aux/=10;
                i--;
            }
            s[14]=(char)NULL;
            s[i]=' ';
            i--;
            s[i]=':';
            i--;
            s[i]='L';
            i--;
            strcpy(s,s+i+1);
            L.setString(s);

            window.draw(W);
            window.draw(D);
            window.draw(L);
        }

        text2.setString(numarul);
        window.draw(total);
        window.draw(text);
        window.draw(text2);

        window.display();

    }
    timp=clock();
    int timp_inceput=clock();
    wins=losts=draws=0;
    for (int i=1; i<=numar; i++)
    {
        invatare(i,numar);
        numar_total++;
    }
    mps+=numar;
    numar_mps+=(clock()-timp_inceput)/CLOCKS_PER_SEC;
}



void afisare_elemente_tabla()
{
    int offset_x=0,offset_y=0;
    sf::Text litera;
    litera.setCharacterSize(80);
    litera.setFillColor(culoare_text);
    litera.setFont(DejaVuSans);
    litera.setOrigin(sf::Vector2f(litera.getCharacterSize()/2,litera.getCharacterSize()/2));
    for (int i=0; i<=2; i++)
    {
        for (int j=0; j<=2; j++)
        {
            if (tabla[i][j]==1)
            {
                litera.setString("O");
                litera.setFillColor(culoare_O);
            }
            if (tabla[i][j]==2)
            {
                litera.setString("X");
                litera.setFillColor(culoare_X);
            }
            if (tabla[i][j]==0)
                litera.setString(" ");
            litera.setPosition(sf::Vector2f(1.f*width*((float)j/3.f)+1.f*width/6,1.f*hight*((float)i/3.f)+1.f*hight/6));
            window.draw(litera);
        }
    }
}
void scena_2()
{
    int turn=rand()%2+1;
    reset_tabla();
    while (win()==0)
    {
        if (turn==2)
        {
            actiune(turn);
        }
        else
        {
            while (turn == 1)
            {
                window.clear();

                afisare_background();

                afisare_chenar();

                sf::Text litera;
                litera.setCharacterSize(80);
                litera.setColor(culoare_text);
                litera.setFont(DejaVuSans);
                litera.setString("O");
                sf::Mouse mouse;
                litera.setOrigin(sf::Vector2f(litera.getCharacterSize()/2,litera.getCharacterSize()/2));
                litera.setPosition(sf::Vector2f(mouse.getPosition(window).x,mouse.getPosition(window).y));
                litera.setFillColor(culoare_O);
                int x,y;
                x=mouse.getPosition(window).y;
                x=x/((int)width/3);
                y=mouse.getPosition(window).x;
                y=y/((int)hight/3);
                bool ok=0;
                if (tabla[x][y]==0)
                {
                    tabla[x][y]=1;
                    ok=1;
                }
                afisare_elemente_tabla();
                if (ok==1)
                    tabla[x][y]=0;
                window.draw(litera);
                window.display();

                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type==sf::Event::MouseButtonReleased)
                    {
                        int x,y;
                        x=mouse.getPosition(window).y;
                        x=x/((int)width/3);
                        y=mouse.getPosition(window).x;
                        y=y/((int)hight/3);
                        if (tabla[x][y]==0)
                        {
                            tabla[x][y]=1;
                            turn=2;
                        }
                    }
                }
            }
        }
    }
    window.clear();
    afisare_background();

    afisare_chenar();
    afisare_elemente_tabla();
    int castigator=win();
    if (castigator==2)
    {

        for (int i=1; i<=numar_decizii_1; i++)
        {
            elementare[neelementare[decizii_1[i]].indice_elementar].scor_X+=3;
        }
    }
    if (castigator==1)
    {
        for (int i=1; i<=numar_decizii_1; i++)
        {
            elementare[neelementare[decizii_1[i]].indice_elementar].scor_X-=1;
            if (elementare[neelementare[decizii_1[i]].indice_elementar].scor_X<0)
                elementare[neelementare[decizii_1[i]].indice_elementar].scor_X=0;
        }
    }
    if (castigator==-1)
    {

    }
    sf::RectangleShape bara;
    bara.setFillColor(culoare_bara_win);
    bara.setSize(sf::Vector2f(width,10));

    switch (win_state)
    {
    case 0:
    {
        bara.setPosition(sf::Vector2f(0,hight/6));
        break;
    }
    case 1:
    {
        bara.setPosition(sf::Vector2f(0,hight/2));
        break;
    }
    case 2:
    {
        bara.setPosition(sf::Vector2f(0,hight-hight/6));
        break;
    }
    case 3:
    {
        bara.setPosition(sf::Vector2f(width/6,0));
        bara.setRotation(90);
        break;
    }
    case 4:
    {
        bara.setPosition(sf::Vector2f(width/2,0));
        bara.setRotation(90);
        break;
    }
    case 5:
    {
        bara.setPosition(sf::Vector2f(width-width/6,0));
        bara.setRotation(90);
        break;
    }
    case 6:
    {
        bara.setPosition(sf::Vector2f(width/6,hight/6));
        bara.setRotation(45);
        break;
    }
    case 7:
    {
        bara.setPosition(sf::Vector2f(width/6,hight-hight/6));
        bara.setRotation(-45);
        break;
    }
    case -1:
    {
        bara.setSize(sf::Vector2f(0,0));
    }
    }
    window.draw(bara);

    sf::Text text;
    text.setCharacterSize(80);
    text.setFillColor(culoare_text_selectat);
    text.setOutlineColor(sf::Color::White);
    text.setOutlineThickness(1);
    text.setFont(DejaVuSans);
    text.setPosition(sf::Vector2f(30,hight/2));
    text.setOrigin(sf::Vector2f(0,text.getCharacterSize()/2));
    if (castigator==1)
        text.setString("WINNER");
    if (castigator==2)
        text.setString("DEFEATED");
    if (castigator==-1)
        text.setString("DRAW");

    while (abs(text.getGlobalBounds().left-(width-text.getGlobalBounds().left-text.getGlobalBounds().width))>10)
        text.move(sf::Vector2f(5,0));
    while (abs(text.getGlobalBounds().top-(width-text.getGlobalBounds().top-text.getGlobalBounds().height))>10)
        text.move(sf::Vector2f(0,-5*(int)(text.getGlobalBounds().top-(width-text.getGlobalBounds().top-text.getGlobalBounds().height))/abs(text.getGlobalBounds().top-(width-text.getGlobalBounds().top-text.getGlobalBounds().height))));
    window.draw(text);
    window.display();
    sf::Event event;
    bool stay=1;
    while (stay==1)
        while (window.pollEvent(event))
        {
            if (event.type==sf::Event::KeyReleased||event.type==sf::Event::MouseButtonReleased)
                stay=0;
        }
    scena_curenta=0;

}

void update()
{
    if (scena_curenta==0)
    {
        scena_0();
    }
    if (scena_curenta==1)
    {
        scena_1();
    }
    if (scena_curenta==2)
    {
        scena_2();
    }
    if (scena_curenta==3)
    {
        game_on=0;
    }
}

int main()
{
    inits();
    srand(time(0));
    citire();
    while (game_on)
    {
        update();
    }



    scriere();
    return 0;
}

