#include<cstdio>
#include <iostream>
#include "scanner.h"
#include<cstdlib>
#include<stack>
using namespace std;
int X=0;
int pi;
tipolex t;
stack<int> pila;
                   
   
int T(int X,tipolex t){ 
 //  cout<<X<<" T: "<<t<<endl;
   switch(X){
   
   case _body:
        cout<<"entra a body"<<endl;
        palabras();
        if(t == _begin){                  
            pila.push(_end);
            pila.push(_eseq);
            pila.push(_begin);
            return 1;
        }
        break;
        
   case _eseq:
        cout<<"entra a eseq"<<endl;
        palabras();
        if(t==_id){
               pila.push(_eseqP);
               pila.push(_assign);
               return 2;
        } 
         break; 
        
   case _eseqP:
         cout<<"entra a eseqPRIMA"<<endl;
         palabras();
        if(t==_puntCom){
             pila.push(_eseqP);
             pila.push(_assign);
             pila.push(_puntCom);
             return 3;             
        }
        else if(t==_end){
              return 4;
        }
         break;
        
   case _assign:
        cout<<"entra a assign"<<endl;
        palabras();
        if(t==_id){
            pila.push(_quest);
            pila.push(_dosPuntosIg);
            pila.push(_id);
            return 5;
        }
        
   case _quest:
         cout<<"entra a questttt"<<endl;
         palabras();
         if(t==_rest){
             pila.push(_questP);
             pila.push(_prop);
             return 6;
          }   
          else if(t== _not){
             pila.push(_questP);
             pila.push(_prop);
             return 6;
         }   
         else if(t== _parIzq){
             pila.push(_questP);
             pila.push(_prop);
             return 6;
         }   
         else if(t== _num){
             pila.push(_questP);
             pila.push(_prop);
             return 6;
         }   
         else if(t== _true){
             pila.push(_questP);
             pila.push(_prop);
             return 6;
         }   
         else if(t== _false){
              cout<<"entra al false"<<endl;
             pila.push(_questP);
             pila.push(_prop);
             return 6;
         }
         break;   
   
   case _questP:
         cout<<"entra a questPRIMA"<<endl;
         palabras();
          if(t==_puntCom || t==_end || t== _dosPuntos || t== _parDer){
               return 8;
          }          
          else if(t==_interrogativo){
               pila.push(_quest);
               pila.push(_dosPuntos);
               pila.push(_quest);
               pila.push(_interrogativo);
               return 7;
          }
          break;
           
   case _prop:
         cout<<"entra a prop"<<endl;
         palabras();
          if(t==_rest){
             pila.push(_propP);
             pila.push(_clause);
             return 9;
          }   
          else if(t==_not){
             pila.push(_propP);
             pila.push(_clause);
             return 9;
          }   
          else if(t==_parIzq){
             pila.push(_propP);
             pila.push(_clause);
             return 9;
          }   
          else if(t==_num){
             pila.push(_propP);
             pila.push(_clause);
             return 9;
          }   
          else if(t==_true){
             pila.push(_propP);
             pila.push(_clause);
             return 9;
          }   
          else if(t==_false){
             pila.push(_propP);
             pila.push(_clause);
             return 9;
         } 
         break;  
       
    case _propP:
          cout<<"entra a PROPPRIMA"<<endl;
          palabras();
         if(t==_puntCom || t== _interrogativo || t==_end || t== _parDer || t==_dosPuntos){
              return 11;    
         }
        else if(t==_or){
               pila.push(_propP);
               pila.push(_clause);
               pila.push(_or);
               return 10;
        }
        break;
         
     case _clause:
          cout<<"entra a clause"<<endl;
          palabras();
           if(t==_rest){
             pila.push(_clauseP);
             pila.push(_rel);
             return 12;
          }   
          else if(t==_not){
             pila.push(_clauseP);
             pila.push(_rel);
             return 12;
         }   
          else if(t==_parIzq){
             pila.push(_clauseP);
             pila.push(_rel);
             return 12;
         }   
          else if(t==_num){
             pila.push(_clauseP);
             pila.push(_rel);
             return 12;
         }   
          else if(t==_true){
             pila.push(_clauseP);
             pila.push(_rel);
             return 12;
         }   
          else if(t==_false){
             pila.push(_clauseP);
             pila.push(_rel);
             return 12;
         }    
         break;
          
    case _clauseP:
         cout<<"entra a ClausePRIMA"<<endl;
         palabras();
            
          if(t==_puntCom || t== _parDer || t== _end || t== _dosPuntos || t== _or || t== _interrogativo){
               return 14;
          }            
          else if(t==_and){
                pila.push(_clauseP);   
                pila.push(_rel);         
                pila.push(_and);
                return 13; 
          }  
          break;
           
    case _rel:
          cout<<"entra a rel"<<endl;
          palabras();
         if(t==_rest || t== _parIzq || t== _num || t==_not || t==_true || t==_false ){
               pila.push(_relP);
               pila.push(_exp); 
               return 15;
         }
         break;
          
    case _relP:
        cout<<"entra a relPRIMA"<<endl;
        palabras();
         if(t==_puntCom || t==_interrogativo || t==_end || t==_and || t==_or || t==_dosPuntos || t== _parDer){
                 return 22;
         }
         else if(t==_mayQ){
                 pila.push(_exp);
                 pila.push(_mayQ);
                 return 17;
         }
         else if(t==_menQ){
                 pila.push(_exp);
                 pila.push(_menQ); 
                 return 16;       
         }
          else if(t==_menIg){
                 pila.push(_exp);
                 pila.push(_menIg);
                 return 18;
         }
         else if(t==_mayIg){
                 pila.push(_exp);
                 pila.push(_mayIg);
                 return 19;
         }
         else if(t==_igualdad){
                 pila.push(_exp);
                 pila.push(_igualdad);
                 return 20; 
         }           
         else if(t==_desig){
                 pila.push(_exp);
                 pila.push(_desig);
                 return 21;
         } 
         break;
         
   case _exp:
         cout<<"entra a exp"<<endl;
         palabras();
        if(t==_rest || t== _parIzq || t== _num || t==_not || t==_true || t==_false ){
                 pila.push(_expP); 
                 pila.push(_term);
                 return 23;
        }          
        break;
         
   case _expP:
        cout<<"entra a expPRIMA"<<endl;
        palabras();
        if(t==_menQ || t==_mayQ || t==_menIg || t==_mayIg || t==_igualdad || t== _parDer || t== _puntCom ){
                    return 26;
        }
        else if(t==_desig || t==_and || t==_or || t== _interrogativo || t== _dosPuntos || t== _end){
                    return 26;
        }
        else if(t== _sum){
                  pila.push(_expP); 
                  pila.push(_term); 
                  pila.push(_sum); 
                  return 24;
        }
        else if(t== _rest){
                  pila.push(_expP); 
                  pila.push(_term); 
                  pila.push(_rest);
                  return 25;
        }
        break; 
 
   case _term:
         cout<<"entra a term"<<endl;
         palabras();
        if(t==_rest || t== _parIzq || t== _num || t==_not || t==_true || t==_false ){
               pila.push(_termP);
               pila.push(_fact); 
               return 27;
         }
         break;
   
   case _termP:
        cout<<"entra a termprima"<<endl;
        palabras();
        if(t==_menQ || t==_mayQ || t==_menIg || t==_mayIg || t==_igualdad || t==_sum || t== _rest || t== _parDer){
                    return 30;
        }
        else if(t==_desig || t==_and || t==_or || t== _interrogativo || t== _dosPuntos || t== _end || t== _puntCom){
                    return 30;
        }
        else if(t== _mult){
               pila.push(_termP);
               pila.push(_fact);
               pila.push(_mult);
               return 28;
        }
        else if(t== _div){
               pila.push(_termP);
               pila.push(_fact);
               pila.push(_div);
               return 29;
        }
        break;
         
   case _fact:
        cout<<"entra a fact"<<endl;
        palabras();
         if(t==_rest){
             pila.push(_fact);
             pila.push(_rest);
             return 31;
         }   
          else if(t==_not || t== _parDer){
             pila.push(_fact);
             pila.push(_not);
             return 32;
         }   
         else if(t==_parIzq){
             pila.push(_parDer);
             pila.push(_quest);
             pila.push(_parIzq);
             return 33;
         }   
         else if(t==_num){
             pila.push(_num);
             return 34;
         }   
         else if(t==_true){
             pila.push(_true);
             return 35;
         }   
         else if(t==_false){
             pila.push(_false);    
             return 36;         
         }    
         break;
   }
return _error;
}

bool LL_one(){     
 t=scanner();
 pila.push(_body);
        
   do{      
        cout<<endl;
        X=pila.top();
        pila.pop();    
        if(X < 100){
            if(X==t){
                t=scanner();
            }
            else{
                return false;
            }
        } 
        else{
            pi=T(X,t);
            if(pi == _error){
                return false;
            }           
        }             
      } while(!pila.empty());
      return true;
}
               
                
                     
                     
                     
                     
        
