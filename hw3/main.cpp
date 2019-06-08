#include <iostream>

#include "eurovision.h"

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
    vote_arr_size = DEAFULT_INITIAL_ARRAY_SIZE;
    times_voted =  0;
    //votes_arr = new Vote[DEAFULT_INITIAL_ARRAY_SIZE];
}

int Voter::voterType() {
    return voter_type;
}

string Voter::state() {
    return voter_origin;
}

int Voter::timesOfVotes() {
    return times_voted;
}

Voter& Voter::operator++() {
    times_voted++;
}


Vote::Vote(Voter v, string p1_name, string p2_name, string p3_name, string p4_name, string p5_name, string p6_name,
           string p7_name, string p8_name, string p9_name, string p10_name):
           voter(v){
    vote_receiver_names = new string[10];
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