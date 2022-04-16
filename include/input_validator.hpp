#pragma once
#include "PCH.hpp"

/**
 * @class VALIDATOR_INPUT
 *  The class is designed to validate
 *  - inputs from commandline argument
 *  -- Format : target_operation file_one file_two
 *
 *  - targeted file format is supported by the program
 *  -- .mtx, .d_mat, .d_vec, .s_vec
 *
 *  - file format matches with targeted operation
 *  -- i.e. SpMV file_one.mtx file_two.d_vec
 *
 *  - existence of file targeted by input value
 *  - existence of directory targeted by input value
 *
 *  The class is not designed to validate
 *  - targeted file can be opened
 *  - targeted file contains error
 *  - targeted file is not damaged
 *
 *  The member functions of the class is implemented by <filesystem> library.
 *  For compilation, a compiler must support C++17. *
 */
class INPUT_VALIDATOR
{
public:
    enum class target_operation
    {
        SpMV,
        SpMV_T,
        SpMM,
        SpMM_T,
        SpM_SpV,
        SpM_SpV_T,
        SpM_SpM,
        SpM_SpM_T
    };

    INPUT_VALIDATOR(std::string t_operation, std::string input_one, std::string input_two);
    virtual ~INPUT_VALIDATOR();

    void validate_arguments();
    void set_input(std::string t_operation, std::string input_one, std::string input_two);
    target_operation get_targeted_operation() const;

private:
    std::map<std::string, target_operation> operation_list{
        {"SpMV", target_operation::SpMV},
        {"SpMV_T", target_operation::SpMV_T},
        {"SpMM", target_operation::SpMM},
        {"SpMM_T", target_operation::SpMM_T},
        {"SpM_SpV", target_operation::SpM_SpV},
        {"SpM_SpV_T", target_operation::SpM_SpV_T},
        {"SpM_SpM", target_operation::SpM_SpM},
        {"SpM_SpM_T", target_operation::SpM_SpM_T}};
    std::vector<std::string> f_format_list{".dvec", ".svec", ".dmat", ".mtx"};
    std::pair<std::string, std::string> input_num {"One", "Two"};

    std::string m_target_operation;
    target_operation m_targeted_operation;
    std::filesystem::path m_input_one;
    std::filesystem::path m_input_two;

    std::string e_message = "Error in input ";

    void validate_operation(const std::string &target_oper);

    bool validate_existence(const std::filesystem::path &input_path);

    bool validate_is_file(const std::filesystem::path &input_path);

    bool validate_is_directory(const std::filesystem::path &input_path);

    bool validate_format(const std::filesystem::path &input_path, std::string target_format);

    void validate_input(const std::filesystem::path &target_input, std::string required_format, std::string input_num);
};