/*
Sistema de gestión de tareas
Estudiantes: Cristian Camilo Bonilla, Nicolas Velasco y Jesús Antonio Murcia
Fecha: 5 de Junio
*/


#include <iostream>
#include <locale.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <vector>
#include <cmath>

using namespace std;

//REGISTROS 

//Nombre de los cursos del estudiante
struct Cursos {
    string nombre;
    string codigo;
    int cantidad;
    int cantidadMaterias;
};

//Crear estudiante
struct Estudiante {
    string nombre;
    string codigo;
    string apellido;
    string correo;
    Cursos materias[15];
    int numMateriasInscritas; 
};

//Datos de las tareas
struct Tarea {
    string nombre;
    string descripcion;
    string codigoTarea;
    string curso;
    string estado;//En proceso, entregada y no entregada
    int dia;
    int mes;
    int anio;
    float nota;
    Cursos materia;
};

//FUNCIONES

// Prototipado de funciones
void registrarEstudiante(Estudiante &estudiante);
void registrarMaterias(Estudiante &estudiante); 

// Funciones de las tareas
int crearTarea(Estudiante &estudiante, Tarea tareas[], Cursos materias[], int contadorTarea);
int crearNTareas(Estudiante &estudiante, Tarea tareas[], Cursos materias[], int contadorTarea);
int eliminarTarea(Tarea tarea[],Tarea TareaEliminada[], int contadorTarea, int contadorEliminado);
void modificarTarea(Tarea tareas[], int contadorTarea);
void cambiarEstadoTarea(Tarea tareas[], int contadorTarea);
void estadoTarea(Tarea &tarea);
void buscarFechaTarea(Tarea tareas[], int contadorTarea);

// Consultas
void tareasMateria(Tarea &tarea);
void tareasFecha(Tarea &tarea);
void historialTareas(Tarea tarea[],Tarea TareaEliminada[],int contadorTarea,int contadorEliminado, Estudiante &estudiante);

// Funciones adicionales
string obtenercodigo();
int obtenerAnio();
int indiceTarea(Tarea tareas[], int contadorTarea);
int indiceTareaEstado(Tarea tareas[], int contadorTarea);
int obtenerMes(int anio);
int obtenerDia(int mes, int anio);
bool validarcorreo(string correo);
bool validarNombre(string nombre);
string crearCodigo(Estudiante &estudiante, string cursoNombre);
string obtenerCorreo();
string obtenerNombre(string aPedir);


main() { 
    //Vectorizacion de los struct
    Tarea tareas[100], tareaEliminada[100];
    Cursos materias[15];
    Estudiante perfil;

    setlocale(LC_ALL, "spanish");
    system("cls");

    //Variales globales
    int decision = 0, contadorMateria = 0, opcion = 0, contadorTarea = 0, contadorEliminado=0, condicionEliminar=0;
    cout << "¡Bienvenido a tu sistema de gestion de tareas personal!\n";

    system("PAUSE");
    system("CLS");

    cout << "Es hora de registrar tu perfil.\n";
    registrarEstudiante(perfil);

    // Menú de opciones
    while (decision == 0) {
        system("CLS");
        cout << "Menú de tareas.\n";
        cout << "\nEdición\n";
        cout << "--------------------\n";
        cout << "\t 1. Crear tarea.\n";
        cout << "\t 2. Crear n tareas.\n";
        cout << "\t 3. Modificar tarea.\n";
        cout << "\t 4. Cambiar estado de tarea.\n";
        cout << "\t 5. Eliminar tarea.\n";
        cout << "\nConsultas\n";
        cout << "--------------------\n";
        cout << "\t 6. Consultar el historial de tareas de una materia.\n";
        cout << "\t 7. Consultar tareas para una fecha específica.\n";
        cout << "\n0. Salir del programa.\n";

        cout << "\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                contadorTarea = crearTarea(perfil, tareas, materias, contadorTarea);
                system("pause");
                break;

            case 2:
                contadorTarea = crearNTareas(perfil, tareas, materias, contadorTarea);
                system("pause");
                break;

            case 3:
                modificarTarea(tareas, contadorTarea);
                break;

            case 4:
                cambiarEstadoTarea(tareas, contadorTarea);
                break;

            case 5:
                condicionEliminar=eliminarTarea( tareas, tareaEliminada,  contadorTarea,  contadorEliminado);
                if (condicionEliminar==0){
                }else{
                    contadorTarea--;
                    contadorEliminado++;
                }
                break;
            case 6:
                historialTareas( tareas, tareaEliminada, contadorTarea, contadorEliminado, perfil);
                break;

            case 7:
                buscarFechaTarea(tareas, contadorTarea);
                break;

            case 0:
                decision = 1;
                break;

            default:
                cout << "\nDigite una opción válida.";
                break;
        }
    }

}

// Funciones
void registrarEstudiante(Estudiante &estudiante) {
    // Solicitar nombre, apellido, correo y codigo
    cout << "--------------------\n";
    cout << "Datos personales.\n";

    estudiante.nombre = obtenerNombre("nombre");

    estudiante.apellido = obtenerNombre("apellido");

    estudiante.correo = obtenerCorreo();

    estudiante.codigo = obtenercodigo();

    registrarMaterias(estudiante);
}

