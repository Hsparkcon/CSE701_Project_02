INC_DIR = include/
SRC_DIR = src/
OBJ_DIR = obj/

CC = g++
CFLAGS = -Wall -Wextra -Wconversion -Wpedantic -Wno-unused-result -Wno-unused-parameter -std=c++20 -O2

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


# Compile main contenst
main_component := io_data.o read_mtx.o read_dmat.o read_dvec.o read_svec.o write_mtx.o write_dvec.o write_svec.o $\
input_validator.o matrix_allocation.o matrix_print.o matrix_convert.o matrix_rand.o $\
operation_list.o operation_COO.o operation_CSC.o operation_CSR.o 

main_component_OBJ := $\
$(OBJ_DIR)io_data.o $(OBJ_DIR)read_mtx.o $(OBJ_DIR)read_dmat.o $(OBJ_DIR)read_dvec.o $(OBJ_DIR)read_svec.o $(OBJ_DIR)write_mtx.o $(OBJ_DIR)write_dvec.o $(OBJ_DIR)write_svec.o $\
$(OBJ_DIR)input_validator.o $(OBJ_DIR)matrix_allocation.o $(OBJ_DIR)matrix_print.o $(OBJ_DIR)matrix_convert.o $(OBJ_DIR)matrix_rand.o $\
$(OBJ_DIR)operation_list.o $(OBJ_DIR)operation_COO.o $(OBJ_DIR)operation_CSC.o $(OBJ_DIR)operation_CSR.o

main_lin: $(main_component)
	$(CC) $(CFLAGS) $(main_component_OBJ) main.cpp -o proj_r.out

main_win: $(main_component)
	$(CC) $(CFLAGS) $(main_component_OBJ) main.cpp -o proj_r.exe


