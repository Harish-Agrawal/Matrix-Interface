#include "IMatrix.h"
#include <iostream>
#include<fstream>
#include <sstream>
#include<stdexcept>

using namespace std;

IMatrix::~IMatrix()
{
	// cout<<"Destructor of IMatrix"<<endl;
}

/**
 * 2D Matrix Implementation usign 2-Dimensional Array
 */

class ArrayMatrix: public IMatrix
{
	/*#######################################################
	 # Define your own data structures here
	 #######################################################*/

	private:
		// TODO
		int numofRows, numofCols, rowNumber=0;
		int arrNNZ_count;
		float ** arr;
		bool in=false;
//		float arr[numofRows][numofCols];

	public:
		// TODO


	/**
     * Default constructor is required.
	 * You may optionally define additional constructors as well.
     */
	ArrayMatrix()
	{
		// TODO: Provide implementation for default constructor
		// cout << "Inside Default ArrayMatrix constructor" << endl;
		// cannot initialize any member of ArrayMatrix class as we don't have any information regarding number of rows
		// and number of columns
	}
	// ArrayMatrix(int rows=10, int cols=10)
	// {
	// 	// TODO: Provide implementation for default constructor
	// 	cout << "Inside Modified ArrayMatrix constructor" << endl;
	// 	numofRows=rows;
	// 	numofCols=cols;
	// 	init(numofRows,numofCols);
	// }

	///////////////////Destructor////////////////////////
	~ArrayMatrix()
	{
		// TODO: Provide implementation for default constructor
		// cout << "Inside ArrayMatrix Destrutor" << endl;
         for(int i=0;i<numofRows;i++)
         {
         	delete[] arr[i];  
         }
        delete [] arr;
        // cout << "Deleted array from heap" << endl;
	}


	/*#######################################################
 	  # Override functions defined in IMatrix interface
	  #######################################################*/

/** Override the init function defined in the IMatrix interface */
    void init (int N, int M)
 	{
		// TODO: Provide implementation for init using array
		try
		{
			if(in==true)
				throw runtime_error("You are trying to Initialize ArrayMatrix again");

				numofRows=N;
				numofCols=M;
		//		float arr[numofRows][numofCols];
				try
				{
			        arr = new float * [numofRows];
			         for(int i=0;i<numofRows;i++)
			         {
			             arr[i]=new float [numofCols]();
			         }					
				}
				catch(bad_alloc &error)
				{
					cout<<"Bad alloc Exception Occured"<< endl;
					cout<<error.what() << endl;
				}
		        // int i,j;
				// for(i=0;i<numofRows;i++)
		  //       {
		  //           for(j=0;j<numofCols;j++)
		  //           {
		  //               arr[i][j]=0;
		  //           }
		  //       }
		        in=true;
			
		}
		catch(runtime_error &error)
		{
			cout<<"Logic Error Exception Occured-2D-Array"<<endl;
			cout<<error.what()<<endl;
			throw;
		}
	}



/** Override the append function defined in the IMatrix interface */
    void append (float* row_vals)
	{
        // TODO: Provide implementation for append using array
        // as row_val is float pointer we cannot check if it has more elements than Column of given matrix
        // so assuming that is correct even if it not we are only taking first M(Number of column) values 
	    try
	    {

		    if(rowNumber>=numofRows)
	        	throw out_of_range("You are trying to insert more data than specified");

	            for(int i=0;i<numofCols;i++)
	            {
	                arr[rowNumber][i]=*(row_vals+i);
	            }
	            rowNumber++;
	    }
	    catch(out_of_range &error)
	    {
	    	cout << "Out of Range Exception Occured-2D-Array" <<endl;
	    	cout << error.what() << endl;
	    	throw;
	    }



	}


/** Override the get function defined in the IMatrix interface */
	float get(int i, int j)
	{
	    // TODO: Provide implementation for get using array
	    try
	    {
		    if(i>=numofRows||j>=numofCols)
		    	throw out_of_range("You are trying access out of Range element");
		    
		    return arr[i][j];
	    }
	    catch(out_of_range &error)
	    {
            cout << "Out of Range Exception Occured-2D-Array" << endl;
            cout << "Matrix is of dimension:"<<numofRows<<"x"<<numofCols<<endl;
            cout << error.what() << endl;
            throw;
        }
	}




	/**
	  * This returns the number of rows in the matrix based on init()
	  */
	int row_count()
	{
		// TODO: Provide implementation using array
		return numofRows;
	}

