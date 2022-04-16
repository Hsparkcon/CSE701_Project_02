#include "../include/operation_CSR.hpp"

OPERATION_CSR::OPERATION_CSR() {}

OPERATION_CSR::~OPERATION_CSR() {}

void OPERATION_CSR::SpMV(const CSR &mat_A, const D_VECTOR &vec_x, D_VECTOR &vec_b)
{
    validate_length(mat_A.mat_data.num_col, vec_x.vec_data.len_vec, is_transpose::NO);

    for (uint32_t row_ptr = 0; row_ptr < mat_A.mat_data.num_row; row_ptr++)
    {
        for (uint32_t idx_nz = mat_A.row_ptr[row_ptr]; idx_nz < mat_A.row_ptr[row_ptr + 1]; idx_nz++)
        {
            vec_b.vec_element[row_ptr] += (mat_A.col_and_val[idx_nz].val *
                                           vec_x.vec_element[mat_A.col_and_val[idx_nz].index]);
        }
    }

    vec_b.vec_data.num_nz = count_nz(vec_b);
}

void OPERATION_CSR::SpMV_T(const CSR &mat_A, const D_VECTOR &vec_x, D_VECTOR &vec_b)
{
    validate_length(mat_A.mat_data.num_row, vec_x.vec_data.len_vec, is_transpose::YES);

    for (uINT row_ptr = 0; row_ptr < mat_A.mat_data.num_row; row_ptr++)
    {
        for (uINT nnz_row = mat_A.row_ptr[row_ptr]; nnz_row < mat_A.row_ptr[row_ptr + 1]; nnz_row++)
        {
            vec_b.vec_element[mat_A.col_and_val[nnz_row].index] += (mat_A.col_and_val[nnz_row].val * vec_x.vec_element[row_ptr]);
        }
    }

    vec_b.vec_data.num_nz = count_nz(vec_b);
}

