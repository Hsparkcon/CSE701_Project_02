#pragma once
#include "PCH.hpp"
#include "matrix_struct.hpp"

class READ_DMAT
{
public:
    READ_DMAT();
    ~READ_DMAT();

    bool load_dmat_ANSI_BASE(std::string file_name, D_MATRIX &output_mat);

    bool load_dmat_UNSAFE(std::string file_name, D_MATRIX &output_mat);

    bool load_dmat_SAFE(std::string file_name, D_MATRIX &output_mat);

private:
};