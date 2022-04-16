#include "include/input_validator.hpp"
#include "include/operation_COO.hpp"
#include "include/operation_CSC.hpp"
#include "include/operation_CSR.hpp"
#include "include/io_data.hpp"
#include "include/matrix_allocation.hpp"
#include "include/matrix_print.hpp"

int main(int argc, char *argv[])
{
    if (argc < 4 || argc > 4)
    {
        std::cout << argc << std::endl;

        std::cout << "The program is designed to compute Sparse Matrix related computation.\n\n"
                     "First Input\n"
                     "\tSpMV\t\t Sparse Matrix * Dense Vector\n"
                     "\tSpMV_T\t\t transpose(Sparse Matrix) * Dense Vector\n"

                     "\tSpMM\t\t Sparse Matrix * Dense Matrix\n"
                     "\tSpMM_T\t\t transpose(Sparse Matrix) * Dense Matrix\n"

                     "\tSpM_SpV\t\t Sparse Matrix * Sparse Vector\n"
                     "\tSpM_SpV_t\t transpose(Sparse Matrix) * Sparse Vector\n"

                     "\tSpM_SpM\t\t Sparse Matrix * Sparse Matrix\n"
                     "\tSpM_SpM_t\t transpose(Sparse Matrix) * Sparse Matrix\n\n"

                     "Second Input\n"
                     "\tPath to .mtx format sparse matrix file.\n\n"

                     "Third Input\n"
                     "\tPath to the second file, which matches with the operation.\n\n"
                  << std::endl;

        std::cout << "Example Input\n"
                     "\tproj_r.out SpMV\t\t sample_mat.mtx sample_vec.dvec\n"
                     "\tproj_r.out SpMV_T\t sample_mat.mtx sample_vec.dvec\n"
                     "\tproj_r.out SpM_SpV\t sample_one.mtx sample_vec.svec\n"
                     "\tproj_r.out SpM_SpV_T\t sample_one.mtx sample_vec.svec\n"
                     "\tproj_r.out SpM_SpM\t Transpose-Sparse Matrix * Sparse Matrix\n"
                     "\tproj_r.out SpM_SpM_T\t Transpose-Sparse Matrix * Sparse Matrix\n"
                  << std::endl;
        return 0;
    }

    INPUT_VALIDATOR validator(argv[1], argv[2], argv[3]);

    try
    {
        validator.validate_arguments();
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Argument error\n"
                  << e.what() << "\n"
                  << std::endl;
        exit(1);
    }

    MATRIX_ALLOCATION alloc;
    MATRIX_CONVERT convertor;
    IO_DATA data_io(IO_MODE::UNSAFE);

    COO input_one_coo;
    CSR input_one_csr;
    D_VECTOR input_two_dvec;
    S_VECTOR input_two_svec;
    D_MATRIX input_two_dmat;
    COO input_two_coo;
    CSR input_two_csr;

    D_VECTOR vec_result;
    D_MATRIX mat_result;
    COO result_coo;

    data_io.load_mat(argv[2], input_one_coo);
    convertor.convert(input_one_coo, input_one_csr);
    alloc.delete_mat(input_one_coo);

    OPERATION_CSR csr_oper;
    switch (validator.get_targeted_operation())
    {
    case INPUT_VALIDATOR::target_operation::SpMV:
        data_io.load_vec(argv[3], input_two_dvec);
        alloc.alloc_vec(input_two_dvec.vec_data.len_vec, "SpMV", vec_result);
        csr_oper.SpMV(input_one_csr, input_two_dvec, vec_result);
        print_vec(vec_result);
        break;

    case INPUT_VALIDATOR::target_operation::SpMV_T:
        data_io.load_vec(argv[3], input_two_dvec);
        alloc.alloc_vec(input_two_dvec.vec_data.len_vec, "SpMV_T", vec_result);
        csr_oper.SpMV_T(input_one_csr, input_two_dvec, vec_result);
        print_vec(vec_result);
        break;

    case INPUT_VALIDATOR::target_operation::SpMM:
        data_io.load_mat(argv[3], input_two_dmat);
        alloc.alloc_mat(input_one_csr.mat_data.num_row, input_two_dmat.mat_data.num_col, "SpMM", mat_result);
        csr_oper.SpMM(input_one_csr, input_two_dmat, mat_result);
        convertor.convert(mat_result, result_coo);
        print_mat(result_coo);
        break;

    case INPUT_VALIDATOR::target_operation::SpMM_T:
        data_io.load_mat(argv[3], input_two_dmat);
        alloc.alloc_mat(input_one_csr.mat_data.num_col, input_two_dmat.mat_data.num_col, "SpMM_T", mat_result);
        csr_oper.SpMM_T(input_one_csr, input_two_dmat, mat_result);
        convertor.convert(mat_result, result_coo);
        print_mat(result_coo);
        break;

    case INPUT_VALIDATOR::target_operation::SpM_SpV:
        data_io.load_vec(argv[3], input_two_svec);
        alloc.alloc_vec(input_two_svec.vec_data.len_vec, "SpM_SpV", vec_result);
        csr_oper.SpM_SpV(input_one_csr, input_two_svec, vec_result);
        print_vec(vec_result);
        break;

    case INPUT_VALIDATOR::target_operation::SpM_SpV_T:
        data_io.load_vec(argv[3], input_two_svec);
        alloc.alloc_vec(input_two_svec.vec_data.len_vec, "SpM_SpV_T", vec_result);
        csr_oper.SpM_SpV_T(input_one_csr, input_two_svec, vec_result);
        print_vec(vec_result);
        break;

    case INPUT_VALIDATOR::target_operation::SpM_SpM:
        data_io.load_mat(argv[3], input_two_coo);
        convertor.convert(input_two_coo, input_two_csr);
        alloc.delete_mat(input_two_coo);
        alloc.alloc_mat(input_one_csr.mat_data.num_row, input_two_csr.mat_data.num_col, "SpM_SpM", mat_result);
        csr_oper.SpM_SpM(input_one_csr, input_two_csr, mat_result);
        convertor.convert(mat_result, result_coo);
        print_mat(result_coo);
        break;

    case INPUT_VALIDATOR::target_operation::SpM_SpM_T:
        data_io.load_mat(argv[3], input_two_coo);
        convertor.convert(input_two_coo, input_two_csr);
        alloc.delete_mat(input_two_coo);
        alloc.alloc_mat(input_one_csr.mat_data.num_row, input_two_csr.mat_data.num_col, "SpM_SpM", mat_result);
        csr_oper.SpM_SpM_T(input_one_csr, input_two_csr, mat_result);
        convertor.convert(mat_result, result_coo);
        print_mat(result_coo);
        break;
    }

    return 0;
}