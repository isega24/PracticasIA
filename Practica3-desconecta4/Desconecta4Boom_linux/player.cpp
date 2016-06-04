#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;


// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}

double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return masinf; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return menosinf; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar

/**
* Método que devuelve el número de cuatro en raya que se pueden hacer con una ponderación
* dependiendo del número de fichas que queden para hacer el cuatro en raya. La ponderación
* inversamente proporcional doble(al cuadrado).
*/
double analizaEnRaya(int row,int col,const Environment & estado){
  //cout << "Fallo en analiza0"<<endl;
  int jugador = estado.See_Casilla(row,col);
  //cout << "Fallo en analiza1"<<endl;
  if(jugador > 3){
    jugador = jugador-3;
  }
  //Aquí ya sabemos que ningún posible cuatro en raya está hecho.
  double suma = 0;
  //cout << "Fallo en analiza2"<<endl;
  int casillas_necesarias = 0;
  if(row < 4){
    //cout << "Fallo en norte"<<endl;
    //Norte
    if((estado.See_Casilla(row+1,col)==0 or estado.See_Casilla(row+1,col)==jugador or
      estado.See_Casilla(row+1,col)==jugador+3) and
      (estado.See_Casilla(row+2,col)==0 or estado.See_Casilla(row+2,col)==jugador or
        estado.See_Casilla(row+2,col)==jugador+3) and
      (estado.See_Casilla(row+3,col)==0 or estado.See_Casilla(row+3,col)==jugador or
        estado.See_Casilla(row+3,col)==jugador+3)){

              casillas_necesarias=0;
              if(estado.See_Casilla(row+1,col)==0 or estado.See_Casilla(row+1,col)==jugador or
                estado.See_Casilla(row+1,col)==jugador+3){
                  casillas_necesarias++;
              }
              if(estado.See_Casilla(row+2,col)==0 or estado.See_Casilla(row+2,col)==jugador or
                estado.See_Casilla(row+2,col)==jugador+3){
                casillas_necesarias++;
              }
              if(estado.See_Casilla(row+3,col)==0 or estado.See_Casilla(row+3,col)==jugador or
                estado.See_Casilla(row+3,col)==jugador+3){
                casillas_necesarias++;
              }
              suma+=2.0/casillas_necesarias;
    }
    //NorOeste
    //cout << "Fallo en analiza3"<<endl;
    if(col > 2){
      //cout << "Fallo en NorOeste"<<endl;
      if((estado.See_Casilla(row+1,col-1)==0 or estado.See_Casilla(row+1,col-1)==jugador or
        estado.See_Casilla(row+1,col-1)==jugador+3) and
        (estado.See_Casilla(row+2,col-2)==0 or estado.See_Casilla(row+2,col-2)==jugador or
          estado.See_Casilla(row+2,col-2)==jugador+3) and
        (estado.See_Casilla(row+3,col-3)==0 or estado.See_Casilla(row+3,col-3)==jugador or
          estado.See_Casilla(row+3,col-3)==jugador+3)){

                  casillas_necesarias=0;
                  if(estado.See_Casilla(row+1,col-1)==0 or estado.See_Casilla(row+1,col-1)==jugador or
                    estado.See_Casilla(row+1,col-1)==jugador+3){
                      casillas_necesarias++;
                  }
                  if(estado.See_Casilla(row+2,col-2)==0 or estado.See_Casilla(row+2,col-2)==jugador or
                      estado.See_Casilla(row+2,col-2)==jugador+3){
                      casillas_necesarias++;
                  }
                  if(estado.See_Casilla(row+3,col-3)==0 or estado.See_Casilla(row+3,col-3)==jugador or
                      estado.See_Casilla(row+3,col-3)==jugador+3){
                      casillas_necesarias++;
                  }
                  suma+=1.0/casillas_necesarias;

      }
    }

    //cout << "Fallo en analiza4"<<endl;
    //Noreste
    if(col < 4){
      //cout << "Fallo en Noreste"<<endl;
      if((estado.See_Casilla(row+1,col+1)==0 or estado.See_Casilla(row+1,col+1)==jugador or
        estado.See_Casilla(row+1,col+1)==jugador+3) and
        (estado.See_Casilla(row+2,col+2)==0 or estado.See_Casilla(row+2,col+2)==jugador or
          estado.See_Casilla(row+2,col+2)==jugador+3) and
        (estado.See_Casilla(row+3,col+3)==0 or estado.See_Casilla(row+3,col+3)==jugador or
          estado.See_Casilla(row+3,col+3)==jugador+3)){

                  casillas_necesarias=0;
                  if(estado.See_Casilla(row+1,col+1)==0 or estado.See_Casilla(row+1,col+1)==jugador or
                    estado.See_Casilla(row+1,col+1)==jugador+3){
                      casillas_necesarias++;
                  }
                  if(estado.See_Casilla(row+2,col+2)==0 or estado.See_Casilla(row+2,col+2)==jugador or
                      estado.See_Casilla(row+2,col+2)==jugador+3){
                      casillas_necesarias++;
                  }
                  if(estado.See_Casilla(row+3,col+3)==0 or estado.See_Casilla(row+3,col+3)==jugador or
                      estado.See_Casilla(row+3,col+3)==jugador+3){
                      casillas_necesarias++;
                  }
                  suma+=1.0/casillas_necesarias;

          }
      }
  //cout << "Fallo en analiza5"<<endl;
  //Este
  if(col < 4){
    //cout << "Fallo en Este"<<endl;
    if((estado.See_Casilla(row,col+1)==0 or estado.See_Casilla(row,col+1)==jugador or
      estado.See_Casilla(row,col+1)==jugador+3) and
      (estado.See_Casilla(row,col+2)==0 or estado.See_Casilla(row,col+2)==jugador or
        estado.See_Casilla(row,col+2)==jugador+3) and
      (estado.See_Casilla(row,col+3)==0 or estado.See_Casilla(row,col+3)==jugador or
        estado.See_Casilla(row,col+3)==jugador+3)){

                casillas_necesarias=0;
                if(estado.See_Casilla(row,col+1)==0 or estado.See_Casilla(row,col+1)==jugador or
                  estado.See_Casilla(row,col+1)==jugador+3){
                    casillas_necesarias++;
                }
                if(estado.See_Casilla(row,col+2)==0 or estado.See_Casilla(row,col+2)==jugador or
                    estado.See_Casilla(row,col+2)==jugador+3){
                    casillas_necesarias++;
                }
                if(estado.See_Casilla(row,col-3)==0 or estado.See_Casilla(row,col-3)==jugador or
                    estado.See_Casilla(row,col-3)==jugador+3){
                    casillas_necesarias++;
                }
                suma+=1.0/casillas_necesarias;

      }
    }

  //Oeste
  if(col > 2){
    //cout << "Fallo en Este"<<endl;
    if((estado.See_Casilla(row,col-1)==0 or estado.See_Casilla(row,col-1)==jugador or
      estado.See_Casilla(row,col-1)==jugador+3) and
      (estado.See_Casilla(row,col-2)==0 or estado.See_Casilla(row,col-2)==jugador or
        estado.See_Casilla(row,col-2)==jugador+3) and
      (estado.See_Casilla(row,col-3)==0 or estado.See_Casilla(row,col-3)==jugador or
        estado.See_Casilla(row,col-3)==jugador+3)){

                casillas_necesarias=0;
                if(estado.See_Casilla(row,col-1)==0 or estado.See_Casilla(row,col-1)==jugador or
                  estado.See_Casilla(row,col-1)==jugador+3){
                    casillas_necesarias++;
                }
                if(estado.See_Casilla(row,col-2)==0 or estado.See_Casilla(row,col-2)==jugador or
                    estado.See_Casilla(row,col-2)==jugador+3){
                    casillas_necesarias++;
                }
                if(estado.See_Casilla(row,col-3)==0 or estado.See_Casilla(row,col-3)==jugador or
                    estado.See_Casilla(row,col-3)==jugador+3){
                    casillas_necesarias++;
                }
                suma+=1.0/casillas_necesarias;

      }
    }
  }

  //Sur
  if(row > 2){
    //SurEste
    if(col < 4){
      if((estado.See_Casilla(row-1,col+1)==0 or estado.See_Casilla(row-1,col+1)==jugador or
        estado.See_Casilla(row-1,col+1)==jugador+3) and
        (estado.See_Casilla(row-2,col+2)==0 or estado.See_Casilla(row-2,col+2)==jugador or
          estado.See_Casilla(row-2,col+2)==jugador+3) and
        (estado.See_Casilla(row-3,col+3)==0 or estado.See_Casilla(row-3,col+3)==jugador or
          estado.See_Casilla(row-3,col+3)==jugador+3)){

            casillas_necesarias=0;
            if(estado.See_Casilla(row-1,col+1)==0 or estado.See_Casilla(row-1,col+1)==jugador or
              estado.See_Casilla(row-1,col+1)==jugador+3){
                casillas_necesarias++;
            }
            if(estado.See_Casilla(row-2,col+2)==0 or estado.See_Casilla(row-2,col+2)==jugador or
                estado.See_Casilla(row-2,col+2)==jugador+3){
                casillas_necesarias++;
            }
            if(estado.See_Casilla(row-3,col+3)==0 or estado.See_Casilla(row-3,col+3)==jugador or
                estado.See_Casilla(row-3,col+3)==jugador+3){
                casillas_necesarias++;
            }
            suma+=1.0/casillas_necesarias;

        }
      }
    //SurOeste
    if(col > 2){
      if((estado.See_Casilla(row-1,col-1)==0 or estado.See_Casilla(row-1,col-1)==jugador or
        estado.See_Casilla(row-1,col-1)==jugador+3) and
        (estado.See_Casilla(row-2,col-2)==0 or estado.See_Casilla(row-2,col-2)==jugador or
          estado.See_Casilla(row-2,col-2)==jugador+3) and
        (estado.See_Casilla(row-3,col-3)==0 or estado.See_Casilla(row-3,col-3)==jugador or
          estado.See_Casilla(row-3,col-3)==jugador+3)){

            casillas_necesarias=0;
            if(estado.See_Casilla(row-1,col-1)==0 or estado.See_Casilla(row-1,col-1)==jugador or
              estado.See_Casilla(row-1,col-1)==jugador+3){
                casillas_necesarias++;
            }
            if(estado.See_Casilla(row-2,col-2)==0 or estado.See_Casilla(row-2,col-2)==jugador or
                estado.See_Casilla(row-2,col-2)==jugador+3){
                casillas_necesarias++;
            }
            if(estado.See_Casilla(row-3,col-3)==0 or estado.See_Casilla(row-3,col-3)==jugador or
                estado.See_Casilla(row-3,col-3)==jugador+3){
                casillas_necesarias++;
            }
            suma+=1.0/casillas_necesarias;
        }
      }
    }
  return suma;
}


// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)
double Valoracion(const Environment &estado, int jugador){
  double suma = 0;
  //cout << "Será aquí?"<<endl;
  for(int j = 0; j < 7; j++){
    int i = 0;
    int casilla = estado.See_Casilla(i,j);
    //cout << "Aquí"<<endl;
    while(casilla!=0 and i < 6){
      //cout << "Analiza??"<<i<<" " << j <<endl;
      double enRaya = analizaEnRaya(i,j,estado);
      //cout << "Analiza..."<<endl;
      if(casilla == jugador or casilla == jugador+3){
        suma-=enRaya;
      }
      else{
        suma+=enRaya;
      }
      i++;
      //cout << "Puedo ver casilla"<< i << " "<<j <<endl;
      casilla = estado.See_Casilla(i,j);
      //cout << "Yes"<<endl;
    }
  }
  //cout << "Nooo..."<<endl;
  return suma;
}





// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<8; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}

/*
Poda alfa beta:
  Environment estado es el estado que queremos evaluar.
  int jugador es la marca de nuestro jugador.
  int profundidad es la profundidad en la que estamos.
  int max_profundidad es el máximo de profundidad al que podemos llegar.
  double alpha es el valor alpha de la poda actual.
  double beta es el valor beta de la poda actual.
*/
double Poda_AlfaBeta(Environment &estado, int jugador, int profundidad, int max_profundidad, double alpha, double beta){
    Environment V[8];
    bool Vb[8];
    int ganador = estado.RevisarTablero();

    if(ganador == jugador){
        return masinf-10*profundidad;
    }
    else if(ganador != 0){
        return menosinf-10*profundidad;
    }
    else if(profundidad == max_profundidad){
        return Valoracion(estado,jugador);
    }
    else if( jugador == estado.JugadorActivo()/*Soy yo el jugador que juega ahora*/){
        estado.GenerateAllMoves(V);
        estado.possible_actions(Vb);
        for(int i = 0; i < 8 and  beta > alpha; i++){
          if(Vb[i]){
            alpha = max(alpha,Poda_AlfaBeta(V[i],jugador,profundidad+1,max_profundidad,alpha,beta));
          }
        }
        return alpha;
        //Maximizo la función.
    }
    else{//Si no soy yo el jugador que juega
        estado.GenerateAllMoves(V);
        estado.possible_actions(Vb);
        for(int i = 0; i < 8 and beta > alpha; i++){
          if(Vb[i]){
            beta = min(beta,Poda_AlfaBeta(V[i],jugador,profundidad+1,max_profundidad,alpha,beta));
          }
        }
        return beta;
      //Minimiza la función
    }
}





// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acci�n que se va a devolver
    bool aplicables[8]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable
                        // aplicables[1]==true si PUT2 es aplicable
                        // aplicables[2]==true si PUT3 es aplicable
                        // aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable
                        // aplicables[5]==true si PUT6 es aplicable
                        // aplicables[6]==true si PUT7 es aplicable
                        // aplicables[7]==true si BOOM es aplicable



    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha, beta; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    // actual_.PintaTablero();
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;


    /*--------------------- COMENTAR Desde aqui
    //cout << "\n\t";
    if(jugador_==2){
      int n_opciones=0;
      JuegoAleatorio(aplicables, opciones, n_opciones);

      if (n_act==0){
        //(jugador_==1) ? cout << "Verde: " : //cout << "Azul: ";
        //cout << " No puede realizar ninguna accion!!!\n";
        //accion = Environment::actIDLE;
      }
      else if (n_act==1){
             //(jugador_==1) ? //cout << "Verde: " : //cout << "Azul: ";
              //cout << " Solo se puede realizar la accion << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
              accion = static_cast< Environment::ActionType > (opciones[0]);

      }
      else { // Hay que elegir entre varias posibles acciones
        int aleatorio = rand()%n_opciones;
        //cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[aleatorio])  ) << endl;
        accion = static_cast< Environment::ActionType > (opciones[aleatorio]);
      }
      return accion;
    }


    //--------------------- COMENTAR Hasta aqui*/


    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------


    // Opcion: Poda AlfaBeta
    // NOTA: La parametrizacion es solo orientativa
    Environment V[8];
    bool Vb[8];
    int movimientos = actual_.GenerateAllMoves(V);
    actual_.possible_actions(Vb);
    int mejor = 0;
    double best = menosinf, puntActual = menosinf;
    int i = 0;
    //if(jugador_==1){
      while(i < 8){
        if(Vb[i]){
          puntActual = Poda_AlfaBeta(V[i],jugador_, 0, PROFUNDIDAD_ALFABETA, menosinf, masinf);
          cout << i << " puntuacion:"<<puntActual<<endl;
          if(puntActual >= best){
            if(puntActual > best or i == 7){
              best = puntActual;
              mejor = i;
            }
          }
        }
        i++;
      }
    //}
    switch (mejor) {
      case 0:
        return static_cast<Environment::ActionType>(mejor);
      break;
      case 1:
        return static_cast<Environment::ActionType>(mejor);
      break;
      case 2:
        return static_cast<Environment::ActionType>(mejor);
      break;
      case 3:
        return static_cast<Environment::ActionType>(mejor);
      break;
      case 4:
        return static_cast<Environment::ActionType>(mejor);
      break;
      case 5:
        return static_cast<Environment::ActionType>(mejor);
      break;
      case 6:
        return static_cast<Environment::ActionType>(mejor);
      break;
      case 7:
        return static_cast<Environment::ActionType>(mejor);
      break;
//cout
    }
    // valor = Poda_AlfaBeta(actual_, jugador_, 0, PROFUNDIDAD_ALFABETA, alpha, beta);
    ////cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;
}
