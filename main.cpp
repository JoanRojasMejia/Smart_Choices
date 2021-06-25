#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream> 
#include<time.h>
#include<stdlib.h>
#include<cstring> 

using namespace std;

#define maxfilas 20
#define maxcol 60

struct jugador {
  char nombre[20];
  char apellido[20];
  char correo[50];
  char alias[30];
	int juegosjugados;
  int juegosganados;
  double tiempo;
  int puntaje;
};

struct pausaTablero{
	char tableropausa[maxfilas][maxcol];
	char alias[30];
	int filas;
	int columnas;
	int puntaje;
	double tiempo;
};

//el limite de puntos para ganar es de 100

int menu();
void menu2a(char[][maxcol],int[],char []);
void cambiardif(char [][maxcol],int [],char []);
void perstablero(char [][maxcol],int [],char[]);
void adminjugs(char [][maxcol],int[],char[]);
void desEst(char [][maxcol],int[],char[]);
void statsorden();
void statsrachavict();
void statstiempo();
void statspunt();
void statscorreo();
void stats();
void mpuntemps();
void statsxplayer();
int buscarderecha(char[][maxcol],int,int,int,int,int);
int buscararriba(char[][maxcol],int,int,int,int,int);
int buscarizquierda(char[][maxcol],int,int,int,int,int);
int buscarabajo(char[][maxcol],int,int,int,int,int);
jugador cambiarJugadores(jugador,jugador ); 
void gravedadderecha(char [][maxcol],int, int,int,int,int );
void gravedadizquierda(char [][maxcol],int, int,int,int,int );
void gravedadarriba(char [][maxcol],int, int,int,int,int );
void gravedadabajo(char [][maxcol],int, int,int,int,int );
bool evaluartablero(char [][maxcol],int, int);
void sobreescribirdatos(jugador [],int);

