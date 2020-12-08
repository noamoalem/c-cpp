//
// Created by Noa Moalem on 17.6.2020.
//

#include "RecommenderSystem.h"

/**
 * This method read a line of user ranks.
 * @param line line to read.
 */
void RecommenderSystem::_readRanksLine(string &line)
{
    int wordCounter = 0;
    string currName;
    string str;
    std::istringstream my_stream(line);
    while (my_stream >> str)
    {
        string rate;
        if (wordCounter == ZERO)
        {
            currName = str;
        }
        else
        {
            if (str == NA)
            {
                _rateForMovies[currName].emplace_back(NOT_RANKED);
            }
            else
            {
                double num;
                std::istringstream(str) >> num;
                _rateForMovies[currName].emplace_back(num);
            }
        }
        ++wordCounter;
    }
}

/**
 * This method read given file stream of the users ranks for the movies.
 * @param infile file stream to read the data from.
 */
void RecommenderSystem::_readUserRanksFile(std::ifstream &infile)
{
    string line;
    int lineCounter = 0;
    while (std::getline(infile, line))
    {
        std::istringstream my_stream(line); //read first line
        if (lineCounter == ZERO)
        {
            string currMovie;
            while (my_stream >> currMovie)
            {
                _moviesOrder.emplace_back(currMovie);
            }
        }
        else //read other lines
        {
            _readRanksLine(line);
        }
        ++lineCounter;
    }
}

/**
 * This method read given file stream of the movies characteristic.
 * @param infile file stream to read the data from.
 */
void RecommenderSystem::_readMoviesAttributesFile(std::ifstream &infile)
{
    std::string line;
    int counter;
    while (std::getline(infile, line))
    {
        std::istringstream my_stream(line);
        counter = 0;
        string currMovieName;
        string str;
        vector<double> ranks;
        while (my_stream >> str)
        {
            if (counter == ZERO)
            {
                currMovieName = str;
            }
            else
            {
                double num;
                std::istringstream(str) >> num;
                ranks.emplace_back(num);
            }
            ++counter;
        }
        _moviesInfo[currMovieName] = ranks;
    }
    _numOfCharacteristics = counter - 1;
}

/**
 * This method find the norm of a given vector.
 * @param vector given vector.
 * @return norm of a given vector.
 */
double RecommenderSystem::_norm(const vector<double> &vector)
{
    double sum = 0;
    for (double num:vector)
    {
        sum += pow(num, 2);
    }
    return sqrt(sum);
}

/**
 * This method find the angel between two given vectors.
 * @param u vector.
 * @param v vector.
 * @return The angel between the given vectors.
 */
double RecommenderSystem::_angel(const vector<double> &u, const vector<double> &v)
{
    double up = 0;
    double down = 0;
    for (int i = 0; i < (int) u.size(); ++i)
    {
        up += u[i] * v[i];
    }
    down += _norm(u) * _norm(v);
    return (up / down);
}

/**
 * This method multiply a given vector with given scalar.
 * @param vector given vector.
 * @param c given scalar.
 * @return The vector after the multiplication.
 */
vector<double> RecommenderSystem::_scalarMultiplication(const vector<double> &vector, double c)
{
    std::vector<double> toReturn;
    toReturn.reserve(vector.size());
    for (int i = 0; i < (int) vector.size(); ++i)
    {
        toReturn[i] = c * vector[i];
    }
    return toReturn;
}

/**
 * This method read the data from given files.
 * @param moviesAttributesFilePath The movies characteristic file.
 * @param userRanksFilePath The users ranks file.
 * @return -1 if the read fail, 0 otherwise.
 */
int RecommenderSystem::loadData(string moviesAttributesFilePath, string userRanksFilePath)
{
    std::ifstream inFile(moviesAttributesFilePath);
    std::ifstream inFileSec(userRanksFilePath);
    if (!inFile.is_open())
    {
        std::cerr << FILE_ERROR << moviesAttributesFilePath << std::endl;
        return ERROR;
    }
    if (!inFileSec.is_open())
    {
        std::cerr << FILE_ERROR << userRanksFilePath << std::endl;
        return ERROR;
    }
    _readUserRanksFile(inFileSec);
    _readMoviesAttributesFile(inFile);
    return SUCCES;
}

/**
 * This method fined the recommend movie to a given user based on the movies he already watched.
 * @param userName Given user.
 * @return The recommend movie.
 */
