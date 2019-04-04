//
// Created by Jacob Upton on 2019-03-23.
//

#ifndef MARCHMADNESS_TEAM_H
#define MARCHMADNESS_TEAM_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <map>

#include "Game.h"

class Game;

class Team {

public:

    // The ID number for the team
    int ID;

    // The number of games the team has played
    int numGamesPlayed;

    // The name of the current team object
    std::string teamName;

    // A vector containing all of the different games that the Team has played
    std::vector<Game> gameCollection;

    /**
     * Default constructor. Takes no parameters. Sets Team name to an empty string
     * and sets the teamID and number of games played to -1
     */
    Team();

    /**
     * Constructor taking in different arguemnts to set to local varibales
     * @param id the teamID
     * @param numGamesPlayed the number of games played
     * @param teamName the team name
     */
    Team(int id, std::string teamName);


    /**
     * sets the current teamID to this parameter
     * @param id new teamID
     */
    void setID(int id);

    /**
     * gets the current teamID
     * @return the current teamID
     */
    int getID();

    /**
     * sets the current numGamesPlayed to this parameter
     * @param numGamesPlayed new numGamesPlayed
     */
    void setNumGamesPlayed(int id);

    /**
     * gets the current numGamesPlayed
     * @return the current numGamesPlayed
     */
    int getNumGamesPlayed();

    /**
     * sets the current teamName to this parameter
     * @param teamName new teamName
     */
    void setTeamName(std::string teamName);

    /**
     * gets the current teamName
     * @return the current teamName
     */
    std::string getTeamName();

    /**
     * adds another game to the vector of games that the team had been apart of
     * @param game a Game that the team has played
     */
    void addGame(Game game);

    /**
     * gets the vector that contains all of the games that the team has played
     * @return a collection of games the team has played
     */
    std::vector<Game> getGameCollection();


    /**
     * displays all of the games that this team has played
     */
    void displayGames();

    /**
     * this is a toString method for the team. Returns a string of the teamName, teamID, and
     * number of games played
     * @return string of the team object
     */
    std::string toString();

};
#endif //MARCHMADNESS_TEAM_H
