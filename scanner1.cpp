#include "scanner.h"
# define UDEF -1
# define tks 200
#include <fstream>
#include <string>
#include <cctype>
#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
FILE *p,*q;
string palabra;
int contador=1,i=0;
char EOL= '\n';
string tokens[tks];

char siguiente(){ return fgetc(p);}
void retroceso(){ fseek(p,-1,SEEK_CUR);}
void acepta(){ fseek(q, ftell(p), SEEK_SET);}
void falla(){ fseek(p, ftell(q), SEEK_SET);}


void abrir(char* fname){     
     p= fopen(fname, "r");
     q= fopen(fname, "r");
}


          
void cerrar(){ 
     fclose(p); 
     fclose(q);
}

void palabras(){
     tokens[i]=palabra;
     cout<<tokens[i];
     i++;
}

void lineaDeError(){
     cout<<contador;
}

bool wsp(){
     char c = siguiente(); 
     if(c== EOL){ 
         contador=contador+1;  
     }
     if(isspace(c)){
         acepta();
         return true;      
     }        
     else{ 
      falla();
      return false;
     }
}

bool eof(){
     char c= siguiente();
     if(c == EOF) return true;
     else return false;
}
              
     
tipolex numerico(){
     palabra="";
     int actual=0, anterior;
     char c;
     
     while(actual != UDEF){          
          anterior = actual;
          c = siguiente();  
          palabra+=c;
          switch(actual ){ 
                        
              case 0:                                   
                  if( c == '0' ) actual=1;
                  else if(isdigit(c) && c != '0') actual=6;
                  else actual= UDEF;
                  break;
              case 1:                                    
                   if(isdigit(c) && c <= '7') actual=2;                    
                   else if (c == 'x' || c == 'X') actual = 3;
                   else actual= UDEF;
                   break;
              case 2:                   
                   if(isdigit(c) && c <= '7') actual=2; 
                   else actual= UDEF;
                   break;
              case 3:  
                   if(isdigit(c)) actual=4;
                   else if( c >= 'a' && c <= 'f') actual= 4;
                   else if( c >= 'A' && c <= 'F') actual= 4;                                                       
                                   
                   else actual= UDEF;
                   break;
               case 4:                                                 
                   if(isdigit(c)) actual=5;
                   else if( c >= 'a' && c <= 'f') actual= 5;
                   else if( c >= 'A' && c <= 'F') actual= 5;   
                   else actual= UDEF;
                   break;
                case 5:                       
                   if(isdigit(c)) actual=4;
                   else if( c >= 'a' && c <= 'f') actual= 4;
                   else if( c >= 'A' && c <= 'F') actual= 4;                                  
                   else actual= UDEF;
                   break;
                case 6:                                     
                   if(isdigit(c)) actual=6; 
                   else if(ispunct(c)) actual=7;
                   else actual= UDEF;
                   break;
                case 7:                    
                    if(isdigit(c)) actual=7;
                    else if(isalpha(c) && c== 'E') actual=8;
                    else if(isalpha(c) && c== 'e') actual=8;
                    else actual= UDEF;
                    break; 
                case 8:
                     if(isdigit(c)) actual=7;
                     else if(c == '+') actual=7;
                     else if(c == '-') actual=7;
                     else actual= UDEF;
                     break;  
          } 
                     
     }           
     if(anterior == 2 || anterior==5 || anterior==6 || anterior==7  ){                                 
           acepta();          
           return _num;
     }
        
falla();     
return _error; 
}          

tipolex delimitacion(){
     int actual=0, anterior;
     char c;
     palabra="";
     while(actual != UDEF){         
          anterior = actual;
          c = siguiente(); 
          palabra+=c;         
          switch(actual){ 
                        
                case 0:
                     if(c == '(') actual= 1;
                     else if( c == ')') actual= 2;
                     else if (c == '[') actual=3;
                     else if (c == ']') actual=4;
                     else actual = UDEF;
                     break;
                case 1:
                     actual = UDEF;
                     break;
                case 2:
                     actual = UDEF;
                     break;
                case 3:
                     actual = UDEF;
                     break;
                case 4:
                     actual = UDEF;
                     break;
                }
          }  
          if(anterior== 1){
                 acepta();
                 return _parIzq;
          }
          if(anterior== 2){
                 acepta();
                 return _parDer;
          }
          if(anterior== 3){
                 acepta();
                 return _corIzq;
          }
          if(anterior== 4){
                 acepta();
                 return _corDer;
          }
falla();
return _error;
}

