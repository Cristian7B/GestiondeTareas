/*
Sistema de gestión de tareas
Estudiantes: Cristian Camilo Bonilla, Nicolas Velasco y Jesús Antonio Murcia
Fecha: 5 de Junio
*/


#include <iostream>
#include <locale.h>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h>


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


//PROTOTIPADO DE LAS FUNCIONES DEL PROGRAMA

void registrarEstudiante(Estudiante &estudiante);
void registrarMaterias(Estudiante &estudiante); 

// Funciones para los ficheros
bool leerEstudianteDesdeFichero(Estudiante &estudiante);
void guardarEstudianteEnFichero(Estudiante &estudiante);
bool leerTareasDesdeFichero(Tarea tareas[], int &contadorTarea);
void guardarTareasEnFichero(const Tarea tareas[], int contadorTarea);
void guardarTareasEliminadasFichero(Tarea ta_eliminadas[], int contadorEliminado);
bool leerTareasEliminadasDesdeFichero(Tarea tareas_eliminadas[], int &contadorEliminado);

// Funciones de las tareas
int crearTarea(Estudiante &estudiante, Tarea tareas[], int contadorTarea);
int crearNTareas(Estudiante &estudiante, Tarea tareas[], int contadorTarea);
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

//Colores fuente

void cambiarColorTexto(int color); //Color es el código de color ANSI

main() { 
    //Vectorizacion de los struct
    Tarea tareas[100], tareaEliminada[100];
    Cursos materias[15];
    Estudiante perfil;

    setlocale(LC_ALL, "spanish");
    system("cls");

    //Variales globales
    int opcion = 0, contadorTarea = 0, contadorEliminado=0, condicionEliminar=0;    
    bool decision = true;

    cambiarColorTexto(8);

    cout << "+%@@@@@%%%%%###***+++==----=*@@*:.      \n";
    cout << "@@@#                  .=%@#=.    \n";
    cout << "@@@@@*:       .......:::::-----=#@@@*-. \n";
    cout << "@@@@@@@%####%%%%%@@@@@@@@@@@@@@@@@@@@@: \n";
    cout << "@@@@@@@@@%%###****+++===----:::::..+@@- \n";
    cout << "@@@@@@@%.                          -@@- \n";
    cout << "@@@@@@@%.   "; 
    cambiarColorTexto(5);
    cout << "..::::-.     -+++**=   ";
    cambiarColorTexto(8);
    cout<<"-@@- \n";
    cout << "@@@@@@@%.   "; 
    cambiarColorTexto(5); 
    cout << "+%@@@@@%-   .-+@@@-:   "; 
    cambiarColorTexto(8);
    cout << "-@@- \n";
    cambiarColorTexto(8);
    cout << "@@@@@@@%.   "; 
    cambiarColorTexto(5); 
    cout << "..%@@@@@@=     #@%     "; 
    cambiarColorTexto(8);
    cout << "-@@- \n";
    cambiarColorTexto(8);
    cout << "@@@@@@@%.     "; 
    cambiarColorTexto(5); 
    cout << "%@@@@@@@+.   #@%.    "; 
    cambiarColorTexto(8);
    cout << "-@@- \n";
    cambiarColorTexto(8);
    cout << "@@@@@@@%.    "; 
    cambiarColorTexto(5); 
    cout << ".%@@-%@@@@*.  #@%.    "; 
    cambiarColorTexto(8);
    cout << "-@@- \n";
    cambiarColorTexto(8);
    cout << "@@@@@@@%.    "; 
    cambiarColorTexto(5); 
    cout << ".%@@..#@@@@#. #@%.    "; 
    cambiarColorTexto(8);
    cout << "-@@- \n";
    cambiarColorTexto(8);
    cout << "@@@@@@@%.    "; 
    cambiarColorTexto(5); 
    cout << ".%@@. .*@@@@%:#@%.    "; 
    cambiarColorTexto(8);
    cout << "-@@- \n";
    cambiarColorTexto(8);
    cout << "@@@@@@@%.    "; 
    cambiarColorTexto(5); 
    cout << ".%@@.  .+@@@@@@@%.    "; 
    cambiarColorTexto(8);
    cout << "-@@- \n";
    cambiarColorTexto(8);
    cout << "@@@@@@@%.    "; 
    cambiarColorTexto(5); 
    cout << ".%@@.    =@@@@@@%.    "; 
    cambiarColorTexto(8);
    cout << "-@@- \n";
    cambiarColorTexto(8);
    cout << "#@@@@@@%.    "; 
    cambiarColorTexto(5); 
    cout << " %@@:     -@@@@@%.    "; 
    cambiarColorTexto(8);
    cout << "-@@- \n";
    cambiarColorTexto(8);
    cout << ".*@@@@@%.   "; 
    cambiarColorTexto(5); 
    cout << "-+@@@%*:    :#@@@*.    "; 
    cambiarColorTexto(8);
    cout << "-@@- \n";
    cambiarColorTexto(8);
    cout << " .=@@@@%.  "; 
    cambiarColorTexto(5); 
    cout << ".-=--:::.      ::.      "; 
    cambiarColorTexto(8);
    cout << "-@@- \n";
    cambiarColorTexto(8);
    cout << "   :#@@%.        .....::::::---===+%@@- \n";
    cout << "    .+@@%*####%%%%@@@@@@@@@@@@@@@@@@@#. \n";
    cout << "      -%@@@@@@%%%%###***+++===----::.   \n";
    cout << endl;
    system("PAUSE");
    system("CLS");


    if (!leerEstudianteDesdeFichero(perfil)){
        cambiarColorTexto(15);
        cout << "Es hora de registrar tu perfil.\n";
        registrarEstudiante(perfil);
        guardarEstudianteEnFichero(perfil);
    }else{
        cambiarColorTexto(10);
        cout << "Perfil cargado exitosamente.\n";
        cambiarColorTexto(14);
        cout << "Bienvenido " << perfil.nombre << ".\n";
        system("PAUSE");
    }

    leerTareasEliminadasDesdeFichero(tareaEliminada, contadorEliminado);

    if (leerTareasDesdeFichero(tareas, contadorTarea) && contadorTarea > 0 && leerTareasEliminadasDesdeFichero(tareaEliminada, contadorEliminado)){
        system("CLS");
        cambiarColorTexto(2);
        cout << contadorTarea << " Tarea(s) han sido cargadas exitosamente.\n";
        cambiarColorTexto(4);
        cout << contadorEliminado << " Tarea(s) eliminadas han sido cargadas exitosamente.\n";
        system("PAUSE");
    }


    // Menú de opciones
    while (decision) {
        system("CLS");
        cambiarColorTexto(14);
        cout << "Menú de tareas.\n";

        cambiarColorTexto(15);
        cout << "\nEdición\n";
        cout << "--------------------\n";
        cambiarColorTexto(6);
        cout << "\t 1. Crear tarea.\n";
        cout << "\t 2. Crear n tareas.\n";
        cout << "\t 3. Modificar tarea.\n";
        cout << "\t 4. Cambiar estado de tarea.\n";
        cout << "\t 5. Eliminar tarea.\n";

        
        cambiarColorTexto(15);
        cout << "\nConsultas\n";
        cout << "--------------------\n";
        cambiarColorTexto(5);
        cout << "\t 6. Consultar el historial de tareas de una materia.\n";
        cout << "\t 7. Consultar tareas para una fecha específica.\n";
        cambiarColorTexto(4);
        cout << "\n0. Salir del programa.\n";
        cambiarColorTexto(15);
        cout << "\nOpcion: ";
        cambiarColorTexto(7);
        cin >> opcion;

        switch (opcion) {
            case 1:
                contadorTarea = crearTarea(perfil, tareas, contadorTarea);
                system("pause");
                guardarTareasEnFichero(tareas, contadorTarea);
                break;

            case 2:
                contadorTarea = crearNTareas(perfil, tareas, contadorTarea);
                system("pause");
                guardarTareasEnFichero(tareas, contadorTarea);
                break;

            case 3:
                modificarTarea(tareas, contadorTarea);
                guardarTareasEnFichero(tareas, contadorTarea);
                break;

            case 4:
                cambiarEstadoTarea(tareas, contadorTarea);
                guardarTareasEnFichero(tareas, contadorTarea);
                break;

            case 5:
                condicionEliminar = eliminarTarea( tareas, tareaEliminada,  contadorTarea,  contadorEliminado);
                if (condicionEliminar == 0){
                }else{
                    contadorTarea--;
                    cout << contadorEliminado<< endl;
                    contadorEliminado++;
                    cout << contadorEliminado<< endl;
                }
                
                guardarTareasEnFichero(tareas, contadorTarea);
                guardarTareasEliminadasFichero(tareaEliminada, contadorEliminado);
                break;
            case 6:
                historialTareas( tareas, tareaEliminada, contadorTarea, contadorEliminado, perfil);
                break;

            case 7:
                buscarFechaTarea(tareas, contadorTarea);
                break;

            case 0:
                decision = false;
                break;

            default:
                system("cls");
                cambiarColorTexto(4);
                cout << "\nDigite una opción válida, será redirigido automáticamente al menú principal.\n\n";
                system("PAUSE");
                break;
        }
    }

}

