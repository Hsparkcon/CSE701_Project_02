#include <cassert>
#include "../include/PCH.hpp"
#include "../include/matrix_rand.hpp"

MATRIX_INFO sample_mat_info = (MATRIX_INFO){"sample", 10, 10, 20};
std::vector<uint32_t> true_nz_mat{10, 20, 30, 40, 50};

VECTOR_INFO sample_vec_info = (VECTOR_INFO){"sample", 10, 5};
std::vector<uint32_t> true_nz_vec{1, 2, 3, 4, 5};

int main()
{
    MATRIX_RAND gen_rand;
    COO *rand_coo = nullptr;
    for (uint32_t test_cases = 0; test_cases < true_nz_mat.size(); test_cases++)
    {
        rand_coo = new COO();
        gen_rand.rand_mat(sample_mat_info, true_nz_mat[test_cases], *rand_coo);
        assert(rand_coo->mat_elements.size() == true_nz_mat[test_cases]);
        delete rand_coo;
        rand_coo = nullptr;
    }

    D_MATRIX *rand_d_mat = nullptr;
    for (uint32_t test_cases = 0; test_cases < true_nz_mat.size(); test_cases++)
    {
        rand_d_mat = new D_MATRIX();
        gen_rand.rand_mat(sample_mat_info, true_nz_mat[test_cases], *rand_d_mat);
        assert(rand_d_mat->mat_data.num_nz == true_nz_mat[test_cases]);
        delete rand_d_mat;
        rand_d_mat = nullptr;
    }

    S_VECTOR *rand_s_vec = nullptr;
    for (uint32_t test_cases = 0; test_cases < true_nz_vec.size(); test_cases++)
    {
        rand_s_vec = new S_VECTOR();
        gen_rand.rand_vec(sample_vec_info, true_nz_vec[test_cases], *rand_s_vec);
        assert(rand_s_vec->vec_element.size() == true_nz_vec[test_cases]);
        delete rand_s_vec;
        rand_s_vec = nullptr;
    }

    D_VECTOR *rand_d_vec = nullptr;
    for (uint32_t test_cases = 0; test_cases < true_nz_vec.size(); test_cases++)
    {
        rand_d_vec = new D_VECTOR();
        gen_rand.rand_vec(sample_vec_info, true_nz_vec[test_cases], *rand_d_vec);
        assert(rand_d_vec->vec_data.num_nz == true_nz_vec[test_cases]);
        delete rand_d_vec;
        rand_d_vec = nullptr;
    }

    std::cout << "Validation for rand matrix complete" << std::endl;

    return 0;
}