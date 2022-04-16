#include "test_cases.hpp"
#include "../include/facade_CSC.hpp"


int main()
{
    facade_CSC test_csc(sample_coo);

    assert(test_csc.to_COO() == sample_coo);
    assert(test_csc.to_CSR() == sample_csr);

    D_VECTOR mv_result;
    mv_result = test_csc.SpMV(sample_d_vec);
    assert(mv_result.vec_element == desired_spmv_result);

    mv_result = test_csc() * sample_d_vec;
    assert(mv_result.vec_element == desired_spmv_result);

    mv_result = test_csc.SpM_SpV(sample_s_vec);
    assert(mv_result.vec_element == desired_spmv_result);

    mv_result = test_csc() * sample_s_vec;
    assert(mv_result.vec_element == desired_spmv_result);

    mv_result = test_csc.SpMV_T(sample_d_vec);
    assert(mv_result.vec_element == desired_spmv_t_result);

    mv_result = test_csc.transpose() * sample_d_vec;
    assert(mv_result.vec_element == desired_spmv_t_result);

    mv_result = test_csc.SpM_SpV_T(sample_s_vec);
    assert(mv_result.vec_element == desired_spmv_t_result);

    mv_result = test_csc.transpose() * sample_s_vec;
    assert(mv_result.vec_element == desired_spmv_t_result);

    D_MATRIX mm_result;
    mm_result = test_csc.SpMM(sample_d_mat);
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_csc() * sample_d_mat;
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_csc.SpM_SpM(sample_csc);
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_csc() * sample_csc;
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_csc.SpM_SpM(sample_csr);
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_csc() * sample_csr;
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_csc.SpMM_T(sample_d_mat);
    assert(mm_result.matrix == desired_spmm_t_result);

    mm_result = test_csc.transpose() * sample_d_mat;
    assert(mm_result.matrix == desired_spmm_t_result);

    mm_result = test_csc.SpM_SpM_T(sample_csc);
    assert(mm_result.matrix == desired_spmm_t_result);

    mm_result = test_csc.transpose() * sample_csc;
    assert(mm_result.matrix == desired_spmm_t_result);

    mm_result = test_csc.SpM_SpM_T(sample_csr);
    assert(mm_result.matrix == desired_spmm_t_result);

    mm_result = test_csc.transpose() * sample_csr;
    assert(mm_result.matrix == desired_spmm_t_result);

    std::cout << "Validation for facade_CSC complete" << std::endl;

    return 0;
}