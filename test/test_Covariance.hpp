///-------------------------------------------------------------------------------------------------
/// 
/// \file test_UtilsCovariance.hpp
/// \brief Tests for Riemannian Geometry Utils : Covariance
/// \author Thibaut Monseigne (Inria).
/// \version 1.0.
/// \date 09/01/2019.
/// \copyright <a href="https://choosealicense.com/licenses/agpl-3.0/">GNU Affero General Public License v3.0</a>.
/// 
///-------------------------------------------------------------------------------------------------

#pragma once

#include "gtest/gtest.h"
#include "misc.hpp"
#include "Init.hpp"

#include <geometry/Covariance.hpp>

//---------------------------------------------------------------------------------------------------
class Tests_Covariances : public testing::Test
{
protected:
	std::vector<std::vector<Eigen::MatrixXd>> m_dataSet;

	void SetUp() override { m_dataSet = InitDataset::Dataset(); }
};

//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
TEST_F(Tests_Covariances, Covariance_Matrix_COR)
{
	std::vector<std::vector<Eigen::MatrixXd>> calc, ref = InitCovariance::COR::Dataset();
	calc.resize(m_dataSet.size());
	for (size_t k = 0; k < m_dataSet.size(); ++k)
	{
		calc[k].resize(m_dataSet[k].size());
		for (size_t i = 0; i < m_dataSet[k].size(); ++i)
		{
			CovarianceMatrix(m_dataSet[k][i], calc[k][i], Geometry::EEstimator::COR, Geometry::EStandardization::None);
			const std::string title = "Covariance Matrix COR Sample [" + std::to_string(k) + "][" + std::to_string(i) + "]";
			EXPECT_TRUE(isAlmostEqual(ref[k][i], calc[k][i])) << ErrorMsg(title, ref[k][i], calc[k][i]);
		}
	}
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
TEST_F(Tests_Covariances, Covariance_Matrix_COV)
{
	std::vector<std::vector<Eigen::MatrixXd>> calc, ref = InitCovariance::COV::Dataset();
	calc.resize(m_dataSet.size());
	for (size_t k = 0; k < m_dataSet.size(); ++k)
	{
		calc[k].resize(m_dataSet[k].size());
		for (size_t i = 0; i < m_dataSet[k].size(); ++i)
		{
			CovarianceMatrix(m_dataSet[k][i], calc[k][i], Geometry::EEstimator::COV, Geometry::EStandardization::None);
			const std::string title = "Covariance Matrix COV Sample [" + std::to_string(k) + "][" + std::to_string(i) + "]";
			EXPECT_TRUE(isAlmostEqual(ref[k][i], calc[k][i])) << ErrorMsg(title, ref[k][i], calc[k][i]);
		}
	}
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
TEST_F(Tests_Covariances, Covariance_Matrix_LWF)
{
	std::vector<std::vector<Eigen::MatrixXd>> calc, ref = InitCovariance::LWF::Reference();
	calc.resize(m_dataSet.size());
	for (size_t k = 0; k < m_dataSet.size(); ++k)
	{
		calc[k].resize(m_dataSet[k].size());
		for (size_t i = 0; i < m_dataSet[k].size(); ++i)
		{
			CovarianceMatrix(m_dataSet[k][i], calc[k][i], Geometry::EEstimator::LWF, Geometry::EStandardization::Center);
			const std::string title = "Covariance Matrix LWF Sample [" + std::to_string(k) + "][" + std::to_string(i) + "]";
			EXPECT_TRUE(isAlmostEqual(ref[k][i], calc[k][i])) << ErrorMsg(title, ref[k][i], calc[k][i]);
		}
	}
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
TEST_F(Tests_Covariances, Covariance_Matrix_MCD)
{
	std::cout << "Not implemented" << std::endl;
	std::vector<std::vector<Eigen::MatrixXd>> calc;
	//std::vector<std::vector<Eigen::MatrixXd>> ref = InitCovariance::MCD::Reference();
	calc.resize(m_dataSet.size());
	for (size_t k = 0; k < m_dataSet.size(); ++k)
	{
		calc[k].resize(m_dataSet[k].size());
		for (size_t i = 0; i < m_dataSet[k].size(); ++i)
		{
			CovarianceMatrix(m_dataSet[k][i], calc[k][i], Geometry::EEstimator::MCD, Geometry::EStandardization::Center);
			//const std::string title = "Covariance Matrix MCD Sample [" + std::to_string(k) + "][" + std::to_string(i) + "]";
			//EXPECT_TRUE(isAlmostEqual(ref[k][i], calc[k][i])) << ErrorMsg(title, ref[k][i], calc[k][i]);
		}
	}
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
TEST_F(Tests_Covariances, Covariance_Matrix_OAS)
{
	std::vector<std::vector<Eigen::MatrixXd>> calc, ref = InitCovariance::OAS::Reference();
	calc.resize(m_dataSet.size());
	for (size_t k = 0; k < m_dataSet.size(); ++k)
	{
		calc[k].resize(m_dataSet[k].size());
		for (size_t i = 0; i < m_dataSet[k].size(); ++i)
		{
			CovarianceMatrix(m_dataSet[k][i], calc[k][i], Geometry::EEstimator::OAS, Geometry::EStandardization::Center);
			const std::string title = "Covariance Matrix OAS Sample [" + std::to_string(k) + "][" + std::to_string(i) + "]";
			EXPECT_TRUE(isAlmostEqual(ref[k][i], calc[k][i])) << ErrorMsg(title, ref[k][i], calc[k][i]);
		}
	}
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
TEST_F(Tests_Covariances, Covariance_Matrix_SCM)
{
	std::vector<std::vector<Eigen::MatrixXd>> calc, ref = InitCovariance::SCM::Reference();
	calc.resize(m_dataSet.size());
	for (size_t k = 0; k < m_dataSet.size(); ++k)
	{
		calc[k].resize(m_dataSet[k].size());
		for (size_t i = 0; i < m_dataSet[k].size(); ++i)
		{
			CovarianceMatrix(m_dataSet[k][i], calc[k][i], Geometry::EEstimator::SCM, Geometry::EStandardization::None);
			const std::string title = "Covariance Matrix SCM Sample [" + std::to_string(k) + "][" + std::to_string(i) + "]";
			EXPECT_TRUE(isAlmostEqual(ref[k][i], calc[k][i])) << ErrorMsg(title, ref[k][i], calc[k][i]);
		}
	}
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
TEST_F(Tests_Covariances, Covariance_Matrix_IDE)
{
	std::vector<std::vector<Eigen::MatrixXd>> calc;
	const Eigen::MatrixXd ref = Eigen::MatrixXd::Identity(NB_CHAN, NB_CHAN);
	calc.resize(m_dataSet.size());
	for (size_t k = 0; k < m_dataSet.size(); ++k)
	{
		calc[k].resize(m_dataSet[k].size());
		for (size_t i = 0; i < m_dataSet[k].size(); ++i)
		{
			CovarianceMatrix(m_dataSet[k][i], calc[k][i], Geometry::EEstimator::IDE, Geometry::EStandardization::None);
			const std::string title = "Covariance Matrix IDE Sample [" + std::to_string(k) + "][" + std::to_string(i) + "]";
			EXPECT_TRUE(isAlmostEqual(ref, calc[k][i])) << ErrorMsg(title, ref, calc[k][i]);
		}
	}
}
//---------------------------------------------------------------------------------------------------
