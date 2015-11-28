
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

/** VARIABLES GLOBALES */
static string extension1 = "avi";
static string extension2 = "mp4";
static string extension3 = "mkv";
string ruta, carpeta, patron;

/** FUNCION PARA LISTAR ARCHIVOS EN UN DIRECTORIO */
vector<string> NombreArchivosEnDirectorio(string directorio) {
    vector<string> archivos;
    WIN32_FIND_DATA fileData;
    HANDLE hFind;
    if ( !((hFind = FindFirstFile(directorio.c_str(), &fileData)) == INVALID_HANDLE_VALUE) ) {
        while(FindNextFile(hFind, &fileData)) {
            archivos.push_back(fileData.cFileName);
        }
    }
    FindClose(hFind);
    return archivos;
}


/** Funcion para RENOMBRAR un determinado archivo*/

void modificarArchivo (string fichero, int i1, int i2){
    string char1, char2, char3, fichExt;
    char * num1 = new char[3];
    char * num2 = new char[3];
    string aux, aux2;
    string fviejo, fnuevo;

    char1 = fichero[fichero.length()-3];
    char2 = fichero[fichero.length()-2];
    char3 = fichero[fichero.length()-1];
    fichExt = char1+char2+char3; // Sacamos la extension del fichero

    itoa(i1, num1,10);
    itoa(i2,num2,10);

    if (fichero != ".."){
    if (fichExt == extension1 || fichExt == extension2 || fichExt == extension3){
    //RENOMBRAMOS LOS CAPITULOS

    //-->rename B:\Gotham\fichero.ext patroni1i2.ext
        aux = ruta + "\\\"" + fichero + "\"";             /**  B:\Gotham\"fichero.ext"  */
        fnuevo = patron + num1 + num2;
        aux2 = "rename " + aux + " \"" + fnuevo + "." + fichExt + "\""; /** rename B:\Gotham\"fichero.ext"  "patroni1i2.fichExt" */

        char * com_renombrar = new char[aux2.length() + 1];
        strcpy(com_renombrar, aux2.c_str());

        system(com_renombrar);                // Renombra el archivo

    }
    }
}


/** MAIN */
int main()
{
	/**Definicion de valiables locales */
	string rutaFich, carpeta2, fichero;
    vector <string> NombreFicheros;
    int i1=0, i2=1;

    do {
        cout << "Escribe la ruta de la carpeta padre: " << endl;					  //Pedimos la ruta de la carpeta
        cin >> ruta;															      //Introducen la ruta
        rutaFich= ruta + "\\*";
        NombreFicheros = NombreArchivosEnDirectorio( rutaFich );
        if (NombreFicheros.size() == 0){cerr << "Error al listar los ficheros." <<endl;}
    }while(NombreFicheros.size() == 0);

    cout << "Escribe el PATRON DE NOMBRE para los archivos: " << endl;
    cin >> patron;                  //Gotham1x

    for (int i = 1; i < NombreFicheros.size(); i++){ // empezamos con i=1 porque i=0 es el directorio '..'
        fichero = NombreFicheros[i];
        modificarArchivo(fichero,i1,i2); // dependendiendo de su extension --> renombrar || no hacer nada
        i2++;
        if (i2==10){
            i1++;
            i2 = 0;} // El futuro nombre sera del tipo: patroni1i2.extension
    }
    cout << "Todo Renombrado." << endl;
}




