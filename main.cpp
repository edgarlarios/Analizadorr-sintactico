#include<cstdio>
#include <iostream>
#include "scanner.h"
#include<cstdlib>

using namespace std;

int main(int argc, char *argv[]){
    
    abrir("prueba.txt");
  
bool resultado; 

       
     resultado=LL_one();  
     if( resultado==true){
         cout<<"la cadena es aceptada"<<endl;
     }   
     else{
          cout<<"la cadena no es aceptada"<<endl;
     }     

  cerrar();
  system("PAUSE");
  return EXIT_SUCCESS;
}

