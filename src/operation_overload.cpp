#include "../include/operation_overload.hpp"

D_VECTOR operator*(const COO &mat_A, const D_VECTOR &vec_x)
{
    OPERATION_COO oper_coo;
    MATRIX_ALLOCATION alloc_mat;
    D_VECTOR vec_b;
    alloc_mat.alloc_vec(vec_x.vec_data.len_vec, "Result", vec_b);
    oper_coo.SpMV(mat_A, vec_x, vec_b);
    return vec_b;
}

D_VECTOR operator*(const COO &mat_A, const S_VECTOR &vec_x)
{
    OPERATION_COO oper_coo;
    MATRIX_ALLOCATION alloc_mat;
    D_VECTOR vec_b;
    alloc_mat.alloc_vec(vec_x.vec_data.len_vec, "Result", vec_b);
    oper_coo.SpM_SpV(mat_A, vec_x, vec_b);
    return vec_b;
}

D_MATRIX operator*(const COO &mat_A, const D_MATRIX &mat_X)
{
    OPERATION_COO oper_coo;
    MATRIX_ALLOCATION alloc_mat;
    D_MATRIX mat_B;
    alloc_mat.alloc_mat(mat_A.mat_data.num_row, mat_X.mat_data.num_col, "Result", mat_B);
    oper_coo.SpMM(mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX operator*(const COO &mat_A, const CSC &mat_X)
{
    OPERATION_COO oper_coo;
    MATRIX_ALLOCATION alloc_mat;
    D_MATRIX mat_B;
    alloc_mat.alloc_mat(mat_A.mat_data.num_row, mat_X.mat_data.num_col, "Result", mat_B);
    oper_coo.SpM_SpM(mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX operator*(const COO &mat_A, const CSR &mat_X)
{
    OPERATION_COO oper_coo;
    MATRIX_ALLOCATION alloc_mat;
    D_MATRIX mat_B;
    alloc_mat.alloc_mat(mat_A.mat_data.num_row, mat_X.mat_data.num_col, "Result", mat_B);
    oper_coo.SpM_SpM(mat_A, mat_X, mat_B);
    return mat_B;
}

D_VECTOR operator*(const CSC &mat_A, const D_VECTOR &vec_x)
{
    OPERATION_CSC oper_csc;
    MATRIX_ALLOCATION alloc_mat;
    D_VECTOR vec_b;
    alloc_mat.alloc_vec(vec_x.vec_data.len_vec, "Result", vec_b);
    oper_csc.SpMV(mat_A, vec_x, vec_b);
    return vec_b;
}

D_VECTOR operator*(const CSC &mat_A, const S_VECTOR &vec_x)
{
    OPERATION_CSC oper_csc;
    MATRIX_ALLOCATION alloc_mat;
    D_VECTOR vec_b;
    alloc_mat.alloc_vec(vec_x.vec_data.len_vec, "Result", vec_b);
    oper_csc.SpM_SpV(mat_A, vec_x, vec_b);
    return vec_b;
}

D_MATRIX operator*(const CSC &mat_A, const D_MATRIX &mat_X)
{
    OPERATION_CSC oper_csc;
    MATRIX_ALLOCATION alloc_mat;
    D_MATRIX mat_B;
    alloc_mat.alloc_mat(mat_A.mat_data.num_row, mat_X.mat_data.num_col, "Result", mat_B);
    oper_csc.SpMM(mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX operator*(const CSC &mat_A, const CSC &mat_X)
{
    OPERATION_CSC oper_csc;
    MATRIX_ALLOCATION alloc_mat;
    D_MATRIX mat_B;
    alloc_mat.alloc_mat(mat_A.mat_data.num_row, mat_X.mat_data.num_col, "Result", mat_B);
    oper_csc.SpM_SpM(mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX operator*(const CSC &mat_A, const CSR &mat_X)
{
    OPERATION_CSC oper_csc;
    MATRIX_ALLOCATION alloc_mat;
    D_MATRIX mat_B;
    alloc_mat.alloc_mat(mat_A.mat_data.num_row, mat_X.mat_data.num_col, "Result", mat_B);
    oper_csc.SpM_SpM(mat_A, mat_X, mat_B);
    return mat_B;
}

D_VECTOR operator*(const CSR &mat_A, const D_VECTOR &vec_x)
{
    OPERATION_CSR oper_csr;
    MATRIX_ALLOCATION alloc_mat;
    D_VECTOR vec_b;
    alloc_mat.alloc_vec(vec_x.vec_data.len_vec, "Result", vec_b);
    oper_csr.SpMV(mat_A, vec_x, vec_b);
    return vec_b;
}

D_VECTOR operator*(const CSR &mat_A, const S_VECTOR &vec_x)
{
    OPERATION_CSR oper_csr;
    MATRIX_ALLOCATION alloc_mat;
    D_VECTOR vec_b;
    alloc_mat.alloc_vec(vec_x.vec_data.len_vec, "Result", vec_b);
    oper_csr.SpM_SpV(mat_A, vec_x, vec_b);
    return vec_b;
}

D_MATRIX operator*(const CSR &mat_A, const D_MATRIX &mat_X)
{
    OPERATION_CSR oper_csr;
    MATRIX_ALLOCATION alloc_mat;
    D_MATRIX mat_B;
    alloc_mat.alloc_mat(mat_A.mat_data.num_row, mat_X.mat_data.num_col, "Result", mat_B);
    oper_csr.SpMM(mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX operator*(const CSR &mat_A, const CSC &mat_X)
{
    OPERATION_CSR oper_csr;
    MATRIX_ALLOCATION alloc_mat;
    D_MATRIX mat_B;
    alloc_mat.alloc_mat(mat_A.mat_data.num_row, mat_X.mat_data.num_col, "Result", mat_B);
    oper_csr.SpM_SpM(mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX operator*(const CSR &mat_A, const CSR &mat_X)
{
    OPERATION_CSR oper_csr;
    MATRIX_ALLOCATION alloc_mat;
    D_MATRIX mat_B;
    alloc_mat.alloc_mat(mat_A.mat_data.num_row, mat_X.mat_data.num_col, "Result", mat_B);
    oper_csr.SpM_SpM(mat_A, mat_X, mat_B);
    return mat_B;
}
