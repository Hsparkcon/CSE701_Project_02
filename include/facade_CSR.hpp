#pragma once
#include "matrix_struct.hpp"
#include "operation_CSR.hpp"

class facade_CSR : private OPERATION_CSR
{
public:
    facade_CSR();

    facade_CSR(const CSR &mat_A);

    facade_CSR(COO &mat_A);

    facade_CSR(CSC &mat_A);

    facade_CSR(const std::vector<uint32_t> row_idx, const std::vector<uint32_t> col_idx, const std::vector<double> val, const uint32_t num_row, const uint32_t num_col);

    virtual ~facade_CSR();

    CSR get_mat_A() const;

    void set_mat_A(COO &mat_A);

    COO to_COO();

    CSC to_CSC();

    CSR transpose();

    bool compare(const CSR &target);

    bool compare(const facade_CSR &target);

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

    CSR &operator()();

    bool operator==(const CSR &target);

    bool operator!=(const CSR &target);

    bool operator==(const facade_CSR &target);

    bool operator!=(const facade_CSR &target);

private:
    CSR m_mat_A;
    MATRIX_ALLOCATION m_alloc;
    MATRIX_CONVERT m_convert;
};