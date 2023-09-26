#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include "Articulo.h"

typedef struct{
    Articulo vipd;
    struct nodo *izq;
    struct nodo *der;
}nodo;

typedef struct{
    nodo *raiz;
    nodo *padre;
    nodo *cur;
    int cargados;
}Arbol;

void inicializarABB(Arbol *arbol){
    //crea un arbol vacío y lo deja en disposición de ser usado
    arbol->raiz = arbol->padre = arbol->cur = NULL;
    (*arbol).cargados = 0;
}

int isEmptyABB(Arbol *arbol){
    if (arbol->raiz == NULL){
        return 1;
    } else {
        return 0;
    }
}

void resetABB(Arbol *arbol){
    arbol->cur = arbol->padre = arbol->raiz;
}


void localizarABB(Arbol *arbol, char *idBuscado, int *rLocalizar, int *cantConsultas){
    // exito: se detiene en nodo interno
    // fracaso: nodo externo /NULL
    arbol->cur = arbol->padre = arbol->raiz; //reset
    *rLocalizar = 0;
    if (arbol->raiz != NULL) {
        while ((arbol->cur != NULL) && strcmpi((arbol->cur->vipd).codigo, idBuscado)!=0){
            //avanzar
            if (strcmpi((arbol->cur->vipd).codigo, idBuscado)>0){
                arbol->padre = arbol->cur;
                arbol->cur = arbol->cur->izq;
            } else {
                arbol->padre = arbol->cur;
                arbol->cur = arbol->cur->der;
            }
            (*cantConsultas)++;
        }
        if (arbol->cur != NULL){
            //lo encontro
            (*cantConsultas)++;
            *rLocalizar = 1; // Localizar exitoso
        } else {
            *rLocalizar = 0; // Localizar falla
        }
    } else {
        *rLocalizar = 2; //No hay elementos en la lista
    }
}

void altaABB(Arbol *arbol, int *rAlta, Articulo art, int lecOp, float *costoMax, float *sumCostos, int *cantExitos){
    int rLocalizar = 0, intBasuraInt = 0;
    float sumAux = 0;
    *rAlta = 0;

    localizarABB(arbol, art.codigo, &rLocalizar, &intBasuraInt);

    if (rLocalizar == 1){
        *rAlta = 0; //Como se encontró el elemento entonces el alta falla
    } else {
        nodo *n = (nodo*)malloc(sizeof(nodo));

        if (n != NULL){ //reviso que me haya dado memoria
            n->vipd = art;
            //CASO 1 -- Arbol vacio
            if (arbol->raiz == NULL){
                arbol->raiz = n;
                n->izq = n->der = NULL;
                *rAlta = 1; //alta exitosa
                ((*arbol).cargados)++;
                sumAux+= 1.5;
            } else { //CASO 2 - Me dejo el loc el cur en null y doy alta
                if(strcmpi(arbol->padre->vipd.codigo, n->vipd.codigo)>0){
                    //izq
                    arbol->padre->izq = n;
                } else {
                    arbol->padre->der = n;
                }
                n->izq = n->der = NULL;
                *rAlta = 1; //alta exitosa
                ((*arbol).cargados)++;
                sumAux+= 1.5;
            }

            if(lecOp == 1){
                *sumCostos += sumAux;
                if(sumAux > *costoMax){
                    *costoMax = sumAux;
                }
                (*cantExitos)++;
            }

        } else { //no habia memoria para nodos
            *rAlta = 2; //El alta falla porque no hay más espacio en la estructura
        }
    }
}

