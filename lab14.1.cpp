/*Datos de personas
Autor: Jesús Antonio Murcia
Fecha: 15 de mayo*/

#include <iostream>
#include <locale.h>

using namespace std;

struct datosPersonas{
    string nombre;
    int diaNacimiento;
    string mesDeNacimiento;
    int anoNacimiento;
};

int obtenerNumMes(string mensaje, string mensajeDeError);
int obtenerAno(string mensaje, string mensajeDeError);
int obtenerDiaDelMes(string mensaje, string mensajeDeError, int diasDelMes);

int main(){
    setlocale(LC_ALL, "");
    //Crear vector de datos
    datosPersonas agenda[100];
    int contador= 0;
    string meses[12]= {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    string continuar;
    string filtrarPorMes;
    int filtroMes;

    cout<<"Este programa recopila datos de la fecha nacimiento de las personas y puedes filtrar por mes";
    do{    
        //Añadir personas
        do{
            string nombre;
            int diaDeNacimiento;
            int numDeDiasDelMes;
            int mes;
            int ano;
            datosPersonas persona;

            cout<<"\nIngrese el nombre de la persona: ";
            cin>> nombre;

            cout<<"\nIngrese el número del mes de nacimiento:\n";
            for (int i = 0; i < 12; i++){
                cout<< i+1<< "."<< meses[i] << endl;
            }

            mes= obtenerNumMes("Seleccione el mes: ", "El valor ingresado debe ser un número entre 1 y 12");

            ano= obtenerAno("\nIngrese el año de nacimiento", "Debe ingresar un valor número entre 1900 y 2024");

            //Revisar los dias del mes y obtener el valor
            switch (mes){
                case 2:
                    //Revisar si es bisiesto
                    if (ano % 4 == 0){
                        numDeDiasDelMes= 29;
                    }else{
                        numDeDiasDelMes= 28;
                    }
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                    numDeDiasDelMes= 30;
                default:
                    numDeDiasDelMes= 31;
                    break;
            }

            diaDeNacimiento= obtenerDiaDelMes("Ingrese el día de nacimiento: ", "El valor debe ser un número contenido en los días del mes ", numDeDiasDelMes);

            //Añadir datos a la agenda
            persona.nombre= nombre;
            persona.mesDeNacimiento= meses[mes - 1];
            persona.diaNacimiento= diaDeNacimiento;
            persona.anoNacimiento= ano;
            agenda[contador]= persona;
            contador++;

            cout<<"Escriba si para añadir a más personas ";
            cin>>continuar;
        }while(continuar == "si" );

        //Mostrar agenda
        cout<<"\nEsta es su agenda:";
        for (int i = 0; i < contador; i++){
            cout<<"\nNombre: "<< agenda[i].nombre;
            cout<<"\nDía de nacimiento: "<< agenda[i].diaNacimiento;
            cout<<"\nMes de nacimiento: "<< agenda[i].mesDeNacimiento;
            cout<<"\nAñó de nacimiento: "<< agenda[i].anoNacimiento;
            cout<< "\n\t\t------\n";
        }
        
        //Preguntar para obtener mes
        cout<<"Escriba sí para filtrar la agenda por mes ";
        cin>> filtrarPorMes;

        if (filtrarPorMes == "sí" || filtrarPorMes == "si"){
            int numPersonasFiltradas = 0;
            cout<<"\nIngrese el número del mes de nacimiento:\n";
            for (int i = 0; i < 12; i++){
                cout<< i+1<< "."<< meses[i] << endl;
            }

            filtroMes= obtenerNumMes("Seleccione el mes: ", "El valor ingresado debe ser un número entre 1 y 12 ");

            //Imprimir el filtro de datos
            for (int i= 0; i < contador; i++){
                if (agenda[i].mesDeNacimiento == meses[filtroMes - 1]){
                    cout<<"\nNombre: "<< agenda[i].nombre;
                    cout<<"\nDía de nacimiento: "<< agenda[i].diaNacimiento;
                    cout<<"\nMes de nacimiento: "<< agenda[i].mesDeNacimiento;
                    cout<<"\nAñó de nacimiento: "<< agenda[i].anoNacimiento;
                    cout<< "\n\t\t------\n";
                    numPersonasFiltradas++;
                }
            }

            if (numPersonasFiltradas == 0){
                cout<< "No hay nadie que haya nacido en este mes";
            }
        }


        cout<<"Escriba si para reiniciar el programa ";
        cin>>continuar;
    }while(continuar == "si");

    cout<<"\nGracias por usar el programa, ¡nunca cambies!";
    return 0;
}

int obtenerNumMes(string mensaje, string mensajeDeError){
    //Declarar variables
    int entero;
    cout<< mensaje;
    cin>> entero;
    while(cin.fail() || entero < 1 || entero > 12){
        cin.clear();
        cin.ignore();
        cout<<mensajeDeError;
        cin>> entero;
    }
    return entero;
}

int obtenerAno(string mensaje, string mensajeDeError){
    //Declarar variables
    int entero;
    cout<< mensaje;
    cin>> entero;
    while(cin.fail() || entero < 1899 || entero > 2024){
        cin.clear();
        cin.ignore();
        cout<<mensajeDeError;
        cin>> entero;
    }
    return entero;
}

int obtenerDiaDelMes(string mensaje, string mensajeDeError, int diasDelMes){
    //Declarar variables
    int entero;
    cout<< mensaje;
    cin>> entero;
    while(cin.fail() || entero < 1 || entero > diasDelMes){
        cin.clear();
        cin.ignore();
        cout<<mensajeDeError;
        cin>> entero;
    }
    return entero;  
}