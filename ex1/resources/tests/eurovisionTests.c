#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "../list.h"
#include "../eurovision.h"
#include "eurovisionTests.h"

#define POINTS_OPTIONS_NUMBER 10

#define CHECK(b,res)                            \
  if((b) != (res)) do{                          \
      printf("fail: %s != %s\n", #b, #res);     \
      eurovisionDestroy(eurovision);            \
      return false;                             \
    } while(0)

#define CHECK_WITH_FREE(b,res,f)                \
  if((b) != (res)) do{                          \
      printf("fail: %s != %s\n", #b, #res);     \
      eurovisionDestroy(eurovision);            \
      free(f);                                  \
      return false;                             \
    } while(0)

static Eurovision setupEurovision() {
  Eurovision eurovision = eurovisionCreate();
  assert(eurovision);
  return eurovision;
}

static void setupEurovisionStates(Eurovision eurovision) {
  eurovisionAddState(eurovision, 0, "israel", "home");
  eurovisionAddState(eurovision, 1, "malta", "chameleon");
  eurovisionAddState(eurovision, 2, "croatia", "the dream");
  eurovisionAddState(eurovision, 3, "russia", "scream");
  eurovisionAddState(eurovision, 4, "moldova", "stay");
  eurovisionAddState(eurovision, 5, "cyprus", "replay");
  eurovisionAddState(eurovision, 6, "spain", "la venda");
  eurovisionAddState(eurovision, 7, "italy", "soldi");
  eurovisionAddState(eurovision, 8, "france", "roi");
  eurovisionAddState(eurovision, 9, "germany", "sister");
  eurovisionAddState(eurovision, 10, "united kingdom", "bigger than us");
  eurovisionAddState(eurovision, 11, "armenia", "walking out");
  eurovisionAddState(eurovision, 12, "austria", "limits");
  eurovisionAddState(eurovision, 13, "ireland", "twenty two");
  eurovisionAddState(eurovision, 14, "netherlands", "arcade");
  eurovisionAddState(eurovision, 15, "sweden", "too late for love");
}

static int *makeJudgeResults(int id0, int id1, int id2, int id3, int id4,
                             int id5, int id6, int id7, int id8, int id9) {
  int *results = malloc(POINTS_OPTIONS_NUMBER * sizeof(*results));
  assert(results);
  results[0] = id0;
  results[1] = id1;
  results[2] = id2;
  results[3] = id3;
  results[4] = id4;
  results[5] = id5;
  results[6] = id6;
  results[7] = id7;
  results[8] = id8;
  results[9] = id9;
  return results;
}

/** total judge result: (stateid: score)
 * 0:  12 + 2  + 0  = 14
 * 1:  10 + 0  + 0  = 10
 * 2:  8  + 1  + 0  = 9
 * 3:  7  + 0  + 7  = 14
 * 4:  6  + 6  + 6  = 18
 * 5:  5  + 5  + 5  = 15
 * 6:  4  + 4  + 4  = 12
 * 7:  3  + 0  + 3  = 6
 * 8:  2  + 0  + 2  = 4
 * 9:  1  + 0  + 1  = 2
 * 10: 0  + 8  + 12 = 20
 * 11: 0  + 0  + 10 = 10
 * 12: 0  + 0  + 8  = 8
 * 13: 0  + 10 + 0  = 12
 * 14: 0  + 12 + 0  = 12
 * 15: 0  + 3  + 0  = 3
 */
static void setupEurovisionJudges(Eurovision eurovision) {
  int *results;
  results = makeJudgeResults( 0,  1,  2, 3, 4, 5, 6,  7, 8, 9);
  eurovisionAddJudge(eurovision, 0, "olsen", results);
  free(results);
  results = makeJudgeResults(14, 13, 10, 8, 4, 5, 6, 15, 0, 2);
  eurovisionAddJudge(eurovision, 1, "tanel", results);
  free(results);
  results = makeJudgeResults(10, 11, 12, 3, 4, 5, 6,  7, 8, 9);
  eurovisionAddJudge(eurovision, 2, "marie", results);
  free(results);
}

static void giveVotes(Eurovision eurovision, int giver, int taker, int votes) {
  for (int i = 0; i < votes; i++) {
    if (eurovisionAddVote(eurovision, giver, taker) != EUROVISION_SUCCESS) {
      printf("error in eurovisionAddVote %d -> %d\n", giver, taker);
    }
  }
}

static void setupEurovisionVotes(Eurovision eurovision) {
  giveVotes(eurovision, 1, 12, 4);
  giveVotes(eurovision, 2, 8, 2);
  giveVotes(eurovision, 3, 4, 1);
}

/** total voters result:
 * 1:  12 + 0  + 0       = 12
 * 2:  12 + 0  + 8       = 20
 * 3:  10 + 6  + 0       = 16
 * 4:  7  + 7  + 12 + 12 = 38
 * 5:  8  + 8  + 4       = 20
 * 6:  6  + 10 + 6       = 22
 * 7:  5  + 5  + 5       = 15
 * 8:  4  + 0  + 7       = 11
 * 9:  3  + 0  + 3       = 6
 * 10: 2  + 0  + 10      = 12
 * 11: 1  + 0  + 0       = 1
 * 13: 0  + 0  + 1       = 1
 * 14: 0  + 0  + 2       = 2
 */
static void setupEurovisionVotes2(Eurovision eurovision) {
  giveVotes(eurovision, 1, 2, 20);
  giveVotes(eurovision, 1, 3, 18);
  giveVotes(eurovision, 1, 5, 16);
  giveVotes(eurovision, 1, 4, 14);
  giveVotes(eurovision, 1, 6, 12);
  giveVotes(eurovision, 1, 7, 10);
  giveVotes(eurovision, 1, 8, 8);
  giveVotes(eurovision, 1, 9, 6);
  giveVotes(eurovision, 1, 10, 5);
  giveVotes(eurovision, 1, 11, 4);
  giveVotes(eurovision, 1, 12, 3);
  giveVotes(eurovision, 1, 13, 2);
  giveVotes(eurovision, 1, 14, 1);

  giveVotes(eurovision, 2, 1, 20);
  giveVotes(eurovision, 2, 6, 18);
  giveVotes(eurovision, 2, 5, 16);
  giveVotes(eurovision, 2, 4, 14);
  giveVotes(eurovision, 2, 3, 12);
  giveVotes(eurovision, 2, 7, 10);

  giveVotes(eurovision, 3, 4, 14);
  giveVotes(eurovision, 3, 10, 13);
  giveVotes(eurovision, 3, 2, 12);
  giveVotes(eurovision, 3, 8, 11);
  giveVotes(eurovision, 3, 6, 11);
  giveVotes(eurovision, 3, 7, 10);
  giveVotes(eurovision, 3, 5, 9);
  giveVotes(eurovision, 3, 9, 8);
  giveVotes(eurovision, 3, 14, 7);
  giveVotes(eurovision, 3, 13, 6);
  giveVotes(eurovision, 3, 12, 5);
  giveVotes(eurovision, 3, 11, 4);

  giveVotes(eurovision, 4, 3, 2);
}

bool testAddState() {
  Eurovision eurovision = setupEurovision();
  CHECK(eurovisionAddState(eurovision, 0, "israel", "home"), EUROVISION_SUCCESS);
  CHECK(eurovisionAddState(eurovision, 1, "malta", "chameleon"), EUROVISION_SUCCESS);
  CHECK(eurovisionAddState(eurovision, 0, "croatia", "the dream"), EUROVISION_STATE_ALREADY_EXIST);
  CHECK(eurovisionAddState(eurovision, 0, "israel", "home"), EUROVISION_STATE_ALREADY_EXIST);
  CHECK(eurovisionAddState(eurovision, -1, "croatia", "the dream"), EUROVISION_INVALID_ID);
  eurovisionDestroy(eurovision);
  return true;
}

bool testRemoveState() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  CHECK(eurovisionRemoveState(eurovision, 24), EUROVISION_STATE_NOT_EXIST);
  CHECK(eurovisionRemoveState(eurovision, -1), EUROVISION_INVALID_ID);
  CHECK(eurovisionRemoveState(eurovision, 1), EUROVISION_SUCCESS);
  CHECK(eurovisionRemoveState(eurovision, 1), EUROVISION_STATE_NOT_EXIST);
  eurovisionDestroy(eurovision);
  return true;
}

bool testAddJudge() {
  int *results;
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  CHECK(eurovisionAddJudge(eurovision, -1, "olsen", NULL), EUROVISION_NULL_ARGUMENT);
  results = makeJudgeResults(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, -1, "olsen", results), EUROVISION_INVALID_ID, results);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 0, "olsen", results), EUROVISION_SUCCESS, results);
  free(results);
  results = makeJudgeResults(0, 1, -2, -3, 4, 5, 6, 7, 8, -9);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "tanel", results), EUROVISION_INVALID_ID, results);
  free(results);
  results = makeJudgeResults(100, 1, 2, 3, 4, 5, 6, 7, 8, 9);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "tanel", results), EUROVISION_STATE_NOT_EXIST, results);
  free(results);
  results = makeJudgeResults(14, 13, 10, 8, 4, 5, 6, 15, 0, 2);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "tanel", results), EUROVISION_SUCCESS, results);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "marie", results), EUROVISION_JUDGE_ALREADY_EXIST, results);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 2, "marie", results), EUROVISION_SUCCESS, results);
  free(results);
  eurovisionDestroy(eurovision);
  return true;
}

