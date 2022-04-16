#pragma once
#include "PCH.hpp"
#include "matrix_struct.hpp"
#include "read_mtx.hpp"
#include "read_dmat.hpp"
#include "read_dvec.hpp"
#include "read_svec.hpp"
#include "write_mtx.hpp"
#include "write_dvec.hpp"
#include "write_svec.hpp"

/**
 * @class
 * Data loader class is designed to load data from following format
 *  .r_mtx
 *  .r_dmat
 *  .r_dvec
 *  .r_svec
 *
 * Load Method
 *  ANSI_BASE - Implemented based on ANSI style (in C) .r_mtx loading method
 *  SAFE - Using C++ feature to load data, check input data format
 *  UNSAFE - Using C++ feature to load data, does not check input data format
 */
enum class IO_MODE
{
    ANSI_BASE,
    UNSAFE,
    SAFE
};

class IO_DATA
{
public:
    IO_DATA(IO_MODE io_method);

    ~IO_DATA();

    bool load_mat(std::string file_name, COO &output_mat);

    bool load_mat(std::string file_name, D_MATRIX &output_mat);

    bool load_vec(std::string file_name, D_VECTOR &output_vec);

    bool load_vec(std::string file_name, S_VECTOR &output_vec);

    bool write_mat(std::string file_name, COO &output_mat);

    bool write_vec(std::string file_name, D_VECTOR &output_vec);

    bool write_vec(std::string file_name, S_VECTOR &output_vec);

    void check_io_method() const;

    void set_io_method(IO_MODE new_mode);

private:
    IO_MODE m_io_method;
    READ_MTX r_mtx;
    READ_DMAT r_dmat;
    READ_DVEC r_dvec;
    READ_SVEC r_svec;
    WRITE_MTX w_mtx;
    WRITE_DVEC w_dvec;
    WRITE_SVEC w_svec;

    void print_mode() const;
};