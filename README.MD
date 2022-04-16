# CSE 701 - Project 02 code instruction
## Brief
- This code is designed to compute the following arithmetic operations related to sparse matrix.
  
  - SpMV : Sparse Matrix * Dense Vector
  
  - SpMV_T : Transposed-Sparse Matrix * Dense Vector
  
  - SpMM : Sparse Matrix * Dense Matrix
  
  - SpMM_T : Transposed-Sparse Matrix * Dense Matrix
  
  - SpM_SpV : Sparse Matrix * Sparse Vector
  
  - SpM_SpV_T : Transposed-Sparse Matrix * Sparse Vector
  
  - SpM_SpM : Sparse Matrix * Sparse Matrix
  
  - SpM_SpM_T : Transposed-Sparse Matrix * Sparse Matrix
  
    
  
- Project 02 contains three sections
  - Main - main directory

    - The section contains a code to generate a program which perform above arithmetic operations

- Performance testing section - performance_Test directory

  - The section contains performance comparison of arithmetic operation based on input format.

  - Function confirmation section - func_confirm directory

    - The section contains unit tests of implemented functions.

    - The section contains following tests.

      - Matrix format conversion process

      - Arithmetic operations with COO/CSC/CSR

      - Arithmetic operations with simplified COO/CSC/CSR

      - DATA read/write process

      - Random sparse matrix, dense vector, and sparse vector generating process

        


