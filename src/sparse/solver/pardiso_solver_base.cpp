#include <es_la/sparse/solver/pardiso_solver_base.hpp>

namespace es_la::internal
{
Pardiso_solver_base::Params::operator MKL_INT*()
{
	return params_;
}

void Pardiso_solver_base::Params::set_matrix_checker(bool enable)
{
	params_[26] = enable;
}

void Pardiso_solver_base::Params::set_zero_based_indexing()
{
	params_[34] = 1;
}

std::string Pardiso_solver_base::pardiso_error_string(MKL_INT error)
{
	std::string str = "PARDISO error " + std::to_string(error) + ": ";
	switch (error)
	{
	case 0:
		return str + "No error";
	case -1:
		return str + "Input inconsistent";
	case -2:
		return str + "Not enough memory";
	case -3:
		return str + "Reordering problem";
	case -4:
		return str + "Zero pivot, numerical factorization or iterative refinement problem";
	case -5:
		return str + "Unclassified (internal) error";
	case -6:
		return str + "Reordering failed (nonsymmetric real and complex matrices only)";
	case -7:
		return str + "Diagonal matrix is singular";
	case -8:
		return str + "32-bit integer overflow problem";
	case -9:
		return str + "Not enough memory for OOC";
	case -10:
		return str + "Error opening OOC files";
	case -11:
		return str + "Read/write error with OOC files";
	case -12:
		return str + "pardiso_64 called from 32-bit library";
	}

	return str + "Unknown error";
}
} // namespace es_la::internal
