/******************************************** MODO ESTRATEGIA *****************************************/
#include <stdio.h>
#include <stdlib.h>

/*** para la lista de soldados ***/
#define TIPO_GUERRERO 1
#define TIPO_ARQUERO 2
#define TIPO_CONVERTIDO 3

/*** para la fila de acciones ***/
#define FLAG_ATAQUE 1
#define FLAG_DEFENSA 2
#define FLAG_ESPECIAL 3

/********** estructura para guardar datos en el archivo ***********/

typedef struct
{
    char nombre[30];
    int puntaje;
    ////hora y fecha, con Windows.
}stJugadorDLC;

/***** estructuras para la lista de soldados (ejercito dinamico) *****/

typedef struct
{
    int tipo; /// flag que indica el tipo de soldado, 1: guerrero, 2: arquero, 3: convertido
    int hp;
    int ataque;
    int defensa;
    int especial; //bonus segun clase.
}stSoldado;

typedef struct _nodo
{
    stSoldado soldado;
    struct _nodo* siguiente;
}nodoSoldado;

/***** estructuras para la fila de acciones *****/

typedef struct
{
    int tipo; ///flag que indica si la accion es ataque, defensa o especial
    int ataque;
    int defensa;
    int especial;
}stAccion;

typedef struct _nodoA
{
    stAccion accion;
    struct _nodoA* anterior;
    struct _nodoA* siguiente;
}nodoAccion;

typedef struct
{
    nodoAccion* primera;
    nodoAccion* ultima;
}filaAccion;

/***** funciones lista de soldados *****/

nodoSoldado* inicListaEjercito()
{
    return NULL;
}

stSoldado asignarStatSegunTipo(int tipo)
{
    stSoldado aux;

    switch(tipo)
    {

    case 1:
        //guerrero
        aux.tipo = TIPO_GUERRERO;
        aux.hp = 40;
        aux.ataque = 13;
        aux.defensa = 15;
        aux.especial = 0;
        break;

    case 2:
        //arquero
        aux.tipo = TIPO_ARQUERO;
        aux.hp = 30;
        aux.ataque = 18;
        aux.defensa = 10;
        aux.especial = 0;
        break;

    case 3:
        //convertido
        aux.tipo = TIPO_CONVERTIDO;
        aux.hp = 20;
        aux.ataque = 8;
        aux.defensa = 8;
        aux.especial = 5;
        break;

    } // fin switch

    return aux;
}

nodoSoldado* crearNodoSoldado(int tipo)
{
    nodoSoldado* nuevo = (nodoSoldado*) malloc ( sizeof(nodoSoldado) );

    nuevo->soldado = asignarStatSegunTipo(tipo);

    nuevo->siguiente = NULL;

    return nuevo;
}

nodoSoldado* buscarUltimoSoldadoRecursiva(nodoSoldado* plista)
{
    nodoSoldado* ultimo;

    if( plista->siguiente == NULL )
    {
        ultimo = plista;
    }
    else
    {
        ultimo = buscarUltimoSoldadoRecursiva(plista->siguiente);
    }

    return ultimo;
}

nodoSoldado* agregarSoldadoFinal(nodoSoldado* plista, nodoSoldado* nuevo)
{
    if( plista == NULL )
    {
        plista = nuevo;
    }
    else
    {
        nodoSoldado* aux = plista;

        nodoSoldado* ultimo = buscarUltimoSoldadoRecursiva(aux);

        ultimo->siguiente = nuevo;
    }

    return plista;
}

nodoSoldado* crearEjercitoInicial(nodoSoldado* player)
{

    nodoSoldado* nuevoUno = crearNodoSoldado(TIPO_GUERRERO);
    nodoSoldado* nuevoDos = crearNodoSoldado(TIPO_GUERRERO);
    nodoSoldado* nuevoTres = crearNodoSoldado(TIPO_ARQUERO);

    player = agregarSoldadoFinal(player, nuevoUno);
    player = agregarSoldadoFinal(player, nuevoDos);
    player = agregarSoldadoFinal(player, nuevoTres);

    return player;
}

int contarSoldados(nodoSoldado* plista)
{
    int cantSoldados = 0;

    if( plista != NULL )
    {
        cantSoldados = 1 + contarSoldados(plista->siguiente);
    }

    return cantSoldados;
}