tipolex AsigRelacionales(){
      int actual=0, anterior;
      char c;
      palabra="";   
    while(actual != UDEF){
       anterior = actual;
       c = siguiente();
       palabra+=c;  
       switch(actual){
           
         case 0:  
                           
                if(c == '<') actual = 1;
                else if(c == '=') actual = 3;
                else if( c == '>') actual = 5;
                else if( c == '!') actual = 7;
                else if(c == '?') actual=9;
                
                else  actual=UDEF;
                break;
           case 1:               
                if(c == '=') actual=2;
                else  actual=UDEF;
                break;
           case 2:                
                actual=UDEF;
                break;
           case 3:               
                if(c == '=') actual=4;
                else  actual=UDEF;
                break;
           case 4:             
                actual=UDEF;
                break;
          case 5:
               if(c == '=') actual=6;
               else  actual=UDEF;
               break;
          case 6:
                actual=UDEF;
                break;
          case 7:
               if(c == '=') actual=8;
               else  actual=UDEF;
               break;
          case 8:
                actual=UDEF;
                break;
          
          case 9:
                actual=UDEF;
                break;
          }
    } 
    if(anterior==1){
          
          acepta();
          return _menQ;
    } 
    if(anterior == 2){         
          acepta();
          return _menIg;
    }   
    if(anterior == 3){         
          acepta();
          return _opAsig;
    } 
    if(anterior == 4){      
          acepta();
          return _igualdad;          
    } 
    if(anterior == 5){         
          acepta();
          return _mayQ;
    } 
    if(anterior == 6){         
          acepta();
          return _mayIg;
    } 
    if(anterior == 8){         
          acepta();
          return _desig;
    } 
    if(anterior == 9){         
          acepta();
          return _interrogativo;
    } 
falla();      
return _error;
}   

tipolex logicos(){
     int actual=0, anterior;
     char c;
     palabra="";
     while(actual != UDEF){         
          anterior = actual;
          c = siguiente(); 
          palabra+=c;         
          switch(actual){ 
                        
                case 0:                     
                     if(c == '!') actual=5;
                     else if(c == '|') actual=3;
                     else if(c == '&') actual=1;                     
                     else actual=UDEF;
                     break;
                 case 1:                      
                      if(c == '&') actual=2;
                      else actual=UDEF;
                      break;
                 case 2:                                     
                      actual=UDEF;
                      break;
                 case 3:                      
                      if(c == '|') actual=4;
                      else actual= UDEF;
                      break;
                 case 4:                                         
                      actual= UDEF;
                      break;
                 case 5:                     
                      actual= UDEF;
                      break;
          }
     }            
     if(anterior==2){
           acepta();
           return _opConj;
     }
     if(anterior == 4){
            acepta();
            return _opDisy;
     }      
     if(anterior == 5){
             acepta();
             return _opNeg;
     }
falla();      
return _error;
}

tipolex aritmeticos(){
     int actual=0, anterior;
     char c;
     palabra="";
     
     while(actual != UDEF){        
          anterior = actual;
          c = siguiente();
          palabra+=c;
          switch(actual){ 
                        
                case 0:                                       
                     if(c == '+') actual= 1;
                     else if( c== '-') actual=2;
                     else if( c== '*') actual=3;
                     else if( c=='/') actual=4;
                     else actual= UDEF;
                     break;
                case 1:                                                                        
                      actual= UDEF;
                      break; 
                case 2:                                                       
                      actual= UDEF;
                      break;
                case 3:                                                       
                      actual= UDEF;
                      break; 
                case 4:                                                       
                      actual= UDEF;
                      break;                                      
          } 
     }    
     if(anterior== 1){
           acepta();
           return _sum;
     }
     if(anterior== 2){
           acepta();
           return _rest;
     }
     if(anterior== 3){
           acepta();
           return _mult;
     }
     if(anterior== 4){
           acepta();
           return _div;
     }
falla();
return _error;
}  
  
