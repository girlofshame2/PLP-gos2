#include "matrix.h"
#include <stdlib.h>
#include <errno.h> /* for ENOSYS */
#include <stdio.h>  /* enable print for debugging */
#include <ctype.h>
#include <string.h>

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
            m->content = NULL;
            m->rows=0;
            m->columns=0;
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
    if(m->rows != m->columns){
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


int matrix_product(matrix_t *m1, matrix_t *m2, matrix_t *result) {
    if(!m1 || !m2 || !result || !m1->content || !m2->content){
        return -1;
    }

    if(m1->columns != m2->rows){
        return -1;

    }

    if(matrix_allocate(result, m1->rows, m2->columns) != 00){
        return -1;
    }

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
    
    //does the file, matrix and matrix content exist?
    if(!output_file || !m || !m->content){
        return -1;
    }
    //open file in overwrite mode
    FILE* f = fopen(output_file,"w");
    //check that worked 
   if(!f){
    return -1;
   }

    //iterate through the matrix and print it to the file 
    for(int i=0;i<m->rows;i++){
        for(int j=0; j<m->columns; j++){
            if (fprintf(f, "%d", m->content[i][j]) < 0){
                return -1;
            }
            
            if(j+1<m->columns){
                if(fprintf(f, " ") < 0){
                    fclose(f);
                    return -1;
                }
                //check if thats right
            }
        }
        if(fprintf(f,"\n") < 0){
            fclose(f);
            return -1;
        }
        //check that worked
    }
       
    //close file and make sure it closed properly
    if(fclose(f) < 0){
        fclose(f);
        return -1;
    }
    //if all went well return 0 
    return 0;
}

int matrix_allocate_and_init_file(matrix_t *m, const char *input_file) {

    //check that m exists, and that the output file also exists 
    if (!m || !input_file) {
        return -1;
    }

    //open file in read mode and check that worked 
    FILE *f = fopen(input_file, "r");
    if (!f) {
        return -1;
    }
     const size_t LINE_BUF_SIZE = 8192;

    char *line_buf = malloc(LINE_BUF_SIZE);
    if (line_buf == NULL) {
        fclose(f);
        return -1;
    }

    size_t cols = 0;
    size_t rows = 0;
    int *flat_values = NULL;
    size_t values_capacity = 0;
    size_t values_count = 0;


    while (fgets(line_buf, LINE_BUF_SIZE, f) != NULL) {
        char *p = line_buf;
        while (*p && isspace((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            continue;
        }

        size_t this_row_cols = 0;
        //char *saveptr = NULL;
        char *token = strtok_r(line_buf, " \t\r\n");//,&savetpr


        while (token != NULL) {
            char *endptr = NULL;
            errno = 0;
            long v = strtol(token, &endptr, 10);

            if (endptr == token || *endptr != '\0' || errno != 0) {
                free(flat_values);
                free(line_buf);
                fclose(f);
                return -1;
            }

            if (values_count == values_capacity) {
                size_t newcap = (values_capacity == 0 ? 64 : values_capacity * 2);
                int * tmp = realloc(flat_values, newcap * sizeof *flat_values);
                if (tmp  == NULL) {
                    free(flat_values);
                    free(line_buf);
                    fclose(f);
                    return -1;
                }
                flat_values = tmp;
                values_capacity = newcap;
            }

            flat_values[values_count++] = (int)v;
            this_row_cols++;
            token = strtok_r(NULL, " \t\r\n");//,andsavetpr
        }

        if (this_row_cols == 0) {
            continue;
        }
        if (cols == 0) {
            cols = this_row_cols;
        } 
        else if (cols != this_row_cols) 
        {
            free(flat_values);
            free(line_buf);
            fclose(f);
            
            return -1;
        }
        rows++;
    }

    free(line_buf);
    fclose(f);

    if (rows == 0 || cols == 0) {
        free(flat_values);
        return -1;
    }

    if (matrix_allocate(m, (int)rows, (int)cols) != 0)
     {
        free(flat_values);
        return -1;
    }
    size_t idx = 0;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            m->content[i][j] = flat_values[idx++];
        }
    }
    free(flat_values);
    return 0;
} 

     

