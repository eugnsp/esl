#pragma once
#include <mkl_spblas.h>
#include <mkl_types.h>

#include <complex>
#include <cstddef>

namespace es_la::internal
{
#define ES_LA_MKL_SPARSE_CREATE_CSR(T)                                                                                 \
	::sparse_status_t mkl_sparse_create_csr(::sparse_matrix_t&, MKL_UINT n_rows, MKL_UINT n_cols,                      \
		MKL_UINT* rows_start, MKL_UINT* rows_end, MKL_UINT* col_index, T*);

ES_LA_MKL_SPARSE_CREATE_CSR(float)
ES_LA_MKL_SPARSE_CREATE_CSR(double)
ES_LA_MKL_SPARSE_CREATE_CSR(std::complex<float>)
ES_LA_MKL_SPARSE_CREATE_CSR(std::complex<double>)

#define ES_LA_MKL_SPARSE_SET_VALUE(T)                                                                                  \
	::sparse_status_t mkl_sparse_set_value(::sparse_matrix_t, MKL_UINT row, MKL_UINT col, T);

ES_LA_MKL_SPARSE_SET_VALUE(float)
ES_LA_MKL_SPARSE_SET_VALUE(double)
ES_LA_MKL_SPARSE_SET_VALUE(std::complex<float>)
ES_LA_MKL_SPARSE_SET_VALUE(std::complex<double>)

#define ES_LA_MKL_SPARSE_EXPORT_CSR(T)                                                                                 \
	::sparse_status_t mkl_sparse_export_csr(::sparse_matrix_t, ::sparse_index_base_t&, MKL_UINT& n_rows,               \
		MKL_UINT& n_cols, MKL_UINT*& rows_start, MKL_UINT*& rows_end, MKL_UINT*& col_index, T*& values);

ES_LA_MKL_SPARSE_EXPORT_CSR(float)
ES_LA_MKL_SPARSE_EXPORT_CSR(double)
ES_LA_MKL_SPARSE_EXPORT_CSR(std::complex<float>)
ES_LA_MKL_SPARSE_EXPORT_CSR(std::complex<double>)

#define ES_LA_MKL_SPARSE_MM(T)                                                                                         \
	::sparse_status_t mkl_sparse_mm(::sparse_operation_t operation, T alpha, ::sparse_matrix_t handle,                 \
		const ::matrix_descr& descr, ::sparse_layout_t layout, const T* x, std::size_t columns, std::size_t l_dim_x,   \
		T beta, T* y, std::size_t l_dim_y);

ES_LA_MKL_SPARSE_MM(float)
ES_LA_MKL_SPARSE_MM(double)
ES_LA_MKL_SPARSE_MM(std::complex<float>)
ES_LA_MKL_SPARSE_MM(std::complex<double>)
} // namespace es_la::internal
