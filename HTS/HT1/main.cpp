#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cctype>

using namespace std;

void RegistrarProfesor();
void RegistrarEstudiante();
void Menu();

struct Profesor
{
    int tipo_P;
    int id_P;
    char CUI_P[15];
    char nombre_P[25];
    char curso[25];
};

struct Estudiante
{
    int tipo_E;
    int id_E;
    char CUI_E[15];
    char nombre_E[25];
    char carnet[25];
};

bool ExisteArchivo(string nombre)
{
    ifstream ifile;
    ifile.open(nombre);
    if (ifile)
    {
        return true;
    }
    return false;
}

void CrearArchivo()
{

    // Creando archivo para el registro de Profesores
    if (!ExisteArchivo("Registro_P.bin"))
    {
        FILE *archivo;
        archivo = fopen("Registro_P.bin", "wb");
        if (archivo == NULL)
        {
            exit(1);
        }
        fclose(archivo);
    }

    // Creando archivo para el registro de Estudiantes
    if (!ExisteArchivo("Registro_E.bin"))
    {
        FILE *archivo;
        archivo = fopen("Registro_E.bin", "wb");
        if (archivo == NULL)
        {
            exit(1);
        }
        fclose(archivo);
    }
}

void NuevoRegistro(string rol)
{
    cout << "¿Desea registrar un nuevo " << rol << "?. Presione y/n: ";
    string opcion = "";
    cin >> opcion;
    if (opcion == "y")
    {
        system("clear");
        cout << "Registrando nuevo " << rol << endl;
        if (rol == "profesor")
        {
            RegistrarProfesor();
        }
        if (rol == "estudiante")
        {
            RegistrarEstudiante();
        }
    }
    else if (opcion == "n")
    {
        system("clear");
        Menu();
    }
    else
    {
        cout << "Opción incorrecta" << endl;
        NuevoRegistro(rol);
    }
}

bool ValidarCUI(string dato, int tamano, bool validacion)
{
    if (dato.length() == 0)
    {
        return false;
    }

    for (int i = 0; i < dato.size(); i++)
    {
        try
        {
            if (!isdigit(dato[i]))
            {
                return false;
            }
        }
        catch (exception e)
        {
            return false;
        }
    }

    if (validacion == true)
    {
        if (dato.length() != tamano)
        {
            return false;
        }
    }
    return true;
}

void RegistrarProfesor()
{

    // Primero verificamos que el archivo existe.
    if (ExisteArchivo("Registro_P.bin"))
    {
        // Abrimos primeramente el archivo
        FILE *archivo;
        archivo = fopen("Registro_P.bin", "ab");

        // Empezamos a crear nuestra estructura.
        Profesor nuevo;
        cout << "======== REGISTRO DE PROFESORES ========" << endl;
        cout << "Ingrese el tipo de profesor: ";
        cin >> nuevo.tipo_P;
        cout << "Ingrese el ID del profesor: ";
        cin >> nuevo.id_P;
        cout << "Ingrese el CUI del profesor: ";
        cin >> nuevo.CUI_P;
        while (!ValidarCUI(nuevo.CUI_P, 13, true))
        {
            cout << "CUI inválildo. Vuelva a ingresar el CUI del profesor: ";
            cin >> nuevo.CUI_P;
        }
        cout << "Ingrese el nombre del profesor: ";
        cin >> nuevo.nombre_P;
        cout << "Ingrese el curso del profesor: ";
        cin >> nuevo.curso;

        // Escribimos y cerramos el archivo binario.
        fwrite(&nuevo, sizeof(Profesor), 1, archivo);
        fclose(archivo);

        // Llamamos nuestra fución si desea registrar un nuevo profesor
        NuevoRegistro("profesor");
    }
    else
    {
        cout << "Archivo no existente" << endl;
        CrearArchivo();
        // exit(1);
    }
}

