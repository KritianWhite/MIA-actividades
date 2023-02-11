#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>

using namespace std;

// para el menu
void menuGeneral();
int menuError(string opcion, int minimo, int maximo);
void procesarOpcion(int opcion);
void menuProfesor();
void menuEstudiante();
void menuReporte();
void crearArchivo();

// para validaciones
bool esNumeroValido(string dato, int largo, bool validarLongitud);
void imprimirValoresProfesor();
void imprimirValoresEstudiante();

struct Profesor
{
    int Id_profesor;
    char CUI[14];
    char Nombre[25];
    char Curso[25];
};

struct Estudiante
{
    int Id_estudiante;
    char CUI[14];
    char Nombre[25];
    char Carnet[10];
};

int main()
{
    string entrada;
    int opcion;
    const int minMenuGeneral = 1, outMenuGeneral = 4;

    crearArchivo();
    do
    {
        menuGeneral();
        cin >> entrada;

        opcion = menuError(entrada, minMenuGeneral, outMenuGeneral);

        if (opcion != outMenuGeneral)
        {
            procesarOpcion(opcion);
            continue;
        }

    } while (opcion != outMenuGeneral);

    return 0;
}

// Funciones Menu y Submenus
void menuGeneral()
{
    cout << "*********MENU GENERAL**********" << endl
         << "***Christian Blanco-202000173**" << endl
         << "*1. Registro de Profesor      *" << endl
         << "*2. Registro de Estudiante    *" << endl
         << "*3. Ver Registros             *" << endl
         << "*4. Salir                     *" << endl
         << "*******************************" << endl;

    cout << "Ingrese opcion:";
}

int menuError(string dato, int minimo, int maximo)
{
    int opcion;
    while (!esNumeroValido(dato, 1, true))
    {
        if (opcion < minimo || opcion > maximo)
        {
            cout << "Invalida, ingrese una opcion: ";
            cin >> dato;
        }
        else
        {
            break;
        }
    }
    opcion = stoi(dato);
    return opcion;
}

void procesarOpcion(int opcion)
{
    string entrada;
    int opMenu;
    const int minMenuGeneral = 1, outMenuGeneral = 2;

    switch (opcion)
    {
    case 1:
        menuProfesor();
        break;
    case 2:
        menuEstudiante();
        break;
    case 3:
        imprimirValoresProfesor();
        imprimirValoresEstudiante();
        break;
    }
}

bool esNumeroValido(string dato, int largo, bool validaLongitud)
{
    if (dato.length() == 0)
    {
        return false;
    }

    for (int j = 0; j < dato.size(); j++)
    {
        try
        {
            if (!isdigit(dato[j]))
                return false;
        }
        catch (exception e)
        {
            return false;
        }
    }

    if (validaLongitud == true)
    {
        if (dato.length() != largo)
            return false;
    }
    return true;
}

void menuProfesor()
{
    FILE *arch;
    arch = fopen("archivoP.bin", "ab");
    if (arch == NULL)
        exit(1);

    system("clear");
    Profesor nuevo;
    cout << "***DATOS NUEVO PROFESOR***" << endl
         << "**L.Santiago***201213505**" << endl;

    cout << "Ingrese ID: ";
    cin >> nuevo.Id_profesor;

    cout << "Ingresa CUI: ";
    cin >> nuevo.CUI;

    while (!esNumeroValido(nuevo.CUI, 13, true))
    {
        cout << "Invalido, ingrese CUI: ";
        cin >> nuevo.CUI;
    }

    cout << "Ingrese nombre: ";
    cin >> nuevo.Nombre;

    cout << "Ingrese curso: ";
    cin >> nuevo.Curso;

    fwrite(&nuevo, sizeof(Profesor), 1, arch);
    fclose(arch);

    system("clear");
    cout << "Registro almacenado!" << endl
         << endl;
}

void menuEstudiante()
{
    FILE *arch;
    arch = fopen("archivoE.bin", "ab");
    if (arch == NULL)
        exit(1);

    system("clear");
    Estudiante nuevoE;
    cout << "***DATOS NUEVO ESTUDIANTE***" << endl
         << "****L.Santiago*201213505****" << endl;
    cout << "Ingrese ID: ";
    cin >> nuevoE.Id_estudiante;

    cout << "Ingresa CUI: ";
    cin >> nuevoE.CUI;

    while (!esNumeroValido(nuevoE.CUI, 13, true))
    {
        cout << "Invalido, ingrese CUI: ";
        cin >> nuevoE.CUI;
    }

    cout << "Ingrese nombre: ";
    cin >> nuevoE.Nombre;

    cout << "Ingrese carnet: ";
    cin >> nuevoE.Carnet;

    fwrite(&nuevoE, sizeof(Estudiante), 1, arch);
    fclose(arch);

    system("clear");
    cout << "Registro almacenado!" << endl
         << endl;
}

bool existsFile(string name)
{
    ifstream ifile;
    ifile.open(name);
    if (ifile)
    {
        return true;
    }
    return false;
}

void crearArchivo()
{
    if (!existsFile("archivoP.bin"))
    {
        cout << "Entro a crear archivo" << endl;
        FILE *arch;
        arch = fopen("archivoP.bin", "wb");
        if (arch == NULL)
            exit(1);

        fclose(arch);
    }

    if (!existsFile("archivoE.bin"))
    {
        cout << "Entro a crear archivo" << endl;
        FILE *arch;
        arch = fopen("archivoE.bin", "wb");
        if (arch == NULL)
            exit(1);

        fclose(arch);
    }
}

void imprimirValoresProfesor()
{
    FILE *arch;
    arch = fopen("archivoP.bin", "rb");
    if (arch == NULL)
        exit(1);

    Profesor tmp;
    fread(&tmp, sizeof(Profesor), 1, arch);
    while (!feof(arch))
    {
        printf("%i %s %s %s \n", tmp.Id_profesor, tmp.CUI, tmp.Nombre, tmp.Curso);
        fread(&tmp, sizeof(Profesor), 1, arch);
    }
    fclose(arch);
}

void imprimirValoresEstudiante()
{
    FILE *arch;
    arch = fopen("archivoE.bin", "rb");
    if (arch == NULL)
        exit(1);

    Estudiante tmp;
    fread(&tmp, sizeof(Estudiante), 1, arch);

    while (!feof(arch))
    {
        printf("%i %s %s %s \n", tmp.Id_estudiante, tmp.CUI, tmp.Nombre, tmp.Carnet);
        fread(&tmp, sizeof(Estudiante), 1, arch);
    }
    fclose(arch);
}