#include "test_cases.hpp"
#include "../include/matrix_convert.hpp"

int main()
{
    MATRIX_CONVERT f_convert;

    COO *temp_coo = nullptr;
    CSR *result_csr = nullptr;
    CSC *result_csc = nullptr;

    temp_coo = new COO();
    result_csr = new CSR();
    f_convert.convert(sample_csr, *temp_coo);
    f_convert.convert(*temp_coo, *result_csr);
    assert(sample_csr == *result_csr);
    delete temp_coo;
    delete result_csr;
    temp_coo = nullptr;
    result_csr = nullptr;
  
    temp_coo = new COO();
    result_csc = new CSC();
    f_convert.convert(sample_csc, *temp_coo);
    f_convert.convert(*temp_coo, *result_csc);
    assert(sample_csc == *result_csc);
    delete temp_coo;
    delete result_csc;
    temp_coo = nullptr;
    result_csc = nullptr;


    CSR transpose_csr;
    f_convert.transpose(sample_csr, transpose_csr);
    for (uint32_t ptr = 0; ptr < sample_csc.mat_data.num_col + 1; ptr++)
    {
        assert(transpose_csr.row_ptr[ptr] == sample_csc.col_ptr[ptr]);
    }
    for (uint32_t idx_val = 0; idx_val < sample_csc.mat_data.num_nz; idx_val++)
    {
        assert(transpose_csr.col_and_val[idx_val] == sample_csc.row_and_val[idx_val]);
    }

    CSC transpose_csc;
    f_convert.transpose(sample_csc, transpose_csc);
    for (uint32_t ptr = 0; ptr < sample_csr.mat_data.num_row + 1; ptr++)
    {
        assert(transpose_csc.col_ptr[ptr] == sample_csr.row_ptr[ptr]);
    }
    for (uint32_t idx_val = 0; idx_val < sample_csr.mat_data.num_nz; idx_val++)
    {
        assert(transpose_csc.row_and_val[idx_val] == sample_csr.col_and_val[idx_val]);
    }

    std::cout << "Validation for matrix convertor complete" << std::endl;

    return 0;
}