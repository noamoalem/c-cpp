#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SpreaderDetectorParams.h"

#define USAGE_MSG "Usage: ./SpreaderDetectorBackend <Path to People.in> <Path to Meetings.in>\n"
#define INPUT_FILE_ERROR "Error in input files.\n"
#define OUTPUT_FILE_ERROR "Error in output file.\n"
#define PERSON_LINE_REGEX "%[^' '] %[^' '] %s"
#define MEETING_LINE_REGEX "%[^' '] %[^' '] %[^' '] %s"
#define PARS_ONE_ID "%s"
#define ID_LEN 10
#define BASE 10
#define DOUBLE 2
#define LEN_OF_LINE 1024
#define FIRST_INFECTOR 1
#define FIRST_INDEX 0
#define SMALLER -1
#define EQUAL 0
#define BIGGER 1
#define NOT_FOUND -1
#define CORON_DEF 0.f

/**
 * Person struct, include the fields name, id, age, corona factor.
 */
typedef struct Person
{
    char name[LEN_OF_LINE];
    long id;
    float age;
    float crnaFactor;
} Person;

/**
 * Comparator function to use while sort person array by increasing id number.
 * @param one first person.
 * @param two second person.
 * @return -1 if the id number of one is smaller then two id, 1 if the id number of one is bigger
 * then two id number, 0 otherwise.
 */
int compareById(const void *one, const void *two)
{
    const Person personOne = *(const Person *) one;
    const Person personTwo = *(const Person *) two;
    if (personOne.id < personTwo.id)
    {
        return SMALLER;
    }
    else if (personOne.id > personTwo.id)
    {
        return BIGGER;
    }
    return EQUAL;
}

/**
 * Comparator function to use while sort person array by decreasing chance to get corona.
 * @param one first person.
 * @param two second person.
 * @return -1 if the corona factor of one is bigger then two id, 1 if the corona factor of one is
 * smaller then two id, 0 otherwise.
 */
int compareByCrnaFactor(const void *one, const void *two)
{
    const Person personOne = *(const Person *) one;
    const Person personTwo = *(const Person *) two;
    if (personOne.crnaFactor > personTwo.crnaFactor)
    {
        return SMALLER;
    }
    else if (personOne.crnaFactor < personTwo.crnaFactor)
    {
        return BIGGER;
    }
    return EQUAL;
}

/**
 * This function finds the index of a person in a sorted given array by his id number. Implement
 * binary search.
 * @param personArray given array.
 * @param first the first index of the array.
 * @param last the last index of the array.
 * @param neededPerson given id to find this person in the array.
 * @return the index of a person in the given array.
 */
int findPersonIndex(const Person *personArray, const int first, const int last, long neededPerson)
{
    if (last >= first)
    {
        int mid = first + (last - first) / 2;
        if (personArray[mid].id == neededPerson)
        {
            return mid;
        }
        if (personArray[mid].id < neededPerson)
        {
            return findPersonIndex(personArray, mid + 1, last, neededPerson);
        }
        return findPersonIndex(personArray, first, mid - 1, neededPerson);
    }
    return NOT_FOUND;
}

/**
 * This function calculate the chance to get corona, considering a meeting between two person.
 * @param distance The distance between the people.
 * @param time The duration of the meeting.
 * @return The result.
 */
float findCrnaFctor(const float distance, const float time)
{
    float up = time * MIN_DISTANCE;
    float down = distance * MAX_TIME;
    return up / down;
}

/**
 * This function close the allocated memory.
 */
void freeAllMemory(FILE *personFile, FILE *meetingsFile, Person *personArray)
{
    fclose(personFile);
    fclose(meetingsFile);
    free(personArray);
}

/**
 * This function increases the size of thr person array when needed.
 * @param personArray All person array.
 * @param size the current size of the person array.
 * @return 1 if the resize fail, 0 otherwise.
 */
int resizePersonArray(Person **personArray, int *size)
{
    Person *temp = (Person *) realloc(*personArray, (*size) * DOUBLE * sizeof(Person));
    if (temp == NULL)
    {
        return EXIT_FAILURE;
    }
    else
    {
        (*size) *= 2;
        *personArray = temp;
        return EXIT_SUCCESS;
    }
}

