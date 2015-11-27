
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

void modificarArchivo (string fichero){
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
    /*else {
    // ELIMINAMOS LO SOBRANTE
        aux = ruta + "\\\"" + carpeta;                      /**  B:\Gotham\"Gothan 1x03  
        aux2 = "del " + aux + "\\*." + fichExt + "\""; /** del B:\Gotham\"Gothan 1x03\Gothan 1x03.fichExt" 
        char * com_eliminar = new char[aux2.length() + 1];
        strcpy(com_eliminar, aux2.c_str());
        system(com_eliminar);            //Elimina el archivo
    }*/
    }
}


/** MAIN */
int main()
{
	/**Definicion de valiables locales */
	string rutaDir, carpeta2, fichero;
	vector <string> NombreCarpetas;
    vector <string> NombreFichero;

    do {
        cout << "Escribe la ruta de la carpeta padre: " << endl;					  //Pedimos la ruta de la carpeta
        cin >> ruta;															      //Introducen la ruta
        rutaDir = ruta + "\\*";

        NombreCarpetas = NombreArchivosEnDirectorio( rutaDir );
        if (NombreCarpetas.size() == 0){cerr << "Esa carpeta no existe o no es accesible." <<endl;}
    }while(NombreCarpetas.size() == 0);

    for (int i = 0; i < NombreCarpetas.size(); i++ ){                            //Leemos el array
        carpeta = NombreCarpetas[i];
        if (carpeta != "..") {
               carpeta2 = ruta + "\\" + carpeta + "\\*";         //  B:\Gotham\"Gothan 1x03\*"

               NombreFichero = NombreArchivosEnDirectorio ( carpeta2 ); // Lista todos los archivos dentro de carpeta2
               if (NombreFichero.size() == 0 ) {cerr << "Error al listar los ficheros." <<endl;}
               else{
                for (int i = 0; i < NombreFichero.size(); i++){
                    fichero = NombreFichero[i];
                    modificarArchivo(fichero); // dependendiendo de su extension --> renombrar y mover || mover || eliminar
                }
               }
        }
    }
    cout << "Todo Renombrado o Eliminado." <<endl;
}