int cicloPeleaEstrategia(nodoSoldado** player, nodoSoldado** enemigo)
{
    int estadoBatalla;

    if( (*player) != NULL && (*enemigo) != NULL)
    {
        ///todavia ninguno de los bandos perdió oficialmente.

        estadoBatalla = 1;
    }
    else
    {
        ///alguno de los bandos perdió.
        estadoBatalla = 0;
    }

    return estadoBatalla;
}

stSoldado eliminarPrimerSoldado(nodoSoldado** plista)
{
    stSoldado eliminado;

    if( (*plista) != NULL )
    {
        nodoSoldado* aux = (*plista);
        eliminado = aux->soldado;
        (*plista) = (*plista)->siguiente;
        aux->siguiente = NULL;
        free(aux);
    }
    else
    {
        eliminado.tipo = -1;
        eliminado.hp = 0;
        eliminado.ataque = 0;
        eliminado.defensa = 0;
        eliminado.especial = 0;
    }

    return eliminado;
}

void mostrarSoldado(stSoldado soldado)
{
    switch(soldado.tipo)
    {

    case 1:
        printf("\nTipo: Guerrero\n");
        break;

    case 2:
        printf("\nTipo: Arquero\n");
        break;

    case 3:
        printf("\nTipo: Convertido\n");
        break;

    } // fin switch

    printf("HP: %d\n",soldado.hp);
    printf("Ataque: %d\n",soldado.ataque);
    printf("Defensa: %d\n",soldado.defensa);
    printf("Especial: %d\n\n",soldado.especial);

} // fin funcion mostrarSoldado

void mostrarEjercito(nodoSoldado* plista)
{
    if( plista != NULL )
    {
        mostrarSoldado(plista->soldado);

        mostrarEjercito(plista->siguiente);
    }

} // fin funcion mostrarEjercito

/***** funciones fila de acciones *****/

nodoAccion* inicListaAccion()
{
    return NULL;
}

stAccion crearAccionAtaque()
{
    stAccion accionAtaque;

    accionAtaque.tipo = FLAG_ATAQUE;
    accionAtaque.ataque = 15;
    accionAtaque.defensa = 0;
    accionAtaque.especial = 0;

    return accionAtaque;
}

stAccion crearAccionDefensa()
{
    stAccion accionDefensa;

    accionDefensa.tipo = FLAG_DEFENSA;
    accionDefensa.ataque = 0;
    accionDefensa.defensa = 15;
    accionDefensa.especial = 0;

    return accionDefensa;
}

stAccion crearAccionEspecial()
{
    stAccion accionEspecial;

    accionEspecial.tipo = FLAG_ESPECIAL;
    accionEspecial.ataque = 0;
    accionEspecial.defensa = 5;
    accionEspecial.especial = 10;

    return accionEspecial;
}

nodoAccion* crearNodoAccion(int flagAccion)
{
    nodoAccion* nuevaAccion = (nodoAccion*) malloc ( sizeof(nodoAccion) );

    switch(flagAccion)
    {

    case FLAG_ATAQUE:
        ///asignar stats de ataque
        nuevaAccion->accion = crearAccionAtaque();
        break;

    case FLAG_DEFENSA:
        ///asignar stats de defensa
        nuevaAccion->accion = crearAccionDefensa();
        break;

    case FLAG_ESPECIAL:
        ///asignar stats de ataque especial
        nuevaAccion->accion = crearAccionEspecial();
        break;

    } // fin switch

    nuevaAccion->anterior = NULL;

    nuevaAccion->siguiente = NULL;

    return nuevaAccion;
}

nodoAccion* buscarUltimoNodoAccion(nodoAccion* listaAcciones)
{
    nodoAccion* ultimo;

    if( listaAcciones->siguiente == NULL )
    {
        ultimo = listaAcciones;
    }
    else
    {
        ultimo = buscarUltimoNodoAccion(listaAcciones->siguiente);
    }

    return ultimo;
}

nodoAccion* agregarNodoAccionFinal(nodoAccion* listaAcciones, nodoAccion* nuevo)
{
    if( listaAcciones == NULL )
    {
        listaAcciones = nuevo;
    }
    else
    {
        nodoAccion* aux = listaAcciones;

        nodoAccion* ultimo = buscarUltimoNodoAccion(aux);

        ultimo->siguiente = nuevo;

        nuevo->anterior = ultimo;
    }

    return listaAcciones;
}

