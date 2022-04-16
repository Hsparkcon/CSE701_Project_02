#include "../include/matrix_print.hpp"

void print_info(const VECTOR_INFO &info)
{
    std::cout << std::left
              << std::setw(15) << "Vector Name"
              << " : " << info.vec_name << "\n"
              << std::setw(15) << "Vector Length"
              << " : " << info.len_vec << "\n"
              << std::setw(15) << "Vector Non-Zero"
              << " : " << info.num_nz << std::endl;
}

void print_vec(const D_VECTOR &vec)
{
    std::cout << "Elements : ";
    for (const auto &iter_d_vec : vec.vec_element)
    {
        std::cout << iter_d_vec << " ";
    }
    std::cout << "\n"
              << std::endl;
}

void print_vec(const S_VECTOR &vec)
{
    std::cout << std::setw(9) << "IDX"
              << "\t"
              << "Val\n";
    for (const auto &ele_vec : vec.vec_element)
    {
        std::cout << std::setw(9) << ele_vec.index << "\t" << std::scientific << std::setprecision(2) << ele_vec.val << "\n";
    }
    std::cout << "\n"
              << std::endl;
}

void info_line()
{
    uint32_t width_val = 9;
    std::cout << std::setw(width_val) << "Row"
              << "\t" << std::setw(width_val) << "Col"
              << "\t"
              << "Val" << std::endl;
}

void data_line(uint32_t row, uint32_t col, double value)
{
    uint32_t width_val = 9;
    std::cout << std::setw(width_val) << row << "\t" << std::setw(width_val) << col << "\t" << std::scientific << std::setprecision(2) << value << "\n";
}

void print_info(const MATRIX_INFO &info)
{
    std::cout << std::left
              << std::setw(15) << "Matrix Name"
              << " : " << info.matrix_name << "\n"
              << std::setw(15) << "Matrix Row"
              << " : " << info.num_row << "\n"
              << std::setw(15) << "Matrix Column"
              << " : " << info.num_col << "\n"
              << std::setw(15) << "Matrix Non-Zero"
              << " : " << info.num_row << std::endl;
}

void print_mat(const D_MATRIX &mat)
{
    info_line();
    for (uint32_t row = 0; row < mat.mat_data.num_row; row++)
    {
        for (uint32_t col = 0; col < mat.mat_data.num_col; col++)
        {
            if (mat.matrix[row][col] != 0)
            {
                data_line(row, col, mat.matrix[row][col]);
            }
        }
    }
    std::cout << std::endl;
}

void print_mat(const COO &mat)
{
    info_line();
    for (const auto &iter_coo : mat.mat_elements)
    {
        data_line(iter_coo.row_index, iter_coo.col_index, iter_coo.val);
    }
    std::cout << "\n"
              << std::endl;
}

void print_mat(const CSR &mat)
{
    info_line();
    for (uint32_t row_ptr = 0; row_ptr < mat.mat_data.num_row; row_ptr++)
    {
        uint32_t row_start = mat.row_ptr[row_ptr];
        uint32_t row_end = mat.row_ptr[row_ptr + 1];
        for (uint32_t row = row_start; row < row_end; row++)
        {
            data_line(row_ptr, mat.col_and_val[row].index, mat.col_and_val[row].val);
        }
    }
}

void print_mat(const CSC &mat)
{
    info_line();
    for (uint32_t col_ptr = 0; col_ptr < mat.mat_data.num_col; col_ptr++)
    {
        uint32_t col_start = mat.col_ptr[col_ptr];
        uint32_t col_end = mat.col_ptr[col_ptr + 1];
        for (uint32_t col = col_start; col < col_end; col++)
        {
            data_line(col_ptr, mat.row_and_val[col].index, mat.row_and_val[col].val);
        }
    }
}

std::ostream &operator<<(std::ostream &out, const D_VECTOR &vec)
{
    print_info(vec.vec_data);
    print_vec(vec);
    return out;
}

std::ostream &operator<<(std::ostream &out, const S_VECTOR &vec)
{
    print_info(vec.vec_data);
    print_vec(vec);
    return out;
}

std::ostream &operator<<(std::ostream &out, const D_MATRIX &mat)
{
    print_info(mat.mat_data);
    print_mat(mat);
    return out;
}

std::ostream &operator<<(std::ostream &out, const COO &mat)
{
    print_info(mat.mat_data);
    print_mat(mat);
    return out;
}

std::ostream &operator<<(std::ostream &out, const CSC &mat)
{
    print_info(mat.mat_data);
    print_mat(mat);
    return out;
}

std::ostream &operator<<(std::ostream &out, const CSR &mat)
{
    print_info(mat.mat_data);
    print_mat(mat);
    return out;
}