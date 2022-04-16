#include "../include/matrix_struct.hpp"
#include "test_cases.hpp"

template <typename T>
void validate_operator_overload(T &input_one, T &input_two)
{
    assert((input_one == input_two));
    assert(!(input_one != input_two));
}

int main()
{
    MATRIX_INFO temp_mat_info_one{"null", 1, 2, 3};
    MATRIX_INFO temp_mat_info_two{"null", 1, 2, 3};
    validate_operator_overload(temp_mat_info_one, temp_mat_info_two);

    VECTOR_INFO temp_vec_info_one{"null", 1, 2};
    VECTOR_INFO temp_vec_info_two{"null", 1, 2};
    validate_operator_overload(temp_vec_info_one, temp_vec_info_two);

    MAT_ELE_DATA temp_mat_ele_one{1, 2, 3};
    MAT_ELE_DATA temp_mat_ele_two{1, 2, 3};
    validate_operator_overload(temp_mat_ele_one, temp_mat_ele_two);

    IDX_VAL test_idx_val_one{1, 10};
    IDX_VAL test_idx_val_two{1, 10};
    validate_operator_overload(test_idx_val_one, test_idx_val_two);

    D_MATRIX copy_dmat = sample_d_mat;
    validate_operator_overload(copy_dmat, sample_d_mat);

    COO copy_coo = sample_coo;
    validate_operator_overload(copy_coo, sample_coo);

    CSR copy_csr = sample_csr;
    validate_operator_overload(copy_csr, sample_csr);

    CSC copy_csc = sample_csc;
    validate_operator_overload(copy_csc, sample_csc);

    D_VECTOR copy_dvec = sample_d_vec;
    validate_operator_overload(copy_dvec, sample_d_vec);

    S_VECTOR copy_svec = sample_s_vec;
    validate_operator_overload(copy_svec, sample_s_vec);

    std::cout << "Validation for struct operator overload complete."
              << std::endl;

    return 0;
}