/**
 * This function get data, creat person object and add it to the persons array.
 * @param id given id.
 * @param name given name.
 * @param age given age.
 * @param personArray array of all persons.
 * @param numOfPersons number of person in the person array.
 * @return
 */
int creatPerson(const char id[], const char name[], const char age[], Person **personArray,
                int *numOfPersonsP, int *size)
{
    Person person;
    float ageF = strtof(age, NULL);
    person.age = ageF;
    long idF = strtol(id, NULL, BASE);
    person.id = idF;
    strcpy(person.name, name);
    person.crnaFactor = CORON_DEF;
    if (*size == *numOfPersonsP)
    {
        int result = resizePersonArray(personArray, size);
        if (result == EXIT_FAILURE)
        {
            return EXIT_FAILURE;
        }
    }
    (*personArray)[*numOfPersonsP] = person;
    (*numOfPersonsP) += 1;
    return EXIT_SUCCESS;
}

/**
 * This function reads the people file, and creat array of Person objects.
 * @param personFile given people file.
 * @param numOfPersonsP pointer to the number of person in the person array..
 * @return A pointer to a sort by id array, null if something fail during the process.
 */
Person *readPersonFile(FILE *personFile, int *numOfPersonsP)
{
    char line[LEN_OF_LINE];
    Person *personArray = NULL;
    personArray = (Person *) malloc(BASE * sizeof(Person));
    if (personArray == NULL)
    {
        return NULL;
    }
    int size = BASE;
    while (fgets(line, LEN_OF_LINE, personFile) != NULL && !feof(personFile))
    {
        char id[LEN_OF_LINE], name[LEN_OF_LINE], age[LEN_OF_LINE];
        sscanf(line, PERSON_LINE_REGEX, name, id, age);
        if (creatPerson(id, name, age, &personArray, numOfPersonsP, &size) == EXIT_FAILURE)
        {
            free(personArray);
            return NULL;
        }
    }
    qsort(personArray, *numOfPersonsP, sizeof(Person), compareById);
    return personArray;
}

/**
 * This function reads the first line of a meeting file.
 * @param personArray all person array.
 * @param numOfPersons number of person in the person array.
 * @param line a given line to pars.
 * @param currInfector place to fill in the infector from the first line.
 */
void findFirstInfector(Person *personArray, const int numOfPersons, const char *line, Person
                       **currInfector)
{
    char infectorIdArray[ID_LEN];
    sscanf(line, PARS_ONE_ID, infectorIdArray);
    long infectorId = strtol(infectorIdArray, NULL, BASE);
    *currInfector = &personArray[findPersonIndex(personArray, 0, numOfPersons - 1,
                                                 infectorId)];
    (*currInfector)->crnaFactor = FIRST_INFECTOR;
}

/**
 * This function reads a line (except the first line) of a meeting file.
 * @param personArray all person array.
 * @param numOfPersons number of person in the person array.
 * @param line line to pars.
 * @param currInfector place to fill in the infector from the line.
 * @param currInfected place to fill in the infected from the line.
 * @param distance place to fill in the distance.
 * @param time place to fill in the time.
 */
void getInfoMeetingLine(Person *personArray, const int numOfPersons, const char *line, Person
                        **currInfector, Person **currInfected, float *distance, float *time)
{
    char distanceAsArray[LEN_OF_LINE], timeAsArray[LEN_OF_LINE], infectorIdAsArray[ID_LEN],
    infectedIdAsArray[ID_LEN];
    sscanf(line, MEETING_LINE_REGEX, infectorIdAsArray, infectedIdAsArray,
           distanceAsArray, timeAsArray);
    *distance = strtof(distanceAsArray, NULL);
    *time = strtof(timeAsArray, NULL);
    long infectorId = strtol(infectorIdAsArray, NULL, BASE);
    long infectedId = strtol(infectedIdAsArray, NULL, BASE);
    if (infectorId != (*currInfector)->id)
    {
        *currInfector = &personArray[findPersonIndex(personArray, FIRST_INDEX, numOfPersons - 1,
                                                     infectorId)];
    }
    *currInfected = &personArray[findPersonIndex(personArray, FIRST_INDEX, numOfPersons - 1,
                                                 infectedId)];
}

