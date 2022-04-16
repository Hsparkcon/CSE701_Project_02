#include <cassert>
#include "../include/input_validator.hpp"

std::vector<std::pair<std::tuple<std::string, std::string, std::string>, bool>> true_case{
    {{"SpMV", "sample_mtx.mtx", "sample_dvec.dvec"}, true},
    {{"SpMV_T", "sample_mtx.mtx", "sample_dvec.dvec"}, true},

    {{"SpMM", "sample_mtx.mtx", "sample_dmat.dmat"}, true},
    {{"SpMM_T", "sample_mtx.mtx", "sample_dmat.dmat"}, true},

    {{"SpM_SpV", "sample_mtx.mtx", "sample_svec.svec"}, true},
    {{"SpM_SpV_T", "sample_mtx.mtx", "sample_svec.svec"}, true},

    {{"SpM_SpM", "sample_mtx.mtx", "sample_mtx.mtx"}, true},
    {{"SpM_SpM_T", "sample_mtx.mtx", "sample_mtx.mtx"}, true}};

std::vector<std::pair<std::tuple<std::string, std::string, std::string>, bool>> false_case{
    {{"SpMV", "sample_mtx.mtx", "sample.dvec"}, false},      // file not exist
    {{"SpMV_T", "sample_mtx.m", "sample_dvec.dvec"}, false}, // incorrect file format

    {{"SpM", "sample_mtx.mtx", "sample_dmat.dmat"}, false}, // incorrect operation
    {{"SpMM_T", "sample_mtx.mtx", "sample_dmat.d"}, false}, // incorrect file format

    {{"SpM_Sp", "sample_mtx.mtx", "sample_svec.svec"}, false}, // incorrect operation
    {{"SpM_SpV_T", "sample.mtx", "sample.svec"}, false},       // file not exist

    {{"SpM_", "sample_mtx.mtx", "sample_mtx.mtx"}, false},      // incorrect operation
    {{"SpM_SpM_T", "sample_mtxx.mtx", "sample_mtx.mtx"}, false} // file not exist
};

int main()
{
    std::string t_operation = "";
    std::string input_one = "";
    std::string input_two = "";
    INPUT_VALIDATOR validator(t_operation, input_one, input_two);
    for (const auto &iter_check_list : true_case)
    {
        validator.set_new_input(std::get<0>(iter_check_list.first), std::get<1>(iter_check_list.first), std::get<2>(iter_check_list.first));
        assert(iter_check_list.second == validator.validate_input());
    }
    std::cout << "INPUT_VALIDATOR passed correct input case." << std::endl;

    for (const auto &iter_check_list : false_case)
    {
        validator.set_new_input(std::get<0>(iter_check_list.first), std::get<1>(iter_check_list.first), std::get<2>(iter_check_list.first));
        assert(iter_check_list.second == validator.validate_input());
    }
    std::cout << "INPUT_VALIDATOR passed incorrect input case." << std::endl;
    return 0;

    return 0;
}