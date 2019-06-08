#include <iostream>
#include "eurovision.h"

const string EMPTY_STRING = "";

Participant::Participant(const string& p_origin, const string& p_song, const int p_song_len, const string& p_name):
participant_origin_country(p_origin), participant_song(p_song), participant_song_len(p_song_len),
participant_name(p_name), participant_is_registered(false){}

void Participant::update(const string& p_song, const int p_song_len, const string& p_name) {
    participant_song = p_song;
    participant_song_len = p_song_len;
    participant_name = p_name;
}

void Participant::updateRegistered(const bool is_registered) {
    participant_is_registered = is_registered;
}

string Participant::song() const {
    return participant_song;
}

string Participant::state() const {
    return participant_origin_country;
}

string Participant::singer() const {
    return participant_name;
}

int Participant::timeLength() const {
    return participant_song_len;
}

bool Participant::isRegistered() const {
    return participant_is_registered;
}


Voter::Voter(const string& v_origin, const int v_type):
voter_origin(voter_origin), voter_type(v_type)
{
    times_voted =  0;
}

int Voter::voterType() const {
    return voter_type;
}

string Voter::state() const {
    return voter_origin;
}

int Voter::timesOfVotes() const{
    return times_voted;
}

Voter& Voter::operator++() {
    times_voted++;
}

bool operator==(const Voter& voter1,const Voter& voter2){
    if (voter1.voter_type == voter2.voter_type && voter1.voter_origin == voter2.voter_origin){
        return true;
    }
    return false;
}

Voter::Voter(const Voter &voter):
voter_origin(voter.voter_origin), voter_type(voter.voter_type)
{
    times_voted = voter.times_voted;
}

Vote::Vote(Voter v, string p1_name, string p2_name, string p3_name, string p4_name, string p5_name, string p6_name,
           string p7_name, string p8_name, string p9_name, string p10_name):
           voter(v){
    vote_receiver_names = new string[JUDGE_VOTE_ARRAY_SIZE];
    vote_times = 1;
    if (v.voterType() == Regular){
        vote_receiver_names[0] = p1_name;
    }
    else if (v.voterType() == Judge){
        vote_receiver_names[0] = p1_name;
        vote_receiver_names[1] = p2_name;
        vote_receiver_names[2] = p3_name;
        vote_receiver_names[3] = p4_name;
        vote_receiver_names[4] = p5_name;
        vote_receiver_names[5] = p6_name;
        vote_receiver_names[6] = p7_name;
        vote_receiver_names[7] = p8_name;
        vote_receiver_names[8] = p9_name;
        vote_receiver_names[9] = p10_name;
    }
}

Vote::~Vote() {
    delete(vote_receiver_names);
}

Vote::Vote(const Vote &vote):
voter(vote.voter)
{
    vote_receiver_names = new string[JUDGE_VOTE_ARRAY_SIZE];
    for (int i = 0; i<JUDGE_VOTE_ARRAY_SIZE; i++){
        vote_receiver_names[i] = vote.vote_receiver_names[i];
    }
    vote_times = vote.vote_times;
}

bool operator==(const Vote& vote1,const Vote& vote2){
    if (vote1.voter == vote2.voter && vote1.vote_receiver_names == vote2.vote_receiver_names) {
        return true;
    }
    return false;
}

MainControl::MainControl(const int max_song_len, int max_participants, int max_regular_votes):
max_song_len(max_song_len), max_participants(max_participants), max_regular_votes(max_regular_votes){
    phase = Registration;
    participants = new Participant*[INITIAL_ARRAY_SIZE];
    num_participants = 0;
    participants_arr_size = INITIAL_ARRAY_SIZE;
    voters = new Voter*[INITIAL_ARRAY_SIZE];
    num_voters = 0;
    voters_arr_size = INITIAL_ARRAY_SIZE;
    votes = new Vote*[INITIAL_ARRAY_SIZE]();
    num_votes = 0;
    votes_arr_size = INITIAL_ARRAY_SIZE;
}

MainControl::~MainControl() {
    delete(participants);
    delete(voters);
    delete(votes);
}

void MainControl::setPhase(const int phase) {
    this->phase = phase;
}

bool MainControl::participate(const string& p_name) { //Might raise problems
    Participant* cur_p_ptr;
    for(int i = 0; i<max_participants; i++){
        cur_p_ptr = participants[i];
        if (cur_p_ptr!= nullptr){
            Participant cur_p = *cur_p_ptr;
            if (cur_p.singer() == p_name){
                return true;
            }
        }
    }
    return false;
}

bool MainControl::legalParticipant(const Participant &p) {
    if (p.singer() == EMPTY_STRING || p.state() == EMPTY_STRING || p.song() == EMPTY_STRING ||
    p.timeLength() > max_song_len){
        return false;
    }
    return true;
}

MainControl& MainControl::operator+=(const Vote &vote) {
    Vote *cur_vote_ptr;
    //adding a vote is only defined for regular voters. also, if a voter voted max_regular_votes times, we should ignore
    //all his subsequent votes.
    if (vote.voter.voterType() == Regular && vote.vote_times < max_regular_votes) {
        //first, we check if there is already an existing vote, if there is, we will add 1 to it.
        for (int i = 0; i < votes_arr_size; i++) {
            cur_vote_ptr = votes[i];
            Vote cur_vote = *cur_vote_ptr;
            if (vote.voter.voterType() == Regular && cur_vote == vote) {
                cur_vote.vote_times += vote.vote_times;
            }
        }
        //such a vote doesn't exist, so we will create one. first, we will check if we need to increase the size of our
        //vote_arr.
        num_votes += 1;
        if (num_votes > votes_arr_size) {
            //how are we gonna change the votes_arr_size from expand_votes_arr?
            votes_arr_size *= ARRAY_INCREASE_FACTOR;
            Vote** new_votes = new Vote*[votes_arr_size]();
            for (int i = 0; i<votes_arr_size/ARRAY_INCREASE_FACTOR; i++){
                new_votes[i] = votes[i];
            }
            delete(votes);
            votes = new_votes;
        }
        for (int i = 0; i<votes_arr_size;i++){
            if (votes[i] == nullptr){
                Vote new_vote = Vote(vote);
                //this might get destroyed when exiting this function. we should make sure it isn't, and in the case it
                //is, we should use new. and then delete when destroying eurovision.
                votes[i] = &new_vote;
            }
        }
    }
    return this;
}