/**
 * This function read the meeting file, and calculate the corona factor of each person according
 * to the information in the file.
 * @param personArray given person array.
 * @param meetingsFile given meeting file to read.
 * @param numOfPersons number of person in the person array.
 */
void readMeetingFile(Person *personArray, FILE *meetingsFile, const int numOfPersons)
{
    float defaultValDis = 0;
    float defaultValTime = 0;
    int numOfLine = 0;
    char line[LEN_OF_LINE];
    Person *currInfector = NULL;
    Person *currInfected = NULL;
    while (fgets(line, LEN_OF_LINE, meetingsFile) != NULL && !feof(meetingsFile))
    {
        if (numOfLine == FIRST_INDEX)
        {
            findFirstInfector(personArray, numOfPersons, line, &currInfector);
        }
        else
        {
            float *distance = &defaultValDis;
            float *time = &defaultValTime;
            getInfoMeetingLine(personArray, numOfPersons, line, &currInfector, &currInfected,
                               distance, time);
            (*currInfected).crnaFactor = ((*currInfector).crnaFactor) * findCrnaFctor(*distance,
                                                                                      *time);
        }
        numOfLine++;
    }
}

/**
 * This function creat the output file, sorting the people by their corona factor.
 * @param personArray given person array.
 * @param numOfPersons number of person in the person array.
 * @return 0 if it succeed creating the result file, 1 otherwise.
 */
int creatOutFile(Person *personArray, const int numOfPersons)
{
    qsort(personArray, numOfPersons, sizeof(Person), compareByCrnaFactor);
    FILE *file;
    file = fopen(OUTPUT_FILE, "w");
    if (file == NULL)
    {
        fprintf(stderr, OUTPUT_FILE_ERROR);
        return EXIT_FAILURE;
    }
    int i = 0;
    char *toPrint;
    while (i < numOfPersons)
    {
        if (personArray[i].crnaFactor >= MEDICAL_SUPERVISION_THRESHOLD)
        {
            toPrint = MEDICAL_SUPERVISION_THRESHOLD_MSG;
        }
        else if (personArray[i].crnaFactor >= REGULAR_QUARANTINE_THRESHOLD)
        {
            toPrint = REGULAR_QUARANTINE_MSG;
        }
        else
        {
            toPrint = CLEAN_MSG;
        }
        fprintf(file, toPrint, personArray[i].name, personArray[i].id);
        ++i;
    }
    fclose(file);
    return EXIT_SUCCESS;
}

/**
 * This function run the spreader detector backend.
 * @param argv the files to preform the analyses on.
 * @return 0 if it succeed finishing run the program, 1 otherwise.
 */
int runProgram(char *const *argv)
{
    FILE *personFile, *meetingsFile;
    int numOfPersons = 0;
    if ((personFile = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, INPUT_FILE_ERROR);
        return EXIT_FAILURE;
    }
    else if ((meetingsFile = fopen(argv[2], "r")) == NULL)
    {
        fclose(personFile);
        fprintf(stderr, INPUT_FILE_ERROR);
        return EXIT_FAILURE;
    }
    Person *personArray = readPersonFile(personFile, &numOfPersons);
    if (personArray == NULL)
    {
        fprintf(stderr, STANDARD_LIB_ERR_MSG);
        freeAllMemory(personFile, meetingsFile, personArray);
        return EXIT_FAILURE;

    }
    readMeetingFile(personArray, meetingsFile, numOfPersons);
    if (creatOutFile(personArray, numOfPersons)) //if creat out  file fail.
    {
        freeAllMemory(personFile, meetingsFile, personArray);
    }
    freeAllMemory(personFile, meetingsFile, personArray);
    return EXIT_SUCCESS;
}

/**
 * The main function.
 * @param argc number of given arguments.
 * @param argv given arguments array.
 * @return 0 if it succeed finishing run the program, 1 otherwise.
 */
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "%s", USAGE_MSG);
        return EXIT_FAILURE;
    }
    return runProgram(argv);
}
