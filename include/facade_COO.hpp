#pragma once
#include "matrix_struct.hpp"
#include "operation_COO.hpp"

class facade_COO : private OPERATION_COO
{
public:
    facade_COO();

    facade_COO(const COO &mat_A);

    facade_COO(CSR &mat_A);

    facade_COO(CSC &mat_A);

    facade_COO(
        const std::vector<uint32_t> &row_idx,
        const std::vector<uint32_t> &col_idx,
        const std::vector<double> &val,
        const uint32_t num_row,
        const uint32_t num_col);

    virtual ~facade_COO();

    COO get_mat_A() const;

    void set_mat_A(const COO& new_COO);

    CSC to_CSC();

    CSR to_CSR();

    COO transpose();

    bool compare(const COO &target);

    bool compare(const facade_COO &target);

    D_VECTOR SpMV(const D_VECTOR &vec_x);

    D_VECTOR SpMV_T(const D_VECTOR &vec_x);

    D_VECTOR SpM_SpV(const S_VECTOR &vec_x);

    D_VECTOR SpM_SpV_T(const S_VECTOR &vec_x);

    D_MATRIX SpMM(const D_MATRIX &mat_X);

    D_MATRIX SpMM_T(const D_MATRIX &mat_X);

    D_MATRIX SpM_SpM(const CSC &mat_X);

    D_MATRIX SpM_SpM_T(const CSC &mat_X);

    D_MATRIX SpM_SpM(const CSR &mat_X);

    D_MATRIX SpM_SpM_T(const CSR &mat_X);

    COO &operator()();

    bool operator==(const COO &target);

    bool operator!=(const COO &target);

    bool operator==(const facade_COO &target);

    bool operator!=(const facade_COO &target);

private:
    COO m_mat_A;
    MATRIX_ALLOCATION m_alloc;
    MATRIX_CONVERT m_convert;
};