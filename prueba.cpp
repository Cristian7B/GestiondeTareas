#include <iostream>
#include <locale.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <vector>
#include <fstream>

using namespace std;

// REGISTROS

// Nombre de los cursos del estudiante
struct Cursos
{
    string nombre;
    string codigo;
    int cantidad;
    int cantidadMaterias;
};

// Crear estudiante
struct Estudiante
{
    string nombre;
    int codigo;
    string apellido;
    string correo;
    Cursos materias[15];
    int numMateriasInscritas;
};

// Datos de las tareas
struct Tarea
{
    string nombre;
    string descripcion;
    string codigoTarea;
    string curso;
    string estado; // En proceso, entregada y no entregada
    int dia;
    int mes;
    int anio;
    float nota;
    Cursos materia;
};

// Prototipado de funciones
void registrarEstudiante(Estudiante &estudiante);
void registrarMaterias(Estudiante &estudiante);
bool leerEstudianteDesdeFichero(Estudiante &estudiante);
void guardarEstudianteEnFichero(const Estudiante &estudiante);
int crearTarea(Estudiante &estudiante, Tarea tareas[], Cursos materias[], int contadorTarea);
bool leerTareasDesdeFichero(Tarea tareas[], int &contadorTarea);
void guardarTareasEnFichero(const Tarea tareas[], int contadorTarea);

// Funciones adicionales
int obtenercodigo();
int obtenerAnio();
int obtenerMes(int anio);
int obtenerDia(int mes, int anio);
string obtenerCorreo();
string obtenerNombre(string aPedir);
bool validarNombre(string nombre);
string crearCodigo(Estudiante &estudiante, string cursoNombre);

int main()
{
    // Vectorización de los struct
    Tarea tareas[100];
    Cursos materias[15];
    Estudiante perfil;
    int contadorTarea = 0;

    setlocale(LC_ALL, "spanish");
    system("cls");

    // Variables globales
    int decision = 0, opcion = 0;

    cout << "¡Bienvenido a tu sistema de gestión de tareas personal!\n";
    system("PAUSE");
    system("CLS");

    cout << "Es hora de registrar tu perfil.\n";
    if (!leerEstudianteDesdeFichero(perfil))
    {
        registrarEstudiante(perfil);
        guardarEstudianteEnFichero(perfil);
    }
    else
    {
        cout << "Perfil cargado exitosamente.\n";
        system("PAUSE");
    }

    if (leerTareasDesdeFichero(tareas, contadorTarea))
    {
        cout << contadorTarea << endl;
        cout << "Tareas cargadas exitosamente.\n";

        for ( int i = 0; i <contadorTarea; i++ ){
            cout << tareas[i].nombre << endl;
            cout << tareas[i].descripcion << endl;
        }
        system("PAUSE");
    }

    // Menú de opciones
    while (decision == 0)
    {
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

        cout << "\nOpción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            contadorTarea = crearTarea(perfil, tareas, materias, contadorTarea);

             
            system("pause");
            break;

        case 2:
            // Implementación para crear n tareas
            system("pause");
            break;

        case 3:
            // Implementación para modificar tarea
            break;

        case 4:
            // Implementación para cambiar estado de tarea
            break;

        case 5:
            // Implementación para eliminar tarea
            break;

        case 6:
            // Implementación para consultar historial de tareas de una materia
            break;

        case 7:
            // Implementación para consultar tareas para una fecha específica
            break;

        case 0:
            decision = 1;
            break;

        default:
            cout << "\nDigite una opción válida.";
            break;
        }
    }
    return 0;
}

// Funciones

void registrarEstudiante(Estudiante &estudiante)
{
    // Solicitar nombre, apellido, correo y código
    cout << "--------------------\n";
    cout << "Datos personales.\n";

    estudiante.nombre = obtenerNombre("nombre");
    estudiante.apellido = obtenerNombre("apellido");
    estudiante.correo = obtenerCorreo();
    estudiante.codigo = obtenercodigo();

    registrarMaterias(estudiante);
}

