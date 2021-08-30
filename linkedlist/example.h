#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _Matrix Matrix;

/* type definitions for VTable */
/* destructor */
typedef bool (*fptrDestroy)(Matrix *);

/* Matrix manipulators */
typedef bool (*fptrRowSwap)(Matrix *, int, int);
typedef bool (*fptrScalarMultiply)(Matrix *, double);
typedef bool (*fptrScalarRowMultiply)(Matrix *, int, double);
typedef bool (*fptrAdd)(Matrix *, Matrix *);
typedef bool (*fptrSubtract)(Matrix *, Matrix *);

/* Matrix derived values */
typedef double (*fptrDeterminant)(Matrix *);
typedef bool (*fptrZeroVector)(Matrix *);

/* Matrix-derived constructions */
typedef Matrix *(*fptrInvert)(Matrix *);
typedef Matrix *(*fptrTranspose)(Matrix *);
typedef Matrix *(*fptrMultiply)(Matrix *, Matrix *);
typedef Matrix *(*fptrHadamard)(Matrix *, Matrix *);

/* Accessors and Mutators */
typedef double (*fptrGet)(Matrix *, int, int);
typedef bool (*fptrSet)(Matrix *, int, int, double);

/* Misc */
typedef bool (*fptrPrint)(Matrix *);
typedef bool (*fptrPrintSize)(Matrix *);
typedef bool (*fptrEquals)(Matrix *, Matrix *);

typedef struct _Matrix
{
    void *super;
    int rows;
    int cols;
    double *data;

    fptrDestroy destroy;
    fptrRowSwap row_swap;
    fptrScalarMultiply scalar_multiply;
    fptrScalarRowMultiply row_scalar_multiply;
    fptrAdd add;
    fptrSubtract subtract;
    fptrDeterminant determinant;
    fptrZeroVector zero_vector;
    fptrInvert invert;
    fptrTranspose transpose;
    fptrMultiply multiply;
    fptrHadamard hadamard;
    fptrGet get;
    fptrSet set;
    fptrPrint print;
    fptrPrintSize size;
    fptrEquals equals;

} Matrix;

/* Constructors and destructors */
Matrix *Matrix__constructor(int r, int c);
Matrix *Matrix__identity(int length);
Matrix *Matrix__clone(Matrix *m);
Matrix *Matrix__fromArr(int r, int c, double *vals, int arr_size);
bool Matrix__destroy(Matrix *m);

/* Matrix manipulators */
bool Matrix__row_swap(Matrix *m, int a, int b);
bool Matrix__scalar_multiply(Matrix *m, double f);
bool Matrix__row_scalar_multiply(Matrix *m, int row, double factor);
bool Matrix__add(Matrix *m1, Matrix *m2);
bool Matrix__subtract(Matrix *m1, Matrix *m2);

/* Matrix-derived values */
double Matrix__determinant(Matrix *m);
bool Matrix__zero_vector(Matrix *m);

/* Matrix-derived constructions */
Matrix *Matrix__invert(Matrix *m);
Matrix *Matrix__transpose(Matrix *m);
Matrix *Matrix__multiply(Matrix *m1, Matrix *m2);
Matrix *Matrix__hadamard(Matrix *m1, Matrix *m2);

/* Mutators and accessors */
double Matrix__get(Matrix *m, int r, int c);
bool Matrix__set(Matrix *m, int r, int c, double val);

/* Misc */
bool Matrix__print(Matrix *m);
bool Matrix__print_size(Matrix *m);
bool Matrix__equals(Matrix *m1, Matrix *m2);

//Planned features for the future:
// int reduce(Matrix *m, int a, int b, float factor);
// Matrix *gram_schmidt(Matrix *);
// double *projection(Matrix *, double *, int length);
// Matrix *orthonormal_basis(Matrix *);
// Matrix *solved_aug_matrix(Matrix *);
// double *eigenvalues(Matrix *m);

// static double vector_multiply(double *col, double *row, int length);
// static void vector_addition(double *v1, double *v2, int length);
// static void scalar_vector_multiplication(double factor, double *vector, int length);
// static void vector_subtraction(double *v1, double *v2, int length);

#endif

#include "matrix.h"
#include "special_math.h"

