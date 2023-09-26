#ifndef LSOBT_H_INCLUDED
#define LSOBT_H_INCLUDED
#include "Articulo.h"

void localizarLSOBT(Articulo *arreglo, char *idBuscado, int *pos, int *rLocalizar, int cargados, int *cantConsultas){
    //Función strcmpi (No usamos strcmp porque es CaseSensitive)
    //0 si a = b
    //<0 si a < b
    //>0 si a > b
    *pos = 0; *rLocalizar = 0;

    if(cargados > 0){
     // li inclusivo, ls inclusivo, segmento más grande a la derecha
        int li=0,ls=cargados-1;

        //pos es el testigo
        (*pos) = floor((li+ls)/2);

        while ((li <= ls) && (strcmpi(arreglo[*pos].codigo, idBuscado) != 0)){

            if (strcmpi(arreglo[*pos].codigo, idBuscado) < 0){
                li = (*pos) + 1;
            } else {
                ls = (*pos) - 1;
            }

            (*cantConsultas)++;

        (*pos) = floor((li+ls)/2);
        //Reiteramos la consigna
        }

        if(li>ls){
            (*pos)=li;
        }

        if (li<=ls){
            (*cantConsultas)++;
            *rLocalizar = 1; // Localizar exitoso
        } else {
            *rLocalizar = 0; // Localizar fallido
        }
    } else {
        *rLocalizar = 2; //No hay elementos en la lista
    }

}

void altaLSOBT(Articulo *arreglo, int *cargados, int *rAlta, Articulo aux, int lecOp, float *costoMax, float *sumCostos, int *cantExitos){
    *rAlta = 0;
    int rLocalizar = 0, pos = 0, intBasura = 0;
    float sumAux = 0;

    if (*cargados < MAX){
            localizarLSOBT(arreglo, aux.codigo, &pos, &rLocalizar, *cargados, &intBasura);
            if(rLocalizar == 1){
                *rAlta = 0; //Como se encontró el elemento entonces el alta falla
            } else {

                //Corrimiento denegado en caso de cargados = 0
                if(*cargados > 0){
                        for(int i=(*cargados); i>pos; i--){
                            arreglo[i] = arreglo [i-1];
                            if(lecOp == 1){
                                //1 porque significa que estamos evaluando costos
                                sumAux += 1.5;
                            }
                        }
                }
            arreglo[pos] = aux;
            (*cargados)++;

            if(lecOp == 1){
                *sumCostos += sumAux;
                if (sumAux > *costoMax){
                    *costoMax = sumAux;
                }
                (*cantExitos)++;
            }

            *rAlta = 1; //El alta fue exitosa
            }
        } else {
            *rAlta = 2; //El alta falla porque no hay más espacio en la estructura
    }
}

void bajaLSOBT(Articulo *arreglo, int *cargados, int *rBaja, Articulo aux, int lecOp, float *costoMax, float *sumCostos, int *cantExitos){
    *rBaja = 0;
    int eleccion = 0, rLocalizar = 0, pos = 0, intBasura = 0;
    float sumAux = 0;
    localizarLSOBT(arreglo, aux.codigo, &pos, &rLocalizar, *cargados, &intBasura);


    if(rLocalizar == 1){
        if(lecOp == 0){
            //ESTAMOS EN ADMINISTRACIÓN
            printf("El articulo que quiere borrar es: \n");
            printArt(arreglo[pos]);

            do{
                printf("\n\n Esta seguro que quiere borrarlo? \n"
                       "<1> -------- Si --------\n"
                       "<2> -------- No --------\n");
                scanf("%d", &eleccion);
                getchar();
            } while (eleccion < 1 || eleccion > 2);

        } else {
            //ESTAMOS EN OPERACIONES
            if (strcmpi(arreglo[pos].tipoArt, aux.tipoArt)==0 &&
                strcmpi(arreglo[pos].marca, aux.marca)==0 &&
                strcmpi(arreglo[pos].desc, aux.desc)==0 &&
                arreglo[pos].precio == aux.precio &&
                arreglo[pos].cantidad == aux.cantidad){
                eleccion = 1;
            }
        }

        if (eleccion == 1){
            for(int i = pos; i < (*cargados - 1); i++){
                arreglo[i] = arreglo[i+1];
                if (lecOp == 1){
                    sumAux += 1.5;
                }
            }

            *rBaja = 1; //Baja exitosa
            (*cargados)--;

            if (lecOp == 1){
                *sumCostos += sumAux;
                if(sumAux > *costoMax){
                    *costoMax = sumAux;
                }
                (*cantExitos)++;
            }

        } else {
            *rBaja = 0;
        }

    } else {
        *rBaja = 0; //Baja falida
    }

}

Articulo evocarLSOBT(Articulo *arreglo, char *idBuscado, int cargados, int *rEvocar, int lecOp, int *costoMaxExito, int *sumCostosExito, int *cantExitos, int *costoMaxFracaso, int *sumCostosFracaso, int *cantFracasos){
    int rLocalizar = 0, pos = 0, cantConsultas = 0;
    Articulo aux;
    localizarLSOBT(arreglo, idBuscado, &pos, &rLocalizar, cargados, &cantConsultas);
    if (rLocalizar == 1){
        *rEvocar = 1;
        if(lecOp == 1){
            *sumCostosExito += cantConsultas;
            (*cantExitos)++;
            if(*costoMaxExito < cantConsultas){
                *costoMaxExito = cantConsultas;
            }
        }
        return arreglo[pos];
    } else {
        *rEvocar = 0;
        if(lecOp == 1){
            *sumCostosFracaso += cantConsultas;
            (*cantFracasos)++;
            if(*costoMaxFracaso < cantConsultas){
                *costoMaxFracaso = cantConsultas;
            }
        }
        return aux;
    }
}

#endif // LSOBT_H_INCLUDED
