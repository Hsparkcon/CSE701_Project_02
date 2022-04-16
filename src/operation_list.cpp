#include "../include/operation_list.hpp"

OPERATION_LIST::OPERATION_LIST() {}

OPERATION_LIST::~OPERATION_LIST() {}

void OPERATION_LIST::validate_length(const uint32_t length_one, const uint32_t length_two, is_transpose mode)
{
    if (length_one != length_two)
    {
        std::string e_message = "Error - Length mismatch\n";
        switch (mode)
        {
        case is_transpose::NO:
            e_message = e_message +
                        "Matrix A's row does not match with Vector's length / Matrix B's column.\n" +
                        "Row          : " + std::to_string(length_one) + "\n" +
                        "Length/Column: " + std::to_string(length_two) + "\n";
            break;
        case is_transpose::YES:
            e_message = e_message +
                        "Matrix A's column does not match with Vector's length / Matrix B's column.\n" +
                        "Column       : " + std::to_string(length_one) + "\n" +
                        "Length/Column: " + std::to_string(length_two) + "\n";
            break;
        }
        throw std::logic_error(e_message);
    }
}

void OPERATION_LIST::sort_COO(COO &s_mat, sort_target target)
{
    switch (target)
    {
    case sort_target::CSR:
        std::sort(s_mat.mat_elements.begin(), s_mat.mat_elements.end(), sort_for_CSR);
        break;
    case sort_target::CSC:
        std::sort(s_mat.mat_elements.begin(), s_mat.mat_elements.end(), sort_for_CSC);
        break;
    }
}

bool OPERATION_LIST::bin_search_s_vec(const S_VECTOR &s_vec, uint32_t target_index, uint32_t &target_position)
{
    int32_t low_ptr = 0;
    int32_t upper_ptr = s_vec.vec_data.num_nz - 1;
    int32_t mid_ptr = 0;

    while (low_ptr <= upper_ptr)
    {
        mid_ptr = (low_ptr + upper_ptr) / 2;

        if (s_vec.vec_element[mid_ptr].index == target_index)
        {
            target_position = mid_ptr;
            return true;
        }
        else if (s_vec.vec_element[mid_ptr].index > target_index)
        {
            upper_ptr = mid_ptr - 1;
        }
        else
        { // s_vec->vec_elements[mid_ptr].index < target_index
            low_ptr = mid_ptr + 1;
        }
    }
    return false;
}

bool OPERATION_LIST::bin_search_s_mat(const std::vector<IDX_VAL> &ind_and_ele, uint32_t l_ptr, uint32_t u_ptr, uint32_t target_index, uint32_t &target_position)
{
    if (l_ptr == u_ptr)
    {
        if (target_index == ind_and_ele[l_ptr].index)
        {
            target_position = l_ptr;
            return true;
        }
        else
        {
            return false;
        }
    }

    uint32_t low_ptr = l_ptr;
    uint32_t upper_ptr = u_ptr - 1;
    uint32_t mid_ptr = 0;
    while (low_ptr <= upper_ptr)
    {
        mid_ptr = (low_ptr + upper_ptr) / 2;

        if (ind_and_ele[mid_ptr].index == target_index)
        {
            target_position = mid_ptr;
            return true;
        }
        else if (ind_and_ele[mid_ptr].index > target_index)
        {
            upper_ptr = mid_ptr - 1;
        }
        else
        { // s_vec->vec_elements[mid_ptr].index < target_index
            low_ptr = mid_ptr + 1;
        }
    }
    return false;
}

uint32_t OPERATION_LIST::count_nz(const D_VECTOR &d_vec)
{
    uint32_t count_nz = 0;
    for (const auto &iter_result : d_vec.vec_element)
    {
        if (iter_result != 0)
            count_nz++;
    }
    return count_nz;
}

uint32_t OPERATION_LIST::count_nz(const D_MATRIX &d_mat)
{
    uint32_t count_nz = 0;
    for (const auto &row : d_mat.matrix)
    {
        for (const auto &col : row)
        {
            if (col != 0)
                count_nz++;
        }
    }

    return count_nz;
}