/* Constructors and destructors */
Matrix *Matrix__constructor(int r, int c)
{
    //memory allocation
    Matrix *mObj = NULL;
    mObj = (Matrix *)malloc(sizeof(Matrix));
    if (mObj == NULL)
    {
        return NULL;
    }

    //pointer to itself because Matrix has no parent class
    mObj->super = mObj;
    mObj->rows = r;
    mObj->cols = c;
    mObj->data = malloc(sizeof(double) * r * c);

    if (mObj->data == NULL)
    {
        return NULL;
    }

    //Initializing matrix with 0.0 entries
    for (int i = 0; i < (mObj->rows) * (mObj->cols); i++)
    {
        (mObj->data)[i] = 0.0;
    }

    //initializing interface for access to functions
    mObj->destroy = Matrix__destroy;
    mObj->row_swap = Matrix__row_swap;
    mObj->scalar_multiply = Matrix__scalar_multiply;
    mObj->row_scalar_multiply = Matrix__row_scalar_multiply;
    mObj->add = Matrix__add;
    mObj->subtract = Matrix__subtract;
    mObj->determinant = Matrix__determinant;
    mObj->zero_vector = Matrix__zero_vector;
    mObj->invert = Matrix__invert;
    mObj->transpose = Matrix__transpose;
    mObj->multiply = Matrix__multiply;
    mObj->hadamard = Matrix__hadamard;
    mObj->get = Matrix__get;
    mObj->set = Matrix__set;
    mObj->print = Matrix__print;
    mObj->size = Matrix__print_size;
    mObj->equals = Matrix__equals;

    return mObj;
}

Matrix *Matrix__identity(int length)
{
    Matrix *result = Matrix__constructor(length, length);
    for (int i = 0; i < length; i++)
    {
        result->set(result, i, i, 1.0);
    }
    return result;
}

Matrix *Matrix__clone(Matrix *m)
{
    Matrix *copy = Matrix__constructor(m->rows, m->cols);
    for (int i = 0; i < m->rows * m->cols; i++)
    {
        (copy->data)[i] = (m->data)[i];
    }
    return copy;
}

Matrix *Matrix__fromArr(int r, int c, double *vals, int arr_size)
{
    if (arr_size != r * c)
    {
        printf("Cannot form matrix from array because the provided array does not match specified dimensions.\n");
        return NULL;
    }

    Matrix *ret = Matrix__constructor(r, c);

    for (int i = 0; i < arr_size; i++)
    {
        (ret->data)[i] = vals[i];
    }

    return ret;
}

bool Matrix__destroy(Matrix *m)
{
    free(m->data);
    free(m);
    return true;
}

/* Matrix manipulators */
bool Matrix__row_swap(Matrix *m, int a, int b)
{
    if (a < 0 || b < 0 || a > m->rows || b > m->rows)
    {
        printf("Error (row_swap): rows are out of bounds.\n");
        printf("m:");
        m->size(m);
        return false;
    }

    for (int i = 0; i < m->cols; i++)
    {
        double tmp1 = m->get(m, a, i);
        double tmp2 = m->get(m, b, i);
        m->set(m, a, i, tmp2);
        m->set(m, b, i, tmp1);
    }
    return true;
}
bool Matrix__scalar_multiply(Matrix *m, double factor)
{
    for (int r = 0; r < m->rows; r++)
    {
        for (int c = 0; c < m->cols; c++)
        {
            double x = (m->get(m, r, c)) * factor;
            m->set(m, r, c, x);
        }
    }
    return true;
}
bool Matrix__row_scalar_multiply(Matrix *m, int row, double factor)
{
    for (int c = 0; c < (m->cols); c++)
    {
        double x = (m->get(m, row, c)) * factor;
        m->set(m, row, c, x);
    }
    return true;
}
/*
    m1 is modified such that every element of m1 becomes the sum
    of every element of m1 with the corresponding element of m2.
*/
bool Matrix__add(Matrix *m1, Matrix *m2)
{
    if (m1->rows != m2->rows || m1->cols != m2->cols)
    {
        printf("Error (add): Matrices m1 and m2 have mismatched dimensions.\n");
        printf("m1:");
        m1->size(m1);
        printf("m2:");
        m2->size(m2);
        return false;
    }

    for (int r = 0; r < m1->rows; r++)
    {
        for (int c = 0; c < m1->cols; c++)
        {
            double x = (m1->get(m1, r, c)) + (m2->get(m2, r, c));
            m1->set(m1, r, c, x);
        }
    }
    return true;
}
/*
    m1 is modified such that every element of m1 becomes the difference
    of every element of m1 with the corresponding element of m2.
*/
bool Matrix__subtract(Matrix *m1, Matrix *m2)
{
    if (m1->rows != m2->rows || m1->cols != m2->cols)
    {
        printf("Error (subtract): Matrices m1 and m2 have mismatched dimensions.\n");
        printf("m1:");
        m1->size(m1);
        printf("m2:");
        m2->size(m2);
        return false;
    }

    for (int r = 0; r < m1->rows; r++)
    {
        for (int c = 0; c < m1->cols; c++)
        {
            double x = (m1->get(m1, r, c)) - (m2->get(m2, r, c));
            m1->set(m1, r, c, x);
        }
    }
    return true;
}

