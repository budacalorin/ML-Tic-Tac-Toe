#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
ofstream fout_elementar ("C:/Informatica/PROBLEME/X si O 2.0 AI/elementare.txt");
ofstream fout_neelementar("C:/Informatica/PROBLEME/X si O 2.0 AI/neelementare.txt");
int a[3][3];
struct elementar
{
    int a[3][3];
    int scor_X=5;
    int scor_O=5;
} elementare[10000];
struct neelementar
{
    int a[3][3];
    int indice_elementar;
} neelementare[10000];
int numar_neelementare;
int numar_elementare;
bool finalizare(int l,int c)
{
    if (l>2)
        return 1;
    return 0;
}
void afisare()
{
    numar_neelementare++;
    for (int i=0; i<=2; i++)
        for (int j=0; j<=2; j++)
            neelementare[numar_neelementare].a[i][j]=a[i][j];
}
void  initializare(int l,int c)
{
    a[l][c]=-1;
}
bool succ(int l,int c)
{
    if (a[l][c]==2)
    {
        a[l][c]=0;
        return 0;
    }
    else
        a[l][c]++;
    return 1;
}

int win(int l,int c)
{
    for (int i=0; i<=2; i++)
    {
        if (a[i][0]==a[i][1]&&a[i][1]==a[i][2]&&a[i][0]!=0)
            return a[i][0];
    }
    for (int i=0; i<=2; i++)
    {
        if (a[0][i]==a[1][i]&&a[1][i]==a[2][i]&&a[0][i]!=0)
            return a[0][i];
    }
    if (a[0][0]==a[1][1]&&a[1][1]==a[2][2]&&a[0][0]!=0)
        return a[0][0];
    if (a[0][2]==a[1][1]&&a[1][1]==a[2][0]&&a[2][0]!=0)
        return a[1][1];
    return 0;
}
bool e_ok(int l,int c)
{
    int n1=0,n2=0;
    for (int i=0; i<=2; i++)
    {
        for (int j=0; j<=2; j++)
        {
            if (a[i][j]==1)
                n1++;
            if (a[i][j]==2)
                n2++;
        }
    }
    if (abs(n1-n2)>1)
        return 0;
    return 1;
}

void bkt (int l,int c)
{
    if (finalizare(l,c)==0)
    {
        initializare(l,c);
        while (succ(l,c))
        {
            if ((a[l][c]!=0&&e_ok(l,c))||(win(l,c)==1&&e_ok(l,c)==1))
                afisare();
            if (c+1>2)
                bkt(l+1,0);
            else
                bkt(l,c+1);
        }
    }
}
bool comp (int a[3][3],int b[3][3])
{
    for (int i=0; i<=2; i++)
        for (int j=0; j<=2; j++)
            if (a[i][j]!=b[i][j])
                return 0;
    return 1;
}
void copiere(int a[3][3],int b[3][3])
{
    for (int i=0; i<=2; i++)
        for (int j=0; j<=2; j++)
            a[i][j]=b[i][j];
}

int verificare_elementare(int a[3][3])
{
    for (int i=1; i<=numar_elementare; i++)
    {
        if (comp(a,elementare[i].a)==1)
            return i;
    }
    return 0;
}
void rotire_90(int q[3][3])
{
    int b[3][3];
    for (int i=0; i<=2; i++)
        for (int j=0; j<=2; j++)
            b[i][j]=q[i][j];
    q[0][0]=b[2][0];
    q[0][2]=b[0][0];
    q[2][2]=b[0][2];
    q[2][0]=b[2][2];
    q[0][1]=b[1][0];
    q[1][2]=b[0][1];
    q[2][1]=b[1][2];
    q[1][0]=b[2][1];
}
void rotire_verticala(int q[3][3])
{
    swap (q[0][0],q[0][2]);
    swap (q[1][0],q[1][2]);
    swap (q[2][0],q[2][2]);
}
int main()
{
    numar_neelementare=1;
    neelementare[1].indice_elementar=1;
    numar_elementare=1;
    bkt(0,0);
    for (int i=1; i<=numar_neelementare; i++)
    {
        int q;
        int b[3][3];
        for (int x=0; x<=2; x++)
            for (int y=0; y<=2; y++)
                b[x][y]=neelementare[i].a[x][y];

        q=verificare_elementare(neelementare[i].a);
        if (q!=0)
        {
            neelementare[i].indice_elementar=q;
            continue;
        }

        rotire_90(neelementare[i].a);
        q=verificare_elementare(neelementare[i].a);
        if (q!=0)
        {
            copiere(neelementare[i].a,b);
            neelementare[i].indice_elementar=q;
            continue;
        }

        rotire_90(neelementare[i].a);
        q=verificare_elementare(neelementare[i].a);
        if (q!=0)
        {
            copiere(neelementare[i].a,b);
            neelementare[i].indice_elementar=q;
            continue;
        }

        rotire_90(neelementare[i].a);
        q=verificare_elementare(neelementare[i].a);
        if (q!=0)
        {
            copiere(neelementare[i].a,b);
            neelementare[i].indice_elementar=q;
            continue;
        }

        copiere(neelementare[i].a,b);
        rotire_verticala(neelementare[i].a);
        q=verificare_elementare(neelementare[i].a);
        if (q!=0)
        {
            copiere(neelementare[i].a,b);
            neelementare[i].indice_elementar=q;
            continue;
        }

        rotire_90(neelementare[i].a);
        q=verificare_elementare(neelementare[i].a);
        if (q!=0)
        {
            copiere(neelementare[i].a,b);
            neelementare[i].indice_elementar=q;
            continue;
        }

        rotire_90(neelementare[i].a);
        q=verificare_elementare(neelementare[i].a);
        if (q!=0)
        {
            copiere(neelementare[i].a,b);
            neelementare[i].indice_elementar=q;
            continue;
        }

        rotire_90(neelementare[i].a);
        q=verificare_elementare(neelementare[i].a);
        if (q!=0)
        {
            copiere(neelementare[i].a,b);
            neelementare[i].indice_elementar=q;
            continue;
        }

        copiere(neelementare[i].a,b);
        numar_elementare++;
        copiere(elementare[numar_elementare].a,neelementare[i].a);
        neelementare[i].indice_elementar=numar_elementare;
    }

    cout <<numar_neelementare << " " <<numar_elementare;

    for (int q=1; q<=numar_neelementare; q++)
    {
        for (int i=0; i<=2; i++)
        {
            for (int j=0; j<=2; j++)
            {
                fout_neelementar <<neelementare[q].a[i][j]<< " ";
            }
            fout_neelementar <<endl;
        }
        fout_neelementar <<neelementare[q].indice_elementar <<endl <<endl;
    }
    for (int q=1; q<=numar_elementare; q++)
    {
        for (int i=0; i<=2; i++)
        {
            for (int j=0; j<=2; j++)
            {
                fout_elementar <<elementare[q].a[i][j]<< " ";
            }
            fout_elementar <<endl;
        }
        fout_elementar <<elementare[q].scor_X << " " <<elementare[q].scor_O <<endl <<endl;
    }



    return 0;
}
