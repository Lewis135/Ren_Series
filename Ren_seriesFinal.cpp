
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

/** VARIABLES GLOBALES */
static string extension1 = "avi";
static string extension2 = "mp4";
static string extension3 = "mkv";
string ruta, carpeta;

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


/** Funcion para RENOMBRAR/MOVER o ELIMINAR un determinado archivo*/

void modArchivo1 (string fichero){
    string char1, char2, char3, fichExt;
    string aux, aux2;
    string fviejo, fnuevo, comando_mover, comando_eliminar;

    char1 = fichero[fichero.length()-3];
    char2 = fichero[fichero.length()-2];
    char3 = fichero[fichero.length()-1];
    fichExt = char1+char2+char3; // Sacamos la extension del fichero
    if (fichero != ".."){
    if (fichExt == extension1 || fichExt == extension2 || fichExt == extension3){
    //RENOMBRAMOS LOS CAPITULOS
        aux = ruta + "\\\"" + carpeta + "\\*." + fichExt + "\"";              /**  B:\Gotham\"Gothan 1x03\*.fichExt"  */
        aux2 = "rename " + aux + " \"" + carpeta + "." + fichExt + "\""; /** rename B:\Gotham\"Gothan 1x03\*.fichExt"  "Gothan 1x03.fichExt" */

        char * com_renombrar = new char[aux2.length() + 1];
        strcpy(com_renombrar, aux2.c_str());

        system(com_renombrar);                // Renombra el archivo

    //MOVEMOS LOS CAPITULOS
        fviejo = ruta + "\\\"" + carpeta + "\\" + carpeta + "." + fichExt + "\""; //B:\Gotham\"Gothan 1x03\Gothan 1x03.fichExt"
        fnuevo = ruta + "\\\"" + carpeta + "." + fichExt + "\"";
        comando_mover = "move " + fviejo + " " + fnuevo;

        char * com_mover = new char[comando_mover.length() + 1];
        strcpy(com_mover, comando_mover.c_str());

        system(com_mover);                   // Mueve el archivo
    }else if (fichExt == "srt"){
    //MOVEMOS LOS SUBTITULOS
        fviejo = ruta + "\\\"" + carpeta + "\\*.srt\""; //B:\Gotham\"Gothan 1x03\*.srt"
        fnuevo = ruta + "\\\"" + fichero + "\"";
        comando_mover = "move " + fviejo + " " + fnuevo;

        char * com_mover = new char[comando_mover.length() + 1];
        strcpy(com_mover, comando_mover.c_str());

        system(com_mover);                   // Mueve el archivo
    }
    }
}

/* Funcion para conseguir los nombres de los archivos que estan
    *  dentro de las carpetas y despues modificar esos archivos    */
int nomArchivos(vector<string> NombreCarpetas){
    string carpeta2, fichero;
    vector<string> NombreFichero;

    for (int i = 0; i < NombreCarpetas.size(); i++ ){                            //Leemos el array
        carpeta = NombreCarpetas[i];
        if (carpeta != "..") {
               carpeta2 = ruta + "\\" + carpeta + "\\*";         //  B:\Gotham\"Gothan 1x03\*"

               NombreFichero = NombreArchivosEnDirectorio ( carpeta2 ); // Lista todos los archivos dentro de carpeta2
               if (NombreFichero.size() == 0 ) {cerr << "Error al listar los ficheros." <<endl;}
               else{
                for (int i = 0; i < NombreFichero.size(); i++){
                    fichero = NombreFichero[i];
                    modArchivo1(fichero); // dependendiendo de su extension --> renombrar y mover || mover
                }
               }
        }
    }
    cout << "Todo Renombrado y puesto en la carpeta padre." <<endl;
    return 0;
}

void modConPatron (string fichero, int i1, int i2, string patron){
    string char1, char2, char3, fichExt;
    char * num1 = new char[3];
    char * num2 = new char[3];
    string aux, aux2;
    string fnuevo;

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

int nomPatron (vector<string> NombreFicheros, string patron){
    int i1 = 0;
    int i2 = 1;
    string fichero;
    for (int i = 1; i < NombreFicheros.size(); i++){ // empezamos con i=1 porque i=0 es el directorio '..'
        fichero = NombreFicheros[i];
        modConPatron(fichero,i1,i2, patron); // dependendiendo de su extension --> renombrar || no hacer nada
        i2++;
        if (i2==10){
            i1++;
            i2 = 0;} // El futuro nombre sera del tipo: patroni1i2.extension
    }
    cout << "Todo Renombrado con el Patron indicado." <<endl;
    return 0;
}

/** MAIN */
int main()
{
	/**Definicion de valiables locales */
	string rutaDir;
	bool cond = true;
	int opcion = 5;
	string patron;
	vector <string> NombreF;

/** MENU INICIAL */
    while (cond){
        cout << "1.- Renombrar capitulos dentro de carpetas." << endl;
        cout << "2.- Renombrar capitulos con un patron." << endl;
        cout << "3.- Salir." << endl;

        cin >> opcion;

        if (opcion ==1 || opcion == 2 || opcion == 3){cond = false;}
    }

        if (opcion !=3){
        do {
            cout << "Escribe la ruta de la carpeta padre: " << endl;			//Pedimos la ruta de la carpeta
            cin >> ruta;													    //Introducen la ruta
            rutaDir = ruta + "\\*";

            NombreF = NombreArchivosEnDirectorio( rutaDir );
            if (NombreF.size() == 0){cerr << "Esa carpeta no existe o no es accesible." <<endl;}
        }while(NombreF.size() == 0);

        if (opcion == 2) {
            cout << "Escribe el PATRON DE NOMBRE para los archivos: " << endl;
            cin >> patron;          //Gotham1x
        }

        }
   /*Fin del menu*/

    if (opcion == 1){
        nomArchivos(NombreF);
    }
    else if(opcion == 2){
        nomPatron(NombreF, patron);
    }
    else{
        cout << "Eso es todo amigos!" <<endl;
    }

    return 0;
}