void registrarMaterias(Estudiante &estudiante) { 
    string continuar;
    int numMateriasRegistradas = 0;
    bool materiaValida = true;

    cout << "\nMaterias.\n";
    cout << "--------------------";
    cout << "\nEs momento de registrar tus materias.\n";

    // Solicitar los datos de las materias inscritas
    while (continuar != "n" && estudiante.numMateriasInscritas < 15) {

        cin.ignore();

        cout << "\nIngresa el nombre de la materia: ";
        do{
            getline(cin, estudiante.materias[numMateriasRegistradas].nombre);
            if (numMateriasRegistradas != 0){
                for (int i=0; i<numMateriasRegistradas; i++){
                    if (estudiante.materias[i].nombre == estudiante.materias[numMateriasRegistradas].nombre){
                        cout << "Dos materias no pueden llamarse igual, ingrese un nuevo nombre: ";
                        materiaValida = false;
                    }               
                }
            }
        }while (!materiaValida);


        cout << "\tAhora registra el código de la materia: ";
        do{
            getline(cin, estudiante.materias[numMateriasRegistradas].codigo);
            if (numMateriasRegistradas !=0){
                for (int i=0; i<numMateriasRegistradas; i++){
                    if ( estudiante.materias[i].codigo == estudiante.materias[numMateriasRegistradas].codigo){
                        cout << "Dos materias no pueden tener el mismo código, ingrese uno nuevo: ";
                        materiaValida = false;
                    }               
                }
            }
        }while (!materiaValida);

        cout << "\nLa materia se registró como " << estudiante.materias[numMateriasRegistradas].nombre << endl;
        cout << "El código de " << estudiante.materias[numMateriasRegistradas].nombre << " es " << estudiante.materias[numMateriasRegistradas].codigo;



        // Definir la cantidad de tareas para cada materia
        estudiante.materias[numMateriasRegistradas].cantidad = 0;
        numMateriasRegistradas++;

        // Preguntar por si se quiere dejar de registrar materias
        cout << "\n--------------------\n";
        cout << "¿Desea inscribir más materias? s/n: ";
        cin >> continuar;

        while (continuar != "s" && continuar != "n") {
            cout << "Digite 's' o 'n', ningún otro valor: ";
            cin >> continuar;
        }
    }


    // Almacenar el número de materias registradas
    estudiante.numMateriasInscritas += numMateriasRegistradas;
}


int crearTarea(Estudiante &estudiante, Tarea tareas[], Cursos materias[], int contadorTarea){
    system("CLS");
    int i;

    cin.ignore();
    cout << "Tarea " << contadorTarea + 1<< endl;
    cout << "--------------------\n";

    cout << "Ingresa el nombre de la tarea: ";
    getline(cin, tareas[contadorTarea].nombre);

    cout << "Ingresa la descripción de la tarea: ";
    getline(cin, tareas[contadorTarea].descripcion);

    cout << "Ingrese el código del curso al que pertenece la materia, las materias son: \n";
    cout << endl;

    cout << left << setw(20) << "Materia" << setw(10) << "Codigo" << endl;
    for(i = 0; i < estudiante.numMateriasInscritas ; i++) {//impresion de nombre y codigo de materia
        cout << setw(20) << left << estudiante.materias[i].nombre << setw(10) << left << estudiante.materias[i].codigo << endl;
    }

    cout << endl << "Ingrese código: ";

    int cantmaterias=i;

    do{ //Validación del ingreso del codigo del curso en la tarea
        int numTarea=0;
        getline(cin, tareas[contadorTarea].curso);
        for (int i=0;i<cantmaterias;i++){
            if ( tareas[contadorTarea].curso==estudiante.materias[i].codigo){
                numTarea++;
                break;
            }
        }
        if (numTarea!=0){
            break;
        }
        cout << "El código que ingreso no pertenece a ninguna materia, ingrese de nuevo el código: ";
    }while (true);



    cout << "\nFecha de entrega de la tarea.\n";
    cout << "--------------------\n";

    //Fechas
    tareas[contadorTarea].anio = obtenerAnio();
    tareas[contadorTarea].mes = obtenerMes(tareas[contadorTarea].anio);
    tareas[contadorTarea].dia = obtenerDia(tareas[contadorTarea].mes, tareas[contadorTarea].anio);   


    tareas[contadorTarea].estado = "En proceso";

    contadorTarea++;

    for (i=0; i < contadorTarea; i++) {
        cout << endl << "Nombre de la tarea "<< i+1 << ": " << tareas[i].nombre << endl;
        cout << "Descripcion: " << tareas[i].descripcion << endl;
        cout << "Estado: " << tareas[i].estado << endl;
        cout << "Curso: " << tareas[i].curso << endl;
        cout << "Codigo: " << tareas[i].codigoTarea << endl;
        cout << "Año de entrega: " << tareas[i].anio << endl;
        cout << "Mes de entrega: " << tareas[i].mes << endl;
        cout << "Dia de entrega: " <<tareas[i].dia << endl;
        cout << endl;
    }

    return contadorTarea;
}

