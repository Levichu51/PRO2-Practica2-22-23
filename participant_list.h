
#ifndef PARTICIPANT_LIST_H
#define PARTICIPANT_LIST_H

#include "types.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define NULLP NULL


typedef struct tItemP {
    tParticipantName participantName;
    tNumVotes numVotes;
    tEUParticipant EUParticipant;
} tItemP;

typedef struct tNode* tPosP;

struct tNode{
    tItemP data;
    tPosP next;
};

typedef tPosP tListP;

void createEmptyListP(tListP* L);
bool isEmptyListP(tListP L );
tPosP firstP(tListP L);
tPosP lastP(tListP L);
tPosP nextP(tPosP p, tListP L);
tPosP previousP(tPosP p, tListP L);
bool insertItemP(tItemP d, tListP* L);
void deleteAtPositionP(tPosP p, tListP* L);
tItemP getItemP(tPosP p, tListP L);
void updateItemP(tItemP d, tPosP p, tListP* L);
tPosP findItemP(tParticipantName d, tListP L);

#endif
