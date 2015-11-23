#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <cstring> // INCLUDE NECESARIO PARA EL strcpy()

using namespace std;

/** VARIABLES GLOBALES */
    ofstream fw;
    ofstream copia_fich;
    ifstream fr;

 void copiar_fichero( string linea){
        copia_fich << linea << endl;
        cout << "Copia realizada sin problemas." << endl;
    }

int main(){

    /// Declaracion de las variables
    char * datos= new char [100]; // Almacenara el contenido de lo que escribamos por teclado
    string linea_fichero; // Esta variable se usara para volcar las lineas del fichero

    fw.open("datos.txt");
    if (fw == NULL ) {
        cout << "Error al abrir el fichero" << endl;

    }else{

    /** ######## INTRODUCIR DATOS ######*/

    cout << "Escribe tu nombre: ";// Muestra por pantalla
    cin >> datos;      // Entrada de teclado guardado en 'datos' // cin.getline(datos,100);
    fw << datos << endl;


    cout << "Tu edad: ";
    cin >> datos;


    fw << datos << endl;  // Volvemos a escribir en el fichero (Actualiza)
    fw.close();  // Cerramos el stream para que no haya problemas.
    }

    /** ######## LEER DATOS ######*/

    fr.open("datos.txt");
    copia_fich.open("copiaDatos.txt");
    if (fr == NULL || copia == NULL){
        cout<< "Error al abrir el fichero" << endl;
    }else{
    cout << "Contenido del fichero: " << endl;
    /// Lectura linea a linea del fichero

    while(getline(fr, linea_fichero)){

        cout << linea_fichero << endl;
        copiar_fichero(linea_fichero); // Copiar linea a linea el contenido de un fichero a otro fichero
    }

    copia_fich.close();
    fr.close();
    }




}