int main() {

// Decalaracion de variables

char tablero[maxfilas][maxcol];
char tablerotemp[maxfilas][maxcol];
int opcion, config, filas, columnas;
char colores[6]={'M','R','V','A','N','B'};
int filcol[2];
char jugestadisticas[30]; //los alias tienen 30 caracteres maximos
opcion = 0;
string nombre;
int puntaje=0; //con cada grupo de esferas retiradas son 10 puntos mas
int movcolumna, movfila,direccion,randomnumero;
bool cambio=false;
bool continuarjuego=true;
jugador jugadoresLect[100];
jugador t;
int tam = 0, tamx = 0, tamtablero = 0;
bool aliasesta=false;
int pausa;
pausaTablero tablerospausa[100];
pausaTablero tableropausaLect[100];
int canttableros=0;
pausaTablero a;
int reanudar;
int cantidaddejuegosjugados=0;
bool haberganado=false, archivotemp = false;
double segundos,segundospausa;
int puntajepausa=0;
int cantjuegosganados = 0;
// Decalaracion de variables

	do{
    
		cout<<endl;
		opcion = menu();
		ifstream archivoTableroLect;
    
		switch(opcion){
      
			case 1:

				cout<<endl<<"--------------- Bienvenido a Smart Choices ---------------"<<endl;
        
				cout<<endl<<"Recuerde configurar el tablero con el que desea jugar."<<endl;
        
				//el bool de cambio es para asegurarnos de que el jugador haya configurado el tablero antes de iniciar el juego 
        
				cout<<endl<<"Digite su alias para verficar si tiene un juego pausado: "; 
				cin.ignore();
				cin.getline(jugestadisticas, 20);
				
				archivoTableroLect.open("tablero.dat", ios::binary);
				
				if(!archivoTableroLect){
						cout<<endl<<"No se ha guardado ningun tablero"<<endl;
					}
				else{
					do{
						archivoTableroLect.read(reinterpret_cast<char *>(&a), sizeof(pausaTablero));
						if(!archivoTableroLect){
							tableropausaLect[tamtablero] = a;
							tamtablero++;
						}
					}while(archivoTableroLect.eof()==false);

					archivoTableroLect.close();

				}
				
				for (int i = 0; i < tamtablero; i++){
					if(strcmp(jugestadisticas, tableropausaLect[i].alias) == 0){
						cambio=true;
					}
				}
  
          if(cambio==true){
						
						ifstream archivoJugadoresLect;
						archivoJugadoresLect.open("jugadores.dat", ios::binary);
    
						if(!archivoJugadoresLect){
							cout<<"El archivo no existe."<<endl;
						}
						else{
							do{
								archivoJugadoresLect.read(reinterpret_cast<char *> (&t) , sizeof(jugador));
								if(!archivoJugadoresLect.eof()){
									jugadoresLect[tam]= t;
									tam++;
                  
								}
							}while(archivoJugadoresLect.eof() == false);

							archivoJugadoresLect.close();

						}

						for(int i = 0; i < tamtablero; i++){
					
							if(strcmp(jugestadisticas, tableropausaLect[i].alias)== 0){// tablero.dat
                
								cout<<endl<<"Usted tiene un juego que fue pausado, digite: "<<endl;
								cout<<"1. Si quiere reanudar su juego"<<endl;
								cout<<"0. Comenzar un nuevo juego"<<endl;
								cout<<"¿Cual opcion desea?: ";
								cin>>reanudar;
                
								if(reanudar==1){
                  
									puntajepausa = tableropausaLect[i].puntaje;
                  segundospausa = tableropausaLect[i].tiempo;
									filcol[0]=tableropausaLect[i].filas;
									filcol[1]=tableropausaLect[i].columnas;
									
									for (int j=0;j<tableropausaLect[i].filas;j++){
										for(int k=0;k<tableropausaLect[i].columnas;k++){
											tablero[j][k] = tableropausaLect[i].tableropausa[j][k];
										}
									}
								}
								else{
									cambio=false;
								}
							} 
						}

						for(int i = 0; i < tam; i++){
							
							if((strcmp(jugestadisticas, jugadoresLect[i].alias)==0)){// jugadores.dat
								
                time_t inicio,fin;
                time(&inicio);
								aliasesta=true;
								filas=filcol[0];
								columnas=filcol[1];
							
								cout<<endl<<"Este seria el tablero para el juego"<<endl<<endl;
						
								for(int i=0;i<filas;i++){
									for(int j=0;j<columnas;j++){
										cout<<tablero[i][j]<<" ";
									}
									cout<<endl;
									continuarjuego=true;
								}

                haberganado=evaluartablero(tablero, filas, columnas);
								
								while(continuarjuego==true&&haberganado==false){
									
									haberganado=evaluartablero(tablero, filas, columnas);
                  
									if(haberganado==false){

										cout<<endl<<"Ingrese su movimiento"<<endl;
										cout<<"Fila: "; cin>>movfila;
										cout<<"Columna: "; cin>>movcolumna;
										cout<<endl;
										cout<<"Direcciones: \n1)Hacia arriba. \n2)Hacia la derecha. \n3)Hacia abajo. \n4)Hacia la izquierda."<<endl<<endl;
										cout<<"Introduzca el numero de direccion a buscar: ";
										cin>>direccion;

										cout<<endl<<"------------------------ Nueva Jugada ------------------------"<<endl;

										if(direccion==1){
											puntaje = buscararriba(tablero,filas,columnas,movfila,movcolumna,puntaje);
										}

										else if(direccion==2){
											puntaje = buscarderecha(tablero,filas,columnas,movfila,movcolumna,puntaje);
										}

										else if(direccion==3){
											puntaje = buscarabajo(tablero,filas,columnas,movfila,movcolumna,puntaje);
										}

										else if(direccion==4){
											puntaje = buscarizquierda(tablero,filas,columnas,movfila,movcolumna,puntaje);
										}

										for(int i=0;i<filas;i++){
											for(int j=0;j<columnas;j++){
												cout<<tablero[i][j]<<" ";
											}
											cout<<endl;
										}
										
										cout<<endl<<"Opciones de movimiento, digite:"<<endl;
										cout<<"1. Hacer otro movimiento."<<endl;
										cout<<"0. No hacer mas movimientos."<<endl;
										cout<<"¿Cual opcion desea?: ";
										cin>>continuarjuego;
										
                  }
									else {
										cout<<endl<<" --------------------"<<endl;
										cout<<"|"<<"                    |"<<endl;
										cout<<"|"<<"                    |"<<endl;
										cout<<"|"<<"   ¡¡¡GANASTE!!!    |"<<endl;
										cout<<"|"<<"     ᕙ( ͡❛ ᴥ ͡❛)ᕗ     |"<<endl;
										cout<<"|"<<"                    |"<<endl;
										cout<<"|"<<"                    |"<<endl;
										cout<<" --------------------"<<endl;
										
										
                    //posicionar el puntero  
										cantidaddejuegosjugados++;
										cantjuegosganados++;
                    
										time(&fin);
                    segundos = difftime(fin, inicio)+segundospausa;
                    puntaje = puntaje + puntajepausa;

										jugadoresLect[i].juegosjugados = jugadoresLect[i].juegosjugados+cantidaddejuegosjugados;
                    
										jugadoresLect[i].juegosganados=jugadoresLect[i].juegosganados+cantjuegosganados;

										jugadoresLect[i].tiempo = jugadoresLect[i].tiempo + segundos; 
								
                    jugadoresLect[i].puntaje=jugadoresLect[i].puntaje+puntaje;
                    
										sobreescribirdatos(jugadoresLect, tam);

										opcion=4;

										cout<<endl<<endl<<"--------- Gracias por jugar Smart Choices :) ---------"<<endl<<endl;
										cout<<"Juego realizado por:"<<endl<<endl;
										cout<<"➳  Juan Manuel Duran Rueda."<<endl;
										cout<<"➳  Andres Felipe Cenatanaro Tibaquira."<<endl;
										cout<<"➳  Joan Sebastian Rojas Mejia."<<endl<<endl;
										cout<<"©Javeriana - 2021";
                    
                  }
									
									if(continuarjuego==0){
										
										cout<<endl<<"Opciones de pausa, digite: "<<endl;
										cout<<"-1. Dejar el juego en pausa."<<endl;
										cout<<"0. Borrar el juego actual."<<endl;
										cout<<"¿Cual opcion desea?: ";
										cin>>pausa;

										if(pausa==-1){
											// archivo tablero para escribir
											ofstream archivoTableroTemp("temporal.dat", ios::binary);

											for (int i = 0; i < tamtablero; i++){
												if(strcmp(jugestadisticas, tableropausaLect[i].alias) == 0){
													cout<<endl<<"Un juego ya estaba en pausa, sobreescribira los datos."<<endl;
												}
												else{
													archivoTableroTemp.write(reinterpret_cast<const char *>(&tableropausaLect[i]), sizeof(pausaTablero));
												}
											}

											archivoTableroTemp.close();
											remove("tablero.dat");
											rename("temporal.dat","tablero.dat");

										}

										if(pausa==-1){
											
											time(&fin);
                      segundos = difftime(fin, inicio)+segundospausa;
                      puntaje = puntaje + puntajepausa;
											
											ofstream archivoTablero;
											archivoTablero.open("tablero.dat", ios::binary | ios::app);

											for(int i=0;i<filas;i++){
												for(int j=0;j<columnas;j++){
													tablerotemp[i][j] = tablero[i][j];
												}
											}

											for(int i=0;i<filas;i++){
												for(int j=0;j<columnas;j++){
													tablerospausa[canttableros].tableropausa[i][j] = tablerotemp[i][j];
												}
											}
											
											strcpy(tablerospausa[canttableros].alias, jugestadisticas);
											tablerospausa[canttableros].filas = filas;
											tablerospausa[canttableros].columnas = columnas;
											tablerospausa[canttableros].puntaje = puntaje;
                      tablerospausa[canttableros].tiempo = segundos;

											archivoTablero.write(reinterpret_cast<const char *>(&tablerospausa[canttableros]), sizeof(pausaTablero));

											canttableros++;

											cout<<endl<<"Su tiempo fue de: "<<segundos<<" segundos."<<endl<<"El puntaje obtenido para esta sesion fue de: "<<puntaje<<" puntos.";
                      
											cambio=false;
											opcion=4;

											cout<<endl<<endl<<"--------- Gracias por jugar Smart Choices :) ---------"<<endl<<endl;
											cout<<"Juego realizado por:"<<endl<<endl;
            					cout<<"➳  Juan Manuel Duran Rueda."<<endl;
                      cout<<"➳  Andres Felipe Cenatanaro Tibaquira."<<endl;
                      cout<<"➳  Joan Sebastian Rojas Mejia."<<endl<<endl;
                      cout<<"©Javeriana - 2021";
										}
										else if(pausa==0 && haberganado==false){
											time(&fin);
											segundos = difftime(fin, inicio)+segundospausa;
                      puntaje = puntaje + puntajepausa;
											cout<<endl<<"Su tiempo fue de: "<<segundos<<" segundos."<<endl;
											cout<<"su puntaje fue de: "<<puntaje<<endl;
                      
											cantidaddejuegosjugados++;
                      
											cambio=false;
                      
											jugadoresLect[i].juegosjugados = jugadoresLect[i].juegosjugados+cantidaddejuegosjugados;
									
											sobreescribirdatos(jugadoresLect, tam);

											opcion=4;

											cout<<endl<<endl<<"--------- Gracias por jugar Smart Choices :) ---------"<<endl<<endl;
											cout<<"Juego realizado por:"<<endl<<endl;
            					cout<<"➳  Juan Manuel Duran Rueda."<<endl;
                      cout<<"➳  Andres Felipe Cenatanaro Tibaquira."<<endl;
                      cout<<"➳  Joan Sebastian Rojas Mejia."<<endl<<endl;
                      cout<<"©Javeriana - 2021";
                  	}
              		}
								}
        			}
						}
          	//preguntar acerca de por que esta pasando esto solamente cuando se ingresa el alias incorrecto al final;
						if(aliasesta==false){
							cout<<endl<<"El alias no se encuentra registrado"<<endl;
						}
					} 
					else if(cambio==false){
          cout<<endl<<"Recuerde configurar su tablero antes de iniciar."<<endl;
        }
        
			break;
				
			case 2:
				menu2a(tablero,filcol,colores);
        cambio=true;
			break;

			case 3:
				stats();
			break;

      case 4:
      	cout<<endl<<"--------- Gracias por jugar Smart Choices :) ---------"<<endl<<endl;
				cout<<"Juego realizado por:"<<endl<<endl;
				cout<<"➳  Juan Manuel Duran Rueda."<<endl;
				cout<<"➳  Andres Felipe Cenatanaro Tibaquira."<<endl;
				cout<<"➳  Joan Sebastian Rojas Mejia."<<endl<<endl;
				cout<<"©Javeriana - 2021";
      break;

			default:
				cout<<endl<<"Esta opcion no esta disponible :(";
			
		}
    
	}while(opcion!=4);
    
}
  
