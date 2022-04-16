#include "test_cases.hpp"
#include "../include/facade_CSR.hpp"

int main()
{
    facade_CSR test_csr(sample_coo);

    assert(test_csr.to_COO() == sample_coo);
    assert(test_csr.to_CSC() == sample_csc);

    D_VECTOR mv_result;
    mv_result = test_csr.SpMV(sample_d_vec);
    assert(mv_result.vec_element == desired_spmv_result);

    mv_result = test_csr() * sample_d_vec;
    assert(mv_result.vec_element == desired_spmv_result);

    mv_result = test_csr.SpM_SpV(sample_s_vec);
    assert(mv_result.vec_element == desired_spmv_result);

    mv_result = test_csr() * sample_s_vec;
    assert(mv_result.vec_element == desired_spmv_result);

    mv_result = test_csr.SpMV_T(sample_d_vec);
    assert(mv_result.vec_element == desired_spmv_t_result);

    mv_result = test_csr.transpose() * sample_d_vec;
    assert(mv_result.vec_element == desired_spmv_t_result);

    mv_result = test_csr.SpM_SpV_T(sample_s_vec);
    assert(mv_result.vec_element == desired_spmv_t_result);

    mv_result = test_csr.transpose() * sample_s_vec;
    assert(mv_result.vec_element == desired_spmv_t_result);

    D_MATRIX mm_result;
    mm_result = test_csr.SpMM(sample_d_mat);
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_csr() * sample_d_mat;
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_csr.SpM_SpM(sample_csc);
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_csr() * sample_csc;
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_csr.SpM_SpM(sample_csr);
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_csr() * sample_csr;
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_csr.SpMM_T(sample_d_mat);
    assert(mm_result.matrix == desired_spmm_t_result);

    mm_result = test_csr.transpose() * sample_d_mat;
    assert(mm_result.matrix == desired_spmm_t_result);

    mm_result = test_csr.SpM_SpM_T(sample_csc);
    assert(mm_result.matrix == desired_spmm_t_result);

    mm_result = test_csr.transpose() * sample_csc;
    assert(mm_result.matrix == desired_spmm_t_result);

    mm_result = test_csr.SpM_SpM_T(sample_csr);
    assert(mm_result.matrix == desired_spmm_t_result);

    mm_result = test_csr.transpose() * sample_csr;
    assert(mm_result.matrix == desired_spmm_t_result);

    std::cout << "Validation for facade_CSR complete" << std::endl;

    return 0;
}