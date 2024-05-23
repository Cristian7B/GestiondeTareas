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
    string nombre;
    string codigo;
    int cantidad;
    int cantidadMaterias;
};

//Crear estudiante
struct Estudiante {
    string nombre;
    int codigo;
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
    Cursos materia;
};

// Prototipado de funciones
void registrarEstudiante(Estudiante &estudiante);
void registrarMaterias(Estudiante &estudiante); 

// Funciones de las tareas
int crearTarea(Estudiante &estudiante, Tarea tareas[], Cursos materias[], int contadorTarea);
int crearNTareas(Estudiante &estudiante, Tarea tareas[], Cursos materias[], int contadorTarea);
void modificarTarea(Tarea &tarea);
void eliminarTarea(Tarea &tarea, int contadorTarea);
void estadoTarea(Tarea &tarea);

// Consultas
void tareasMateria(Tarea &tarea);
void tareasFecha(Tarea &tarea);

// Funciones adicionales
int obtenercodigo();
int obtenerAnio();
int obtenerMes(int anio);
int obtenerDia(int mes, int anio);

string obtenerCorreo();
string crearCodigo(Estudiante &estudiante, string cursoNombre, Cursos materias[]);
bool validarcorreo(string correo);


main() { 
    //Vectorizacion de los struct
    Tarea tareas[100];
    Cursos materias[15];
    Estudiante perfil;

    setlocale(LC_ALL, "spanish");
    system("cls");
    
    //Variales globales
    int decision = 0, contadorMateria = 0, opcion = 0, contadorTarea = 0;

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
        cout << "\t 2. Crear n tareas tarea.\n";
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
                break;

            case 4:
                break;

            case 5:
                break;

            case 6:
                break;

            case 7:
                decision = 1;
                break;

            default:
                break;
        }
    }

}

// Funciones
void registrarEstudiante(Estudiante &estudiante) {
    // Solicitar nombre, apellido, correo y codigo
    cout << "--------------------\n";
    cout << "Datos personales.\n";

    cout << "Ingresa tu nombre: ";
    cin >> estudiante.nombre;

    cout << "Ingresa tu apellido: ";
    cin >> estudiante.apellido;

    estudiante.correo = obtenerCorreo();


    estudiante.codigo = obtenercodigo();

    registrarMaterias(estudiante);
}

void registrarMaterias(Estudiante &estudiante) { 
    string continuar;
    int numMateriasRegistradas = 0;

    cout << "\nMaterias.\n";
    cout << "--------------------";
    cout << "\nEs momento de registrar tus materias.\n";

    // Solicitar los datos de las materias inscritas
    while (continuar != "n" && estudiante.numMateriasInscritas < 15) {

        cout << "\nIngresa el nombre de la materia: ";
        cin >> estudiante.materias[numMateriasRegistradas].nombre;


        cout << "\tLa materia se registró como " << estudiante.materias[numMateriasRegistradas].nombre;

        cout << "\n\tAhora registra el código de la materia: ";
        cin >> estudiante.materias[numMateriasRegistradas].codigo;

        // Definir la cantidad de tareas para cada materia
        estudiante.materias[numMateriasRegistradas].cantidad = 0;
        numMateriasRegistradas++;

        // Preguntar por si se quiere dejar de registrar materias
        cout << "--------------------\n";
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
    int i;

    cout << "Ingresa el nombre de la tarea: ";
    cin >> tareas[contadorTarea].nombre;
    
    cout << "Ingresa la descripción de la tarea: ";
    cin >> tareas[contadorTarea].descripcion;

    cout << "Ingrese el curso al que pertenece la materia, las materias son: \n";
    cout << endl;
    for(i = 0; i < estudiante.numMateriasInscritas ; i++) {
        cout << "- " << estudiante.materias[i].nombre << endl;
    }

    cin >> tareas[contadorTarea].curso;
    
    cout << "Fecha de entrega de la tarea.\n";
    cout << "--------------------\n";

    //Fechas
    tareas[contadorTarea].anio = obtenerAnio();
    tareas[contadorTarea].mes = obtenerMes(tareas[contadorTarea].anio);
    // tareas[contadorTarea].dia = obtenerDia(tareas[contadorTarea].anio, tareas[contadorTarea].mes);
    
    tareas[contadorTarea].estado = "En proceso";

    tareas[contadorTarea].codigoTarea = crearCodigo(estudiante, tareas[contadorTarea].curso, materias);  
    contadorTarea++;  

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

int crearNTareas(Estudiante &estudiante, Tarea tareas[100], Cursos materias[], int contadorTarea){
    int i = 0;
    
    string repeticion = "s";
    
    while(repeticion == "s" && contadorTarea < 100) {
        cout << "Ingresa el nombre de la tarea: ";
        cin >> tareas[contadorTarea].nombre;
        
        cout << "Ingresa la descripción de la tarea: ";
        cin >> tareas[contadorTarea].descripcion;

        cout << "Ingrese el curso al que pertenece la materia, las materias son: \n";
        cout << endl;

        for(i = 0; i < estudiante.numMateriasInscritas ; i++) {
            cout << "- " << estudiante.materias[i].nombre << endl;
        }

        cin >> tareas[contadorTarea].curso;
        
        // tareas[contadorTarea].codigoTarea = crearCodigo(materias);
        
        cout << "Fecha de entrega de la tarea.\n";
        cout << "--------------------\n";

        //Fechas
        tareas[contadorTarea].anio = obtenerAnio();
        tareas[contadorTarea].mes = obtenerMes(tareas[contadorTarea].anio);
        tareas[contadorTarea].codigoTarea = crearCodigo(estudiante, tareas[contadorTarea].curso, materias);    

        // tareas[contadorTarea].dia = obtenerDia(tareas[contadorTarea].anio, tareas[contadorTarea].mes);
        
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


//Funciones adicionales
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

string obtenerCorreo (){
	string correo;
	int contador=0;
    cin.ignore(); 
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

string crearCodigo(Estudiante &estudiante, string cursoNombre, Cursos materias[]){
    int i;
    string codigo= cursoNombre + to_string(cursoNombre[0]);

    //Incrementar la cantidad de tareas
    for(i = 0; i < estudiante.numMateriasInscritas ; i++) {
        if (materias[i].nombre == cursoNombre)
        {
            materias[i].cantidad++;
        } 
    }

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
        while (cin.fail() || anio < 2023){
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

    cout << "Seleccione el mes de entrega: \n";
    for (int i= 0; i< 12; i++){
        cout << i+1 << ". " << meses[i] << "\n";
    }

    //Si el año es 2024, el mes debe ser mayor a 5
    if (anio == 2024){
        mesMinimo = 5;
        cout << "Recuerda que el mes de entrega debe partir desde junio";
    }

    cout << "Ingrese el número del mes: ";
    cin >> mes;
    
    while (cin.fail() || mes < mesMinimo || mes > 12){
        cin.clear();
        cin.ignore();
        cout << "Ingrese un mes válido, solo el  número. Intente nuevamente: ";
    }

    return mes;
}
// int obtenerDia(int mes, int anio){
//     int dia;
// }