bool testRemoveJudge() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  setupEurovisionJudges(eurovision);
  CHECK(eurovisionRemoveJudge(eurovision, -1), EUROVISION_INVALID_ID);
  CHECK(eurovisionRemoveJudge(eurovision, 5), EUROVISION_JUDGE_NOT_EXIST);
  CHECK(eurovisionRemoveJudge(eurovision, 0), EUROVISION_SUCCESS);
  CHECK(eurovisionRemoveJudge(eurovision, 0), EUROVISION_JUDGE_NOT_EXIST);
  eurovisionDestroy(eurovision);
  return true;
}

bool testAddVote() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  CHECK(eurovisionAddVote(eurovision, -1, 12), EUROVISION_INVALID_ID);
  CHECK(eurovisionAddVote(eurovision, 12, -1), EUROVISION_INVALID_ID);
  CHECK(eurovisionAddVote(eurovision, 100, 12), EUROVISION_STATE_NOT_EXIST);
  CHECK(eurovisionAddVote(eurovision, 12, 100), EUROVISION_STATE_NOT_EXIST);
  CHECK(eurovisionAddVote(eurovision, 12, 1), EUROVISION_SUCCESS);
  eurovisionDestroy(eurovision);
  return true;
}

bool testRemoveVote() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  setupEurovisionVotes(eurovision);
  CHECK(eurovisionRemoveVote(eurovision, -1, 12), EUROVISION_INVALID_ID);
  CHECK(eurovisionRemoveVote(eurovision, 12, -1), EUROVISION_INVALID_ID);
  CHECK(eurovisionRemoveVote(eurovision, 100, 12), EUROVISION_STATE_NOT_EXIST);
  CHECK(eurovisionRemoveVote(eurovision, 12, 100), EUROVISION_STATE_NOT_EXIST);
  CHECK(eurovisionRemoveVote(eurovision, 1, 12), EUROVISION_SUCCESS);
  CHECK(eurovisionRemoveVote(eurovision, 3, 4), EUROVISION_SUCCESS);
  CHECK(eurovisionRemoveVote(eurovision, 3, 7), EUROVISION_SUCCESS);
  CHECK(eurovisionRemoveVote(eurovision, 8, 3), EUROVISION_SUCCESS);
  CHECK(eurovisionRemoveVote(eurovision, 10, 11), EUROVISION_SUCCESS);
  eurovisionDestroy(eurovision);
  return true;
}

