// Random large matrix generator
// Author : Harish Agrawal
// Generates nxn dense or sparse matrices 
// Usage - 
// Compile the code using make command 
// Run the file 
// >> ./exec [dense/sparse] sparsity_parameter
// Then Enter a number b such that 
//              : Generated Matrices are of size: 2^b x 2^b to 4 x 4
// If no sparsity_parameter is passed it will take default as 0.5
// Eg.
// ./exec sparse 0.7
// b = 2
// This generates a sparse matrix of 4 x 4 with sparsity parameter 0.7
// The output file will be sparse_4x4_70.tsv -- 70 denotes 70 % sparcity
// Sparsity parameter can be 0, 0.1, 0.2, ... 1 (1 means all the elements will be zero)

#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <fstream> // Used for File handling in CPP 
#include <bits/stdc++.h>
#include <cstdlib>

using namespace std;

int main(int n, char *argv[])
{
    int rand();
    std::random_device rd;
    int exponent, element, i, j, num_elements, q; 
    unsigned long size;
    float sparse_f;
    float sparse_par = 0.5;
    if (n>2)
        sparse_par = stof(argv[2]);

    std::mt19937_64 e2(rd());
    std::uniform_real_distribution<> dist(-1000, 1000);

//  For generating sparse matrices
    std::uniform_real_distribution<float> sparsity_distribution(0, 1);
    
    cout << "Enter b such that : Generated Matrices are of size: 2^b x 2^b to 4 x 4 " << endl;
    cout << "b = " ;
    cin  >> exponent;
    size = pow(2,exponent);
    num_elements = size*size;
    i = exponent%3;
    j = size%4;
    // m    = 1;

    fstream op_file[exponent];
    
    for(int m = 1; m < exponent; m++)
    {
        num_elements = size*size;
        string s = to_string(size);
        string par = to_string(int(ceil(sparse_par*10)*10)) ;
        string file_ext = ".tsv", op = argv[1] ;
        string outputFile = op + "_" + s + "x" + s + file_ext;
        if(strcmp("sparse", argv[1])==0)
            outputFile = op + "_" + s + "x" + s + "_" +  par + file_ext;

        cout << endl; 
        cout << "Generating next Matrix " << endl;

        op_file[m].open(outputFile, ios::out | ios::trunc);
        

        if(i==0)
        {
            cout <<"Random Engine used to generate " << m << " Matrix is :" <<"mt19937_64" <<endl;
            std::mt19937_64 e2(rd());
            i++;    
        }
        else if(i==1)
        {
            cout <<"Random Engine used to generate " << m << " Matrix is :" <<"knuth_b" <<endl;
            std::knuth_b e2(rd());
            i++;
        }
        else if(i==2)
        {
            cout <<"Random Engine used to generate " << m << " Matrix is :" <<"default_random_engine" <<endl;
            std::default_random_engine e2(rd()) ;
            i=0;
        }

        //
        // Distribtuions
        //
  
        if(j==0)
        {
            cout <<"Distributiom used to generate " << m << " Matrix is :" <<"uniform_real_distribution" <<endl;
            std::uniform_real_distribution<> dist(-1000, 1000);
            j++;
        }    
        else if(j==1)
        {
            cout <<"Distributiom used to generate " << m << " Matrix is :"<<"normal_distribution" <<endl;
            std::normal_distribution<> dist(5000,2);
            j++;
        }
        else if(j==2)
        {
            cout <<"Distributiom used to generate " << m << " Matrix is :"<<"student_t_distribution" <<endl;
            std::student_t_distribution<> dist(1000);
            j++;
        }
        else if(j==3)
        {
            cout <<"Distributiom used to generate " << m << " Matrix is :"<<"extreme_value_distribution" <<endl;
            std::extreme_value_distribution<> dist(-5000,5000);
            j=0;
        }


        // Starting to write to output file  
        if(!op_file[m].is_open())
        {
            cout << "Error while opening the file" << endl;
        }
        else
        {    
            op_file[m]<< size << "\t" << size << endl;
            // If sparse matrix is needed
            if(strcmp("sparse", argv[1])==0)
            {
                for(i = 0; i < size; i++)
                {
                    for(j = 0; j < size; j++)
                    {
                        bool isZero = sparsity_distribution(e2) < sparse_par; 
                        if(isZero)
                            sparse_f = 0.0;
                        else
                            sparse_f = dist(e2);


                        if(j < (size-1))
                            op_file[m] <<fixed<<setprecision(3)<< sparse_f << "\t";
                        else
                            op_file[m] <<fixed<<setprecision(3)<< sparse_f << "\n";
                    }
                }
            }
            else if(strcmp("dense",argv[1])==0)
            {
                for(i = 0; i < size; i++)
                {
                    for(j = 0; j < size; j++)
                    {
                    if(j < (size-1))
                        op_file[m] <<fixed<<setprecision(3)<< dist(e2) << "\t";
                    else
                        op_file[m] <<fixed<<setprecision(3)<< dist(e2) << "\n";
                    }
                }                
            }    

        }

       size=size/2;
       op_file[m].close();
       
   }
}