int menu(){
  
	int opc;
  
  cout<<endl<<"------------------- Menu ------------------"<<endl;
  
	cout<<endl<<"Recuerde configurar el tablero con el que desea jugar :)"<<endl<<endl;

  cout<<"1. Jugar"<<endl;
  cout<<"2. Configuración"<<endl;
  cout<<"3. Estadisticas"<<endl;
  cout<<"4. Salir"<<endl;
  cout<<"Ingrese la opción que desea utilizar: "; 
	cin>>opc;

	return opc;

}

//-------------------- Opciones del menu configuracion --------------------

void menu2a(char tablero[][maxcol],int filcol[],char colores[]){
  
	int opc;
	bool cambio;

 	cout<<endl<<"------------------ Configuración --------------"<<endl<<endl;
  cout<<"2.1 Cambiar nivel de dificultad"<<endl;
  cout<<"2.2 Perzonalizar tablero  "<<endl;
  cout<<"2.3 Administrar jugadores"<<endl;
	cout<<"2.4 Volver"<<endl;
  cout<<"Ingrese la opción que desea utilizar: "; cin>>opc;
	
  if(opc==1){
  	cambiardif(tablero,filcol,colores);
  }
  else if(opc==2){
    perstablero(tablero,filcol,colores);
  }
  else if(opc==3){
    adminjugs(tablero,filcol,colores);
  }
	else if(opc==4){
    menu();
  }

}

void cambiardif(char tablero[][maxcol],int filcol[],char colores[]){
 
  int opc;
	int randomnum;
	
  cout<<endl<<"---------------- Niveles de dificultad ---------------- "<<endl<<endl;
  cout<<"2.1.1 Principiante (tablero de 9x9)"<<endl;
  cout<<"2.1.2 Intermedio (tablero de 16x16)"<<endl;
  cout<<"2.1.3 Avanzado (tablero de 16x30)"<<endl;
	cout<<"2.1.4 Volver"<<endl;
  
	cout<<"Ingrese el ultimo valor decimal para la opcion que desea: ";
  cin>>opc;
  
	srand((unsigned) time(0));

	if(opc==1){
    
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				randomnum=rand()%6;
				tablero[i][j]=colores[randomnum];
			}
    }
    
		cout<<endl<<"----------- Tablero Principiante -----------"<<endl<<endl;
    
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				cout<<tablero[i][j]<<" ";
			}
			cout<<endl;
    }

  	filcol[0]=9;
  	filcol[1]=9;
   	//tablero[9][9];
  }

  else if(opc==2){

    for(int i=0;i<16;i++){
			for(int j=0;j<16;j++){
				randomnum=rand()%6;
				tablero[i][j]=colores[randomnum];
			}
    }
		
		cout<<endl<<"----------- Tablero Intermedio -----------"<<endl<<endl;
    
		for(int i=0;i<16;i++){
			for(int j=0;j<16;j++){
				cout<<tablero[i][j]<<" ";
			}
			cout<<endl;
    }

		filcol[0]=16;
  	filcol[1]=16;
  	//tablero[16][16];
  }

  else if(opc==3){

    for(int i=0;i<16;i++){
			for(int j=0;j<30;j++){
				randomnum=rand()%6;
				tablero[i][j]=colores[randomnum];
      }
    }

		cout<<endl<<"----------- Tablero Avanzado -----------"<<endl<<endl;
    
		for(int i=0;i<16;i++){
			for(int j=0;j<30;j++){
				cout<<tablero[i][j]<<" ";
			}
			cout<<endl;
    }
  	
  	filcol[0]=16;
  	filcol[1]=30;
		//tablero[16][30];
	}
 
	else if(opc==4){
		menu2a(tablero,filcol,colores);
	}

}

