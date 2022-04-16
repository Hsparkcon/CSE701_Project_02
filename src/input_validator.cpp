#include "../include/input_validator.hpp"

INPUT_VALIDATOR::INPUT_VALIDATOR(std::string t_operation, std::string input_one, std::string input_two) : m_target_operation{t_operation}, m_input_one{input_one}, m_input_two{input_two} {}
INPUT_VALIDATOR::~INPUT_VALIDATOR() {}

void INPUT_VALIDATOR::validate_arguments()
{
    validate_operation(m_target_operation);

    validate_input(this->m_input_one, f_format_list[3], input_num.first);

    std::string input_two_format;
    switch (m_targeted_operation)
    {
    case target_operation::SpMV:
        input_two_format = f_format_list[0];
        break;

    case target_operation::SpMV_T:
        input_two_format = f_format_list[0];
        break;

    case target_operation::SpM_SpV:
        input_two_format = f_format_list[1];
        break;

    case target_operation::SpM_SpV_T:
        input_two_format = f_format_list[1];
        break;

    case target_operation::SpMM:
        input_two_format = f_format_list[2];
        break;

    case target_operation::SpMM_T:
        input_two_format = f_format_list[2];
        break;

    case target_operation::SpM_SpM:
        input_two_format = f_format_list[3];
        break;

    case target_operation::SpM_SpM_T:
        input_two_format = f_format_list[3];
        break;
    }
    validate_input(this->m_input_two, input_two_format, input_num.second);
}

void INPUT_VALIDATOR::set_input(std::string t_operation, std::string input_one, std::string input_two)
{
    m_target_operation = t_operation;
    m_input_one = std::filesystem::path(input_one);
    m_input_two = std::filesystem::path(input_two);
    this->validate_arguments();
}

INPUT_VALIDATOR::target_operation INPUT_VALIDATOR::get_targeted_operation() const
{
    return m_targeted_operation;
}

void INPUT_VALIDATOR::validate_operation(const std::string &target_oper)
{
    auto iter_operation_list = operation_list.find(target_oper);

    if (iter_operation_list == operation_list.end())
    {
        e_message = e_message + "\n"
                                "Targeted operation - " +
                    m_target_operation + " - is not exist.";
        throw std::invalid_argument(e_message);
    }

    m_targeted_operation = iter_operation_list->second;
}

bool INPUT_VALIDATOR::validate_existence(const std::filesystem::path &input_path)
{
    if (std::filesystem::exists(input_path) == false)
    {
        return false;
    }
    return true;
}

bool INPUT_VALIDATOR::validate_is_file(const std::filesystem::path &input_path)
{
    if (std::filesystem::is_regular_file(input_path) == false)
    {
        return false;
    }
    return true;
}

bool INPUT_VALIDATOR::validate_is_directory(const std::filesystem::path &input_path)
{
    if (std::filesystem::is_directory(input_path) == false)
    {
        e_message = "Given input - " + input_path.string() + " - is not a directory.";
        throw std::invalid_argument(e_message);
    }
    return true;
}

bool INPUT_VALIDATOR::validate_format(const std::filesystem::path &input_path, std::string target_format)
{
    if (input_path.extension() != target_format)
    {
        return false;
    }
    return true;
}

void INPUT_VALIDATOR::validate_input(const std::filesystem::path &target_input, std::string required_format, std::string input_num)
{
    if (validate_existence(target_input) == false)
    {
        e_message = e_message + input_num + "\n"
                                            "Given input - " +
                    target_input.string() + " - is not existing.";
        throw std::invalid_argument(e_message);
    }

    if (validate_is_file(target_input) == false)
    {
        e_message = e_message + input_num + "\n"
                                            "Given input - " +
                    target_input.string() + " - is not a file.";
        throw std::invalid_argument(e_message);
    }

    if (validate_format(target_input, required_format) == false)
    {
        e_message = e_message + input_num + "\n"
                                            "Given file format is invalided.\n"
                                            "Input file format needs to be " +
                    required_format + "\n"
                                      "But received format is " +
                    target_input.extension().string();
        throw std::invalid_argument(e_message);
    }
}
