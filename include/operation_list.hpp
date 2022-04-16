/**
    This header file contains interface class for following child classes.
        - matrix_coo
        - matrix_csc
        - matrix_csr

    This header file must contains following header files
        - matrix_allocation_manager.hpp
        - matrix_utility.hpp

    This class contains virtual function; therefore, it cannot be instantiacted.
*/
#pragma once
#include "../include/PCH.hpp"
#include "../include/matrix_struct.hpp"
#include "../include/matrix_allocation.hpp"
#include "../include/matrix_convert.hpp"

enum class is_transpose
{
    YES,
    NO
};

class OPERATION_LIST
{
public:
    OPERATION_LIST();
    virtual ~OPERATION_LIST();

    /**
     * SpMV(x, b) => A * x = b where
     * SpMV_T(X, B) => transpose(A) * x = b where
     * A is sparse matrix
     * x is dense vector
     * b is dense vector
     */

    /**
     * SpMM(X, B) => A * X = B and
     * SpMM_T(X, B) => transpose(A) * X = B where
     * A is sparse matrix
     * X is dense matrix
     * B is dense matrix
     */

    /**
     * SpM_SpV(x, b) => A * x = b where
     * SpM_SpV_T(X, B) => transpose(A) * x = b where
     * A is sparse matrix
     * x is sparse vector
     * b is dense vector
     */

    /**
     * SpM_SpM(X, B) -> A * X = B
     * SpM_SpM_T(X, B) -> transpose(A) * X = B where
     * A is sparse matrix
     * X is sparsec matrix
     * B is dense matrix
     */

protected:
    using uINT = uint32_t;
    enum class sort_target
    {
        CSR,
        CSC
    };

    MATRIX_ALLOCATION m_alloc;
    MATRIX_CONVERT m_convert;

    void validate_length(const uint32_t length_one, const uint32_t length_two, is_transpose mode);

    void sort_COO(COO &s_mat, sort_target target);

    bool bin_search_s_vec(const S_VECTOR &s_vec, uint32_t target_index, uint32_t &target_position);

    bool bin_search_s_mat(const std::vector<IDX_VAL> &ind_and_ele, uint32_t l_ptr, uint32_t u_ptr, uint32_t target_index, uint32_t &target_position);

    uint32_t count_nz(const D_VECTOR &d_vec);

    uint32_t count_nz(const D_MATRIX &d_mat);

private:
    struct
    {
        bool operator()(MAT_ELE_DATA one, MAT_ELE_DATA two) const
        {
            if (one.row_index > two.row_index)
            {
                return false;
            }
            else if (one.row_index == two.row_index)
            {
                return two.col_index - one.col_index;
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
            else if (one.col_index == two.col_index)
            {
                return two.row_index - one.row_index;
            }
            else
            {
                return true;
            }
        }
    } sort_for_CSC;
};
