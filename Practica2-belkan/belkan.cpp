#include "belkan.h"
#include "conexion.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <cstring>
#include <algorithm>
#include <cmath>

//#define NO_CHOCAR
#define MIGUITAS


using namespace std;


// -----------------------------------------------------------
void PasarVectoraMapaCaracteres(int fila, int columna, char m[200][200], char *v, int brujula){
  m[fila][columna]=v[0];

    switch(brujula){
        case 0: // Orientacion Norte

		m[fila-1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila-2][columna+i-1]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila-3][columna+j-2]=v[5+j];
		}
	   break;
	case 1: // Orientacion Este
		m[fila][columna+1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+i-1][columna+2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+j-2][columna+3]=v[5+j];
		}
	   break;
    case 2: // Orientacion Sur
		m[fila+1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+2][columna+1-i]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+3][columna+2-j]=v[5+j];
		}
		break;
    case 3: // Orientacion Oeste
		m[fila][columna-1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+1-i][columna-2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+2-j][columna-3]=v[5+j];
		}

        break;
    }

}
void PasarVectoraMapaCaracteres_(int fila, int columna, char m[100][100], char *v, int brujula){
    m[fila][columna]=v[0];

    switch(brujula){
        case 0: // Orientacion Norte

        m[fila-1][columna]=v[1];
        for (int i=0; i<3; i++){
          m[fila-2][columna+i-1]=v[2+i];
        }
        for (int j=0; j<5; j++){
          m[fila-3][columna+j-2]=v[5+j];
        }
       break;
    case 1: // Orientacion Este
        m[fila][columna+1]=v[1];
        for (int i=0; i<3; i++){
          m[fila+i-1][columna+2]=v[2+i];
        }
        for (int j=0; j<5; j++){
          m[fila+j-2][columna+3]=v[5+j];
        }
       break;
    case 2: // Orientacion Sur
        m[fila+1][columna]=v[1];
        for (int i=0; i<3; i++){
          m[fila+2][columna+1-i]=v[2+i];
        }
        for (int j=0; j<5; j++){
          m[fila+3][columna+2-j]=v[5+j];
        }
        break;
    case 3: // Orientacion Oeste
        m[fila][columna-1]=v[1];
        for (int i=0; i<3; i++){
          m[fila+1-i][columna-2]=v[2+i];
        }
        for (int j=0; j<5; j++){
          m[fila+2-j][columna-3]=v[5+j];
        }

        break;
    }
}
int Agent::rellena_solucion(int dx,int dy, int dx_,int dy_){
    if(dx == dx_ and dy == dy_){
        orientacion = orientacion_;
        for(int i = 0; i < 100; i++){
            for(int j = 0; j < 100; j++){
                if(mapa_entorno_[y_-y+j][x_-x+i] != '?'){
                    mapa_solucion_[j][i]=mapa_entorno_[y_-y+j][x_-x+i];
                }
                else if(mapa_solucion_[j][i] != '?'){
                    mapa_entorno_[y_-y+j][x_-x+i]=mapa_solucion_[j][i];
                }
            }
        }
    }

    else if(dx == dy_ and dy == -dx_ ){
        orientacion = (3 + orientacion_)%4;
        for(int i = 0; i < 100; i++){
            for(int j = 0; j < 100; j++){
                if(mapa_entorno_[y_-x+i][x_+y-j] != '?'){
                    mapa_solucion_[j][i]=mapa_entorno_[y_-x+i][x_+y-j];
                }
                else if(mapa_solucion_[j][i] != '?'){
                    mapa_entorno_[y_-x+i][x_+y-j]=mapa_solucion_[j][i];
                }
            }
        }

    }
    else if(dx == -dx_ and dy == -dy_ ){
        orientacion = (2 + orientacion_)%4;
        for(int i = 0; i < 100; i++){
            for(int j = 0; j < 100; j++){
                if(mapa_entorno_[y_+y-j][x_+x-i] != '?'){
                    mapa_solucion_[j][i] = mapa_entorno_[y_+y-j][x_+x-i];
                }
                else if(mapa_solucion_[j][i] != '?'){
                    mapa_entorno_[y_+y-j][x_+x-i] = mapa_solucion_[j][i];
                }
            }
        }
    }
    else if(dx == -dy_ and dy == dx_ ){
        orientacion = (1 + orientacion_)%4;
        for(int i = 0; i < 100; i++){
            for(int j = 0; j < 100; j++){
                if(mapa_entorno_[y_+x-i][x_-y+j] != '?'){
                    mapa_solucion_[j][i]=mapa_entorno_[y_+x-i][x_-y+j];
                }
                else if(mapa_solucion_[j][i] != '?'){
                    mapa_entorno_[y_+x-i][x_-y+j]=mapa_solucion_[j][i];
                }
            }
        }
    }
    return orientacion;
}




