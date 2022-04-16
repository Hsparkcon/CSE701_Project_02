#pragma once
#include "PCH.hpp"
#include "matrix_struct.hpp"

class WRITE_MTX
{
public:
    WRITE_MTX();
    virtual ~WRITE_MTX();

    bool write_mtx_ANSI_based(std::string file_name, COO &output_mat);

    bool write_mtx_UNSAFE(std::string file_name, COO &output_mat);

    bool write_mtx_SAFE(std::string file_name, COO &output_mat);

private:
};