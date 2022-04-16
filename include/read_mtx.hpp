#pragma once
#include "PCH.hpp"
#include "matrix_struct.hpp"

class READ_MTX
{
public:
    READ_MTX();
    ~READ_MTX();

    bool load_matrix_mtx_ANSI_based(std::string file_name, COO &output_mat);

    bool load_matrix_mtx_UNSAFE(std::string file_name, COO &output_mat);

    bool load_matrix_mtx_SAFE(std::string file_name, COO &output_mat);

private:
    bool index_check(uint32_t row_limit, uint32_t col_limit, uint32_t row_ind, uint32_t col_ind) const;
};