INC_DIR = ../include/
SRC_DIR = ../src/
OBJ_DIR = ../obj/

CC = g++
#CFLAGS = -Wall -Wextra -Wconversion -Wpedantic -Wno-unused-result -Wno-unused-parameter -std=c++20 -O2
CFLAGS = -Wall -Wextra -Wconversion -Wno-unused-result -Wno-unused-parameter -std=c++20 -O2


#Compile DATA-I/O
io_data.o : $(SRC_DIR)io_data.cpp $(INC_DIR)io_data.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)io_data.cpp  -o $(OBJ_DIR)io_data.o

read_mtx.o : $(SRC_DIR)read_mtx.cpp $(INC_DIR)read_mtx.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)read_mtx.cpp -o $(OBJ_DIR)read_mtx.o

read_dmat.o : $(SRC_DIR)read_dmat.cpp $(INC_DIR)read_dmat.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)read_dmat.cpp -o $(OBJ_DIR)read_dmat.o

read_dvec.o : $(SRC_DIR)read_dvec.cpp $(INC_DIR)read_dvec.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)read_dvec.cpp -o $(OBJ_DIR)read_dvec.o

read_svec.o : $(SRC_DIR)read_svec.cpp $(INC_DIR)read_svec.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)read_svec.cpp -o $(OBJ_DIR)read_svec.o

write_mtx.o : $(SRC_DIR)write_mtx.cpp $(INC_DIR)write_mtx.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)write_mtx.cpp -o $(OBJ_DIR)write_mtx.o

write_dvec.o : $(SRC_DIR)write_dvec.cpp $(INC_DIR)write_dvec.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)write_dvec.cpp -o $(OBJ_DIR)write_dvec.o

write_svec.o : $(SRC_DIR)write_svec.cpp $(INC_DIR)write_svec.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)write_svec.cpp -o $(OBJ_DIR)write_svec.o


#Compile Basic requirments
input_validator.o : $(SRC_DIR)input_validator.cpp $(INC_DIR)input_validator.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)input_validator.cpp -o $(OBJ_DIR)input_validator.o

matrix_allocation.o : $(SRC_DIR)matrix_allocation.cpp $(INC_DIR)matrix_allocation.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_allocation.cpp -o $(OBJ_DIR)matrix_allocation.o

matrix_print.o : $(SRC_DIR)matrix_print.cpp $(INC_DIR)matrix_print.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_print.cpp -o $(OBJ_DIR)matrix_print.o

matrix_convert.o : $(SRC_DIR)matrix_convert.cpp $(INC_DIR)matrix_convert.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_convert.cpp -o $(OBJ_DIR)matrix_convert.o

matrix_rand.o : $(SRC_DIR)matrix_rand.cpp $(INC_DIR)matrix_rand.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_rand.cpp -o $(OBJ_DIR)matrix_rand.o



#Compile Sparse Operations
operation_list.o : $(SRC_DIR)operation_list.cpp $(INC_DIR)operation_list.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)operation_list.cpp -o $(OBJ_DIR)operation_list.o

operation_COO.o : $(SRC_DIR)operation_COO.cpp $(INC_DIR)operation_COO.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)operation_COO.cpp -o $(OBJ_DIR)operation_COO.o

operation_CSC.o : $(SRC_DIR)operation_CSC.cpp $(INC_DIR)operation_CSC.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)operation_CSC.cpp -o $(OBJ_DIR)operation_CSC.o

operation_CSR.o : $(SRC_DIR)operation_CSR.cpp $(INC_DIR)operation_CSR.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)operation_CSR.cpp -o $(OBJ_DIR)operation_CSR.o



#Compile FACADE version
facade_COO.o : $(SRC_DIR)facade_COO.cpp $(INC_DIR)facade_COO.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)facade_COO.cpp -o $(OBJ_DIR)facade_COO.o

facade_CSC.o : $(SRC_DIR)facade_CSC.cpp $(INC_DIR)facade_CSC.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)facade_CSC.cpp -o $(OBJ_DIR)facade_CSC.o

facade_CSR.o : $(SRC_DIR)facade_CSR.cpp $(INC_DIR)facade_CSR.hpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)facade_CSR.cpp -o $(OBJ_DIR)facade_CSR.o



#Compile Validation Code
confirm_convertor: matrix_convert.o matrix_allocation.o
	$(CC) $(CFLAGS) $(OBJ_DIR)matrix_convert.o $(OBJ_DIR)matrix_allocation.o confirm_convertor.cpp -o confirm_convertor.out