int crearNTareas(Estudiante &estudiante, Tarea tareas[100], Cursos materias[], int contadorTarea){
    int i = 0;

    string repeticion = "s";

    while(repeticion == "s" && contadorTarea < 100) {
        system("CLS");
        cout << "Tarea " << contadorTarea+1 << endl;
        cout << "--------------------\n";
        cin.ignore();

        cout << "Ingresa el nombre de la tarea: ";
        getline(cin, tareas[contadorTarea].nombre);

        cout << "Ingresa la descripción de la tarea: ";
        getline(cin, tareas[contadorTarea].descripcion);

        cout << "Ingrese el codigo del curso al que pertenece la materia, las materias son: \n";
        cout << endl;

        cout << left << setw(20) << "Materia" << setw(10) << "Codigo" << endl;
        for(i = 0; i < estudiante.numMateriasInscritas ; i++) {
            cout << setw(20) << left << estudiante.materias[i].nombre << setw(10) << left << estudiante.materias[i].codigo << endl;
        }

        cout << endl << "Ingrese código: ";

        int cantmaterias=i;

        do{ //Validación del ingreso del codigo del curso en la tarea
            int numTarea=0;
            getline(cin, tareas[contadorTarea].curso);
            for (int i=0;i<cantmaterias;i++){
                if ( tareas[contadorTarea].curso==estudiante.materias[i].codigo){
                    numTarea++;
                    break;
                }
            }
            if (numTarea!=0){
                break;
            }
            cout << "El código que ingreso no pertenece a ninguna materia, ingrese de nuevo el código: ";
        }while (true);





        cout << "\nFecha de entrega de la tarea.\n";
        cout << "--------------------\n";

        //Fechas
        tareas[contadorTarea].anio = obtenerAnio();
        tareas[contadorTarea].mes = obtenerMes(tareas[contadorTarea].anio);
        tareas[contadorTarea].dia = obtenerDia(tareas[contadorTarea].mes, tareas[contadorTarea].anio);
        tareas[contadorTarea].codigoTarea = crearCodigo(estudiante, tareas[contadorTarea].curso);    
        tareas[contadorTarea].estado = "En proceso";

        contadorTarea++;

        cout << "¿Desea agregar otra tarea? s/n: ";
        cin >> repeticion;
    }

    for (i=0; i < contadorTarea; i++) {
        cout << endl << "Nombre de la tarea "<< i+1 << ": " << tareas[i].nombre << endl;
        cout << "Descripcion: " << tareas[i].descripcion << endl;
        cout << "Estado: " << tareas[i].estado << endl;
        cout << "Curso: " << tareas[i].curso << endl;
        cout << "Codigo: " << tareas[i].codigoTarea << endl;
        cout << "Año de entrega: " << tareas[i].anio << endl;
        cout << "Mes de entrega: " << tareas[i].mes << endl;
        cout << endl;
    }

    return contadorTarea;
}

