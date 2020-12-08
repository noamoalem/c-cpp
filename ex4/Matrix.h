// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H
#define ERR_MSG_IVALID_SIZE "Error: Matrix cols and rows must be bigger then 0"
#define ERR_MSG_DIFFRENT_MATRIX_SIZE "Error: The matrix size doesnt fit"
#define ERR_MSG_INDEX_OUT_OF_RANGE "Error: Index out of range"
#define ERR_MSG_FILE "Error: Problem with the file"
#define ZERO 0
#define FAIL 1
#define DEFAULT_SIZE 1

#include <iostream>


/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims
{
    int rows, cols;
} MatrixDims;

// Insert Matrix class here...
/**
 * The matrix class.
 */
class Matrix
{
private:
    int rows, cols;
    float *matrix;

public:
    /**
     * The constructor, initialize new matrix in size rows*cols, with zeros.
     * @param rows The matrix rows number.
     * @param cols The matrix cols number.
     */
    Matrix(int rows, int cols);

    /**
     * The default constructor. initialize new matrix in size 1*1, with zero.
     */
    Matrix();

    /**
     * The copy constructor, initialize new matrix with the given matrix values.
     * @param m given matrix.
     */
    Matrix(const Matrix &m);

    /**
     * The destructor. delete the matrix array.
     */
    ~Matrix();

    /**
     * getter for the matrix rows number
     * @return The number of rows.
     */
    int getRows() const;

    /**
     * getter for the matrix cols number
     * @return The number of columns.
     */
    int getCols() const;

    /**
     * Transforms a matrix into a column vector.
     * @return reference for the matrix that vectorize preform on.
     */
    Matrix &vectorize();

    /**
     * Prints matrix elements as a matrix.
     */
    void plainPrint() const;

    /**
     * Assignment of one matrix (rhs) to another.
     * @param rhs matrix to copy the value from.
     * @return the matrix after assignment.
     */
    Matrix &operator=(const Matrix &rhs);

    /**
     * multiplication of two matrix.
     * @param rhs the second matrix.
     * @return the result of the multiplication.
     */
    Matrix operator*(const Matrix &rhs) const;

    /**
     * Scalar multiplication on the right.
     * @param c Scalar.
     * @return The matrix by reference.
     */
    Matrix operator*(float c) const;

    /**
     * Scalar multiplication on the left.
     * @param c Scalar.
     * @return The matrix by reference.
     */
    friend Matrix operator*(float c, const Matrix &rhs);

    /**
     * Matrix addition. (lhs + rhs)
     * @param lhs
     * @param rhs
     * @return the result of the addition.
     */
    Matrix operator+(const Matrix &rhs) const;

    /**
     * Matrix addition accumulation.
     * @param rhs the matrix to add.
     * @return the matrix after the addition of rhs.
     */
    Matrix &operator+=(const Matrix &rhs);

    /**
     * Return the i,j element in the matrix.
     * @param row the row of the wanted element.
     * @param col the column of the wanted element.
     * @return the i,j element in the matrix.
     */
    float operator()(int row, int col) const;

    /**
     * Return the i,j element in the matrix. allowed assigment.
     * @param row the row of the wanted element.
     * @param col the column of the wanted element.
     * @return the i,j element in the matrix.
     */
    float &operator()(int row, int col);

    /**
     * Return the i’th element of matrix that represent as a vector. allowed assigment.
     * @param index the wanted element.
     * @return Return the i’th element of matrix.
     */
    float &operator[](int index);

    /**
     * Return the i’th element of matrix that represent as a vector.
     * @param index the wanted element.
     * @return Return the i’th element of matrix.
     */
    float operator[](int index) const;

    /**
     * Fills matrix elements.
     * @param s given input stream.
     * @param rhs The matrix to fill.
     * @return The input stream.
     */
    friend std::istream &operator>>(std::istream &s, const Matrix &rhs);

    /**
     * Prints the number the matrix represent.
     * @param s given output stream.
     * @param rhs The matrix to print.
     * @return The output stream.
     */
    friend std::ostream &operator<<(std::ostream &s, const Matrix &rhs);

};

#endif //MATRIX_H