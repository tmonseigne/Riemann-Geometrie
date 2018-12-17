#pragma once

#include <vector>
#include <Eigen/Dense>

bool LSQR(const std::vector<std::vector<Eigen::RowVectorXd>>& datasets, Eigen::MatrixXd& weight);

bool FgDACompute(const std::vector<std::vector<Eigen::MatrixXd>>& datasets);
bool FgDAApply(const std::vector<std::vector<Eigen::MatrixXd>>& datasets);