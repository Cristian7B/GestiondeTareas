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
};

//Crear estudiante
struct Estudiante {
    string nombre;
    int codigo;
    string apellido;
    string correo;
    Cursos materias[15];
    int numMateriasInscritas; //Para conocer la cantidad de materias registradas
};

//Datos de las tareas
struct Tarea {
    string nombre;
    string descripcion;
    string codigoTarea;
    string estado;//En proceso, entregada y no entregada
    Cursos materia;

    //Fecha de entrega
    int dia;
    int mes;
    int anio;
};

//Prototipado de funciones
void crearEstudianteCursos(Estudiante &es, Cursos materias[], int contador);
void registrarEstudiante(Estudiante &estudiante);
void registrarMaterias(Estudiante &estudiante);

//Funciones de las tareas
void crearTarea(Cursos &curso, Tarea tareas[], int cantidadTareas);
void crearNTareas(Tarea tareas[], int cantidadTareas);
void modificarTarea( Tarea &tarea );
void eliminarTarea( Tarea &tarea, int contadorTarea);
void estadoTarea( Tarea &tarea );

//Consultas
void tareasMateria( Tarea &tarea);
void tareasFecha( Tarea &tarea);

//Funciones adicionales
int obtenercodigo();
string crearCodigo(Cursos &curso);
bool validarcorreo(string correo);
int obtnerAnio();
int obtenerMes(int anio);
int obtenerDia(int mes, int anio);


main() {
    Tarea tareas[100];
    setlocale(LC_ALL, "spanish");

    system("cls");
    Cursos materias[15];
    Estudiante perfil;

    int cantidadTareas = 0, contadorMateria = 0, opcion = 0;

    cout << "¡Bienvenido a tu sistema de gestion de tareas personal!\n";

    system("PAUSE");
    system("CLS");

    cout << "Es hora de registrar tu perfil.\n";
    registrarEstudiante(perfil);

    //Menu de opciones
    while (opcion == 0)
    {    
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

        switch (opcion)
        {
        case 1:
            //Crear función para solicitar curso
            break;
        
        case 2:
            crearNTareas(tareas, cantidadTareas);
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
    //Solicitar nombre, apellido, correo y codigo
    cout << "--------------------\n";
    cout << "Datos personales.\n";
    
    cout << "Ingresa tu nombre: ";
    cin >> estudiante.nombre;


    cout << "Ingresa tu apellido: ";
    cin >> estudiante.apellido;


    cout << "Ingresa tu correo: ";
    estudiante.correo = obtenercorreo();

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

        //Definir la cantidad de tareas para cada materia
        estudiante.materias[numMateriasRegistradas].cantidad = 0;
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

void crearTarea(Cursos &curso, Tarea tareas[], int cantidadTareas){
    Tarea tarea;
    cout << "Ingrese el nombre de la tarea: ";
    cin >> tarea.nombre;

    cout << "Añada la descripción de la tarea: ";
    cin >> tarea.descripcion;

    tarea.codigoTarea = crearCodigo(curso);
    
    tarea.estado = "En proceso";
    
    //Solicitar fecha de entrega
    tarea.anio = obtnerAnio();
    tarea.mes = obtenerMes(tarea.anio);
    tarea.dia = obtenerDia(tarea.mes, tarea.anio);
    
    //Añadir a la lista de tareas
    tareas[cantidadTareas] = tarea;

    cantidadTareas++;

}

void crearNTareas(Tarea tareas[100], int cantidadTareas){
    int contadorTarea = 0;
    
    string repeticion = "s";
    
    while(repeticion == "s" && contadorTarea < 100) {
        cout << "Ingresa el nombre de la tarea: ";
        cin >> tareas[contadorTarea].nombre;
        
        cout << "Ingresa la descripción de la tarea: ";
        cin >> tareas[contadorTarea].descripcion;
        
        cout << "Ingresa el código de la tarea: ";
        cin >> tareas[contadorTarea].codigoTarea;
        
        //Solicitar fecha de entrega
        tareas[contadorTarea].anio = obtnerAnio();
        tareas[contadorTarea].mes = obtenerMes(tareas[contadorTarea].anio);
        tareas[contadorTarea].dia = obtenerDia(tareas[contadorTarea].mes, tareas[contadorTarea].anio);
        
        cout << "¿Desea agregar otra tarea? s/n: ";
        cin >> repeticion;
    }
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
string obtenercorreo (){
	string correo;
	int contador=0;
	do{
		if (contador==0){
			cout<<"\nIngrese correo: ";
		}else{
			cout<<"\nEl correo no es válido, vuelva a ingresar el correo: ";
		}
		cin>>correo;
		contador++;
	}while (!validarcorreo(correo));
	return correo;
}
int obtnerAnio(){
    int anio;
    string respuesta;

    //Preguntar si la fecha de entrega es este año
    cout << "\n¿La tarea se entrega este año? s/n: ";
    cin >> respuesta;
    
    while(respuesta != "s" && respuesta != "n"){
        cout << "\nDigite 's' o 'n', ningún otro valor: ";
        cin >> respuesta;
    }

    if (respuesta == "s"){
        anio = 2024;
    }else{
        cout << "\nIngrese el año de entrega: ";
        cin >> anio;
        while (cin.fail() || anio < 2023){
            cin.clear();
            cin.ignore();
            cout << "\nIngrese una año que aún no haya pasado, intente nuevamente: ";
            cin >> anio;
        }
    }

    return anio;
}

int obtenerMes(int anio){
    int mes;
    int mesMinimo= 1;
    string meses[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo","Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    cout << "\nSeleccione el mes de entrega: \n";
    for (int i= 0; i< 12; i++){
        cout << i+1 << ". " << meses[i] << "\n";
    }

    cout << "\nIngrese el número del mes: ";
    //Si el año es 2024, el mes debe ser mayor a 5
    if (anio == 2024){
        mesMinimo = 5;
        cout << "(recuerda que el mes de entrega debe partir desde junio)";
    }   
    cin >> mes;
    
    while (cin.fail() || mes < mesMinimo || mes > 12){
        cin.clear();
        cin.ignore();
        cout << "\nIngrese un mes válido, solo el  número. Intente nuevamente: ";
    }

    return mes;
}
int obtenerDia(int mes, int anio){
    int dia, maximoDia;

    //Establecer día en la que acaba el mes
    switch (mes){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            maximoDia = 31;
            break;
        case 2:
            //Revisar si es bisiesto
            if(anio % 4){
                maximoDia = 29;
            }else{
                maximoDia = 28;
            }
            break;
        default:
            maximoDia = 30;//30 para los demás meses
    }

    cout << "\nAhora ingrese el día de entrega de la tarea";
    cin >> dia;

    while (cin.fail() || dia < 1 || dia > maximoDia){
        cin.clear();
        cin.ignore();
        cout << "\nDebes ingresar un número entre 1 y " << maximoDia << ".Intenta nuevamente: ";
        cin >> dia;
    }

    return dia;
}