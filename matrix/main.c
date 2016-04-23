#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double determinant(int rc, double **matrix);
void cofactor_matrix(int rc, double **matrix, double **out);
void get_minor(int rc, double **matrix, double **out, int row, int col);

int main()
{
	int row, i, j = 0;

	double **matrix, *b;

	printf("Enter the row,column count of your square matrix: ");
	scanf("%d", &row);

	// Allocate memory for our matrix A
	matrix = malloc(row * sizeof(double *));
	if(NULL == matrix) {
		fprintf(stderr, "Cannot allocate memory for matrix!");
		return 1;
	}

	for(i = 0; i < row; i++) {
		matrix[i] = malloc(row * sizeof(double));
		if(NULL == matrix[i]) {
			fprintf(stderr, "Cannot allocate memory for matrix!");
			return 1;
		}
	}

	b = malloc(row * sizeof(double));
	if(NULL == b) {
		fprintf(stderr, "Cannot allocate memory for matrix!");
		return 1;
	}

	for(i = 0; i < row; i++) {
		for(j = 0; j < row; j++) {
			printf("Enter the value of [%d][%d]: ", i, j);
			scanf("%lf", &matrix[i][j]);
		}
	}

	for(j = 0; j < row; j++) {
		printf("Enter the value [%d] of B matrix: ", j);
		scanf("%lf", &b[j]);
	}

	double det = determinant(row, matrix);
	if(floor(det) == 0.0) {
		printf("Determinant of your matrix is %lf. Cannot compute the inverse of the matrix!\n", det);
		return 1;
	}

	printf("Determinant of your matrix is %lf\n", det);

	// Allocate memory for cofactor_matrix
	double **cof_matrix;
	cof_matrix = malloc(row * sizeof(double *));
	if(NULL == cof_matrix) {
		fprintf(stderr, "Cannot allocate memory for cofactor matrix!");
		return 1;
	}

	for(i = 0; i < row; i++) {
		cof_matrix[i] = malloc(row * sizeof(double));
		if(NULL == cof_matrix[i]) {
			fprintf(stderr, "Cannot allocate memory for cofactor matrix!");
			return 1;
		}
	}

	cofactor_matrix(row, matrix, cof_matrix);

	// Transpose the matrix
	double tmp;

    for (i = 1; i < row; i++) {
    	for (j = 0; j < i; j++) {
        	tmp = cof_matrix[i][j];
        	cof_matrix[i][j] = cof_matrix[j][i];
        	cof_matrix[j][i] = tmp;
    	}
    }

    det = 1 / det;

    for (i = 0; i < row; i++) {
    	for (j = 0; j < row; j++) {
        	cof_matrix[i][j] = cof_matrix[i][j] * det;
    	}
    }

    // cof_matrix is now the inverse of the A matrix
    // to find x, we are gonna multiply the inverse of A and B
    double t = 0.0;
    printf("SOLUTION MATRIX\n");
    for (i = 0; i < row; i++) {
    	for (j = 0; j < row; j++) {
        	t += cof_matrix[i][j] * b[j];
    	}
    	printf("%lf\n", t);
    	t = 0.0;
    }

	// cleanup the allocated memory
	for(i = 0; i < row; i++) {
		free(matrix[i]);
		free(cof_matrix[i]);
	}

	free(matrix);
	free(cof_matrix);
	free(b);

	return 0;
}

double determinant(int rc, double **matrix)
{
	double **sub_array;
	double det = 0.0;

	int i, k, j;
	int ii, kk, jj, ll, row, column;

	// If it is a 1x1 matrix
	if(1 == rc) {
		return matrix[0][0];
	} else if (2 == rc) {
		// If it is a 2x2 matrix
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}

	sub_array = malloc((rc - 1) * sizeof(double *));
    for (i = 0; i < rc - 1; i++)
        sub_array[i] = malloc((rc - 1) * sizeof(double));

	for (i = 0; i < rc; i++) {
		get_minor(rc, matrix, sub_array, 0, i);

		det += (i % 2 == 1 ? - 1.0 : 1.0) * matrix[0][i] * determinant(rc - 1, sub_array);
	}

	for(i = 0; i < rc - 1; i++) {
		free(sub_array[i]);
	}

	return det;
}

void cofactor_matrix(int rc, double **matrix, double **out)
{
	int i,j;

	double **minor = malloc((rc - 1) * sizeof(double *));
	for (i = 0; i < rc - 1; i++)
		minor[i] = malloc((rc - 1) * sizeof(double));

	int cofactor_index = 0;

	for (i = 0; i < rc; ++i) {
		for (j = 0; j < rc; ++j) {
			get_minor(rc, matrix, minor, i, j);

			out[i][j] = (cofactor_index % 2 == 0 ? 1.0 : -1.0) * determinant(rc - 1, minor);

			cofactor_index++;
		}
	}
}

void get_minor(int rc, double **matrix, double **out, int row, int col)
{
	int i,j;
	int cc = 0, roc = 0;
 
    for(i = 0; i < rc; i++ ) {
        if(i != row)
        {
            cc = 0;
            for(j = 0; j < rc; j++ )
            {
                if(j != col)
                {
                    out[roc][cc] = matrix[i][j];
                    cc++;
                }
            }
            roc++;
        }
    }
}