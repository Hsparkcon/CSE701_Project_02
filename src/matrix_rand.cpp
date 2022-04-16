#include "../include/matrix_rand.hpp"

MATRIX_RAND::MATRIX_RAND()
{
    /*Do Nothing*/
}

MATRIX_RAND::~MATRIX_RAND()
{
    /*Do Nothing*/
}

void MATRIX_RAND::rand_mat(const MATRIX_INFO &mat_info, const uint32_t num_nz, COO &coo)
{
    validate_nnz(mat_info, num_nz);
    validate_efficiency(mat_info.num_row * mat_info.num_col, num_nz);

    MATRIX_INFO temp_mat_info;
    temp_mat_info.matrix_name = "rand_mat";
    temp_mat_info.num_row = mat_info.num_col;
    temp_mat_info.num_col = mat_info.num_row;
    temp_mat_info.num_nz = num_nz;
    m_alloc.alloc_mat(temp_mat_info, coo);

    std::random_device rd;
    std::mt19937 mt32(rd());
    std::uniform_int_distribution<uint32_t> uid(0, (mat_info.num_row * mat_info.num_col - 1));
    std::uniform_real_distribution<double> urd(-1, 1);

    uint32_t count_filled = 0;
    std::set<uint32_t> used_idx;
    MAT_ELE_DATA temp_ele;
    while (count_filled < num_nz)
    {
        uint32_t rand_idx = uid(mt32);
        if (used_idx.insert(rand_idx).second == true)
        {
            decode_index(rand_idx, temp_mat_info.num_col, temp_ele.row_index, temp_ele.col_index);
            temp_ele.val = urd(mt32);
            coo.mat_elements.push_back(temp_ele);
            count_filled++;
        }
    }
}

void MATRIX_RAND::rand_mat(const MATRIX_INFO &mat_info, const uint32_t num_nz, D_MATRIX &d_mat)
{
    validate_nnz(mat_info, num_nz);

    MATRIX_INFO temp_mat_info;
    temp_mat_info.matrix_name = "rand_mat";
    temp_mat_info.num_row = mat_info.num_col;
    temp_mat_info.num_col = mat_info.num_row;
    temp_mat_info.num_nz = num_nz;
    m_alloc.alloc_mat(temp_mat_info, d_mat);

    std::random_device rd;
    std::mt19937 mt32(rd());
    std::uniform_int_distribution<uint32_t> uid(0, (mat_info.num_row * mat_info.num_col - 1));
    std::uniform_real_distribution<double> urd(-1, 1);

    uint32_t count_filled = 0;
    std::set<uint32_t> used_idx;
    uint32_t row_idx = 0;
    uint32_t col_idx = 0;
    while (count_filled < num_nz)
    {
        uint32_t rand_idx = uid(mt32);
        if (used_idx.insert(rand_idx).second == true)
        {
            decode_index(rand_idx, temp_mat_info.num_col, row_idx, col_idx);
            d_mat.matrix[row_idx][col_idx] = urd(mt32);
            count_filled++;
        }
    }
}

void MATRIX_RAND::rand_vec(const VECTOR_INFO &vec_info, const uint32_t num_nz, S_VECTOR &s_vec)
{
    validate_nnz(vec_info, num_nz);
    validate_efficiency(vec_info.len_vec, num_nz);

    VECTOR_INFO temp_vec_info;
    temp_vec_info.vec_name = "rand_vec";
    temp_vec_info.len_vec = vec_info.len_vec;
    temp_vec_info.num_nz = num_nz;
    m_alloc.alloc_vec(temp_vec_info, s_vec);

    std::random_device rd;
    std::mt19937 mt32(rd());
    std::uniform_int_distribution<uint32_t> uid(0, (vec_info.len_vec - 1));
    std::uniform_real_distribution<double> urd(-1, 1);

    uint32_t count_filled = 0;
    std::set<uint32_t> used_idx;
    IDX_VAL temp_ele;
    while (count_filled < num_nz)
    {
        uint32_t rand_idx = uid(mt32);
        if (used_idx.insert(rand_idx).second == true)
        {
            temp_ele.index = rand_idx;
            temp_ele.val = urd(mt32);
            s_vec.vec_element.push_back(temp_ele);
            count_filled++;
        }
    }
}

void MATRIX_RAND::rand_vec(const VECTOR_INFO &vec_info, const uint32_t num_nz, D_VECTOR &d_vec)
{
    validate_nnz(vec_info, num_nz);

    VECTOR_INFO temp_vec_info;
    temp_vec_info.vec_name = "rand_vec";
    temp_vec_info.len_vec = vec_info.len_vec;
    temp_vec_info.num_nz = num_nz;
    m_alloc.alloc_vec(temp_vec_info, d_vec);

    std::random_device rd;
    std::mt19937 mt32(rd());
    std::uniform_int_distribution<uint32_t> uid(0, (vec_info.len_vec - 1));
    std::uniform_real_distribution<double> urd(-1, 1);

    uint32_t count_filled = 0;
    std::set<uint32_t> used_idx;
    while (count_filled < num_nz)
    {
        uint32_t rand_idx = uid(mt32);
        if (used_idx.insert(rand_idx).second == true)
        {
            d_vec.vec_element[rand_idx] = urd(mt32);
            count_filled++;
        }
    }
}

void MATRIX_RAND::validate_nnz(const MATRIX_INFO &mat_info, const uint32_t requested_num_nz)
{
    uint32_t max_ele_num = mat_info.num_row * mat_info.num_col;
    if (requested_num_nz > max_ele_num)
    {
        std::string e_message;
        e_message =
            "Error At   - Random Matrix Generator\n"
            "Error Type - Requested number of non-zero exceed matrix dimension\n"
            "Max Ele    - " +
            std::to_string(max_ele_num) + "\n"
                                          "Requested  - " +
            std::to_string(requested_num_nz) + "\n";
        throw std::logic_error(e_message);
    }
}

void MATRIX_RAND::validate_nnz(const VECTOR_INFO &vec_info, const uint32_t requested_num_nz)
{
    if (requested_num_nz > vec_info.len_vec)
    {
        std::string e_message;
        e_message = "Error At   - Random Vector Generator\n"
                    "Error Type - Requested number of non-zero exceed vector length\n"
                    "Max Ele    - " +
                    std::to_string(vec_info.len_vec) + "\n"
                                                       "Requested  - " +
                    std::to_string(requested_num_nz) + "\n";
        throw std::logic_error(e_message);
    }
}

void MATRIX_RAND::validate_efficiency(const uint32_t container_size, const uint32_t requested_num_nz)
{
    auto usage_sparse = requested_num_nz * (sizeof(double) + 2 * sizeof(uint32_t));
    auto usage_dense = container_size * sizeof(double);
    if (usage_sparse > usage_dense)
    {
        std::string e_message;
        e_message = "Error at      - Random Matrix/Vector Generator\n"
                    "Error Type    - Size of sparse mat/vec is bigger than size of dense mat/vec\n"
                    "Sparse usage  - " +
                    std::to_string(usage_sparse) + " bytes\n"
                                                   "Dense usage   - " +
                    std::to_string(usage_dense) + " bytes\n";
        throw std::logic_error(e_message);
    }
}

void MATRIX_RAND::decode_index(const uint32_t &encoded_idx, const uint32_t &num_col, uint32_t &decoded_row, uint32_t &decoded_col)
{
    decoded_row = encoded_idx / num_col;
    decoded_col = encoded_idx % num_col;
}
