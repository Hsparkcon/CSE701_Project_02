#pragma once
#include "PCH.hpp"
#include "matrix_struct.hpp"

void print_info(const VECTOR_INFO &info);

void print_vec(const D_VECTOR &vec);

void print_vec(const S_VECTOR &vec);

void info_line();

void data_line(uint32_t row, uint32_t col, double value);

void print_info(const MATRIX_INFO &info);

void print_mat(const D_MATRIX &mat);

void print_mat(const COO &mat);

void print_mat(const CSR &mat);

void print_mat(const CSC &mat);

std::ostream &operator<<(std::ostream &out, const D_VECTOR &vec);

std::ostream &operator<<(std::ostream &out, const S_VECTOR &vec);

std::ostream &operator<<(std::ostream &out, const D_MATRIX &mat);

std::ostream &operator<<(std::ostream &out, const COO &mat);

std::ostream &operator<<(std::ostream &out, const CSC &mat);

std::ostream &operator<<(std::ostream &out, const CSR &mat);