void perstablero(char tablero[][maxcol],int filcol[],char colores[]){
  
	int filas,columnas,randomnum;

  cout<<endl<<"-------------------- Personalizar Tablero --------------------"<<endl<<endl;
  
	cout<<"¿Cuantas filas quiere en su tablero?: "; cin>>filas;
  cout<<"¿Cuantas columnas quiere en su tablero?: "; cin>>columnas;
  
	srand((unsigned) time(0));

	if(filas<21 && columnas<61){
		
		for(int i=0;i<filas;i++){
			for(int j=0;j<columnas;j++){
				randomnum=rand()%6;
				tablero[i][j]=colores[randomnum];
			}
		}

		cout<<endl<<"----------- Tablero Personalizado -----------"<<endl<<endl;

		for(int i=0;i<filas;i++){
			for(int j=0;j<columnas;j++){
				cout<<tablero[i][j]<<" ";
		}
		cout<<endl;
		}
  }
	else if (filas>20||columnas>60){
    cout<<endl<<"No se puede generar el tablero personalizado."<<endl<<endl;
		cout<<"Maximo de filas permitidas en el juego: 20."<<endl;
		cout<<"Maximo de columnas permitidas en el juego: 60."<<endl;
  }

  filcol[0]=filas;
  filcol[1]=columnas;
	//tablero[filas][columnas];

}

void adminjugs(char tablero [][maxcol],int filcol[],char colores[]){
	
  int opc;
  int cantjugadores = 0;
	bool continuar = true;
	jugador jugadores[100];
	jugador jugadoresLect[100];
	jugador t;
	int tam = 0;
  int tamanyo = sizeof(jugador);

  cout<<endl<<"------------------- Administrar jugadores ------------------"<<endl<<endl;
  cout<<"2.3.1 Crear un jugador"<<endl;
  cout<<"2.3.2 Eliminar jugador"<<endl;
  cout<<"2.3.3 Despliegue de estadisticas"<<endl;
	cout<<"2.3.4 Volver"<<endl;

  cout<<"Ingrese la opcion que desea utilizar: ";
	cin>>opc;
  
  if(opc==1){
		
		cout<<endl<<"------------------- Crear Jugador ------------------"<<endl<<endl;

		ofstream archivoJugadores;
		ifstream archivoJugadoresLect;
		archivoJugadoresLect.open("jugadores.dat", ios::binary);
		
		if(!archivoJugadoresLect){
			cout<<"El archivo no existe"<<endl<<endl;
		}
		else{
			
			do{
				archivoJugadoresLect.read(reinterpret_cast<char *> (&t) , sizeof(jugador));
				if(!archivoJugadoresLect.eof()){
					jugadoresLect[tam]= t;
					tam++;
				}
			}while(archivoJugadoresLect.eof() == false);
    
			archivoJugadoresLect.close();  
		}

		archivoJugadores.open("jugadores.dat", ios::binary | ios::app);

		cout<<"¿Cual es su nombre?: ";
		cin.ignore();
		cin.getline(jugadores[cantjugadores].nombre, 20);

		for(int i=0;i<tam;i++){
			if(strcmp(jugadores[cantjugadores].nombre,jugadoresLect[i].nombre) == 0){
				cout<<endl<<"No se pueden crear dos jugadores con el mismo nombre, escoja otro nombre";
				continuar = false;
			}
		}
		
    if(continuar==true){
			cout<<"¿Cual es su apellido?: ";
			cin>>jugadores[cantjugadores].apellido;

			cout<<"¿Cual es su alias?: ";
			cin>>jugadores[cantjugadores].alias;

			cout<<"¿Cual es su correo?: ";
			cin>>jugadores[cantjugadores].correo;

			jugadores[cantjugadores].juegosjugados = 0;
			jugadores[cantjugadores].juegosganados = 0;
			jugadores[cantjugadores].tiempo = 0;
			jugadores[cantjugadores].puntaje = 0;

			archivoJugadores.write(reinterpret_cast<const char *>(&jugadores[cantjugadores]), sizeof(jugador));
			
			cantjugadores++;

    }

		cout<<endl<<"El jugador ha sido creado exitosamente.";
		
		archivoJugadores.close();
  }
	
	else if(opc==2){

		int tamanyo; //pueden haber 2 aliasm, entonces se verifica el tamaño de cada alias
    int tamanyo2;
		string jugeliminado;
		//char jugeliminadochar[20];
		
		cout<<endl<<"------------------- Eliminar Jugador ------------------"<<endl<<endl;
    
    ifstream archivoJugadoresLect;
		archivoJugadoresLect.open("jugadores.dat", ios::binary);
    
		if(!archivoJugadoresLect){
			cout<<"El archivo no existe"<<endl;
		}
		else{
			
			do{
				archivoJugadoresLect.read(reinterpret_cast<char *> (&t) , sizeof(jugador));
				if(!archivoJugadoresLect.eof()){
					jugadoresLect[tam]= t;
					tam++;
				}
			}while(archivoJugadoresLect.eof() == false);
     
			for(int i = 0; i < tam; i++){
				cout<<"------ Jugador numero "<<i<<" -------"<<endl<<endl;
				cout<<"Nombre: "<<jugadoresLect[i].nombre<<endl;
				cout<<"Apellido: "<<jugadoresLect[i].apellido<<endl;
				cout<<"Alias: "<<jugadoresLect[i].alias<<endl;
				cout<<"Correo: "<<jugadoresLect[i].correo<<endl;
        cout<<endl;
			}
    
			archivoJugadoresLect.close();  
		}

		cout<<endl<<"Indique el alias del jugador a eliminar: ";
		cin>>jugeliminado;
		
    tamanyo = jugeliminado.size();// .size() cuenta el tamaño
    bool encontrado=false;
		
		ofstream archivoTemp("temp.dat", ios::binary);

		for(int i=0;i<tam;i++){
      
			tamanyo2 = strlen(jugadoresLect[i].alias);
      
      if(jugeliminado == jugadoresLect[i].alias&&tamanyo==tamanyo2){
				cout<<endl<<"El jugador ha sido eliminado permanentemente del juego."<<endl;
				cout<<"El jugador tenia como nombre registrado: "<<jugadoresLect[i].nombre<<".";
				encontrado=true;
      }
			else{
				archivoTemp.write(reinterpret_cast<const char *>(&jugadoresLect[i]), sizeof(jugador));
			}

    }

		archivoTemp.close();
    remove("jugadores.dat");
    rename("temp.dat","jugadores.dat");

		if(encontrado==false){
			cout<<"El alias: "<<jugeliminado<<", no se encuentra registrado."<<endl;
    }

	}

  else if(opc==3){
		desEst(tablero,filcol,colores);
	}
	else if(opc==4){
		menu2a(tablero,filcol,colores);
	}
  
}

