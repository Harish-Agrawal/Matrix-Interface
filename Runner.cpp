// For executing Runner.o, the command has to be given in the following way-

//     ./Runner.o load [array|csr] <input_file> <output_file>

//     ./Runner.o transpose [array|csr] <input_file> <output_file>

//     ./Runner.o multiply [array|csr] <input_file_1> <inpout_file_2> <output_file>

//     ./Runner.o bmultiply [array|csr] <input_file_1> <inpout_file_2> <output_file>

// Example - if you want to execute multiply() on csr implementation of the matrix with
// input text files small1.tsv and small2.tsv, the command line will look like - 
//     ./Runner.o multiply csr small1.tsv smal2l.tsv mult_out.tsv



#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>

#include <fstream>
#include <sstream>

#include <chrono>

#include <bits/stdc++.h>
#include "MatrixImpl.cpp"

using namespace std;
/**
  * Runner code that serves as harness for invoking various functions required
  * to be implemented for this assignment.
  * You may modify this code, but need to retain the input parameter signature and
  * output requirements specified in the assignment.
  */

/////////////////////////////////////////////////////////////////////////////
    
IMatrix* init_arr(int rows, int cols)
{   
    // TODO: Code for initializing an empty matrix using array impl with rows and cols as 
    // dimensions, and returning the object
    try
    {
        ArrayMatrix * arr_matrix_obj1 = new ArrayMatrix();
        IMatrix* imat=arr_matrix_obj1;
        imat->init(rows,cols);
        return imat;
    }
    catch(bad_alloc &error)
    {
        cout<<"Bad alloc Exception Occured"<< endl;
        cout<<error.what() << endl;
        throw;
    }

}    


IMatrix* load_arr(char* input_file)
{
	// TODO: Code for loading matrix from input_file into array impl and returning object
    fstream ip_file;
    ip_file.open(input_file, ios::in);
    if(!ip_file.is_open())
    {
        cout << "Error while opening the file" << endl;
    }
    else
    {
        string s_row, s_col, value;
        int rowNo, colNo;

        getline(ip_file,s_row,'\t');
        getline(ip_file,s_col,'\n');

        rowNo=stoi(s_row);
        colNo=stoi(s_col);

        // cout << rowNo << "x" << colNo << endl;

        IMatrix* arr_matrix_obj2= init_arr(rowNo,colNo);
        // stringstream x[rowNo][colNo]; // SS objects are created ---This doesnt work when matrix size is large
        try
        {
            float *y=new float[colNo]();
            for(int i=0;i<rowNo;i++)
            {
                for(int j=0;j<colNo;j++)
                {
                    if(j<(colNo-1))
                    {
                        getline(ip_file,value,'\t');
                    }
                    else
                    {
                        getline(ip_file,value,'\n');
                    }
                    y[j]=stof(value);
                }

                arr_matrix_obj2->append(y);
            }
            delete[] y;
            ip_file.close();
            return arr_matrix_obj2;
        }
        catch(bad_alloc &error)
        {
            cout<<"Bad alloc Exception Occured"<< endl;
            cout<<error.what() << endl;
            throw;
        }


    }   
}




IMatrix* init_csr(int rows, int cols)
{
	// TODO: Code for initializing an empty matrix using CSR impl with rows and cols as
	// dimensions, and returning the object
    try
    {
        CSRMatrix * csr_matrix_obj1 = new CSRMatrix();
        IMatrix* imat=csr_matrix_obj1;
        csr_matrix_obj1->init(rows,cols);
        return csr_matrix_obj1;
    }
    catch(bad_alloc &error)
    {
        cout<<"Bad alloc Exception Occured"<< endl;
        cout<<error.what() << endl;
        throw;
    }

}



