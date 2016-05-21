#ifndef AGENT
#define AGENT
#include "belkan.h"

using namespace std;

class Casilla{
private:
    int X,Y,orientacion;
    Casilla *anterior;
    int coste;

public:
    //Constructores:
    Casilla(int x, int y, int orientacion ){
        this->X = x;
        this->Y = y;
        this->orientacion = orientacion;
        this->anterior = NULL;
        this->coste = 0;
    }

    Casilla(int x, int y, int orientacion , Casilla *anteriori){

        this->X = x;
        this->Y = y;
        this->orientacion = orientacion;
        cout << "¿"<<endl;
        this->anterior = anteriori;
         cout << "?"<<endl;
        this->coste = this->anterior->getCoste()+1;
        cout << "OKS"<<endl;
    }

    int getX(){
        return X;
    }
    int getY(){
        return Y;
    }
    int getOrientacion(){
        return this->orientacion;
    }
    int getCoste(){
        int coste0;
        if(this->anterior == NULL){
            coste0 =0;
        }
        else{
            Casilla * ultima = this->anterior->anterior;
            coste0 = 1;
            while(ultima != NULL){
                ultima = ultima->anterior;
                coste0++;
            }
        }

        return coste0;
    }
    Casilla * getAnterior(){
        return this->anterior;
    }
};
#endif