void modificarTarea(Tarea tareas[], int contadorTarea) {
    system("ClS");

    int decision = 0, opcion, indice, opcionFecha;

    if ( contadorTarea > 0 ) {
            cout << "Modificar tarea.\n";
            cout << "--------------------\n";
            indice = indiceTarea(tareas, contadorTarea) - 1;

            while(decision == 0) {
                system("CLS");

                cout << "Opciones.\n";
                cout << "--------------------\n";
                cout << "1. Modificar nombre de una tarea.\n";
                cout << "2. Modificar fecha de una tarea.\n";
                cout << "3. Modificar descripcion de una tarea.\n";
                cout << "4. Modificar todo.\n";
                cout << "5. Cambiar tarea.\n";
                cout << "6. Salir.\n";

                cin >> opcion;

                while (cin.fail())
                {
                    cin.clear();
                    cin.ignore();
                    cout << "\nIngrese una opción válida. Intente nuevamente: ";
                    cin >> opcion;
                }

                switch (opcion)
                {
                case 1:
                    system("CLS");
                    cout << "Ingrese el nuevo nombre de la tarea " << tareas[indice].nombre << ": ";
                    cin.ignore();

                    getline(cin, tareas[indice].nombre);
                    break;

                case 2:
                    system("CLS");
                    cout << "¿Qué desea cambiar?\n";
                    cout << "--------------------\n";
                    cout << "1. Modificar año.\n";
                    cout << "2. Modificar mes.\n";
                    cout << "3. Modificar día.\n";
                    cout << "4. Modificar 2 o más parámetros.\n";
                    cout << "5. Salir.\n";

                    cin >> opcionFecha;

                    while (cin.fail() || opcionFecha > 5 || opcionFecha < 1)
                    {
                        cin.clear();
                        cin.ignore();
                        cout << "\nIngrese una opción válida. Intente nuevamente: ";
                        cin >> opcionFecha;
                    }

                    switch (opcionFecha)
                    {
                    case 1:
                        tareas[indice].anio = obtenerAnio();
                        break;

                    case 2:
                        tareas[indice].mes = obtenerMes(tareas[indice].anio);
                        break;

                    case 3:
                        tareas[indice].dia = obtenerDia(tareas[indice].mes, tareas[indice].anio);
                        break;

                    case 4:
                        tareas[indice].anio = obtenerAnio();
                        tareas[indice].mes = obtenerMes(tareas[indice].anio);
                        tareas[indice].dia = obtenerDia(tareas[indice].mes, tareas[indice].anio);
                        break;

                    case 5:
                        break;

                    }
                    break;

                case 3:
                    system("CLS");

                    cout << "Ingrese la nueva descripción de la tarea " << tareas[indice].nombre << "." << endl;
                    cout << "La descripción actual es " << tareas[indice].descripcion << "." << endl;

                    cin.ignore();
                    getline(cin, tareas[indice].descripcion);

                    break;

                case 4:
                    system("CLS");

                    cout << "Ingrese el nuevo nombre de la tarea " << tareas[indice].nombre << ": ";
                    cin.ignore();

                    getline(cin, tareas[indice].nombre);

                    system("CLS");
                    cout << "¿Qué desea cambiar de la fecha?\n";
                    cout << "--------------------\n";
                    cout << "1. Modificar año.\n";
                    cout << "2. Modificar mes.\n";
                    cout << "3. Modificar día.\n";
                    cout << "4. Modificar 2 o más parámetros.\n";
                    cout << "5. Salir.\n";

                    cin >> opcionFecha;

                    while (cin.fail() || opcionFecha > 5 || opcionFecha < 1)
                    {
                        cin.clear();
                        cin.ignore();
                        cout << "\nIngrese una opción válida. Intente nuevamente: ";
                        cin >> opcionFecha;
                    }

                    switch (opcionFecha)
                    {
                    case 1:
                        tareas[indice].anio = obtenerAnio();
                        break;

                    case 2:
                        tareas[indice].mes = obtenerMes(tareas[indice].anio);
                        break;

                    case 3:
                        tareas[indice].dia = obtenerDia(tareas[indice].mes, tareas[indice].anio);
                        break;

                    case 4:
                        tareas[indice].anio = obtenerAnio();
                        tareas[indice].mes = obtenerMes(tareas[indice].anio);
                        tareas[indice].dia = obtenerDia(tareas[indice].mes, tareas[indice].anio);
                        break;

                    case 5:
                        break;

                    }

                    system("CLS");

                    cout << "Ingrese la nueva descripción de la tarea " << tareas[indice].nombre << "." << endl;
                    cout << "La descripción actual es " << tareas[indice].descripcion << "." << endl;
                    cin.ignore();

                    getline(cin, tareas[indice].descripcion);
                    break;

                case 5:
                    cout << "Modificar tarea.\n";
                    cout << "--------------------\n";
                    indiceTarea(tareas, contadorTarea);
                    break;

                case 6:
                    decision = 1;
                    break;

                default:
                    cout << "Ingrese una opción válida.";
                    break;
                }

            }
    }
    else {
        cout << "Primero debe ingresar alguna tarea.\n";
        system("PAUSE");
    }
}

void buscarFechaTarea(Tarea tareas[], int contadorTarea) {
    string repeticion = "s";
    int tareasCoinciden = 0,  diaTarea, mesTarea, anioTarea, i;
    system("CLS");

    while(repeticion == "s") {
        tareasCoinciden = 0;
        cout << "Ingrese el dia a buscar de la tarea: ";
        cin >> diaTarea;
        for (i = 0; i < contadorTarea; i++)
        {
            if ( tareas[i].dia == diaTarea) {
                cout << "Ingrese el mes a buscar de la tarea: ";
                cin >> mesTarea;
                while (cin.fail() || mesTarea < 1 || mesTarea > 12){
                    cin.clear();
                    cin.ignore();
                    cout << "Ingrese un mes válido. Intente nuevamente: ";
                    cin >> mesTarea;
                }
                if ( tareas[i].mes == mesTarea) {
                    cout << "Ingrese el anio a buscar de la tarea: ";
                    cin >> anioTarea;
                    while (cin.fail() || anioTarea <= 0 ){
                        cin.clear();
                        cin.ignore();
                        cout << "Ingrese un anio válido. Intente nuevamente: ";
                        cin >> anioTarea;
                    }
                    if (tareas[i].anio == anioTarea)
                    {
                        cout << endl << "Tareas que coinciden con la busqueda. \n";
                        cout << endl << "Nombre de la tarea "<< i+1 << ": " << tareas[i].nombre << endl;
                        cout << "Descripcion: " << tareas[i].descripcion << endl;
                        cout << "Estado: " << tareas[i].estado << endl;
                        cout << "Curso: " << tareas[i].curso << endl;
                        cout << "Codigo: " << tareas[i].codigoTarea << endl;
                        cout << "Año de entrega: " << tareas[i].anio << endl;
                        cout << "Mes de entrega: " << tareas[i].mes << endl;
                        cout << endl;
                        tareasCoinciden++;
                    }

                }
            }
        }

        if (tareasCoinciden == 0) {
            cout << endl << "Ninguna tarea coincide con el criterio de búsqueda.\n";
        }

        cout << "¿Desea buscar otra tarea? s/n: ";
        cin >> repeticion;
        cout << endl;

    }
}

