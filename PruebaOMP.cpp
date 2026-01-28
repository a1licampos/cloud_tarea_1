// PruebaOMP.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
// By Ali Campos

#include <iostream>
#include <random>

#ifdef _OPENMP
  #include <omp.h>
#else 
  #define omp_get_thread_num() 0
#endif

#define N 1000
#define chunk 100
#define show 15

void printArrays(float* d);

using namespace std;
int tid;

int main()
{
  double start = omp_get_wtime();

  std::random_device rd;    // Semilla aleatoria
  std::mt19937 gen(rd());   // Generador
  std::uniform_int_distribution<>dist(1, 10);   // Rango entre [1 y 10]

  std::cout << "--SUMANDO ARREGLOS EN PARALELO--\n";

  float a[N], b[N], c[N];
  int i;
  
  for (i = 0; i < N; i++)
  {
    a[i] = dist(gen);
    b[i] = dist(gen);
  }

  int pieces = chunk;

  #pragma omp parallel for \
  shared(a, b, c, pieces) private(i) \
  schedule(static, pieces)

  for (i = 0; i < N; i++)
  {
    c[i] = a[i] + b[i];
  }

  std::cout << "Imprimiendo los primeros " << show << " valores del arreglo A: " << std::endl;
  printArrays(a);

  std::cout << "Imprimiendo los primeros " << show << " valores del arreglo B: " << std::endl;
  printArrays(b);

  std::cout << "Imprimiendo los primeros " << show << " valores del arreglo C: " << std::endl;
  printArrays(c);

  double end = omp_get_wtime();
  cout << "\nTiempo transcurrido: " << end - start << endl;
}

void printArrays(float* d)
{
  for (int x = 0; x < show; x++)
  {
    std::cout << d[x] << " - ";
  }

  std::cout << std::endl;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
