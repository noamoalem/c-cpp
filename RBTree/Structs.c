#include <stdio.h>
#include  <stdlib.h>
#include "Structs.h"
#include <math.h>
#include <string.h>

#define LESS (-1)
#define EQUAL (0)
#define GREATER (1)
#define FAIL (0)
#define SUCCESS (1)

/**
 * This function find the shorter vector len.
 * @param a first vector.
 * @param b second vector.
 * @return the len of the shorter vector.
 */
int findShortVectotLen(const void *a, const void *b)
{
    Vector one = *(Vector *) a;
    Vector two = *(Vector *) b;
    int len = 0;
    if (one.len > two.len)
    {
        len = two.len;
    }
    else
    {
        len = one.len;
    }
    return len;
}

/**
 * CompFunc for Vectors, compares element by element, the vector that has the first larger
 * element is considered larger. If vectors are of different lengths and identify for the length
 * of the shorter vector, the shorter vector is considered smaller.
 * @param a - first vector
 * @param b - second vector
 * @return equal to 0 iff a == b. lower than 0 if a < b. Greater than 0 iff b < a.
 */
int vectorCompare1By1(const void *a, const void *b)
{
    Vector one = *(Vector *) a;
    Vector two = *(Vector *) b;
    int len = findShortVectotLen(a, b);

    for (int i = 0; i < len; ++i)
    {
        if (one.vector[i] > two.vector[i])
        {
            return GREATER;
        }
        if (one.vector[i] < two.vector[i])
        {
            return LESS;
        }
    }
    if (one.len == two.len)
    {
        return EQUAL;
    }
    else if (one.len < two.len)
    {
        return LESS;
    }
    return GREATER;
}

/**
 * This finds the norm of vector.
 * @param vector given vector.
 * @return the vector norm.
 */
double norm(Vector vector)
{
    double sqrSum = 0;
    if (vector.vector == NULL)
    {
        return LESS;
    }
    for (int i = 0; i < vector.len; ++i)
    {

        sqrSum += pow((double) vector.vector[i], 2);
    }
    return sqrt(sqrSum);
}

/**
 * copy pVector to pMaxVector if : 1. The norm of pVector is greater then the norm of pMaxVector.
 * 								   2. pMaxVector->vector == NULL.
 * @param pVector pointer to Vector
 * @param pMaxVector pointer to Vector
 * @return 1 on success, 0 on failure (if pVector == NULL: failure).
 */
int copyIfNormIsLarger(const void *pVector, void *pMaxVector)
{
    if (pVector == NULL || pMaxVector == NULL)
    {
        return FAIL;
    }
    Vector *vector = (Vector *) pVector;
    Vector *maxVector = (Vector *) pMaxVector;

    if (maxVector->vector == NULL || norm(*vector) > norm(*maxVector))
    {
        maxVector->vector = realloc(maxVector->vector, (vector->len) * sizeof(double));
        maxVector->len = vector->len;
        if (maxVector->vector == NULL)
        {
            return FAIL;
        }
        for (int i = 0; i < vector->len; ++i)
        {
            maxVector->vector[i] = vector->vector[i];
        }
        return SUCCESS;
    }
    return SUCCESS;
}

/**
* @param tree a pointer to a tree of Vectors
* @return pointer to a *copy* of the vector that has the largest norm (L2 Norm).
*/
Vector *findMaxNormVectorInTree(RBTree *tree)
{
    if (tree == NULL)
    {
        return NULL;
    }
    Vector *toReturn = (Vector *) malloc(sizeof(Vector));
    if (toReturn != NULL)
    {
        toReturn->vector = NULL;
        toReturn->len = 0;
    }
    forEachRBTree(tree, copyIfNormIsLarger, toReturn);
    return toReturn;
}

/**
 * FreeFunc for vectors
 */
void freeVector(void *pVector)
{
    if (pVector != NULL)
    {
        free((*(Vector *) pVector).vector);
        (*(Vector *) pVector).vector = NULL;
        free((Vector *) pVector);
        pVector = NULL;
    }
}

/**
 * CompFunc for strings (assumes strings end with "\0")
 * @param a - char* pointer
 * @param b - char* pointer
 * @return equal to 0 iff a == b. lower than 0 if a < b. Greater than 0 iff b < a. (lexicographic
 * order)
 */
int stringCompare(const void *a, const void *b)
{
    return strcmp((char *) a, (char *) b);
}

/**
 * ForEach function that concatenates the given word and \n to pConcatenated. pConcatenated is
 * already allocated with enough space.
 * @param word - char* to add to pConcatenated
 * @param pConcatenated - char*
 * @return 0 on failure, other on success
 */
int concatenate(const void *word, void *pConcatenated)
{
    if (word == NULL || pConcatenated == NULL)
    {
        return FAIL;
    }
    const char *toAdd = (const char *) "\n";
    strcat((char *) pConcatenated, (const char *) word);
    strcat((char *) pConcatenated, toAdd);
    return SUCCESS;
}

/**
 * FreeFunc for strings
 */
void freeString(void *s)
{
    if (s != NULL)
    {
        free(s);
        s = NULL;
    }
}