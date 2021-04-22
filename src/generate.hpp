#pragma once

#include <map>
#include <random>

#include "CSV.hpp"
#include "pcg_random.hpp"
#include "linearAlgebra.hpp"
#include "common.hpp"
#include "site1d.hpp"

namespace percolation {
struct Generate {
    //* Member variables
   protected:
    int m_size;
    double m_prob;
    int m_coreNum;
    unsigned m_ensembleSize;
    pcg32 m_randomEngine;
    std::uniform_real_distribution<double> m_probDistribution;

    //* Observables
    std::map<int, unsigned long long> obs_clusterSizeDist;

    //* Member functions
   public:
    Generate(){};
    Generate(const int&, const double&, const int&, const int&);
    void run(const unsigned&);
    void save() const;

   protected:
    void m_singleRun();
};

Generate::Generate(const int& t_size, const double& t_prob, const int& t_coreNum, const int& t_randomEngineSeed) : m_size(t_size), m_prob(t_prob), m_coreNum(t_coreNum) {
    //* Initialize random variables
    t_randomEngineSeed == -1 ? m_randomEngine.seed((std::random_device())()) : m_randomEngine.seed(t_randomEngineSeed);
    m_probDistribution.param(std::uniform_real_distribution<double>::param_type(0.0, 1.0));
}

void Generate::m_singleRun() {
    //* Generate model
    Site1D model(m_size, m_prob, m_randomEngine);

    //! cluster size distribution
    {
        for (const std::pair<unsigned, unsigned>& cluster : model.getSortedCluster()) {
            obs_clusterSizeDist[cluster.first] += cluster.second;
        }
    }
}

void Generate::run(const unsigned& t_ensembleSize) {
    m_ensembleSize = t_ensembleSize;
    for (unsigned ensemble = 0; ensemble < t_ensembleSize; ++ensemble) {
        m_singleRun();
    }
}

void Generate::save() const {
    const int precision = -1;
    const std::string NG = fileName::NG(m_size, m_prob, m_coreNum);
    const std::string NGE = fileName::NGE(m_size, m_prob, m_ensembleSize, m_coreNum);

    //! Cluster size distribution
    {
        const std::string directory = dataDirectory + "clusterSizeDist/";
        CSV::generateDirectory(directory);
        std::map<int, double> trimmed;
        for (const std::pair<int, int>& cluster : obs_clusterSizeDist) {
            trimmed[cluster.first] = cluster.second / (double)m_ensembleSize;
        }
        CSV::write(directory + NGE, trimmed, precision);
    }
}

}  // namespace percolation