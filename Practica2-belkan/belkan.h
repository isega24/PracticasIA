
#ifndef AGENT__
#define AGENT__

#define agua 'A'
#define arbol 'B'
#define PK 'K'
#define muro 'M'
#define puerta 'D'
#define desconocido '?'

#define BIKINI '0'
#define PIEDRA '1'
#define LLAVE '2'
#define ROSA '3'
#define ORO '4'
#define OSCAR '5'
#define ZAPATILLAS '6'
#define PALA '7'
#define MANZANA '8'
#define ALGORITMO '9'
#define PRINCESA1 'g'
#define PRINCESA2 'h'
#define LEONARDO1 'i'
#define LEONARDO2 'j'
#define PRINCIPE1 'k'
#define PRINCIPE2 'l'
#define BRUJA1 'm'
#define BRUJA2 'n'
#define PROFE1 'o'
#define PROFE2 'p'
#define OSO 'q'

#define NORTE 0
#define ESTE 1
#define SUR 2
#define OESTE 3


#include <string>
#include <iostream>
#include <cstdlib>
#include <list>
#include "conexion.h"



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
// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent(){
		x_= 99;
		y_= 99;
		orientacion_=3;
		role_="PlYR";
		last_accion_=3;
		REINICIADO_=false;
		size_=200;
		primera_amarilla=false;
		orientado = false;
		N=S=E=W=0;
		paso_puerta = 0;
		pasos = 0;
		NObjetos = 0;
		for (int i=0;i<200;i++){
		    for(int j=0;j<200;j++){
		      	mapa_entorno_[i][j]='?';
		      	mapa_objetos_[i][j]='?';
		      	miguitas_[i][j]=0;
		    }
		}

		for (int i=0;i<100;i++){
		    for(int j=0;j<100;j++){
		    	if(i < 3 or j < 3 or i > 96 or j > 96){
                	mapa_solucion_[i][j] = 'P';
            }
		      	else{
		      		mapa_solucion_[i][j]='?';
		      	}
		    }
		}
		mejor = -1;

	}

	enum ActionType
	{
	    actFORWARD, // avanzar
	    actTURN_L,  // Girar Izquierda
	    actTURN_R,  // Girar Derecha
	    actIDLE,    // No hacer nada
	    actPICKUP,  // Recoger un objeto
	    actPUTDOWN, // Soltar un objeto
	    actPUSH,    // Meter en la mochila
	    actPOP,     // Sacar de la mochila
	    actGIVE,	// Dar un objeto a un personaje
	    actTHROW	// Lanzar un objeto

	};

	void Perceive(Environment &env);
	bool Perceive_Remote(conexion_client &Cliente, Environment &env);
	void ActualizarInformacion(Environment *env);
	ActionType Think();
	void FixLastAction(Agent::ActionType x){last_accion_=x;};

	char mapa_entorno_[200][200]; // mapa que muestra el tipo de terreno
	char mapa_objetos_[200][200]; // mapa que muestra los objetos que estan encima del terreno
	char mapa_solucion_[100][100]; // Mapa que almacena la solucion que el alumno propone
	int miguitas_[200][200];
	int mapa_pesos_[200][200];
	// Funciones de acceso a los datos
	void GetCoord(int &fila, int &columna, int &brujula){fila=y_;columna=x_;brujula=orientacion_;};

	int rellena_solucion(int dx, int dy, int dx_,int dy_);
	bool puedo_avanzar(int x, int y);
	int mejor_opcion(bool norte, bool este, bool sur, bool oeste);

	bool mochilaLlena(){return MOCHILLA_[0]!='-' and MOCHILLA_[1]!='-' and MOCHILLA_[2]!='-' and MOCHILLA_[3]!='-' and EN_USO_!= '-' ;}
	const int MAXObjetos = 4;
	int NObjetos;
	void actualizaPesos();
	char correspondencia(char personaje);
	int pasos;



private:
	//Variables de interaccion con el entorno grafico
	int size_;

	//SENSORES
	char VISTA_[10];
	char SURFACE_[10];
	bool REINICIADO_;
	string MENSAJE_;
	char EN_USO_;
	char MOCHILLA_[5];
	char PUNTUACION_[9];
	bool FIN_JUEGO_;
	char SALUD_;
	int paso_puerta;
	//Variables de estado
	int x_,y_, orientacion_;
	int last_accion_;
	string role_;



	// Datos necesarios para la ubicación del agente.

	//Guarda la posición de la primera casilla y la posición relativa
	//de nuestro agente a la misma.


	bool primera_amarilla;
	bool orientado;
	int N,S,E,W;

	//Una vez ya estamos orientados, trabajamos con el mapa bueno.
	int orientacion;
	int x,y;
	int x1real,y1real;
	int x1relativo,y1relativo;

	int mejor;


	Agent::ActionType accion(int i);
	int vacias( Casilla C);


};


string ActionStr(Agent::ActionType);

#endif