- This code can be used with following inputs
  - .mtx : Standard COO sparse matrix format.
        
        - The project supports real/integer type sparse matrix only, it does not supports complex value.
        - The project supports - row column value - formatted data only, it does not support symmetrically formatted data nor coordinate value separated format.
        - The performance test sections supports square shape matrix only due to **memory issue**. With non-square matrix, the performance test requires twice memory space to generate test cases compares to square matrix caes. 
        - For more information [link](https://math.nist.gov/MatrixMarket/formats.html) 
- Also, to get .mtx file, please visit [SuiteSparse Matrix Collection](https://sparse.tamu.edu/)
        
  - .dmat : None standard dense matrix format designed for the project.
            For more information check **About the non-standard input format** section.
        
    - .dvec : None standard dense vector format designed for the project.
           For more information check **About the non-standard input format** section.
  
    - .svec : None standard sparse vector format designed for the project.
           For more information check **About the non-standard input format** section.
  
         


- Limitation of the code
  - The code supports arithmetic operations with dense matrix; however, because of memory limit, any operation that generates dense matrix is not recommanded.

  - Performance test does not support non-square matrix due to memory limitation.

  - To see the actual performance achievement, it is required to download a large-size sparse matrix from  [SuiteSparse Matrix Collection](https://sparse.tamu.edu/) and compare the difference.

    


## Overloaded operators in Project 02 Code
- == and != operation operator between COO/CSC/CSC
- multiplication operation operator between
  - COO * COO
  - COO * CSC
  - COO * CSR
  - CSC * COO
  - CSC * CSC
  - CSC * CSR 
  - CSR * COO
  - CSR * CSC
  - CSR * CSR 
- << ofstream operation operator for
  - COO
  - CSC
  - CSR
  - D_MATRIX
  - D_VECTOR
  - S_VECTOR
- Operators which are not supportted in the project
  - Any operator that causes addtion or substraction
  - The operation can result expansion of matrix to cause memory limit issue.


## To use Project 02 code as part of another code
- Simply include facade_COO.hpp/facade_CSC.hpp/facade_CSR.hpp based on required sparse matrix format.
- facade_CXX.hpp includes 
  - initialization from COO/CSC/CSR/ vectors of matrix data
  - converstion to the other format
  - transpose of matrix
  - overloaded operators
  - sparse matrix operations
- The facade version can be slower than the non-simplified version, but for third-party usage, it is recommended. 

## About sparse matrix

- **Sparse matrix** is used in many scientific computation applications. Especially, multiplication of a matrix with a vector. 

- As the computation gets complex and large, a method to compress the data size and minimize unnecessary memory accessing processes is required.

- One method to achieve data compression and minimization of unnecessary memory accessing is using a sparse matrix.

- Dense matrix contains every element including zero in the matrix which requires  **sizeof(double) * (column * row)** bytes in memory space, and zero value elements are generally not required for the multiplication process.

- Sparse matrix only containing non-zero elements with index information, and with a standard format **COO**, it uses **(sizeof(double) + sizeof(int32_t) + sizeof(int32_t)) * number of non-zero** bytes in memory space.

- Also, the iteration process can be reduced from **column * row** to **number of non-zero**.

  

## About directories
- The project contains following directories.
  - include : Contains header files for the project
  - src : Contains header files for the project
  - obj: Directory to separate object files from compilation process
  - func_confirm: Directory contains .cpp file for function test
  - performance_test : Directory contains code file for performantce test



## To compile the code
> For **main** - In **workspace** or **CSE701_Project_02** directory, type
>
> ```bash
> make main_lin // for Linux
> make main_win // for Windows
> ```
>
> This will generate **proj_r.out**  or  **proj_r.exe** file at **workspace** or **CSE701_Project_02** directory.

> For **function validation** - In **CSE701_Project_02/func_confirm** directory, type
>
> ```bash
> make run_test // for Linux
> ```
>
> This will automatically create validation process file, run the test and **delete** the validation file if the validation process done **successfully**.

> For **performance test** - In **CSE701_Project_02/performance_test** directory, type
>
> ```bash
> make perforance // for Linux
> ```
>
> This will generate **performance.out**



## To use proj_r.out
> In **workspace** or **CSE701_Project_01** directory, after generating **proj_r.out**, type
>
> ```bash
> ./proj_r.out operation input_one input_two
> ```
>
> **NOTE**
>  - following inputs can be used
> ```bash
> ./proj_r.out SpMV sample_mtx.mtx sample_dvec.dvec
> ./proj_r.out SpMV_T sample_mtx.mtx sample_dvec.dvec
> 
> ./proj_r.out SpM_SpV sample_mtx.mtx sample_svec.svec
> ./proj_r.out SpM_SpV_T sample_mtx.mtx sample_svec.svec
> 
> ./proj_r.out SpM_SpM sample_mtx.mtx sample_mtx.mtx
> ./proj_r.out SpM_SpM_T sample_mtx.mtx sample_mtx.mtx
> ```
>
> - example
> ```bash
> INPUT - ./proj_r.out SpMV sample_mtx.mtx sample_dvec.dvec
> INPUT - ./proj_r.out SpM_SpV sample_mtx.mtx sample_svec.svec
> Return - 87.00 6.00 54.00 16.00 36.00 54.00 70.00 70.00 173.00 0.00
> 
> INPUT - ./proj_r.out SpMV_T sample_mtx.mtx sample_dvec.dvec
> INPUT - ./proj_r.out SpM_SpV_T sample_mtx.mtx sample_svec.svec
> Return - 1.00 18.00 0.00 20.00 55.00 54.00 126.00 96.00 63.00 90.00
> ```
> 
>   
>   - About the operations
> 
>     - Currently, computation operation is done by using CSR - Compressed Sparse Row format for performance issues..
>   - Computation operations for COO - Coordinates format and CSC - Compressed Sparse Column format are implemented, but not used in the computation process.
>   - The operation of unused computation functions is confirmed by the separated functional testing process.



## To use performance.out

> In CSE701_Project_02/performance_test, after generating **performance.out**,
>
> Under CSE701_Project_02/performance_test/sample_data, place wanted square and integer/real valued spare matrix from [SuiteSparse Matrix Collection](https://sparse.tamu.edu/) and then tpye following
>
> ```bash
> ./performance.out
> ```
>
> **NOTE**
>
>  - following is example output
>
> ```bash
> Proceed - name of matrix used.mtx
> Uint - microsecond
> 
> Matrix Name  : name of matrix used.mtx
> Num Row      : 365344
> Num Column   : 365344
> Num Nz       : 884120
> 
>             SpMV        SpMV_T      SpM_SpV     SpM_SpV_T
> COO         2.89e+03    2.45e+03    2.86e+03    3.27e+03
> CSC         5.12e+03    4.25e+03    7.91e+03    7.15e+03
> CSR         5.04e+03    4.61e+03    7.12e+03    7.18e+03
> FCOO        2.49e+03    7.79e+03    3.33e+03    5.22e+03
> FCSC        4.93e+03    1.48e+05    7.37e+03    1.44e+05
> FCSR        2.40e+03    6.30e+03    2.91e+03    5.45e+03
> ```
>



## To validate operations
> Under CSE701_Project_02/ **func_confirm** directory, type
> 
>```bash
> make run_test
>```

> **NOTE**
>
> - The tests checks following operations
>   - Matrix I/O operations
>   - Matrix converting operations
>   - Arithmetic operations with COO/CSC/CSR
>   - Arithmetic operations with simplified COO/CSC/CSR
>   - Random sparse matrix, dense vector, and sparse vector generating process

> - The process must be done when there are modifications in the listed operations to check the updates do not make bugs.
>- The new operations need to be added to the process when a new operation is added to the listed operations.



## About the non-standard input format
> - Non-standard input format **.dvec** and **.svec** are designed for this project
>
> > - **.dvec**
> >   - It is designed for denoting **dense vector**.
> >
> >   - The first element in the file denotes **length of vector**.
> >
> >   - The remaining elements in the file denote **elements** in the vector.
> >
> >   - To load **length of vector** by **fscanf()**, **%d** needs to be used.
> >
> >   - To load **element** by **fscanf()**, **%lg** needs to be used.
> >
> >   - To generate **.dvec** file for operation, do the followings
> >
> >   - Generate **.txt**, write contents as follow and change the format into **.dvec**
> >
> >   >```.txt
> >   > 7
> >   > 0
> >   > 3
> >   > 1
> >   > 2
> >   > 5
> >   > 5
> >   > 8
> >   >```
> >   >
> >   The above example represents dense vector with
> >   - Vector length : 7
> >   - Value : 0 3 1 2 5 5 8
> > 
> >
> > - **.svec**
> >   
> > - It is designed for denoting **sparse vector**.
> >   
> > - The first two elements in the file denotes **number of none zero** and **length of vector**.
> >   
> > - The remaining elements in the file denote **index** and **elements** in the vector.
> >   
> > - To load **number of none zero**, **length of vector** and **index** by **fscanf()**, **%d** needs to be used.
> >   
> > - To load **element** by **fscanf()**, **%lg** needs to be used.
> >   
> > - To generate **.svec** file for operation, do the followings
> >   
> > - Generate **.txt**, write contents as follow and change the format into **.dvec**
> >   
> >   >```.txt
> >   >10 8
> >   >1 1
> >   >2 3
> >   >4 4
> >   >5 6
> >   >6 9
> >   >7 10
> >   >8 5
> >   >9 7
> >   >```
> >   >
> >   The above example represents sparse vector with
> >   - Vector length : 10
> >   - Number of none zero : 8
> >   - Index :  8 1 2 4 5 6  7 8 9
> >   - Value : 10 1 3 4 6 9 10 5 7