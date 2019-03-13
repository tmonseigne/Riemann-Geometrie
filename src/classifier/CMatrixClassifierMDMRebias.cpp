#include "CMatrixClassifierMDMRebias.hpp"
#include "utils/Mean.hpp"
#include "utils/Distance.hpp"
#include "utils/Basics.hpp"
#include "utils/Geodesic.hpp"
#include <unsupported/Eigen/MatrixFunctions> // SQRT of Matrix
#include <iostream>

using namespace std;
using namespace Eigen;
using namespace tinyxml2;


//**********************
//***** Classifier *****
//**********************

///-------------------------------------------------------------------------------------------------
bool CMatrixClassifierMDMRebias::train(const vector<vector<MatrixXd>>& datasets)
{
	//Rebias Reference
	Mean(Vector2DTo1D(datasets), m_Rebias, m_Metric);				// Compute Rebias reference
	const MatrixXd isR = m_Rebias.sqrt().inverse();					// Square root & Inverse Square root of Rebias matrix => isR

	setClassCount(datasets.size());									// Change the number of classes if needed
	for (size_t i = 0; i < m_classCount; ++i)
	{
		m_NbTrials[i] = datasets[i].size();
		vector<MatrixXd> newDatas;									// Create new dataset trasnforme with Rebias
		newDatas.reserve(m_NbTrials[i]);
		for (const auto& data : datasets[i]) { newDatas.emplace_back(isR * data * isR.transpose()); }	// Transforme dataset for class i
		if (!Mean(newDatas, m_Means[i], m_Metric)) { return false; }	// Compute the mean of each class
	}
	m_NbClassify = 0;												// Used for Rebias Reference adaptation
	return true;
}
///-------------------------------------------------------------------------------------------------

///-------------------------------------------------------------------------------------------------
bool CMatrixClassifierMDMRebias::classify(const MatrixXd& sample, size_t& classId, std::vector<double>& distance,
										  std::vector<double>& probability, const EAdaptations adaptation, const size_t& realClassId)
{
	if (!isSquare(sample)) { return false; }					// Verification if it's a square matrix 
	double distMin = std::numeric_limits<double>::max();		// Init of distance min
	m_NbClassify++;												// Update number of classify
	// Change sample
	const MatrixXd isR = m_Rebias.sqrt().inverse(),				// Inverse Square root of Rebias matrix => isR
				   newSample = isR * sample * isR.transpose();	// Affine trasnformation : isR * sample * isR^T

	cout << "m_Rebias : " << m_NbClassify << "\t Adapt : " << ((m_NbClassify > 1) ? 1.0 / (m_NbClassify - 1) : 1) << endl
		<< m_Rebias << endl
		<< "Sample : " << endl << sample << endl
		<< "New Sample : " << endl << newSample << endl;


	// Modify rebias for the next step
	if (m_NbClassify == 1) { m_Rebias = sample; }				// At the first pass
	else { Geodesic(m_Rebias, sample, m_Rebias, m_Metric, 1.0 / m_NbClassify); }

	// Compute Distance
	distance.resize(m_classCount);
	for (size_t i = 0; i < m_classCount; ++i)
	{
		distance[i] = Distance(newSample, m_Means[i], m_Metric);
		if (distMin > distance[i])
		{
			classId = i;
			distMin = distance[i];
		}
	}

	// Compute Probability (personnal method)
	probability.resize(m_classCount);
	double sumProbability = 0.0;
	for (size_t i = 0; i < m_classCount; ++i)
	{
		probability[i] = distMin / distance[i];
		sumProbability += probability[i];
	}

	for (auto& p : probability) { p /= sumProbability; }

	// Adaptation
	if (adaptation == Adaptation_None) { return true; }
	// Get class id for adaptation and increase number of trials, expected if supervised, predicted if unsupervised
	const size_t id = adaptation == Adaptation_Supervised ? realClassId : classId;
	if (id >= m_classCount) { return false; }	// Check id (if supervised and bad input)
	m_NbTrials[id]++;							// Update number of trials for the class id
	return Geodesic(m_Means[id], newSample, m_Means[id], m_Metric, 1.0 / m_NbTrials[id]);
}
///-------------------------------------------------------------------------------------------------

///-------------------------------------------------------------------------------------------------
bool CMatrixClassifierMDMRebias::isEqual(const CMatrixClassifierMDMRebias& obj, const double precision) const
{
	return CMatrixClassifierMDM::isEqual(obj) && AreEquals(m_Rebias, obj.m_Rebias, precision) && m_NbClassify == obj.m_NbClassify;
}
///-------------------------------------------------------------------------------------------------

///-------------------------------------------------------------------------------------------------
void CMatrixClassifierMDMRebias::copy(const CMatrixClassifierMDMRebias& obj)
{
	CMatrixClassifierMDM::copy(obj);
	m_Rebias = obj.m_Rebias;
	m_NbClassify = obj.m_NbClassify;
}
///-------------------------------------------------------------------------------------------------

///-------------------------------------------------------------------------------------------------
bool CMatrixClassifierMDMRebias::saveAdditional(XMLDocument& doc, XMLElement* data) const
{
	// Save Rebias
	XMLElement* rebias = doc.NewElement("REBIAS");				// Create REBIAS node
	rebias->SetAttribute("nb-classify", int(m_NbClassify));		// Set attribute number of Classification performed
	if (!saveMatrix(rebias, m_Rebias)) { return false; }		// Save REBIAS Matrix
	data->InsertEndChild(rebias);
	return true;
}
///-------------------------------------------------------------------------------------------------

///-------------------------------------------------------------------------------------------------
bool CMatrixClassifierMDMRebias::loadAdditional(XMLDocument& /*doc*/, XMLElement* data)
{
	// Load Rebias
	XMLElement* rebias = data->FirstChildElement("REBIAS");		// Get REBIAS Node
	m_NbClassify = rebias->IntAttribute("nb-classify");			// Get the number of Classification performed
	return loadMatrix(rebias, m_Rebias);						// Load REBIAS Matrix
}
///-------------------------------------------------------------------------------------------------

///-------------------------------------------------------------------------------------------------
std::stringstream CMatrixClassifierMDMRebias::printAdditional() const
{
	stringstream ss;
	ss << "Number of Classification : " << m_NbClassify << endl;
	ss << "REBIAS Matrix : ";
	if (m_Rebias.size() != 0) { ss << endl << m_Rebias << endl; }
	else { ss << "Not Computed" << endl; }
	return ss;
}
///-------------------------------------------------------------------------------------------------
