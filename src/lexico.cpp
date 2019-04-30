#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::to_string;

#include <string>
using std::string;
using std::getline;
#include <stdlib.h>
#include<stdio.h>
#include <ctype.h>
#include "hash.h"




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
HashMap<string, string> *h = new HashMap<string, string>; 
string palavraReservada[47] = {"and","array","begin","case","const","constructor","destructor","div","do","downto","else","end","file","for","function","goto","if","inherited","implementation","in","inline","interface","label","mod","nil","not","object","of","or","packed","procedure","program","record","repeat","set","shl","shr","string","then","to","type","unit","until","uses","var","while","with"};
int finais[9] = {2,3,4,5,6,7,8,9,10}; //TODOS ESTADOS SERÃO FINAIS. TMJ CIENCIAS
int lines;
int nfinais = 9;
string saidas[9] = {"SIMBOLO ESPECIAL","ID","SIMBOLO ESPECIAL","SIMBOLO ESPECIAL","SIMBOLO ESPECIAL","SIMBOLO ESPECIAL COMPOSTO","NUMERO","NUMERO","SIMBOLO ESPECIAL"};

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
    else cout<<saidas[k]<<"--> ";



}
int getFinal(int inicio, int fim, string palavra,int estado)
{   string printar;
    int i;
    int k=-1;
    for(i=0;i<nfinais;i++)
    {
        if(estado ==finais[i]) k = i;
    }
    
    return k;



}


int verificaPalavraReservada(string palavra){
	int i;
	for(i=0;i<palavra.size();i++){
		palavra[i] = tolower(palavra[i]);
	}
	//cout <<"verifica " <<palavra<<endl;
	for(i=0;i<47;i++){
		if(palavra == palavraReservada[i]){
			return 1;
		}
	}
	return 0;
	
 
}

int printLastPalavra(int inicio, int fim ,string palavra,bool op,int id){
	//Salva palavra para verificação de palavra reservada
	string novaPalavra = "";
	string palavraLower= "";


	
	for(int i = inicio; i<fim ; i++){ 
		novaPalavra = novaPalavra + palavra[i];
        palavra[i] = tolower(palavra[i]);
        palavraLower = palavraLower + palavra[i];
	}
	if(	verificaPalavraReservada(novaPalavra)==1){
		if(op){
			h->insertNode(novaPalavra,palavraLower); 

			cout << "Palavra Reservada --> " << novaPalavra << " Posicao hash --> " << h->getPos(novaPalavra); 
 
		}
		return 1;
	}else{
		if(op){
            if(id != -1){
                h->insertNode(novaPalavra,to_string(id));
                cout <<novaPalavra << " Posicao hash --> " << h->getPos(novaPalavra);
            }
		}
		return 0;
	}
}
int main()
{
    lines =0;
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
    string auxPalavra;
    while(!feof(stdin))
    {
        lines++;
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
			            //printLastPalavra(k,i,palavra,true);

					 	cout<<"ERRO na linha "<< lines<< ". Token: "<<palavra[i];
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
                      if(printLastPalavra(k,i,palavra,false,-1)==1){
                    	printLastPalavra(k,i,palavra,true,-1);

                    }else{
	                    printPalavra(k,posLastFinal,palavra,lastFinal);

	                    printLastPalavra(k,i,palavra,true,getFinal(k,posLastFinal,palavra,lastFinal));
	                }
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
                    //printLastPalavra(k,i,palavra,true);

                    cout << "ERRO na linha "<< lines<< ". Token: "<<palavra[i];
					k=i+1;
                }
                else
                {
                    if(pulo==1)cout<<endl;
                    else pulo=1;
                    if(printLastPalavra(k,i,palavra,false,1)==1){
                    	printLastPalavra(k,i,palavra,true,-1);

                    }else{
                        //auxPalavra = printPalavra2(k,posLastFinal,palavra,lastFinal);
                        printPalavra(k,posLastFinal,palavra,lastFinal);
                        printLastPalavra(k,i,palavra,true,getFinal(k,posLastFinal,palavra,lastFinal));

	                }
                    stateAtual = 1;
                    i=posLastFinal;
                    k = posLastFinal+1;
                    //i=posLastFinal;
                    lastFinal = 0;
                }
            }
        }while(palavra[i]!='\0');

    }
    cout << endl;
    return 0;
}
