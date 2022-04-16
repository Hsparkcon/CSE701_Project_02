#include "test_cases.hpp"
#include "../include/operation_COO.hpp"

int main()
{
    OPERATION_COO test_coo;
    MATRIX_ALLOCATION alloc;

    D_VECTOR vec_result;
    alloc.alloc_vec(sample_d_vec.vec_data.len_vec, "SpMV", vec_result);
    test_coo.SpMV(sample_coo, sample_d_vec, vec_result);
    check_D_VECTOR_result(vec_result, desired_spmv_result);
    alloc.delete_vec(vec_result);

    alloc.alloc_vec(sample_d_vec.vec_data.len_vec, "SpMV_T", vec_result);
    test_coo.SpMV_T(sample_coo, sample_d_vec, vec_result);
    check_D_VECTOR_result(vec_result, desired_spmv_t_result);
    alloc.delete_vec(vec_result);

    alloc.alloc_vec(sample_d_vec.vec_data.len_vec, "SpM_SpV", vec_result);
    test_coo.SpM_SpV(sample_coo, sample_s_vec, vec_result);
    check_D_VECTOR_result(vec_result, desired_spmv_result);
    alloc.delete_vec(vec_result);

    alloc.alloc_vec(sample_d_vec.vec_data.len_vec, "SpM_SpV_T", vec_result);
    test_coo.SpM_SpV_T(sample_coo, sample_s_vec, vec_result);
    check_D_VECTOR_result(vec_result, desired_spmv_t_result);
    alloc.delete_vec(vec_result);

    D_MATRIX mat_result;
    alloc.alloc_mat(sample_coo.mat_data.num_row, sample_coo.mat_data.num_col, "SpMM", mat_result);
    test_coo.SpMM(sample_coo, sample_d_mat, mat_result);
    check_D_MATRIX_result(mat_result, desired_spmm_result);
    alloc.delete_mat(mat_result);

    alloc.alloc_mat(sample_coo.mat_data.num_col, sample_coo.mat_data.num_col, "SpM_SpM_CSR", mat_result);
    test_coo.SpM_SpM(sample_coo, sample_csr, mat_result);
    check_D_MATRIX_result(mat_result, desired_spmm_result);
    alloc.delete_mat(mat_result);

    alloc.alloc_mat(sample_coo.mat_data.num_col, sample_coo.mat_data.num_col, "SpM_SpM_CSC", mat_result);
    test_coo.SpM_SpM(sample_coo, sample_csc, mat_result);
    check_D_MATRIX_result(mat_result, desired_spmm_result);
    alloc.delete_mat(mat_result);

    alloc.alloc_mat(sample_coo.mat_data.num_col, sample_coo.mat_data.num_col, "SpMM_T", mat_result);
    test_coo.SpMM_T(sample_coo, sample_d_mat, mat_result);
    check_D_MATRIX_result(mat_result, desired_spmm_t_result);
    alloc.delete_mat(mat_result);

    alloc.alloc_mat(sample_coo.mat_data.num_col, sample_coo.mat_data.num_col, "SpM_SpM_T_CSR", mat_result);
    test_coo.SpM_SpM_T(sample_coo, sample_csr, mat_result);
    check_D_MATRIX_result(mat_result, desired_spmm_t_result);
    alloc.delete_mat(mat_result);

    alloc.alloc_mat(sample_coo.mat_data.num_col, sample_coo.mat_data.num_col, "SpM_SpM_T_CSR", mat_result);
    test_coo.SpM_SpM_T(sample_coo, sample_csc, mat_result);
    check_D_MATRIX_result(mat_result, desired_spmm_t_result);
    alloc.delete_mat(mat_result);

    std::cout << "Validation for operation_COO complete" << std::endl;

    return 0;
}