
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

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
	string linea,ruta, rutaFich, rutaDir, aux, aux2;
    vector <string> NombreFicheros;
    ofstream fwrite;
    ifstream fread;

	cout << "Escribe la ruta de la carpeta padre: " << endl;					  //Pedimos la ruta de la carpeta
	cin >> ruta;															  //Introducen la ruta
	rutaDir = ruta + "\\*";
	rutaFich = ruta + "\\carpetas.txt";

    NombreFicheros = NombreArchivosEnDirectorio( rutaDir );

    cout << rutaDir<<endl;
    fwrite.open(rutaFich.c_str());

    for (int i = 0; i < NombreFicheros.size(); i++ ){                   //Leemos el array y lo escribimos en un fichero
        fwrite << NombreFicheros[i] << endl;
        cout << NombreFicheros[i] <<endl;
    }
    fwrite.close();

    fread.open(rutaFich.c_str());

	if ( fread == NULL ) { cout << "No se ha podido abrir el fichero \n"; }
	else {
		//Si el archivo se a abierto lo recorremos y renombramos.

		while (getline(fread, linea)) {
			if (linea == "carpetas.txt" || linea == "..") {
			}
			else{
                aux = ruta + "\\\"" + linea + "\\*\"";              /**  B:\Gotham\"Gothan 1x03\*"  */
				aux2 = "rename " + aux + " \"" + linea + ".mkv\""; /** rename B:\Gotham\"Gothan 1x03\*"  "Gothan 1x03.mkv" */

				char * cadena = new char[aux2.length() + 1];
				strcpy(cadena, aux2.c_str());

				system(cadena);

				//cout << cadena << endl;
			}
		}
		cout<< "Todo Renombrado." <<endl;

	}
	fread.close();
}
