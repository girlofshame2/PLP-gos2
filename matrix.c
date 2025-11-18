#include "matrix.h"

#include <errno.h> /* for ENOSYS */

int matrix_allocate(matrix_t *m, int rows, int columns) {
    
    if (rows <= 0 || columns <= 0) {
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
    if(m->content == NULL ){
        return;
    }
    for(int i=0;i< m->columns; i++){
        free(m->content[i]);
    }
    free(m->content);

    m->content == NULL;
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
}

int matrix_sum(matrix_t *m1, matrix_t *m2, matrix_t *result) {
    return -ENOSYS;
}

int matrix_scalar_product(matrix_t *m, int scalar, matrix_t *result) {
    /* implement the function here ... */
    return -ENOSYS;
}

int matrix_transposition(matrix_t *m, matrix_t *result) {
    /* implement the function here ... */
    return -ENOSYS;
}

int matrix_product(matrix_t *m1, matrix_t *m2, matrix_t *result) {
    /* implement the function here ... */
    return -ENOSYS;
}

int matrix_dump_file(matrix_t *m, const char *output_file) {
    /* implement the function here ... */
    return -ENOSYS;
}

int matrix_allocate_and_init_file(matrix_t *m, const char *input_file) {
    /* implement the function here ... */
    return -ENOSYS;
}