IMatrix* load_csr(char* input_file)
{
	// TODO: Code for loading matrix from input_file into CSR impl and returning object

    fstream ip_file;
    ip_file.open(input_file, ios::in);
    if(!ip_file.is_open())
    {
        cout << "Error while opening the file" << endl;
    }
    else
    {
        string s_row, s_col, value;
        int rowNo, colNo;

        getline(ip_file,s_row,'\t');
        getline(ip_file,s_col,'\n');

        rowNo=stoi(s_row);
        colNo=stoi(s_col);

        // cout << rowNo << "x" << colNo << endl;

        IMatrix* csr_matrix_obj2= init_csr(rowNo,colNo);
        // stringstream x[rowNo][colNo]; // SS objects are created ---This doesnt work when matrix size is large
        try
        {
            float *y=new float[colNo]();
            for(int i=0;i<rowNo;i++)
            {
                for(int j=0;j<colNo;j++)
                {
                    if(j<(colNo-1))
                    {
                        getline(ip_file,value,'\t');
                    }
                    else
                    {
                        getline(ip_file,value,'\n');
                    }
                    y[j]=stof(value);
                }

                csr_matrix_obj2->append(y);
            }
            delete[] y;
            ip_file.close();
            return csr_matrix_obj2;

        }
        catch(bad_alloc &error)
        {
            cout<<"Bad alloc Exception Occured"<< endl;
            cout<<error.what() << endl;
            throw;
        }

    }  

}





void print_mat(IMatrix* mat, char* output_file)
{
	// TODO: print matrix as TSV to output_file
	fstream op_file;
    op_file.open(output_file, ios::out | ios::trunc);

    if(!op_file.is_open())
    {
        cout << "Error while opening the file" << endl;
    }
    else
    {
        int rowNo=mat->row_count();
        int colNo=mat->col_count();
        op_file<< rowNo << "\t";
        op_file<< colNo << "\n";
        for(int i=0;i<rowNo;i++)
        {
            for(int j=0;j<colNo;j++)
            {
                if(j<(colNo-1))
                {
                    op_file <<fixed<<setprecision(3)<< mat->get(i,j) << "\t" ;
                }
                else
                {
                    op_file <<fixed<<setprecision(3)<< mat->get(i,j) << endl;
                }
            }

        }

    }
    return ;
}

/////////////////////////////////////////////////////////////////////////////

void load(char* mat_type, char* input_file, char* output_file)
{
	// TODO: any other validation?
    chrono::time_point<chrono::system_clock> start, end;
    
	IMatrix* mat1;

	if (strcmp("array", mat_type)==0) // TODO: time this region and print "load,array,output_file,time_Millisec"
    {
        start = chrono::system_clock::now();
		mat1 = load_arr(input_file);
        end = chrono::system_clock::now();
        double loadTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
        cout << "load,array,"<<output_file<<","<< loadTime*1e-6 << endl;
        // cout<<"\t\tSpace 2-D Array,"<<(mat1->col_count()*mat1->row_count())<<endl;
    }
	else if (strcmp("csr", mat_type)==0) // TODO: time this region and print "load,csr,output_file,time_Millisec"
	{
        start = chrono::system_clock::now();
		mat1 = load_csr(input_file);
        end = chrono::system_clock::now();
        double loadTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
        cout << "load,csr,"<<output_file<<","<< loadTime*1e-6 << endl;
        // cout<<"\t\tSpace CSR,"<<(2*mat1->nnz_count()+(mat1->row_count()+1))<<endl;
	}
	else
		cout << "[load] invalid matrix type input seen: " << mat_type << endl;

	// store the loaded matrix mat1 in output file given by output_file
	print_mat(mat1, output_file);
    delete mat1;
	return;
}

/////////////////////////////////////////////////////////////////////////////
void transpose(IMatrix* mat1, IMatrix* mat2)
{
    // TODO: Code for finding the transpose of mat1 and storing in a new matrix mat2
    int t_rowNo=mat1->row_count(), t_colNo=mat1->col_count();
    try
    {
        float *x=new float[t_rowNo]();
        for(int i=0;i<t_colNo;i++)
        {
            for(int j=0;j<t_rowNo;j++)
            {
               x[j]= mat1->get(j,i);
            }
            mat2->append(x);
        }

        delete[] x;
        return;

    }
    catch(bad_alloc &error)
    {
        cout<<"Bad alloc Exception Occured"<< endl;
        cout<<error.what() << endl;
        throw;
    }

}

