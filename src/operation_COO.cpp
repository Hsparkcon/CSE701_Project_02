#include "../include/operation_COO.hpp"

OPERATION_COO::OPERATION_COO()
{
    /*Do Nothing*/
}

OPERATION_COO::~OPERATION_COO()
{
    /*Do Nothing*/
}

void OPERATION_COO::SpMV(const COO &mat_A, const D_VECTOR &vec_x, D_VECTOR &vec_b)
{
    validate_length(mat_A.mat_data.num_col, vec_x.vec_data.len_vec, is_transpose::NO);

    for (const auto &iter_nz : mat_A.mat_elements)
    {
        vec_b.vec_element[iter_nz.row_index] += (iter_nz.val * vec_x.vec_element[iter_nz.col_index]);
    }

    vec_b.vec_data.num_nz = count_nz(vec_b);
}

void OPERATION_COO::SpMV_T(const COO &mat_A, const D_VECTOR &vec_x, D_VECTOR &vec_b)
{
    validate_length(mat_A.mat_data.num_row, vec_x.vec_data.len_vec, is_transpose::YES);

    for (const auto &iter_nz : mat_A.mat_elements)
    {
        vec_b.vec_element[iter_nz.col_index] += (iter_nz.val * vec_x.vec_element[iter_nz.row_index]);
    }

    vec_b.vec_data.num_nz = count_nz(vec_b);
}

void OPERATION_COO::SpMM(const COO &mat_A, const D_MATRIX &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_col, mat_X.mat_data.num_row, is_transpose::NO);

    for (uINT x_col = 0; x_col < mat_X.mat_data.num_col; x_col++)
    {
        for (const auto &ele_A : mat_A.mat_elements)
        {
            mat_B.matrix[ele_A.row_index][x_col] += (ele_A.val * mat_X.matrix[ele_A.col_index][x_col]);
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
}

void OPERATION_COO::SpMM_T(const COO &mat_A, const D_MATRIX &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_row, mat_X.mat_data.num_row, is_transpose::YES);

    for (uINT x_col = 0; x_col < mat_X.mat_data.num_col; x_col++)
    {
        for (const auto &iter_nz : mat_A.mat_elements)
        {
            mat_B.matrix[iter_nz.col_index][x_col] += (iter_nz.val * mat_X.matrix[iter_nz.row_index][x_col]);
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
}

void OPERATION_COO::SpM_SpV(const COO &mat_A, const S_VECTOR &vec_x, D_VECTOR &vec_b)
{
    validate_length(mat_A.mat_data.num_col, vec_x.vec_data.len_vec, is_transpose::NO);

    for (const auto &ele_A : mat_A.mat_elements)
    {
        uint32_t target_index = 0;
        if (bin_search_s_vec(vec_x, ele_A.col_index, target_index) == true)
        {
            vec_b.vec_element[ele_A.row_index] += (ele_A.val * vec_x.vec_element[target_index].val);
        }
    }
    vec_b.vec_data.num_nz = count_nz(vec_b);
}

void OPERATION_COO::SpM_SpV_T(const COO &mat_A, const S_VECTOR &vec_x, D_VECTOR &vec_b)
{
    validate_length(mat_A.mat_data.num_row, vec_x.vec_data.len_vec, is_transpose::YES);

    for (const auto &ele_A : mat_A.mat_elements)
    {
        uint32_t target_index = 0;
        if (bin_search_s_vec(vec_x, ele_A.row_index, target_index) == true)
        {
            vec_b.vec_element[ele_A.col_index] += (ele_A.val * vec_x.vec_element[target_index].val);
        }
    }
    vec_b.vec_data.num_nz = count_nz(vec_b);
}

void OPERATION_COO::SpM_SpM(const COO &mat_A, const CSR &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_col, mat_X.mat_data.num_row, is_transpose::NO);

    for (const auto &ele_A : mat_A.mat_elements)
    {
        uINT row_start = mat_X.row_ptr[ele_A.col_index];
        uINT row_end = mat_X.row_ptr[ele_A.col_index + 1];
        for (uINT nz_row = row_start; nz_row < row_end; nz_row++)
        {
            mat_B.matrix[ele_A.row_index][mat_X.col_and_val[nz_row].index] += (ele_A.val * mat_X.col_and_val[nz_row].val);
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
}

void OPERATION_COO::SpM_SpM(const COO &mat_A, const CSC &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_col, mat_X.mat_data.num_row, is_transpose::NO);

    for (uINT col_ptr = 0; col_ptr < mat_X.mat_data.num_col; col_ptr++)
    {
        for (const auto &ele_A : mat_A.mat_elements)
        {
            uINT col_start = mat_X.col_ptr[col_ptr];
            uINT col_end = mat_X.col_ptr[col_ptr + 1];
            uINT target_idx = ele_A.col_index;
            uINT target_pos = 0;
            if ((col_start < col_end) && bin_search_s_mat(mat_X.row_and_val, col_start, col_end, target_idx, target_pos))
            {
                mat_B.matrix[ele_A.row_index][col_ptr] += ele_A.val * mat_X.row_and_val[target_pos].val;
            }
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
}

void OPERATION_COO::SpM_SpM_T(const COO &mat_A, const CSR &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_row, mat_X.mat_data.num_row, is_transpose::YES);

    for (const auto &ele_A : mat_A.mat_elements)
    {
        uINT row_prt_start_X = mat_X.row_ptr[ele_A.row_index];
        uINT row_prt_end_X = mat_X.row_ptr[ele_A.row_index + 1];

        for (uINT nz_row_X = row_prt_start_X; nz_row_X < row_prt_end_X; nz_row_X++)
        {
            mat_B.matrix[ele_A.col_index][mat_X.col_and_val[nz_row_X].index] +=
                ele_A.val * mat_X.col_and_val[nz_row_X].val;
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
}

void OPERATION_COO::SpM_SpM_T(const COO &mat_A, const CSC &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_row, mat_X.mat_data.num_row, is_transpose::YES);

    for (const auto &ele_A : mat_A.mat_elements)
    {
        for (uINT col_ptr_X = 0; col_ptr_X < mat_X.mat_data.num_col; col_ptr_X++)
        {
            uINT nz_col_start_X = mat_X.col_ptr[col_ptr_X];
            uINT nz_col_end_X = mat_X.col_ptr[col_ptr_X + 1];
            uINT target_idx = ele_A.row_index;
            uINT target_pos = 0;

            if ((nz_col_start_X < nz_col_end_X) &&
                bin_search_s_mat(mat_X.row_and_val, nz_col_start_X, nz_col_end_X, target_idx, target_pos))
            {
                mat_B.matrix[ele_A.col_index][col_ptr_X] +=
                    ele_A.val * mat_X.row_and_val[target_pos].val;
            }
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
}

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