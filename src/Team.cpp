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

    // The ID number for the team
    int ID;

    // The number of games the team has played
    int numGamesPlayed;

    // The name of the current team object
    std::string teamName;

    // A map containing all of the different games that the Team has played
    std::vector<Game> gameCollection;

    /**
     * Default constructor. Takes no parameters. Sets Team name to an empty string
     * and sets the teamID and number of games played to -1
     */
    Team::Team(){
        setID(-1);
        setNumGamesPlayed(-1);
        setTeamName("");
    }

    /**
     * Constructor taking in different arguemnts to set to local varibales
     * @param id the teamID
     * @param numGamesPlayed the number of games played
     * @param teamName the team name
     */
    Team::Team(int id, std::string teamName){
        setID(id);
        setNumGamesPlayed(-1);
        setTeamName(teamName);
    }

    /**
     * sets the current teamID to this parameter
     * @param id new teamID
     */
    void Team::setID(int id){
        this->ID = id;
    }

    /**
     * gets the current teamID
     * @return the current teamID
     */
    int Team::getID(){
        return this->ID;
    }

    /**
     * sets the current numGamesPlayed to this parameter
     * @param numGamesPlayed new numGamesPlayed
     */
    void Team::setNumGamesPlayed(int numGamesPlayed){
        this->numGamesPlayed = numGamesPlayed;
    }

    /**
     * gets the current numGamesPlayed
     * @return the current numGamesPlayed
     */
    int Team::getNumGamesPlayed(){
        return this->numGamesPlayed;
    }

    /**
     * sets the current teamName to this parameter
     * @param teamName new teamName
     */
    void Team::setTeamName(std::string teamName){
        this->teamName = teamName;
    }

    /**
     * gets the current teamName
     * @return the current teamName
     */
    std::string Team::getTeamName(){
        return this->teamName;
    }

    /**
     * adds another game to the vector of games that the team had been apart of
     * @param game a Game that the team has played
     */
    void Team::addGame(Game game) {
        gameCollection.push_back(game);
    }

    /**
     * gets the vector that contains all of the games that the team has played
     * @return a collection of games the team has played
     */
    std::vector<Game> Team::getGameCollection(){
        return this->gameCollection;
    }

    /**
     * displays all of the games that this team has played
     */
    void Team::displayGames(){
        for(Game g: gameCollection){
            std::cout<< g.toString();
        }
    }

    /**
     * this is a toString method for the team. Returns a string of the teamName, teamID, and
     * number of games played
     * @return string of the team object
     */
    std::string Team::toString(){
        return "";
    }