void mostrarUnaAccion(stAccion a)
{
    printf("\ntipo: %d\n",a.tipo);
    printf("atk: %d\n",a.ataque);
    printf("def: %d\n",a.defensa);
    printf("esp: %d\n\n",a.especial);
}

void mostrarAcciones(nodoAccion* lista)
{
    if( lista != NULL )
    {
        mostrarUnaAccion(lista->accion);

        mostrarAcciones(lista->siguiente);
    }
}

void inicFilaAcciones(filaAccion* pfila)
{
    pfila->primera = inicListaAccion();

    pfila->ultima = inicListaAccion();
}

void agregarFilaAccion(filaAccion* pfila, int flagAccion)
{
    nodoAccion* nuevaAccion = crearNodoAccion(flagAccion);

    if( pfila->primera == NULL )
    {
        pfila->primera = nuevaAccion;

        pfila->ultima = nuevaAccion;
    }
    else
    {
        pfila->primera = agregarNodoAccionFinal(pfila->primera, nuevaAccion);

        pfila->ultima = nuevaAccion;
    }
}

stAccion verPrimeraAccion(nodoAccion* listaAcciones)
{
    stAccion primera;

    if( listaAcciones != NULL )
    {
        primera = listaAcciones->accion;
    }

    return primera;
}

nodoAccion* eliminarPrimerAccion(nodoAccion* listaAcciones)
{
    nodoAccion* aborrar = listaAcciones;

    if( listaAcciones != NULL )
    {
        listaAcciones = listaAcciones->siguiente;

        if( listaAcciones != NULL )
        {
            listaAcciones->anterior = NULL;
        }

        free(aborrar);
    }

    return listaAcciones;
}

stAccion extraerFilaAccion(filaAccion* pfila)
{
    stAccion ejecutada;

    if( pfila->primera != NULL )
    {
        ejecutada = verPrimeraAccion(pfila->primera);

        pfila->primera = eliminarPrimerAccion(pfila->primera);

        if( pfila->primera == NULL )
        {
            pfila->ultima = inicListaAccion();
        }
    }

    return ejecutada;
}

void mostrarFilaAcciones(filaAccion fila)
{
    if( fila.primera != NULL )
    {
        mostrarAcciones(fila.primera);
    }
}

int main()
{
    nodoSoldado* player;
    nodoSoldado* enemigo;
    stSoldado soldadoConvertido;
    nodoSoldado* nodoConvertido;
    int cantSoldadosPlayer = 0;
    int cantSoldadosEnemigo = 0;

    player = inicListaEjercito();
    enemigo = inicListaEjercito();

    player = crearEjercitoInicial(player);
    enemigo = crearEjercitoInicial(enemigo);

    printf("\n<< Modo estrategia >>\n");

    cantSoldadosPlayer = contarSoldados(player);
    cantSoldadosEnemigo = contarSoldados(enemigo);

    printf("\nPlayer: %d\n",cantSoldadosPlayer);
    printf("\nEnemigo: %d\n",cantSoldadosEnemigo);

    while( enemigo != NULL )
    {
        soldadoConvertido = eliminarPrimerSoldado(&enemigo);

        nodoConvertido = crearNodoSoldado(soldadoConvertido.tipo);

        player = agregarSoldadoFinal(player, nodoConvertido);

        cantSoldadosPlayer = contarSoldados(player);
        cantSoldadosEnemigo = contarSoldados(enemigo);

        printf("\nPlayer: %d\n",cantSoldadosPlayer);
        printf("\nEnemigo: %d\n",cantSoldadosEnemigo);

        system("pause");
    }


//    filaAccion fila;
//    stAccion ejecutada;
//
//    inicFilaAcciones(&fila);
//
//    agregarFilaAccion(&fila, FLAG_ATAQUE);
//    mostrarFilaAcciones(fila);
//    system("pause");
//
//    agregarFilaAccion(&fila, FLAG_DEFENSA);
//    mostrarFilaAcciones(fila);
//    system("pause");
//
//    agregarFilaAccion(&fila, FLAG_ESPECIAL);
//    mostrarFilaAcciones(fila);
//    system("pause");
//
//    ejecutada = extraerFilaAccion(&fila);
//    printf("\nTras la extraccion\n");
//    mostrarFilaAcciones(fila);
//
//    printf("\nUltima en ejecutarse:\n");
//    mostrarUnaAccion(ejecutada);

    return 0;
}
