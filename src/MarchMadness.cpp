//
// Created by Jacob Upton on 2019-03-19.
//

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <map>

#include "MarchMadness.h"
#include "Game.h"
#include "Team.h"

    /**
     * Main constructer for MarchMadness Class
     * @param teamFileName the name of the file containing information about teams
     * @param gameFileName the name of the file containing information about games
     */
    MarchMadness::MarchMadness(std::string teamFileName, std::string gameFileName) {
        readInTeams(teamFileName);
        readInGames(gameFileName);
    }

    /**
     * Responsible for iterating through a document containing all team names
     * along with an ID
     * @param teamFileName
     */
    void MarchMadness::readInTeams(std::string teamFileName) {

        std::string team, index;
        std::ifstream in2(teamFileName);

        getline(in2,index,'\n');
        getline(in2,index,'\n');
        getline(in2,index,'\n');
        getline(in2,index,'\n');
        getline(in2,index,'\n');
        getline(in2,index,'\n');
        getline(in2,index,'\n');
        getline(in2,index,'\n');
        getline(in2,index,'\n');

        while( getline(in2,index, ',') )
        {

            getline(in2,team,'\n');
            team.pop_back();

            std::cout << index << '\t'
            << team << '\n';
        }
    }

    /**
     * Responsible for iterating through a document containing information about
     * all of the different games that were played. This document containds a gameID, date,
     * team1, score1, field1, team2, score2, and field2
     * @param gameFileName
     */
    void MarchMadness::readInGames(std::string gameFileName) {

        std::string index,date,team1,field1,score1,team2,field2,score2;

        std::ifstream in1(gameFileName);
        getline(in1,index,'\n');
        getline(in1,index,'\n');
        getline(in1,index,'\n');
        getline(in1,index,'\n');
        getline(in1,index,'\n');
        getline(in1,index,'\n');
        getline(in1,index,'\n');
        getline(in1,index,'\n');
        getline(in1,index,'\n');

        while( getline(in1,index, ',') )
        {

            getline(in1,date,',');
            getline(in1,team1,',');
            getline(in1,field1,',');
            getline(in1,score1,',');
            getline(in1,team2,',');
            getline(in1,field2,',');
            getline(in1,score2,'\n');
            score2.pop_back();

            std::cout << index << '\t'
                      << date << '\t'
                      << team1 << '\t'
                      << field1 << '\t'
                      << score1 << '\t'
                      << team2 << '\t'
                      << field2 << '\t'
                      << score2 << '\n';
        }
    }

    /**
     * This method is responsible for displaying the Matrix and the solution to the
     * linear system of equations.
     */
    void MarchMadness::display() {


    }

    /**
     * MAIN METHOD
     */
    int main() {
        std::string teamFileName, gameFileName;
        std::cout << "Please input the name of the team file:" << "\n";
        std::cin >> teamFileName;
        std::cout << "Please input the name of the game file:" << "\n";
        std::cin >> gameFileName;
        MarchMadness m = MarchMadness(teamFileName,gameFileName);

    }
