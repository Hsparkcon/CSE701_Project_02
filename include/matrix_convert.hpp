#pragma once
#include "PCH.hpp"
#include "matrix_struct.hpp"
#include "matrix_allocation.hpp"

class MATRIX_CONVERT
{
public:
    MATRIX_CONVERT();
    virtual ~MATRIX_CONVERT();

    bool convert(
        const std::vector<uint32_t> &row_idx,
        const std::vector<uint32_t> &col_idx,
        const std::vector<double> &val,
        const uint32_t num_row,
        const uint32_t num_col,
        COO &coo);

    bool convert(
        const std::vector<uint32_t> &row_idx,
        const std::vector<uint32_t> &col_idx,
        const std::vector<double> &val,
        const uint32_t num_row,
        const uint32_t num_col,
        CSC &csc);

    bool convert(
        const std::vector<uint32_t> &row_idx,
        const std::vector<uint32_t> &col_idx,
        const std::vector<double> &val,
        const uint32_t num_row,
        const uint32_t num_col,
        CSR &csr);

    bool convert(COO &coo, CSR &csr);

    bool convert(COO &coo, CSC &csc);

    bool convert(CSR &csr, COO &coo);

    bool convert(CSR &csr, CSC &csc);

    bool convert(CSC &csc, COO &coo);

    bool convert(CSC &csc, CSR &csr);

    bool convert(D_MATRIX &d_mat, COO &coo);

    bool convert(COO &coo, D_MATRIX &d_mat);

    bool transpose(COO &input, COO &output);

    bool transpose(CSR &input, CSR &output);

    bool transpose(CSC &input, CSC &output);

private:
    MATRIX_ALLOCATION m_alloc;

    enum class sort_target
    {
        CSR,
        CSC
    };

    void sort_COO(COO &s_mat, sort_target target);

    struct
    {
        bool operator()(MAT_ELE_DATA one, MAT_ELE_DATA two) const
        {
            if (one.row_index > two.row_index)
            {
                return false;
            }
            else if (one.row_index == two.row_index && one.col_index > two.col_index)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    } sort_for_CSR;

    struct
    {
        bool operator()(MAT_ELE_DATA one, MAT_ELE_DATA two) const
        {
            if (one.col_index > two.col_index)
            {
                return false;
            }
            else if (one.col_index == two.col_index && one.row_index > two.row_index)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    } sort_for_CSC;
};