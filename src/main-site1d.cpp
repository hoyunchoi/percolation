#include <chrono>
#include <fstream>
#include "generate.hpp"

int main(int argc, char* argv[]){
    const int size = std::stoi(argv[1]);
    const double prob = std::stod(argv[2]);
    const unsigned ensembleSize = std::stoul(argv[3]);
    const int coreNum = std::stoi(argv[4]);
    const int randomEngineSeed = -1;

    //* Generate and Run percolation::Generate model
    const auto start = std::chrono::system_clock::now();
    percolation::Generate model(size, prob, coreNum, randomEngineSeed);
    model.run(ensembleSize);
    model.save();
    std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
    std::ofstream logFile(percolation::logDirectory + "time.log", std::ios_base::app);
    logFile << percolation::fileName::NGE(size, prob, ensembleSize, coreNum) << ": " << std::setprecision(6) << sec.count() << "seconds\n";


    return 0;
}