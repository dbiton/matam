#include <stdio.h>
#include <stdlib.h>
#include "eurovisionTests.h"

#define TEST(t)                                                                \
  do {                                                                         \
    printf("Testing %s ...\n", #t);                                            \
    if ((t()))                                                                 \
      printf("Test %s: SUCCESS\n", #t);                                        \
    else                                                                       \
      printf("Test %s: FAIL\n", #t);                                           \
  } while (0);

int main(int argc, char *argv[]) {
    TEST(testAddState)
    TEST(testRemoveState)
    TEST(testAddJudge)
    TEST(testRemoveJudge)
    TEST(testAddVote)
    TEST(testRemoveVote)
    TEST(testRunContest)
    TEST(testRunAudienceFavorite)
    TEST(testRunGetFriendlyStates)
    return 0;
}