confirm_coo: matrix_convert.o matrix_allocation.o operation_list.o operation_COO.o
	$(CC) $(CFLAGS) $(OBJ_DIR)matrix_convert.o $(OBJ_DIR)matrix_allocation.o $(OBJ_DIR)operation_list.o $(OBJ_DIR)operation_COO.o confirm_coo.cpp -o confirm_coo.out

confirm_csc: matrix_convert.o matrix_allocation.o operation_list.o operation_CSC.o 
	$(CC) $(CFLAGS) $(OBJ_DIR)matrix_convert.o $(OBJ_DIR)matrix_allocation.o $(OBJ_DIR)operation_list.o $(OBJ_DIR)operation_CSC.o confirm_csc.cpp -o confirm_csc.out

confirm_csr: matrix_convert.o matrix_allocation.o operation_list.o operation_CSR.o 
	$(CC) $(CFLAGS) $(OBJ_DIR)matrix_convert.o $(OBJ_DIR)matrix_allocation.o $(OBJ_DIR)operation_list.o $(OBJ_DIR)operation_CSR.o confirm_csr.cpp -o confirm_csr.out

confirm_facade_COO: matrix_convert.o matrix_allocation.o operation_list.o operation_COO.o facade_COO.o 
	$(CC) $(CFLAGS) $(OBJ_DIR)matrix_convert.o $(OBJ_DIR)matrix_allocation.o $(OBJ_DIR)operation_list.o $(OBJ_DIR)operation_COO.o $(OBJ_DIR)facade_COO.o confirm_facade_COO.cpp -o confirm_facade_COO.out

confirm_facade_CSC: matrix_convert.o matrix_allocation.o operation_list.o operation_CSC.o facade_CSC.o
	$(CC) $(CFLAGS) $(OBJ_DIR)matrix_convert.o $(OBJ_DIR)matrix_allocation.o $(OBJ_DIR)operation_list.o $(OBJ_DIR)operation_CSC.o $(OBJ_DIR)facade_CSC.o confirm_facade_CSC.cpp -o confirm_facade_CSC.out

confirm_facade_CSR: matrix_convert.o matrix_allocation.o operation_list.o operation_CSR.o facade_CSR.o
	$(CC) $(CFLAGS) $(OBJ_DIR)matrix_convert.o $(OBJ_DIR)matrix_allocation.o $(OBJ_DIR)operation_list.o $(OBJ_DIR)operation_CSR.o $(OBJ_DIR)facade_CSR.o confirm_facade_CSR.cpp -o confirm_facade_CSR.out

confirm_io_data: io_data.o read_mtx.o read_dmat.o read_dvec.o read_svec.o write_mtx.o write_dvec.o write_svec.o
	$(CC) $(CFLAGS) $(OBJ_DIR)io_data.o $(OBJ_DIR)read_mtx.o $(OBJ_DIR)read_dmat.o $(OBJ_DIR)read_dvec.o $(OBJ_DIR)read_svec.o $(OBJ_DIR)write_mtx.o $(OBJ_DIR)write_dvec.o $(OBJ_DIR)write_svec.o confirm_io_data.cpp -o confirm_io_data.out

confirm_randgen: matrix_allocation.o matrix_rand.o
	$(CC) $(CFLAGS) $(OBJ_DIR)matrix_allocation.o $(OBJ_DIR)matrix_rand.o confirm_randgen.cpp -o confirm_randgen.out


TEST_LIST := confirm_convertor $\
			 confirm_coo confirm_csc confirm_csr $\
			 confirm_facade_COO confirm_facade_CSC confirm_facade_CSR $\
			 confirm_io_data confirm_randgen

run_test: $(TEST_LIST)
	./confirm_convertor.out
	./confirm_coo.out
	./confirm_csc.out
	./confirm_csr.out
	./confirm_facade_COO.out 
	./confirm_facade_CSC.out 
	./confirm_facade_CSR.out
	./confirm_io_data.out 
	./confirm_randgen.out
	rm confirm_convertor.out
	rm confirm_coo.out
	rm confirm_csc.out
	rm confirm_csr.out
	rm confirm_facade_COO.out 
	rm confirm_facade_CSC.out 
	rm confirm_facade_CSR.out
	rm confirm_io_data.out 
	rm confirm_randgen.out
	rm val_mtx.mtx
	rm val_svec.svec
	rm val_dvec.dvec