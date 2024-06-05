
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "jury_list.h"
#include "participant_list.h"
#define MAX_BUFFER 255



///Prototipos de las funciones
void Create(char *param1, tListJ* J, char *param2);
void New(char *param1, tListJ* J, char *param3, char *param2);
void Vote(char *param1, char *param2, tListJ* J);
void Disqualify(tListJ* J, char *param1);
void RemoveJury(tListJ* J);
void Stats(tListJ J);
void Winners(tListJ J);

///Funciones auxiliares
tPosP findFirstEUParticipant(tListP P);
tPosP findFirstNonEUParticipant(tListP P);
int euDraw(tListP P, tItemP itemP);
int nonEuDraw(tListP P, tItemP itemP);
void deleteListP(tListP* L);




void Create(char *param1, tListJ* J, char *param2){
    tItemJ itemJ;

    if(findItemJ(param1, *J) != NULLJ) { //si el jurado ya existe no se puede crear el mismo
        printf("+ Error: Create not possible\n");

    }else if(findItemJ(param1, *J) == NULLJ){ //si el jurado no existe dentro de la Lista se crea.
        strcpy(itemJ.juryName, param1);
        itemJ.totalVoters = (int)atof(param2);
        itemJ.nullVotes = 0;
        itemJ.validVotes = 0;
        createEmptyListP(&itemJ.partcipantList);

        printf("* Create: jury %s totalvoters %d\n",itemJ.juryName, itemJ.totalVoters);

        insertItemJ(itemJ, J);
    }
    //Objetivo: Crea un nuevo jurado en la Lista de jurados inicializando sus parámetros.
    //Salida: La lista ordenada de jurados.
    //Precondición: Que el nombre del jurado no exista ya dentro de la Lista de jurados.
    //Postcondición: -
}


void New(char *param1, tListJ* J, char *param3, char *param2){
    tItemJ itemJ;
    tItemP itemP;
    tPosJ pj;

    pj = findItemJ(param1, *J);
    itemJ = getItemJ(pj, *J);

    if(pj != NULLJ && findItemP(param2, itemJ.partcipantList) == NULLP){ //si el juryname se encuetra en la lista y el participant name no se encuentra se inserta en la Lista
        strcpy(itemP.participantName, param2);
        itemP.numVotes = 0;

        if(strcmp(param3, "eu") == 0){
            itemP.EUParticipant = true;
        }else{
            itemP.EUParticipant = false;
        }

        insertItemP(itemP, &itemJ.partcipantList); //se inserta el participante con sus campos inicializados y se actualiza la Lista del jurado para guardarlo
        updateItemJ(itemJ, pj, J);

        printf("* New: jury %s participant %s location %s\n", itemJ.juryName, itemP.participantName, param3);

    }else{
        printf("+ Error: New not possible\n");
    }
    //Objetivo: Dar de alta la Lista de los países con su nombre y número de votos (nulos y no-nulos) a 0, asignando si son de EU o no. Luego se inserta en la lista de jurados.
    //Salida: La Lista con los países insertados en la Lista de jurados.
    //Precondición: Que el nombre del participante no esté ya en la lista y el jurado exista.
    //Postcondición: -
}


