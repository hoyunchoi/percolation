#pragma once

#include "../library/stringFormat.hpp"

namespace percolation {

const std::string dataDirectory = "../data/";
const std::string logDirectory = "../log/";

namespace fileName {

inline const std::string base(const int&, const double&);
const std::string NG(const int&, const double&, const int&);
const std::string NGE(const int&, const double&, const unsigned&, const int&);

}  // namespace fileName

inline const std::string fileName::base(const int& t_size, const double& t_prob) {
    return "N" + to_stringWithExponent((double)t_size, 1) + ",P" + to_stringWithPrecision(t_prob, 5);
}

const std::string fileName::NG(const int& t_size, const double& t_prob, const int& t_coreNum = -1) {
    const std::string fileName = base(t_size, t_prob);
    return t_coreNum == -1 ? fileName + ".txt" : fileName + "-" + std::to_string(t_coreNum) + ".txt";
}

const std::string fileName::NGE(const int& t_size, const double& t_prob, const unsigned& t_ensembleSize, const int& t_coreNum = -1) {
    const std::string fileName = base(t_size, t_prob) + ",E" + std::to_string(t_ensembleSize);
    return t_coreNum == -1 ? fileName + ".txt" : fileName + "-" + std::to_string(t_coreNum) + ".txt";
}

}  // namespace percolation
