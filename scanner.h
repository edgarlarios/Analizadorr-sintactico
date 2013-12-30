#ifndef  __definiciones_
#define __definiciones_
#include <cstdlib>

typedef enum{_error, _id, _eof,_nNat,_nHexa, _nFlot,_nOct,
             _parIzq, _parDer, _corIzq, _corDer,
             _opAsig,_mayQ,_menQ,_mayIg,_menIg, _desig ,_igualdad,
             _opConj, _opDisy, _opNeg, _com,
              _rest,_sum,_mult,_div, _true, _false, _and,
              _punto,_puntCom,_coma, _dosPuntos, _interrogativo,_dosPuntosIg,
              _if,_do,_while,_else,_then,_begin,_end, _num, _or, _not,
              _body=100, _eseq, _eseqP, _assign, _quest, _questP, _prop,
              _propP, _clause, _clauseP, _rel, _relP, _exp, _expP, _term, _termP, _fact,} tipolex;


extern void abrir(char*);
extern void cerrar();
extern tipolex scanner();
extern void lineaDeError();
extern void palabras();
extern bool LL_one();





# endif