void Vote(char *param1, char *param2, tListJ* J){
    tItemJ itemJ;
    tPosJ pj;
    tItemP itemP;
    tPosP p;

    pj = findItemJ(param1, *J);
    itemJ = getItemJ(pj, *J);
    p = findItemP(param2, itemJ.partcipantList);

    if((pj == NULLJ || p == NULLP) || (isEmptyListJ(*J))){ //si no se encuentra al jurado, o no se encuentra al participante o la Lista de jurados está vacía el voto será NULO.
        itemJ.nullVotes = itemJ.nullVotes + 1;
        updateItemJ(itemJ, pj, J);
        printf("+ Error: Vote not possible. Participant %s not found in jury %s. NULLVOTE\n", param2, param1);
    }else{
        itemJ.validVotes = itemJ.validVotes + 1; //si se encontro el jurado y el país, se le cuenta al jurado como voto válido el voto del participante (o sea uno)
        itemP = getItemP(p, itemJ.partcipantList);
        itemP.numVotes = itemP.numVotes + 1;

        updateItemP(itemP, p, &itemJ.partcipantList); //se guardan los votos del participante en la Lista de participantes
        updateItemJ(itemJ, pj, J); //se actualiza la Lista de jurados con todos los cambios

        if(itemP.EUParticipant == true) {
            printf("* Vote: jury %s participant %s location eu numvotes %d\n", itemJ.juryName, itemP.participantName, itemP.numVotes);
        }else{
            printf("* Vote: jury %s participant %s location non-eu numvotes %d\n", itemJ.juryName, itemP.participantName, itemP.numVotes);
        }
    }
    //Objetivo: Se asgina un voto al participante de la Lista si éste se encuentra en ella. Si no estuviese, se le asigna como voto NULO.
    //Salida: Devuelve la Lista con los elementos actualizados (se suma un voto en el campo numVotes y validVotes) si han ejercido el derecho a voto.
    //Precondición: Que exista el participante en la Lista o el jurado en la Lista de jurados.
    //Postcondición: -
}


void Disqualify(tListJ* J, char *param1){
    tItemJ itemJ;
    tItemP itemP;
    tPosJ pj;
    tPosP p, pp;

    if(!isEmptyListJ(*J)){
        pj = firstJ(*J);

        while(pj != NULLJ){
            itemJ = getItemJ(pj, *J);
            printf("Jury %s\n", itemJ.juryName);

            if(findItemP(param1, itemJ.partcipantList) == NULLP || isEmptyListP(itemJ.partcipantList)){ //si la lista de participantes esta vacia o no se encuentra al participante se indiciará que no hay
                printf("No participant %s\n", param1);
            }

            if(!isEmptyListP(itemJ.partcipantList)){
                p = firstP(itemJ.partcipantList);

                while(p != NULLP){
                    itemP = getItemP(p, itemJ.partcipantList);

                    if(findItemP(param1, itemJ.partcipantList) != NULLP) { //si se encuentra al participante deseado
                        pp = findItemP(param1, itemJ.partcipantList);

                        if (itemP.numVotes > 0) { // si tienes votos, pasan a ser NULOS
                            itemJ.nullVotes = itemP.numVotes;
                        }

                        if (itemJ.validVotes > 0) { //si hay votos validos en el jurado, se le restan los votos del participante
                            itemJ.validVotes = itemJ.validVotes - itemP.numVotes;
                        }
                        itemP.numVotes = 0; //los votos de ese participante pasan a ser 0
                        updateItemP(itemP, pp, &itemJ.partcipantList);

                        printf("Participant %s disqualified\n", itemP.participantName);

                        deleteAtPositionP(pp, &itemJ.partcipantList);

                    }
                    p = nextP(p, itemJ.partcipantList);
                }
            }
            updateItemJ(itemJ, pj, J); //se actualizan todos los cambios en la Lista de participantes
            printf("\n");
            pj = nextJ(pj, *J);
        }

    }else{
        printf("+ Error: Disqualify not possible\n");
    }
    //Objetivo: Se borra al país deseado de la Lista de participantes, asignando sus votos a 0, pasando a ser NULOS.
    //Salida: Nada, se borra el elemento de la Lista. Sólo se contabilizan sus votos como NULOS.
    //Precondición: Que el participante esté en la Lista.
    //Postcondición: Las posiciones de los elementos de la Lista pueden haber variado.
}


void deleteListP(tListP* L){
    tPosP p;

    while (*L != NULLP){
        p = *L;
        *L = (*L)->next;
        free(p);
    }
    //Objetivo: Eliminar todos los elementos de la Lista introducida.
    //Salida: -
    //Precondición: La Lista debe de estar inicializada y contener mínimo un nodo para que haga su trabajo la función.
    //Postcondición: -
}

