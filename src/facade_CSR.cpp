#include "../include/facade_CSR.hpp"

facade_CSR::facade_CSR() {}

facade_CSR::facade_CSR(const CSR &mat_A) : m_mat_A{mat_A} {}

facade_CSR::facade_CSR(COO &mat_A)
{
    m_convert.convert(mat_A, m_mat_A);
}

facade_CSR::facade_CSR(CSC &mat_A)
{
    m_convert.convert(mat_A, m_mat_A);
}

facade_CSR::facade_CSR(const std::vector<uint32_t> row_idx, const std::vector<uint32_t> col_idx, const std::vector<double> val, const uint32_t num_row, const uint32_t num_col)
{
    if ((row_idx.size() != col_idx.size()) || (row_idx.size() != val.size()))
    {
        std::string e_message = "Logic Error\n"
                                "Length mitmatch between the given vectors.\n"
                                "row idx - " +
                                std::to_string(row_idx.size()) + "\n"
                                                                 "col idx - " +
                                std::to_string(col_idx.size()) + "\n"
                                                                 "value - " +
                                std::to_string(val.size()) + "\n";
        throw std::logic_error(e_message);
    }

    COO *temp = new COO();
    uint32_t track_row = 0;
    uint32_t track_col = 0;
    temp->mat_elements = std::vector<MAT_ELE_DATA>(temp->mat_data.num_nz, MAT_ELE_DATA{0, 0, 0});
    for (uint32_t ele_A = 0; ele_A < temp->mat_data.num_nz; ele_A++)
    {
        track_row = track_row < row_idx[ele_A] ? row_idx[ele_A] : track_row;
        temp->mat_elements[ele_A].row_index = row_idx[ele_A];

        track_col = track_row < col_idx[ele_A] ? col_idx[ele_A] : track_row;
        temp->mat_elements[ele_A].col_index = col_idx[ele_A];

        temp->mat_elements[ele_A].val = val[ele_A];
    }

    if (track_row > num_row - 1 || track_col > num_col - 1)
    {
        std::string e_message = "Logic Error\n"
                                "One of Index exceed matrix dimension.\n"
                                "Row Limit - " +
                                std::to_string(num_row - 1) + "\n"
                                                              "Row Index - " +
                                std::to_string(track_row) + "\n"
                                                            "Col Limit - " +
                                std::to_string(num_col - 1) + "\n"
                                                              "Col Index - " +
                                std::to_string(track_col) + "\n";
        throw std::logic_error(e_message);
    }

    temp->mat_data.matrix_name = "NONE";
    temp->mat_data.num_row = num_row;
    temp->mat_data.num_col = num_col;
    temp->mat_data.num_nz = (uint32_t)temp->mat_elements.size();
    m_convert.convert(*temp, m_mat_A);
}

facade_CSR::~facade_CSR() {}

CSR facade_CSR::get_mat_A() const
{
    return this->m_mat_A;
}

void facade_CSR::set_mat_A(COO &mat_A)
{
    m_convert.convert(mat_A, m_mat_A);
}

COO facade_CSR::to_COO()
{
    COO result;
    m_alloc.alloc_mat(m_mat_A.mat_data, result);
    m_convert.convert(m_mat_A, result);
    return result;
}

CSC facade_CSR::to_CSC()
{
    CSC result;
    m_alloc.alloc_mat(m_mat_A.mat_data, result);
    m_convert.convert(m_mat_A, result);
    return result;
}

CSR facade_CSR::transpose()
{
    CSR result;
    m_convert.transpose(m_mat_A, result);
    return result;
}

bool facade_CSR::compare(const CSR &target)
{
    return this->m_mat_A == target;
}

bool facade_CSR::compare(const facade_CSR &target)
{
    return this->m_mat_A == target.get_mat_A();
}

D_VECTOR facade_CSR::SpMV(const D_VECTOR &vec_x)
{
    D_VECTOR vec_b;
    m_alloc.alloc_vec(vec_x.vec_data.len_vec, "SpMV", vec_b);
    OPERATION_CSR::SpMV(m_mat_A, vec_x, vec_b);
    return vec_b;
}

D_VECTOR facade_CSR::SpMV_T(const D_VECTOR &vec_x)
{
    D_VECTOR vec_b;
    m_alloc.alloc_vec(vec_x.vec_data.len_vec, "SpMV_T", vec_b);
    OPERATION_CSR::SpMV_T(m_mat_A, vec_x, vec_b);
    return vec_b;
}

D_VECTOR facade_CSR::SpM_SpV(const S_VECTOR &vec_x)
{
    D_VECTOR vec_b;
    m_alloc.alloc_vec(vec_x.vec_data.len_vec, "SpM_SpV", vec_b);
    OPERATION_CSR::SpM_SpV(m_mat_A, vec_x, vec_b);
    return vec_b;
}

D_VECTOR facade_CSR::SpM_SpV_T(const S_VECTOR &vec_x)
{
    D_VECTOR vec_b;
    m_alloc.alloc_vec(vec_x.vec_data.len_vec, "SpM_SpV_T", vec_b);
    OPERATION_CSR::SpM_SpV_T(m_mat_A, vec_x, vec_b);
    return vec_b;
}

D_MATRIX facade_CSR::SpMM(const D_MATRIX &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_row, mat_X.mat_data.num_col, "SpMM", mat_B);
    OPERATION_CSR::SpMM(m_mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX facade_CSR::SpMM_T(const D_MATRIX &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_col, mat_X.mat_data.num_col, "SpMM_T", mat_B);
    OPERATION_CSR::SpMM_T(m_mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX facade_CSR::SpM_SpM(const CSC &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_row, mat_X.mat_data.num_col, "SpM_SpM", mat_B);
    OPERATION_CSR::SpM_SpM(m_mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX facade_CSR::SpM_SpM_T(const CSC &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_col, mat_X.mat_data.num_col, "SpM_SpM_T", mat_B);
    OPERATION_CSR::SpM_SpM_T(m_mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX facade_CSR::SpM_SpM(const CSR &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_row, mat_X.mat_data.num_col, "SpM_SpM", mat_B);
    OPERATION_CSR::SpM_SpM(m_mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX facade_CSR::SpM_SpM_T(const CSR &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_col, mat_X.mat_data.num_col, "SpM_SpM_T", mat_B);
    OPERATION_CSR::SpM_SpM_T(m_mat_A, mat_X, mat_B);
    return mat_B;
}

CSR &facade_CSR::operator()()
{
    return m_mat_A;
}

bool facade_CSR::operator==(const CSR &target)
{
    return compare(target);
}

bool facade_CSR::operator!=(const CSR &target)
{
    return !compare(target);
}

bool facade_CSR::operator==(const facade_CSR &target)
{
    return compare(target);
}

bool facade_CSR::operator!=(const facade_CSR &target)
{
    return !compare(target);
}
