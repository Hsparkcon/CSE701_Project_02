#pragma once
#include "matrix_struct.hpp"
#include "operation_CSC.hpp"


class facade_CSC : private OPERATION_CSC
{
public:
    facade_CSC();

    facade_CSC(const CSC &mat_A);

    facade_CSC(COO &mat_A);

    facade_CSC(CSR &mat_A);

    facade_CSC(const std::vector<uint32_t> row_idx, const std::vector<uint32_t> col_idx, const std::vector<double> val, const uint32_t num_row, const uint32_t num_col);
   
    virtual ~facade_CSC();

    CSC get_mat_A() const;

    void set_mat_A(COO &mat_A);

    COO to_COO();

    CSR to_CSR();

    CSC transpose();

    bool compare(const CSC &target);

    bool compare(const facade_CSC &target);

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

    CSC &operator() ();

    bool operator== (const CSC &target);

    bool operator!= (const CSC &target);

    bool operator== (const facade_CSC &target);

    bool operator!= (const facade_CSC &target);

private:
    CSC m_mat_A;
    MATRIX_ALLOCATION m_alloc;
    MATRIX_CONVERT m_convert;
};