void RemoveJury(tListJ* J){
    tItemJ itemJ;
    tPosJ pj;
    int aux = 0; //aux cuenta los jurados con votos validos. Si no hay, o sea es 0, no se puede hacer un Remove

    if(!isEmptyListJ(*J)){
        pj = firstJ(*J);

        while(pj != NULLJ){
            itemJ = getItemJ(pj, *J);

            if(itemJ.validVotes == 0 && isEmptyListP(itemJ.partcipantList)) { //si los votos válidos del jurado son 0, se borra de la Lista
                printf("* Remove: jury %s\n", itemJ.juryName);
                deleteAtPositionJ(pj, J);
                pj = previousJ(pj, *J);

            }else if(itemJ.validVotes == 0 && (!isEmptyListP(itemJ.partcipantList))){ //hay que vaciar la lista como precondicion si quieres borrar el jurado
                printf("* Remove: jury %s\n", itemJ.juryName);
                deleteListP(&itemJ.partcipantList);
                updateItemJ(itemJ, pj, J);
                deleteAtPositionJ(pj, J);
                pj = previousJ(pj, *J);

            }else{
                aux++;  //cuenta los jurados con votos válidos mayores que 0
            }
            pj = nextJ(pj, *J);
        }
        if(aux == 0){
            printf("+ Error: Remove not possible\n");
        }
    }
    else{
        printf("+ Error: Remove not possible\n");
    }
    //Objetivo: Borra de la Lista de jurados todos los jurados cuyos votos válidos sean 0.
    //Salida: La Lista de jurados con los jurados borrados (si se han borrado debido a las condiciones).
    //Precondición: Los votos válidos del jurado han de ser 0.
    //Postcondición: Las posiciones de la Lista de jurados pueden haber variado.
}


void Stats(tListJ J){
    tPosJ pj;
    tItemJ itemJ;
    tItemP itemP;
    tPosP p;
    float totalPercentage;
    float percentage;


    if (!isEmptyListJ(J)) {
        pj = firstJ(J);

        while (pj != NULLJ){
            itemJ = getItemJ(pj, J);
            printf("Jury %s\n", itemJ.juryName);

            if(isEmptyListP(itemJ.partcipantList)){
                printf("No participants\n");
            }else{
                p = firstP(itemJ.partcipantList);

                while(p != NULLP){
                    itemP = getItemP(p, itemJ.partcipantList);

                    if(itemJ.validVotes > 0){ //si tiene mas de 0 votos válidos se calcula el porcentaje de participación (el num de votos del país / los votos totales del jurado)
                        percentage = ((float) itemP.numVotes / (float) itemJ.validVotes) * 100;
                    }else{ //para evitar que de infinito o un porcentaje negativo se dice directamente que es 0 si no hay votos válidos
                        percentage = 0;
                    }

                    if(itemP.EUParticipant == true){
                        printf("Participant %s location eu numvotes %d (%.2f%%)\n", itemP.participantName, itemP.numVotes, percentage);
                    }else{
                        printf("Participant %s location non-eu numvotes %d (%.2f%%)\n", itemP.participantName, itemP.numVotes, percentage);
                    }
                    p = nextP(p, itemJ.partcipantList);
                }

            }
            totalPercentage = ((float)(itemJ.validVotes+itemJ.nullVotes)/(float)itemJ.totalVoters) * 100; //se calcula el índice total de participación con los votos NULOS incluídos
            printf("Nullvotes %d\n", itemJ.nullVotes);
            printf("Participation: %d votes from %d voters (%.2f%%)\n", (itemJ.validVotes+itemJ.nullVotes), itemJ.totalVoters, totalPercentage);
            printf("\n");
            pj = nextJ(pj, J);
        }
    }else{
        printf("+ Error: Stats not possible\n");
    }
    //Objetivo: Imprime la Lista con toda la información de los participantes, los votos NULOS y el porcentaje de participación en cada jurado.
    //Salida: La Lista entera de jurados con la Lista de participantes.
    //Precondición: Que la Lista no esté vacía.
    //Postcondición: -
}



