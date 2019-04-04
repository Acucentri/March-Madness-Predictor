//
// Created by Jacob Upton on 2019-03-23.
//

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <map>

#include "Game.h"
#include "Team.h"

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
    Game::Game(){
        setDate(nullptr);
        setTeam1(-1);
        setScore1(-1);
        setField1(-2);
        setTeam1(-1);
        setScore1(-1);
        setField1(-2);
    }

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
    Game::Game(std::string date,int team1, int field1, int score1, int team2, int field2, int score2){
        setDate(date);
        setTeam1(team1);
        setScore1(score1);
        setField1(field1);
        setTeam2(team2);
        setScore2(score2);
        setField2(field2);
    }

    /**
     * sets the date of to a parameter value
     * @param date the new date
     */
    void Game::setDate(std::string date){
        this->date = date;
    }

    /**
     * gets the current date
     * @return the current date
     */
    std::string Game::getDate(){
        return this->date;
    }

    /**
     * sets the team to a parameter value
     * @param team1 the new team
     */
    void Game::setTeam1(int team1){
        this->team1 = team1;
    }

    /**
     * gets the current team1
     * @return the current team1
     */
    int Game::getTeam1(){
        return this->team1;
    }

    /**
     * sets the score1 to a parameter value
     * @param score1 the new score
     */
    void Game::setScore1(int score1){
        this->score1 = score1;
    }

    /**
     * gets the current score1
     * @return the current score1
     */
    int Game::getScore1(){
        return this->score1;
    }

    /**
     * sets the field1 to a parameter value
     * @param field1 the new field1
     */
    void Game::setField1(int field1){
        this->field1 = field1;
    }

    /**
     * gets the current field1
     * @return the current field1
     */
    int Game::getField1(){
        return this->field1;
    }

    /**
     * sets the team2 to a parameter value
     * @param team2 the new team2
     */
    void Game::setTeam2(int team2){
        this->team2 = team2;
    }


    /**
     * gets the current team2
     * @return the current team2
     */
    int Game::getTeam2(){
        return this->team2;
    }

    /**
     * sets the score2 to a parameter value
     * @param score2 the new score2
     */
    void Game::setScore2(int score2){
        this->score2 = score2;
    }

    /**
     * gets the current score2
     * @return the current score2
     */
    int Game::getScore2(){
        return this->score2;
    }

    /**
     * sets the field2 to a parameter value
     * @param field2 the new field2
     */
    void Game::setField2(int field2){
        this->field2 = field2;
    }

    /**
     * gets the current field2
     * @return the current field2
     */
    int Game::getField2(){
        return this->field2;
    }

    /**
     * returns the score of the winning team
     * @return the score of the winning team
     */
    int Game::getWinningScore(){
        return 0;
    }

    /**
     * returns the score of the losing team
     * @return the score of the losing team
     */
    int Game::getLosingScore(){
        return 0;
    }

    /**
     * returns a string of the game object. It contains the date, team names,
     * team fields and team scores.
     * @return the game object as a string.
     */
    std::string Game::toString(){
        return  "\t" + this->getDate() + " : "
                + std::to_string(this->getTeam1()) + " : "
                + std::to_string(this->getScore1()) + " : "
                + std::to_string(this->getField1()) + " : "
                + std::to_string(this->getTeam2()) + " : "
                + std::to_string(this->getScore2()) + " : "
                + std::to_string(this->getField2()) + "\n";
    }