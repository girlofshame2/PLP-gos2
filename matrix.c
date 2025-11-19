#include "matrix.h"
#include <stdlib.h>
#include <errno.h> /* for ENOSYS */
#include <stdio.h>  /* enable print for debugging */

int matrix_allocate(matrix_t *m, int rows, int columns) {
    
    if (rows <= 0 || columns <= 0 || !m) {
        return -1;
    }

    m->rows = rows;
    m->columns = columns;

    /* row of pointers*/
    m->content = malloc(rows * sizeof(int*)); 
    if(m->content == NULL){
      return -1;
    }  
    for(int j=0;j <rows;j++){
        m->content[j] = malloc( columns * sizeof(int));
        if(m->content[j] == NULL){
            //if it doesn't work free all the previous allocations
            //freethe rows
            for(int i=0;i<j;i++){
                free(m->content[i]);

            }
            //free the pointer array
            free(m->content);
            return -1;
        }
    }
    return 0;
}
void matrix_free(matrix_t *m) {
    if(!m || m->content == NULL ){ /*make sure u did actually give it memory at some point, and there is actually
                                    content to be freed*/ 
        return;
    }
    for(int i=0;i< m->rows; i++){
        free(m->content[i]);
    }
    free(m->content);
    m->content = NULL;
    m->rows = 0;
    m->columns = 0;
}

void matrix_init_n(matrix_t *m, int n) {
   if ((m == NULL) || (m->content == NULL)){
    return;
   }
   for(int i=0;i<m->rows;i++){
        for(int j=0;j<m->columns;j++){
            m->content[i][j] = n;
        }
   }
   
}

void matrix_init_zeros(matrix_t *m) {
    if((m == NULL) || (m->content == NULL)){
        return;
    }
    for(int i=0;i<m->rows;i++){
        for(int j =0; j<m->columns; j++){
            m->content[i][j] = 0;
        }
    }
}

int matrix_init_identity(matrix_t *m){
    if((m == NULL) || (m->content == NULL)){
        return -1;
   }
   for(int i=0;i<m->rows;i++){
        for(int j=0;j<m->columns;j++){
            if(i==j){
                m->content[i][j] = 1;
            }
            else{
                m->content[i][j] = 0;
            }
        }
   }
    
    if((m == NULL) || (m->content == NULL)|| m->rows != m->columns){
        return -1;
   }
   for(int i=0;i<m->rows;i++){
        for(int j=0;j<m->columns;j++){
            if(i==j){
                m->content[i][j] = 1;
            }
            else{
                m->content[i][j] = 0;
            }
        }
   }
   return 0;
    
}
int matrix_init_rand(matrix_t *m, int val_min, int val_max) {
    //make sure pointer to matrix isn't null
    //or array of poiters is null
   if(m == NULL){
    return -1;
   }
   if(m->content == NULL){
    return -1;
   }
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            if(val_max - val_min + 1 <= 0){
               return -1;
            }
            m->content[i][j] = rand() % (val_max - val_min + 1) + val_min;
        }
    }
    return 0;
}

int matrix_equal(matrix_t *m1, matrix_t *m2) {
    if(!m1 || !m2 || !(m1->content) || !(m2->content)){
        return 0;
   }
   if((m1->rows != m2->rows) || (m1->columns != m2->columns)){
        return 0;
   }
    for(int i =0; i<m1->rows;i++){
        for(int j=0;j<m1->columns;j++){
            if(m1->content[i][j] != m2->content[i][j]){
                return 0;
            }
        }
    }
    return 1;
    if(!m1 || !m2 || !(m1->content) || !(m2->content)){
        return 0;
   }
   if((m1->rows != m2->rows) || (m1->columns != m2->columns)){
        return 0;
   }
    for(int i =0; i<m1->rows;i++){
        for(int j=0;j<m1->columns;j++){
            if(m1->content[i][j] != m2->content[i][j]){
                return 0;
            }
        }
    }
    return 1;
}

/* Sum 'm1' and 'm2' into result. matrix_sum should take care of allocating
 * result. Return 0 on success, something else on failure. */
int matrix_sum(matrix_t *m1, matrix_t *m2, matrix_t *result) {
    if(!m1 || !m2 || !m1->content || !m2->content || m1->rows !=m2->rows || m1->columns !=m2->columns){
        return -1;
    }

     if(matrix_allocate(result, m1->rows, m1->columns) != 0){
        return -1;
    }
    for(int i=0;i<m1->rows;i++){
        for(int j=0;j<m1->columns;j++){
            result->content[i][j] = m1->content[i][j] + m2->content[i][j];
        }
    }
    return 0;
}

/* Multiply the matrix 'm' by the scalar 'scalar' and places the result into
 * 'result'. Should take care of the allocation of 'result'. Return 0 on
 * success, something else on failure. */
int matrix_scalar_product(matrix_t *m, int scalar, matrix_t *result) {
    if(!m || !m->content){
        return -1;
    }

    if(matrix_allocate(result, m->rows, m->columns) != 0){
        return -1;
    }

    for(int i=0;i<m->rows;i++){
        for(int j=0; j<m->columns; j++){
            result->content[i][j] = (scalar)* (m->content[i][j]);
        }
    }
    return 0;
}

/* Transpose 'm' into 'result'. Should take care of the allocation of 'result'.
 * Return 0 on success, something else on failure. */
int matrix_transposition(matrix_t *m, matrix_t *result) {
   if(!m || !m->content){
        return -1;
    }
   
    if(matrix_allocate(result, m->columns, m->rows) != 0){
        return -1;
    }

    for(int i=0;i<m->rows;i++){
        for(int j=0; j<m->columns; j++){
            result->content[j][i] = (m->content[i][j]);
        }
    }
    return 0;
 
}

/* Multiply 'm1' by 'm2' and place the result in 'result'. Should take care of
 * allocating 'result'. Return 0 on success and something else on failure. */
int matrix_product(matrix_t *m1, matrix_t *m2, matrix_t *result) {
    if(!m1 || !m2 || !result || !m1->content || !m2->content){
        return -1;
    }
    if(m1->columns != m2->rows){
        return -1;
    }

    if(matrix_allocate(result, m1->rows, m2->columns) != 0){
        return -1;
    }

    /* Correct multiplication:
       iterate rows of m1, columns of m2, sum over shared dimension */
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m2->columns; j++) {
            int sum = 0;
            for (int k = 0; k < m1->columns; k++) {
                sum += m1->content[i][k] * m2->content[k][j];
            }
            result->content[i][j] = sum;
        }
    }
    return 0;
}

int matrix_dump_file(matrix_t *m, const char *output_file) {
    /* implement the function here ... */
    return -ENOSYS;
}

int matrix_allocate_and_init_file(matrix_t *m, const char *input_file) {
    /* implement the function here ... */
    return -ENOSYS;
}
