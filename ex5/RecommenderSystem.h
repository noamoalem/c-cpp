// Created by Noa Moalem on 17.6.2020.
#ifndef EX2_RECOMMENDERSYSTEM_H
#define EX2_RECOMMENDERSYSTEM_H

#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
#include <queue>
#define FILE_ERROR "Unable to open file "
#define USER_NOT_EXIST "USER NOT FOUND"
#define SMALL_NUM -2
#define ERROR -1
#define SUCCES 0
#define NOT_RANKED 0
#define ZERO 0
#define NA "NA"

using std::string;
using std::vector;
using std::unordered_map;
using std::priority_queue;

/**
 * This class represent Recommender movies System
 */
class RecommenderSystem
{
private:
    /**
    * include each user ranks for the movies.
    */
    unordered_map<string, vector<double>> _rateForMovies;
    /**
    * include each movie characteristic.
    */
    unordered_map<string, vector<double>> _moviesInfo;
    /**
     * include the movies names as they appear in the ranks file.
    */
    vector<string> _moviesOrder;
    int _numOfCharacteristics;

    /**
     * This method find the norm of a given vector.
     * @param vector given vector.
     * @return norm of a given vector.
     */
    static double _norm(const vector<double> &vector);

    /**
     * This method find the angel between two given vectors.
     * @param u vector.
     * @param v vector.
     * @return The angel between the given vectors.
     */
    static double _angel(const vector<double> &u, const vector<double> &v);

    /**
     * This method multiply a given vector with given scalar.
     * @param vector given vector.
     * @param c given scalar.
     * @return The vector after the multiplication.
     */
    static vector<double> _scalarMultiplication(const vector<double> &vector, double c);

    /**
     * This method read given file stream of the users ranks for the movies.
     * @param infile file stream to read the data from.
     */
    void _readUserRanksFile(std::ifstream &infile);

    /**
     * This method read given file stream of the movies characteristic.
     * @param infile file stream to read the data from.
     */
    void _readMoviesAttributesFile(std::ifstream &infile);
    /**
     * This method read a line of user ranks.
     * @param line line to read.
     */
    void _readRanksLine(string& line);

    /**
     * This method find the preference vector of a given user.
     * @param userName given user.
     * @return The preference vector of the user.
     */
    vector<double> _findPrefVector(const string &userName) const;

public:
    /**
     * This method read the data from given files.
     * @param moviesAttributesFilePath The movies characteristic file.
     * @param userRanksFilePath The users ranks file.
     * @return -1 if the read fail, 0 otherwise.
     */
    int loadData(string moviesAttributesFilePath, string userRanksFilePath);

    /**
     * This method fined the recommend movie to a given user based on the movies he already watched.
     * @param userName Given user.
     * @return The recommend movie.
     */
    std::string recommendByContent(const string &userName) const;

    /**
     * This method find the score of a given movie for specific user, based on k movies he
     * already watched.
     * @param movieName Movie to find the score for.
     * @param userName Given user.
     * @param k Number of movies to based on.
     * @return The score for the given movie, -1 if the given movie/user name dose not exist.
     */
    double predictMovieScoreForUser(const string &movieName, const string &userName, int k) const;

    /**
     * This method find the recommend movie for the given user, based on common filter.
     * @param userName Given user.
     * @param k  Number of movies to based on.
     * @return The recommend movie.
     */
    string recommendByCF(const string userName, int k) const;
};
#endif //EX2_RECOMMENDERSYSTEM_H
