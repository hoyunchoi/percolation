#pragma once

#include <map>
#include <random>
#include <vector>

#include "pcg_random.hpp"

namespace percolation {

struct Site1D {
    //* Member variables
   protected:
    unsigned m_size;
    double m_prob;
    unsigned m_occupationNum;
    std::vector<bool> m_occupation;
    std::map<unsigned, unsigned> m_sortedCluster;  //* sortedCluster[size] : number of cluster of 'size'

    //* Member functions
   public:
    Site1D(){};
    Site1D(const unsigned&, const double&, pcg32&);
    const std::map<unsigned, unsigned> getSortedCluster() const {return m_sortedCluster;}
    const std::map<unsigned, unsigned> getSortedCluster2() const;

   protected:
    void m_generate(pcg32&);
};

Site1D::Site1D(const unsigned& t_size, const double& t_prob, pcg32& t_randomEngine) : m_size(t_size), m_prob(t_prob) {
    //* Initialize
    m_occupationNum = 0;
    m_occupation.assign(t_size, false);

    //* Generate
    m_generate(t_randomEngine);
}

void Site1D::m_generate(pcg32& t_randomEngine) {
    std::uniform_real_distribution<double> probDistribution(0.0, 1.0);
    unsigned clusterSize = 0;
    for (unsigned site = 0; site < m_size; ++site) {
        if (probDistribution(t_randomEngine) < m_prob) {
            m_occupation[site] = true;
            ++clusterSize;
        } else {
            if (clusterSize) {
                ++m_sortedCluster[clusterSize];
            }
            clusterSize = 0;
        }
    }
    if (clusterSize) {
        ++m_sortedCluster[clusterSize];
    }
}

}  // namespace percolation
