//
// Created by Jacob Upton on 2019-03-23.
//

#ifndef MARCHMADNESS_GAME_H
#define MARCHMADNESS_GAME_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <map>

#include "Team.h"

class Team;

class Game {

public:

    //The date that the game took place on
    std::string date;

    //One of the teams that played in the game
    int team1;

    //The score that the first team had
    int score1;

    //Whether the team was home (1) or away (-1) or neither (0)
    int field1;

    //One of the teams that played in the game
    int team2;

    //The score that the second team had
    int score2;

    //Whether the team was home (1) or away (-1) or neither (0)
    int field2;


    /**
     * DEFAULT constructor. this sets the date to null, creates empty team objects, sets the 
     * score of each team to -1, and the field of each team to -2
     */
    Game();

    /**
     * This constructor takes in a value of each of the class variables and sets them equal to 
     * their corresponding variable.
     * @param date the date of the game
     * @param team1 the team object for the first team
     * @param score1 the score of the first game
     * @param field1 the field for the first team
     * @param team2 the team object for the second team
     * @param score2 the score of the second game
     * @param field2 the field for the second team
     */
    Game(std::string date,int team1, int score1, int field1, int team2, int score2, int field2);

    /**
     * sets the date of to a parameter value
     * @param date the new date
     */
    void setDate(std::string date);

    /**
     * gets the current date 
     * @return the current date
     */
    std::string getDate();

    /**
     * sets the team to a parameter value
     * @param team1 the new team 
     */
    void setTeam1(int team1);

    /**
     * gets the current team1
     * @return the current team1
     */
    int getTeam1();

    /**
     * sets the score1 to a parameter value
     * @param score1 the new score
     */
    void setScore1(int score1);

    /**
     * gets the current score1
     * @return the current score1
     */
    int getScore1();

    /**
     * sets the field1 to a parameter value
     * @param field1 the new field1
     */
    void setField1(int field1);

    /**
     * gets the current field1
     * @return the current field1
     */
    int getField1();

    /**
     * sets the team2 to a parameter value
     * @param team2 the new team2 
     */
    void setTeam2(int team2);


    /**
     * gets the current team2
     * @return the current team2
     */
    int getTeam2();

    /**
     * sets the score2 to a parameter value
     * @param score2 the new score2
     */
    void setScore2(int score2);

    /**
     * gets the current score2
     * @return the current score2
     */
    int getScore2();

    /**
     * sets the field2 to a parameter value
     * @param field2 the new field2
     */
    void setField2(int field2);

    /**
     * gets the current field2
     * @return the current field2
     */
    int getField2();

    /**
     * returns the score of the winning team
     * @return the score of the winning team
     */
    int getWinningScore();

    /**
     * returns the score of the losing team
     * @return the score of the losing team
     */
    int getLosingScore();

    /**
     * returns a string of the game object. It contains the date, team names, 
     * team fields and team scores.
     * @return the game object as a string.
     */
    std::string toString();

};
#endif //MARCHMADNESS_GAME_H
