#ifndef TruthValidation_TruthReader_H
#define TruthValidation_TruthReader_H

#include <stdlib.h>

#include <TH1.h>

#include <EventLoop/Algorithm.h>
#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>

#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/tools/Message.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODJet/JetAuxContainer.h"
#include "xAODMissingET/MissingETContainer.h"
#include "TLorentzVector.h"
#include "TruthValidation/Hist.h"
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

class TruthReader : public EL::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.

private:

  //Has to be vector<TH1D*> instead of vector<TH1D> otherwise histograms will not be filled in the output file
  vector<TH1D*> oneDHistograms; //!

public:
  // float cutValue;


  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
public:

  // this is a standard constructor
  TruthReader ();
  void fillOneDHistogram(int index, vector<xAOD::Jet*> jets, vector<TH1D*> hists, double weight);
  double findSingleVariable(xAOD::Jet* jet, string var);
  double findPairVariable(xAOD::Jet* jet1, xAOD::Jet* jet2,string var);
  vector<string> getStringSegments(string input, char delim);
  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  // this is needed to distribute the algorithm to the workers
  ClassDef(TruthReader, 1);
};

#endif
