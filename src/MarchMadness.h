//
// Created by Jacob Upton on 2019-03-23.
//
#ifndef MARCHMADNESS_MARCHMADNESS_H
#define MARCHMADNESS_MARCHMADNESS_H

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

class MarchMadness {

    public:

        /**
         * Main constructer for MarchMadness Class
         * @param teamFileName the name of the file containing information about teams
         * @param gameFileName the name of the file containing information about games
         */
        MarchMadness(std::string teamFileName,std::string gameFileName);

        /**
         * Responsible for iterating through a document containing all team names
         * along with an ID
         * @param teamFileName
         */
        void readInTeams(std::string teamFileName);

        /**
         * Responsible for iterating through a document containing information about
         * all of the different games that were played. This document containds a gameID, date,
         * team1, score1, field1, team2, score2, and field2
         * @param gameFileName
         */
        void readInGames(std::string gameFileName);

        /**
         * This method is responsible for displaying the Matrix and the solution to the
         * linear system of equations.
         */
        void display();

        /**
         * Reformat
         */
        void reformatDocumentTeam(std::string file);

        /**
         * Reformat
         */
        void reformatDocumentGame(std::string file);
};

#endif //MARCHMADNESS_MARCHMADNESS_H