tPosP findFirstEUParticipant(tListP P){
    tPosP p;
    p = firstP(P);

    while(p != NULLP){
        tItemP itemP = getItemP(p, P);

        if(itemP.EUParticipant == true){ //a la que detecte ya el primer item europeo ya devuelve su posición
            return p;
        }
        p = nextP(p, P);
    }
    return NULLP;

    //Objetivo: Obtiene el primer participante europeo de la Lista de participantes.
    //Salida: La posición del primer participante europeo de la Lista de participantes, si no, retorna NULO.
    //Precondición: La Lista debe de estar incializada y no vacía.
    //Postcondición: -
}

tPosP findFirstNonEUParticipant(tListP P){
    tPosP p;
    p = firstP(P);

    while (p != NULLP){
        tItemP itemP = getItemP(p, P);
        if(itemP.EUParticipant == false){ //a la que detecte ya el primer item no europeo ya devuelve su posición
            return p;
        }
        p = nextP(p, P);
    }
    return NULLP;

    //Objetivo: Obtiene el primer participante no europeo de la Lista de participantes.
    //Salida: La posición del primer participante no europeo de la Lista de participantes, si no, retorna NULO.
    //Precondición: La Lista debe de estar incializada y no vacía.
    //Postcondición: -
}


int euDraw(tListP P, tItemP itemP){
    tPosP p;
    tItemP auxItem;
    int count = 0;
    p = firstP(P);

    while(p != NULLP){
        auxItem = getItemP(p, P);

        if((itemP.numVotes == auxItem.numVotes) && (itemP.EUParticipant == true && auxItem.EUParticipant == true)){  //si un item de la Lista tiene el mismo número de votos que el ganador europeo y son los dos europeos, el contador suma 1
            count++;
        }
        p = nextP(p, P);
    }
    return count;

    //Objetivo: Determinar si hay algún país europeo en la Lista de participantes que tenga el mismo número de votos que el ganador europeo.
    //Salida: Las veces que ha aparecido un país europeo con los mismos votos que el ganador europeo.
    //Precondición: La Lista debe de estar incializada y no vacía.
    //Postcondición: -
}


int nonEuDraw(tListP P, tItemP itemP){
    tPosP p;
    tItemP auxItem;
    int count = 0;
    p = firstP(P);

    while(p != NULLP){
        auxItem = getItemP(p, P);

        if((itemP.numVotes == auxItem.numVotes) && (itemP.EUParticipant == false && auxItem.EUParticipant == false)){ //si un item de la Lista tiene el mismo número de votos que el ganador no europeo y son los dos no europeos, el contador suma 1
            count++;
        }
        p = nextP(p, P);
    }
    return count;

    //Objetivo: Determinar si hay algún país no europeo en la Lista de participantes que tenga el mismo número de votos que el ganador no europeo.
    //Salida: Las veces que ha aparecido un país no europeo con los mismos votos que el ganador no europeo.
    //Precondición: La Lista debe de estar incializada y no vacía.
    //Postcondición: -
}