void desEst(char tablero [][maxcol],int filcol[],char colores[]){
	  
	int opc;
	
	cout<<endl<<"------------------- Estadisticas jugadores ------------------"<<endl<<endl;
	cout<<"2.3.3.1 En orden por cantidad de juegos jugados."<<endl;
	cout<<"2.3.3.2 En orden por cantidad de juegos ganados."<<endl;
	cout<<"2.3.3.3 En orden por tiempos."<<endl;
	cout<<"2.3.3.4 En orden por puntajes."<<endl;
	cout<<"2.3.3.5 En orden por correo."<<endl;
	cout<<"2.3.3.6 Volver"<<endl;

	cout<<"Ingrese la opcion que desea utilizar: "; 
	cin>>opc;

	if(opc==1){
		statsorden();
	}
	else if(opc==2){
		statsrachavict();
	}
	else if(opc==3){
		statstiempo();
	}
	else if(opc==4){
		statspunt();
	}
	else if(opc==5){
		statscorreo();
	}
	else if(opc==6){
		adminjugs(tablero,filcol,colores);
	}

}

void statsorden(){
  
	cout<<endl<<"-------- Jugadores Ordenados por Cantidad de Juegos Jugados --------"<<endl<<endl;

	jugador jugadoresLect[100];
	jugador t;
	int tam = 0;
	string jugeliminado;

	ifstream archivoJugadoresLect;
	archivoJugadoresLect.open("jugadores.dat", ios::binary);
  
	if(!archivoJugadoresLect){
		cout<<"El archivo no existe"<<endl;
	}
	else{
		
		do{
			archivoJugadoresLect.read(reinterpret_cast<char *> (&t) , sizeof(jugador));
			if(!archivoJugadoresLect.eof()){
				jugadoresLect[tam]= t;
				tam++;
			}
		}while(archivoJugadoresLect.eof() == false);
	
		archivoJugadoresLect.close();  
	}

	for(int i = 0; i < tam; i++){
		for(int j=i+1; j<tam; j++){
     if(jugadoresLect[i].juegosjugados < jugadoresLect[j].juegosjugados){
				jugador temp;
				temp = cambiarJugadores(temp, jugadoresLect[i]);
				jugadoresLect[i] = cambiarJugadores(jugadoresLect[i], jugadoresLect[j]);
				jugadoresLect[j] = cambiarJugadores(jugadoresLect[j], temp);
		 } 
    }
	}

	for(int i = 0; i < tam; i++){
		cout<<endl<<"------ Jugador numero "<<i<<" -------"<<endl<<endl;
		cout<<"Nombre: "<<jugadoresLect[i].nombre<<endl;
		cout<<"Apellido: "<<jugadoresLect[i].apellido<<endl;
		cout<<"Alias: "<<jugadoresLect[i].alias<<endl;
		cout<<"Correo: "<<jugadoresLect[i].correo<<endl;
		cout<<"Cantidad de juegos: "<<jugadoresLect[i].juegosjugados<<" juegos jugados."<<endl;
		cout<<"Cantidad de juegos ganados: "<<jugadoresLect[i].juegosganados<<" juegos."<<endl;
		cout<<"Tiempo Jugado: "<<jugadoresLect[i].tiempo<<" segundos."<<endl;
		cout<<"Puntaje total obtenido: "<<jugadoresLect[i].puntaje<<" puntos."<<endl;
		cout<<endl;
	}

}

void statsrachavict(){
  
	cout<<endl<<"-------- Jugadores Ordenados por Cantidad de juegos ganados --------"<<endl<<endl;

	jugador jugadoresLect[100];
	jugador t;
	int tam = 0;
	string jugeliminado;

	ifstream archivoJugadoresLect;
	archivoJugadoresLect.open("jugadores.dat", ios::binary);
  
	if(!archivoJugadoresLect){
		cout<<"El archivo no existe"<<endl;
	}
	else{
		
		do{
			archivoJugadoresLect.read(reinterpret_cast<char *> (&t) , sizeof(jugador));
			if(!archivoJugadoresLect.eof()){
				jugadoresLect[tam]= t;
				tam++;
			}
		}while(archivoJugadoresLect.eof() == false);
	
		archivoJugadoresLect.close();  
	}

	for(int i = 0; i < tam; i++){
		for(int j=i+1; j<tam; j++){
     if(jugadoresLect[i].juegosganados < jugadoresLect[j].juegosganados){
				jugador temp;
				temp = cambiarJugadores(temp, jugadoresLect[i]);
				jugadoresLect[i] = cambiarJugadores(jugadoresLect[i], jugadoresLect[j]);
				jugadoresLect[j] = cambiarJugadores(jugadoresLect[j], temp);
		 } 
    }
	}

	for(int i = 0; i < tam; i++){
		cout<<endl<<"------ Jugador numero "<<i<<" -------"<<endl<<endl;
		cout<<"Nombre: "<<jugadoresLect[i].nombre<<endl;
		cout<<"Apellido: "<<jugadoresLect[i].apellido<<endl;
		cout<<"Alias: "<<jugadoresLect[i].alias<<endl;
		cout<<"Correo: "<<jugadoresLect[i].correo<<endl;
		cout<<"Cantidad de juegos: "<<jugadoresLect[i].juegosjugados<<" juegos jugados."<<endl;
		cout<<"Cantidad de juegos ganados: "<<jugadoresLect[i].juegosganados<<" juegos."<<endl;
		cout<<"Tiempo Jugado: "<<jugadoresLect[i].tiempo<<" segundos."<<endl;
		cout<<"Puntaje total obtenido: "<<jugadoresLect[i].puntaje<<" puntos."<<endl;
		cout<<endl;
	}


}

