#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define ARGUMENTS_NUM 6
#define FAIL 1
#define OK 0
#define INVALID 999
#define G_ASCII 71
#define C_ASCII 67
#define A_ASCII 65
#define Z_ASCII 90
#define SMALL_A_ASCII 97
#define SMALL_Z_ASCII 122
#define SPACE_ASCII 32
#define SEP_ASCII 45
#define MIN_AGE 18
#define MAX_AGE 120
#define MAX_GRADE 100
#define LEN_OF_LINE 61
#define LEN_OF_PARAM 43
#define LEN_OF_ID 10
#define MAX_STUDENTS_NUM 5500
#define LEN_HALF_STUDENTS 2750
#define G 'G'
#define A 'A'
#define C 'C'
#define SMALL_C 'c'
#define MISSING_ARGUMENTS "ERROR: some arguments are missing "
#define ID_INVALID "ERROR: id number invalid "
#define NAME_INVALID "ERROR: name can only contain alphabetic characters, whitespaces or '-'"
#define GRADE_INVALID "ERROR: grade number invalid "
#define AGE_INVALID "ERROR: age invalid "
#define COUNTRY_INVALID "ERROR: country invalid "
#define CITY_INVALID "ERROR: city invalid "
#define LINE_NUM "in line "
#define END_INPUT "q\n"
#define BEST_STUDENT "best student info is: "
#define SEPERATOR ','
#define INPUT_MSG "Enter student info. To exit press q, then enter"
#define USAGE_MSG "USAGE: find best student, merge sort acording to grade, quick sort alphabetical"

/**
 * student struct.
 */
typedef struct Student
{
    long id;
    char name[LEN_OF_PARAM];
    int grade;
    int age;
    char city[LEN_OF_PARAM];
    char country[LEN_OF_PARAM];
    double accomplishments;
} Student;

Student gStudentsArray[MAX_STUDENTS_NUM];
Student *pStudentsArray = gStudentsArray;
int gStudentNumber = 0;
int gLineNumber = 0;

/**
 * This function check that id number is valid.
 * @param idArray given id number.
 * @param lineNum the number of the current line.
 * @return the id number if it valid, 1 otherwise.
 */
long checkId(char idArray[], int lineNum)
{
    long id;
    char *leftovers;
    id = strtol(idArray, &leftovers, 10);

    if (strlen(leftovers) != OK)
    {
        printf("%s\n%s%i\n", ID_INVALID, LINE_NUM, lineNum);
        return FAIL;
    }
    if ((long)pow(LEN_OF_ID, 9) <=  id &&  id < (long) pow(LEN_OF_ID, LEN_OF_ID))
    {
        return id;
    }
    printf("%s\n%s%i\n", ID_INVALID, LINE_NUM, lineNum);
    return FAIL;
}

/**
 * This function check that the name is valid.
 * @param name given name.
 * @param lineNum the number of the current line.
 * @return 0 if it valid, 1 otherwise.
 */
int checkName(const char name[], int lineNum)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!(((int) name[i] >= A_ASCII && (int) name[i] <= Z_ASCII) ||
              ((int) name[i] >= SMALL_A_ASCII && (int) name[i] <= SMALL_Z_ASCII)
              || (int) name[i] == SPACE_ASCII || (int) name[i] == SEP_ASCII))
        {
            printf("%s\n%s%i\n", NAME_INVALID, LINE_NUM, lineNum);
            return FAIL;
        }
    }
    return OK;
}

/**
 * This function check that the grade and age are valid.
 * @param num given grade/age.
 * @param ageOrGrade what to check.
 * @param lineNum the number of the current line.
 * @return the number if it valid, 1 otherwise.
 */
int checkGradeAndAge(char *num, char ageOrGrade, int lineNum)
{
    long number;
    char *leftovers;
    number = strtol(num, &leftovers, 10);
    if (strlen(leftovers) != OK)
    {
        printf("%s\n%s%d\n", GRADE_INVALID, LINE_NUM, lineNum);
        return INVALID;
    }
    if ((MAX_GRADE < number || number < OK) && (int) ageOrGrade == G_ASCII)
    {
        printf("%s\n%s%d\n", GRADE_INVALID, LINE_NUM, lineNum);
        return INVALID;
    }
    if ((MAX_AGE < number || number < MIN_AGE) && (int) ageOrGrade == A_ASCII)
    {
        printf("%s\n%s%d\n", AGE_INVALID, LINE_NUM, lineNum);
        return INVALID;
    }
    return (int) number;
}