tipolex Puntuacion(){
     int actual=0, anterior;
     char c; 
     palabra="";  
     while(actual != UDEF){          
          anterior = actual;
          c = siguiente();   
          palabra+=c;      
          switch(actual){                        
                case 0:                                            
                     if( c == '.') actual = 1;   
                     else if( c == ',') actual=2;  
                     else if (c == ';') actual=3;
                     else if( c == ':') actual=4;  
                     else actual = UDEF;
                     break;
                 case 1:                     
                     actual=UDEF;
                     break; 
                 case 2:                  
                     actual=UDEF;
                     break;
                 case 3:                   
                     actual=UDEF;
                     break; 
                 case 4:
                     if(c == '=') actual=5;                   
                     else actual=UDEF;
                     break; 
                 case 5:
                      actual=UDEF;
                      break;                            
          }
     } 
     if(anterior==1){
             acepta();
             return _punto;
     }
     if(anterior==2){
             acepta();
             return _coma;
     }
     if(anterior==3){
             acepta();
             return _puntCom;
     }
     if(anterior==4){
             acepta();
             return _dosPuntos;
     }
     if(anterior==5){
             acepta();
             return _dosPuntosIg;
     }
falla();
return _error;
}    

tipolex identificador(){
     palabra="";
     int actual=0, anterior;
     char c;
     
     while(actual != UDEF){
          anterior = actual;
          c = siguiente();
          palabra+=c;
          switch(actual){
           
           case 0:
                if(isalpha(c)) actual = 2;
                else if (c== '_') actual=1;
                else actual = UDEF;
                break;
           
           case 1:
                if(isdigit(c) || c== '_') actual=1;  
                else if(isalpha(c)) actual=2;
                else actual= UDEF;
                break;
                
           case 2:
                if(isalnum(c)|| c == '_') actual=2;
                else actual= UDEF;
                break;
                
           }
     }    
     
     if (anterior==2){  
        if(palabra=="if "){
                  acepta();
                  return _if;
        } 
        if(palabra=="end "){
                  acepta();
                  return _end;
        }     
        if(palabra=="then "){
                  acepta();
                  return _then;
        }     
        if(palabra=="else "){
                  acepta();
                  return _else;
        }       
        if(palabra=="do "){
                  acepta();
                  return _do;
        }    
        if(palabra=="while "){
                  acepta();
                  return _while;
        }
        if(palabra=="begin "){
                  acepta();
                  return _begin;
        }
        if(palabra=="or "){
                  acepta();
                  return _or;
        }
        if(palabra=="true "){
                  acepta();
                  return _true;
        }
        if(palabra=="false "){
                  acepta();
                  return _false;
        } 
        if(palabra=="and "){
                  acepta();
                  return _and;
        }
        if(palabra=="end "){
                  acepta();
                  return _end;
        }                                                                                             
        acepta();
        return _id;
     }
falla();
return _error; 
}  

bool comentarios(){
     int actual=0, anterior;
     char c;
     palabra="";
     while(actual != UDEF){        
          anterior = actual;
          c = siguiente();
          
          switch(actual){ 
                        
                case 0:                    
                     if( c == '{') actual = 1;
                     else actual= UDEF;
                     break;
                case 1:
                     if(c != '}' && c != EOF) actual=1;                     
                     else if(c == EOF) actual=2;                     
                     else if(c == '}') actual=2;                                     
                     else actual= UDEF;
                     break; 
                case 2:                    
                     actual=UDEF;
                     break;
          }          
     }              
     if(anterior== 2){          
             acepta();
             return true;
     }
falla();
return false; 
} 

bool errores(){
     int actual=0, anterior;
     char c;
     
     while(actual != UDEF){        
          anterior = actual;
          c = siguiente();
          
          switch(actual){ 
               case 0:                    
                    if(isdigit(c) || c == '_') actual=1;
                   if( c >= '!' && c <= '}') actual= 1;
                    else actual=UDEF;
                    break;
               case 1:              
                    if(isdigit(c)) actual=1;
                    if(isalpha(c)) actual=1;
                    if( c >= '!' && c <= '}') actual= 1;
                    else actual=UDEF;
                    break;
          }
     }
     if(anterior==1){
            acepta();
            return true;
     }
}

tipolex scanner(){
      
      while (wsp());
        tipolex t;
         
        if((t = AsigRelacionales()) != _error)  return t; 
        if((t=delimitacion()) != _error) return t;  
        if((t=numerico()) != _error) return t; 
        if((t = logicos()) != _error) return t; 
        if(comentarios()) return _com;     
        if((t=aritmeticos()) != _error) return t;  
        if((t=Puntuacion()) != _error) return t;  
        if((t=identificador()) != _error) return t;
        if(errores()) return _error;             
        if(eof()) return _eof;     
}
