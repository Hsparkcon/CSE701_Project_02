#pragma once
#include <cassert>
#include "../include/PCH.hpp"
#include "../include/matrix_struct.hpp"

// TEST CASES
// TEST MATRIX INFO
MATRIX_INFO sample_mat_data = (MATRIX_INFO){"test_case", 10, 10, 18};

D_MATRIX sample_d_mat{
    sample_mat_data,
    (std::vector<std::vector<double>>){
        {1, 0, 0, 4, 0, 0, 7, 0, 0, 0},
        {0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 3, 0, 0, 6, 0, 0, 0, 0},
        {0, 0, 0, 4, 0, 0, 0, 0, 0, 0},
        {0, 2, 0, 0, 5, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 6, 0, 0, 0, 10},
        {0, 0, 0, 0, 0, 0, 7, 0, 0, 0},
        {0, 0, 0, 0, 5, 0, 0, 8, 0, 0},
        {0, 0, 0, 0, 0, 0, 7, 8, 9, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 10}}};

// TEST for COO, CSR and CSC
COO sample_coo{
    sample_mat_data,
    (std::vector<MAT_ELE_DATA>){
        {0, 0, 1}, {0, 3, 4}, {0, 6, 7}, {1, 1, 2}, {2, 2, 3}, {2, 5, 6}, {3, 3, 4}, {4, 1, 2}, {4, 4, 5}, {5, 5, 6}, {5, 9, 10}, {6, 6, 7}, {7, 4, 5}, {7, 7, 8}, {8, 6, 7}, {8, 7, 8}, {8, 8, 9}, {9, 9, 10}}};

CSR sample_csr{
    sample_mat_data,
    std::vector<uint32_t>{0, 3, 4, 6, 7, 9, 11, 12, 14, 17, 18},
    std::vector<IDX_VAL>{
        {0, 1}, {3, 4}, {6, 7}, {1, 2}, {2, 3}, {5, 6}, {3, 4}, {1, 2}, {4, 5}, {5, 6}, {9, 10}, {6, 7}, {4, 5}, {7, 8}, {6, 7}, {7, 8}, {8, 9}, {9, 10}}};

CSC sample_csc{
    sample_mat_data,
    std::vector<uint32_t>{0, 1, 3, 4, 6, 8, 10, 13, 15, 16, 18},
    std::vector<IDX_VAL>{
        {0, 1}, {1, 2}, {4, 2}, {2, 3}, {0, 4}, {3, 4}, {4, 5}, {7, 5}, {2, 6}, {5, 6}, {0, 7}, {6, 7}, {8, 7}, {7, 8}, {8, 8}, {8, 9}, {5, 10}, {9, 10}}};

// TESTING MATRIX * VECTOR MULTIPLICATION
VECTOR_INFO sample_vec_data = (VECTOR_INFO){"Sample_Vector", 10, 8};
D_VECTOR sample_d_vec{
    sample_vec_data,
    std::vector<double>{1, 3, 0, 4, 6, 9, 10, 5, 7, 0}};

S_VECTOR sample_s_vec{
    sample_vec_data,
    std::vector<IDX_VAL>{
        {0, 1}, {1, 3}, {3, 4}, {4, 6}, {5, 9}, {6, 10}, {7, 5}, {8, 7}}};

//// DESIRED RESULTS
std::vector<double> desired_spmv_result{
    87, 6, 54, 16, 36, 54, 70, 70, 173, 0};

std::vector<double> desired_spmv_t_result{
    1, 18, 0, 20, 55, 54, 126, 96, 63, 90};

// TESTING MATRIX * MATRIX MULTIPLICATION
std::vector<std::vector<double>> desired_spmm_result{
    {1, 0, 0, 20, 0, 0, 56, 0, 0, 0},
    {0, 4, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 9, 0, 0, 54, 0, 0, 0, 60},
    {0, 0, 0, 16, 0, 0, 0, 0, 0, 0},
    {0, 14, 0, 0, 25, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 36, 0, 0, 0, 160},
    {0, 0, 0, 0, 0, 0, 49, 0, 0, 0},
    {0, 10, 0, 0, 65, 0, 0, 64, 0, 0},
    {0, 0, 0, 0, 40, 0, 112, 136, 81, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 100}};

std::vector<std::vector<double>> desired_spmm_t_result{
    {1, 0, 0, 4, 0, 0, 7, 0, 0, 0},
    {0, 8, 0, 0, 10, 0, 0, 0, 0, 0},
    {0, 0, 9, 0, 0, 18, 0, 0, 0, 0},
    {4, 0, 0, 32, 0, 0, 28, 0, 0, 0},
    {0, 10, 0, 0, 50, 0, 0, 40, 0, 0},
    {0, 0, 18, 0, 0, 72, 0, 0, 0, 60},
    {7, 0, 0, 28, 0, 0, 147, 56, 63, 0},
    {0, 0, 0, 0, 40, 0, 56, 128, 72, 0},
    {0, 0, 0, 0, 0, 0, 63, 72, 81, 0},
    {0, 0, 0, 0, 0, 60, 0, 0, 0, 200}};

// Validation function
void check_D_VECTOR_result(D_VECTOR &result, std::vector<double> &expected_result)
{
    for (uint32_t iter_d_vec = 0; iter_d_vec < result.vec_data.len_vec; iter_d_vec++)
    {
        assert((int32_t)result.vec_element[iter_d_vec] == (int32_t)expected_result[iter_d_vec]);
    }
}

void check_D_MATRIX_result(D_MATRIX &result, std::vector<std::vector<double>> &expected_result)
{
    for (uint32_t iter_row = 0; iter_row < result.mat_data.num_row; iter_row++)
    {
        for (uint32_t iter_col = 0; iter_col < result.mat_data.num_col; iter_col++)
        {
            assert((int32_t)result.matrix[iter_row][iter_col] == (int32_t)expected_result[iter_row][iter_col]);
        }
    }
}