void cambiarEstadoTarea(Tarea tareas[], int contadorTarea) {
    int i, opcion, indice, decision = 0, caracteres;
    float nota;
    string estado, lower;

    system("CLS");

    if (contadorTarea > 0) {

        cout << "Modificar el estado de una tarea.\n";
        cout << "--------------------\n";

        indice = indiceTareaEstado(tareas, contadorTarea) - 1;

        if (indice < 0) {
            decision = 1;
        }


        while (decision == 0)
        {
            system("CLS");

            cout << "Opciones.\n";
            cout << "--------------------\n";

            cout << "\n1. Cambiar el estado.\n";
            cout << "2. Cambiar de tarea.\n";
            cout << "3. Salir.\n";

            cin >> opcion;
            while (cin.fail() || opcion < 0  || opcion > 3)
            {
                cin.clear();
                cin.ignore();
                cout << "\nIngrese una opcion correcta: ";
                cin >> opcion;
            }


            switch (opcion)
            {
            case 1:
                system("CLS");
                cout << "¿Ha entregado la tarea " << "'" << tareas[indice].nombre << "'" << "?: ";
                cin >> estado;


                caracteres = estado.length();

                for (i = 0; i < caracteres; i++) {
                    estado[i] = tolower(estado[i]);
                }

                while (estado != "entregada" && estado != "no entregada" && estado != "si" && estado != "no")
                {
                    cin.clear();
                    cin.ignore();
                    cout << "\nIngrese si/no, entregada/no entregada: ";
                    cin >> estado;
                }

                if (estado == "entregada" || estado == "si")
                {
                    tareas[indice].estado = "Entregada";
                    cout << "La tarea ha sido entregada, ahora ingrese la nota ( 0 a 5 ): ";
                    cin >> nota;

                    while (cin.fail() || nota < 0  || nota > 5)
                    {
                        cin.clear();
                        cin.ignore();
                        cout << "\nIngrese una nota correcta: ";
                        cin >> nota;
                    }

                    cout << "\nLa nota de " << tareas[indice].nombre << " es " << nota << "." << endl;

                    tareas[indice].nota = nota;
                }

                else {
                    tareas[indice].estado = "No Entregada";
                    cout << "La tarea " << tareas[indice].nombre << " no ha sido entregada. La nota es 0.\n";
                    tareas[indice].nota = 0;
                }

                decision = 1;

                system("PAUSE");
                break;

            case 2:
                indice = indiceTareaEstado(tareas, contadorTarea) - 1;
                break;

            case 3:
                decision = 1;
                break;

            default:
                break;
            }

        }
    }
    else {
        cout << "Primero debe ingresar alguna tarea.\n";
        system("PAUSE");
    }

}


//Funciones adicionales

string obtenerNombre(string aPedir){
    string nombre;
    cout << "Ingrese su(s) "<< aPedir <<"(s): ";
    getline(cin, nombre);
    while (!validarNombre(nombre)){
        cin.clear();
        cin.ignore();
        cout << "El " << aPedir << " no puede llevar números\nIntente otra vez: ";
        getline(cin, nombre);
    }

    return nombre;
}


string obtenercodigo(){
    string codigo;
    bool soloNumeros = true;

    cout << "Ingrese el código de estudiante (solo recibe números enteros): ";
    do{
        cin >> codigo;
        //Verificar que se hayan ingresado digitos
        for (int i = 0; i < codigo.length(); i++){
            if(!isdigit(codigo[i])){
                cout << "Solamente recibe codigos como números naturales, ingrese nuevamente el código: ";
                soloNumeros = false;
                break;
            }else{
                soloNumeros = true;
            }
        }
    }while(!soloNumeros);

    return codigo;
}

int indiceTarea(Tarea tareas[], int contadorTarea) {
    int i, opcion, tareaModificar, indiceTarea;
    cout<<contadorTarea;
    cout << "\nEscoja la tarea donde se realizarán los cambios.\n"<<contadorTarea<<endl;

    for (i=0; i < contadorTarea; i++) {
        cout << endl << i+1 << ". " << tareas[i].nombre << endl;
    }

    cout << endl;
    cin >> tareaModificar;
    while (cin.fail() || tareaModificar < 1 || tareaModificar > contadorTarea)
    {
        cin.clear();
        cin.ignore(200, '\n');
        cout << "\nIngrese una tarea válida. Intente nuevamente: ";
        cin >> tareaModificar;
    }

    return tareaModificar;
}