// -----------------------------------------------------------
bool Agent::puedo_avanzar(int y, int x){
    if((mapa_entorno_[y][x] != 'B' or EN_USO_ == '6') and
        (mapa_entorno_[y][x]!= 'A' or EN_USO_ == '0') and
        mapa_entorno_[y][x] != 'P' and mapa_entorno_[y][x] != 'M'
        and (mapa_entorno_[y][x] != 'D' or EN_USO_ == '2') and
         (mapa_objetos_[y][x] < 'a' or mapa_objetos_[y][x] > 'z' )){
        return true;
    }
    else{
        return false;
    }
}
int Agent::mejor_opcion(bool norte, bool este, bool sur, bool oeste){
    if(orientacion_ == 0 and norte){
        return orientacion_;
    }
    else if(orientacion_ == 1 and este){
        return 1;
    }
    else if(orientacion_ == 2 and sur){
        return 2;
    }
    else if(orientacion_ == 3 and oeste){
        return 3;
    }
    int minimo = max(N,max(S,max(E,W)));
    if(norte){
        minimo = min(minimo,N);
    }
    if(este){
        minimo = min(minimo,E);
    }
    if(sur){
        minimo = min(minimo,S);
    }
    if(oeste){
        minimo = min(minimo,W);
    }
    if(minimo == N and norte){
        return 0;
    }
    if(minimo == E and este){
        return 1;
    }
    if(minimo == S and sur){
        return 2;
    }
    if(minimo == W and oeste){
        return 3;
    }
}


void Agent::Perceive(Environment &env)
{
	env.SenSorStatus(VISTA_, SURFACE_, MENSAJE_, REINICIADO_, EN_USO_, MOCHILLA_, PUNTUACION_, FIN_JUEGO_, SALUD_, false);

}


bool Agent::Perceive_Remote(conexion_client &Cliente, Environment &env)
{
	bool actualizado=false;


	actualizado = env.Perceive_Remote(Cliente);
	if (actualizado)
		env.SenSorStatus(VISTA_, SURFACE_, MENSAJE_, REINICIADO_, EN_USO_, MOCHILLA_, PUNTUACION_, FIN_JUEGO_, SALUD_, true);

    return actualizado;
}


// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion){
	switch (accion){
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actIDLE: return "IDLE";
	case Agent::actPICKUP: return "PICK UP";
	case Agent::actPUTDOWN: return "PUT DOWN";
	case Agent::actPUSH: return "PUSH";
	case Agent::actPOP: return "POP";
	case Agent::actGIVE: return "GIVE";
	case Agent::actTHROW: return "THROW";
	default: return "????";
	}
}
Agent::ActionType Agent::accion(int i){
    switch (i)
        {
    case 0: return Agent::actFORWARD;
    case 1: return Agent::actTURN_L;
    case 2: return Agent::actTURN_R;
    case 3: return Agent::actIDLE;
    case 4: return Agent::actPICKUP;
    case 5: return Agent::actPUTDOWN;
    case 6: return Agent::actPUSH;
    case 7: return Agent::actPOP;
    case 8: return Agent::actGIVE;
    case 9: return Agent::actTHROW;
    default: return Agent::actIDLE;
    }
}


