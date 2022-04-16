#pragma once
#include "PCH.hpp"
#include "matrix_struct.hpp"

class WRITE_SVEC
{
public:
    WRITE_SVEC();
    virtual ~WRITE_SVEC();

    bool write_svec_ANSI_based(std::string file_name, S_VECTOR &output_vec);

    bool write_svec_UNSAFE(std::string file_name, S_VECTOR &output_vec);

    bool write_svec_SAFE(std::string file_name, S_VECTOR &output_vec);

private:
};