void OPERATION_CSR::SpMM(const CSR &mat_A, const D_MATRIX &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_col, mat_X.mat_data.num_row, is_transpose::NO);

    for (uINT row_ptr = 0; row_ptr < mat_A.mat_data.num_row; row_ptr++)
    {
        for (uINT nnz_row = mat_A.row_ptr[row_ptr]; nnz_row < mat_A.row_ptr[row_ptr + 1]; nnz_row++)
        {
            for (uINT x_col = 0; x_col < mat_X.mat_data.num_col; x_col++)
            {
                mat_B.matrix[row_ptr][x_col] += (mat_A.col_and_val[nnz_row].val * mat_X.matrix[mat_A.col_and_val[nnz_row].index][x_col]);
            }
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
}

void OPERATION_CSR::SpMM_T(const CSR &mat_A, const D_MATRIX &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_row, mat_X.mat_data.num_row, is_transpose::YES);

    for (uINT row_ptr = 0; row_ptr < mat_A.mat_data.num_row; row_ptr++)
    {
        for (uINT nz_row = mat_A.row_ptr[row_ptr]; nz_row < mat_A.row_ptr[row_ptr + 1]; nz_row++)
        {
            for (uINT x_col = 0; x_col < mat_X.mat_data.num_col; x_col++)
            {
                mat_B.matrix[mat_A.col_and_val[nz_row].index][x_col] += (mat_A.col_and_val[nz_row].val * mat_X.matrix[row_ptr][x_col]);
            }
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
}

void OPERATION_CSR::SpM_SpV(const CSR &mat_A, const S_VECTOR &vec_x, D_VECTOR &vec_b)
{
    validate_length(mat_A.mat_data.num_col, vec_x.vec_data.len_vec, is_transpose::NO);

    for (uINT row_ptr = 0; row_ptr < mat_A.mat_data.num_row; row_ptr++)
    {
        for (uINT nz_row = mat_A.row_ptr[row_ptr]; nz_row < mat_A.row_ptr[row_ptr + 1]; nz_row++)
        {
            uINT target_pos = 0;
            if (bin_search_s_vec(vec_x, mat_A.col_and_val[nz_row].index, target_pos) == true)
            {
                vec_b.vec_element[row_ptr] += (mat_A.col_and_val[nz_row].val * vec_x.vec_element[target_pos].val);
            }
        }
    }
    vec_b.vec_data.num_nz = count_nz(vec_b);
}

void OPERATION_CSR::SpM_SpV_T(const CSR &mat_A, const S_VECTOR &vec_x, D_VECTOR &vec_b)
{
    validate_length(mat_A.mat_data.num_row, vec_x.vec_data.len_vec, is_transpose::YES);

    for (uINT row_ptr = 0; row_ptr < mat_A.mat_data.num_row; row_ptr++)
    {
        for (uINT nz_row = mat_A.row_ptr[row_ptr]; nz_row < mat_A.row_ptr[row_ptr + 1]; nz_row++)
        {
            uINT target_pos = 0;
            if (bin_search_s_vec(vec_x, row_ptr, target_pos) == true)
            {
                vec_b.vec_element[mat_A.col_and_val[nz_row].index] += (mat_A.col_and_val[nz_row].val * vec_x.vec_element[target_pos].val);
            }
        }
    }
    vec_b.vec_data.num_nz = count_nz(vec_b);
}

void OPERATION_CSR::SpM_SpM(const CSR &mat_A, const CSR &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_col, mat_X.mat_data.num_row, is_transpose::NO);

    for (uINT row_ptr_A = 0; row_ptr_A < mat_A.mat_data.num_row; row_ptr_A++)
    {
        uINT nz_row_A_start = mat_A.row_ptr[row_ptr_A];
        uINT nz_row_A_end = mat_A.row_ptr[row_ptr_A + 1];
        for (uINT nz_row_A = nz_row_A_start; nz_row_A < nz_row_A_end; nz_row_A++)
        {
            uINT nz_row_X_start = mat_X.row_ptr[mat_A.col_and_val[nz_row_A].index];
            uINT nz_row_X_end = mat_X.row_ptr[mat_A.col_and_val[nz_row_A].index + 1];
            for (uINT nz_row_X = nz_row_X_start; nz_row_X < nz_row_X_end; nz_row_X++)
            {
                mat_B.matrix[row_ptr_A][mat_X.col_and_val[nz_row_X].index] +=
                    (mat_A.col_and_val[nz_row_A].val * mat_X.col_and_val[nz_row_X].val);
            }
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
}

void OPERATION_CSR::SpM_SpM(const CSR &mat_A, const CSC &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_col, mat_X.mat_data.num_row, is_transpose::NO);

    for (uINT row_ptr_A = 0; row_ptr_A < mat_A.mat_data.num_row; row_ptr_A++)
    {
        uINT row_start_A = mat_A.row_ptr[row_ptr_A];
        uINT row_end_A = mat_A.row_ptr[row_ptr_A + 1];
        for (uINT row_nz_A = row_start_A; row_nz_A < row_end_A; row_nz_A++)
        {
            for (uINT col_ptr_X = 0; col_ptr_X < mat_X.mat_data.num_col; col_ptr_X++)
            {
                uINT col_start_X = mat_X.col_ptr[col_ptr_X];
                uINT col_end_X = mat_X.col_ptr[col_ptr_X + 1];
                uINT target_idx = mat_A.col_and_val[row_nz_A].index;
                uINT target_pos = 0;
                if ((col_start_X < col_end_X) && (bin_search_s_mat(mat_X.row_and_val, col_start_X, col_end_X, target_idx, target_pos)))
                {
                    mat_B.matrix[row_ptr_A][col_ptr_X] += mat_A.col_and_val[row_nz_A].val * mat_X.row_and_val[target_pos].val;
                }
            }
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
}

void OPERATION_CSR::SpM_SpM_T(const CSR &mat_A, const CSR &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_row, mat_X.mat_data.num_row, is_transpose::YES);

    for (uINT row_ptr_A = 0; row_ptr_A < mat_A.mat_data.num_row; row_ptr_A++)
    {
        uINT nz_row_A_start = mat_A.row_ptr[row_ptr_A];
        uINT nz_row_A_end = mat_A.row_ptr[row_ptr_A + 1];

        for (uINT nz_row_A = nz_row_A_start; nz_row_A < nz_row_A_end; nz_row_A++)
        {
            uINT nz_row_X_start = mat_X.row_ptr[row_ptr_A];
            uINT nz_row_X_end = mat_X.row_ptr[row_ptr_A + 1];

            for (uINT nz_row_X = nz_row_X_start; nz_row_X < nz_row_X_end; nz_row_X++)
            {
                mat_B.matrix[mat_X.col_and_val[nz_row_X].index][mat_A.col_and_val[nz_row_A].index] +=
                    mat_A.col_and_val[nz_row_A].val * mat_X.col_and_val[nz_row_X].val;
            }
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
}

void OPERATION_CSR::SpM_SpM_T(const CSR &mat_A, const CSC &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_row, mat_X.mat_data.num_row, is_transpose::YES);

    for (uINT row_ptr_A = 0; row_ptr_A < mat_A.mat_data.num_row; row_ptr_A++)
    {
        uINT row_start_A = mat_A.row_ptr[row_ptr_A];
        uINT row_end_A = mat_A.row_ptr[row_ptr_A + 1];

        if (row_start_A < row_end_A)
        {
            for (uINT col_ptr_X = 0; col_ptr_X < mat_X.mat_data.num_col; col_ptr_X++)
            {
                uINT col_start_X = mat_X.col_ptr[col_ptr_X];
                uINT col_end_X = mat_X.col_ptr[col_ptr_X + 1];
                uINT target_idx = row_ptr_A;
                uINT target_pos = 0;

                if ((col_start_X < col_end_X) && (bin_search_s_mat(mat_X.row_and_val, col_start_X, col_end_X, target_idx, target_pos)))
                {
                    for (uINT nz_row_A = row_start_A; nz_row_A < row_end_A; nz_row_A++)
                    {
                        mat_B.matrix[mat_A.col_and_val[nz_row_A].index][col_ptr_X] +=
                            mat_A.col_and_val[nz_row_A].val * mat_X.row_and_val[target_pos].val;
                    }
                }
            }
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
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