/** combined scores:
 * 4:  18 * 0.6 + 38 * 0.4 = 26.0 (moldova)
 * 5:  15 * 0.6 + 20 * 0.4 = 17.0 (cyprus)
 * 10: 20 * 0.6 + 12 * 0.4 = 16.8 (united kingdom)
 * 6:  12 * 0.6 + 22 * 0.4 = 16.0 (spain)
 * 3:  14 * 0.6 + 16 * 0.4 = 14.8 (russia)
 * 2:   9 * 0.6 + 20 * 0.4 = 13.4 (croatia)
 * 1:  10 * 0.6 + 12 * 0.4 = 10.8 (malta)
 * 7:   6 * 0.6 + 15 * 0.4 = 9.6 (italy)
 * 0:  14 * 0.6 +  0 * 0.4 = 8.4 (israel)
 * 14: 12 * 0.6 +  2 * 0.4 = 8.0 (netherlands)
 * 13: 12 * 0.6 +  1 * 0.4 = 7.6 (ireland)
 * 8:   4 * 0.6 + 11 * 0.4 = 6.8 (france)
 * 11: 10 * 0.6 +  1 * 0.4 = 6.4 (armenia)
 * 12:  8 * 0.6 +  0 * 0.4 = 4.8 (austria)
 * 9:   2 * 0.6 +  6 * 0.4 = 3.6 (germany)
 * 15:  3 * 0.6 +  0 * 0.4 = 1.8 (sweden)
 */
bool testRunContest() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  setupEurovisionJudges(eurovision);
  setupEurovisionVotes2(eurovision);

  List ranking = eurovisionRunContest(eurovision, 40);
  CHECK(listGetSize(ranking), 16);
  char *current = (char*)listGetFirst(ranking);
  CHECK(strcmp(current, "moldova"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "cyprus"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "united kingdom"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "spain"), 0);

  listDestroy(ranking);
  eurovisionDestroy(eurovision);
  return true;
}

bool testRunAudienceFavorite() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  setupEurovisionJudges(eurovision);
  setupEurovisionVotes2(eurovision);

  List ranking = eurovisionRunAudienceFavorite(eurovision);
  CHECK(listGetSize(ranking), 16);
  char *current = (char*)listGetFirst(ranking);
  CHECK(strcmp(current, "moldova"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "spain"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "croatia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "cyprus"), 0);

  listDestroy(ranking);
  eurovisionDestroy(eurovision);
  return true;
}

/* friendlies: malta-croatia, russia-moldova */
bool testRunGetFriendlyStates() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  /* setupEurovisionJudges(eurovision); */
  setupEurovisionVotes2(eurovision);

  List friendlies = eurovisionRunGetFriendlyStates(eurovision);
  CHECK((friendlies == NULL), false);
  CHECK(listGetSize(friendlies), 2);
  char *current = (char *)listGetFirst(friendlies);
  CHECK(strcmp(current, "croatia - malta"), 0);
  current  = (char*)listGetNext(friendlies);
  CHECK(strcmp(current, "moldova - russia"), 0);

  listDestroy(friendlies);
  eurovisionDestroy(eurovision);
  return true;
}
