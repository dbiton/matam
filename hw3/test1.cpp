
/**************************************************************************
234124 - Introduction To Systems Programming
Spring 2019
HW3 - C++

In charge : Israel Gutter     
            Noy Naor   
For questions and clarifications : Please use the forum in Moodle.       
**************************************************************************/

#include <iostream>

#include "eurovision.h"

using std::cout;
using std::endl;

#define TEST(num)  cout << endl << "TEST" << " " << (num) << endl;


int main()
{

  MainControl eurovision;

/* The same as defining with the default values
   MainControl eurovision(180, 26, 5);
   180 - max allowed time length (seconds) of a song
   26 - max allowed number of participants
   5 - max allowed times that any regular voter (not judge) can vote.
   other inner default initializations :
   empty system at the start - no participants, no votes,
   phase of Registration.
*/


/* definitions of potential participants.
   still are not registered in the system.
   the values can be here any values, even empty string or 0 for
   time length.
   for example :
  Participant p1("Israel","Song_Israel",175,"Singer_Israel");
  means
  p1 is a potential participant with the following features :
  State : Israel
  Name of the song : Song_Israel
  time length of the song (seconds) : 175
  Name of the singer : Singer_Israel

  No problem to define here many potential participants with the
  same features, like state or Name of song etc.

  if the participant is not still registered in the system, no importance
  to its values which can be updated later, in condition that still
  it is not registered in the system.

*/
  Participant p1("Israel","Song_Israel",175,"Singer_Israel");
  Participant p2("UK","Song_UK",170,"Singer_UK");
  Participant p3("France","Song_France",190,"Singer_France");
  Participant p4("Australia","Song_Australia",180,"Singer_Australia");
  Participant p5("Cyprus","Song_Cyprus",172,"Singer_Cyprus");

//  Participant p11(p1);  // compilation error. every potential participant
                          //  is unique as an object. Can not be copied from
                          //  another participant.*/

//  Participant p12; // compilation error. Must give values to all features.
//  Participant p13("","",0,""); // OK for here. This is not legal initialization,
                                 // however, there are values for all 4 basic features
                                 // and still p13 is not yet registered in the system,
                                 // so, as mentioned, it's OK for here.
//  p13=p1;  // compilation error. can not do such an assignment.

TEST("1.1")
  cout << p1 << endl;
// displays p1 in a single line, in the format
// [Israel/Song_Israel/175/Singer_Israel]

TEST("1.2")
  cout << p2 << endl << p4 << endl;
// we get here the following display :
// [UK/Song_UK/170/Singer_UK]
// [Australia/Song_Australia/180/Singer_Australia]

TEST("1.3")
  cout << p1.state() << endl;  // output is Israel
  cout << p1.song() << endl;  // output is Song_Israel
  cout << p1.timeLength() << endl;  // output is 175
  cout << p1.singer() << endl;  // output is Singer_Israel

TEST("1.4")
  cout << p1.isRegistered() << endl; // output here is 0 because p1 here
                                     // still not registered in the system.
  p1.update("new_name", 140, "new_singer"); // 3 parameters. No parameter for state name,
                                            // because it is NOT possible to change
                                            // the state name. if song name is "" then
                                            // the old name stays. the same is with the singer name.
                                            // if time length is 0 then the old one stays.
                                            // update can be done only if p1 is not registered, otherwise
                                            // nothing is done.

TEST("1.5")
  cout << p1 << endl;
  p1.update("Song_Israel",175,"Singer_Israel");
  cout<< p1 << endl;

  p1.updateRegistered(true); // Although it's a public method, we assume
                             //   that ONLY MainControl will use it for
                             //   inner purposes. p1 is signed as registered in the system.
  p1.updateRegistered(false); // Same remarks. Now it is not registered.

//------------------------------------------------

TEST("1.6")
  ((((eurovision += p1) += p2) += p3) += p4) += p5;
/*
   try to register p1 and then p2 and the p3 and then p4 and then p5
   to the system;
   the registration will not succeed in the following cases :
   1. The current phase is not Registration.
      phase of the system is initialized by default to Registration.
      Then it can be changed by setPhase method, e.g.
      eurovision.setPhase(Contest);
      eurovision.setPhase(Voting);
   2. we've already reached to the max allowed number of participants (default is 26).
   3. There is already a registered participant from the relevant state.
   4. Name of state is "" or name of song or singer is "" or
      time length is greater than the max time allowed. default of max time
      allowed is 180 (sec).
   if registration fails, then just ignore it without anything else and
   continue to the next operation in the program.
   in this example p3 can not be registered bacause its time length 190
   is greater than the maximum allowed.
*/

  cout << eurovision << endl;
/*
  displays the main features of the system.
  All the display is between curly brackets ({ in the first line, then continue
  to next line, then all the relevant data, then } in the last line.
  first line after { displays the phase - can be one of Registration or Contest or Voting.
  if phase is Registration, then all Registered participant are displayed
  sorted regarding state name. each state in a different line, in the same format
  as operator<< to a participant.
  if phase is Contest, nothing more is displayed.
  if phase is Voting, then all votes (both Regular and Judge) are displayed,
  in respect to all states of registered participants.
  each state in a different line. the states are sorted in respect to state name.

  example :
{
Registration
[Australia/Song_Australia/180/Singer_Australia]
[Cyprus/Song_Cyprus/172/Singer_Cyprus]
[Israel/Song_Israel/175/Singer_Israel]
[UK/Song_UK/170/Singer_UK]
}

  another example relevant to Voting phase - explanation will follow later :
{
Voting
Australia : Regular(0) Judge(8)
Cyprus : Regular(6) Judge(12)
Israel : Regular(1) Judge(0)
UK : Regular(1) Judge(10)
}

*/

  eurovision -= p5;
/*
  unregister p5 from the system.
  it is allowed to do this only in the Registration phase.
  Moreover, if p5 is not registered, then just ignore the operation without
  further notice.

  can also do operations like

  (((eurovision -= p5) -= p3) += p4) -= p4;

*/

TEST("1.7")
  (((eurovision -= p5) -= p3) += p4) -= p4;
  cout << eurovision << endl;

  ((eurovision += p4) += p3) += p5;
  cout << eurovision << endl;

  eurovision.setPhase(Voting);
/*
  There are 3 phases :
  Registration - Registration and unregistration of participants.
  This is the default initial phase.
  Contest - This phase symbolizes the performance off all songs on the stage.
  Voting - in this stage we do and count the voting.
  The move from Registration to Contest and/or from Contest to Voting
  is done via the operation setPhase(<new_phase>).
  It's possible to move ONLY from Registration to Contest and from Contest to
  Voting. in all other cases nothing is done and the operation is ignored.
  No other special treatment.
  In this example the operation
  eurovision.setPhase(Voting);
  is ignored because we are still in the phase of Registration.
*/

  eurovision.setPhase(Contest);
  eurovision.setPhase(Voting);  // will work now.


TEST("1.8")
cout << eurovision.legalParticipant(p1); // will display 1 (bool)
cout << eurovision.legalParticipant(p3); // will display 0 (false)

/* the operation legalParticipant checks if all the following exists :
   the names of the state and the song and the singer are not empty "",
   as well as time length of the song is not big than the max allowed time length
   for any song. this max allowed value is determined when defining the
   system object. default is 180 (sec).
*/

TEST("1.9")
  cout << p2 << endl;
  p2.update("", 169, "");  // can not be done. it is not Registration phase.
  cout << p2  << endl;

  cout << p3  << endl;
  p3.update("", 179, "");  // can not be done. it's not Registration phase.
  cout << p3  << endl;

  eurovision += p3; //can not be done. it's not Registration phase.

  cout << eurovision << endl;

  eurovision -= p1; //can not be done. it's not Registration phase.
  cout << eurovision << endl;

TEST("1.10")
  cout << eurovision.participate("Israel");  // 1 (true). The state Israel is registered and participates.
  cout << eurovision.participate("France");  // 0 (false). France is not registered, therefoe does not participate.

  cout << "------------------------------" << endl;


  Voter vr1("Israel");
/* vr1 is a potential voter that comes from Israel.
   any voter belongs to a state and can be either Regular or Judge. The default is Regular.
   no default to the state.  vr1 can be defind also as
   Voter vr1("Israel", Regular);
*/

TEST("1.11")
 cout << vr1.state() << endl;  // Israel
 cout << (vr1.voterType() == Regular) << endl;  // 1 (bool)

 cout << vr1 << endl;  // will display <Israel/Regular>

 Voter vj1("Israel",Judge);
 cout << (vj1.voterType() == Judge) << endl;  // 1
 cout << vj1 << endl;  // will display <Israel/Judge>

//in the following there are other declarations of voters.

  Voter vr2("Israel");
  Voter vr3("UK");
  Voter vr4("France");
  Voter vr5("Australia");
  Voter vr6("Cyprus", Regular);
  Voter vj2("Israel",Judge);
  Voter vj3("UK",Judge);
  Voter vj4("France",Judge);
  Voter vj5("Australia",Judge);
  Voter vj6("Cyprus",Judge);

/* a voter can not vote for his own state.
   can vote for any other state, in condition that both
   his state and the state to vote for are registered and participate.
   otherwise the vote operation is just ignored without any other notice.
   a Regular voter votes each time for a single state. This state gets 1 point
   for each voting. The regular voter can vote more than once, but no more than max allowed times for voting,
   which is defined when declaring the MainControl system. Default is 5.
   Moreover, he can vote all the times for the same state, or he can vote
   each time for a different state, in condition he does not exceed the allowed
   limit of max times of voting.
   a Judge voter can vote only ONCE, no more. all additions votings of his are
   just ignored without furthere notification.
   in contradiction to a regular voter, he can give a list of 1 to 10 different state names.
   the points given to the states are according to the order they are mentioned :
   first state gets 12 points, second 10 points, third 8 points and so on.
   if there less than 10 states, then only the given states get points, starting from 12,
   according to their order.
   if there are states that are not registered in the system, they are ignored.
   in any case, the points to every state are given regarding its absolute order number,
   no matter if previous states in the list are not legal.
   remark - we assume that the list for a Judge voter does not have states that appear
   more than once. No need to check this.
*/

TEST("1.12")
  eurovision += Vote(vr1, "Israel"); // Illegal. Not counted. vr1 is from Israel, therefore
                                     // is NOT allowed to vote for Israel.
  cout << eurovision << endl;

/*
in the Voting phase we'll get here
first line - the phase name
other lines - all states are displayed sorted by state names, each state in a different line.
in each line we get
<state_name> : Regular(<num of points for regular votes>) Judge(<num of points for Judge votes>)
*/

TEST("1.13")
  ((((eurovision += Vote(vr1, "Cyprus")) += Vote(vr1, "Cyprus")) += Vote(vr1, "Cyprus")) += Vote(vr1, "Cyprus")) += Vote(vr1, "Cyprus");
  cout << eurovision << endl;

TEST("1.14")
  eurovision += Vote(vr1, "Cyprus"); /* Not counted. vr1 has already exceeded
  max allowed times for voting (5 in this case) */

  cout << eurovision << endl;

  cout << vr1.timesOfVotes() << endl;  // 5

  ++vr1; // this operation increments the number of times that vr1 has voted.
         // although it's a public method, we assume that it will be use ONLY internally
         // by other relevant operations, specially when vr21 votes successfully and needs
         // to count the number of times he has voted.
         // NO operation of --vr1 is given.


TEST("1.15")
  ((((eurovision += Vote(vr5, "Australia")) += Vote(vr5, "Israel")) += Vote(vr5, "Cyprus")) += Vote(vr5, "UK")) +=
           Vote(vr5, "Australia");
  cout << eurovision << endl;

TEST("1.16")
  eurovision += Vote(vr5, "Cyprus"); /* Not counted. vr5 has already exceeded max allowed times for voting */
  cout << eurovision << endl;

TEST("1.17")
  eurovision += Vote(vj1, "Cyprus", "UK", "Australia");
  /* example of voting of a Judge */
  cout << eurovision << endl;

  return 0;
}
