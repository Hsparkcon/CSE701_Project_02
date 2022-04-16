#include "../include/operation_CSC.hpp"

OPERATION_CSC::OPERATION_CSC() {}

OPERATION_CSC::~OPERATION_CSC() {}

void OPERATION_CSC::SpMV(const CSC &mat_A, const D_VECTOR &vec_x, D_VECTOR &vec_b)
{
    validate_length(mat_A.mat_data.num_col, vec_x.vec_data.len_vec, is_transpose::NO);

    for (uint32_t iter_c_ptr = 0; iter_c_ptr < mat_A.mat_data.num_col; iter_c_ptr++)
    {
        for (uint32_t iter_nz = mat_A.col_ptr[iter_c_ptr]; iter_nz < mat_A.col_ptr[iter_c_ptr + 1]; iter_nz++)
        {
            vec_b.vec_element[mat_A.row_and_val[iter_nz].index] += (mat_A.row_and_val[iter_nz].val * vec_x.vec_element[iter_c_ptr]);
        }
    }
    vec_b.vec_data.num_nz = count_nz(vec_b);
}

void OPERATION_CSC::SpMV_T(const CSC &mat_A, const D_VECTOR &vec_x, D_VECTOR &vec_b)
{
    validate_length(mat_A.mat_data.num_row, vec_x.vec_data.len_vec, is_transpose::YES);

    for (uINT col_ptr = 0; col_ptr < mat_A.mat_data.num_col; col_ptr++)
    {
        for (uINT nnz_col = mat_A.col_ptr[col_ptr]; nnz_col < mat_A.col_ptr[col_ptr + 1]; nnz_col++)
        {
            vec_b.vec_element[col_ptr] += (mat_A.row_and_val[nnz_col].val * vec_x.vec_element[mat_A.row_and_val[nnz_col].index]);
        }
    }
    vec_b.vec_data.num_nz = count_nz(vec_b);
}

