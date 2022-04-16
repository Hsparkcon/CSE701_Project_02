#pragma once
#include "PCH.hpp"
#include "matrix_struct.hpp"

class READ_DVEC
{
public:
    READ_DVEC();
    virtual ~READ_DVEC();

    bool load_dvec_ANSI_BASE(std::string file_name, D_VECTOR &output_vec);

    bool load_dvec_UNSAFE(std::string file_name, D_VECTOR &output_vec);

    bool load_dvec_SAFE(std::string file_name, D_VECTOR &output_vec);
};