/* Matrix-derived values */
double Matrix__determinant(Matrix *m)
{
    //TODO
    printf("WARNING: Matrix__determinant is unimplemented.\n");
    return 0;
}
bool Matrix__zero_vector(Matrix *m)
{
    for (int i = 0; i < m->cols; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < m->rows; j++)
        {
            sum += m->get(m, j, i);
        }
        if (double_equals(sum, 0.0))
        {
            return true;
        }
    }
    return false;
}

/* Matrix-derived constructions */
Matrix *Matrix__invert(Matrix *m)
{
    //TODO
    printf("WARNING: Matrix__invert is unimplemented.\n");
    return NULL;
}

Matrix *Matrix__transpose(Matrix *m)
{
    Matrix *result = Matrix__constructor(m->cols, m->rows);
    for (int r = 0; r < (m->rows); r++)
    {
        for (int c = 0; c < (m->cols); c++)
        {
            result->set(result, c, r, m->get(m, r, c));
        }
    }
    return result;
}

Matrix *Matrix__multiply(Matrix *m1, Matrix *m2)
{
    if (m1->cols != m2->rows)
    {
        printf("Error (multiply): Matrices m1 and m2 have mismatched dimensions.\n");
        printf("m1:");
        m1->size(m1);
        printf("m2:");
        m2->size(m2);
        return NULL;
    }

    Matrix *result = Matrix__constructor(m1->rows, m2->cols);

    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->cols; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < (m1->cols); k++)
            {
                sum += (m1->get(m1, i, k)) * (m2->get(m2, k, j));
            }
            result->set(result, i, j, sum);
        }
    }
    return result;
}

Matrix *Matrix__hadamard(Matrix *m1, Matrix *m2)
{
    if (m1->rows != m2->rows || m1->cols != m2->cols)
    {
        printf("Error (hadamard): Matrices m1 and m2 have mismatched dimensions.\n");
        printf("m1:");
        m1->size(m1);
        printf("m2:");
        m2->size(m2);
        return NULL;
    }

    for (int r = 0; r < m1->rows; r++)
    {
        for (int c = 0; c < m1->cols; c++)
        {
            double x = (m1->get(m1, r, c)) * (m2->get(m2, r, c));
            m1->set(m1, r, c, x);
        }
    }
    return m1;
}

/* Mutators and accessors */
double Matrix__get(Matrix *m, int r, int c)
{
    if (r < 0 || c < 0 || r > m->rows || c > m->cols)
    {
        printf("Error (get): row or column is out of bounds.\n");
        printf("m:");
        m->size(m);
        return 0.0;
    }
    return m->data[r * (m->cols) + c];
}

bool Matrix__set(Matrix *m, int r, int c, double val)
{
    if (r < 0 || c < 0 || r > m->rows || c > m->cols)
    {
        printf("Error (set): row or column is out of bounds.\n");
        printf("m:");
        m->size(m);
        return false;
    }
    m->data[r * (m->cols) + c] = val;
    return true;
}

/* Misc */
bool Matrix__print(Matrix *m)
{
    printf("[");
    for (int i = 0; i < m->rows; i++)
    {
        if (i > 0)
        {
            printf(" [");
        }
        else
        {
            printf("[");
        }

        for (int j = 0; j < m->cols; j++)
        {
            printf(" %.4lf ", m->get(m, i, j));
        }

        if (i == (m->rows) - 1)
        {
            printf("]");
        }
        else
        {
            printf("]\n");
        }
    }
    printf("]\n");
    return true;
}

bool Matrix__print_size(Matrix *m)
{
    printf("(%d, %d)\n", m->rows, m->cols);
    return true;
}

