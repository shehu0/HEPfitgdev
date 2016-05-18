#ifndef HEPFIT_MULTINEST_H_
#define	HEPFIT_MULTINEST_H_

#include "ModelFactory.h"
#include "ThObsFactory.h"
#include "RooArgList.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "RooStats/ModelConfig.h"
#include "RooStats/MultiNestCalculator.h"
//#include "RooStats/MCMCIntervalPlot.h"

using namespace RooFit;
using namespace RooStats;

class MultiNest {
 public:
  MultiNest(ModelFactory& ModelF_i, ThObsFactory& ThObsF_i,
            const std::string& ModelConf_i);

  //virtual ~MultiNest();
  void run(void); 

  void run(ModelConfig& mConf, RooDataSet& theData);

  //  void run(std::string filename = "workspace.root", // if model & data already exist in form of root workspace in a .root file
  void run(std::string filename, // if model & data already exist in form of root workspace in a .root file
	   std::string wsName,                      // workspace's registered name
	   std::string mcName);                     // name of the Model Config object inside the workspace
  
 private:
  ModelFactory& ModelF;
  ThObsFactory& ThObsF;
  const std::string& ModelConf;

  RooArgList axes;      // all the parameters
  RooWorkspace& wSpace;  // Workspace to store objects
  RooDataSet data;      // dataset
  ModelConfig mconfig;  

  MultiNestCalculator mnest;
  MultiNestInterval* interval;
  //  MultiNestIntervalPlot* plot;
};
#endif	/* HEPFIT_MULTINEST_H_ */

