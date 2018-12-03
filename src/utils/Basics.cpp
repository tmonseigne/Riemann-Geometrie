#include "Basics.hpp"

using namespace Eigen;
using namespace std;

//***********************************************
//******************** BASES ********************
//***********************************************
bool VectorCenter(RowVectorXd& v)
{
	const double mu = v.mean();
	for (size_t i = 0, s = v.size(); i < s; ++i) { v(i) -= mu; }
	return true;
}
//---------------------------------------------------------------------------------------------------

bool VectorCenter(const RowVectorXd& in, RowVectorXd& out)
{
	const double mu = in.mean();
	out = in;
	for (size_t i = 0, s = out.size(); i < s; ++i) { out(i) -= mu; }
	return true;
}
//---------------------------------------------------------------------------------------------------

bool MatrixCenter(MatrixXd& m)
{
	for (size_t i = 0, r = m.rows(), c = m.cols(); i < r; ++i)
	{
		const double mu = m.row(i).mean();
		for (size_t j = 0; j < c; ++j) { m(i, j) -= mu; }
	}
	return true;
}
//---------------------------------------------------------------------------------------------------

bool MatrixCenter(const MatrixXd& in, MatrixXd& out)
{
	out = in;
	for (size_t i = 0, r = out.rows(), c = out.cols(); i < r; ++i)
	{
		const double mu = out.row(i).mean();
		for (size_t j = 0; j < c; ++j) { out(i, j) -= mu; }
	}
	return true;
}
//---------------------------------------------------------------------------------------------------

RowVectorXd GetElements(const RowVectorXd& row, const std::vector<size_t>& index)
{
	const size_t k = index.size();
	RowVectorXd result(k);
	for (size_t i = 0; i < k; ++i)
	{
		result[i] = row[index[i]];
	}
	return result;
}
//---------------------------------------------------------------------------------------------------

bool inRange(const double value, const double min, const double max)
{
	return (min <= value && value <= max);
}
//---------------------------------------------------------------------------------------------------

bool areNotEmpty(const vector<MatrixXd>& matrices)
{
	if (matrices.empty()) { return false; }
	for (const auto& m : matrices) { if (!isNotEmpty(m)) { return false; } }
	return true;
}
//---------------------------------------------------------------------------------------------------

bool isNotEmpty(const MatrixXd& matrix)
{
	return (matrix.rows() != 0 && matrix.cols() != 0);
}
//---------------------------------------------------------------------------------------------------

bool haveSameSize(const MatrixXd& a, const MatrixXd& b)
{
	return (isNotEmpty(a) && a.rows() == b.rows() && a.cols() == b.cols());
}
//---------------------------------------------------------------------------------------------------

bool isSquare(const MatrixXd& matrix)
{
	return (isNotEmpty(matrix) && matrix.rows() == matrix.cols());
}
//---------------------------------------------------------------------------------------------------

bool areSquare(const vector<MatrixXd>& matrices)
{
	if (matrices.empty()) { return false; }
	for (const auto& m : matrices) { if (!isSquare(m)) { return false; } }
	return true;
}
//---------------------------------------------------------------------------------------------------

//***********************************************
//***********************************************
//***********************************************
