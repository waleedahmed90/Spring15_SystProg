#include<stdio.h>
#include <stdbool.h>
#include<math.h>

//prototypes

//1.Function to get the matrix sizes
void get_size(int *, int *, int *, int *);
//2.To check the multiplication compatibility
bool iscompatible(int, int, int, int);
//3.Populate the matrices
void populate_matrix(int **, int **, int **, int, int, int, int);
//4.Display both matrices
void display_matrix(int **, int, int);
//5.Multiply the matrices
void mat_mul(int **, int **, int **, int, int, int, int);


//////////main function//////////////
int main(){

    int r1,c1,r2,c2;

    get_size(&r1,&c1,&r2,&c2);

    if(!iscompatible(r1,c1,r2,c2)){
        printf("Matrices are not compatible for multiplication\n");
        return 0;
    }

    int i; int j;

    int **mat1;
    mat1 =  (int*) malloc(r1);
    for(i=0;i<r1;i++){
        mat1[i]=(int) malloc(c1);
    }

    int **mat2;
    mat2 =  (int*) malloc(r2);
    for(i=0; i<r2;i++){
        mat2[i]=(int) malloc(c2);
    }

    int **outmat;
    outmat=(int*) malloc(r1);
    for(i=0;i<r1;i++){
        outmat[i]=(int) malloc(c2);
    }

    populate_matrix(mat1, mat2, outmat, r1,c1,r2,c2);

    //displaying matrix-1
    printf("\n\nMatrix_1\n\n");
    display_matrix(mat1, r1, c1);

    //displaying matrix-2
    printf("\n\nMatrix_2\n\n");
    display_matrix(mat2, r2, c2);

    //calling the matrix multiplication function
    mat_mul(mat1, mat2, outmat, r1, c1, r2, c2);

    //displaying the output matrix
    printf("\n\nOutPut(product) Matrix\n\n");
    display_matrix(outmat, r1, c2);


return 0;
}

//size input
void get_size(int *r1, int *c1, int *r2, int *c2){

    printf("Enter no. of rows in matrix 1: ");
    scanf("%d", &(*r1));
    printf("Enter no. of columns in matrix 1: ");
    scanf("%d", &(*c1));
    printf("Enter no. of rows in matrix 2: ");
    scanf("%d", &(*r2));
    printf("Enter no. of columns in matrix 2: ");
    scanf("%d", &(*c2));

    return;
}

//checking compatibility
bool iscompatible(int r1, int c1, int r2, int c2){
    return (c1==r2);
}

//filling matrices with random numbers
void populate_matrix(int **mat1,int **mat2,int **outmat,int r1, int c1, int r2, int c2){

    int i,j;



    //population of matrix 1
    for(i=0;i<r1;i++){
        for(j=0;j<c1;j++){
              mat1[i][j]=rand()%10+1;
        }
    }
    //population of matrix 2
    for(i=0;i<r2;i++){
        for(j=0;j<c2;j++){
            mat2[i][j]=rand()%10+1;
        }
    }

    //population of outmat
    for(i=0;i<r1;i++){
        for(j=0;j<c2;j++){
            outmat[i][j]=0;
        }
    }

}

//display
void display_matrix(int **mat, int r, int c){

    int i,j;
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }

}
//multiplication
void mat_mul(int **mat1,int **mat2, int **mat3,int r1, int c1,int r2, int c2){

            int i,j,k;
            int sum;
            //multiplication loops complexity n^3
            for(i=0;i<r1;i++){
                for(j=0;j<c2;j++){
                    sum=0;
                    for(k=0;k<r2;k++){
                        sum+=mat1[i][k]*mat2[k][j];
                    }
                    mat3[i][j]=sum;
                }
            }

}