int indiceTareaEstado(Tarea tareas[], int contadorTarea) {
    int i, opcion, tareaModificar, indiceTarea, tareasSinModificar = 0;
    do
    {
        cout << "\nEscoja la tarea donde se realizarán los cambios.\n";

        for (i=0; i < contadorTarea; i++) {
            cout << endl << i+1 << ". " << tareas[i].nombre << endl;
        }

        cout << endl;
        cin >> tareaModificar;
        while (cin.fail() || tareaModificar < 1 || tareaModificar > contadorTarea)
        {
            cin.clear();
            cin.ignore(200, '\n');
            cout << "\nIngrese una tarea válida. Intente nuevamente: ";
            cin >> tareaModificar;
        }

        if (tareas[tareaModificar-1].estado != "En proceso")
            {
                system("CLS");
                if (tareas[tareaModificar-1].estado == "Entregada")
                {
                    cout << "La tarea ya ha sido entregada." << "\nLa nota es " << tareas[tareaModificar-1].nota << ".\n";
                }
                else {
                    cout << "La tarea no fue entregada." << "\nLa nota es " << tareas[tareaModificar-1].nota << ".\n";
                }

                for (i = 0; i < contadorTarea; i++)
                {
                    if (tareas[i].estado == "En proceso")
                    {
                        tareasSinModificar++;
                    }

                }


                if ( tareasSinModificar == 0) {
                    cout << "Agregue otra tarea para realizar cambios en el estado.\n";
                    system("PAUSE");
                    tareaModificar = 0;
                    break;
                }

            }
    } while (tareas[tareaModificar-1].estado != "En proceso");

    return tareaModificar;

}

string obtenerCorreo (){
  string correo;
  int contador=0;
  do{
    if (contador==0){
      cout<<"Ingrese correo: ";
        getline(cin, correo);
    }else{
      cout<<"El correo no es válido, vuelva a ingresar el correo: ";
        getline(cin, correo);
    }
    contador++;
  }while (!validarcorreo(correo));
  return correo;
}

bool validarcorreo(string correo){
    string arroba="@";
  string punto=".";
  string espacio=" ";
  bool var=false;
  int condicion,cantidad=100;

    int cantletras=correo.length();
    for (int i=0;i<cantletras;i++){
      if (correo[i]==espacio[0]){
        condicion=1;
        break;
    }else{
      condicion=0;
    }
  }
  if (condicion == 0){
        for (int i = 0; i < cantletras; i++){
            if (correo[i] == arroba[0]){
              if (i==0){		//Arroba no puede ser inicio del correo
                break;
        }else{
                  for (int j = i; j < cantletras; j++){	//El for empieza a contar desde la posicion del arroba hasta encontrar un punto
                      if (correo[j] == punto[0]){

                        if (j-i<=1){	//El arroba y el punto no pueden ir seguidos
                          break;
              }else{
                if (cantletras-1!=j){
                  var=true;
                            break;
                }

              }

                      }
                  }
              }
            }
        }
    }else{
  }
  return var;    
}

string crearCodigo(Estudiante &estudiante, string codigoMateria){
    string codigo;
    Cursos materia;

    //Validar un código valido
    do{
        for(int i = 0; i < estudiante.numMateriasInscritas; i++){
            if (estudiante.materias[i].codigo == codigoMateria){ 
                materia = estudiante.materias[i];
                codigo = materia.codigo + to_string(materia.cantidad);
                //Incrementar la cantidad de tareas de esa materia
                estudiante.materias[i].cantidad++;
                break;
            }
        }
            cout << "Ingrese un código valido, intente nuevamente: ";
            cin >> codigoMateria;
    } while (true);


    materia.cantidad ++;


    return codigo;
}


int obtenerAnio(){

    int anio;
    string respuesta;

    //Preguntar si la fecha de entrega es este año
    cout << "¿La tarea se entrega este año? s/n: ";
    cin >> respuesta;

    while(respuesta != "s" && respuesta != "n"){
        cout << "Digite 's' o 'n', ningún otro valor: ";
        cin >> respuesta;
    }

    if (respuesta == "s"){
        anio = 2024;
    }else{
        cout << "Ingrese el año de entrega: ";
        cin >> anio;
        while (cin.fail() || anio > 2023){
            cin.clear();
            cin.ignore();
            cout << "Ingrese una año que aún no haya pasado, intente nuevamente: ";
            cin >> anio;
        }
    }

    return anio;
}

