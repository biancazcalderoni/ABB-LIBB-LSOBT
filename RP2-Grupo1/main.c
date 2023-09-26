#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <malloc.h>
#include "ABB.h"
#include "LIBB.h"
#include "LSOBT.h"

// GRUPO 1 - Santiago Politti Gil y Bianca Zoé Calderoni Alvarez

/*
    Analizando y comparando el comportamiento de las estructuras con respecto a las distinas operaciones, podemos lograr obtener algunas conclusiones.
    Primero hablando un poco en general del comportamiento que tienen las estructuras...

    La LIBB es una lista que combina la parte sencilla de trabajar con una LSOBB y que nos proporciona, gracias a realizar corrimientos con punteros, una gran diferencia
    de costos cuando nos referimos a altas y bajas con respecto a una LSOBB convencional, para ser más específicos, la LIBB cuesta 3 veces menos en altas y bajas.
    En cuanto al evocar, los costos van a ser un poco superiores que en otras estructuras, ya que tenemos que consultar 2 celdas por cada vez que busquemos un determinado
    valor.

    La LSOBT es una lista secuencial ordenada con busqueda binaria por trisección, la cuál proporciona muy bajos costos a la hora de localizar elementos, pero que no es
    tan optima a la hora de hacer corrimientos para altas y bajas. Esto se debe a que, al igual que la LIBB, su crecimiento en costos depende de la cantidad de elementos que
    tenga el lote de datos que se utilizará en el programa. A mayor cantidad de elementos, posiblemente los costos sean mayores.

    Evaluando los costos a-priori del ABB, diremos que no debería ser la estructura de datos utilizada si sabemos que los datos vienen de manera ordenada, ya que no se sacará el provecho
    correspondiente a la estructura y puede hacer que tenga unos costos elevados. En el caso del archivo operaciones, ya que el primer elemento resultó ser
    el elemento del medio, aunque el resto vinieran parcialmente ordenados, no fue costoso como una lista vinculada.
    Respecto a altas y bajas, un elemento se da de alta en nodos externos, por lo que su costo de inserción siempre será constante, y en las bajas, lo peor que puede suceder
    es que el nodo a eliminar tenga dos hijos, lo cual realmente no es un problema debido a la política de reemplazo.


    Ahora si pasamos a hablar de los costos obtenidos en las diferentes operaciones

         *******************************************************************
         *                     Comparacion de Estructuras                  *
         *******************************************************************
         *   Costos                LIBB     LSOBT      ABB                 *
         *   ------------------------------------------------------------- *
         *   MAX.ALTA              7.50     22.50      1.50                *
         *   MEDIO ALTA            1.81     5.44       1.50                *
         *   MAX.BAJA              27.00    81.00      2.00                *
         *   MEDIO BAJA            10.50    31.50      1.04                *
         *   MAX. EVOC. EX.        14       6          10                  *
         *   MED. EVOC. EX.        10.76    4.51       5.09                *
         *   MAX. EVOC. NO EX.     12       4          5                   *
         *   MED. EVOC. NO EX.     8.00     3.41       2.04                *
         *                                                                 *
         *******************************************************************

    En las ALTAS podemos ver que la menos conveniente siempre será la LSOBT, ya que al ser secuencial ordenada, cada vez que uno quiera insertar
    deberá realizar costosos corrimientos, mientras que la LIBB aprovecha el uso de punteros y vuelve conveniente las altas. En el ABB las inserciones
    siempre van a ser menos costosas que las otras estructuras, debido a que se realizan en nodos externos y no hay corrimientos.

    En las BAJAS podemos ver que la menos conveniente siempre será la LSOBT, ya que al ser secuencial ordenada, cada vez que uno quiere eliminar
    deberá realizar costosos corrimientos, mientras que la LIBB aprovecha el uso de punteros y vuelve conveniente las bajas. En el ABB comprobamos que,
    aunque el peor caso era la política de reemplazo, seguía siendo lo más conveniente, debido a que la copia de datos más la modificación de punteros = 2.
    Y en costos medios, realizar las bajas en arboles resulta más eficiente.

                En la EVOCACIÓN EXITOSA podemos ver que las dos estructuras que usan busqueda binaria tienen costos muy similares, casi indiferentes. Por lo
                que para elegir entre ambas, este criterio no sería concluyente.

    En las EVOCACIONES podemos ver que hay grandes diferencias entre las dos listas secuenciales. Esto se debe principalemente a que en la LIBB, como mencionamos
    anteriormente, realizamos consultas a 2 celdas cada vez que querramos comparar un valor. Si bien ambas estructuras tienen la particularidad de tener algoritmos
    de busqueda eficientes, se puede apreciar una notable diferencia a medida que crece la cantidad de elementos con la que se trabaja. Finalmente, los árboles pueden
    ser tan eficientes como las otras si el lote de datos se lo permite. En este caso, obtuvo resultados promedio, quedando en algunas ocasiones por debajo y en otras
    sobre los costos de la LSOBT.

    Con todo lo que hemos tenido en cuenta podemos concluir algunos casos donde nos conviene utilizar una estructura antes que otra...

    En caso de que la lista de Artículos venga ordenada, el ABB sería una mala opción a elegir, ya que sería prácticamente una lista vinculada.
    En caso de que lo que más se necesite sean dar altas, la estructura más eficiente posiblemente sería el ABB.
    En caso de que lo que más se necesite sean dar bajas, la estructura más eficiente posiblemente sería el ABB.
    En caso de que demos de alta una única vez y nuestro programa se centre en busquedas, entonces la LSOBT sería la mejor opción ya que está especializada en dar
    buen rendimiento en busquedas.

    ********************************************************************************************************************************************************************

*/
                                Arbol *arbolABB; //Hola profe, mírelo ahí, el revoltoso se escapó del main
