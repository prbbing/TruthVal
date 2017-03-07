#include <TruthValidation/Hist.h>

Hist::Hist() {}

void Hist::setParameters() {
    //Add histogram settings, the name of the histogram is in a form of X_Y, X refers to the variables, which are defined in findSingleVariables and findPairVariables functions of TruthReader.cxx 
    oneDHistogramPara.insert(pair<string, vector<double>>("pt_1",pTBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("pt_2",pTBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("pt_3",pTBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("pt_4",pTBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("eta_1",etaBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("eta_2",etaBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("eta_3",etaBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("eta_4",etaBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("phi_1",phiBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("phi_2",phiBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("phi_3",phiBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("phi_4",phiBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("id_1",idBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("id_2",idBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("id_3",idBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("id_4",idBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("m_12",mjjBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("dphi_12",dphiBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("deta_12",detaBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("dR_12",dRBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("m_13",mjjBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("dphi_13",dphiBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("deta_13",detaBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("dR_13",dRBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("m_14",mjjBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("dphi_14",dphiBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("deta_14",detaBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("dR_14",dRBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("m_23",mjjBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("dphi_23",dphiBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("deta_23",detaBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("dR_23",dRBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("m_24",mjjBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("dphi_24",dphiBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("deta_24",detaBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("dR_24",dRBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("m_34",mjjBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("dphi_34",dphiBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("deta_34",detaBinning));     
    oneDHistogramPara.insert(pair<string, vector<double>>("dR_34",dRBinning));     
} 

Hist::~Hist() { } 