void statstiempo(){
	
	cout<<endl<<"-------- Jugadores Ordenados por los datos de tiempos registrados --------"<<endl<<endl;

	jugador jugadoresLect[100];
	jugador t;
	int tam = 0;
	string jugeliminado;

	ifstream archivoJugadoresLect;
	archivoJugadoresLect.open("jugadores.dat", ios::binary);
  
	if(!archivoJugadoresLect){
		cout<<"El archivo no existe"<<endl;
	}
	else{
		
		do{
			archivoJugadoresLect.read(reinterpret_cast<char *> (&t) , sizeof(jugador));
			if(!archivoJugadoresLect.eof()){
				jugadoresLect[tam]= t;
				tam++;
			}
		}while(archivoJugadoresLect.eof() == false);
	
		archivoJugadoresLect.close();  
	}

	for(int i = 0; i < tam; i++){
		for(int j=i+1; j<tam; j++){
     if(jugadoresLect[i].tiempo < jugadoresLect[j].tiempo){
				jugador temp;
				temp = cambiarJugadores(temp, jugadoresLect[i]);
				jugadoresLect[i] = cambiarJugadores(jugadoresLect[i], jugadoresLect[j]);
				jugadoresLect[j] = cambiarJugadores(jugadoresLect[j], temp);
		 } 
    }
	}

	for(int i = 0; i < tam; i++){
		cout<<endl<<"------ Jugador numero "<<i<<" -------"<<endl<<endl;
		cout<<"Nombre: "<<jugadoresLect[i].nombre<<endl;
		cout<<"Apellido: "<<jugadoresLect[i].apellido<<endl;
		cout<<"Alias: "<<jugadoresLect[i].alias<<endl;
		cout<<"Correo: "<<jugadoresLect[i].correo<<endl;
		cout<<"Cantidad de juegos: "<<jugadoresLect[i].juegosjugados<<" juegos jugados."<<endl;
		cout<<"Cantidad de juegos ganados: "<<jugadoresLect[i].juegosganados<<" juegos."<<endl;
		cout<<"Tiempo Jugado: "<<jugadoresLect[i].tiempo<<" segundos."<<endl;
		cout<<"Puntaje total obtenido: "<<jugadoresLect[i].puntaje<<" puntos."<<endl;
		cout<<endl;
	}

}

void statspunt(){

	cout<<endl<<"-------- Jugadores Ordenados por puntajes registrados de mayor a menor --------"<<endl<<endl;

	jugador jugadoresLect[100];
	jugador t;
	int tam = 0;
	string jugeliminado;

	ifstream archivoJugadoresLect;
	archivoJugadoresLect.open("jugadores.dat", ios::binary);
  
	if(!archivoJugadoresLect){
		cout<<"El archivo no existe"<<endl;
	}
	else{
		
		do{
			archivoJugadoresLect.read(reinterpret_cast<char *> (&t) , sizeof(jugador));
			if(!archivoJugadoresLect.eof()){
				jugadoresLect[tam]= t;
				tam++;
			}
		}while(archivoJugadoresLect.eof() == false);
	
		archivoJugadoresLect.close();  
	}

	for(int i = 0; i < tam; i++){
		for(int j=i+1; j<tam; j++){
     if(jugadoresLect[i].puntaje < jugadoresLect[j].puntaje){
				jugador temp;
				temp = cambiarJugadores(temp, jugadoresLect[i]);
				jugadoresLect[i] = cambiarJugadores(jugadoresLect[i], jugadoresLect[j]);
				jugadoresLect[j] = cambiarJugadores(jugadoresLect[j], temp);
		 } 
    }
	}

	for(int i = 0; i < tam; i++){
		cout<<endl<<"------ Jugador numero "<<i<<" -------"<<endl<<endl;
		cout<<"Nombre: "<<jugadoresLect[i].nombre<<endl;
		cout<<"Apellido: "<<jugadoresLect[i].apellido<<endl;
		cout<<"Alias: "<<jugadoresLect[i].alias<<endl;
		cout<<"Correo: "<<jugadoresLect[i].correo<<endl;
		cout<<"Cantidad de juegos: "<<jugadoresLect[i].juegosjugados<<" juegos jugados."<<endl;
		cout<<"Cantidad de juegos ganados: "<<jugadoresLect[i].juegosganados<<" juegos."<<endl;
		cout<<"Tiempo Jugado: "<<jugadoresLect[i].tiempo<<" segundos."<<endl;
		cout<<"Puntaje total obtenido: "<<jugadoresLect[i].puntaje<<" puntos."<<endl;
		cout<<endl;
	}

}

void statscorreo(){
 	
	jugador jugadoresLect[100];
	jugador t;
	int tam = 0;

	cout<<endl<<"-------- Jugadores Ordenados por Correo --------"<<endl<<endl;

	ifstream archivoJugadoresLect;
	archivoJugadoresLect.open("jugadores.dat", ios::binary);
	
	if(!archivoJugadoresLect){
		cout<<"El archivo no existe"<<endl;
	}
	else{
		
		do{
			archivoJugadoresLect.read(reinterpret_cast<char *> (&t) , sizeof(jugador));
			if(!archivoJugadoresLect.eof()){
				jugadoresLect[tam]= t;
				tam++;
			}
		}while(archivoJugadoresLect.eof() == false);
  
	}

	//ordenar los arreglos

	for(int i=0; i<tam; i++){
		for(int j=0; j<strlen(jugadoresLect[i].correo); j++){
			jugadoresLect[i].correo[j] = tolower(jugadoresLect[i].correo[j]);
		}
	}

	for(int i=0; i<tam;i++){
	  for(int j=i+1;j<tam;j++){
	    if(strcmp(jugadoresLect[i].correo,jugadoresLect[j].correo) > 0){
				jugador temp;
				temp = cambiarJugadores(temp, jugadoresLect[i]);
				jugadoresLect[i] = cambiarJugadores(jugadoresLect[i], jugadoresLect[j]);
				jugadoresLect[j] = cambiarJugadores(jugadoresLect[j], temp);
			}
	  }
	}
	
	for(int i = 0; i < tam; i++){
		cout<<"------ Jugador numero "<<i<<" -------"<<endl<<endl;
		cout<<"Nombre: "<<jugadoresLect[i].nombre<<endl;
		cout<<"Apellido: "<<jugadoresLect[i].apellido<<endl;
		cout<<"Alias: "<<jugadoresLect[i].alias<<endl;
		cout<<"Correo: "<<jugadoresLect[i].correo<<endl<<endl;
	}
}

//-------------------- Opciones del menu configuracion --------------------

//-------------------- Opciones del menu estadisticas --------------------

void stats(){

  int opc;

  cout<<endl<<"------------------- Estadisticas ------------------"<<endl<<endl;
  cout<<"3.1 Mejores puntajes y tiempos"<<endl;
  cout<<"3.2 Estadisticas por jugador "<<endl;
	cout<<"3.3 Volver "<<endl;
  
	cout<<"Ingrese la opción que desea utilizar: ";
  cin>>opc;

  if(opc==1){
    mpuntemps();
  }
  else if(opc==2){
 		statsxplayer();
  }
	else if(opc==3){
 		menu();
  }

}