	/**
	  * This returns the number of columns in the matrix based on init()
	  */
	int col_count()
	{
		// TODO: Provide implementation using array
		return numofCols;
	}


	/**
	  * This returns the number of non zero values in the matrix
	  */
	int nnz_count()
	{
		// TODO: Provide implementation using array
		arrNNZ_count=0;
		for(int i=0;i<numofRows;i++)
        {
            for(int j=0;j<numofCols;j++)
            {
                if(arr[i][j]!=0)
                	arrNNZ_count++;
            }
        }
	}

	/*#######################################################
	 # Optionally define any other private utility functions here
	 #######################################################*/

};

/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/**
 * 2D Matrix Implementation usign CSR
 */
class CSRMatrix: public IMatrix
{

	/*#######################################################
	 # Define your own data structures here
	 #######################################################*/

	private:
		// TODO
		int CSR_numofRows,CSR_numofCols,csrNNZ_count=0,CSR_rowNumber=0;
		float * arr_NZele;
        int * Comp_row;
        int * col;
        bool csr_in=false;
	public:
		// TODO
		unsigned long int Maxsize,size;
        

	/**
     * Default constructor is required.
	 * You may optionally define additional constructors as well.
     */
	CSRMatrix()
	{
		// TODO: Provide implementation for default constructor
		// cout<<"Inside Constructor of CSR matrix"<<endl;
	}


	~CSRMatrix()
	{
		// cout << "Inside CSR Destructor" << endl;
		delete [] arr_NZele;
		delete [] Comp_row;
		delete [] col;
	}


	/*#######################################################
 	  # Override functions defined in IMatrix interface
	  #######################################################*/

	/** Override the init function defined in the IMatrix interface */
	void init (int N, int M)
 	{
 		// TODO: Provide implementation for init using csr
 		try
		{
			if(csr_in==true)
				throw runtime_error("You are trying to Initialize CSR_Matrix again");

	 	    CSR_numofRows=N;
	 	    CSR_numofCols=M;
	 	    Maxsize=N*M;
	 	    size=Maxsize/2;
	        // Maximum size can be M x N that is all elements are non zero elements
	        try
	        {
		 	    arr_NZele = new float [Maxsize]();
		 	    Comp_row=new int [CSR_numofRows+1]();
		 	    col=new int [Maxsize]();	        	
	        }
	        catch(bad_alloc &error)
			{
				cout<<"Bad alloc Exception Occured"<< endl;
				cout<<error.what() << endl;
				throw;
			}

	 	    Comp_row[0]=0;  // Always will be equal to zero as per CSR representation

	 	    // for(int i=0;i<CSR_numofRows;i++)
	      //   {
	      //       for(int j=0;j<(CSR_numofCols);j++)
	      //       {
	      //           arr_NZele[j+i*(CSR_numofCols)]=0;
	      //           col[j+i*(CSR_numofCols)]=0;
	      //       }
	      //       Comp_row[i+1]=0;
	      //   }

	        csr_in=true;

 		}
 		catch(runtime_error &error)
		{
			cout<<"Logic Error Exception Occured-CSR"<<endl;
			cout<<error.what()<<endl;
			throw;
		}
		catch(bad_alloc &error)
			{
				throw;
			}
		
	}
//

	/** Override the append function defined in the IMatrix interface */
   void append (float* row_vals)
	{
	    // TODO: Provide implementation for append using csr
		try
		{

		    if(CSR_rowNumber >= CSR_numofRows)
		    	throw out_of_range("You are trying to insert more data than specified");
	        
	            for(int j=0;j<CSR_numofCols;j++)
	            {
	                if(row_vals[j]!=0)
	                {
	                    arr_NZele[csrNNZ_count]=row_vals[j];
	                    col[csrNNZ_count]=j;
	                    csrNNZ_count++;
	                }
	                
	// Calling increase 
	                // if(csrNNZ_count==size)
	                // 	{
	                // 	IncreaseSize(j);
	                // 	}  ///   ---- Not using this function instead alloted maximum size to both Element array and col array
	                // and at last shrinking them of how much is required
	            }
	            Comp_row[CSR_rowNumber+1]=csrNNZ_count;
	            
	//			after scanning last row, now resizing(shrinking) arrays which store elements and col data 
	//			to number of NonZero elements
	            if(CSR_rowNumber==(CSR_numofRows-1))
	            {
	            	shrink();	
	            	// displayMat();
	            }
	            CSR_rowNumber++;

		}
		catch(out_of_range &error)
	    {
	    	cout << "Out of Range Exception Occured-CSR" <<endl;
	    	cout << error.what() << endl;
	    	throw;
	    }
    return;
	}


