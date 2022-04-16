#pragma once
#include "PCH.hpp"
#include "matrix_struct.hpp"
#include "matrix_allocation.hpp"

class MATRIX_RAND
{
public:
    MATRIX_RAND();
    virtual ~MATRIX_RAND();

    void rand_mat(const MATRIX_INFO &mat_info, const uint32_t num_nz, COO &coo);

    void rand_mat(const MATRIX_INFO &mat_info, const uint32_t num_nz, D_MATRIX &d_mat);

    void rand_vec(const VECTOR_INFO &vec_info, const uint32_t num_nz, S_VECTOR &s_vec);

    void rand_vec(const VECTOR_INFO &vec_info, const uint32_t num_nz, D_VECTOR &d_vec);

private:
    MATRIX_ALLOCATION m_alloc;

    void validate_nnz(const MATRIX_INFO &mat_info, const uint32_t requested_num_nz);

    void validate_nnz(const VECTOR_INFO &vec_info, const uint32_t requested_num_nz);

    void validate_efficiency(const uint32_t container_size, const uint32_t requested_num_nz);

    void decode_index(const uint32_t &encoded_idx, const uint32_t &num_col, uint32_t &decoded_row, uint32_t &decoded_col);
};