void OPERATION_CSC::SpMM(const CSC &mat_A, const D_MATRIX &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_col, mat_X.mat_data.num_row, is_transpose::NO);

    for (uINT col_ptr = 0; col_ptr < mat_A.mat_data.num_col; col_ptr++)
    {
        for (uINT nnz_col = mat_A.col_ptr[col_ptr]; nnz_col < mat_A.col_ptr[col_ptr + 1]; nnz_col++)
        {
            for (uINT x_col = 0; x_col < mat_X.mat_data.num_col; x_col++)
            {
                mat_B.matrix[mat_A.row_and_val[nnz_col].index][x_col] += (mat_A.row_and_val[nnz_col].val * mat_X.matrix[col_ptr][x_col]);
            }
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
}

void OPERATION_CSC::SpMM_T(const CSC &mat_A, const D_MATRIX &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_row, mat_X.mat_data.num_row, is_transpose::YES);

    for (uINT col_ptr = 0; col_ptr < mat_A.mat_data.num_col; col_ptr++)
    {
        for (uINT nnz_col = mat_A.col_ptr[col_ptr]; nnz_col < mat_A.col_ptr[col_ptr + 1]; nnz_col++)
        {
            for (uINT x_col = 0; x_col < mat_X.mat_data.num_col; x_col++)
            {
                mat_B.matrix[col_ptr][x_col] += (mat_A.row_and_val[nnz_col].val * mat_X.matrix[mat_A.row_and_val[nnz_col].index][x_col]);
            }
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
}

void OPERATION_CSC::SpM_SpV(const CSC &mat_A, const S_VECTOR &vec_x, D_VECTOR &vec_b)
{
    validate_length(mat_A.mat_data.num_col, vec_x.vec_data.len_vec, is_transpose::NO);

    for (uINT col_ptr = 0; col_ptr < mat_A.mat_data.num_col; col_ptr++)
    {
        for (uINT nz_col = mat_A.col_ptr[col_ptr]; nz_col < mat_A.col_ptr[col_ptr + 1]; nz_col++)
        {
            uINT target_pos = 0;
            if (bin_search_s_vec(vec_x, col_ptr, target_pos) == true)
            {
                vec_b.vec_element[mat_A.row_and_val[nz_col].index] += (mat_A.row_and_val[nz_col].val * vec_x.vec_element[target_pos].val);
            }
        }
    }
    vec_b.vec_data.num_nz = count_nz(vec_b);
}

void OPERATION_CSC::SpM_SpV_T(const CSC &mat_A, const S_VECTOR &vec_x, D_VECTOR &vec_b)
{
    validate_length(mat_A.mat_data.num_row, vec_x.vec_data.len_vec, is_transpose::YES);

    for (uINT col_ptr = 0; col_ptr < mat_A.mat_data.num_col; col_ptr++)
    {
        for (uINT nz_col = mat_A.col_ptr[col_ptr]; nz_col < mat_A.col_ptr[col_ptr + 1]; nz_col++)
        {
            uINT target_pos = 0;
            if (bin_search_s_vec(vec_x, mat_A.row_and_val[nz_col].index, target_pos) == true)
            {
                vec_b.vec_element[col_ptr] += (mat_A.row_and_val[nz_col].val * vec_x.vec_element[target_pos].val);
            }
        }
    }
    vec_b.vec_data.num_nz = count_nz(vec_b);
}

void OPERATION_CSC::SpM_SpM(const CSC &mat_A, const CSR &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_col, mat_X.mat_data.num_row, is_transpose::NO);

    for (uINT col_ptr_A = 0; col_ptr_A < mat_A.mat_data.num_col; col_ptr_A++)
    {
        uINT nz_col_A_start = mat_A.col_ptr[col_ptr_A];
        uINT nz_col_A_end = mat_A.col_ptr[col_ptr_A + 1];
        for (uINT nz_col_A = nz_col_A_start; nz_col_A < nz_col_A_end; nz_col_A++)
        {
            uINT nz_row_X_start = mat_X.row_ptr[col_ptr_A];
            uINT nz_row_X_end = mat_X.row_ptr[col_ptr_A + 1];
            for (uINT nz_row_X = nz_row_X_start; nz_row_X < nz_row_X_end; nz_row_X++)
            {
                mat_B.matrix[mat_A.row_and_val[nz_col_A].index][mat_X.col_and_val[nz_row_X].index] +=
                    mat_A.row_and_val[nz_col_A].val * mat_X.col_and_val[nz_row_X].val;
            }
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
}

void OPERATION_CSC::SpM_SpM(const CSC &mat_A, const CSC &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_col, mat_X.mat_data.num_row, is_transpose::NO);

    // for(uINT col_ptr_A = 0; col_ptr_A < mat_A.mat_data.num_col; col_ptr_A++){
    //     uINT col_start_A = mat_A.col_ptr[col_ptr_A];
    //     uINT col_end_A = mat_A.col_ptr[col_ptr_A + 1];
    //     for(uINT col_nz_A = col_start_A; col_nz_A < col_end_A; col_nz_A++){
    //         for(uINT col_ptr_X = 0; col_ptr_X < mat_X.mat_data.num_col; col_ptr_X++){
    //             uINT col_start_X = mat_X.col_ptr[col_ptr_X];
    //             uINT col_end_X = mat_X.col_ptr[col_ptr_X + 1];
    //             uINT target_idx = col_ptr_A;
    //             uINT target_pos = 0;
    //             if((col_start_X < col_end_X) && (bin_search_s_mat(mat_X.row_and_val, col_start_X, col_end_X, target_idx, target_pos))){
    //                 mat_B.matrix[mat_A.row_and_val[col_nz_A].index][col_ptr_X] +=
    //                     mat_A.row_and_val[col_nz_A].val * mat_X.row_and_val[target_pos].val;
    //             }
    //         }
    //     }
    // }

    // for(uINT col_ptr_X = 0; col_ptr_X < mat_X.mat_data.num_col; col_ptr_X++){
    //     uINT col_start_X = mat_X.col_ptr[col_ptr_X];
    //     uINT col_end_X = mat_X.col_ptr[col_ptr_X + 1];
    //     if(col_start_X < col_end_X){
    //         for(uINT col_ptr_A = 0; col_ptr_A < mat_A.mat_data.num_col; col_ptr_A++){
    //             uINT col_start_A = mat_A.col_ptr[col_ptr_A];
    //             uINT col_end_A = mat_A.col_ptr[col_ptr_A + 1];
    //             uINT target_idx = col_ptr_A;
    //             uINT target_pos = 0;
    //             if(bin_search_s_mat(mat_X.row_and_val, col_start_X, col_end_X, target_idx, target_pos)){
    //                 for(uINT col_nz_A = col_start_A; col_nz_A < col_end_A; col_nz_A++){
    //                     mat_B.matrix[mat_A.row_and_val[col_nz_A].index][col_ptr_X] +=
    //                         mat_A.row_and_val[col_nz_A].val * mat_X.row_and_val[target_pos].val;
    //                 }
    //             }
    //         }
    //     }
    // }

    for (uINT col_ptr_A = 0; col_ptr_A < mat_A.mat_data.num_col; col_ptr_A++)
    {
        uINT col_start_A = mat_A.col_ptr[col_ptr_A];
        uINT col_end_A = mat_A.col_ptr[col_ptr_A + 1];

        if (col_start_A < col_end_A)
        {
            for (uINT col_ptr_X = 0; col_ptr_X < mat_X.mat_data.num_col; col_ptr_X++)
            {
                uINT col_start_X = mat_X.col_ptr[col_ptr_X];
                uINT col_end_X = mat_X.col_ptr[col_ptr_X + 1];
                uINT target_idx = col_ptr_A;
                uINT target_pos = 0;

                if ((col_start_X < col_end_X) && (bin_search_s_mat(mat_X.row_and_val, col_start_X, col_end_X, target_idx, target_pos)))
                {
                    for (uINT col_nz_A = col_start_A; col_nz_A < col_end_A; col_nz_A++)
                    {
                        mat_B.matrix[mat_A.row_and_val[col_nz_A].index][col_ptr_X] += mat_A.row_and_val[col_nz_A].val * mat_X.row_and_val[target_pos].val;
                    }
                }
            }
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
}

void OPERATION_CSC::SpM_SpM_T(const CSC &mat_A, const CSR &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_row, mat_X.mat_data.num_row, is_transpose::YES);

    for (uINT col_ptr_A = 0; col_ptr_A < mat_A.mat_data.num_col; col_ptr_A++)
    {
        uINT col_A_start = mat_A.col_ptr[col_ptr_A];
        uINT col_A_end = mat_A.col_ptr[col_ptr_A + 1];

        for (uINT col_A = col_A_start; col_A < col_A_end; col_A++)
        {

            uINT nz_row_X_start = mat_X.row_ptr[mat_A.row_and_val[col_A].index];
            uINT nz_row_X_end = mat_X.row_ptr[mat_A.row_and_val[col_A].index + 1];

            for (uINT nz_row_X = nz_row_X_start; nz_row_X < nz_row_X_end; nz_row_X++)
            {
                mat_B.matrix[col_ptr_A][mat_X.col_and_val[nz_row_X].index] +=
                    (mat_A.row_and_val[col_A].val * mat_X.col_and_val[nz_row_X].val);
            }
        }
    }

    mat_B.mat_data.num_nz = count_nz(mat_B);
}

void OPERATION_CSC::SpM_SpM_T(const CSC &mat_A, const CSC &mat_X, D_MATRIX &mat_B)
{
    validate_length(mat_A.mat_data.num_row, mat_X.mat_data.num_row, is_transpose::YES);

    for (uINT col_ptr_A = 0; col_ptr_A < mat_A.mat_data.num_col; col_ptr_A++)
    {
        uINT col_A_start = mat_A.col_ptr[col_ptr_A];
        uINT col_A_end = mat_A.col_ptr[col_ptr_A + 1];

        for (uINT col_A = col_A_start; col_A < col_A_end; col_A++)
        {
            for (uINT col_ptr_X = 0; col_ptr_X < mat_X.mat_data.num_col; col_ptr_X++)
            {
                uINT col_X_start = mat_X.col_ptr[col_ptr_X];
                uINT col_X_end = mat_X.col_ptr[col_ptr_X + 1];
                uINT target_idx = mat_A.row_and_val[col_A].index;
                uINT target_pos = 0;

                if (bin_search_s_mat(mat_X.row_and_val, col_X_start, col_X_end, target_idx, target_pos) != false)
                {
                    mat_B.matrix[col_ptr_A][col_ptr_X] += (mat_A.row_and_val[col_A].val * mat_X.row_and_val[target_pos].val);
                }
            }
        }
    }
    mat_B.mat_data.num_nz = count_nz(mat_B);
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

