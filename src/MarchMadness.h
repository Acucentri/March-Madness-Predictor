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
#include "../Eigen_Folder/Eigen/Core"
#include "../Eigen_Folder/Eigen/Dense"

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
         * This method is responsible for constructing the main matrix. Each Row and corresponding column represents a team.
         * The bottom row of the matrix is set to all 1's so that the solution is unique
         * @param m The Matrix
         * @param b The Vector
         * @param size The number of teams
         * @param teamCollection the collection of teams
         */
        void ConstructMatrix(Eigen::MatrixXf *m, Eigen::VectorXf *b, const size_t size, std::vector<Team> teamCollection);

        /**
         * This method is used to sort the solution to the system of linear equations. Then, this solution is
         * printed out, showing the teams in decreasing order, where the first team is the team most likely to win.
         * @param x The Vector
         * @param size The number of teams
         * @param teamCollection the collection of teams
         */
        std::vector<std::pair<int, long double>> sortSolution(Eigen::VectorXf x, const size_t size, std::vector<Team> teamCollection);

        /**
         * Responsible for iterating through a document containing all team names
         * along with an ID
         * @param teamFileName
         */
        std::vector<Team> readInTeams(std::string teamFileName);

        /**
         * Responsible for iterating through a document containing information about
         * all of the different games that were played. This document containds a gameID, date,
         * team1, score1, field1, team2, score2, and field2
         * @param gameFileName
         */
        void readInGames(std::string gameFileName,std::vector<Team> *teamCollection);

        /**
         * This method is responsible for displaying the Matrix and the solution to the
         * linear system of equations.
         */
        void display(Eigen::MatrixXf *m, Eigen::VectorXf *b, std::vector<std::pair<int, long double>> *s, const size_t size, std::vector<Team> *teamCollection);

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
