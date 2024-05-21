/*
Sistema de gestión de tareas
Estudiantes: Cristian Camilo Bonilla, Nicolas Velasco y Jesús Antonio Murcia
Fecha: 5 de Junio
*/


#include <iostream>
#include <locale.h>
#include <string>

using namespace std;


//Nombre de los cursos del estudiante
struct Cursos {
    char nombre[1];
    char codigo[1];
};

//Crear estudiante
struct Estudiante {
    char nombre[100];
    int codigo;
    char apellido[100];
    char correo[100];
    Cursos materias[15];
    int numMateriasInscritas; //Para conocer la cantidad de materias registradas
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
void registrarEstudiante(Estudiante &estudiante);
void registrarMaterias(Estudiante &estudiante);

//Funciones de las tareas
void crearTarea( Cursos &curso );
void modificarTarea( Tarea &tarea );
void eliminarTarea( Tarea &tarea, int contadorTarea );
void estadoTarea( Tarea &tarea );

//Consultas
void tareasMateria( Tarea &tarea);
void tareasFecha( Tarea &tarea);

//Funciones adicionales
int obtenercodigo();


main() {
    setlocale(LC_ALL, "spanish");

    system("cls");
    Tarea tareas[100];
    Cursos materias[15];
    Estudiante perfil;

    int contadorTarea, contadorMateria = 0, opcion = 0;

    cout << "¡Bienvenido a tu sistema de gestion de tareas personal!\n";

    system("PAUSE");
    system("CLS");

    cout << "Es hora de registar tu perfil.\n";
    registrarEstudiante(perfil);

    //Menu de opciones
    while (opcion == 0)
    {    
        system("CLS");      
        cout << "Menú de tareas.\n";
        cout << "\nEdición\n";
        cout << "--------------------\n";
        cout << "\t 1. Crear tarea.\n";    
        cout << "\t 2. Crear tarea.\n";
        cout << "\t 3. Modificar tarea.\n";
        cout << "\t 4. Cambiar estado de tarea.\n";
        cout << "\t 5. Eliminar tarea.\n";
        cout << "\nConsultas\n";
        cout << "--------------------\n";
        cout << "\t 6. Consultar el historial de tareas de una materia.\n";
        cout << "\t 7. Consultar tareas para una fecha específica.\n";
        cout << "Salir del programa.\n";

        cout << "\nOpcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            break;
        
        case 2:
            break;
        
        case 3:
            break;
        
        case 4:
            break;
        
        case 5:
            break;
        
        case 6:
            break;
        
        case 7:
            opcion = 1;
            break;
        
        default:
            break;
        }
    }
}

//Funciones
void registrarEstudiante(Estudiante &estudiante){
    //Solicitar nombre, apellido y código
    cout << "--------------------\n";
    cout << "Datos personales.\n";
    do{
        cout << "Ingresa tu nombre: ";
        cin.getline(estudiante.nombre, 100);
    }while(estudiante.nombre == NULL);

    do{
        cout << "Ingresa tu apellido: ";
        cin.getline(estudiante.apellido, 100);
    }while(estudiante.apellido == NULL);

    do{
        cout << "Ingresa tu correo: ";
        cin >> estudiante.correo;
    }while(estudiante.correo == NULL);

    //Solicitar código
    estudiante.codigo = obtenercodigo();

    registrarMaterias(estudiante);
}

void registrarMaterias(Estudiante &estudiante){
    string continuar;
    int numMateriasRegistradas = 0;

    cout << "\nMaterias.\n";
    cout << "--------------------";
    cout << "\nEs momento de registrar tus materias.\n";

    //Solicitar los datos de las materias inscritas
    while (continuar != "n" && numMateriasRegistradas < 15){
        cout << "\nIngresa el nombre de la materia: ";
        cin >> estudiante.materias[numMateriasRegistradas].nombre;
        cout << "\tLa materia se registro como " << estudiante.materias[numMateriasRegistradas].nombre;

        cout << "\n\tAhora registra el código de la materia: ";
        cin >> estudiante.materias[numMateriasRegistradas].codigo;

        numMateriasRegistradas++;

        //Preguntar por si se quiere dejar de registrar materias
        cout << "--------------------\n";
        cout << "¿Desea inscribir más materias? s/n: ";
        cin >> continuar;

        while(continuar != "s" && continuar != "n"){
            cout << "Digite 's' o 'n', ningún otro valor: ";
            cin >> continuar;
        }

    }

    //Almacenar el número de materias registradas
    estudiante.numMateriasInscritas = numMateriasRegistradas;
}

int obtenercodigo(){
    int codigo;
    
    cout << "Ingrese el código de estudiante: ";
    cin >> codigo;

    while(cin.fail() || codigo < 0){
        cin.clear();
        cin.ignore();
        cout << "Ingrese solamente valores númericos: ";
        cin >> codigo;
    }

    return codigo;
}

void crearEstudianteCursos(Estudiante &perfil, Cursos materias[], int contador) {
    int i;
    string decision = "s";
    cin.ignore();

    cout << "Nombre del estudiante: ";
    cin.getline(perfil.nombre, 100);

    cout << "Apellidos del estudiante: ";
    cin.getline(perfil.apellido, 100);

    cout << "Código del estudiante: ";
    cin >> perfil.codigo;

    cout << "Correo del estudiante: ";
    cin.getline(perfil.correo, 100);

    cout << perfil.nombre << endl;
    cout << perfil.apellido << endl;
    cout << perfil.codigo << endl;
    cout << perfil.correo << endl;

    cout << "\nEl estudiante tiene un máximo de 15 materias para registrar.";

    while( contador <15 && decision == "s") {
        cout << "Nombre del curso " << contador + 1 << ": ";
        cin.getline(materias[contador].nombre, 50);
        cout << materias[contador].nombre << endl;

        cin.clear();

        cout << "Código del curso " << materias[contador].nombre << ": ";
        cin.getline(materias[contador].codigo, 100);
        cin.clear();
        cout << materias[contador].codigo;

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