void mpuntemps(){
  
	cout<<endl<<"-------- Mejores tiempos y puntajes registrados--------"<<endl<<endl;

	jugador jugadoresLect[100];
	jugador t;
	int tam = 0;
	string jugeliminado;

	ifstream archivoJugadoresLect;
	archivoJugadoresLect.open("jugadores.dat", ios::binary);
  
	if(!archivoJugadoresLect){
		cout<<"El archivo no existe"<<endl;
	}
	else{
		
		do{
			archivoJugadoresLect.read(reinterpret_cast<char *> (&t) , sizeof(jugador));
			if(!archivoJugadoresLect.eof()){
				jugadoresLect[tam]= t;
				tam++;
			}
		}while(archivoJugadoresLect.eof() == false);
	
		archivoJugadoresLect.close();  
	}

	for(int i = 0; i < tam; i++){
		for(int j=i+1; j<tam; j++){
     if(jugadoresLect[i].puntaje < jugadoresLect[j].puntaje && jugadoresLect[i].tiempo < jugadoresLect[j].tiempo){
				jugador temp;
				temp = cambiarJugadores(temp, jugadoresLect[i]);
				jugadoresLect[i] = cambiarJugadores(jugadoresLect[i], jugadoresLect[j]);
				jugadoresLect[j] = cambiarJugadores(jugadoresLect[j], temp);
		 } 
    }
	}

	for(int i = 0; i < 5; i++){
		
		cout<<endl<<"------ Jugador numero "<<i<<" -------"<<endl<<endl;
		cout<<"Nombre: "<<jugadoresLect[i].nombre<<endl;
		cout<<"Apellido: "<<jugadoresLect[i].apellido<<endl;
		cout<<"Alias: "<<jugadoresLect[i].alias<<endl;
		cout<<"Correo: "<<jugadoresLect[i].correo<<endl;
		cout<<"Cantidad de juegos: "<<jugadoresLect[i].juegosjugados<<" juegos jugados."<<endl;
		cout<<"Cantidad de juegos ganados: "<<jugadoresLect[i].juegosganados<<" juegos."<<endl;
		cout<<"Tiempo Jugado: "<<jugadoresLect[i].tiempo<<" segundos."<<endl;
		cout<<"Puntaje total obtenido: "<<jugadoresLect[i].puntaje<<" puntos."<<endl;
		cout<<endl;

	}

  
}

void statsxplayer(){
  
	cout<<endl<<"------------------- Estadisticas por Jugador ------------------"<<endl;

	jugador jugadoresLect[100];
	jugador t;
	int tam = 0;
	string jugeliminado;

	ifstream archivoJugadoresLect;
	archivoJugadoresLect.open("jugadores.dat", ios::binary);
  
	if(!archivoJugadoresLect){
		cout<<"El archivo no existe"<<endl;
	}
	else{
		
		do{
			archivoJugadoresLect.read(reinterpret_cast<char *> (&t) , sizeof(jugador));
			if(!archivoJugadoresLect.eof()){
				jugadoresLect[tam]= t;
				tam++;
			}
		}while(archivoJugadoresLect.eof() == false);
	
		archivoJugadoresLect.close();  
	}

	cout<<endl<<"Indique el alias para mostrar las estadisticas: ";
	cin>>jugeliminado;

	for(int i = 0; i < tam; i++){
		
		if(jugeliminado == jugadoresLect[i].alias){
			cout<<endl<<"------ Jugador numero "<<i<<" -------"<<endl<<endl;
			cout<<"Nombre: "<<jugadoresLect[i].nombre<<endl;
			cout<<"Apellido: "<<jugadoresLect[i].apellido<<endl;
			cout<<"Alias: "<<jugadoresLect[i].alias<<endl;
			cout<<"Correo: "<<jugadoresLect[i].correo<<endl;
			cout<<"Cantidad de juegos: "<<jugadoresLect[i].juegosjugados<<" juegos jugados."<<endl;
			cout<<"Cantidad de juegos ganados: "<<jugadoresLect[i].juegosganados<<" juegos."<<endl;
			cout<<"Tiempo Jugado: "<<jugadoresLect[i].tiempo<<" segundos."<<endl;
			cout<<"Puntaje total obtenido: "<<jugadoresLect[i].puntaje<<" puntos."<<endl;
			cout<<endl;
		}

	}
 
}

//-------------------- Opciones del menu estadisticas --------------------

//-------------------- Buscar palabras --------------------

int buscarderecha(char tablero[][maxcol],int filas,int columnas,int movfila,int movcolumna,int puntaje){
  
	int iguales;
	iguales = 0;
  int temp;
  char letra;
  
  letra=tablero[movfila][movcolumna];
	
	for (int i=0; i < columnas; i++) {
		if (tablero[movfila][movcolumna+i] == letra){
			iguales++;
		}
		else if (tablero[movfila][movcolumna+i] != letra){
			i=columnas;
		}
	}

  cout<<endl<<"Fichas eliminadas en la anterior jugada: "<<iguales<<endl<<endl;
	
	if(iguales>=2){
		for(int j=movfila;j>=0;j--){
			for(int i=0;i<iguales;i++){
				tablero[movfila][movcolumna+i] = ' ';
			}
		}
	}
  
	gravedadderecha(tablero,filas,columnas,movfila,movcolumna,iguales);

  //------------este es el go to de los puntajes--------------

	if(iguales<2){
    puntaje=puntaje+0;
  }
  
	else if(iguales==2){
    puntaje=puntaje+10;
  }
    
	else if(iguales>2){
    puntaje=puntaje+10;
		temp=iguales-2;
		for(int i=0;i<temp;i++){
			puntaje=puntaje+(puntaje*0.1);
		}
	}

	return puntaje;
}

int buscararriba(char tablero[][maxcol],int filas,int columnas,int movfila,int movcolumna,int puntaje){

	int iguales;
	iguales = 0;
  int temp;
  char letra;
  
  letra=tablero[movfila][movcolumna];
	
	for (int j=movfila;j>=0; j--) {
    
		if (tablero[j][movcolumna] == letra){
			iguales++; 
		}
   	else if (tablero[j][movcolumna] != letra){
    	j=0;
   }
	}

	cout<<endl<<"Fichas eliminadas en la anterior jugada: "<<iguales<<endl<<endl;

  if(iguales>=2){
    for(int i=0;i<iguales;i++){
      tablero[movfila-i][movcolumna] = ' ';
      //aca copia la de arriba
      //tablero[j-1][movcolumna]
    }
  }
  
  //--------puntajes----------
  gravedadarriba(tablero,filas,columnas,movfila,movcolumna,iguales); 

  if(iguales<2){
    puntaje=puntaje+0;
  }
  else if(iguales==2){
    puntaje=puntaje+10;
  }
    
	else if(iguales>2){
    puntaje=puntaje+10;
		temp=iguales-2;
		for(int i=0;i<temp;i++){
			puntaje=puntaje+(puntaje*0.1);
		}
	}

	return puntaje;
}
 
