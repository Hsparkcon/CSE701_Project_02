#pragma once
#include "PCH.hpp"
#include "matrix_struct.hpp"

class READ_SVEC
{
public:
    READ_SVEC();
    virtual ~READ_SVEC();

    bool load_svec_ANSI_BASE(std::string file_name, S_VECTOR &output_vec);

    bool load_svec_UNSAFE(std::string file_name, S_VECTOR &output_vec);

    bool load_svec_SAFE(std::string file_name, S_VECTOR &output_vec);

private:
    bool index_check(uint32_t idx_limit, uint32_t idx) const;
};