	/** Override the get function defined in the IMatrix interface */
	float get(int i, int j)
	{
	    // TODO: Provide implementation for get using csr
		try
		{
			if(i>=CSR_numofRows||j>=CSR_numofCols)
		    	throw out_of_range("You are trying access out of Range element");
			int s,e;
		    s=Comp_row[i];
	        e=Comp_row[i+1];
	        for(int m=s;m<e;m++)
	        {
	            if(col[m]==j)
	                return arr_NZele[m];		            
	        }
		  

		}
	  	catch(out_of_range &error)
		{
			cout << "Out of Range Exception Occured-CSR" << endl;
			cout << "Matrix is of dimension:"<<CSR_numofRows<<"x"<<CSR_numofCols<<endl;
			cout<<error.what()<<endl;
			throw;
		}


      
	}

	/**
	  * This returns the number of rows in the matrix based on init()
	  */
	int row_count()
	{
		// TODO: Provide implementation using csr
		return CSR_numofRows;
	}

	/**
	  * This returns the number of columns in the matrix based on init()
	  */
	int col_count()
	{
		// TODO: Provide implementation using csr
		return CSR_numofCols;
	}


	/**
	  * This returns the number of non zero values in the matrix
	  */
	int nnz_count()
	{
		// TODO: Provide implementation using csr
		return csrNNZ_count;
	}


	/*#######################################################
	 # Optionally define any other private utility functions here
	 #######################################################*/

	// TODO

	void shrink()
	{

		try
		{
			float * NewEle=new float[csrNNZ_count]();
			int * NewCol=new int[csrNNZ_count]();
			
			memcpy(NewEle,arr_NZele,csrNNZ_count * sizeof(float));

		
			memcpy(NewCol,col,csrNNZ_count * sizeof(int));

			size=csrNNZ_count;
			delete[] arr_NZele;
			delete[] col;
			arr_NZele=NewEle;
			col=NewCol;
		}
		catch(bad_alloc &error)
		{
			cout<<"Bad alloc Exception Occured"<< endl;
			cout<<error.what() << endl;
			throw;
		}
		catch (...)
		{
			cout<<"Unexpected Exception Occured Inside Shrink" << endl;
			throw;
		}
	

	 	
		// arr_NZele=(float*) realloc(arr_NZele,csrNNZ_count * sizeof(float));
		// col=(int*) realloc(col,csrNNZ_count * sizeof(int));
		// displayMat();
	}


	// void IncreaseSize(int j)
	// {
	// 	unsigned long int temp=0,ele;
	// 	ele=CSR_rowNumber*CSR_numofCols+(j+1);
	// 	cout<<"ele="<<ele<<endl;
	// 	cout<<"Increase Size has been called with size="<<size<< endl;
	// 	temp=(Maxsize-ele);
	// 	cout<<"Temp="<<temp<<endl;
	// 	cout<<"CSR_RowNumber ="<<CSR_rowNumber<<endl;
	// 	temp=(temp/ele)*(size);
	// 	cout<<"Temp="<<temp<<endl;
	// 	size = size+temp;
	// 	cout<<"New size is="<<size<<endl;


	// 	float * NewEle=new float[size];
	// 	int * NewCol=new int[size];
	// 	memcpy(NewEle,arr_NZele,size * sizeof(float));
	// 	memcpy(NewCol,col,size * sizeof(int));
	// 	size=csrNNZ_count;
	// 	delete [] arr_NZele;
	// 	delete [] col;
	// 	arr_NZele=NewEle;
	// 	col=NewCol;

	// }




    void displayMat()
    {
        int N=CSR_numofRows;
        int M=CSR_numofCols;
        int i,j;
        cout << "CR"<<"\t\t\t"<<"Col"<<"\t\t\t"<<"NZEle"<<endl;
		for(i=0;i<size;i++)
        {

                if(i<(N+1))
                    cout<<Comp_row[i]<<"\t\t\t";
                else
                    cout<<"\t\t\t";

                cout<<col[i]<<"\t\t\t";
                cout<<arr_NZele[i]<<endl;

        }

        cout<<endl;
        cout<<endl;
        cout<<endl;

    }

};