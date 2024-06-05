
#ifndef JURY_LIST_H
#define JURY_LIST_H

#include "types.h"
#include "participant_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define NULLJ -1
#define MAX 10


typedef struct tItemJ {
    tJuryName juryName;
    tNumVotes totalVoters;
    tNumVotes validVotes;
    tNumVotes nullVotes;
    tListP partcipantList;
} tItemJ;

typedef int tPosJ;

typedef struct {
    tItemJ dataJ[MAX];
    tPosJ lastPos;
}tListJ;

void createEmptyListJ(tListJ* L);
bool isEmptyListJ(tListJ L );
tPosJ firstJ(tListJ L);
tPosJ lastJ(tListJ L);
tPosJ nextJ(tPosJ p, tListJ L);
tPosJ previousJ(tPosJ p, tListJ L);
bool insertItemJ(tItemJ d, tListJ* L);
void deleteAtPositionJ(tPosJ p, tListJ* L);
tItemJ getItemJ(tPosJ p, tListJ L);
void updateItemJ(tItemJ d, tPosJ p, tListJ* L);
tPosJ findItemJ(tJuryName d, tListJ L);


#endif
