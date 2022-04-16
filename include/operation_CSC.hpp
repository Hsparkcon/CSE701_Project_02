#pragma once
#include "operation_list.hpp"

class OPERATION_CSC : public OPERATION_LIST
{
public:
    OPERATION_CSC();
    virtual ~OPERATION_CSC();

    void SpMV(const CSC &mat_A, const D_VECTOR &vec_x, D_VECTOR &vec_b);

    void SpMV_T(const CSC &mat_A, const D_VECTOR &vec_x, D_VECTOR &vec_b);

    void SpMM(const CSC &mat_A, const D_MATRIX &mat_X, D_MATRIX &mat_B);

    void SpMM_T(const CSC &mat_A, const D_MATRIX &mat_X, D_MATRIX &mat_B);

    void SpM_SpV(const CSC &mat_A, const S_VECTOR &vec_x, D_VECTOR &vec_b);

    void SpM_SpV_T(const CSC &mat_A, const S_VECTOR &vec_x, D_VECTOR &vec_b);

    void SpM_SpM(const CSC &mat_A, const CSR &mat_X, D_MATRIX &mat_B);

    void SpM_SpM(const CSC &mat_A, const CSC &mat_X, D_MATRIX &mat_B);

    void SpM_SpM_T(const CSC &mat_A, const CSR &mat_X, D_MATRIX &mat_B);

    void SpM_SpM_T(const CSC &mat_A, const CSC &mat_X, D_MATRIX &mat_B);

private:
};

D_VECTOR operator*(const CSC &mat_A, const D_VECTOR &vec_x);

D_VECTOR operator*(const CSC &mat_A, const S_VECTOR &vec_x);

D_MATRIX operator*(const CSC &mat_A, const D_MATRIX &mat_X);

D_MATRIX operator*(const CSC &mat_A, const CSC &mat_X);

D_MATRIX operator*(const CSC &mat_A, const CSR &mat_X);