//Colores

void cambiarColorTexto(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Funciones
void registrarEstudiante(Estudiante &estudiante) {
    // Solicitar nombre, apellido, correo y codigo
    cout << "--------------------\n";
    cambiarColorTexto(6);
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

    cambiarColorTexto(15);
    cout << "\nMaterias.\n";
    cout << "--------------------";
    cambiarColorTexto(6);
    cout << "\nEs momento de registrar tus materias.\n";

    // Solicitar los datos de las materias inscritas
    while (continuar != "n" && estudiante.numMateriasInscritas < 15) {

        cin.ignore();
        cambiarColorTexto(6);
        cout << "\nIngresa el nombre de la materia: ";
        do{
            cambiarColorTexto(7);
            getline(cin, estudiante.materias[numMateriasRegistradas].nombre);
            cambiarColorTexto(4);
            if (numMateriasRegistradas != 0){
                for (int i=0; i<numMateriasRegistradas; i++){
                    if (estudiante.materias[i].nombre == estudiante.materias[numMateriasRegistradas].nombre){
                        cout << "Dos materias no pueden llamarse igual, ingrese un nuevo nombre: ";
                        materiaValida = false;
                    }               
                }
            }
        }while (!materiaValida);

        cambiarColorTexto(6);
        cout << "Ahora registra el código de la materia " << estudiante.materias[numMateriasRegistradas].nombre << ": ";
        do{
            cambiarColorTexto(7);
            getline(cin, estudiante.materias[numMateriasRegistradas].codigo);
            cambiarColorTexto(4);
            if (numMateriasRegistradas !=0){
                for (int i=0; i<numMateriasRegistradas; i++){
                    if ( estudiante.materias[i].codigo == estudiante.materias[numMateriasRegistradas].codigo){
                        cout << "Dos materias no pueden tener el mismo código, ingrese uno nuevo: ";
                        materiaValida = false;
                    }               
                }
            }
        }while (!materiaValida);

        cambiarColorTexto(2);
        cout << "\nLa materia se registró como: " << estudiante.materias[numMateriasRegistradas].nombre << endl << endl;
        cambiarColorTexto(15);
        cout << "El código de " << estudiante.materias[numMateriasRegistradas].nombre << " es " << estudiante.materias[numMateriasRegistradas].codigo;



        // Definir la cantidad de tareas para cada materia
        estudiante.materias[numMateriasRegistradas].cantidad = 1;
        numMateriasRegistradas++;

        // Preguntar por si se quiere dejar de registrar materias
        cambiarColorTexto(15);
        cout << "\n\n--------------------\n";
        cambiarColorTexto(6);
        cout << "¿Desea inscribir más materias? s/n: ";
        cambiarColorTexto(7);
        cin >> continuar;

        while (continuar != "s" && continuar != "n") {
            cambiarColorTexto(4);
            cout << "Digite 's' o 'n', ningún otro valor: ";
            cambiarColorTexto(7);
            cin >> continuar;
        }
    }


    // Almacenar el número de materias registradas
    estudiante.numMateriasInscritas += numMateriasRegistradas;
}

bool leerEstudianteDesdeFichero(Estudiante &estudiante)
{
    ifstream fichero("estudiante.txt");
    cambiarColorTexto(7);
    if (fichero.is_open())
    {   
        getline(fichero, estudiante.nombre);
        getline(fichero, estudiante.apellido);
        getline(fichero, estudiante.correo);
        fichero >> estudiante.codigo;
        fichero >> estudiante.numMateriasInscritas;
        fichero.ignore(); 

        for (int i = 0; i < estudiante.numMateriasInscritas; ++i)
        {
            getline(fichero, estudiante.materias[i].nombre);
            getline(fichero, estudiante.materias[i].codigo);
            fichero >> estudiante.materias[i].cantidad;
            fichero >> estudiante.materias[i].cantidadMaterias;
            fichero.ignore(); 
        }
        fichero.close();
        return true;
    }
    return false;
}

void guardarEstudianteEnFichero(Estudiante &estudiante)
{
    ofstream fichero("estudiante.txt");
    if (fichero.is_open())
    {
        fichero << estudiante.nombre << endl;
        fichero << estudiante.apellido << endl;
        fichero << estudiante.correo << endl;
        fichero << estudiante.codigo << endl;
        fichero << estudiante.numMateriasInscritas << endl;

        for (int i = 0; i < estudiante.numMateriasInscritas; ++i)
        {
            fichero << estudiante.materias[i].nombre << endl;
            fichero << estudiante.materias[i].codigo << endl;
            fichero << estudiante.materias[i].cantidad << endl;
            fichero << estudiante.materias[i].cantidadMaterias << endl;
        }
        fichero.close();
    }
}



int crearTarea(Estudiante &estudiante, Tarea tareas[], int contadorTarea){
    bool codigoValido = false;
    system("CLS");

    cin.ignore();

    cambiarColorTexto(15);
    cout << "Tarea " << contadorTarea + 1<< endl;
    cout << "--------------------\n";
    cambiarColorTexto(6);
    cout << "Ingresa el nombre de la tarea: ";
    cambiarColorTexto(7);

    getline(cin, tareas[contadorTarea].nombre);
    cambiarColorTexto(6);

    cout << "Ingresa la descripción de la tarea: ";
    cambiarColorTexto(7);

    getline(cin, tareas[contadorTarea].descripcion);
    cambiarColorTexto(6);

    cout << "Ingrese el código del curso al que pertenece la materia, las materias son: \n";
    cout << endl;

    cambiarColorTexto(15);
    cout << left << setw(20) << "Materia" << setw(10) << "Codigo" << endl;
    cambiarColorTexto(8);
    for(int i = 0; i < estudiante.numMateriasInscritas ; i++) {//impresion de nombre y codigo de materia
        cout << setw(20) << left << estudiante.materias[i].nombre << setw(10) << left << estudiante.materias[i].codigo << endl;
    }
    cambiarColorTexto(6);
    cout << endl << "Ingrese código: ";

    do{ //Validación del ingreso del codigo del curso en la tarea
        cambiarColorTexto(7);
        getline(cin, tareas[contadorTarea].curso);
        for (int i=0; i< estudiante.numMateriasInscritas; i++){
            if ( tareas[contadorTarea].curso == estudiante.materias[i].codigo){
                codigoValido = true;
                break;
            }
        }
        if (!codigoValido){
            cambiarColorTexto(4);
            cout << "El código que ingreso no pertenece a ninguna materia, ingrese de nuevo el código: ";
        }
    }while (!codigoValido);

    cambiarColorTexto(15);

    cout << "\nFecha de entrega de la tarea.\n";
    cout << "--------------------\n";

    //Fechas
    
    tareas[contadorTarea].anio = obtenerAnio();
    tareas[contadorTarea].mes = obtenerMes(tareas[contadorTarea].anio);
    tareas[contadorTarea].dia = obtenerDia(tareas[contadorTarea].mes, tareas[contadorTarea].anio);
    tareas[contadorTarea].codigoTarea = crearCodigo(estudiante, tareas[contadorTarea].curso);    
    tareas[contadorTarea].estado = "En proceso";    

    tareas[contadorTarea].estado = "En proceso";

    contadorTarea++;   
    
    system("CLS");
    for (int i=0; i < contadorTarea; i++) {
        cambiarColorTexto(15);
        cout << endl << "Nombre de la tarea "<< i+1 << ": " << tareas[i].nombre << endl;
        cambiarColorTexto(2);
        cout << "Descripcion: " << tareas[i].descripcion << endl;
        cout << "Estado: " << tareas[i].estado << endl;
        cout << "Curso: " << tareas[i].curso << endl;
        cout << "Codigo: " << tareas[i].codigoTarea << endl;
        cambiarColorTexto(6);
        cout << "Año de entrega: " << tareas[i].anio << endl;
        cout << "Mes de entrega: " << tareas[i].mes << endl;
        cout << "Dia de entrega: " <<tareas[i].dia << endl;
        cout << endl;
    }

    //Actualizar fichero
    guardarTareasEnFichero(tareas, contadorTarea);

    return contadorTarea;
}

int crearNTareas(Estudiante &estudiante, Tarea tareas[100], int contadorTarea){

    string repeticion = "s";
    while(repeticion == "s" && contadorTarea < 100) {
        
        contadorTarea = crearTarea(estudiante, tareas, contadorTarea);
        cambiarColorTexto(6);
        cout << "¿Desea agregar otra tarea? s/n: ";
        cambiarColorTexto(7);
        cin >> repeticion;
        cout<<endl<<endl;
        while (repeticion!="s" && repeticion!="n"){ 
                cambiarColorTexto(4);
                cout<<"Solo se puede ingresar 's' o 'n': ";
                cambiarColorTexto(7);
                cin>>repeticion;
                cout<<endl<<endl;
        };
    }

    return contadorTarea;
}


void guardarTareasEnFichero(const Tarea tareas[], int contadorTarea)
{
    ofstream fichero("tareas.txt");
    if (fichero.is_open())
    {
        fichero << contadorTarea << endl;
        for (int i = 0; i < contadorTarea; ++i)
        {
            fichero << tareas[i].nombre << endl;
            fichero << tareas[i].descripcion << endl;
            fichero << tareas[i].codigoTarea << endl;
            fichero << tareas[i].curso << endl;
            fichero << tareas[i].estado << endl;
            fichero << tareas[i].dia << endl;
            fichero << tareas[i].mes << endl;
            fichero << tareas[i].anio << endl;
            fichero << tareas[i].nota << endl;
        }
        fichero.close();
    }
}


bool leerTareasEliminadasDesdeFichero(Tarea ta_eliminadas[], int &contadorEliminado){
    ifstream fichero("tareaselim.txt");
    if (fichero.is_open())
    {
        fichero >> contadorEliminado;
        fichero.ignore(); 

        for (int i = 0; i < contadorEliminado; ++i)
        {
            getline(fichero, ta_eliminadas[i].nombre);
            getline(fichero, ta_eliminadas[i].descripcion);
            getline(fichero, ta_eliminadas[i].codigoTarea);
            getline(fichero, ta_eliminadas[i].curso);
            getline(fichero, ta_eliminadas[i].estado);
            fichero >> ta_eliminadas[i].dia;
            fichero >> ta_eliminadas[i].mes;
            fichero >> ta_eliminadas[i].anio;
            fichero >> ta_eliminadas[i].nota;
            fichero.ignore(); 
        }
        fichero.close();
        return true;
    }
    return false;
}

void guardarTareasEliminadasFichero(Tarea ta_eliminadas[], int contadorEliminado)
{
    ofstream fichero("tareaselim.txt");
    if (fichero.is_open())
    {
        fichero << contadorEliminado << endl;

        for (int i = 0; i < contadorEliminado; ++i)
        {
            fichero << ta_eliminadas[i].nombre << endl;
            fichero << ta_eliminadas[i].descripcion << endl;
            fichero << ta_eliminadas[i].codigoTarea << endl;
            fichero << ta_eliminadas[i].curso << endl;
            fichero << ta_eliminadas[i].estado << endl;
            fichero << ta_eliminadas[i].dia << endl;
            fichero << ta_eliminadas[i].mes << endl;
            fichero << ta_eliminadas[i].anio << endl;
            fichero << ta_eliminadas[i].nota << endl;
        }
        fichero.close();
    }
}

bool leerTareasDesdeFichero(Tarea tareas[], int &contadorTarea)
{
    ifstream fichero("tareas.txt");
    if (fichero.is_open())
    {
        fichero >> contadorTarea;
        fichero.ignore(); 

        for (int i = 0; i < contadorTarea; ++i)
        {
            getline(fichero, tareas[i].nombre);
            getline(fichero, tareas[i].descripcion);
            getline(fichero, tareas[i].codigoTarea);
            getline(fichero, tareas[i].curso);
            getline(fichero, tareas[i].estado);
            fichero >> tareas[i].dia;
            fichero >> tareas[i].mes;
            fichero >> tareas[i].anio;
            fichero >> tareas[i].nota;
            fichero.ignore(); 
        }
        fichero.close();
        return true;
    }
    return false;
}

void modificarTarea(Tarea tareas[], int contadorTarea) {
    system("ClS");

    int decision = 0, opcion, indice, opcionFecha;

    if ( contadorTarea > 0 ) {
            cambiarColorTexto(15);
            cout << "Modificar tarea.\n";
            cout << "--------------------\n";
            indice = indiceTarea(tareas, contadorTarea) - 1;

            while(decision == 0) {
                system("CLS");
                cambiarColorTexto(15);
                cout << "Opciones.\n";
                cout << "--------------------\n";
                cambiarColorTexto(6);
                cout << "1. Modificar nombre de una tarea.\n";
                cout << "2. Modificar fecha de una tarea.\n";
                cout << "3. Modificar descripcion de una tarea.\n";
                cout << "4. Modificar todo.\n";
                cout << "5. Cambiar tarea.\n";
                cout << "6. Salir.\n";
                cambiarColorTexto(7);
                cin >> opcion;

                while (cin.fail())
                {
                    cin.clear();
                    cin.ignore();
                    cambiarColorTexto(4);
                    cout << "\nIngrese una opción válida. Intente nuevamente: ";
                    cambiarColorTexto(7);
                    cin >> opcion;
                }

                switch (opcion)
                {
                case 1:
                    system("CLS");
                    cambiarColorTexto(6);
                    cout << "Ingrese el nuevo nombre de la tarea " << tareas[indice].nombre << ": ";
                    cin.ignore();
                    cambiarColorTexto(7);
                    getline(cin, tareas[indice].nombre);
                    break;

                case 2:
                    system("CLS");
                    cambiarColorTexto(15);
                    cout << "¿Qué desea cambiar?\n";
                    cout << "--------------------\n";
                    cambiarColorTexto(6);
                    cout << "1. Modificar año.\n";
                    cout << "2. Modificar mes.\n";
                    cout << "3. Modificar día.\n";
                    cout << "4. Modificar 2 o más parámetros.\n";
                    cout << "5. Salir.\n";
                    cambiarColorTexto(7);

                    cin >> opcionFecha;

                    while (cin.fail() || opcionFecha > 5 || opcionFecha < 1)
                    {
                        cin.clear();
                        cin.ignore();
                        cambiarColorTexto(4);
                        cout << "\nIngrese una opción válida. Intente nuevamente: ";
                        cambiarColorTexto(7);
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

                    cambiarColorTexto(6);
                    cout << "Ingrese la nueva descripción de la tarea " << tareas[indice].nombre << "." << endl;
                    cambiarColorTexto(2);
                    cout << "La descripción actual es " << tareas[indice].descripcion << "." << endl;

                    cin.ignore();
                    cambiarColorTexto(7);
                    getline(cin, tareas[indice].descripcion);

                    break;

                case 4:
                    system("CLS");
                    cambiarColorTexto(6);

                    cout << "Ingrese el nuevo nombre de la tarea " << tareas[indice].nombre << ": ";
                    cin.ignore();
                    cambiarColorTexto(7);

                    getline(cin, tareas[indice].nombre);

                    system("CLS");
                    cambiarColorTexto(15);
                    cout << "¿Qué desea cambiar de la fecha?\n";
                    cout << "--------------------\n";
                    cambiarColorTexto(6);
                    cout << "1. Modificar año.\n";
                    cout << "2. Modificar mes.\n";
                    cout << "3. Modificar día.\n";
                    cout << "4. Modificar 2 o más parámetros.\n";
                    cout << "5. Salir.\n";
                    cambiarColorTexto(7);

                    cin >> opcionFecha;

                    while (cin.fail() || opcionFecha > 5 || opcionFecha < 1)
                    {
                        cin.clear();
                        cin.ignore();
                        cambiarColorTexto(4);
                        cout << "\nIngrese una opción válida. Intente nuevamente: ";
                        cambiarColorTexto(7);
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
                    cambiarColorTexto(6);

                    cout << "Ingrese la nueva descripción de la tarea " << tareas[indice].nombre << "." << endl;
                    cambiarColorTexto(2);
                    cout << "La descripción actual es " << tareas[indice].descripcion << "." << endl;
                    cin.ignore();
                    cambiarColorTexto(7);

                    getline(cin, tareas[indice].descripcion);
                    break;

                case 5:
                    system("CLS");
                    cambiarColorTexto(15);
                    cout << "Modificar tarea.\n";
                    cout << "--------------------\n";
                    indiceTarea(tareas, contadorTarea);
                    break;

                case 6:
                    decision = 1;
                    break;

                default:
                    cambiarColorTexto(4);
                    cout << "Ingrese una opción válida.";
                    cambiarColorTexto(7);
                    break;
                }

            }
    }
    else {
        cambiarColorTexto(4);
        cout << "Primero debe ingresar alguna tarea.\n\n";
        cambiarColorTexto(7);
        system("PAUSE");
    }
}

void buscarFechaTarea(Tarea tareas[], int contadorTarea) {
    string repeticion = "s";
    int tareasCoinciden = 0,  diaTarea, mesTarea, anioTarea, i;
    system("CLS");

    if(contadorTarea > 0) {
        while(repeticion == "s") {
            tareasCoinciden = 0;
            diaTarea=obtenerDia(12,2024);
            for (i = 0; i < contadorTarea; i++)
            {
                if ( tareas[i].dia == diaTarea) {
                    cambiarColorTexto(6);
                    cout << "Ingrese el mes a buscar de la tarea: ";
                    cambiarColorTexto(7);
                    cin >> mesTarea;
                    while (cin.fail() || mesTarea < 1 || mesTarea > 12){
                        cin.clear();
                        cin.ignore();
                        cambiarColorTexto(4);
                        cout << "Ingrese un mes válido. Intente nuevamente: ";
                        cambiarColorTexto(7);
                        cin >> mesTarea;
                    }
                    if ( tareas[i].mes == mesTarea) {
                        cambiarColorTexto(6);
                        cout << "Ingrese el anio a buscar de la tarea: ";
                        cambiarColorTexto(7);
                        cin >> anioTarea;
                        while (cin.fail() || anioTarea <= 0 ){
                            cin.clear();
                            cin.ignore();
                            cambiarColorTexto(4);
                            cout << "Ingrese un anio válido. Intente nuevamente: ";
                            cambiarColorTexto(7);
                            cin >> anioTarea;
                        }
                        if (tareas[i].anio == anioTarea)
                        {
                            cambiarColorTexto(6);
                            cout << endl << "Tareas que coinciden con la busqueda. \n";
                            cambiarColorTexto(8);
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
                cambiarColorTexto(4);
                cout << endl << "Ninguna tarea coincide con el criterio de búsqueda.\n";
            }
            cambiarColorTexto(15);
            cout << "¿Desea buscar otra tarea? s/n: ";
            int contador=0;
            do{ 
                if (contador==0){
                    cambiarColorTexto(7);
                    cin >> repeticion;
                    cout<<endl<<endl;
                }else{
                    cambiarColorTexto(4);
                    cout<<"Solo se puede ingresar 's' o 'n': ";
                    cambiarColorTexto(7);
                    cin>>repeticion;
                    cout<<endl<<endl;
                }
                if (repeticion=="s"||repeticion=="n"){
                    break;
                }
                contador++;
            }while (true);
            cout << endl;

        }

    }
    else {
        cambiarColorTexto(4);
        cout << "No ha ingresado ninguna tarea. Por lo tanto no tiene ningún historial.\n";
        system("PAUSE");
    }
}

void cambiarEstadoTarea(Tarea tareas[], int contadorTarea) {
    int i, opcion, indice, decision1 = 0, caracteres;
    float nota;
    string estado, lower;

    system("CLS");

    if (contadorTarea > 0) {
        cambiarColorTexto(15);
        
        cout << "Modificar el estado de una tarea.\n";
        cout << "--------------------\n";

        indice = indiceTareaEstado(tareas, contadorTarea);

        while (decision1 == 0)
        {
            system("CLS");
            cambiarColorTexto(15);
            cout << "Opciones.\n";
            cout << "--------------------\n";
            cambiarColorTexto(6);
            cout << "\n1. Cambiar el estado.\n";
            cout << "2. Cambiar de tarea.\n";
            cout << "3. Salir.\n";

            cambiarColorTexto(7);
            cin >> opcion;

            while (cin.fail() || opcion < 0  || opcion > 3)
            {
                cin.clear();
                cin.ignore();
                cambiarColorTexto(4);
                cout << "\nIngrese una opcion correcta: ";
                cambiarColorTexto(7);
                cin >> opcion;
            }


            switch (opcion)
            {
            case 1:
                system("CLS");
                cambiarColorTexto(15);
                cout << "¿Ha entregado la tarea " << "'" << tareas[indice].nombre << "'" << "?: ";
                cambiarColorTexto(7);
                cin >> estado;

                while (estado != "entregada" && estado != "no entregada" && estado != "si" && estado != "no")
                {
                    cin.clear();
                    cin.ignore();
                    cambiarColorTexto(4);
                    cout << "\nIngrese si/no, entregada/no entregada: ";
                    cambiarColorTexto(7);
                    cin >> estado;
                }

                if (estado == "entregada" || estado == "si")
                {
                    tareas[indice].estado = "Entregada";
                    cambiarColorTexto(2);
                    cout << "La tarea ha sido entregada, ahora ingrese la nota ( 0 a 5 ): ";
                    cambiarColorTexto(7);
                    cin >> nota;

                    while (cin.fail() || nota < 0  || nota > 5)
                    {
                        cin.clear();
                        cin.ignore();
                        cambiarColorTexto(4);
                        cout << "\nIngrese una nota correcta: ";
                        cambiarColorTexto(7);
                        cin >> nota;
                    }
                    cambiarColorTexto(2);
                    cout << "\nLa nota de " << tareas[indice].nombre << " es " << nota << "." << endl;

                    tareas[indice].nota = nota;
                }

                else {
                    cambiarColorTexto(4);
                    tareas[indice].estado = "No Entregada";
                    cout << "La tarea " << tareas[indice].nombre << " no ha sido entregada. La nota es 0.\n";
                    tareas[indice].nota = 0;
                }

                decision1 = 1;
                cambiarColorTexto(7);
                system("PAUSE");
                break;

            case 2:
                indice = indiceTareaEstado(tareas, contadorTarea) - 1;
                break;

            case 3:
                decision1 = 1;
                break;

            default:
                break;
            }

        }
    }
    else {
        cambiarColorTexto(4);
        cout << "Primero debe ingresar alguna tarea.\n";
        cambiarColorTexto(7);
        system("PAUSE");
    }

}


//Funciones adicionales

string obtenerNombre(string aPedir){
    string nombre;
    cambiarColorTexto(6);
    cout << "\nIngrese su(s) "<< aPedir <<"(s): ";
    cambiarColorTexto(7);
    getline(cin, nombre);
    while (!validarNombre(nombre) || nombre == "" || nombre == " "){
        cambiarColorTexto(4);
        if (nombre==""||nombre== " "){
            cout << "Debe ingresar un "<< aPedir <<"\nIntente otra vez: ";
        }else{
            cout << "El " << aPedir << " no puede llevar números\nIntente otra vez: ";
        }
        cin.clear();
        cambiarColorTexto(7);
        getline(cin, nombre);
    }
    return nombre;
}


string obtenercodigo(){
    string codigo;
    bool soloNumeros = true;

    cambiarColorTexto(6);
    cout << "\nIngrese el código de estudiante (solo recibe números enteros): ";
    do{
        cambiarColorTexto(7);
        cin >> codigo;
        //Verificar que se hayan ingresado digitos
        for (int i = 0; i < codigo.length(); i++){
            if(!isdigit(codigo[i])){
                cambiarColorTexto(4);
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
    int  tareaModificar;
    cambiarColorTexto(15);
    cout << "\nEscoja la tarea donde se realizarán los cambios, cuenta con "<<contadorTarea<< " tarea(s)." <<endl;

    cambiarColorTexto(8);
    for (int i=0; i < contadorTarea; i++) {
        cout << endl << i+1 << ". " << tareas[i].nombre << endl;
    }

    cout << endl;
    cambiarColorTexto(7);
    cin >> tareaModificar;
    while (cin.fail() || tareaModificar < 1 || tareaModificar > contadorTarea){
        cin.clear();
        cin.ignore(200, '\n');
        cambiarColorTexto(4);
        cout << "\nIngrese una tarea válida. Intente nuevamente: ";
        cambiarColorTexto(7);
        cin >> tareaModificar;
    }

    return tareaModificar;
}

int indiceTareaEstado(Tarea tareas[], int contadorTarea) {
    int tareaModificar, tareasSinModificar = 0;
    do{
        cambiarColorTexto(6);
        cout << "\nEscoja la tarea donde se realizarán los cambios.\n";

        //Mostrar tareas
        cambiarColorTexto(8);
        for (int i=0; i < contadorTarea; i++){
            cout << endl << i+1 << ". " << tareas[i].nombre << endl;
        }

        cout << endl;
        cambiarColorTexto(7);
        cin >> tareaModificar;

        //Verificar que la tarea sea valida
        while (cin.fail() || tareaModificar < 1 || tareaModificar > contadorTarea){
            cin.clear();
            cin.ignore(200, '\n');
            cambiarColorTexto(4);
            cout << "\nIngrese una tarea válida. Intente nuevamente: ";
            cambiarColorTexto(7);
            cin >> tareaModificar;
        }

        //Obtener indice de tarea
        tareaModificar--;
        if (tareas[tareaModificar].estado != "En proceso"){
                system("CLS");
                if (tareas[tareaModificar-1].estado == "Entregada"){
                    cambiarColorTexto(2);
                    cout << "La tarea ya ha sido entregada." << "\nLa nota es " << tareas[tareaModificar].nota << ".\n";
                }else {
                    cambiarColorTexto(4);
                    cout << "La tarea no fue entregada." << "\nLa nota es " << tareas[tareaModificar].nota << ".\n";
                }

                for (int i = 0; i < contadorTarea; i++){
                    if (tareas[i].estado == "En proceso"){
                        tareasSinModificar++;
                    }

                }

                if ( tareasSinModificar == 0) {
                    cambiarColorTexto(6);
                    cout << "Agregue otra tarea para realizar cambios en el estado.\n\n";
                    cambiarColorTexto(7);
                    system("PAUSE");
                    tareaModificar = 0;
                    break;
                }

            }
    } while (tareas[tareaModificar].estado != "En proceso");

    return tareaModificar;

}

string obtenerCorreo (){
  string correo;
  int contador=0;
  do{
    if (contador==0){
        cambiarColorTexto(6);
      cout<<"\nIngrese correo: ";
      cambiarColorTexto(7);
        getline(cin, correo);
    }else{
        cambiarColorTexto(4);
      cout<<"El correo no es válido, vuelva a ingresar el correo: ";
      cambiarColorTexto(7);
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
    bool var = false;
    int condicion;

    for (int i=0; i < correo.length(); i++){
        if (correo[i]==espacio[0]){
            condicion=1;
            break;
        }else{
            condicion=0;
        }
    }

    if (condicion == 0){
        for (int i = 0; i < correo.length(); i++){
            if (correo[i] == arroba[0]){
                if (i==0){		//Arroba no puede ser inicio del correo
                    break;
                }else{
                    for (int j = i; j < correo.length(); j++){	//El for empieza a contar desde la posicion del arroba hasta encontrar un punto
                        if (correo[j] == punto[0]){

                            if (j-i<=1){	//El arroba y el punto no pueden ir seguidos
                                    break;
                            }else if (correo.length()-1!=j){
                                var = true;
                                break;
                            }

                        }
                    }
                }
            }
        }
    }
    return var;    
}

string crearCodigo(Estudiante &estudiante, string codigoMateria){
    string codigo = "";
    bool codigoValido = false;
    Cursos materia;

    //Validar un código valido
    do{
        for(int i = 0; i < estudiante.numMateriasInscritas; i++){
            if (estudiante.materias[i].codigo == codigoMateria){
                codigoValido = true;
                codigo += estudiante.materias[i].codigo;
                codigo += to_string(estudiante.materias[i].cantidad);

                //Incrementar la cantidad de tareas de esa materia
                estudiante.materias[i].cantidad++;
                break;
            }
        }

        if (!codigoValido){
            cambiarColorTexto(4);
            cout << "Ingrese un código valido, intente nuevamente: ";
            cambiarColorTexto(7);
            cin >> codigoMateria;
        }
    } while (!codigoValido);

    return codigo;
}


int obtenerAnio(){

    int anio;
    string respuesta;
    //Preguntar si la fecha de entrega es este año
    cambiarColorTexto(6);
    cout << "¿La tarea se entrega este año? s/n: ";
    cambiarColorTexto(7);
    cin >> respuesta;

    while(respuesta != "s" && respuesta != "n"){
        cambiarColorTexto(4);
        cout << "Digite 's' o 'n', ningún otro valor: ";
        cambiarColorTexto(7);
        cin >> respuesta;
    }

    if (respuesta == "s"){
        anio = 2024;
    }else{
        cambiarColorTexto(6);
        cout << "Ingrese el año de entrega: ";
        cambiarColorTexto(7);
        cin >> anio;
        while (cin.fail() || anio < 2024){
            cin.clear();
            cin.ignore();
            cambiarColorTexto(4);
            cout << "Ingrese una año que aún no haya pasado, intente nuevamente: ";
            cambiarColorTexto(7);
            cin >> anio;
        }
    }

    return anio;
}

int obtenerMes(int anio){
    int mes;
    int mesMinimo= 0;
    string meses[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo","Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    cambiarColorTexto(6);
    cout << "\nSeleccione el mes de entrega: \n";
    cout << endl;
    cambiarColorTexto(8);
    for (int i = 0; i< 12; i++){
        cout << i+1 << ". " << meses[i] << "\n";
    }

    //Si el año es 2024, el mes debe ser mayor a 5
    if (anio == 2024){
        mesMinimo = 6;
        cambiarColorTexto(6);
        cout << "\nRecuerda que el mes de entrega debe partir desde junio" <<endl ;
    }
    cambiarColorTexto(1);
    cout << "\nIngrese el número del mes: ";
    cambiarColorTexto(7);
    cin>>mes;

    while (cin.fail() || mes < mesMinimo || mes > 12){
        cin.clear();
        cin.ignore(200, '\n');
        cambiarColorTexto(4);
        cout << "Ingrese un mes válido. Intente nuevamente: ";
        cambiarColorTexto(7);
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

    cambiarColorTexto(1);
    cout << "\nIngrese el día de entrega: ";
    cambiarColorTexto(7);
    cin >> dia;
    while (cin.fail() || dia < 1 || dia > ultimoDiaDelMes){
        cin.clear();
        cin.ignore();
        cambiarColorTexto(4);
        cout << "\nAlgo salió mal, solo puedes ingresar números entre 1 y " << ultimoDiaDelMes << " , intenta otra vez: ";
        cambiarColorTexto(7);
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
        cambiarColorTexto(4);
        cout << "No tiene ninguna tarea actualmente\n \n";
        cambiarColorTexto(7);
        system("PAUSE");
        condicionEliminar=0;
    }else{  //Condición si existen tareas para borrar
        cambiarColorTexto(6);
        cout<<"Las tareas creadas anteriormente son: "<< endl << endl;
        cambiarColorTexto(8);
        for (int i=0; i<contadorTarea;i++){     //Impresión del número de la tarea con la tarea. Ejemplo: Tarea 1: cartelera
            if (tarea[i].nombre!=""){
                cout << "       Tarea " << i+1 <<": " << tarea[i].nombre<<endl;   
            }
        }
        cambiarColorTexto(6);
        cout<<"\nIngrese el número de la tarea que deséa eliminar: ";
        do{     //Validación en caso de que el usuario un número de una tarea que no exista o ingrese letras
            cambiarColorTexto(7);
            cin >> numTarea;
            if (cin.fail()){
                cin.clear();
                cin.ignore(200, '\n');
            }else{}
            if ( numTarea<=contadorTarea && numTarea>0 ){
                break;
            }
            cambiarColorTexto(4);
            cout << "La tarea que ingresaste es inválida o no existe.\nVuelva a ingresar el número de la tarea: ";
        }while (true);

        numTarea--; //Restamos 1 al número de la tarea para convertirlo en el índice de tarea[i] 

        //Impresión de la tarea eliminada
        cambiarColorTexto(1);
        cout << "\nLa tarea que eliminaste es: "<< endl;
        cambiarColorTexto(8);
        cout << endl << "       Tarea " << numTarea+1 << ": " << tarea[numTarea].nombre << endl;

        TareaEliminada[contadorEliminado]=tarea[numTarea];//Asignamos un nuevo vector donde en un futuro se establecerán todas las tareas eliminadas

        for (int i = numTarea; i < contadorTarea ; i++) {//for para que desde la tarea que se elimine todas las tareas se corran un puesto para atras
            if (i != contadorTarea - 1){
                tarea[i] = tarea[i + 1];
            }
        }//En el último ciclo del for, el bucle no hará nada, para que se deje la última tarea quieta, hasta acá la tarea n y la tarea n-1 serán iguales

        condicionEliminar=1;
        //Finalmente en el main() se declará que el contador eliminado(contador que cuenta cuantas tareas se han eliminado) aumenta uno, y el contador de las tareas disminuye en uno
        cambiarColorTexto(7);

        system("PAUSE");
    }

    return condicionEliminar;
}

void historialTareas(Tarea tarea[],Tarea TareaEliminada[],int contadorTarea,int contadorEliminado, Estudiante &estudiante){

    //Para esta función es importante tener en cuenta que anteriormente ya habíamos validado que el ingreso del código del curso en una tarea, concuerde con algún curso.

    system("CLS");
    string buscador;    //Se declara buscador, porque ahorita se le pedirá al usuario que materia quiere ver el historial, preguntandole el código de la materia
    int numTarea=0, contadorTareasEliminadas=0, contadorTareasActuales=0;
    if (contadorTarea==0 && contadorEliminado==0){  //Condición si no existe ninguna tarea, ni ninguna tarea eliminada
        cambiarColorTexto(4);
        cout << "No ha ingresado ninguna tarea. Por lo tanto no tiene ningún historial.\n\n";
        system("PAUSE");
    }else if(contadorTarea==0 && contadorEliminado!=0){ //Condición si no existe ninguna tarea, pero si has eliminado tareas
        cambiarColorTexto(6);
        cout<< "No tienes ninguna tarea actualmente, sin embargo, puedes buscar que tareas has eliminado en las siguientes materias: ";
        cout<<endl<<endl;
        cambiarColorTexto(15);
        cout << left << setw(20) << "Materia" << setw(10) << "Código" << endl;
        cambiarColorTexto(8);
        for(int i = 0; i < estudiante.numMateriasInscritas ; i++) {	//impresión de nombre y código de materia
            cout << setw(20) << left << estudiante.materias[i].nombre << setw(10) << left << estudiante.materias[i].codigo << endl;
        }

        //Ingreso del código de la materia por el usuario
        cambiarColorTexto(6);
        cout<< "\n\nIngrese el código de la materia al cual deséas saber que tareas has eliminado: " ;

        //Validación del ingreso para que concuerde el código que ingresa el usuario y los códigos que tienen las materias
        do{
            cambiarColorTexto(7);
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
            cambiarColorTexto(4);
            cout<<endl<<"El código que ingreso no pertenece a ninguna materia."<<endl<<"Ingrese nuevamente el código de la materia: ";
        }while (true);

        numTarea=0; //contador para imprimir el número de la tarea, es decir tarea 1 y asi sucesivamente.
        cambiarColorTexto(6);
        cout<< endl<<endl<<"Tareas eliminadas: \n\n";
        cambiarColorTexto(8);
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
            cambiarColorTexto(6);
            cout<<"No has eliminado ninguna tarea en esta materia.\n\n";
        }
        system("PAUSE");
    }else{  //El código de esta condición tiene una lógica muy similar a la de la condición anterior
        
        cambiarColorTexto(6);
        cout<< "Las materias con su código respectivamente son: "<<endl<<endl;
        cambiarColorTexto(15);
        cout << left << setw(20) << "Materia" << setw(10) << "Código" << endl;
        cambiarColorTexto(8);
        for(int i = 0; i < estudiante.numMateriasInscritas ; i++) {	//impresión de nombre y código de materia
            cout << setw(20) << left << estudiante.materias[i].nombre << setw(10) << left << estudiante.materias[i].codigo << endl;
        }

        //Ingreso de código de la materia
        cambiarColorTexto(6);
        cout<< "\n\nIngrese el código de la materia al cual desea saber que tareas tienes actualmente: " ;
        
        //Validación del código de la materia
        do{
            cambiarColorTexto(7);
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
            cambiarColorTexto(4);
            cout<<endl<<"El código que ingreso no pertenece a ninguna materia."<<endl<<"Ingrese nuevamente el código de la materia: ";
        }while (true);
        cout<<endl<<endl;
        //Impresión: historial total de la <materia> 
        cambiarColorTexto(1);
        for (int i=0;i<estudiante.numMateriasInscritas;i++){
            if (buscador==estudiante.materias[i].codigo){
                cambiarColorTexto(6);
                cout<< "El historial total de tareas en la materia "<<estudiante.materias[i].nombre<<" es: "<<endl<<endl<<endl;
            }
        }

        //Impresión de cada tarea
        cambiarColorTexto(15);
        cout<<"Tareas: "<<endl<<endl;
        cambiarColorTexto(8);
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
            cambiarColorTexto(4);
            cout<< "\n\nNo tienes ninguna tarea en esta materia: ";
        }
        numTarea=0;

        //Impresión de las tareas eliminadas
        cambiarColorTexto(6);
        cout<< endl<<endl<<"Tareas eliminadas: "<<endl<<endl;
        cambiarColorTexto(8);
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
            cambiarColorTexto(6);
            cout << "\n\nNo tienes ninguna tarea eliminada en esta materia.\n\n ";
        }
        system("PAUSE");
    }
}