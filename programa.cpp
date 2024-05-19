#include <iostream>
#include <locale.h>
#include <string>
using namespace std;

//Crear estudiante
struct Estudiante 
{
    char nombre[1];
    char codigo[1];
    char apellidos[1];
    char correo[1];
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
void crearEstudianteCursos(Estudiante &es);

//Funciones de las tareas
void crearTarea( Cursos &curso );
void modificarTarea( Tarea &tarea );
void eliminarTarea( Tarea &tarea );
void estadoTarea( Tarea &tarea );

//Consultas
void tareasMateria( Tarea &tarea);
void tareasFecha( Tarea &tarea);


main() {

    
}