void RegistrarEstudiante()
{

    // Primero verificamos que el archivo existe.
    if (ExisteArchivo("Registro_E.bin"))
    {
        // Abrimos primeramente el archivo
        FILE *archivo;
        archivo = fopen("Registro_E.bin", "ab");

        // Empezamos a crear nuestra estructura.
        Estudiante nuevo;
        cout << "======== REGISTRO DE ESTUDIANTES ========" << endl;
        cout << "Ingrese el tipo de estudiante: ";
        cin >> nuevo.tipo_E;
        cout << "Ingrese el ID del estudiante: ";
        cin >> nuevo.id_E;
        cout << "Ingrese el CUI del estudiante: ";
        cin >> nuevo.CUI_E;
        while (!ValidarCUI(nuevo.CUI_E, 13, true))
        {
            cout << "CUI inválildo. Vuelva a ingresar el CUI del estudiante: ";
            cin >> nuevo.CUI_E;
        }
        cout << "Ingrese el nombre del estudiante: ";
        cin >> nuevo.nombre_E;
        cout << "Ingrese el carnet del estudiante: ";
        cin >> nuevo.carnet;

        // Escribimos y cerramos el archivo binario.
        fwrite(&nuevo, sizeof(Estudiante), 1, archivo);
        fclose(archivo);

        // Llamamos nuestra fución si desea registrar un nuevo profesor
        NuevoRegistro("estudiante");
    }
    else
    {
        cout << "Archivo no existente" << endl;
        CrearArchivo();
        // exit(1);
    }
}

void RegresarMenu()
{
    string opcion = "";
    cout << "Para regresar al menú principal presione la tecla m. ";
    cin >> opcion;

    if (opcion == "m")
    {
        system("clear");
        Menu();
    }else{
        cout << endl << "Opción incorrecta. ";
        RegresarMenu();
    }
}

void VerRegistro(string rol)
{

    if (rol == "Profesor")
    {
        if (ExisteArchivo("Registro_P.bin"))
        {
            FILE *archivo;
            archivo = fopen("Registro_P.bin", "rb");

            Profesor temporal;
            fread(&temporal, sizeof(Profesor), 1, archivo);
            cout << "============ TABLA DE REGISTRO (PROFESORES) ============" << endl;
            while (!feof(archivo))
            {
                printf("%i %i %s %s %s \n", temporal.tipo_P, temporal.id_P, temporal.CUI_P, temporal.nombre_P, temporal.curso);
                fread(&temporal, sizeof(Profesor), 1, archivo);
            }
            cout << "=========================================================" << endl
                 << endl
                 << endl
                 << endl;
            fclose(archivo);
        }
    }

    if (rol == "Estudiante")
    {
        if (ExisteArchivo("Registro_E.bin"))
        {
            FILE *archivo;
            archivo = fopen("Registro_E.bin", "rb");

            Estudiante temporal;
            fread(&temporal, sizeof(Estudiante), 1, archivo);
            cout << "============ TABLA DE REGISTRO (ESTUDIANTES) ============" << endl;
            while (!feof(archivo))
            {
                printf("%i %i %s %s %s \n", temporal.tipo_E, temporal.id_E, temporal.CUI_E, temporal.nombre_E, temporal.carnet);
                fread(&temporal, sizeof(Estudiante), 1, archivo);
            }
            cout << "=========================================================" << endl
                 << endl
                 << endl
                 << endl;
            fclose(archivo);
        }

        // Para regresar al menu estando en las tablas de registros.
        RegresarMenu();
    }
}

void Menu()
{
    int opcion = 0;
    while (opcion != 4)
    {
        cout << "|========= BIENVENIDO =========|" << endl
             << "|                              |" << endl
             << "|Christian Blanco              |" << endl
             << "|202000173                     |" << endl
             << "|                              |" << endl
             << "|                              |" << endl
             << "|1. Registro de profesor.      |" << endl
             << "|2. Registro de estudiante.    |" << endl
             << "|3. Ver registros.             |" << endl
             << "|4. Salir                      |" << endl
             << "|                              |" << endl
             << "================================" << endl
             << "Seleccione una opción: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            system("clear");
            cout << "Elegiste la opcion 1." << endl;
            RegistrarProfesor();
            break;
        case 2:
            system("clear");
            cout << "Elegiste la opcion 2." << endl;
            RegistrarEstudiante();
            break;
        case 3:
            system("clear");
            cout << "Elegiste la opcion 3." << endl;
            VerRegistro("Profesor");
            VerRegistro("Estudiante");
            break;
        case 4:
            system("clear");
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion incorrecta, presione cualquier tecla para continuar." << endl;
            break;
        }
    }
}

int main()
{
    /* code */
    Menu();

    return 0;
}