// -----------------------------------------------------------
void Agent::ActualizarInformacion(Environment *env){
	// Actualizar mi informacion interna
  actualizaPesos();
	if (REINICIADO_){
		// Lo que tengas que hacer si eres reposicionado en el juego

        for(int i = 0; i < 200; i++){
            for(int j= i; j < 200;j++){
                mapa_entorno_[i][j] = mapa_entorno_[j][i] = '?';
                mapa_objetos_[i][j] = mapa_objetos_[j][i] = '?';
                miguitas_[i][j]= miguitas_[j][i]=0;
            }

        }
        x_=99;
        y_=99;
        orientacion_=3;
        orientado = false;
        primera_amarilla = false;
        orientacion = x = y = -1;
	}
    else{

    	switch(last_accion_){
    	  case 0: //avanzar
            miguitas_[y_][x_]+=1;
            switch(orientacion_){
        	    case 0: // norte
                    N++;
                    miguitas_[y_][x_-1]++;
                    miguitas_[y_][x_]++;
                    miguitas_[y_][x_+1]++;
                    miguitas_[y_+1][x_-2]++;
                    miguitas_[y_+1][x_-1]++;
                    miguitas_[y_+1][x_]++;
                    miguitas_[y_+1][x_+1]++;
                    miguitas_[y_+1][x_+2]++;
        		    y_--;
        		    break;
        	    case 1: // este
                    E++;
                    miguitas_[y_-1][x_]++;
                    miguitas_[y_][x_]++;
                    miguitas_[y_+1][x_]++;
                    miguitas_[y_-2][x_-1]++;
                    miguitas_[y_-1][x_-1]++;
                    miguitas_[y_][x_-1]++;
                    miguitas_[y_+1][x_-1]++;
                    miguitas_[y_+2][x_-1]++;
        		    x_++;
        		    break;
        	    case 2: // sur
                    S++;
                    miguitas_[y_][x_-1]++;
                    miguitas_[y_][x_]++;
                    miguitas_[y_][x_+1]++;
                    miguitas_[y_-1][x_-2]++;
                    miguitas_[y_-1][x_-1]++;
                    miguitas_[y_-1][x_]++;
                    miguitas_[y_-1][x_+1]++;
                    miguitas_[y_-1][x_+2]++;
        		    y_++;
        		    break;
        	    case 3: // oeste
                    W++;
                    miguitas_[y_-1][x_]++;
                    miguitas_[y_][x_]++;
                    miguitas_[y_+1][x_]++;

                    miguitas_[y_-2][x_+1]++;
                    miguitas_[y_-1][x_+1]++;
                    miguitas_[y_][x_+1]++;
                    miguitas_[y_+1][x_+1]++;
                    miguitas_[y_+2][x_+1]++;
        		    x_--;
        		    break;
            }
            if(orientado){
                switch(orientacion){
                    case 0: // norte
                        y--;
                        break;
                    case 1: // este
                        x++;
                        break;
                    case 2: // sur
                        y++;
                        break;
                    case 3: // este
                        x--;
                        break;
                }
            }

    	  break;
    	  case 1: // girar izq
    		  orientacion_=(orientacion_+3)%4;
              if(orientado){
                orientacion = (orientacion + 3)%4;
              }
    		  break;
    	  case 2: // girar dch
    		  orientacion_=(orientacion_+1)%4;
              if(orientado){
                orientacion = (orientacion + 1)%4;
              }
    		  break;
    	}
    }

	// Comprobacion para no salirme del rango del mapa
	bool algo_va_mal=false;
	if (y_<0){
		y_=0;
		algo_va_mal=true;
	}
	else if (y_>199){
		y_=199;
		algo_va_mal=true;
	}
	if (x_<0){
		x_=0;
		algo_va_mal=true;
	}
	else if (x_>199){
		x_=199;
		algo_va_mal=true;
	}

	if (algo_va_mal){
		cout << "CUIDADO: NO ESTAS CONTROLANDO BIEN LA UBICACION DE TU AGENTE\n";
	}


	PasarVectoraMapaCaracteres(y_,x_,mapa_entorno_,VISTA_,orientacion_);
	PasarVectoraMapaCaracteres(y_,x_,mapa_objetos_,SURFACE_,orientacion_);

  if (orientado){
    PasarVectoraMapaCaracteres_(y,x,mapa_solucion_,VISTA_,orientacion);
  }

	env->ActualizarMatrizUsuario(mapa_entorno_);

    /**
     * @brief Parte para rellenar mapa.
     * @details Depende de si está en una casilla de control o no.
     *
     * Formato de entrada:
     * "PK fila: "+to_string(agentPosX_)+" columna: " + to_string(agentPosY_)+". "
     * @param _ [description]
     * @return [description]
     */

     // Si no estoy orientado todavía.

    if(not orientado and VISTA_[0] != PK and not primera_amarilla){

    }
    else if(not orientado and VISTA_[0] == PK and not primera_amarilla){

        primera_amarilla = true;

        string mens = MENSAJE_;
        string::iterator i;
        for( i = mens.begin(); *i != ' '; ++i);
        mens.erase(mens.begin(),++i);
        for( i = mens.begin(); *i != ' '; ++i);
        mens.erase(mens.begin(),++i);
        for( i = mens.begin(); *i != ' '; ++i);
        string posY = string(mens.begin(),i);
        mens.erase(mens.begin(),++i);
        for(i=mens.begin();*i != ' ';++i);
        mens.erase(mens.begin(),++i);
        for(i=mens.begin();*i != '.';++i);
        string posX = string(mens.begin(),i);


        x1real = atoi(posX.c_str());
        y1real = atoi(posY.c_str());

        x1relativo = x_;
        y1relativo = y_;
    }
    else if(not orientado and primera_amarilla){

        if( VISTA_[0] == PK and ( x1relativo != x_ or y1relativo != y_)) {
            orientado = true;

            string mens = MENSAJE_;
            string::iterator i;
            for( i = mens.begin(); *i != ' '; ++i);
            mens.erase(mens.begin(),++i);
            for( i = mens.begin(); *i != ' '; ++i);
            mens.erase(mens.begin(),++i);
            for( i = mens.begin(); *i != ' '; ++i);
            string posY = string(mens.begin(),i);
            mens.erase(mens.begin(),++i);
            for(i=mens.begin();*i != ' ';++i);
            mens.erase(mens.begin(),++i);
            for(i=mens.begin();*i != '.';++i);
            string posX = string(mens.begin(),i);

            x = atoi(posX.c_str());
            y = atoi(posY.c_str());


            int dx = x-x1real;
            int dy = y-y1real;
            int dx_ = x_ - x1relativo;
            int dy_ = y_ - y1relativo;

            rellena_solucion(dx,dy,dx_,dy_);



        }
    }
    cout << "Porcentaje: " << env->Comparar(mapa_solucion_)<< endl;

}