void Winners(tListJ J){
    tItemP itemP;
    tItemP euWinner;
    tItemP nonEuWinner;
    tItemP auxItemEU;
    tItemP auxItemNonEU;
    tItemJ itemJ;
    tPosP p, pEU, pNonEu;
    tPosJ pj;
    int countEu;
    int countNonEu;


    if(!isEmptyListJ(J)) {
        pj = firstJ(J);

        while (pj != NULLJ){
            itemJ = getItemJ(pj, J);
            printf("Jury %s\n", itemJ.juryName);

            bool euEmpty = true;
            bool nonEuEmpty = true;

            if(!isEmptyListP(itemJ.partcipantList)){
                p = firstP(itemJ.partcipantList);

                pEU = findFirstEUParticipant(itemJ.partcipantList);
                pNonEu = findFirstNonEUParticipant(itemJ.partcipantList);

                auxItemEU = getItemP(pEU, itemJ.partcipantList);
                auxItemNonEU = getItemP(pNonEu, itemJ.partcipantList); //se obtienen los primeros países europeos y no europeos de la Lista de participantes

                while(p != NULLP){
                    itemP = getItemP(p, itemJ.partcipantList);

                    if(itemP.EUParticipant == true){
                        if(itemP.numVotes >= auxItemEU.numVotes){ //se va haciendo un barrido de la Lista hasta obtener el participante con mayor número de votos
                            euWinner = itemP;
                        }
                        euEmpty = false; //si se detecta que hay participantes, indicamos que no está vacío para evitar que salte la notificación de que no hay ganadores
                    }

                    else if(itemP.EUParticipant == false){
                        if(itemP.numVotes >= auxItemNonEU.numVotes){
                            nonEuWinner = itemP;
                        }
                        nonEuEmpty = false;
                    }

                    p = nextP(p, itemJ.partcipantList);
                }
            }
            countEu = euDraw(itemJ.partcipantList, euWinner); //se busca si ha habido empate
            countNonEu = nonEuDraw(itemJ.partcipantList, nonEuWinner);

            if(euEmpty == true || countEu > 1){ //si no se encontraron participantes o ha habido empate no habrá ganadores
                printf("Location eu: No winner\n");
            }else{
                printf("Location eu: Participant %s numvotes %d\n", euWinner.participantName, euWinner.numVotes);
            }

            if(nonEuEmpty == true || countNonEu > 1){
                printf("Location non-eu: No winner\n");
            }else{
                printf("Location non-eu: Participant %s numvotes %d\n", nonEuWinner.participantName,nonEuWinner.numVotes);
            }

            printf("\n");
            pj = nextJ(pj, J);
        }
    }else{
        printf("+ Error: Winners not possible\n");
    }
    //Objetivo: Dar los ganadores de la Lista de participantes. El país con más votos gana, si hay empate no hay ganador.
    //Salida: El ganador (si hubo) de la Lista de participantes.
    //Precondición: Ambas Listas han se estar incializadas y no vacías.
    //Postcondición: -
}




void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tListJ* J) {
    printf("********************\n");
    switch (command) {
        case 'C':
            printf("%s %c: jury %s totalvoters %s\n",commandNumber, command, param1, param2);
            Create(param1, J, param2);
            break;
        case 'N':
            printf("%s %c: jury %s participant %s location %s\n",commandNumber, command, param1, param2, param3);
            New(param1, J, param3, param2);
            break;
        case 'V':
            printf("%s %c: jury %s participant %s\n", commandNumber, command, param1, param2);
            Vote(param1, param2, J);
            break;
        case 'D':
            printf("%s %c: participant %s\n", commandNumber, command, param1);
            Disqualify(J, param1);
            break;
        case 'S':
            printf("%s %c:\n", commandNumber, command);
            Stats(*J);
            break;
        case 'R':
            printf("%s %c:\n", commandNumber, command);
            RemoveJury(J);
            break;
        case 'W':
            printf("%s %c:\n", commandNumber, command);
            Winners(*J);
            break;
        default:
            break;
    }
    //Objetivo: Dependiendo del carácter introducido, realiza la operación deseada.
    //Salida: Dependiendo del comando, devuelve el resultado de una de las operaciones deseadas.
    //Precondición: -
    //Postcondición: -
}


void readTasks(char *filename) {

    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];
    tListJ J;

    f = fopen(filename, "r");

    if (f != NULL) {
        createEmptyListJ(&J);

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, &J);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
    //Objetivo: Lee el fichero .txt introducido y asigna un valor a los parámetros de la funcion processCommand.
    //Salida: Los parámetros para asignar el nombre del país, n de comando, letra del comando, si es eu o non-eu...
    //Precondición: Que el fichero .txt exista.
    //Postcondición: -
}


int main(int nargs, char **args) {

    char *file_name = "create.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}
