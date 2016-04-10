/* 
 * Copyright (C) 2012 HEPfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

// (1) no rank, totally serial
// (2) InputParser/ReadParameters overloaded, only observables
// (3) Observable/ReadParameters overloaded, no rank

#ifndef __HEPFIT_MULTINEST_H__
#define	__HEPFIT_MULTINEST_H__


#include "RooWorkspace.h"
#include "RooArgList.h"
#include "RooDataSet.h"
#include "RooStats/ModelConfig.h"
#include "RooStats/MultiNestCalculator.h"
#include "RooStats/MCMCIntervalPlot.h"

#include "InputParser.h"


class MultiNest {
public:
  MultiNest(ModelFactory& ModelF, ThObsFactory& ThObsF,
            const std::string& ModelConf_i,
            const std::string& MultiNestConf_i);

  //virtual ~MultiNest();
  
  ModelConfig makeModelConfig(void); 

  RooDataSet setData(void); 
  
  void runMultiNest(ModelConfig& mConf, RooDataSet& theData);

  void runMultiNest(std::string filename = "workspace.root", // if model & data already exist in form of root workspace in a .root file
		    std::string wsName,                      // workspace's registered name
		    std::string mcName);                     // name of the Model Config object inside the workspace
  
private:
  std::string ModelName; ///< The name of the model.
  InputParser myIParser; ///< An object of the InputParser class.
  std::vector<ModelParameter> ModPars; ///< Vector for the model parameters defined in SomeModel.conf.
  boost::ptr_vector<Observable> Obs; ///< Vector for the observables defined in SomeModel.conf.
  std::string ModelConf; ///< String for the name of the SomeModel.conf file.

  std::string MultiNestConf; ///< String for the name of the MultiNest.conf file.

  RooWorkspace wSpace;  // Workspace to store objects
  RooArgList axes;      // all the parameters
  RooDataSet data;      // dataset
  ModelConfig mconfig;  

  MultiNestCalculator MNCalculator;
  MultiNestIntervalPlot* plot;
};

#endif	/* __HEPFIT_MULTINEST_H__ */
