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

        while( getline(in2,index, ',') )
        {

            getline(in2,team,'\n');

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

        while( getline(in1,index, ',') )
        {

            getline(in1,date,',');
            getline(in1,team1,',');
            getline(in1,field1,',');
            getline(in1,score1,',');
            getline(in1,team2,',');
            getline(in1,field2,',');
            getline(in1,score2,'\n');

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
     * This method is responsible for reformatting the Game File
     * @param file file name
     */
    void MarchMadness::reformatDocumentGame(std::string file) {
        std::string index,date,team1,field1,score1,team2,field2,score2;

        std::ofstream myfile;
        std::string newFileName = file.substr (0,file.size()-4);
        myfile.open(newFileName+"(New).txt");

        std::ifstream in1(file);

        while( getline(in1,index, ',') ) {

            getline(in1, date, ',');
            getline(in1, team1, ',');
            getline(in1, field1, ',');
            getline(in1, score1, ',');
            getline(in1, team2, ',');
            getline(in1, field2, ',');
            getline(in1, score2, ' ');
            getline(in1, score2, ' ');

            myfile << index << ','
                      << date << ','
                      << team1 << ','
                      << field1 << ','
                      << score1 << ','
                      << team2 << ','
                      << field2 << ','
                      << score2 << '\n';
        }

        myfile.close();
    }

    /**
     * This method is responsible for reformatting the Team File
     * @param file file name
     */
    void MarchMadness::reformatDocumentTeam(std::string file) {
        std::string team, index;

        std::ifstream in2(file);

        std::ofstream myfile;
        std::string newFileName = file.substr (0,file.size()-4);
        myfile.open(newFileName+"(New).txt");

        while( getline(in2,index, ',') )
        {

            getline(in2,team,' ');
            getline(in2,team,' ');

            myfile << index << ','
                      << team << '\n';
        }
        myfile.close();
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
