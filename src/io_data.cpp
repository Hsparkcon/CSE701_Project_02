#include "../include/io_data.hpp"

IO_DATA::IO_DATA(IO_MODE io_method) : m_io_method{io_method} 
{
    /* Do Nohing*/
}

IO_DATA::~IO_DATA() {
        /* Do Nohing*/
}

bool IO_DATA::load_mat(std::string file_name, COO &output_mat)
{
    bool load_result = true;
    switch (m_io_method)
    {
    case IO_MODE::ANSI_BASE:
        r_mtx.load_matrix_mtx_ANSI_based(file_name, output_mat);
        break;
    case IO_MODE::SAFE:
        r_mtx.load_matrix_mtx_SAFE(file_name, output_mat);
        break;
    case IO_MODE::UNSAFE:
        r_mtx.load_matrix_mtx_UNSAFE(file_name, output_mat);
        break;
    }
    return load_result;
}

bool IO_DATA::load_mat(std::string file_name, D_MATRIX &output_mat)
{
    bool load_result = true;
    switch (m_io_method)
    {
    case IO_MODE::ANSI_BASE:
        load_result = r_dmat.load_dmat_ANSI_BASE(file_name, output_mat);
        break;
    case IO_MODE::SAFE:
        load_result = r_dmat.load_dmat_SAFE(file_name, output_mat);
        break;
    case IO_MODE::UNSAFE:
        load_result = r_dmat.load_dmat_UNSAFE(file_name, output_mat);
        break;
    }
    return load_result;
}

bool IO_DATA::load_vec(std::string file_name, D_VECTOR &output_vec)
{
    bool load_result = true;
    switch (m_io_method)
    {
    case IO_MODE::ANSI_BASE:
        load_result = r_dvec.load_dvec_ANSI_BASE(file_name, output_vec);
        break;
    case IO_MODE::SAFE:
        load_result = r_dvec.load_dvec_SAFE(file_name, output_vec);
        break;
    case IO_MODE::UNSAFE:
        load_result = r_dvec.load_dvec_UNSAFE(file_name, output_vec);
        break;
    }
    return load_result;
}

bool IO_DATA::load_vec(std::string file_name, S_VECTOR &output_vec)
{
    bool load_result = true;
    switch (m_io_method)
    {
    case IO_MODE::ANSI_BASE:
        load_result = r_svec.load_svec_ANSI_BASE(file_name, output_vec);
        break;
    case IO_MODE::SAFE:
        load_result = r_svec.load_svec_SAFE(file_name, output_vec);
        break;
    case IO_MODE::UNSAFE:
        load_result = r_svec.load_svec_UNSAFE(file_name, output_vec);
        break;
    }
    return load_result;
}

bool IO_DATA::write_mat(std::string file_name, COO &output_mat)
{
    switch (m_io_method)
    {
    case IO_MODE::ANSI_BASE:
        w_mtx.write_mtx_ANSI_based(file_name, output_mat);
        break;
    case IO_MODE::SAFE:
        w_mtx.write_mtx_SAFE(file_name, output_mat);
        break;
    case IO_MODE::UNSAFE:
        w_mtx.write_mtx_UNSAFE(file_name, output_mat);
        break;
    }
    return true;
}

bool IO_DATA::write_vec(std::string file_name, D_VECTOR &output_vec)
{
    switch (m_io_method)
    {
    case IO_MODE::ANSI_BASE:
        w_dvec.write_dvec_ANSI_based(file_name, output_vec);
        break;
    case IO_MODE::SAFE:
        w_dvec.write_dvec_SAFE(file_name, output_vec);
        break;
    case IO_MODE::UNSAFE:
        w_dvec.write_dvec_UNSAFE(file_name, output_vec);
        break;
    }
    return true;
}

bool IO_DATA::write_vec(std::string file_name, S_VECTOR &output_vec)
{
    switch (m_io_method)
    {
    case IO_MODE::ANSI_BASE:
        w_svec.write_svec_ANSI_based(file_name, output_vec);
        break;
    case IO_MODE::SAFE:
        w_svec.write_svec_SAFE(file_name, output_vec);
        break;
    case IO_MODE::UNSAFE:
        w_svec.write_svec_UNSAFE(file_name, output_vec);
        break;
    }
    return true;
}

void IO_DATA::check_io_method() const
{
    std::cout << "Current loading method is ";
    print_mode();
}

void IO_DATA::set_io_method(IO_MODE new_mode)
{
    check_io_method();
    this->m_io_method = new_mode;
    print_mode();
}

void IO_DATA::print_mode() const
{
    switch (m_io_method)
    {
    case IO_MODE::ANSI_BASE:
        std::cout << "ANSI based mode.\n";
        break;
    case IO_MODE::SAFE:
        std::cout << "Safe load mode.\n";
        break;
    case IO_MODE::UNSAFE:
        std::cout << "Unsafe load mode.\n";
        break;
    }
}