void transpose(char* mat_type, char* input_file, char* output_file)
{
	// TODO: any other validation?
    chrono::time_point<chrono::system_clock> start, end;

	IMatrix* mat1, *mat2;

	if (strcmp("array", mat_type)==0)
   {
		mat1 = load_arr(input_file);

		// TODO: any other validation? 

		mat2 = init_arr(mat1->col_count(), mat1->row_count()); 
        // cout<<"Transpose-array"<<endl;
   }
	else if (strcmp("csr", mat_type)==0)
	{
		mat1 = load_csr(input_file);

		// TODO: any other validation?

		mat2 = init_csr(mat1->col_count(), mat1->row_count());
        // cout<<"Transpose CSR_Matrix"<<endl;
	}
	else {
		cout << "[transpose] invalid matrix type input seen: " << mat_type << endl;
		return;
	}

	// TODO: time this method and print "transpose,mat_type,output_file,time_Millisec"
    start = chrono::system_clock::now();
	transpose(mat1, mat2);
    end = chrono::system_clock::now();
    double transposeTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
    cout << "transpose"<< mat_type<<","<< output_file<<"," << transposeTime*1e-6 << endl;
	// store output matrix mat2 in file given by output_file
	print_mat(mat2, output_file);

    delete mat1,mat2;

	return;
}



///////////////////////////////////////////////////////////////////////////////
//


void multiply(IMatrix* mat1, IMatrix* mat2, IMatrix* mat3)
{

// Here I have tried to access elements of Matrix 1 and Matrix 2 row wise so that Multiplication 
// Can be done faster and there is no significant delay in accessing elements
    int numofRows =mat1->row_count() , numofCols=mat2->col_count();
    try
    {
        // Allocating Space for Temporary array to store intermediate multiplication results
        float* C=new float[numofCols]();

        if (mat1->col_count()==mat2->row_count())
        {
            for(int i=0;i<numofRows;i++)
            {
                // As I am using only one Dimension array to store the multiplication results
                // need to initialize it with zero for storing second row of Output Matrix
                for(int m=0;m<numofCols;m++)
                    C[m]=0;


                for(int k=0;k<mat1->col_count();k++)
                {
                    for(int j=0;j<numofCols;j++)
                    C[j]+= mat1->get(i,k) * mat2->get(k,j);
                }

                mat3->append(C);
            }
            

        }
        else
            cout<<"Matrix cannot be multiplied as they are out of dimensions"<<endl;
        
        delete[] C;
        return;
        
    }
    catch(bad_alloc &error)
    {
        cout<<"Bad alloc Exception Occured in Multiplication"<< endl;
        cout<<error.what() << endl;
        throw;
    }
    
    // TODO: Code for multiplying the mat1 and mat2 and storing in a third matrix mat3

}

void multiply(char* mat_type, char* input_file1, char* input_file2, char* output_file)
{
	// TODO: any other validation?
    chrono::time_point<chrono::system_clock> start, end;
	IMatrix* mat1, *mat2,* mat3;

	if (strcmp("array", mat_type)==0)
   {
        // cout<<"Multiply-array"<<endl;
		mat1 = load_arr(input_file1);
		mat2 = load_arr(input_file2);

		// TODO: any other validation?

		// TODO: init output matrix mat3 with arr impl
        mat3= init_arr(mat1->row_count(), mat2->col_count());
	}
	else if (strcmp("csr", mat_type)==0)
	{
        // cout<<"Multiply CSR_Matrix"<<endl;
		mat1 = load_csr(input_file1);
		mat2 = load_csr(input_file2);

		// TODO: any other validation?

		// TODO: init output matrix mat3 with csr impl
        mat3= init_arr(mat1->row_count(), mat2->col_count());
	}
	else {
		cout <<"[multiply] invalid matrix type input seen: " << mat_type << endl;
		return;
	}

	// TODO: time this method and print "multiply,mat_type,output_file,time_Millisec"
    start = chrono::system_clock::now();
	multiply(mat1, mat2, mat3);
    end = chrono::system_clock::now();
    double multiplyTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
    cout << "multiply,"<<mat_type<<","<<output_file <<"," << multiplyTime*1e-6 << endl;

	// store output matrix mat3 in file given by output_file
	print_mat(mat3, output_file);
    delete mat1,mat2,mat3;

	return;
}


///////////////////////////////////////////////////////////////////////////////
//

