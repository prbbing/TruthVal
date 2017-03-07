#include <TruthValidation/TruthReader.h>
using namespace std;

/// Helper macro for checking xAOD::TReturnCode return values
#define EL_RETURN_CHECK( CONTEXT, EXP )			   \
  do {                                                     \
    if( ! EXP.isSuccess() ) {				   \
      Error( CONTEXT,					   \
	     XAOD_MESSAGE( "Failed to execute: %s" ),	   \
	     #EXP );					   \
      return EL::StatusCode::FAILURE;			   \
    }							   \
  } while( false )


// this is needed to distribute the algorithm to the workers
ClassImp(TruthReader)


TruthReader :: TruthReader ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
}



EL::StatusCode TruthReader :: setupJob (EL::Job& job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.

  // let's initialize the algorithm to use the xAODRootAccess package
  job.useXAOD ();
  EL_RETURN_CHECK( "setupJob()", xAOD::Init() ); // call before opening first file

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReader :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  // Acceptance
  Hist *h = new Hist();
  h->setParameters(); 
  map<string, vector<double>>::iterator it; 
  for(it=h->oneDHistogramPara.begin(); it!=h->oneDHistogramPara.end(); it++){
    TH1D *histTmp;//!
    histTmp = new TH1D(it->first.c_str(),it->first.c_str(),(int)it->second.at(0),it->second.at(1),it->second.at(2));
    histTmp->Sumw2();
    oneDHistograms.push_back(histTmp) ;
    wk()->addOutput (histTmp);
  } 

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReader :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReader :: changeInput (bool firstFile)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReader :: initialize ()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.

  xAOD::TEvent* event = wk()->xaodEvent();

  // as a check, let's see the number of events in our xAOD
  Info("initialize()", "Number of events = %lli", event->getEntries() ); // print long long int

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReader :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  xAOD::TEvent* event = wk()->xaodEvent();

  //----------------------------
  // Event information
  //--------------------------- 
  const xAOD::EventInfo* eventInfo = 0;
  EL_RETURN_CHECK("execute",event->retrieve( eventInfo, "EventInfo")); 
  // std::cout << eventInfo->eventNumber() << std::endl;

  //----------------------------
  // Jets
  //--------------------------- 
  const xAOD::JetContainer* jets = 0;
  EL_RETURN_CHECK("execute()",event->retrieve( jets, "AntiKt4TruthJets" ));

  std::vector<xAOD::Jet*> v_jet;

  xAOD::JetContainer::const_iterator jet_itr = jets->begin();
  xAOD::JetContainer::const_iterator jet_end = jets->end();
  for( ; jet_itr != jet_end; ++jet_itr ) {
    if(( (*jet_itr)->pt() * 0.001) < 25) continue;
    if( fabs((*jet_itr)->eta()) > 5.0 ) continue;

    xAOD::Jet* jet = new xAOD::Jet();
    jet->makePrivateStore( **jet_itr );
    v_jet.push_back(jet);
  }


  //----------------------------
  // Compute selection variable
  //--------------------------- 
  if ((int)v_jet.size() > 3){
  // Compute Number b-jets
  int N_bjet =0;
  for( int i_jet = 0 ; i_jet < (int)v_jet.size() ; i_jet++ ) {
    if( abs( v_jet.at(i_jet)->auxdata<int>("PartonTruthLabelID") ) == 5 )
      N_bjet++;
  }
  // Compute mjj
  Double_t mcWeight = eventInfo->mcEventWeight();
  if ((int)v_jet.size() >= 1) {
    fillOneDHistogram(1, v_jet, oneDHistograms, mcWeight); 
  }  
  if ((int)v_jet.size() >= 2) { 
    fillOneDHistogram(2, v_jet, oneDHistograms, mcWeight); 
    fillOneDHistogram(12, v_jet, oneDHistograms, mcWeight); 
  }  
  if ((int)v_jet.size() >= 3) { 
    fillOneDHistogram(3, v_jet, oneDHistograms, mcWeight); 
    fillOneDHistogram(13, v_jet, oneDHistograms, mcWeight); 
    fillOneDHistogram(23, v_jet, oneDHistograms, mcWeight); 
  }  
  if ((int)v_jet.size() >= 4) { 
    fillOneDHistogram(4, v_jet, oneDHistograms, mcWeight); 
    fillOneDHistogram(14, v_jet, oneDHistograms, mcWeight); 
    fillOneDHistogram(24, v_jet, oneDHistograms, mcWeight); 
    fillOneDHistogram(34, v_jet, oneDHistograms, mcWeight); 
  }  
  //----------------------------
  // Fill Histograms
  //--------------------------- 
  }
  for( int i = 0 ; i < (int)v_jet.size(); i++)
    delete v_jet[i];
  
  v_jet.clear();

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReader :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReader :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.

  xAOD::TEvent* event = wk()->xaodEvent();

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthReader :: histFinalize ()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.


  return EL::StatusCode::SUCCESS;
}

void TruthReader::fillOneDHistogram(int index, vector<xAOD::Jet*> jets, vector<TH1D*> hists, double weight){
  for (int i = 0; i < (int)hists.size(); i++){
    string name = hists.at(i)->GetName();
    string variable = getStringSegments(name,'_').at(0);
    int objIndex = atoi(getStringSegments(name,'_').at(1).c_str());
    if (objIndex < 10 && objIndex == index)
      hists.at(i)->Fill(findSingleVariable(jets.at(index - 1),variable), weight);
    if (objIndex >= 10 && objIndex == index)
      hists.at(i)->Fill(findPairVariable(jets.at((int)(index/10) - 1),jets.at(index - 10*(int)(index/10) - 1),variable), weight);
  }
}

double TruthReader::findSingleVariable(xAOD::Jet* jet, string var){
  double value = 0;
  if (var == "pt")  value =  (double)jet->pt()*0.001;
  if (var == "eta") value = (double)jet->eta();
  if (var == "phi") value = (double)jet->phi();
  if (var == "id")  value =  (double)abs(jet->auxdata<int>("PartonTruthLabelID"));
  return value;
}

double TruthReader::findPairVariable(xAOD::Jet* jet1, xAOD::Jet* jet2,string var){
  double value = 0;
  TLorentzVector j_1 = TLorentzVector(jet1->px(), jet1->py(), jet1->pz(), jet1->e());  
  TLorentzVector j_2 = TLorentzVector(jet2->px(), jet2->py(), jet2->pz(), jet2->e()); 
  if (var == "m")  value = (j_1 + j_2).M()*0.001; 
  if (var == "dphi")  value = j_1.DeltaPhi(j_2);
  if (var == "dR")  value = j_1.DeltaR(j_2);
  if (var == "deta")  value = abs(j_1.Eta() - j_2.Eta());
  return value;
}

vector<string>
TruthReader::getStringSegments(string input, char delim)
{
  vector<string> elems;
  std::stringstream ss(input);
  std::string item;
  while (std::getline(ss, item, delim)) {
      elems.push_back(item);
  }
  return elems;
}    
