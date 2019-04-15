#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "eurovision.h"

#define JUDGE_VOTES 10
#define MAX_SCORE 12
#define SCORE_SWITCH 8
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
    int score;
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

bool arrContains(int *array,int value){
    while (*array){
        if (*array == value){
            return true;
        }
        array++;
    }
    return false;
}

Judge getJudgeVoted(Eurovision eurovision,int stateId){
    Judge tmpJudge = judgeCopy(listGetFirst(eurovision->Judges));
    while (tmpJudge != NULL){
        if (arrContains(tmpJudge->judgeResults,stateId)){
            return listGetCurrent(eurovision->Judges);
        }
        tmpJudge = listGetNext(eurovision->Judges);
    }
    return NULL;
}

State getState(Eurovision eurovision,int stateId){
    State tmpState = stateCopy(listGetFirst(eurovision->States));
    while (tmpState != NULL){
        if (tmpState->stateId == stateId){
            return listGetCurrent(eurovision->States);
        }
        tmpState = listGetNext(eurovision->States);
    }
    return NULL;
}

EurovisionResult isValidState(Eurovision eurovision,int stateId, const char *stateName, const char *songName){
    if (stateId<0){
        return EUROVISION_INVALID_ID;
    }
    if (!isValidString(stateName) || !isValidString(songName)){
        return EUROVISION_INVALID_NAME;
    }
    if (getState(eurovision,stateId)!=NULL){
        return EUROVISION_STATE_ALREADY_EXIST;
    }
    return EUROVISION_SUCCESS;
}

EurovisionResult outOfMemory(){
    //free all and exit
    return EUROVISION_OUT_OF_MEMORY;
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
        return outOfMemory();
    }
    newState->stateId = stateId;
    newState->songName = malloc(sizeof(char)*strlen(songName));
    newState->stateName = malloc(sizeof(char)*strlen(stateName));
    if (newState->songName == NULL || newState->stateName == NULL){
        return outOfMemory();
    }
    strcpy(newState->songName,songName);
    strcpy(newState->stateName,stateName);
    return EUROVISION_SUCCESS;
}

EurovisionResult eurovisionRemoveState(Eurovision eurovision, int stateId){
    if (stateId<0){
        return EUROVISION_INVALID_ID;
    }
    State statePointer = getState(eurovision,stateId);
    if (statePointer==NULL){
        return EUROVISION_STATE_NOT_EXIST;
    }
    Judge tmpJudge = getJudgeVoted(eurovision,stateId);
    do{
        judgeFree(tmpJudge);
        tmpJudge = getJudgeVoted(eurovision,stateId);
    }while(tmpJudge != NULL);
    stateFree(statePointer);
    return EUROVISION_SUCCESS;
}

VoteEntry entryGet(List list, int stateId){
    VoteEntry tmpEntry = listGetFirst(list);
    while (tmpEntry!= NULL){
        if (tmpEntry->state == stateId){
            return tmpEntry;
        }
        tmpEntry = listGetNext(list);
    }
    return NULL;
}

EurovisionResult eurovisionAddVote(Eurovision eurovision, int stateGiverId, int stateTakerId){
    if (eurovision == NULL){
        return EUROVISION_NULL_ARGUMENT;
    }
    if (stateGiverId<0 || stateTakerId<0){
        return EUROVISION_INVALID_ID;
    }
    State stateGiver = getState(eurovision,stateGiverId);
    State stateTaker = getState(eurovision,stateTakerId);
    if (stateGiver == NULL || stateTaker == NULL){
        return EUROVISION_STATE_NOT_EXIST;
    }
    List voteList = stateGiver->voteList;
    VoteEntry voteEntry = entryGet(voteList,stateTaker);
    if (voteEntry != NULL){
        voteEntry->votes += 1;
        return EUROVISION_SUCCESS;
    }
    voteEntry = malloc(sizeof(VoteEntry));
    voteEntry->votes = 1;
    voteEntry->state = stateTaker;
    listInsertFirst(voteList,voteEntry);
    return EUROVISION_SUCCESS;
}

int compareVoteEntry(VoteEntry voteEntry1,VoteEntry voteEntry2){
    return voteEntry1->votes-voteEntry2->votes;
}

double avgJudgeScore(List judges,int stateId){
    int judgesScoreSum = 0;
    LIST_FOREACH(Judge,curJudge,judges){
        int curScore = MAX_SCORE;
        int *curArray = curJudge->judgeResults;
        for(int i = 0; i<JUDGE_VOTES; i++){
            if (*curArray == stateId){
                judgesScoreSum+=curScore;
                break;
            }
            if (curScore <= SCORE_SWITCH){
                curScore -= 1;
            } else {
                curScore -= 2;
            }
        }
    }
    return judgesScoreSum/listGetSize(judges);
}

double avgStateScore(List states,int stateId){
    int statesScoreSum = 0;
    LIST_FOREACH(State,curState,states){
        int curScore = 1;
        listSort(curState->voteList,compareVoteEntry);
        LIST_FOREACH(VoteEntry,curVoteEntry,curState->voteList){
            if (curVoteEntry->state == stateId){
                statesScoreSum+=curScore;
                break;
            }
            if (curScore >= SCORE_SWITCH){
                curScore += 2;
            } else {
                curScore += 1;
            }
        }
    }
    return statesScoreSum/listGetSize(states);
}

int compareStates(State state1, State state2){
    state1->score==state2->score ? state1->stateId-state2->stateId : state1->score-state2->score;
}

List eurovisionRunContest (Eurovision eurovision, int audiencePercent){
    LIST_FOREACH(State,curState,eurovision->States){
        curState->score = (int)((audiencePercent/100)*avgStateScore(eurovision->States,curState->stateId) +
                ((100-audiencePercent)/100)*avgJudgeScore(eurovision->Judges,curState->stateId));
    }
    listSort(eurovision->States,compareStates);
    return eurovision->States;
}
