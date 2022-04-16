#include "../include/facade_CSC.hpp"

facade_CSC::facade_CSC(){}

facade_CSC::facade_CSC(const CSC &mat_A) : m_mat_A{mat_A} {}

facade_CSC::facade_CSC(COO &mat_A)
{
    m_convert.convert(mat_A, m_mat_A);
}

facade_CSC::facade_CSC(CSR &mat_A)
{
    m_convert.convert(mat_A, m_mat_A);
}

facade_CSC::facade_CSC(const std::vector<uint32_t> row_idx, const std::vector<uint32_t> col_idx, const std::vector<double> val, const uint32_t num_row, const uint32_t num_col)
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

facade_CSC::~facade_CSC() {}

CSC facade_CSC::get_mat_A() const
{
    return this->m_mat_A;
}

void facade_CSC::set_mat_A(COO &mat_A){
    m_convert.convert(mat_A, m_mat_A);
}

COO facade_CSC::to_COO()
{
    COO result;
    m_alloc.alloc_mat(m_mat_A.mat_data, result);
    m_convert.convert(m_mat_A, result);
    return result;
}

CSR facade_CSC::to_CSR()
{
    CSR result;
    m_alloc.alloc_mat(m_mat_A.mat_data, result);
    m_convert.convert(m_mat_A, result);
    return result;
}

CSC facade_CSC::transpose()
{
    CSC result;
    m_convert.transpose(m_mat_A, result);
    return result;
}

bool facade_CSC::compare(const CSC &target)
{
    return this->m_mat_A == target;
}

bool facade_CSC::compare(const facade_CSC &target)
{
    return this->m_mat_A == target.get_mat_A();
}

D_VECTOR facade_CSC::SpMV(const D_VECTOR &vec_x)
{
    D_VECTOR vec_b;
    m_alloc.alloc_vec(vec_x.vec_data.len_vec, "SpMV", vec_b);
    OPERATION_CSC::SpMV(m_mat_A, vec_x, vec_b);
    return vec_b;
}

D_VECTOR facade_CSC::SpMV_T(const D_VECTOR &vec_x)
{
    D_VECTOR vec_b;
    m_alloc.alloc_vec(vec_x.vec_data.len_vec, "SpMV_T", vec_b);
    OPERATION_CSC::SpMV_T(m_mat_A, vec_x, vec_b);
    return vec_b;
}

D_VECTOR facade_CSC::SpM_SpV(const S_VECTOR &vec_x)
{
    D_VECTOR vec_b;
    m_alloc.alloc_vec(vec_x.vec_data.len_vec, "SpM_SpV", vec_b);
    OPERATION_CSC::SpM_SpV(m_mat_A, vec_x, vec_b);
    return vec_b;
}

D_VECTOR facade_CSC::SpM_SpV_T(const S_VECTOR &vec_x)
{
    D_VECTOR vec_b;
    m_alloc.alloc_vec(vec_x.vec_data.len_vec, "SpM_SpV_T", vec_b);
    OPERATION_CSC::SpM_SpV_T(m_mat_A, vec_x, vec_b);
    return vec_b;
}

D_MATRIX facade_CSC::SpMM(const D_MATRIX &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_row, mat_X.mat_data.num_col, "SpMM", mat_B);
    OPERATION_CSC::SpMM(m_mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX facade_CSC::SpMM_T(const D_MATRIX &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_col, mat_X.mat_data.num_col, "SpMM_T", mat_B);
    OPERATION_CSC::SpMM_T(m_mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX facade_CSC::SpM_SpM(const CSC &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_row, mat_X.mat_data.num_col, "SpM_SpM", mat_B);
    OPERATION_CSC::SpM_SpM(m_mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX facade_CSC::SpM_SpM_T(const CSC &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_col, mat_X.mat_data.num_col, "SpM_SpM_T", mat_B);
    OPERATION_CSC::SpM_SpM_T(m_mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX facade_CSC::SpM_SpM(const CSR &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_row, mat_X.mat_data.num_col, "SpM_SpM", mat_B);
    OPERATION_CSC::SpM_SpM(m_mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX facade_CSC::SpM_SpM_T(const CSR &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_col, mat_X.mat_data.num_col, "SpM_SpM_T", mat_B);
    OPERATION_CSC::SpM_SpM_T(m_mat_A, mat_X, mat_B);
    return mat_B;
}

CSC &facade_CSC::operator()()
{
    return m_mat_A;
}

bool facade_CSC::operator==(const CSC &target)
{
    return compare(target);
}

bool facade_CSC::operator!=(const CSC &target)
{
    return !compare(target);
}

bool facade_CSC::operator==(const facade_CSC &target)
{
    return compare(target);
}

bool facade_CSC::operator!=(const facade_CSC &target)
{
    return !compare(target);
}