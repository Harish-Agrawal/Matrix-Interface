# Matrix-Interface
## Two different implementation for matrix interface : 
## 1. Regular 2-D array representation  
## 2. Compressed Sparse Row (CSR) representation 

### How to use:

- Compile the Runner.cpp using the given Makefile.
- Do not change the Makefile.
- For executing Runner.o, the command has to be given in the following way-

		./Runner.o load [array|csr] <input_file> <output_file>

		./Runner.o transpose [array|csr] <input_file> <output_file>

		./Runner.o multiply [array|csr] <input_file_1> <inpout_file_2> <output_file>

		./Runner.o bmultiply [array|csr] <input_file_1> <inpout_file_2> <output_file>

- Example - if you want to execute multiply() on csr implementation of the matrix with
input text files small1.tsv and small2.tsv, the command line will look like -

		./Runner.o multiply csr small1.tsv smal2l.tsv mult_out.tsv



# Random large matrix generator : 

- For Generating Random Matrices Use the Random.cpp and Makefile.
- Generates ***NxN*** dense or sparse matrices.

### How to use:
- Compile the code using make command 
- Run the file

		./exec [dense/sparse] sparsity_parameter

- Then Enter a number *b* such that 
             : Generated Matrices are of size: ***2^b x 2^b*** to ***4 x 4***
- If no sparsity_parameter is passed it will take default as 0.5.
- Eg.

		./exec sparse 0.7
		b = 2

- This generates a sparse matrix of ***4 x 4*** with sparsity parameter 0.7
- The output file will be **sparse_4x4_70.tsv** -- 70 denotes 70 % sparcity
- Sparsity parameter can be 0, 0.1, 0.2, ... 1 (1 means all the elements will be zero)
