#include "test_cases.hpp"
#include "../include/io_data.hpp"

template <typename T>
void validate_io(T &input_one, T &input_two)
{
    assert(input_one == input_two);
}

int main()
{
    IO_DATA data_io(IO_MODE::ANSI_BASE);

    COO validate_mtx;
    data_io.write_mat("val_mtx.mtx", sample_coo);
    data_io.load_mat("val_mtx.mtx", validate_mtx);
    validate_io(sample_coo, validate_mtx);

    D_VECTOR validate_dvec;
    data_io.write_vec("val_dvec.dvec", sample_d_vec);
    data_io.load_vec("val_dvec.dvec", validate_dvec);
    validate_io(sample_d_vec, validate_dvec);

    S_VECTOR validate_svec;
    data_io.write_vec("val_svec.svec", sample_s_vec);
    data_io.load_vec("val_svec.svec", validate_svec);
    validate_io(sample_s_vec, validate_svec);

    std::cout << "Validation for DATA I/O complete." << std::endl;

    return 0;
}