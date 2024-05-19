/*
Sistema de gestión de tareas
Estudiantes: Cristian Camilo Bonilla, Nicolas Velasco y Jesús Antonio Murcia
Fecha: 5 de Junio
*/


#include <iostream>
#include <locale.h>
#include <string>
using namespace std;

//Crear estudiante
struct Estudiante 
{
    char nombre[100];
    char codigo[100];
    char apellidos[100];
    char correo[100];
};

//Nombre de los cursos del estudiante
struct Cursos
{
    char nombre[1];
    char codigo[1];
};


//Datos de las tareas
struct Tarea {
    char nombre[1];
    char descripcion[1];
    char codigoTarea[1];
    char estado[1];
    char dia[1];
    char mes[1];
    Cursos materia;
};

//Prototipado de funciones
void crearEstudianteCursos(Estudiante &es, Cursos materias[], int contador);

//Funciones de las tareas
void crearTarea( Cursos &curso );
void modificarTarea( Tarea &tarea );
void eliminarTarea( Tarea &tarea, int contadorTarea );
void estadoTarea( Tarea &tarea );

//Consultas
void tareasMateria( Tarea &tarea);
void tareasFecha( Tarea &tarea);


main() {
    system("cls");
    Tarea tareas[100];
    Cursos materias[15];
    Estudiante perfil;

    int contadorTarea, contadorMateria = 0;

    crearEstudianteCursos(perfil, materias, contadorMateria);

}

//Funciones
void crearEstudianteCursos(Estudiante &perfil, Cursos materias[], int contador) {
    int i;
    string decision = "s";

    cout << "Nombre del estudiante: ";
    cin.getline(perfil.nombre, 100);

    cin.clear();

    cout << "Apellidos del estudiante: ";
    cin.getline(perfil.apellidos, 100);

    cout << "Código del estudiante: ";
    cin.getline(perfil.codigo, 100);

    cout << "Correo del estudiante: ";
    cin.getline(perfil.correo, 100);

    cout << perfil.nombre << endl;
    cout << perfil.apellidos << endl;
    cout << perfil.codigo << endl;
    cout << perfil.correo << endl;

    cout << "\nEl estudiante tiene un máximo de 15 materias para registrar.";

    while( contador <15 && decision == "s") {
        cout << "Nombre del curso " << contador + 1 << ": ";
        cin.getline(materias[contador].nombre, 100);
        cout << materias[contador].nombre << endl;

        cin.clear();

        cout << "Código del curso " << materias[contador].nombre << ": ";
        cin.getline(materias[contador].codigo, 100);
        cout << materias[contador].nombre;

        cin.clear();
        contador++;

        do
        {
            cout << "\n¿Desea añadir otro curso?: s/n";
            cin >> decision;
        } while (decision != "s" && decision != "n");
        

        cin.ignore();
    }

    for ( i = 0; i < contador; i++) {
        cout << materias[i].nombre << endl;
        cout << materias[i].codigo << endl;
    }

    
}