void bmultiply(IMatrix* mat1, IMatrix* mat2, IMatrix* mat3)
{

    // TODO: Code for multiplying using block matrix multiplication
    // the matrices mat1 and mat2 and storing in a third matrix mat3
    int ori_size=mat1->col_count();
    int blk_size=4, temp=ori_size;
    // while(temp!=2)
    // {
    //     blk_size=temp;
    //     temp=temp/2;
    // }
    //int blk_size = ori_size/2;
    // cout << "Block Matrix Multiplication with Row Size="<<blk_size<<" Original Size="<<ori_size<<endl;

    try
    {

// We only need temporary matrix of size Block Size x Column numbers to store BlkSize number of rows that
// are generated in between

        float** C=new float * [blk_size];
            for(int h=0;h<blk_size;h++)
            {
                C[h]= new float[ori_size]();
            }
        // for(int m=0;m<blk_size;m++)
        //     for(int o=0;o<ori_size;o++)
        //         C[m][o]=0;
        for(int rowBlk=0;rowBlk < ori_size; rowBlk+=blk_size)
        {
            
            for(int colBlk=0; colBlk<ori_size ; colBlk+=blk_size)
            {
               
                for(int i=rowBlk;i<min(rowBlk+blk_size,ori_size);i++)
                {
                    
                    for(int k=colBlk;k< min(colBlk+blk_size,ori_size);k++)
                    {
                           
                        for(int j=0;j<ori_size;j++)
                                C[i-rowBlk][j]+= mat1->get(i,k) * mat2->get(k,j);
                    }
                    
                }
            }
            // this loop is copying results of First blk_size rows to output matrix 
            // and also resetting them to zero so that they can be used again in other loop
            for(int g=0;g<blk_size;g++)
            {
                mat3->append(&C[g][0]);
                for(int u=0;u<ori_size;u++)
                    C[g][u]=0;
            }
            

        }

        // for(int t=0;t<ori_size;t++)
        // {
        //     for(int r=0;r<ori_size;r++)
        //         cout<<C[t][r]<<"\t";
        //     cout<<endl;
        // }

        for(int i=0;i<blk_size;i++)
        {
            delete[] C[i];  
        }
        delete [] C;
        C=nullptr;
        return;
    }
    catch(bad_alloc &error)
    {
        cout<<"Bad alloc Exception Occured in BMultiplication"<< endl;
        cout<<error.what() << endl;
        throw;
    }
}

void bmultiply(char* mat_type, char* input_file1, char* input_file2, char* output_file)
{
	// TODO: any other validation?
    chrono::time_point<chrono::system_clock> start, end;
	IMatrix* mat1, * mat2, * mat3;

	if (strcmp("array", mat_type)==0)
   {
		mat1 = load_arr(input_file1);
		mat2 = load_arr(input_file2);

		// TODO: any other validation?

        // Assuming that matrices are square and number of rows(cols) are in 2^n 

		// TODO: init output matrix mat3 with arr impl
        mat3= init_arr(mat1->row_count(), mat2->col_count());

	}
	else if (strcmp("csr", mat_type)==0)
	{
		mat1 = load_csr(input_file1);
		mat2 = load_csr(input_file2);

		// TODO: any other validation?

        // Assuming that matrices are square and number of rows(cols) are in 2^n 

		// TODO: init output matrix mat3 with csr impl
        mat3= init_arr(mat1->row_count(), mat2->col_count());
	}
	else {
		cout << "[bmultiply] invalid matrix type input seen: " << mat_type << endl;
		return;
	}


   
	// TODO: time this method and print "bmultiply,mat_type,output_file,time_Millisec"

    start = chrono::system_clock::now();
	bmultiply(mat1, mat2, mat3);
    end = chrono::system_clock::now();
    double BmultiplyTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
    cout << "bmultiply,"<<mat_type<<","<<output_file<<","<< BmultiplyTime*1e-6 << endl;
  
	// store output matrix mat3 in file given by output_file
	print_mat(mat3, output_file);

	return;
}


///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int main(int n, char *argv[])
{

    try
    {

    	if(strcmp("load", argv[1])==0)
    	{    
    		load(argv[2], argv[3], argv[4]);
    	}  
       else if( strcmp("transpose", argv[1])==0)
    	{
    		transpose(argv[2], argv[3], argv[4]);
    	}
       else if(strcmp("multiply", argv[1])==0 )
    	{
           multiply(argv[2], argv[3], argv[4], argv[5]);
    	}
       else if(strcmp("bmultiply", argv[1])==0)
    	{
           bmultiply(argv[2], argv[3], argv[4],argv[5]);
    	}
        else
    		cout << "[main] invalid input parameters. Valid usage is..." << endl;

    	return 0;

    }
    catch(...)
    {
        cout<<" Unexpected Exception has Occured"<<endl;
    }
}
