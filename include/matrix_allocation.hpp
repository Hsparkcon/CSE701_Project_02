#pragma once
#include "PCH.hpp"
#include "matrix_struct.hpp"

class MATRIX_ALLOCATION
{
public:
    MATRIX_ALLOCATION();
    virtual ~MATRIX_ALLOCATION();

    void alloc_vec(const uint32_t vector_len, std::string name, D_VECTOR &output);

    /**
     * @brief
     * The following alloc_vec is designed to initialized sparse vector to store result of following operations
     * - SpMV
     * - SpMV_T
     * - SpM_SpV
     * - SpM_SpV_T
     *
     *
     * @param[in] d_vec     length of vector
     * @param[in] name      name of vector
     * @param[out] s_vec    sparse vector to be used
     */
    void alloc_vec(D_VECTOR &d_vec, std::string name, S_VECTOR &s_vec);

    /**
     * @brief
     * The following alloc_vec is designed to initialized sparse vector for
     * - dense vector to sparse vector conversion.
     * - load sparse matrix.
     *
     * @param[in] vec_len   length of vector
     * @param[in] num_nz    number of non-zero in vector
     * @param[in] name      name of vector
     *
     * @param[out] s_vec    sparse vector to be used
     */
    void alloc_vec(const uint32_t vec_len, uint32_t num_nz, std::string name, S_VECTOR &s_vec);

    void alloc_vec(const VECTOR_INFO &vec_info, S_VECTOR &output);

    void alloc_vec(const VECTOR_INFO &vec_info, D_VECTOR &output);

    void alloc_mat(uint32_t num_row, uint32_t num_col, std::string name, D_MATRIX &output);

    void alloc_mat(const MATRIX_INFO &mat_info, D_MATRIX &output);

    void alloc_mat(const MATRIX_INFO &mat_info, COO &output);

    void alloc_mat(const MATRIX_INFO &mat_info, CSR &output);

    void alloc_mat(const MATRIX_INFO &mat_info, CSC &output);

    void delete_vec(D_VECTOR &d_vec);

    void delete_vec(S_VECTOR &s_vec);

    void delete_mat(D_MATRIX &d_mat);

    void delete_mat(COO &s_mat);

    void delete_mat(CSR &s_mat);

    void delete_mat(CSC &s_mat);
};