void bajaABB(Arbol *arbol, int *rBaja, Articulo art, int lecOp, float *costoMax, float *sumCostos, int *cantExitos){
    int rLocalizar = 0, eleccion = 0, intBasuraInt = 0;
    float sumAux = 0;
    nodo *n, *curAux, *padreAux;
    *rBaja = 0;

    localizarABB(arbol,art.codigo,&rLocalizar,&intBasuraInt);

    if(rLocalizar == 1){
        if(lecOp==0){
            printf("El articulo que quiere borrar es: \n");
            printArt(arbol->cur->vipd);

            do{
                printf("\n\n Esta seguro que quiere borrarlo? \n"
                       "<1> -------- Si --------\n"
                       "<2> -------- No --------\n");
                scanf("%d", &eleccion);
                getchar();
            } while (eleccion < 1 || eleccion > 2);
        } else {
            if (arbol->cur->vipd.cantidad == art.cantidad && strcmpi(arbol->cur->vipd.desc,art.desc)==0 && strcmpi(arbol->cur->vipd.marca,art.marca)==0 && arbol->cur->vipd.precio==art.precio && strcmpi(arbol->cur->vipd.tipoArt,art.tipoArt)==0 ){
                eleccion = 1;
            }
        }

            if (eleccion == 1){
                //CASO 0: El nodo a eliminar es la raiz
                if(arbol->raiz == arbol->cur){
                    //Ver a sus hijos para elegir el caso, porque solo puedo eliminar si no tiene
                    //Caso 0.1: La raiz no tiene hijos
                    if (arbol->raiz->der == NULL && arbol->raiz->izq == NULL){
                        n = arbol->raiz;
                        free(n);
                        arbol->raiz=NULL;
                        sumAux+= 0.5;
                    //Caso 0.2: 2 hijos
                    } else if (arbol->raiz->izq != NULL && arbol->raiz->der != NULL){
                        padreAux = arbol->raiz;
                        curAux = arbol->cur->izq;
                        while (curAux->der != NULL){
                            padreAux = curAux;
                            curAux = curAux->der;
                        }

                        if(padreAux->izq == curAux){
                            padreAux->izq = curAux->izq;
                            sumAux+=0.5;

                        } else {
                            //antes de aplicar la politica reviso al hijo izq del nodo a reemplazar
                            if(curAux->izq != NULL){
                                padreAux->der = curAux->izq;
                                sumAux+= 0.5;
                            } else {
                                padreAux->der = NULL;
                                sumAux+= 0.5;
                            }
                        }

                        arbol->cur->vipd = curAux->vipd;
                        sumAux+=1.5; //por la copia de datos
                        free(curAux);


                     //Caso 0.3: 1 hijo
                    } else{
                        if(arbol->raiz->izq != NULL){
                            n = arbol->raiz;
                            arbol->raiz = arbol->raiz->izq;
                            free(n);
                            sumAux+= 0.5;
                        } else {
                            n = arbol->raiz;
                            arbol->raiz = arbol->raiz->der;
                            free(n);
                            sumAux+= 0.5;
                        }
                    }
                } else {
                    //CASO 1: No tiene hijos.
                    if(arbol->cur->izq == NULL && arbol->cur->der == NULL){
                        if (arbol->padre->izq == arbol->cur){
                            //significa que tengo que reconectar el lado izq del padre
                            n = arbol->cur;
                            free(n);
                            arbol->padre->izq = NULL;
                            sumAux+= 0.5;
                        } else { //por los controles anteriores del localizar, si no es izq es der
                            n = arbol->cur;
                            free(n);
                            arbol->padre->der = NULL;
                            sumAux+= 0.5;
                        }

                    //CASO 2: 2 hijos - Política mayor de los menores
                    } else if(arbol->cur->izq != NULL && arbol->cur->der != NULL){
                        //no hago reset, tomo simplemente el cur del localizar
                        padreAux = arbol->cur;
                        curAux = arbol->cur->izq;
                        while (curAux->der != NULL){
                            padreAux = curAux;
                            curAux = curAux->der;
                            //No los consideramos en los costos porque son auxiliares que consultan celdas
                        }

                        if(padreAux->izq == curAux){
                            padreAux->izq = curAux->izq;
                            sumAux+=0.5;

                        } else {
                            //antes de aplicar la politica reviso al hijo izq del nodo a reemplazar
                            if(curAux->izq != NULL){
                                padreAux->der = curAux->izq;
                                sumAux+= 0.5;
                            } else{
                                padreAux->der = NULL;
                                sumAux+= 0.5;
                            }
                        }

                        //antes de aplicar la politica reviso al hijo izq del nodo a reemplazar

                        arbol->cur->vipd = curAux->vipd;
                        sumAux+=1.5; //por la copia de datos
                        //curAux->der = curAux->izq = NULL;
                        //sumAux++;
                        free(curAux);

                    //CASO 3: 1 solo hijo (que puede tener mas cosas)
                    } else {
                        if (arbol->padre->izq == arbol->cur){
                            if(arbol->cur->izq != NULL){
                                n = arbol->cur;
                                arbol->padre->izq = arbol->cur->izq;
                                free(n);
                                sumAux+= 0.5;
                            } else {
                                n = arbol->cur;
                                arbol->padre->izq = arbol->cur->der;
                                free(n);
                                sumAux+= 0.5;
                            }
                        } else {
                            if(arbol->cur->der != NULL){
                                n = arbol->cur;
                                arbol->padre->der = arbol->cur->der;
                                free(n);
                                sumAux+= 0.5;
                            } else {
                                n = arbol->cur;

                                arbol->padre->der = arbol->cur->izq;
                                free(n);
                                sumAux+= 0.5;
                            }
                        }
                    }
                }


            *rBaja = 1;
            ((*arbol).cargados)--;

            if(lecOp == 1){
                (*cantExitos)++;
                *sumCostos += sumAux;
                if(sumAux > *costoMax){
                    *costoMax = sumAux;
                }
            }

            } else {
                //BAJA NO EXITOSA PORQUE SE CANCELÓ
                *rBaja = 0;
            }
    } else {
        //BAJA NO EXITOSA
        *rBaja = 2;
    }
}