int buscarizquierda(char tablero[][maxcol],int filas,int columnas,int movfila,int movcolumna,int puntaje){

  int iguales;
	iguales = 0;
  int temp;
  char letra;
     
  letra=tablero[movfila][movcolumna];

	for (int i=movcolumna; i>=0; i--) {
		if (tablero[movfila][i] == letra){
			iguales++;
		}
    else if (tablero[movfila][i] != letra){
      i=0;
    }
	} //el contador de iguales ya esta funcionando
  cout<<endl<<"Fichas eliminadas en la anterior jugada: "<<iguales<<endl<<endl;

  if(iguales>=2){
    for(int i=0;i<iguales;i++){
      int x=movcolumna-i;
      tablero[movfila][x] = ' ';
    }//tablero[movfila-1][x]
  }

	gravedadizquierda(tablero,filas,columnas,movfila,movcolumna,iguales);

  if(iguales<2){
    puntaje=puntaje+0;
  }
  else if(iguales==2){
    puntaje=puntaje+10;
  }
    
	else if(iguales>2){
    puntaje=puntaje+10;
		temp=iguales-2;
		for(int i=0;i<temp;i++){
			puntaje=puntaje+(puntaje*0.1);
		}
	}

	return puntaje;

}

int buscarabajo(char tablero[][maxcol],int filas,int columnas,int movfila,int movcolumna,int puntaje){

	int iguales;
	iguales = 0;
  int temp;
  char letra;
  
  letra=tablero[movfila][movcolumna];

	for (int i=0; i<filas; i++) {
		if (tablero[movfila+i][movcolumna] == letra){
			iguales++;
		}
    else if(tablero[movfila+i][movcolumna] != letra){
      i=filas+1;
    }
	}
  
	cout<<endl<<"Fichas eliminadas en la anterior jugada: "<<iguales<<endl<<endl;

	if(iguales>=2){
		for(int j=0;j<iguales;j++){
			int x= movfila+j;
			tablero[x][movcolumna] = ' ';
		}
	}
  
  gravedadabajo(tablero,filas,columnas,movfila,movcolumna,iguales);

  if(iguales<2){
    puntaje=puntaje+0;
  }
  else if(iguales==2){
    puntaje=puntaje+10;
  }
    
	else if(iguales>2){
    puntaje=puntaje+10;
		temp=iguales-2;
		for(int i=0;i<temp;i++){
			puntaje=puntaje+(puntaje*0.1);
		}
	}

	return puntaje;

}

jugador cambiarJugadores(jugador a, jugador b){
	strcpy(a.nombre, b.nombre);
	strcpy(a.apellido, b.apellido);
	strcpy(a.alias, b.alias);
	strcpy(a.correo, b.correo);

	return a;
}


//-------------------- Buscar palabras --------------------

//-------------------- Gravedades de las letras --------------------

void gravedadderecha(char tablero [][maxcol],int filas, int columnas,int movfila,int movcolumna, int iguales){
	
	int x=movcolumna+iguales;
	int i=movfila;
  
	if(iguales>=2){
		for(i=movfila;i>=0;i--){
			for(int j=movcolumna;j<x;j++){
				if(tablero[i][j]==' '){
					tablero[i][j]= tablero[i-1][j];
					tablero[i-1][j]=' ';
				}
				if(i==0){
				tablero[i][j]=' ';
				}
			} 
		}
	}

}

void gravedadizquierda(char tablero [][maxcol],int filas, int columnas,int movfila,int movcolumna, int iguales){
  
	int x=movcolumna-iguales;
	int i=movfila;
  int contador=0;
  
	if(iguales>=2){
		for(i=movfila;i>=0;i--){
			for(int j=movcolumna;j>=x;j--){
				if(tablero[i][j]==' '){
					tablero[i][j]= tablero[i-1][j];
					tablero[i-1][j]=' ';
					contador++;
				}
				if(i==0){
				tablero[i][j]=' ';
				}

			}
		} 
  }

}

void gravedadarriba(char tablero [][maxcol],int filas, int columnas,int movfila,int movcolumna, int iguales){
  
	int x=movcolumna-iguales;
	int i=movfila;
  int contador=0;
  int j=movcolumna;
  
	if(iguales>=2){
		for(i=movfila;i>=0;i--){
			if(tablero[i][j]==' '){
        if(i-iguales>=0){
				tablero[i][j]=tablero[i-iguales][j];
        }
        tablero[i-1][j]=' ';
			}
			if(i==0){
				tablero[i][j]=' ';
			}
  	} 
	}
	
}

void gravedadabajo(char tablero [][maxcol],int filas, int columnas,int movfila,int movcolumna, int iguales){
  
	int x=movcolumna-iguales;
	int i=movfila;
  int contador=0;
  int j=movcolumna;
  
	for(int i=movfila+iguales-1;i>=0;i--){ 
  
		if(iguales>=2){
			if(tablero[i][j]==' '){
        if(i-iguales>=0){
				tablero[i][j]=tablero[i-iguales][j];
        }
        tablero[i-1][j]=' ';
			}
			if(i==0){
				tablero[i][j]=' ';
			}
		}
	}
}

//-------------------- Gravedades de las letras --------------------

//-------------------- Evaluacion de tablero --------------------

bool evaluartablero(char tablero[][maxcol],int filas, int columnas ) {
  //esta funcion es la que usamos para verificar que el jugador ganó la partida
  
  bool ganar=true;

	for(int i=0;i<filas;i++){
    for(int j=0;j<columnas;j++){
      if(tablero[i][j]==tablero[i][j+1]&&tablero[i][j]!=' '){
        ganar=false;
      }

      else if(tablero[i][j]==tablero[i+1][j]&&tablero[i][j]!=' '){
        ganar=false;
      }
    
		}
  }

  return ganar;
}

void sobreescribirdatos(jugador a[], int tam){

	ofstream miArchivo;
	miArchivo.open("temp.dat", ios::binary);

	for(int i = 0; i < tam; i++){
		miArchivo.write(reinterpret_cast<const char *>(&a[i]), sizeof(jugador));
	}

	miArchivo.close();
	remove("jugadores.dat");
  rename("temp.dat","jugadores.dat");

}