// -----------------------------------------------------------

int Agent::vacias( Casilla C){
    int X = C.getX(),Y = C.getY(), OR = C.getOrientacion();
    int vacias_ = 0;
    if(OR == 0){
        if(mapa_entorno_[Y-1][X] == '?'){
            vacias_++;
        }
        for(int i = X-1; i <= X+1;i++){
            if(mapa_entorno_[Y-2][i] == '?'){
                vacias_++;
            }
        }
        for(int i = X-2; i <= X+2;i++){
            if(mapa_entorno_[Y-3][i] == '?'){
                vacias_++;
            }
        }

    }
    else if(OR == 1){
        if(mapa_entorno_[Y][X+1] == '?'){
            vacias_++;
        }
        for(int i = Y-1; i <= Y+1;i++){
            if(mapa_entorno_[i][X+2] == '?'){
                vacias_++;
            }
        }
        for(int i = Y-2; i <= Y+2;i++){
            if(mapa_entorno_[i][X+3] == '?'){
                vacias_++;
            }
        }
    }
    else if(OR == 2){
        if(mapa_entorno_[Y+1][X] == '?'){
            vacias_++;
        }
        for(int i = X-1; i <= X+1;i++){
            if(mapa_entorno_[Y+2][i] == '?'){
                vacias_++;
            }
        }
        for(int i = X-2; i <= X+2;i++){
            if(mapa_entorno_[Y+3][i] == '?'){
                vacias_++;
            }
        }
    }
    else if( OR == 3){
        if(mapa_entorno_[Y][X-1] == '?'){
            vacias_++;
        }
        for(int i = Y-1; i <= Y+1;i++){
            if(mapa_entorno_[i][X-2] == '?'){
                vacias_++;
            }
        }
        for(int i = Y-2; i <= Y+2;i++){
            if(mapa_entorno_[i][X-3] == '?'){
                vacias_++;
            }
        }
    }
    return vacias_;
}
	char Agent::correspondencia(char personaje){
    switch (personaje) {
      case PRINCESA1:
      case PRINCESA2:
        return ORO;
        break;
      case LEONARDO1:
      case LEONARDO2:
        return OSCAR;
        break;
      case PRINCIPE1:
      case PRINCIPE2:
        return ORO;
        break;
      case BRUJA1:
      case BRUJA2:
        return MANZANA;
        break;
      case PROFE1:
      case PROFE2:
        return ALGORITMO;
        break;
      default:
        return '!';
    }
  }