Articulo evocarABB(Arbol *arbol, int *rEvocar,  char *idBuscado, int lecOp, int *costoMaxExito, int *sumCostosExito, int *cantExitos, int *costoMaxFracaso, int *sumCostosFracaso, int *cantFracasos){
    int rLocalizar = 0, cantConsultas = 0;
    *rEvocar = 0;
    Articulo basura;

    localizarABB(arbol,idBuscado,&rLocalizar,&cantConsultas);

    if (rLocalizar==1){
        *rEvocar = 1;
        if(lecOp == 1){
            *sumCostosExito += cantConsultas;
            (*cantExitos)++;
            if(*costoMaxExito < cantConsultas){
                *costoMaxExito = cantConsultas;
            }
        }
        return arbol->cur->vipd;
    } else {
        *rEvocar = 0;
        if(lecOp == 1){
            *sumCostosFracaso += cantConsultas;
            (*cantFracasos)++;
            if(*costoMaxFracaso < cantConsultas){
                *costoMaxFracaso = cantConsultas;
            }
        }
        return basura;
    }
}

void preorden(Arbol *arbol){
    nodo *aux;
    if(arbol->raiz != NULL){
        printArt(arbol->raiz->vipd);
        if (arbol->raiz->izq != NULL){
             aux = arbol->raiz->izq;
             printf("\nHijo izquierdo: %s\n",aux->vipd.codigo);
        } else {
             printf("\nHijo izquierdo: NULL\n");
        }
        if (arbol->raiz->der != NULL){
             aux = arbol->raiz->der;
             printf("\nHijo derecho: %s\n",aux->vipd.codigo);
        } else {
             printf("\nHijo derecho: NULL\n");
        }
        system("pause");
        preorden(&arbol->raiz->izq);
        preorden(&arbol->raiz->der);
    }
}

void vaciarABB(Arbol *arbol){
    if (arbol->raiz != NULL){
        vaciarABB(&arbol->raiz->izq);
        vaciarABB(&arbol->raiz->der);
        free(arbol->raiz);
    }
}


#endif // ABB_H_INCLUDED