/**
 * This function check that the city and country are valid.
 * @param name given city/country.
 * @param countyOrCity what to check.
 * @param lineNum
 * @return 0 if it valid, 1 otherwise.
 */
int checkCountryAndCity(const char name[], char countyOrCity, int lineNum)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!(((int) name[i] >= A_ASCII && (int) name[i] <= Z_ASCII) ||
              ((int) name[i] >= SMALL_A_ASCII && (int) name[i] <= SMALL_Z_ASCII)
              || (int) name[i] == SEP_ASCII))
        {
            if ((int) countyOrCity == C_ASCII)
            {
                printf("%s\n%s%d\n", COUNTRY_INVALID, LINE_NUM, lineNum);
                return FAIL;
            }
            else
            {
                printf("%s\n%s%d\n", CITY_INVALID, LINE_NUM, lineNum);
                return FAIL;
            }
        }
    }
    return OK;
}

/**
 * This function check one line of input.
 * @param input given input from the user.
 * @return 0 if all the checks were good, 1 otherwise.
 */
int checkLine(char input[LEN_OF_LINE])
{
    char id[LEN_OF_PARAM];
    char name[LEN_OF_PARAM];
    char grade[LEN_OF_PARAM];
    char age[LEN_OF_PARAM];
    char city[LEN_OF_PARAM];
    char country[LEN_OF_PARAM];
    int arg = sscanf(input, "%[^,],%[^,],%[^,],%[^,],%[^,],%s", id, name, grade, age,
            country,
                     city);
    Student student;
    if (arg != ARGUMENTS_NUM)
    {
        printf("%s\n%s%d\n", MISSING_ARGUMENTS, LINE_NUM, gLineNumber);
        return FAIL;
    }

    if (checkId(id, gLineNumber) != FAIL)
    {
        student.id = checkId(id, gLineNumber);
        if (checkName(name, gLineNumber) != FAIL)
        {
            strcpy(student.name, name);
        }
        else
        {
            return FAIL;
        }
    }
    else
    {
        return FAIL;
    }

    if (checkGradeAndAge(grade, G, gLineNumber) != INVALID &&
        checkGradeAndAge(age, A, gLineNumber) != INVALID)
    {
        student.grade = checkGradeAndAge(grade, G, gLineNumber);
        student.age = checkGradeAndAge(age, A, gLineNumber);
        if (checkCountryAndCity(country, C, gLineNumber) != FAIL &&
            checkCountryAndCity(city, SMALL_C, gLineNumber) != FAIL)
        {
            strcpy(student.country, country);
            strcpy(student.city, city);
        }
        else
        {
            return FAIL;
        }
    }
    else
    {
        return FAIL;
    }
    student.accomplishments = (double) student.grade / student.age;
    *pStudentsArray = student;
    gStudentNumber++;
    pStudentsArray++;
    return OK;
}

/**
 * This function finds the best student from the a students array.
 * @param students all students
 * @param studentNum number of students in the given array.
 */
void findBestStudent(Student *students, int studentNum)
{
    if (gStudentNumber > OK)
    {

        Student bestStudent = students[0];
        for (int i = 0; i <= studentNum; i++)
        {
            if (students[i].accomplishments > bestStudent.accomplishments)
            {
                bestStudent = students[i];
            }
        }
        printf("%s%ld%c%s%c%i%c%i%c%s%c%s\n", BEST_STUDENT, bestStudent.id, SEPERATOR,
               bestStudent.name, SEPERATOR, bestStudent.grade, SEPERATOR, bestStudent.age,
               SEPERATOR, bestStudent.country, SEPERATOR, bestStudent.city);
    }
}
/**
 * Helper for the mergeSort. create two sub array to merge.
 * @param students all students.
 * @param leftArray array to fill.
 * @param rightArray array to fill.
 * @param sizeLeft the size of the array to fill.
 * @param sizeRight the size of the array to fill.
 * @param left start.
 * @param mid middle.
 */
void creatSubArrays(Student students[], Student leftArray[], Student rightArray[], int sizeLeft,
                    int sizeRight, int left, int mid)
{
    int i = 0;
    int j = 0;
    while (i<sizeLeft)
    {
        leftArray[i] = students[(left + i)];
        i++;
    }
    while (j<sizeRight)
    {
        rightArray[j] = students[(mid + j + 1)];
        j++;
    }
}