int obtenerMes(int anio){
    int mes;
    int mesMinimo= 0;
    string meses[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo","Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    cout << "\nSeleccione el mes de entrega: \n";
    cout << endl;
    for (int i = 0; i< 12; i++){
        cout << i+1 << ". " << meses[i] << "\n";
    }

    //Si el año es 2024, el mes debe ser mayor a 5
    if (anio == 2024){
        mesMinimo = 6;
        cout << "\nRecuerda que el mes de entrega debe partir desde junio" <<endl ;
    }

    cout << "Ingrese el número del mes: ";
    cin>>mes;
    int x=0;

    while (cin.fail() || mes < mesMinimo || mes > 12){
        cin.clear();
        cin.ignore(200, '\n');
        cout << "Ingrese un mes válido. Intente nuevamente: ";
        cin>>mes;
    }

    return mes;
}
int obtenerDia(int mes, int anio){
    int dia, ultimoDiaDelMes;

    //Obtener último día del mes
    switch(mes){
        case 1 || 3 || 5 || 7 || 8 || 10 || 12:
            ultimoDiaDelMes = 31;

            break;
        case 2:
            //Revisar si el año es bisiesto
            if (anio % 4 == 0){
                ultimoDiaDelMes = 29;
            }else{
                ultimoDiaDelMes = 28;
            }

            break;
        default:
            ultimoDiaDelMes = 30;
    }

    cout << "\nIngrese el día de entrega: ";
    cin >> dia;
    while (cin.fail() || dia < 1 || dia > ultimoDiaDelMes){
        cin.clear();
        cin.ignore();
        cout << "\nAgo salió mal, solo puedes ingresar números entre 1 y " << ultimoDiaDelMes << " , intenta otra vez: ";
        cin >> dia;
    }

    return dia;
}

bool validarNombre(string nombre){
    bool nombreValido = true;

    for (int i = 0; i < nombre.length(); i++){
        if (isdigit(nombre[i])){
            nombreValido = false;
            break;
        }
    }

    return nombreValido;
}

int eliminarTarea(Tarea tarea[],Tarea TareaEliminada[], int contadorTarea, int contadorEliminado){
    int numTarea, condicionEliminar;
    system("CLS");
    if (contadorTarea==0){  //Condicion si no existen tareas para borrar
        cout << "No tiene ninguna tarea actualmente\n ";
        system("PAUSE");
        condicionEliminar=0;
    }else{  //Condición si existen tareas para borrar
        cout<<"Las tareas creadas anteriormente son: "<< endl << endl;
        for (int i=0; i<contadorTarea;i++){     //Impresión del número de la tarea con la tarea. Ejemplo: Tarea 1: cartelera
            if (tarea[i].nombre!=""){
                cout << "       Tarea " << i+1 <<": " << tarea[i].nombre<<endl;   
            }
        }
        cout<<"\nIngrese el número de la tarea que deséa eliminar: ";
        do{     //Validación en caso de que el usuario un número de una tarea que no exista o ingrese letras
            cin >> numTarea;
            if (cin.fail()){
                cin.clear();
                cin.ignore(200, '\n');
            }else{}
            if ( numTarea<=contadorTarea && numTarea>0 ){
                break;
            }
            cout << "La tarea que ingresaste es inválida o no existe.\nVuelva a ingresar el número de la tarea: ";
        }while (true);

        numTarea--; //Restamos 1 al número de la tarea para convertirlo en el índice de tarea[i] 

        //Impresión de la tarea eliminada
        cout << "\nLa tarea que eliminaste es: "<< endl;
        cout << endl << "       Tarea " << numTarea+1 << ": " << tarea[numTarea].nombre;

        TareaEliminada[contadorEliminado]=tarea[numTarea];  //Asignamos un nuevo vector donde en un futuro se establecerán todas las tareas eliminadas

        for (int i = numTarea; i < contadorTarea ; i++) {   //for para que desde la tarea que se elimine todas las tareas se corran un puesto para atras
            if (i==contadorTarea-1){
            }else{
                tarea[i] = tarea[i + 1];
            }
        }   

        //Ejemplo de la asignación al final del for: se elimina tarea 3. Entonces la tarea 4 pasará a ser 3, la tarea 5 pasará a la 4 y asi sucesivamente
        //En el último ciclo del for, el bucle no hará nada, para que se deje la última tarea quieta, hasta acá la tarea n y la tarea n-1 serán iguales

        condicionEliminar=1;
        //Finalmente en el main() se declará que el contador eliminado(contador que cuenta cuantas tareas se han eliminado) aumenta uno, y el contador de las tareas disminuye en uno
    
        system("PAUSE");
    }
    //En el main hay una condición para que se sume uno al contador eliminado y reste uno al contador de tareas, y este es el valor de condicionEliminar, y para esto lo retornamos
    return condicionEliminar;
}

void historialTareas(Tarea tarea[],Tarea TareaEliminada[],int contadorTarea,int contadorEliminado, Estudiante &estudiante){

    //Para esta función es importante tener en cuenta que anteriormente ya habíamos validado que el ingreso del código del curso en una tarea, concuerde con algún curso.

    system("CLS");
    string buscador;    //Se declara buscador, porque ahorita se le pedirá al usuario que materia quiere ver el historial, preguntandole el código de la materia
    int numTarea=0, contadorTareasEliminadas=0, contadorTareasActuales=0;
    if (contadorTarea==0 && contadorEliminado==0){  //Condición si no existe ninguna tarea, ni ninguna tarea eliminada
        cout << "No ha ingresado ninguna tarea. Por lo tanto no tiene ningún historial.\n\n";
        system("PAUSE");
    }else if(contadorTarea==0 && contadorEliminado!=0){ //Condición si no existe ninguna tarea, pero si has eliminado tareas
        cout<< "No tienes ninguna tarea actualmente, sin embargo, puedes buscar que tareas has eliminado en las siguientes materias: ";
        cout<<endl<<endl;
        cout << left << setw(20) << "Materia" << setw(10) << "Código" << endl;

        for(int i = 0; i < estudiante.numMateriasInscritas ; i++) {	//impresión de nombre y código de materia
            cout << setw(20) << left << estudiante.materias[i].nombre << setw(10) << left << estudiante.materias[i].codigo << endl;
        }

        //Ingreso del código de la materia por el usuario
        cout<< "\n\nIngrese el código de la materia al cual deséas saber que tareas has eliminado: " ;

        //Validación del ingreso para que concuerde el código que ingresa el usuario y los códigos que tienen las materias
        do{
            cin>>buscador;
            int j;
            for (int i=0; i<estudiante.numMateriasInscritas;i++){
                if (buscador==estudiante.materias[i].codigo){
                    j=1;
                    break;
                }
            }
            if (j==1){
                break;
            }
            cout<<endl<<"El código que ingreso no pertenece a ninguna materia."<<endl<<"Ingrese nuevamente el código de la materia: ";
        }while (true);

        numTarea=0; //contador para imprimir el número de la tarea, es decir tarea 1 y asi sucesivamente.
        cout<< endl<<endl<<"Tareas eliminadas: \n\n";

        //Se hace un for para que pase por todas las tareas eliminadas
        for (int i=0;i<contadorEliminado;i++){
            if (buscador==TareaEliminada[i].curso){ //Condición en caso de que el buscador sea igual al código de curso que le asignamos al crear la tarea
                numTarea++;
                cout<<"Tarea "<<numTarea<<": "<< TareaEliminada[i].nombre<<endl;
                contadorTareasEliminadas++;
            }  
        }
        //Si ningún caso en el for cumplirá la condición no se imprimira nada
        cout<<endl<<endl;
        //Condicion en caso de que en la materia ingresada no se haya eliminado ninguna tarea
        if (contadorTareasEliminadas==0){
            cout<<"No has eliminado ninguna tarea en esta materia.\n\n";
        }
        system("PAUSE");
    }else{  //El código de esta condición tiene una lógica muy similar a la de la condición anterior
        
        cout<< "Las materias con su código respectivamente son: "<<endl<<endl;
        cout << left << setw(20) << "Materia" << setw(10) << "Código" << endl;
        for(int i = 0; i < estudiante.numMateriasInscritas ; i++) {	//impresión de nombre y código de materia
            cout << setw(20) << left << estudiante.materias[i].nombre << setw(10) << left << estudiante.materias[i].codigo << endl;
        }

        //Ingreso de código de la materia
        cout<< "\n\nIngrese el código de la materia al cual desea saber que tareas tienes actualmente: " ;
        //Validación del código de la materia
        do{
            cin>>buscador;
            for (int i=0; i<estudiante.numMateriasInscritas;i++){
                if (buscador==estudiante.materias[i].codigo){
                    break;
                }
            }
            cout<<endl<<"El código que ingreso no pertenece a ninguna materia."<<endl<<"Ingrese nuevamente el código de la materia: ";
        }while (true);

        cout<<endl<<endl;
        //Impresión: historial total de la <materia> 
        for (int i=0;i<estudiante.numMateriasInscritas;i++){
            if (buscador==estudiante.materias[i].codigo){
                cout<< "El historial total de tareas en la materia "<<estudiante.materias[i].nombre<<" es: "<<endl<<endl<<endl;
            }
        }

        //Impresión de cada tarea
        cout<<"Tareas: "<<endl<<endl;
        for (int i=0;i<contadorTarea;i++){
            if (buscador== tarea[i].curso){
                numTarea++;
                cout<<"Tarea "<<numTarea<<": "<< tarea[i].nombre<<endl;
                cout<<"Fecha de entrega: "<<tarea[i].dia<<"/"<<tarea[i].mes<<"/"<<tarea[i].anio<<endl;
                cout<<"Estado actual: "<<tarea[i].estado<<endl<<endl;
                contadorTareasActuales++;
            }
        }
        //Impresión si no ha creado ninguna tarea en esa materia o si ha eliminado todas las tareas en esa materia
        if (contadorTareasActuales==0){
            cout<< "\n\nNo tienes ninguna tarea en esta materia: ";
        }
        numTarea=0;

        //Impresión de las tareas eliminadas
        cout<< endl<<endl<<"Tareas eliminadas: "<<endl<<endl;
        for (int i=0;i<contadorEliminado;i++){
            if (buscador==TareaEliminada[i].curso){
                numTarea++;
                cout<<"Tarea "<<numTarea<<": "<< TareaEliminada[i].nombre<<endl;
                contadorTareasEliminadas++;
            } 
        }

        //Condición en caso de que no haya eliminado ninguna tarea en esa materia
        cout << "\n\n";
        if (contadorTareasEliminadas==0){
            cout << "\n\nNo tienes ninguna tarea eliminada en esta materia.\n\n ";
        }
        system("PAUSE");
    }
}