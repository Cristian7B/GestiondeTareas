/*
Sistema de gestión de tareas
Estudiantes: Cristian Camilo Bonilla, Nicolas Velasco y Jesús Antonio Murcia
Fecha: 5 de Junio
*/


#include <iostream>
#include <locale.h>
#include <string>
#include <iomanip>

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
void modificarTarea(Tarea tareas[], int contadorTarea);
void eliminarTarea(Tarea &tarea, int contadorTarea);
void estadoTarea(Tarea &tarea);
void buscarFechaTarea(Tarea tareas[], int contadorTarea);

// Consultas
void tareasMateria(Tarea &tarea);
void tareasFecha(Tarea &tarea);

// Funciones adicionales
int obtenercodigo();
int obtenerAnio();
int indiceTarea(Tarea tareas[], int contadorTarea);
int obtenerMes(int anio);
int obtenerDia(int mes, int anio);
bool validarcorreo(string correo);

string crearCodigo(Estudiante &estudiante, string cursoNombre, Cursos materias[]);
string obtenerCorreo();
string obtenerNombre(string aPedir);
bool validarNombre(string nombre);


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
                break;

            case 5:
                break;

            case 6:
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

    cout << "\nMaterias.\n";
    cout << "--------------------";
    cout << "\nEs momento de registrar tus materias.\n";

    // Solicitar los datos de las materias inscritas
    while (continuar != "n" && estudiante.numMateriasInscritas < 15) {

        cin.ignore();

        cout << "\nIngresa el nombre de la materia: ";
        getline(cin, estudiante.materias[numMateriasRegistradas].nombre);

        cout << "\tAhora registra el código de la materia: ";
        cin >> estudiante.materias[numMateriasRegistradas].codigo;

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
    int i;

    cin.ignore();
    cout << "Tarea " << contadorTarea << endl;
    cout << "--------------------\n";

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

    cout << endl;

    cin >> tareas[contadorTarea].curso;
    
    
    cout << "\nFecha de entrega de la tarea.\n";
    cout << "--------------------\n";

    //Fechas
    tareas[contadorTarea].anio = obtenerAnio();
    tareas[contadorTarea].mes = obtenerMes(tareas[contadorTarea].anio);
    tareas[contadorTarea].dia = obtenerDia(tareas[contadorTarea].mes, tareas[contadorTarea].anio);
    tareas[contadorTarea].codigoTarea = crearCodigo(estudiante, tareas[contadorTarea].curso, materias);    

    
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
        cout << endl;
    }

    return contadorTarea;
}

int crearNTareas(Estudiante &estudiante, Tarea tareas[100], Cursos materias[], int contadorTarea){
    int i = 0;
    
    string repeticion = "s";

    system("CLS");
    while(repeticion == "s" && contadorTarea < 100) {
        cout << "Tarea " << contadorTarea << endl;
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

        cout << endl;

        cin >> tareas[contadorTarea].curso;
        
        
        cout << "\nFecha de entrega de la tarea.\n";
        cout << "--------------------\n";

        //Fechas
        tareas[contadorTarea].anio = obtenerAnio();
        tareas[contadorTarea].mes = obtenerMes(tareas[contadorTarea].anio);
        tareas[contadorTarea].dia = obtenerDia(tareas[contadorTarea].mes, tareas[contadorTarea].anio);
        tareas[contadorTarea].codigoTarea = crearCodigo(estudiante, tareas[contadorTarea].curso, materias);    
        
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
        cout << "Ingrese alguna tarea.\n";
        system("PAUSE");
    }
}

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


//Funciones adicionales
int obtenercodigo(){
    float codigo;
    
    cout << "Ingrese el código de estudiante: ";
    cin >> codigo;

    while(cin.fail() || codigo < 0){
        cin.clear();
        cin.ignore();
        cout << "Ingrese solamente valores númericos: ";
        cin >> codigo;
    }

    return float(codigo);
}

int indiceTarea(Tarea tareas[], int contadorTarea) {
    int i, opcion, tareaModificar, indiceTarea;
    cout << "Modificar tarea.\n";
    cout << "--------------------\n";

    cout << "\nEscoja la tarea a modificar.\n";

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
int obtenerDia(int mes, int anio){
    int dia, ultimoDiaDelMes;

    //Obtener último día del mes
    switch(mes){
        case 1 && 3 && 5 && 7 && 8 && 10 && 12:
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