std::string RecommenderSystem::recommendByContent(const std::string &userName) const
{
    if (!_rateForMovies.count(userName))
    {
        return USER_NOT_EXIST;
    }
    vector<double> userRank = _rateForMovies.at(userName);
    vector<double> preferenceVector = _findPrefVector(userName);
    string recommendMovie;
    double recommendMovieScore = SMALL_NUM;
    for (int i = 0; i < (int) userRank.size(); ++i)
    {
        if (userRank[i] == NOT_RANKED)
        {
            double currScore = _angel(_moviesInfo.at(_moviesOrder[i]), preferenceVector);
            if (currScore > recommendMovieScore)
            {
                recommendMovieScore = currScore;
                recommendMovie = _moviesOrder[i];
            }
        }
    }
    return recommendMovie;
}

/**
 * This method find the preference vector of a given user.
 * @param userName given user.
 * @return The preference vector of the user.
 */
vector<double> RecommenderSystem::_findPrefVector(const string &userName) const
{
    vector<double> userRank = _rateForMovies.at(userName);
    double rankedMoviesNum = 0;
    double sum = 0;
    for (int i = 0; i < (int) userRank.size(); ++i)
    {
        if (userRank[i] != NOT_RANKED)
        {
            sum += userRank[i];
            rankedMoviesNum++;
        }
    }
    double average = sum / rankedMoviesNum;
    for (int i = 0; i < (int) userRank.size(); ++i)
    {
        if (userRank[i] != NOT_RANKED)
        {
            userRank[i] -= average;
        }
    }
    vector<double> preferenceVector(_numOfCharacteristics, 0);
    for (int i = 0; i < (int) userRank.size(); ++i)
    {
        if (userRank[i] != NOT_RANKED)
        {
            vector<double> currVecToAdd = _scalarMultiplication(_moviesInfo.at(_moviesOrder[i]), userRank[i]);
            for (int j = 0; j < (int) preferenceVector.size(); ++j)
            {
                preferenceVector[j] += currVecToAdd[j];
            }
        }
    }
    return preferenceVector;
}


/**
 * This method find the score of a given movie for specific user, based on k movies he
 * already watched.
 * @param movieName Movie to find the score for.
 * @param userName Given user.
 * @param k Number of movies to based on.
 * @return The score for the given movie, -1 if the given movie/user name dose not exist.
 */
double
RecommenderSystem::predictMovieScoreForUser(const string &movieName, const string &userName,
                                            int k) const
{
    if (!_moviesInfo.count(movieName) || !_rateForMovies.count(userName))
    {
        return ERROR;
    }
    std::priority_queue<std::pair<double, string>> rankedMovies;
    unordered_map<string, double> neededRanks;
    vector<double> userRank = _rateForMovies.at(userName);
    for (int i = 0; i < (int) userRank.size(); ++i)
    {
        if (userRank[i] != NOT_RANKED)
        {
            double similarity = _angel(_moviesInfo.at(_moviesOrder[i]), _moviesInfo.at(movieName));
            rankedMovies.push({similarity, _moviesOrder[i]});
            neededRanks[_moviesOrder[i]] = userRank[i];
        }
    }
    double toReturn = 0;
    double sum = 0;
    for (int i = 0; i < k; ++i)
    {
        std::pair<double, string> currPair = rankedMovies.top();
        toReturn += currPair.first * neededRanks[currPair.second];
        sum += currPair.first;
        rankedMovies.pop();
    }
    double final = (toReturn) / (sum);
    return final;
}

/**
 * This method find the recommend movie for the given user, based on common filter.
 * @param userName Given user.
 * @param k  Number of movies to based on.
 * @return The recommend movie.
 */
string RecommenderSystem::recommendByCF(const string userName, int k) const
{
    if (!_rateForMovies.count(userName))
    {
        return USER_NOT_EXIST;
    }
    double similarity = SMALL_NUM;
    string toRet;
    vector<double> userRank = _rateForMovies.at(userName);
    for (int i = 0; i < (int) userRank.size(); ++i)
    {
        if (userRank[i] == NOT_RANKED)
        {
            double tempSimilarity = predictMovieScoreForUser(_moviesOrder[i], userName, k);
            if (tempSimilarity > similarity)
            {
                similarity = tempSimilarity;
                toRet = _moviesOrder[i];
            }
        }
    }
    return toRet;
}