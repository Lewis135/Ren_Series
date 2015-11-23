
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

int main()
{

	/**Definicion de valiables */
	string ruta, rutaDir, aux, aux2, carpeta,carpeta2, fichero;
    vector <string> NombreCarpetas;
    vector <string> NombreFichero;
    string char1, char2, char3, fichExt;


	cout << "Escribe la ruta de la carpeta padre: " << endl;					  //Pedimos la ruta de la carpeta
	cin >> ruta;															      //Introducen la ruta
	rutaDir = ruta + "\\*";
    cout << rutaDir <<endl;
    NombreCarpetas = NombreArchivosEnDirectorio( rutaDir );

    for (int i = 0; i < NombreCarpetas.size(); i++ ){                            //Leemos el array
       carpeta = NombreCarpetas[i];
       if (carpeta != "..") {
           carpeta2 = ruta + "\\" + carpeta + "\\*";         //  B:\Gotham\"Gothan 1x03\*"
           cout << carpeta2 <<endl;
           NombreFichero = NombreArchivosEnDirectorio ( carpeta2 );
           if (NombreFichero.size() == 0 ) {cerr << "error" <<endl;}
           else
           for (int i = 0; i < NombreFichero.size(); i++){
            fichero = NombreFichero[i];
            //cout << fichero <<endl;
            char1 = fichero[fichero.length()-3];
            char2 = fichero[fichero.length()-2];
            char3 = fichero[fichero.length()-1];
            fichExt = char1+char2+char3; // Sacamos la extension del fichero
            cout << fichExt <<endl;
            if (fichero != ".."){
            if (fichExt == extension1 || fichExt == extension2 || fichExt == extension3){
                aux = ruta + "\\\"" + carpeta + "\\*\"";              /**  B:\Gotham\"Gothan 1x03\*"  */
                aux2 = "rename " + aux + " \"" + carpeta + "." + fichExt + "\""; /** rename B:\Gotham\"Gothan 1x03\*"  "Gothan 1x03.mkv" */

                char * cadena = new char[aux2.length() + 1];
                strcpy(cadena, aux2.c_str());

                system(cadena);
            }else if (fichExt == "srt"){}
                else {
                    aux = ruta + "\\\"" + carpeta;                      /**  B:\Gotham\"Gothan 1x03  */
                    aux2 = "del " + aux + "\\*." + fichExt + "\""; /** del B:\Gotham\"Gothan 1x03\Gothan 1x03.fichExt" */
                    char * cadena = new char[aux2.length() + 1];
                    strcpy(cadena, aux2.c_str());
                    system(cadena);
                }
           }
           }
        }

    }
    cout << "Todo Renombrado." <<endl;

}