bool Matrix__equals(Matrix *m1, Matrix *m2)
{
    if (m1->rows != m2->rows || m1->cols != m2->cols)
    {
        return false;
    }
    for (int i = 0; i < m1->rows * m2->cols; i++)
    {
        double a = (m1->data)[i];
        double b = (m2->data)[i];
        if (!double_equals(a, b))
        {
            return false;
        }
    }
    return true;
}

#include "../matrix.h"

void test_matrix()
{
    printf("------------------------------\n");
    printf("-         Test matrix        -\n");
    printf("------------------------------\n");
    Matrix *m1 = Matrix__constructor(5, 3);
    printf("m1:\n");
    m1->print(m1);
    m1->size(m1);

    double arr[10] = {1.0, 2.0, 3.0, 4.0, 5.0,
                      6.0, 7.0, 8.0, 9.0, 10.0};

    Matrix *m2 = Matrix__fromArr(2, 5, arr, 10);
    printf("m2:\n");
    m2->print(m2);
    m2->size(m2);

    printf("row_swap(m2, 0, 1) for m2:\n");
    m2->row_swap(m2, 0, 1);
    printf("m2:\n");
    m2->print(m2);
    m2->size(m2);

    printf("scalar_multiply(m2, 0.5) for m2:\n");
    m2->scalar_multiply(m2, 0.5);
    printf("m2:\n");
    m2->print(m2);
    m2->size(m2);

    printf("row_scalar_multiply(m2, 1, 3) for m2:\n");
    m2->row_scalar_multiply(m2, 1, 3);
    printf("m2:\n");
    m2->print(m2);
    m2->size(m2);

    printf("putting values into m1:\n");
    m1->set(m1, 0, 0, 2);
    m1->set(m1, 0, 1, 4);
    m1->set(m1, 0, 2, 2);
    m1->set(m1, 1, 0, 4);
    m1->set(m1, 1, 1, 2);
    m1->set(m1, 1, 2, 4);
    m1->set(m1, 2, 0, 2);
    m1->set(m1, 2, 1, 4);
    m1->set(m1, 2, 2, 2);
    m1->set(m1, 3, 0, 4);
    m1->set(m1, 3, 1, 2);
    m1->set(m1, 3, 2, 4);
    m1->set(m1, 4, 0, 2);
    m1->set(m1, 4, 1, 4);
    m1->set(m1, 4, 2, 2);
    printf("m1:\n");
    m1->print(m1);
    m1->size(m1);

    Matrix *m3 = m2->multiply(m2, m1);
    printf("m3 = m2 multiply m1:\n");
    m3->print(m3);
    m3->size(m3);

    double arr2[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Matrix *m4 = Matrix__fromArr(2, 3, arr2, 6);
    m4->scalar_multiply(m4, 0.1);
    printf("m4:\n");
    m4->print(m4);
    m4->size(m4);

    m3->hadamard(m3, m4);
    printf("hadamard(m3, m4) into m3:\n");
    m3->print(m3);
    m3->size(m3);

    m3->add(m3, m4);
    printf("add(m3, m4) into m3:\n");
    m3->print(m3);
    m3->size(m3);

    Matrix *m5 = m3->transpose(m3);
    printf("transpose(m3) into m5:\n");
    m5->print(m5);
    m5->size(m5);

    m1->set(m1, 0, 2, 0);
    m1->set(m1, 1, 2, 0);
    m1->set(m1, 2, 2, 0);
    m1->set(m1, 3, 2, 0);
    m1->set(m1, 4, 2, 0);
    printf("zero_vector(m1) (Expected true): %s\n", m1->zero_vector(m1) ? "true" : "false");

    double arr3[6] = {5.7, 25.6, 13, 36.5, 17.1, 38.4};
    Matrix *m6 = Matrix__fromArr(3, 2, arr3, 6);

    printf("equals(m5, m6) (Expected: true) : %s\n", m5->equals(m5, m6) ? "true" : "false");
    printf("equals(m5, m3) (Expected: false) : %s\n", m5->equals(m5, m3) ? "true" : "false");

    m1->destroy(m1);
    m2->destroy(m2);
    m3->destroy(m3);
    m4->destroy(m4);
    m5->destroy(m5);
    m6->destroy(m6);
}

int main()
{
    printf("-----------------------------------------\n");
    printf("-  Testing all components of Alcobra... -\n");
    printf("-----------------------------------------\n");
    test_matrix();
    printf("-----------------------------------------\n");
    printf("-              END OF TESTS             -\n");
    printf("-----------------------------------------\n");
}