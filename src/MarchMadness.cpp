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
#include <iostream>
#include <stdio.h>
#include <locale>
#include <ctime>

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
        try {
            //Start Timer
            std::chrono::steady_clock sc;
            auto start = sc.now();

            //Reads in the data
            std::vector<Team> teamCollection = readInTeams(teamFileName);
            std::vector<tm> dates = readInGames(gameFileName, &teamCollection);

            //Creates the main Matrix and Vector
            const size_t size = teamCollection.size();
            Eigen::MatrixXf m = Eigen::MatrixXf::Zero(size, size);
            Eigen::VectorXf b = Eigen::VectorXf::Zero(size);

            //Construct the Matrix
            ConstructMatrix(&m, &b, size, teamCollection, dates);

            //Solves the system of linear equations
            Eigen::VectorXf x = m.lu().solve(b);

            //Sort Solution and display solution
            std::vector<std::pair<int, long double>> s = sortSolution(x, size, teamCollection);

            //End Timer
            auto end = sc.now();

            //Prints the Matrix into an output file
            display(&m, &b, &s, size, &teamCollection, teamFileName);

            //Print execution time
            auto time_span = static_cast<std::chrono::duration<double>>(end - start);
            std::cout << "\nOperation took: " << time_span.count() << " seconds";
        }
        catch(std::exception e){
            std::cout<< "EXCEPTION THROWN:\n" << e.what();
        }
    }

    /**
     * This method is responsible for constructing the main matrix. Each Row and corresponding column represents a team.
     * The bottom row of the matrix is set to all 1's so that the solution is unique
     * @param m The Matrix
     * @param b The Vector
     * @param size The number of teams
     * @param teamCollection the collection of teams
     */
    void MarchMadness::ConstructMatrix(Eigen::MatrixXf *m, Eigen::VectorXf *b, const size_t size, std::vector<Team> teamCollection, std::vector<tm> dates) {
        try {
            //Constructs the Matrix
            for (int i = 0; i < size; i++) {
                Team team = teamCollection.at(i);
                std::vector<Game> gameCollection = team.gameCollection;
                int total = 0;

                for (Game g: gameCollection) {

                    double score = 0;

                    total++;
                    int team1 = g.getTeam1();
                    int team2 = g.getTeam2();
                    int score1 = g.getScore1();
                    int score2 = g.getScore2();
                    tm date;
                    sscanf(g.getDate().c_str(), "%4d%2d%2d", &date.tm_year, &date.tm_mon, &date.tm_mday, 0, 0, 0, 0);

                    if (team1 == team.getID())
                        score += score1 - score2;
                    else
                        score += score2 - score1;

                    m->row(team1 - 1).col(team2 - 1) << -1;
                    m->row(team2 - 1).col(team1 - 1) << -1;

                    float temp = b->row(team.getID() - 1).value();

                    if (difftime(mktime(&date), mktime(&(dates.at(1)))) < 0) {
                        score = score * 0.7;
                    } else if (difftime(mktime(&date), mktime(&(dates.at(2)))) < 0) {
                        score = score * 0.8;
                    } else if (difftime(mktime(&date), mktime(&(dates.at(3)))) < 0) {
                        score = score * 0.9;
                    }

                    b->row(team.getID() - 1) << temp + score;

                }
                m->row(team.getID() - 1).col(team.getID() - 1) << total;
            }

            //Sets the final row to all 1s = 0
            for (int j = 0; j < size; j++) {
                m->row(size - 1).col(j) << 1;
            }
            b->row(size - 1) << 0;
        }
        catch(std::exception e){
            std::cout<< "EXCEPTION THROWN:\n" << e.what();
        }
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

        while (getline(in2, index, ',')) {
            long id = std::stoi(index);
            getline(in2, team, '\n');

            teamCollection.push_back(Team(id, team));
        }

        return teamCollection;
    }

    /**
     * Responsible for iterating through a document containing information about
     * all of the different games that were played. This document containds a gameID, date,
     * team1, score1, field1, team2, score2, and field2
     * @param gameFileName
     */
    std::vector<tm> MarchMadness::readInGames(std::string gameFileName, std::vector<Team> *teamCollection) {

        std::vector<tm> dates;

        std::string index,date,temp_team1,temp_field1,temp_score1,temp_team2,temp_field2,temp_score2;

        std::ifstream in1(gameFileName);

        while( getline(in1,index, ',') )
        {
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

            tm tm1;

            sscanf(date.c_str(),"%4d%2d%2d",&tm1.tm_year,&tm1.tm_mon,&tm1.tm_mday,
                   0,0,0,0);

            dates.push_back(tm1);
        }

        return configureDates(dates);
    }

    /**
     * Modifies the day, month and year parameters to reflect adding a certain number of days.
     * This is used to construct the different date frames.
     * @param month the month
     * @param day the day
     * @param year the year
     * @param num_of_days the number of days being added to the date
     * @return true if the date was changed successfully
     */
    bool MarchMadness::add_num_of_days(int* month, int* day, int* year, int num_of_days)
    {
        struct tm expire_time = {};
        expire_time.tm_year = *year - 1900;
        expire_time.tm_mon = *month - 1;
        expire_time.tm_mday = *day;

        expire_time.tm_mday += num_of_days;

        if (-1 == mktime(&expire_time))
        {
            return false;
        }

        *day = expire_time.tm_mday;
        *month = expire_time.tm_mon + 1;
        *year = expire_time.tm_year + 1900;
        return true;
    }

    /**
     * This method takes in the dates and creates the different date frames. It finds the
     * earliest and latest date, and then constructs 4 date ranges.
     * @return a vector containing the partitioned dates
     */
    std::vector<tm> MarchMadness::configureDates(std::vector<tm> dates){
        tm temp1 = dates.front();
        tm temp5 = dates.back();

        std::time_t time1 = std::mktime(&temp1);
        std::time_t time2 = std::mktime(&temp5);

        const int seconds_per_day = 60*60*24;
        int difference = (time2 - time1) / seconds_per_day /4;

        int day = temp1.tm_mday;
        int month = temp1.tm_mon;
        int year = temp1.tm_year;

        std::vector<tm> finalDates;
        finalDates.push_back(temp1);

        for(int i = 0; i< 4 - 1; i++) {

            add_num_of_days(&month, &day, &year, difference);

            struct tm temp;
            temp.tm_year = year;
            temp.tm_mon = month;
            temp.tm_mday = day;

            finalDates.push_back(temp);

        }
        finalDates.push_back(temp5);

        return finalDates;
    }


    /**
     * This method is responsible for displaying the Matrix
     */
    void MarchMadness::display(Eigen::MatrixXf *m, Eigen::VectorXf *b, std::vector<std::pair<int, long double>> *s, const size_t size, std::vector<Team> *teamCollection, std::string file) {
        /*for (int i = 0; i < size-1; i++) {
            std::cout << m->block(i,0,1,size);
            std::cout << std::setw(3) << " = " << b->row(i) << "\n";
        }

        for (int i = 0; i < size; i++) {
            std::cout << " " << m->block(size-1,i,1,1) << " ";
        }
        std::cout << "= " << b->row(size-1) << "\n";*/

        if(file == ("../NationalBasketballAssociationTeams.txt")) {
            std::string team;
            std::ifstream in2("../NBA_Results.txt");
            std::vector<std::string> results;

            while (getline(in2, team)) {
                results.push_back(team);
            }

            std::cout << "\n" << std::setw(17) << "SOLUTION :" << std::setw(17) << " | " << std::setw(20) << "RESULTS:" << std::endl;
            std::cout << std::setfill('~') << std::setw(33) << "|" << std::setw(26) << "\n";
            // display the items in sorted order of values
            int counter = 0;
            std::cout << std::setfill(' ');
            for (std::pair<int, long double> element : *s) {
                std::cout << std::setw(15) << teamCollection->at(element.first).getTeamName() << " :: " << std::setw(10)
                          << element.second << std::setw(5) << " | " << std::setw(20) << results.at(counter++)
                          << std::endl;
            }
        }
        else{
            std::cout << "\n" << std::setw(17) << "SOLUTION :" << std::endl;
            std::cout << std::setfill('~') << std::setw(35) << "\n";
            // display the items in sorted order of values
            std::cout << std::setfill(' ');
            for (std::pair<int, long double> element : *s) {
                std::cout << std::setw(15) << teamCollection->at(element.first).getTeamName() << " :: " << std::setw(10)
                          << element.second << std::endl;
            }
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
        MarchMadness(teamFileName,gameFileName);
    }
