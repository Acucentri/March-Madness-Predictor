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
#include <chrono>
#include <iostream>
#include <set>
#include <algorithm>
#include <functional>
#include <iomanip>      // std::setw

#include "MarchMadness.h"
#include "Game.h"
#include "Team.h"
#include "../Eigen_Folder/Eigen/Core"
#include "../Eigen_Folder/Eigen/Dense"

    /**
     * Main constructer for MarchMadness Class
     * @param teamFileName the name of the file containing information about teams
     * @param gameFileName the name of the file containing information about games
     */
    MarchMadness::MarchMadness(std::string teamFileName, std::string gameFileName) {
        //Start Timer
        std::chrono::steady_clock sc;
        auto start = sc.now();

        //Reads in the data
        std::vector<Team> teamCollection = readInTeams(teamFileName);
        readInGames(gameFileName,&teamCollection);

        //Creates the main Matrix and Vector
        const size_t size =  teamCollection.size();
        Eigen::MatrixXf m = Eigen::MatrixXf::Zero(size,size);
        Eigen::VectorXf b = Eigen::VectorXf::Zero(size);

        //Construct the Matrix
        ConstructMatrix( &m, &b, size, teamCollection);

        //Solves the system of linear equations
        Eigen::VectorXf x = m.lu().solve(b);

        //Sort Solution and display solution
        std::vector<std::pair<int, long double>> s = sortSolution( x, size, teamCollection);

        //End Timer
        auto end = sc.now();

        //Prints the Matrix into an output file
        display( &m, &b, &s, size, &teamCollection);

        //Print execution time
        auto time_span = static_cast<std::chrono::duration<double>>(end - start);
        std::cout << "\nOperation took: " << time_span.count() << " seconds";
    }

    /**
     * This method is responsible for constructing the main matrix. Each Row and corresponding column represents a team.
     * The bottom row of the matrix is set to all 1's so that the solution is unique
     * @param m The Matrix
     * @param b The Vector
     * @param size The number of teams
     * @param teamCollection the collection of teams
     */
    void MarchMadness::ConstructMatrix(Eigen::MatrixXf *m, Eigen::VectorXf *b, const size_t size, std::vector<Team> teamCollection) {
        //Constructs the Matrix
        for (int i = 0; i < size; i++) {
            Team team = teamCollection.at(i);
            std::vector<Game> gameCollection = team.gameCollection;
            int total = 0;
            int score = 0;

            for (Game g: gameCollection) {

                total++;
                int team1 = g.getTeam1();
                int team2 = g.getTeam2();
                int score1 = g.getScore1();
                int score2 = g.getScore2();

                if (team1 == team.getID())
                    score += score1 - score2;
                else
                    score += score2 - score1;

                m->row(team1 - 1).col(team2 - 1) << -1;
                m->row(team2 - 1).col(team1 - 1) << -1;
            }
            m->row(team.getID() - 1).col(team.getID() - 1) << total;
            b->row(team.getID() - 1) << score;
        }

        //Sets the final row to all 1s = 0
        for (int j = 0; j < size; j++) {
            m->row(size-1).col(j) << 1;
        }
        b->row(size-1) << 0;
    }

    /**
     * This method is used to sort the solution to the system of linear equations. Then, this solution is
     * printed out, showing the teams in decreasing order, where the first team is the team most likely to win.
     * @param x The Vector
     * @param size The number of teams
     * @param teamCollection the collection of teams
     */
    std::vector<std::pair<int, long double>> MarchMadness::sortSolution(Eigen::VectorXf x, const size_t size, std::vector<Team> teamCollection) {

        std::vector<std::pair<int, long double>> solution;

        //Pairs ech value with the corresponding team name so that when we sort they stay together
        for (int j = 0; j < size; j++) {
            solution.push_back(std::pair<int, long double>(j,x(j)));
        }

        // Creating a new comparator to compare the vector pairs
        typedef std::function<bool(std::pair<int, long double>, std::pair<int, long double>)> Comparator;
        Comparator compFunctor =
                [](std::pair<int, long double> elem1 ,std::pair<int, long double> elem2)
                {
                    return elem1.second > elem2.second;
                };

        // Sorts the solution vector and puts it into a new set
        std::set<std::pair<int, long double>, Comparator> sorted_Solution(
                solution.begin(), solution.end(), compFunctor);

        std::vector<std::pair<int, long double>> s;

        //Add sorted Items to a vector and return it
        for (std::pair<int, long double> element : sorted_Solution) {
            s.push_back(std::pair<int, long double>(element));
        }

        return s;
    }

    /**
     * Responsible for iterating through a document containing all team names
     * along with an ID
     * @param teamFileName
     */
    std::vector<Team> MarchMadness::readInTeams(std::string teamFileName) {

        std::string team, index;
        std::ifstream in2(teamFileName);
        std::vector<Team> teamCollection;

        while( getline(in2,index, ',') )
        {
            long id = std::stoi(index);
            getline(in2,team,'\n');

            teamCollection.push_back(Team(id,team));
        }

        return teamCollection;
    }

    /**
     * Responsible for iterating through a document containing information about
     * all of the different games that were played. This document containds a gameID, date,
     * team1, score1, field1, team2, score2, and field2
     * @param gameFileName
     */
    void MarchMadness::readInGames(std::string gameFileName, std::vector<Team> *teamCollection) {

        std::string index,date,temp_team1,temp_field1,temp_score1,temp_team2,temp_field2,temp_score2;

        std::ifstream in1(gameFileName);

        while( getline(in1,index, ',') )
        {
            long id = std::stoi(index);
            getline(in1,date,',');
            getline(in1,temp_team1,',');
            long team1 = std::stoi(temp_team1);
            getline(in1,temp_field1,',');
            long field1 = std::stoi(temp_field1);
            getline(in1,temp_score1,',');
            long score1 = std::stoi(temp_score1);
            getline(in1,temp_team2,',');
            long team2 = std::stoi(temp_team2);
            getline(in1,temp_field2,',');
            long field2 = std::stoi(temp_field2);
            getline(in1,temp_score2,'\n');
            long score2 = std::stoi(temp_score2);

            Game game = Game(date,team1,field1,score1,team2,field2,score2);
            Team &temp = teamCollection->at(team1-1);
            Team &temp2 = teamCollection->at(team2-1);
            temp.addGame(game);
            temp2.addGame(game);
        }
    }

    /**
     * This method is responsible for displaying the Matrix
     */
    void MarchMadness::display(Eigen::MatrixXf *m, Eigen::VectorXf *b, std::vector<std::pair<int, long double>> *s, const size_t size, std::vector<Team> *teamCollection) {
        for (int i = 0; i < size-1; i++) {
            std::cout << m->block(i,0,1,size);
            std::cout << std::setw(3) << " = " << b->row(i) << "\n";
        }

        for (int i = 0; i < size; i++) {
            std::cout << " " << m->block(size-1,i,1,1) << " ";
        }
        std::cout << "= " << b->row(size-1) << "\n";

        std::cout << "\nSOLUTION:\n";
        // display the items in sorted order of values
        for (std::pair<int, long double> element : *s) {
            std::cout << std::setw(15) << teamCollection->at(element.first).getTeamName() << " :: " << std::setw(10)<< element.second << std::endl;
        }
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

        getline(in1,index, '\n');

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

        getline(in2,index, '\n');

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
        teamFileName = "../"+teamFileName +".txt";
        std::cout << "Please input the name of the game file:" << "\n";
        std::cin >> gameFileName;
        gameFileName = "../"+gameFileName +".txt";
        MarchMadness m = MarchMadness(teamFileName,gameFileName);
    }