/**
 * Helper for the mergeSort, merge two arrays.
 * @param students given student array.
 * @param left index start to merge from
 * @param right index stop merge from
 * @param mid middle point fo the array to merge.
 */
void merge(Student students[], int left, int right, int mid)
{
    int sizeLeftArray = mid - left + 1;
    int sizeRightArray = right - mid;
    Student leftArray[LEN_HALF_STUDENTS];
    Student rightArray[LEN_HALF_STUDENTS];
    creatSubArrays(students, leftArray, rightArray, sizeLeftArray, sizeRightArray, left, mid);
    int i = 0, j = 0, k = left;
    while (i < sizeLeftArray && j < sizeRightArray)
    {
        if (leftArray[i].grade <= rightArray[j].grade)
        {
            students[k] = leftArray[i];
            i++;
        }
        else
        {
            students[k] = rightArray[j];
            j++;
        }
        k++;
    }
    while (i < sizeLeftArray)
    {
        students[k] = leftArray[i];
        i++; k++;
    }
    while (j < sizeRightArray)
    {
        students[k] = rightArray[j];
        j++; k++;
    }
}

/**
 * This function preform the merge sort.
 * @param students array to sort.
 * @param left first index.
 * @param right last index.
 */
void mergeSort(Student students[], int left, int right)
{
    int mid;
    if (left < right)
    {
        mid = left + (right - left) / 2;
        mergeSort(students, left, mid);
        mergeSort(students, mid + 1, right);

        merge(students, left, right, mid);
    }

}

/**
 * helper to the quickSort. preform swap between two students.
 * @param a student.
 * @param b student.
 */
void swap(Student *a, Student *b)
{
    Student temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * This function preform the quick sort.
 * @param students students array to sort.
 * @param start first index.
 * @param end last index.
 */
void quickSort(Student students[], int start, int end)
{
    if (start < end)
    {
        int pivot;
        Student pivotObj = students[end];
        int i = start - 1;
        for (int j = start; j <= end - 1; j++)
        {
            if (strcmp(students[j].name, pivotObj.name) < 0)
            {
                i++;
                swap(&students[i], &students[j]);
            }
        }
        pivot = i + 1;
        swap(&students[end], &students[pivot]);
        quickSort(students, start, pivot - 1);
        quickSort(students, pivot + 1, end);
    }
}

/**
 * This function get all the user input, using checkLine() to check valid.
 */
void getAllStudents()
{
    char input[LEN_OF_LINE];
    printf("%s\n", INPUT_MSG);
    fgets(input, LEN_OF_LINE, stdin);
    while (strcmp(input, END_INPUT) != OK)
    {
        checkLine(input);
        gLineNumber++;
        printf("%s\n", INPUT_MSG);
        fgets(input, LEN_OF_LINE, stdin);
    }
}

/**
 * This function prints the final students array.
 */
void printResults()
{
    for (int i = 0; i < gStudentNumber; i++)
    {
        printf("%ld%c%s%c%i%c%i%c%s%c%s\n", gStudentsArray[i].id, SEPERATOR,
               gStudentsArray[i].name, SEPERATOR, gStudentsArray[i].grade, SEPERATOR,
               gStudentsArray[i].age, SEPERATOR, gStudentsArray[i].country, SEPERATOR,
               gStudentsArray[i].city);
    }
}

/**
 * main driver of the program.
 * @param argc number of arguments.
 * @param argv array of the arguments.
 * @return 0 if all went good, 1 otherwise.
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("%s\n", USAGE_MSG);
        return FAIL;
    }
    if (strcmp(argv[1], "best") == OK)
    {
        getAllStudents();
        findBestStudent(gStudentsArray, gStudentNumber);
        return OK;
    }
    if (strcmp(argv[1], "merge") == OK)
    {
        {
            getAllStudents();
            mergeSort(gStudentsArray, 0, gStudentNumber - 1);
            printResults();
            return OK;
        }
    }
    if (strcmp(argv[1], "quick") == OK)
    {
        getAllStudents();
        quickSort(gStudentsArray, 0, gStudentNumber - 1);
        printResults();
        return OK;
    }
    return FAIL;
}