void registrarMaterias(Estudiante &estudiante)
{
    string continuar;
    int numMateriasRegistradas = 0;
    int contadorMat;

    cout << "\nMaterias.\n";
    cout << "--------------------";
    cout << "\nEs momento de registrar tus materias.\n";

    // Solicitar los datos de las materias inscritas
    while (continuar != "n" && estudiante.numMateriasInscritas < 15)
    {
        cin.ignore();

        cout << "\nIngresa el nombre de la materia: ";
        do
        {
            contadorMat = 0;
            getline(cin, estudiante.materias[numMateriasRegistradas].nombre);
            if (numMateriasRegistradas == 0)
            {
            }
            else
            {
                for (int i = 0; i < numMateriasRegistradas; i++)
                {
                    if (estudiante.materias[i].nombre == estudiante.materias[numMateriasRegistradas].nombre)
                    {
                        cout << "Dos materias no pueden llamarse igual, ingrese un nuevo nombre: ";
                        contadorMat++;
                    }
                }
            }
        } while (contadorMat != 0);

        cout << "\tAhora registra el código de la materia: ";
        do
        {
            contadorMat = 0;
            getline(cin, estudiante.materias[numMateriasRegistradas].codigo);
            if (numMateriasRegistradas == 0)
            {
            }
            else
            {
                for (int i = 0; i < numMateriasRegistradas; i++)
                {
                    if (estudiante.materias[i].codigo == estudiante.materias[numMateriasRegistradas].codigo)
                    {
                        cout << "Dos materias no pueden tener el mismo código, ingrese uno nuevo: ";
                        contadorMat++;
                    }
                }
            }
        } while (contadorMat != 0);

        cout << "\nLa materia se registró como " << estudiante.materias[numMateriasRegistradas].nombre << endl;
        cout << "El código de " << estudiante.materias[numMateriasRegistradas].nombre << " es " << estudiante.materias[numMateriasRegistradas].codigo;

        // Definir la cantidad de tareas para cada materia
        estudiante.materias[numMateriasRegistradas].cantidad = 0;
        numMateriasRegistradas++;

        // Preguntar por si se quiere dejar de registrar materias
        cout << "\n--------------------\n";
        cout << "¿Desea inscribir más materias? s/n: ";
        cin >> continuar;

        while (continuar != "s" && continuar != "n")
        {
            cout << "Digite 's' o 'n', ningún otro valor: ";
            cin >> continuar;
        }
    }

    // Almacenar el número de materias registradas
    estudiante.numMateriasInscritas += numMateriasRegistradas;
}

bool leerEstudianteDesdeFichero(Estudiante &estudiante)
{
    ifstream fichero("estudiante.txt");
    if (fichero.is_open())
    {
        getline(fichero, estudiante.nombre);
        getline(fichero, estudiante.apellido);
        getline(fichero, estudiante.correo);
        fichero >> estudiante.codigo;
        fichero >> estudiante.numMateriasInscritas;
        fichero.ignore(); // Ignorar el salto de línea restante

        for (int i = 0; i < estudiante.numMateriasInscritas; ++i)
        {
            getline(fichero, estudiante.materias[i].nombre);
            getline(fichero, estudiante.materias[i].codigo);
            fichero >> estudiante.materias[i].cantidad;
            fichero >> estudiante.materias[i].cantidadMaterias;
            fichero.ignore(); // Ignorar el salto de línea restante
        }
        fichero.close();
        return true;
    }
    return false;
}

void guardarEstudianteEnFichero(const Estudiante &estudiante)
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

bool leerTareasDesdeFichero(Tarea tareas[], int &contadorTarea)
{
    ifstream fichero("tareas.txt");
    if (fichero.is_open())
    {
        fichero >> contadorTarea;
        fichero.ignore(); // Ignorar el salto de línea restante

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
            fichero.ignore(); // Ignorar el salto de línea restante
        }
        fichero.close();
        return true;
    }
    return false;
}


int crearTarea(Estudiante &estudiante, Tarea tareas[], Cursos materias[], int contadorTarea)
{
    if (contadorTarea >= 100)
    {
        cout << "No se pueden agregar más tareas. Capacidad máxima alcanzada.\n";
        return contadorTarea;
    }

    Tarea nuevaTarea;

    cout << "\nCrear nueva tarea\n";
    cout << "-----------------\n";
    cout << "Ingrese el nombre de la tarea: ";
    cin.ignore();
    getline(cin, nuevaTarea.nombre);

    cout << "Ingrese la descripción de la tarea: ";
    getline(cin, nuevaTarea.descripcion);

    cout << "Ingrese el curso: ";
    getline(cin, nuevaTarea.curso);

    cout << "Ingrese el estado de la tarea (En proceso, entregada, no entregada): ";
    getline(cin, nuevaTarea.estado);

    cout << "Ingrese la fecha de entrega (día mes año): ";
    cin >> nuevaTarea.dia >> nuevaTarea.mes >> nuevaTarea.anio;

    nuevaTarea.codigoTarea = crearCodigo(estudiante, nuevaTarea.curso);

    tareas[contadorTarea] = nuevaTarea;
    contadorTarea++;

    guardarTareasEnFichero(tareas, contadorTarea);

    cout << "Tarea creada exitosamente.\n";

    return contadorTarea;
}

// Funciones adicionales para obtener datos del usuario
int obtenercodigo()
{
    int codigo;
    cout << "Ingrese su código: ";
    cin >> codigo;
    return codigo;
}

string obtenerCorreo()
{
    string correo;
    cout << "Ingrese su correo: ";
    cin >> correo;
    return correo;
}

string obtenerNombre(string aPedir)
{
    string nombre;
    cout << "Ingrese su " << aPedir << ": ";
    cin >> nombre;
    while (!validarNombre(nombre))
    {
        cout << "Nombre inválido. Ingrese su " << aPedir << " nuevamente: ";
        cin >> nombre;
    }
    return nombre;
}

bool validarNombre(string nombre)
{
    for (char c : nombre)
    {
        if (!isalpha(c))
        {
            return false;
        }
    }
    return true;
}

string crearCodigo(Estudiante &estudiante, string cursoNombre)
{
    // Crear un código para la tarea basado en el código del estudiante y el curso
    return to_string(estudiante.codigo) + "_" + cursoNombre;
}
