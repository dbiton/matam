#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "eurovision.h"

#define JUDGE_VOTES 10
#define LAST_VALID_CHAR 'z'
#define FIRST_VALID_CHAR 'a'
#define VALID_CHAR ' '

struct eurovision_t{
    List Judges;
    List States;
};

struct judge_t{
    unsigned int judgeId;
    char *judgeName;
    int *judgeResults;
};

struct state_t{
    unsigned int stateId;
    char *stateName;
    char *songName;
    List voteList;
};

struct vote_entry_t{
    unsigned int votes;
    State *state;
};

void arrcpy(int *destination,int *source){
    while(*destination){
        *source = *destination;
        destination++;
        source++;
    }
}

VoteEntry voteEntryCopy(VoteEntry voteEntry){
    VoteEntry newVoteEntry = malloc(sizeof(VoteEntry));
    if (newVoteEntry == false){
        return NULL;
    }
    newVoteEntry->votes = voteEntry->votes;
    newVoteEntry->state = voteEntry->state;
    return newVoteEntry;
}

void voteEntryFree(VoteEntry voteEntry){
    free(voteEntry);
}

Judge judgeCopy(Judge judge){
    Judge newJudge = malloc(sizeof(Judge));
    if (newJudge == NULL){
        return NULL;
    }
    newJudge->judgeId = judge->judgeId;
    newJudge->judgeName = malloc(sizeof(char)*strlen(judge->judgeName));
    newJudge->judgeResults = malloc(sizeof(int)*JUDGE_VOTES);
    if (newJudge->judgeName == NULL || newJudge->judgeResults == NULL){
        return NULL;
    }
    strcpy(newJudge->judgeName,judge->judgeName);
    arrcpy(newJudge->judgeResults,judge->judgeResults);
    return newJudge;
}

void judgeFree(Judge judge){
    free(judge->judgeName);
    free(judge->judgeResults);
    free(judge);
}

State stateCopy(State state){
    State newState = malloc(sizeof(State));
    if (newState == NULL){
        return NULL;
    }
    newState->stateId = state->stateId;
    newState->songName = malloc(sizeof(char)*strlen(state->songName));
    newState->stateName = malloc(sizeof(char)*strlen(state->stateName));
    newState->voteList = listCopy(state->voteList);
    if (newState->songName == NULL || newState->stateName == NULL || newState->voteList == NULL){
        return NULL;
    }
    strcpy(newState->songName,state->songName);
    strcpy(newState->stateName,state->stateName);
    return newState;
}

void stateFree(State state){
    free(state->stateName);
    free(state->songName);
    listDestroy(state->voteList);
    free(state);
}

Eurovision eurovisionCreate(){
    Eurovision newEurovision = malloc(sizeof(Eurovision));
    if (newEurovision == NULL){
        return NULL;
    }
    newEurovision->Judges = listCreate(judgeCopy,judgeFree);
    newEurovision->States = listCreate(stateCopy,stateFree);
    if (newEurovision == NULL || newEurovision->Judges == NULL || newEurovision->States == NULL){
        return NULL;
    }
    return newEurovision;
}

bool isValidString(char *string){
    while (*string){
        if ((*string>LAST_VALID_CHAR || *string<FIRST_VALID_CHAR) && *string != VALID_CHAR){
            return false;
        }
        string++;
    }
    return true;
}

bool containsState(Eurovision eurovision,int stateId){
    State tmpState = stateCopy(listGetFirst(eurovision->States));
    while (tmpState != NULL){
        if (tmpState->stateId == stateId){
            return true;
        }
        tmpState = listGetNext(eurovision->States);
    }
    return false;
}

EurovisionResult isValidState(Eurovision eurovision,int stateId, const char *stateName, const char *songName){
    if (stateId<0){
        return EUROVISION_INVALID_ID;
    }
    if (!isValidString(stateName) || !isValidString(songName)){
        return EUROVISION_INVALID_NAME;
    }
    if (containsState(eurovision,stateId)){
        return EUROVISION_STATE_ALREADY_EXIST;
    }
    return EUROVISION_SUCCESS;
}

EurovisionResult eurovisionAddState(Eurovision eurovision,int stateId, const char *stateName, const char *songName){
    EurovisionResult stateValid = isValidState(eurovision,stateId,stateName,songName);
    if (stateValid != EUROVISION_SUCCESS){
        return stateValid;
    }
    if (eurovision == NULL || stateName == NULL || songName == NULL){
        return EUROVISION_NULL_ARGUMENT;
    }
    State newState = malloc(sizeof(State));
    if (newState == NULL){
        return EUROVISION_OUT_OF_MEMORY;
    }
    newState->stateId = stateId;
    newState->songName = malloc(sizeof(char)*strlen(songName));
    newState->stateName = malloc(sizeof(char)*strlen(stateName));
    if (newState->songName == NULL || newState->stateName == NULL){
        return EUROVISION_OUT_OF_MEMORY;
    }
    strcpy(newState->songName,songName);
    strcpy(newState->stateName,stateName);
    return EUROVISION_SUCCESS;
}
