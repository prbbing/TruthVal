#ifndef Hist_H
#define Hist_H
#include <map>
#include <string>
#include <vector>

using namespace std;

class Hist { 
  public:
    map<string, vector<double>> oneDHistogramPara;
    map<string, vector<double>> twoDHistogramPara;
    vector<double> mjjBinning = {150,0,7500};
    vector<double> pTBinning = {150,0,3000};
    vector<double> etaBinning = {100,-5,5};
    vector<double> phiBinning = {64,-3.2,3.2};
    vector<double> idBinning = {25,0,25};
    vector<double> dphiBinning = {32,0,3.2};
    vector<double> detaBinning = {50,0,5.0};
    vector<double> dRBinning = {50,0,5.0};

    Hist();
    virtual ~Hist();
    void setParameters();
};

#endif