int main(){

        int typeEstructura = 0, decision = 0, codOperador=0, opciones = 0, cargadosLIBB = 0, cargadosLSOBT = 0, rAlta = 0, rBaja = 0, rEvocar = 0, intBasura = 0;
        float floatBasura = 0;
        char codigoAux[9], tipoArtAux[21], marcaAux[31], descAux[101];
        Articulo aux, *arregloLIBB[MAX], arregloLSOBT[MAX];

        inicializarABB(&arbolABB);

        //Le avisamos al usuario que puede salir en cualquier momento con 0
        printf("------------------------- ATENCION -------------------------\n"
               "En cualquier etapa del programa puede ingresar '0' para salir\n");
               system("pause");
               system("cls");

        do{
            do {
                printf("\n*****************************************************************************\n"
                       "*                               Opciones                                    *\n"
                       "*****************************************************************************\n"
                       "*                                                                           *\n"
                       "*   <0> Salir                                                               *\n"
                       "*   <1> Administrar Estructuras                                             *\n"
                       "*   <2> Comparar Estructuras                                                *\n"
                       "*                                                                           *\n"
                       "*****************************************************************************\n\n");
                scanf("%d", &opciones);
                getchar();
                system("cls");
            }while (opciones<0 || opciones >2);

            switch(opciones){
                case 0:{
                    break;
                }
                case 1:{
                     do{
                        do{
                            printf("\n*****************************************************************************\n"
                                   "*                      Con que estructura desea trabajar?                   *\n"
                                   "*****************************************************************************\n"
                                   "*                                                                           *\n"
                                   "*   <0> Salir                                                               *\n"
                                   "*   <1> Lista Invertida - Busqueda Binaria                                  *\n"
                                   "*   <2> Lista Secuencial Ordenada - Busqueda Binaria Triseccion             *\n"
                                   "*   <3> Arbol Binario de Busqueda                                           *\n"
                                   "*                                                                           *\n"
                                   "*****************************************************************************\n\n");
                            scanf("%d", &typeEstructura);
                            getchar();
                            system("cls");
                        } while (typeEstructura<0 || typeEstructura>3);

                        switch(typeEstructura){
                             default:{
                                 do {
                                    do {
                                        if(typeEstructura == 1){
                                            printf("\n~~~~~~~~ Usted esta trabajando con la LIBB ~~~~~~~~\n\n");
                                        } else if (typeEstructura == 2){
                                            printf("\n~~~~~~~~ Usted esta trabajando con la LSOBT ~~~~~~~~\n\n");
                                        } else if (typeEstructura == 3){
                                            printf("\n~~~~~~~~ Usted esta trabajando con la ABB ~~~~~~~~\n\n");
                                        }
                                        printf("\n*************************************************************************\n"
                                               "*                           Que desea hacer?                            *\n"
                                               "*************************************************************************\n"
                                               "*                                                                       *\n"
                                               "*   <0> Salir                                                           *\n"
                                               "*   <1> Ingresar nuevo articulo                                         *\n"
                                               "*   <2> Eliminar articulo existente                                     *\n"
                                               "*   <3> Consultar un articulo                                           *\n"
                                               "*   <4> Mostrar estructura                                              *\n"
                                               "*   <5> Memorizacion previa                                             *\n"
                                               "*                                                                       *\n"
                                               "*************************************************************************\n\n");
                                        scanf("%d", &decision);
                                        getchar();
                                        system("cls");
                                    } while (decision<0 || decision>5);

                                    switch(decision){
                                        case 0:{
                                            break;
                                        }
                                        case 1:{
                                            //Pedir datos y meter en aux
                                            printf("\n ---------------------------------------------------------- \n");
                                            printf("Ingrese el codigo del articulo: \n");
                                            scanf("%[^\n]s", codigoAux);
                                            getchar();

                                            // Si el usuario ingresa 0 sale de la ejecución
                                            if (strcmp(codigoAux, "0") == 0){
                                                printf("Se ha cancelado el alta ya que ha escrito '0' \n");
                                                break;
                                            }

                                            strcpy(aux.codigo,codigoAux);

                                            printf("Ingrese el tipo de articulo: \n");
                                            scanf("%[^\n]s", tipoArtAux);
                                            getchar();

                                            // Si el usuario ingresa 0 sale de la ejecución
                                            if (strcmp(tipoArtAux, "0") == 0){
                                                printf("Se ha cancelado el alta ya que ha escrito '0' \n");
                                                break;
                                            }

                                            strcpy(aux.tipoArt,tipoArtAux);

                                            printf("Ingrese la marca: \n");
                                            scanf("%[^\n]s", marcaAux);
                                            getchar();

                                            // Si el usuario ingresa 0 sale de la ejecución
                                            if (strcmp(marcaAux, "0") == 0){
                                                printf("Se ha cancelado el alta ya que ha escrito '0' \n");
                                                break;
                                            }

                                            strcpy(aux.marca,marcaAux);

                                            printf("Ingrese la descripcion del articulo: \n");
                                            scanf("%[^\n]s", descAux);
                                            getchar();

                                            // Si el usuario ingresa 0 sale de la ejecución
                                            if (strcmp(descAux, "0") == 0){
                                                printf("Se ha cancelado el alta ya que ha escrito '0' \n");
                                                break;
                                            }

                                            strcpy(aux.desc,descAux);

                                            do{
                                                printf("Ingrese el precio del producto (No puede ser 0 ni menor): \n");
                                                scanf("%lf",&aux.precio);
                                            } while(aux.precio<0);

                                            // Si el usuario ingresa 0 sale de la ejecución
                                            if (aux.precio == 0){
                                                printf("Se ha cancelado el alta ya que ha escrito '0' \n");
                                                break;
                                            }

                                            do{
                                                printf("Ingrese la cantidad de stock (No puede ser 0 ni menor) : \n");
                                                scanf("%d",&aux.cantidad);
                                            } while(aux.cantidad<0);

                                            // Si el usuario ingresa 0 sale de la ejecución
                                            if (aux.cantidad == 0){
                                                printf("Se ha cancelado el alta ya que ha escrito '0' \n");
                                                break;
                                            }
                                            switch(typeEstructura){
                                                case 1:{
                                                    altaLIBB(arregloLIBB, &cargadosLIBB, &rAlta, aux, 0, &floatBasura, &floatBasura, &intBasura);
                                                    break;
                                                }
                                                case 2:{
                                                    altaLSOBT(arregloLSOBT, &cargadosLSOBT, &rAlta, aux, 0, &floatBasura, &floatBasura, &intBasura);
                                                    break;
                                                }
                                                case 3:{
                                                    altaABB(&arbolABB,&rAlta,aux,0,&floatBasura,&floatBasura,&intBasura);
                                                    break;
                                                }
                                            }

                                            if(rAlta == 1){
                                                printf("\n El alta ha sido exitosa \n");
                                            } else if (rAlta == 0){
                                                printf("\n El alta ha fallado porque el elemento ya se encuenta en la estructura \n");
                                            } else {
                                                printf("\n El alta ha fallado porque no hay espacio en la estructura \n");
                                            }

                                            break;

                                        }
                                        case 2:{
                                            //Eliminar
                                            printf("\n ---------------------------------------------------------- \n");
                                            printf("Ingrese el codigo del articulo a eliminar: \n");
                                            scanf("%[^\n]s", codigoAux);
                                            getchar();

                                            // Si el usuario ingresa 0 sale de la ejecución
                                            if (strcmp(codigoAux, "0") == 0){
                                                printf("Se ha cancelado el alta ya que ha escrito '0' \n");
                                                break;
                                            }

                                            strcpy(aux.codigo,codigoAux);
                                            //Pedimos solo el código pero lo metemos en un Artículo Aux

                                            switch(typeEstructura){
                                                case 1:{
                                                    bajaLIBB(arregloLIBB, &cargadosLIBB, &rBaja, aux, 0, &floatBasura, &floatBasura, &intBasura);
                                                    break;
                                                }
                                                case 2:{
                                                    bajaLSOBT(arregloLSOBT, &cargadosLSOBT, &rBaja, aux, 0, &floatBasura, &floatBasura, &intBasura);
                                                    break;
                                                }
                                                case 3:{
                                                    bajaABB(&arbolABB,&rBaja,aux,0,&floatBasura,&floatBasura,&intBasura);
                                                    break;
                                                }
                                            }

                                            if(rBaja == 1){
                                                printf("\n La baja ha sido exitosa \n");
                                            } else if (rBaja == 0){
                                                printf("\n La baja ha fallado \n");
                                            }

                                            break;

                                        }
                                        case 3:{
                                            //Consultar
                                            printf("\n ---------------------------------------------------------- \n");
                                            printf("Ingrese el codigo del articulo a consultar: \n");
                                            scanf("%[^\n]s", codigoAux);
                                            getchar();

                                            // Si el usuario ingresa 0 sale de la ejecución
                                            if (strcmp(codigoAux, "0") == 0){
                                                printf("Se ha cancelado el alta ya que ha escrito '0' \n");
                                                break;
                                            }

                                            switch(typeEstructura){
                                                case 1:{
                                                    aux = evocarLIBB(arregloLIBB, codigoAux, cargadosLIBB, &rEvocar, 0, &intBasura, &intBasura, &intBasura, &intBasura, &intBasura, &intBasura);
                                                    if(rEvocar == 1){
                                                        printf("Se econtro el articulo y es:\n");
                                                        printArt(aux);
                                                    } else {
                                                        printf("No se encontro el articulo\n");
                                                    }
                                                    break;
                                                }
                                                case 2:{
                                                    aux = evocarLSOBT(arregloLSOBT, codigoAux, cargadosLSOBT, &rEvocar, 0, &intBasura, &intBasura, &intBasura, &intBasura, &intBasura, &intBasura);
                                                    if(rEvocar == 1){
                                                        printf("Se econtro el articulo y es:\n");
                                                        printArt(aux);
                                                    } else {
                                                        printf("No se encontro el articulo\n");
                                                    }
                                                    break;
                                                }
                                                case 3:{
                                                    aux = evocarABB(&arbolABB, &rEvocar, codigoAux, 0, &intBasura, &intBasura, &intBasura, &intBasura, &intBasura, &intBasura);
                                                    if(rEvocar == 1){
                                                        printf("Se econtro el articulo y es:\n");
                                                        printArt(aux);
                                                    } else {
                                                        printf("No se encontro el articulo\n");
                                                    }
                                                    break;
                                                }
                                            }
                                            break;
                                        }
                                        case 4:{
                                            switch (typeEstructura){
                                                case 1:{

                                                    //MOSTRAR ESTRUCTURA LIBB
                                                    if (cargadosLIBB == 0){
                                                        printf("No se encuentran elementos cargados \n\n");
                                                    } else {
                                                        for(int i=0; i < cargadosLIBB; i++){
                                                            printArt(*arregloLIBB[i]);
                                                            system("pause");
                                                        }
                                                    }
                                                    break;
                                                }
                                                case 2:{

                                                    //MOSTRAR ESTRUCTURA LSOBT
                                                    if (cargadosLSOBT == 0){
                                                        printf("No se encuentran elementos cargados \n\n");
                                                    } else {
                                                        for(int i=0; i < cargadosLSOBT; i++){
                                                            printArt(arregloLSOBT[i]);
                                                            system("pause");
                                                        }
                                                    }
                                                    break;
                                                }
                                                case 3: {

                                                    //MOSTRAR ESTRUCTURA ABB
                                                    if (isEmptyABB(&arbolABB)){
                                                        printf("No se encuentran elementos cargados \n\n");
                                                    } else {
                                                        preorden(&arbolABB);
                                                    }
                                                    break;
                                                }
                                            }
                                            break;
                                        }
                                        case 5:{
                                            FILE *fp;
                                            Articulo art;
                                            if ((fp = fopen("Articulos.txt","r"))== NULL){
                                                printf("No se puedo abrir el archivo\n");
                                                return 0;
                                            }
                                            if (ferror(fp)!=0) printf("Ocurrio un error en la lectura\n");
                                            else {
                                                while(!(feof(fp))){
                                                    fgets(art.codigo,10,fp);
                                                    art.codigo[strlen(art.codigo)-1] = '\0';
                                                    fgets(art.tipoArt,21,fp);
                                                    art.tipoArt[strlen(art.tipoArt)-1] = '\0';
                                                    fgets(art.marca,31,fp);
                                                    art.marca[strlen(art.marca)-1] = '\0';
                                                    fgets(art.desc,101,fp);
                                                    art.desc[strlen(art.desc)-1] = '\0';
                                                    fscanf(fp,"%lf",&art.precio);
                                                    fgetc(fp);
                                                    fscanf(fp,"%d",&art.cantidad);
                                                    fgetc(fp);

                                                    switch (typeEstructura){
                                                        case 1:{
                                                            altaLIBB(arregloLIBB, &cargadosLIBB, &rAlta, art, 0, &floatBasura, &floatBasura, &intBasura);
                                                            break;
                                                        }
                                                        case 2:{
                                                            altaLSOBT(arregloLSOBT, &cargadosLSOBT, &rAlta, art, 0, &floatBasura, &floatBasura, &intBasura);
                                                            break;
                                                        }
                                                        case 3:{
                                                            altaABB(&arbolABB,&rAlta,art,0,&floatBasura,&floatBasura,&intBasura);
                                                            break;
                                                        }
                                                    }
                                                }

                                                printf("Se cargaron correctamente todos los articulos \n\n");
                                            fclose(fp);
                                            }
                                            break;
                                        }
                                    }
                                 } while (decision != 0);
                                 break;
                            }
                            case 0:{
                                break;
                            }
                        }
                     } while (typeEstructura != 0);
                     break;
                }
                case 2:{

                Articulo *n;

                //LIBERAMOS LIBB
                for(int i=0; i<cargadosLIBB; i++){
                    n = arregloLIBB[i];
                    free(n);
                }
                cargadosLIBB = 0;

                //LIBERAMOS LSOBT
                cargadosLSOBT = 0;

                //LIBERAMOS ABB
                vaciarABB(&arbolABB);
                inicializarABB(&arbolABB);


                //Costos Alta LIBB
                float costoMaxAltaLIBB=0, sumCostosAltaLIBB=0, costoMedioAltaLIBB=0;
                int cantExitosAltaLIBB=0;

                //Costos Baja LIBB
                float costoMaxBajaLIBB=0, sumCostosBajaLIBB=0, costoMedioBajaLIBB=0;
                int cantExitosBajaLIBB=0;

                //costos EvocarLIBB Exito
                float costoMedioEvoExitoLIBB=0;
                int costoMaxEvoExitoLIBB=0, sumCostosEvoExitoLIBB=0, cantExitosEvoLIBB=0;

                //costos EvocarLIBB Fracaso
                float costoMedioEvoFracasoLIBB=0;
                int costoMaxEvoFracasoLIBB=0, sumCostosEvoFracasoLIBB=0, cantFracasosEvoLIBB=0;

                //Costos Alta LSOBT
                float costoMaxAltaLSOBT=0, sumCostosAltaLSOBT=0, costoMedioAltaLSOBT=0;
                int cantExitosAltaLSOBT=0;

                //Costos Baja LSOBT
                float costoMaxBajaLSOBT=0, sumCostosBajaLSOBT=0, costoMedioBajaLSOBT=0;
                int cantExitosBajaLSOBT=0;

                //costos EvocarLSOBT Exito
                float costoMedioEvoExitoLSOBT=0;
                int costoMaxEvoExitoLSOBT=0, sumCostosEvoExitoLSOBT=0, cantExitosEvoLSOBT=0;

                //costos EvocarLSOBT Fracaso
                float costoMedioEvoFracasoLSOBT=0;
                int costoMaxEvoFracasoLSOBT=0, sumCostosEvoFracasoLSOBT=0, cantFracasosEvoLSOBT=0;

                //Costos Alta ABB
                float costoMaxAltaABB=0, sumCostosAltaABB=0, costoMedioAltaABB=0;
                int cantExitosAltaABB=0;

                //Costos Baja ABB
                float costoMaxBajaABB=0, sumCostosBajaABB=0, costoMedioBajaABB=0;
                int cantExitosBajaABB=0;

                //costos EvocarABB Exito
                float costoMedioEvoExitoABB=0;
                int costoMaxEvoExitoABB=0, sumCostosEvoExitoABB=0, cantExitosEvoABB=0;

                //costos EvocarABB Fracaso
                float costoMedioEvoFracasoABB=0;
                int costoMaxEvoFracasoABB=0, sumCostosEvoFracasoABB=0, cantFracasosEvoABB=0;


                                FILE *fp;
                                Articulo art;
                                if ((fp = fopen("Operaciones.txt","r"))== NULL){
                                    printf("No se puedo abrir el archivo\n");
                                    return 0;
                                }

                                if (ferror(fp)!=0) printf("Ocurrio un error en la lectura\n");
                                    else {
                                        while(!(feof(fp))){
                                            fscanf(fp, "%d", &codOperador);
                                            fgetc(fp);
                                            fscanf(fp, "%[^\n]", &art.codigo);
                                            fgetc(fp);

                                            if(codOperador == 1 || codOperador == 2){
                                                fgets(art.tipoArt,21,fp);
                                                art.tipoArt[strlen(art.tipoArt)-1] = '\0';
                                                fgets(art.marca,31,fp);
                                                art.marca[strlen(art.marca)-1] = '\0';
                                                fgets(art.desc,101,fp);
                                                art.desc[strlen(art.desc)-1] = '\0';
                                                fscanf(fp,"%lf",&art.precio);
                                                fgetc(fp);
                                                fscanf(fp,"%d",&art.cantidad);
                                                fgetc(fp);

                                                if(codOperador == 1){

                                                    altaLIBB(arregloLIBB, &cargadosLIBB, &rAlta, art, 1, &costoMaxAltaLIBB, &sumCostosAltaLIBB, &cantExitosAltaLIBB);
                                                    altaLSOBT(arregloLSOBT, &cargadosLSOBT, &rAlta, art, 1, &costoMaxAltaLSOBT, &sumCostosAltaLSOBT, &cantExitosAltaLSOBT);
                                                    altaABB(&arbolABB,&rAlta,art,1,&costoMaxAltaABB,&sumCostosAltaABB,&cantExitosAltaABB);

                                                } else if (codOperador == 2){
                                                    bajaLIBB(arregloLIBB, &cargadosLIBB, &rBaja, art, 1, &costoMaxBajaLIBB, &sumCostosBajaLIBB, &cantExitosBajaLIBB);
                                                    bajaLSOBT(arregloLSOBT, &cargadosLSOBT, &rBaja, art, 1, &costoMaxBajaLSOBT, &sumCostosBajaLSOBT, &cantExitosBajaLSOBT);
                                                    bajaABB(&arbolABB,&rBaja,art,1,&costoMaxBajaABB,&sumCostosBajaABB,&cantExitosBajaABB);
                                                }

                                            }else if (codOperador == 3){
                                                evocarLIBB(arregloLIBB, art.codigo, cargadosLIBB, &rEvocar, 1, &costoMaxEvoExitoLIBB, &sumCostosEvoExitoLIBB, &cantExitosEvoLIBB, &costoMaxEvoFracasoLIBB, &sumCostosEvoFracasoLIBB, &cantFracasosEvoLIBB);
                                                evocarLSOBT(arregloLSOBT, art.codigo, cargadosLSOBT, &rEvocar, 1, &costoMaxEvoExitoLSOBT, &sumCostosEvoExitoLSOBT, &cantExitosEvoLSOBT, &costoMaxEvoFracasoLSOBT, &sumCostosEvoFracasoLSOBT, &cantFracasosEvoLSOBT);
                                                evocarABB(&arbolABB, &rEvocar, art.codigo, 1, &costoMaxEvoExitoABB, &sumCostosEvoExitoABB,&cantExitosEvoABB, &costoMaxEvoFracasoABB, &sumCostosEvoFracasoABB ,&cantFracasosEvoABB);
                                            } else {
                                                printf("Error, el codigo de operacion no fue reconocido\n");
                                            }

                                            codOperador = 0;

                                        }

                                        printf("Se cargaron correctamente todos los articulos \n\n");
                                    fclose(fp);
                                    }


                                    //COSTO MEDIO DE ALTAS

                                    costoMedioAltaLIBB = sumCostosAltaLIBB / cantExitosAltaLIBB;
                                    costoMedioAltaLSOBT = sumCostosAltaLSOBT / cantExitosAltaLSOBT;
                                    costoMedioAltaABB = sumCostosAltaABB / cantExitosAltaABB;

                                    //COSTO MEDIO DE BAJAS

                                    costoMedioBajaLIBB = sumCostosBajaLIBB / cantExitosBajaLIBB;
                                    costoMedioBajaLSOBT = sumCostosBajaLSOBT / cantExitosBajaLSOBT;
                                    costoMedioBajaABB = sumCostosBajaABB / cantExitosBajaABB;

                                    //COSTO MEDIO DE EVOCAR EXITO

                                    costoMedioEvoExitoLIBB = sumCostosEvoExitoLIBB *1.0 / cantExitosEvoLIBB;
                                    costoMedioEvoExitoLSOBT = sumCostosEvoExitoLSOBT *1.0 / cantExitosEvoLSOBT;
                                    costoMedioEvoExitoABB = sumCostosEvoExitoABB *1.0 / cantExitosEvoABB;

                                    //COSTO MEDIO DE EVOCAR FRACASO

                                    costoMedioEvoFracasoLIBB = sumCostosEvoFracasoLIBB *1.0 / cantFracasosEvoLIBB;
                                    costoMedioEvoFracasoLSOBT = sumCostosEvoFracasoLSOBT *1.0 / cantFracasosEvoLSOBT;
                                    costoMedioEvoFracasoABB = sumCostosEvoFracasoABB *1.0 / cantFracasosEvoABB;

                            printf("\n *******************************************************************\n"
                                   " *                     Comparacion de Estructuras                  *\n"
                                   " *******************************************************************\n"
                                   " *   Costos                LIBB     LSOBT      ABB                 *\n"
                                   " *   ------------------------------------------------------------- *\n");
                            printf(" *   MAX.ALTA              %.2f     %.2f      %.2f                *\n", costoMaxAltaLIBB, costoMaxAltaLSOBT, costoMaxAltaABB);
                            printf(" *   MEDIO ALTA            %.2f     %.2f       %.2f                *\n", costoMedioAltaLIBB, costoMedioAltaLSOBT, costoMedioAltaABB);
                            printf(" *   MAX.BAJA              %.2f    %.2f      %.2f                *\n", costoMaxBajaLIBB, costoMaxBajaLSOBT, costoMaxBajaABB);
                            printf(" *   MEDIO BAJA            %.2f    %.2f      %.2f                *\n", costoMedioBajaLIBB, costoMedioBajaLSOBT, costoMedioBajaABB);
                            printf(" *   MAX. EVOC. EX.        %d       %d          %d                  *\n", costoMaxEvoExitoLIBB, costoMaxEvoExitoLSOBT, costoMaxEvoExitoABB);
                            printf(" *   MED. EVOC. EX.        %.2f    %.2f       %.2f                *\n", costoMedioEvoExitoLIBB, costoMedioEvoExitoLSOBT, costoMedioEvoExitoABB);
                            printf(" *   MAX. EVOC. NO EX.     %d       %d          %d                   *\n", costoMaxEvoFracasoLIBB, costoMaxEvoFracasoLSOBT, costoMaxEvoFracasoABB);
                            printf(" *   MED. EVOC. NO EX.     %.2f     %.2f       %.2f                *\n", costoMedioEvoFracasoLIBB, costoMedioEvoFracasoLSOBT, costoMedioEvoFracasoABB);
                            printf(" *                                                                 *\n"
                                   " *******************************************************************\n\n");
                    break;
                }
                break;
            }
        } while (opciones != 0);

        printf("\n      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                 "      |                                                   |\n"
                 "      |    Muchas gracias por utilizar nuestro programa   |\n"
                 "      |                                                   |\n"
                 "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        return 0;
}
