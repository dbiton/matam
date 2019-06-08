/**TODO: we should check when the value a function returns should be const, i.e, if I return the name of a participant,
 * should the return value be const since it shouldn't be changed, or should we allow the user to change it? we should
 * ask a supervisor. for now - I left it as is.
 *
 * p.s. notice vote holds an array of votes. this is to allow the judge voting style, i.e.
 * Vote(voter, "Cyprus", "UK", "Australia");
 * ONLY IN THE CASE THAT VOTER IS A JUDGE SHOULD THIS SYNTAX BE VALID!
 * in the case that he is not a judge, we should return some sort of error, or add a single vote for the first
 * participant. also, in this example, we would add 10 Vote instances of (voter, "Cyprus"), since a judge gives 10
 * points for his chosen first place, and so on for the next places. all the fields after p1 in vote are NULL since
 * they should have some default value for the case in which the voter is of type Regular, so we wouldn't have to type
 * "NULL" in all fields after the Regular votes choosing.
**/

#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>

// it's allowed to define here any using statements, according to needs.
// do NOT define here : using namespace std;

#include <string>
using std::string;
using std::ostream;

//---------------------------------------------------
//this is where we will define values, in order to make the code more readable and avoid using "magic numbers".

const int MAX_SONG_LEN = 180; //in seconds
const int MAX_PARTICIPANTS = 26;
const int MAX_REGULAR_VOTES = 5;
const int INITIAL_ARRAY_SIZE = 8;
const int ARRAY_INCREASE_FACTOR = 2;
const int JUDGE_VOTE_ARRAY_SIZE = 10; //DO NOT CHANGE, IT'S HARDCODED IN!

//---------------------------------------------------

enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };

//---------------------------------------------------

class Participant
{
// relevant private members can be defined here, if necessary.
const string participant_origin_country;
string participant_song;
int participant_song_len;
string participant_name;
bool participant_is_registered;

public :
    Participant(const string& p_origin, const string& p_song, const int p_song_len, const string& p_name);
    string state() const;
    string song() const;
    string singer() const;
    int timeLength() const;
    bool isRegistered() const;
    void update(const string& p_song, const int p_song_len, const string& p_name);
    void updateRegistered(const bool is_registered);
// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

// NO friend is allowed here.
};

ostream& operator<<(ostream& os, const Participant& participant);

//---------------------------------------------------


class Voter
{
// relevant private members can be defined here, if necessary.
const int voter_type;
const string voter_origin;
int times_voted;
//this is a pointer to the first element on an array of votes that we will create to hold each voter's votes. the type
//is void because since Vote hasn't been declared yet, we cannot use it.
//
public :
    Voter(const string& v_origin, const int v_type = Regular);
    Voter(const Voter& voter);
    int voterType() const;
    string state() const;
    int timesOfVotes() const;
    Voter& operator++();
    friend bool operator==(const Voter& vote1,const Voter& vote2);
// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

// NO friend is allowed here.

};

ostream& operator<<(ostream& os, const Voter& voter);

// -----------------------------------------------------------

struct Vote
{
    const Voter voter;
    int vote_times;
    //We shouldn't copy voter to here. we should use a reference to the associated voter, so that in case the voter's
    //name is changed for example, the name here would change as well.
    string* vote_receiver_names;
    Vote(Voter v, string p1_name,string p2_name = nullptr, string p3_name= nullptr, string p4_name = nullptr,
            string p5_name = nullptr, string p6_name = nullptr, string p7_name = nullptr, string p8_name = nullptr,
            string p9_name = nullptr, string p10_name = nullptr);
    ~Vote();
    Vote(const Vote& vote);
    friend bool operator==(const Vote& vote1,const Vote& vote2);

// ALL is public here.
// need to define ONLY data members and c'tr and d'tr.
// NO NEED to define anything else.

};

// -----------------------------------------------------------

class MainControl
{
// relevant private members can be defined here, if necessary.
int phase;
const int max_song_len;
const int max_participants;
const int max_regular_votes;

Participant** participants;
int num_participants;
int participants_arr_size;
Voter** voters;
int num_voters;
int voters_arr_size;
Vote** votes;
int num_votes;
int votes_arr_size;

public :
    MainControl(const int max_song_len = MAX_SONG_LEN, const int max_participants = MAX_PARTICIPANTS,
            const int max_regular_votes = MAX_REGULAR_VOTES);
    ~MainControl();
    void setPhase(const int phase);
    MainControl& operator+=(const Participant& p);
    MainControl& operator-=(const Participant& p);
    MainControl& operator+=(const Vote& vote);
    friend ostream& operator <<(ostream& os, const MainControl& mc);
    bool legalParticipant(const Participant& p);
    bool participate(const string& p_name);
// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

// Also it's allowed here to define friend.

};

// -----------------------------------------------------------

#endif
