#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

using namespace std;

int main(){

    /// Declaracion de las variables
    char * datos= new char [100]; // Almacenara el contenido de lo que escribamos por teclado
    string linea_fichero; // Esta variable se usara para volcar las lineas del fichero
    ofstream fw;
    ifstream fr;

    fw.open("datos.txt");

    /** ######## INTRODUCIR DATOS ######*/

    cout << "Escribe tu nombre: ";// Muestra por pantalla
    cin >> datos;      // Entrada de teclado guardado en 'datos' // cin.getline(datos,100);
    fw << datos << endl;

    cout << "Tu edad: ";
    cin >> datos;



    fw << datos << endl;  // Volvemos a escribir en el fichero (Actualiza)
    fw.close();  // Cerramos el stream para que no haya problemas.

    /** ######## LEER DATOS ######*/

    fr.open("datos.txt");
    cout << "Contenido del fichero: " << endl;
    /// Lectura linea a linea del fichero
    while(getline(fr, linea_fichero)){
        cout << linea_fichero << endl;
    }
    fr.close();

}
