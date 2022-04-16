#include "../include/facade_COO.hpp"

facade_COO::facade_COO(){

}

facade_COO::facade_COO(const COO &mat_A) : m_mat_A{mat_A}
{
    // Do nothing
}

facade_COO::facade_COO(CSR &mat_A)
{
    m_convert.convert(mat_A, m_mat_A);
}

facade_COO::facade_COO(CSC &mat_A)
{
    m_convert.convert(mat_A, m_mat_A);
}

facade_COO::facade_COO(
    const std::vector<uint32_t> &row_idx,
    const std::vector<uint32_t> &col_idx,
    const std::vector<double> &val,
    const uint32_t num_row,
    const uint32_t num_col)
{
    m_convert.convert(row_idx, col_idx, val, num_row, num_col, m_mat_A);
}

facade_COO::~facade_COO()
{
    // Do nothing
}

COO facade_COO::get_mat_A() const
{
    return this->m_mat_A;
}

void facade_COO::set_mat_A(const COO& new_COO){
    this->m_mat_A = new_COO;
}

CSC facade_COO::to_CSC()
{
    CSC result;
    m_alloc.alloc_mat(m_mat_A.mat_data, result);
    m_convert.convert(m_mat_A, result);
    return result;
}

CSR facade_COO::to_CSR()
{
    CSR result;
    m_alloc.alloc_mat(m_mat_A.mat_data, result);
    m_convert.convert(m_mat_A, result);
    return result;
}

COO facade_COO::transpose()
{
    COO result;
    m_convert.transpose(m_mat_A, result);
    return result;
}

bool facade_COO::compare(const COO &target)
{
    return this->m_mat_A == target;
}

bool facade_COO::compare(const facade_COO &target)
{
    return this->m_mat_A == target.get_mat_A();
}

D_VECTOR facade_COO::SpMV(const D_VECTOR &vec_x)
{
    D_VECTOR vec_b;
    m_alloc.alloc_vec(vec_x.vec_data.len_vec, "SpMV", vec_b);
    OPERATION_COO::SpMV(m_mat_A, vec_x, vec_b);
    return vec_b;
}

D_VECTOR facade_COO::SpMV_T(const D_VECTOR &vec_x)
{
    D_VECTOR vec_b;
    m_alloc.alloc_vec(vec_x.vec_data.len_vec, "SpMV_T", vec_b);
    OPERATION_COO::SpMV_T(m_mat_A, vec_x, vec_b);
    return vec_b;
}

D_VECTOR facade_COO::SpM_SpV(const S_VECTOR &vec_x)
{
    D_VECTOR vec_b;
    m_alloc.alloc_vec(vec_x.vec_data.len_vec, "SpM_SpV", vec_b);
    OPERATION_COO::SpM_SpV(m_mat_A, vec_x, vec_b);
    return vec_b;
}

D_VECTOR facade_COO::SpM_SpV_T(const S_VECTOR &vec_x)
{
    D_VECTOR vec_b;
    m_alloc.alloc_vec(vec_x.vec_data.len_vec, "SpM_SpV_T", vec_b);
    OPERATION_COO::SpM_SpV_T(m_mat_A, vec_x, vec_b);
    return vec_b;
}

D_MATRIX facade_COO::SpMM(const D_MATRIX &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_row, mat_X.mat_data.num_col, "SpMM", mat_B);
    OPERATION_COO::SpMM(m_mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX facade_COO::SpMM_T(const D_MATRIX &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_col, mat_X.mat_data.num_col, "SpMM_T", mat_B);
    OPERATION_COO::SpMM_T(m_mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX facade_COO::SpM_SpM(const CSC &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_row, mat_X.mat_data.num_col, "SpM_SpM", mat_B);
    OPERATION_COO::SpM_SpM(m_mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX facade_COO::SpM_SpM_T(const CSC &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_col, mat_X.mat_data.num_col, "SpM_SpM_T", mat_B);
    OPERATION_COO::SpM_SpM_T(m_mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX facade_COO::SpM_SpM(const CSR &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_row, mat_X.mat_data.num_col, "SpM_SpM", mat_B);
    OPERATION_COO::SpM_SpM(m_mat_A, mat_X, mat_B);
    return mat_B;
}

D_MATRIX facade_COO::SpM_SpM_T(const CSR &mat_X)
{
    D_MATRIX mat_B;
    m_alloc.alloc_mat(m_mat_A.mat_data.num_col, mat_X.mat_data.num_col, "SpM_SpM_T", mat_B);
    OPERATION_COO::SpM_SpM_T(m_mat_A, mat_X, mat_B);
    return mat_B;
}

COO &facade_COO::operator()()
{
    return m_mat_A;
}

bool facade_COO::operator==(const COO &target)
{
    return compare(target);
}

bool facade_COO::operator!=(const COO &target)
{
    return !compare(target);
}

bool facade_COO::operator==(const facade_COO &target)
{
    return compare(target);
}

bool facade_COO::operator!=(const facade_COO &target)
{
    return !compare(target);
}