void Agent::actualizaPesos(){
  for(int i = 3; i < 197; i++){
    for(int j = 3; j< 197;j++){
      mapa_pesos_[i][j] = vacias(Casilla(j,i,NORTE))+vacias(Casilla(j,i,ESTE))+vacias(Casilla(j,i,SUR))+vacias(Casilla(j,i,OESTE));
    }
  }

  for(int i = 3; i < 197; i++){
    for(int j = 3; j < 197; j++){
      bool atraccion = false;
      bool repulsion = false;
      if(not orientado and mapa_entorno_[i][j] == PK and (i != y1relativo or j != x1relativo)){
        atraccion = true;
      }
      if(mapa_entorno_[i][j] == puerta and (EN_USO_== LLAVE or
        MOCHILLA_[0] == LLAVE or
        MOCHILLA_[1] == LLAVE or
        MOCHILLA_[2] == LLAVE or
        MOCHILLA_[3] == LLAVE)){
        if(paso_puerta> 0){
          paso_puerta--;
          repulsion = true;
        }
        else{
          atraccion = true;
        }
        if(i == y_ and j == x_){
          paso_puerta = 10;
        }
      }

      if(EN_USO_ == correspondencia(mapa_objetos_[i][j]) or
        MOCHILLA_[0] == correspondencia(mapa_objetos_[i][j]) or
        MOCHILLA_[1] == correspondencia(mapa_objetos_[i][j]) or
        MOCHILLA_[2] == correspondencia(mapa_objetos_[i][j]) or
        MOCHILLA_[3] == correspondencia(mapa_objetos_[i][j]) or
        MOCHILLA_[4] == correspondencia(mapa_objetos_[i][j])){
          atraccion = true;
        }
      if(NObjetos < MAXObjetos and (mapa_objetos_[i][j] == ZAPATILLAS
        or mapa_objetos_[i][j] == BIKINI
        or mapa_objetos_[i][j] == LLAVE
        or mapa_objetos_[i][j] == PIEDRA
        or mapa_objetos_[i][j] == ORO
        or mapa_objetos_[i][j] == ALGORITMO
        or mapa_objetos_[i][j] == MANZANA
        or mapa_objetos_[i][j] == OSCAR)){
          atraccion = true;
      }
      if(EN_USO_ == PIEDRA and mapa_objetos_[i][j] >= 'a' and mapa_objetos_[i][j] <= 'd'){
        atraccion = true;
      }
      if(mapa_objetos_[i][j] == OSO and EN_USO_ != PIEDRA){
        repulsion = true;
      }
      if(repulsion){
        mapa_pesos_[i+1][j]-= 10;
        mapa_pesos_[i][j+1]-= 10;
        mapa_pesos_[i][j]-= 20;
        mapa_pesos_[i][j-1]-= 10;
        mapa_pesos_[i-1][j]-= 10;
      }
      else if(atraccion){
        mapa_pesos_[i+1][j] = mapa_pesos_[i+1][j] + 10;
        mapa_pesos_[i][j+1] =mapa_pesos_[i][j+1]+ 10;
        mapa_pesos_[i][j] =mapa_pesos_[i][j]+20;
        mapa_pesos_[i][j-1] = mapa_pesos_[i][j-1]+10;
        mapa_pesos_[i-1][j] =mapa_pesos_[i-1][j]+  10;
      }
    }
  }
}
Agent::ActionType Agent::Think(){
	Agent::ActionType accion = actFORWARD;

    #ifdef NO_CHOCAR
    switch(orientacion_){
        case 0:
            if(not puedo_avanzar(y_-1,x_)) {
                accion = actTURN_R;
            }
        break;
        case 1:
            if(not puedo_avanzar(y_,x_+1) ){
                accion = actTURN_R;
            }
        break;
        case 2:
            if(not puedo_avanzar(y_+1,x_) ){
                accion = actTURN_R;
            }
        break;
        case 3:
            if(not puedo_avanzar(y_,x_-1) ){
                accion = actTURN_R;
            }
        break;
    }
    #endif

    #ifdef MIGUITAS

    int norte = miguitas_[y_-1][x_] - 200*mapa_pesos_[y_-1][x_];
    int este = miguitas_[y_][x_+1] - 200*mapa_pesos_[y_][x_+1];
    int sur = miguitas_[y_+1][x_] - 200*mapa_pesos_[y_+1][x_];
    int oeste = miguitas_[y_][x_-1] - 200*mapa_pesos_[y_][x_-1];
    bool Nmejor=false,Emejor = false,Smejor = false, Wmejor = false;
    if(mejor ==-1){
        if(puedo_avanzar(y_-1,x_)
            and (norte <= este or not puedo_avanzar(y_,x_+1))
            and (norte <= sur or not puedo_avanzar(y_+1,x_))
            and (norte <= oeste or not puedo_avanzar(y_,x_-1))){
            Nmejor = true;
        }
        if(puedo_avanzar(y_,x_+1)
            and (este <= norte or not puedo_avanzar(y_-1,x_))
            and (este <= sur or not puedo_avanzar(y_+1,x_))
            and (este <= oeste or not puedo_avanzar(y_,x_-1))){
            Emejor = true;
        }
        if(puedo_avanzar(y_+1,x_)
            and (sur <= norte or not puedo_avanzar(y_-1,x_))
            and (sur <= este or not puedo_avanzar(y_,x_+1))
            and (sur <= oeste or not puedo_avanzar(y_,x_-1))){
            Smejor = true;
        }
        if(puedo_avanzar(y_,x_-1)
            and (oeste <= norte or not puedo_avanzar(y_-1,x_))
            and (oeste <= este or not puedo_avanzar(y_,x_+1))
            and (oeste <= sur or not puedo_avanzar(y_+1,x_))){
            Wmejor = true;
        }
        mejor = mejor_opcion(Nmejor,Emejor,Smejor,Wmejor);
    }

    switch(orientacion_){
        case 0:
        if(mejor == 0){
            accion = actFORWARD;
            mejor = -1;
        }
        else if(mejor == 1){
            accion = actTURN_R;
        }
        else if(mejor == 3){
            accion = actTURN_L;
        }
        else{
            if(rand()%2==0){
                accion=actTURN_R;
            }
            else{
                accion=actTURN_L;
            }
        }
        break;
        case 1:
        if(mejor == 1){
            accion = actFORWARD;
            mejor=-1;
        }
        else if(mejor == 2){
            accion = actTURN_R;
        }
        else if(mejor == 0){
            accion = actTURN_L;
        }
        else{
            if(rand()%2==0){
                accion=actTURN_R;
            }
            else{
                accion=actTURN_L;
            }
        }
        break;
        case 2:
        if(mejor == 2){
            accion = actFORWARD;
            mejor=-1;
        }
        else if(mejor == 3){
            accion = actTURN_R;
        }
        else if(mejor == 1){
            accion = actTURN_L;
        }
        else{
            if(rand()%2==0){
                accion=actTURN_R;
            }
            else{
                accion=actTURN_L;
            }
        }
        break;
        case 3:
        if(mejor == 3){
            accion = actFORWARD;
            mejor=-1;
        }
        else if(mejor == 0){
            accion = actTURN_R;
        }
        else if(mejor == 2){
            accion = actTURN_L;
        }
        else{
            if(rand()%2==0){
                accion=actTURN_R;
            }
            else{
                accion=actTURN_L;
            }
        }
        break;
    }

    #endif
    pasos++;
    if(pasos >= 5000){
      pasos = 0;
      for(int i = 0; i<200; i++){
        for(int j = 0; j < 200; j++){
          miguitas_[i][j] = 0;
        }
      }
    }
    bool accion_reactiva = false;
    //COMPORTAMIENTO DE PRIMERA PRIORIDAD: Dar objetos a los personajes.
    if(correspondencia(SURFACE_[1]) == EN_USO_ or
        correspondencia(SURFACE_[1]) == MOCHILLA_[0] or
        correspondencia(SURFACE_[1]) == MOCHILLA_[1] or
        correspondencia(SURFACE_[1]) == MOCHILLA_[2] or
        correspondencia(SURFACE_[1]) == MOCHILLA_[3]){
          if(EN_USO_ == correspondencia(SURFACE_[1])){
            accion = actGIVE;
            NObjetos--;
          }
          else{
            if(EN_USO_ != '-'){
              accion = actPUSH;
            }
            else{
              accion = actPOP;
            }
          }
          accion_reactiva = true;
          cout << "Dar objetos a los personajes"<<endl;
      }
      ////COMPORTAMIENTO DE SEGUNDA PRIORIDAD:Girar cuando hay personajes a los
      //que les puedo dar objetos.
      if(not accion_reactiva){
        switch (orientacion_) {
          case NORTE:
            if(correspondencia(mapa_objetos_[y_][x_-1]) == EN_USO_ or
              correspondencia(mapa_objetos_[y_][x_-1]) == MOCHILLA_[0] or
              correspondencia(mapa_objetos_[y_][x_-1]) == MOCHILLA_[1] or
              correspondencia(mapa_objetos_[y_][x_-1]) == MOCHILLA_[2] or
              correspondencia(mapa_objetos_[y_][x_-1]) == MOCHILLA_[3] ){
                accion = actTURN_L;
                accion_reactiva = true;
              }
            else if(correspondencia(mapa_objetos_[y_][x_+1]) == EN_USO_ or
              correspondencia(mapa_objetos_[y_][x_+1]) == MOCHILLA_[0] or
              correspondencia(mapa_objetos_[y_][x_+1]) == MOCHILLA_[1] or
              correspondencia(mapa_objetos_[y_][x_+1]) == MOCHILLA_[2] or
              correspondencia(mapa_objetos_[y_][x_+1]) == MOCHILLA_[3] ){
                accion = actTURN_R;
                accion_reactiva = true;
              }
          break;
          case ESTE:
          if(correspondencia(mapa_objetos_[y_-1][x_]) == EN_USO_ or
            correspondencia(mapa_objetos_[y_-1][x_]) == MOCHILLA_[0] or
            correspondencia(mapa_objetos_[y_-1][x_]) == MOCHILLA_[1] or
            correspondencia(mapa_objetos_[y_-1][x_]) == MOCHILLA_[2] or
            correspondencia(mapa_objetos_[y_-1][x_]) == MOCHILLA_[3] ){
              accion = actTURN_L;
              accion_reactiva = true;
            }
          else if(correspondencia(mapa_objetos_[y_+1][x_]) == EN_USO_ or
            correspondencia(mapa_objetos_[y_+1][x_]) == MOCHILLA_[0] or
            correspondencia(mapa_objetos_[y_+1][x_]) == MOCHILLA_[1] or
            correspondencia(mapa_objetos_[y_+1][x_]) == MOCHILLA_[2] or
            correspondencia(mapa_objetos_[y_+1][x_]) == MOCHILLA_[3] ){
              accion = actTURN_R;
              accion_reactiva = true;
            }
          break;
          case SUR:
          if(correspondencia(mapa_objetos_[y_][x_+1]) == EN_USO_ or
            correspondencia(mapa_objetos_[y_][x_+1]) == MOCHILLA_[0] or
            correspondencia(mapa_objetos_[y_][x_+1]) == MOCHILLA_[1] or
            correspondencia(mapa_objetos_[y_][x_+1]) == MOCHILLA_[2] or
            correspondencia(mapa_objetos_[y_][x_+1]) == MOCHILLA_[3] ){
              accion = actTURN_L;
              accion_reactiva = true;
            }
          else if(correspondencia(mapa_objetos_[y_][x_-1]) == EN_USO_ or
            correspondencia(mapa_objetos_[y_][x_-1]) == MOCHILLA_[0] or
            correspondencia(mapa_objetos_[y_][x_-1]) == MOCHILLA_[1] or
            correspondencia(mapa_objetos_[y_][x_-1]) == MOCHILLA_[2] or
            correspondencia(mapa_objetos_[y_][x_-1]) == MOCHILLA_[3] ){
              accion = actTURN_R;
              accion_reactiva = true;
            }
          break;
          case OESTE:
          if(correspondencia(mapa_objetos_[y_+1][x_]) == EN_USO_ or
            correspondencia(mapa_objetos_[y_+1][x_]) == MOCHILLA_[0] or
            correspondencia(mapa_objetos_[y_+1][x_]) == MOCHILLA_[1] or
            correspondencia(mapa_objetos_[y_+1][x_]) == MOCHILLA_[2] or
            correspondencia(mapa_objetos_[y_+1][x_]) == MOCHILLA_[3] ){
              accion = actTURN_L;
              accion_reactiva = true;
            }
          else if(correspondencia(mapa_objetos_[y_-1][x_]) == EN_USO_ or
            correspondencia(mapa_objetos_[y_-1][x_]) == MOCHILLA_[0] or
            correspondencia(mapa_objetos_[y_-1][x_]) == MOCHILLA_[1] or
            correspondencia(mapa_objetos_[y_-1][x_]) == MOCHILLA_[2] or
            correspondencia(mapa_objetos_[y_-1][x_]) == MOCHILLA_[3] ){
              accion = actTURN_R;
              accion_reactiva = true;
            }
          break;
          cout << "Girar cuando hay personas a las que le puedo dar cosas"<<endl;
        }

      }
      ////COMPORTAMIENTO DE TERCERA PRIORIDAD: Cojer objetos si tengo hueco en
      ///en la mochila
      if(not accion_reactiva){
        if(not mochilaLlena() and NObjetos < MAXObjetos and (mapa_objetos_[y_][x_] == ZAPATILLAS or
          mapa_objetos_[y_][x_] == BIKINI or
          mapa_objetos_[y_][x_] == LLAVE or
          mapa_objetos_[y_][x_] == PIEDRA or
          mapa_objetos_[y_][x_] == ORO or
          mapa_objetos_[y_][x_] == ALGORITMO or
          mapa_objetos_[y_][x_] == MANZANA or
          mapa_objetos_[y_][x_] == OSCAR)){
            if(EN_USO_ == '-'){
              accion_reactiva = true;
              accion = actPICKUP;
              NObjetos++;
            }
            else{
              accion_reactiva = true;
              accion = actPUSH;
            }
            cout << "Cojer objetos"<<endl;
          }
        }
        //COMPORTAMIENTO DE CUARTA PRIORIDAD: Equiparme para andar.
        if(not accion_reactiva){
          if((mapa_entorno_[y_+1][x_] == arbol or
            mapa_entorno_[y_-1][x_] == arbol or
            mapa_entorno_[y_][x_+1] == arbol or
            mapa_entorno_[y_][x_-1] == arbol or
            mapa_entorno_[y_][x_] == arbol) and EN_USO_ != ZAPATILLAS
            and (MOCHILLA_[0] == ZAPATILLAS or MOCHILLA_[1] == ZAPATILLAS or
                MOCHILLA_[2] == ZAPATILLAS or MOCHILLA_[3] == ZAPATILLAS)
            and (EN_USO_ != BIKINI or (mapa_entorno_[y_][x_] != agua and
                                      mapa_entorno_[y_+1][x_] != agua and
                                      mapa_entorno_[y_][x_+1] != agua and
                                      mapa_entorno_[y_-1][x_] != agua and
                                      mapa_entorno_[y_][x_-1] != agua))
            and (EN_USO_ != LLAVE or (mapa_entorno_[y_][x_] != puerta and
                                      mapa_entorno_[y_+1][x_] != puerta and
                                      mapa_entorno_[y_][x_+1] != puerta and
                                      mapa_entorno_[y_-1][x_] != puerta and
                                      mapa_entorno_[y_][x_-1] != puerta))){
              if(EN_USO_ != '-'){
                accion = actPUSH;
              }
              else{
                accion = actPOP;
              }
              accion_reactiva = true;
          }
          if((mapa_entorno_[y_+1][x_] == agua or
            mapa_entorno_[y_-1][x_] == agua or
            mapa_entorno_[y_][x_+1] == agua or
            mapa_entorno_[y_][x_-1] == agua or
            mapa_entorno_[y_][x_] == agua) and EN_USO_ != BIKINI
            and (MOCHILLA_[0] == BIKINI or MOCHILLA_[1] == BIKINI or
                MOCHILLA_[2] == BIKINI or MOCHILLA_[3] == BIKINI)
            and (EN_USO_ != ZAPATILLAS or (mapa_entorno_[y_][x_] != arbol and
                                      mapa_entorno_[y_+1][x_] != arbol and
                                      mapa_entorno_[y_][x_+1] != arbol and
                                      mapa_entorno_[y_-1][x_] != arbol and
                                      mapa_entorno_[y_][x_-1] != arbol))
            and (EN_USO_ != LLAVE or (mapa_entorno_[y_][x_] != puerta and
                                      mapa_entorno_[y_+1][x_] != puerta and
                                      mapa_entorno_[y_][x_+1] != puerta and
                                      mapa_entorno_[y_-1][x_] != puerta and
                                      mapa_entorno_[y_][x_-1] != puerta))){
              if(EN_USO_ != '-'){
                accion = actPUSH;
              }
              else{
                accion = actPOP;
              }
              accion_reactiva = true;
          }
          if((mapa_entorno_[y_+1][x_] == puerta or
            mapa_entorno_[y_-1][x_] == puerta or
            mapa_entorno_[y_][x_+1] == puerta or
            mapa_entorno_[y_][x_-1] == puerta or
            mapa_entorno_[y_][x_] == puerta) and EN_USO_ != LLAVE
            and (MOCHILLA_[0] == LLAVE or MOCHILLA_[1] == LLAVE or
                MOCHILLA_[2] == LLAVE or MOCHILLA_[3] == LLAVE)
            and (EN_USO_ != BIKINI or (mapa_entorno_[y_][x_] != agua))
            and (EN_USO_ != ZAPATILLAS or (mapa_entorno_[y_][x_] != arbol ))){
              if(EN_USO_ != '-'){
                accion = actPUSH;
              }
              else{
                accion = actPOP;
              }
              accion_reactiva = true;
              cout << "Equiparme"<<endl;
          }
        }
        //COMPORTAMIENTO DE QUINTA PRIORIDAD. Guardar objetos que no esté usando
        /*if(not accion_reactiva and EN_USO_!= '-'){
          if(EN_USO_ != PIEDRA){
            if(EN_USO_ == ZAPATILLAS and not (mapa_entorno_[y_-1][x_] == arbol or
              mapa_entorno_[y_][x_+1] == arbol or
              mapa_entorno_[y_+1][x_] == arbol or
              mapa_entorno_[y_][x_-1] == arbol or
              mapa_entorno_[y_][x_] == arbol )){
                accion = actPUSH;
                accion_reactiva = true;
                cout << "Por tener zapatillas"<<endl;
            }
            else if(EN_USO_ == BIKINI and not (mapa_entorno_[y_+1][x_] == agua or
              mapa_entorno_[y_][x_+1] == agua or
              mapa_entorno_[y_-1][x_] == agua or
              mapa_entorno_[y_][x_-1] == agua or
              mapa_entorno_[y_][x_] != agua)) {
                accion = actPUSH;
                accion_reactiva = true;
                cout << "Por tener bikini"<<endl;
            }
            else if(EN_USO_ == LLAVE and not (mapa_entorno_[y_+1][x_] == puerta or
              mapa_entorno_[y_][x_+1] == puerta or
              mapa_entorno_[y_-1][x_] == puerta or
              mapa_entorno_[y_][x_-1] == puerta or
              mapa_entorno_[y_][x_] == puerta)){
                accion = actPUSH;
                accion_reactiva = true;
                cout <<"Por tener llaves"<<endl;
            }
            else if(EN_USO_ >= '0' and EN_USO_ <= '9'){
              accion = actPUSH;
              accion_reactiva = true;
              cout << "Por tener algo"<<endl;
            }
            cout << "Guardo objetos que no uso"<<endl;

          }
        }*/

        ////COMPORTAMIENTO DE SEXTA PRIORIDAD: Tener siempre una piedra en la mano.
        if(not accion_reactiva){
          if(EN_USO_ != PIEDRA and (MOCHILLA_[0] == PIEDRA or
            MOCHILLA_[1] == PIEDRA or
            MOCHILLA_[2] == PIEDRA or
            MOCHILLA_[3] == PIEDRA) and EN_USO_ != ZAPATILLAS and EN_USO_ != BIKINI and EN_USO_!=LLAVE and
            (SURFACE_[1] == OSO or SURFACE_[3] == OSO or SURFACE_[7] == OSO or
            (SURFACE_[1] >= 'a' and SURFACE_[1]<='d') or
            (SURFACE_[3] >= 'a' and SURFACE_[3]<='d') or
            (SURFACE_[7] >= 'a' and SURFACE_[7]<='d'))){
            if(EN_USO_!='-'){
              accion = actPUSH;
            }
            else{
              accion = actPOP;
            }
            cout << "Tener piedra"<<endl;
            accion_reactiva = true;
          }
        }
        ////COMPORTAMIENTO de septima prioridad: tirar piedra.
        if(not accion_reactiva){
          if(EN_USO_ == PIEDRA and (SURFACE_[1] == OSO or SURFACE_[3] == OSO
            or SURFACE_[7]==OSO or (SURFACE_[1] >= 'a' and SURFACE_[1] <= 'd') or
            (SURFACE_[3] >= 'a' and SURFACE_[3] <= 'd') or (SURFACE_[7] >= 'a' and SURFACE_[7] <= 'd'))){
            accion = actTHROW;
            cout << "Lanzo"<<endl;
          }
        }

        cout << ActionStr(accion) <<endl;
        cout << "MENSAJE_:"<<MENSAJE_<<endl;
        cout << "MOCHILLA_:"<<MOCHILLA_<<endl;
        cout << "EN_USO_:"<<EN_USO_<<endl;
        cout << "PUNTUACION_:"<<PUNTUACION_<<endl;


	// recuerdo la ultima accion realizada
	last_accion_ = accion;

	return accion;

}
