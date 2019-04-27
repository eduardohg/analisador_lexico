#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;
using std::getline;
#include <stdlib.h>
#include<stdio.h>



void setColuna(int **mat, int coluna,int valor,int nEstados)
{
    int i;
    for(i=0;i<nEstados+1;i++)
    {
        mat[i][coluna] = valor;
    }
}
void setLinha(int **mat, int linha,int inicio,int fim,int valor,int nEstados)
{
    int i;
    for(i=inicio;i<fim+1;i++)
    {
        mat[linha][i] = valor;
    }
}
int finais[3] = {3,6,7}; //TODOS ESTADOS SERÃO FINAIS. TMJ CIENCIAS 

int nfinais = 3;
string saidas[3] = {"ID","NUMERO","NUMERO"};

int eFinal(int valor)
{
    int i;
    for(i=0;i<nfinais;i++)
    {
        if (valor==finais[i])return 1;
    }
    return 0;
}
void printPalavra(int inicio, int fim, string palavra,int estado)
{	string printar;
	int i;
	int k;
	for(i=0;i<nfinais;i++)
	{
		if(estado ==finais[i]) k = i;
	}
	if(estado == 19 || estado ==22)
	{
		cout<<saidas[k]<<" ";
		for(i=inicio;i<fim+1;i++)cout<<palavra[i];
	}
	else cout<<saidas[k];




}

void printLastPalavra(int inicio, int fim ,string palavra){

	for(int i = inicio; i<fim ; i++){
		cout << palavra[i];
	}
	cout << endl;

}
int main()
{
    int nEstados = 22;
    int **mat;
    int i,j;
    int stateAtual=1;
    int lastFinal = 0;
    int posLastFinal = 0;
    int pulo = 0;
    int k;
    mat = (int**)calloc(sizeof(int*),nEstados+1);
    for(i = 0;i<nEstados+1;i++)
    {
        mat[i] = (int*)calloc(sizeof(int),255+1);
    }

    /*Identificador e Números*/
    setLinha(mat,1,'0','9',8,nEstados);
    setLinha(mat,8,'0','9',8,nEstados);
    setLinha(mat,8,'.','.',9,nEstados);
    setLinha(mat,9,'0','9',9,nEstados);
    setLinha(mat,1,'a','z',3,nEstados);
    setLinha(mat,1,'A','Z',3,nEstados);
    setLinha(mat,3,'a','z',3,nEstados);
    setLinha(mat,3,'A','Z',3,nEstados);
    setLinha(mat,3,'0','9',3,nEstados);
    setLinha(mat,3,'_','_',3,nEstados);
    setLinha(mat,10,'0','9',8,nEstados);

    /*Simbolos Especiais*/
    setLinha(mat,1,'.','.',2,nEstados);
    setLinha(mat,1,')',')',2,nEstados);
    setLinha(mat,1,',',',',2,nEstados);
    setLinha(mat,1,';',';',2,nEstados);
    setLinha(mat,1,'=','=',2,nEstados);
    setLinha(mat,1,'+','+',10,nEstados);
    setLinha(mat,1,'-','-',10,nEstados);
    setLinha(mat,1,'>','>',2,nEstados);
    setLinha(mat,1,'<','<',2,nEstados);
    setLinha(mat,1,'[','[',2,nEstados);
    setLinha(mat,1,']',']',2,nEstados);

    /*Simbolos Especiais Compostos*/
    setLinha(mat,1,':',':',4,nEstados);
    setLinha(mat,1,'(','(',5,nEstados);
    setLinha(mat,1,'*','*',6,nEstados);

    /*Simbolos Especiais Compostos*/
    setLinha(mat,4,'=','=',7,nEstados);
    setLinha(mat,5,'*','*',7,nEstados);
    setLinha(mat,6,')',')',7,nEstados);


    setColuna(mat,' ',-1,nEstados);
    setColuna(mat,0,-1,nEstados);
    string palavra;
    while(!feof(stdin))
    {
        getline(cin,palavra);
        i=-1;
        j=0;
        stateAtual=1;
        lastFinal = 0;
        posLastFinal = 0;
        k=0;
        do
        {
            i++;
            stateAtual = mat[stateAtual][palavra[i]];

            if (eFinal(stateAtual)==1){lastFinal = stateAtual;posLastFinal = i;}
            if(stateAtual ==-1)
            {
                if(lastFinal == 0)
                {
                	if(i-k>=1)
					{
						if(pulo==1){cout<<endl;}
						else
						{
							pulo=1;
						}
			            printLastPalavra(k,i,palavra);

					 	cout<<"ERRO2";
					}
                	while(i-k>0)i--;
                    k=i+1;
                    stateAtual = 1;
                    lastFinal = 0;
                    posLastFinal = i+1;

                }
                else
                {
                    if(pulo==1)cout<<endl;
                    else pulo=1;
                    printPalavra(k,posLastFinal,palavra,lastFinal);
                    printLastPalavra(k,i,palavra);

                    stateAtual = 1;

                    k = posLastFinal+1;
                    i=posLastFinal;
                    //i=posLastFinal;
                    lastFinal = 0;

                }
            }
            if(stateAtual == 0)
            {
                if(lastFinal == 0)
                {
                    if(pulo==1)cout<<endl;
                    else {pulo=1;}
                    while(i-k>=1)i--;
                    stateAtual = 1;
                    lastFinal = 0;
                    posLastFinal = i+1;
                    printLastPalavra(k,i,palavra);

                    cout << "ERRO1";
					k=i+1;
                }
                else
                {
                    if(pulo==1)cout<<endl;
                    else pulo=1;
                    printPalavra(k,posLastFinal,palavra,lastFinal);
                    printLastPalavra(k,i,palavra);
                    stateAtual = 1;
                    i=posLastFinal;
                    k = posLastFinal+1;
                    //i=posLastFinal;
                    lastFinal = 0;
                }
            }
        }while(palavra[i]!='\0');

    }
    return 0;
}
