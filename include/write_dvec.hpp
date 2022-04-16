#pragma once
#include "PCH.hpp"
#include "matrix_struct.hpp"

class WRITE_DVEC
{
public:
    WRITE_DVEC();
    virtual ~WRITE_DVEC();

    bool write_dvec_ANSI_based(std::string file_name, D_VECTOR &output_vec);

    bool write_dvec_UNSAFE(std::string file_name, D_VECTOR &output_vec);

    bool write_dvec_SAFE(std::string file_name, D_VECTOR &output_vec);

private:
};