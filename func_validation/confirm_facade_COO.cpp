#include "test_cases.hpp"
#include "../include/facade_COO.hpp"

int main(){
    facade_COO test_coo(sample_coo);

    assert(test_coo.to_CSC() == sample_csc);
    assert(test_coo.to_CSR() == sample_csr);

    D_VECTOR mv_result;
    mv_result = test_coo.SpMV(sample_d_vec);
    assert(mv_result.vec_element == desired_spmv_result);

    mv_result = test_coo() * sample_d_vec;
    assert(mv_result.vec_element == desired_spmv_result);

    mv_result = test_coo.SpM_SpV(sample_s_vec);
    assert(mv_result.vec_element == desired_spmv_result);

    mv_result = test_coo() * sample_s_vec;
    assert(mv_result.vec_element == desired_spmv_result);

    mv_result = test_coo.SpMV_T(sample_d_vec);
    assert(mv_result.vec_element == desired_spmv_t_result);

    mv_result = test_coo.transpose() * sample_d_vec;
    assert(mv_result.vec_element == desired_spmv_t_result);

    mv_result = test_coo.SpM_SpV_T(sample_s_vec);
    assert(mv_result.vec_element == desired_spmv_t_result);

    mv_result = test_coo.transpose() * sample_s_vec;
    assert(mv_result.vec_element == desired_spmv_t_result);

    D_MATRIX mm_result;
    mm_result = test_coo.SpMM(sample_d_mat);
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_coo() * sample_d_mat;
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_coo.SpM_SpM(sample_csc);
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_coo() * sample_csc;
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_coo.SpM_SpM(sample_csr);
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_coo() * sample_csr;
    assert(mm_result.matrix == desired_spmm_result);

    mm_result = test_coo.SpMM_T(sample_d_mat);
    assert(mm_result.matrix == desired_spmm_t_result);

    mm_result = test_coo.transpose() * sample_d_mat;
    assert(mm_result.matrix == desired_spmm_t_result);

    mm_result = test_coo.SpM_SpM_T(sample_csc);
    assert(mm_result.matrix == desired_spmm_t_result);

    mm_result = test_coo.transpose() * sample_csc;
    assert(mm_result.matrix == desired_spmm_t_result);

    mm_result = test_coo.SpM_SpM_T(sample_csr);
    assert(mm_result.matrix == desired_spmm_t_result);

    mm_result = test_coo.transpose() * sample_csr;
    assert(mm_result.matrix == desired_spmm_t_result);

    std::cout << "Validation for facade_COO complete" << std::endl;

    return 0;
}