/* 
 * Copyright (C) 2012 HEPfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "MultiNest.h"
#include "ModelFactory.h"
#include "ThObsFactory.h"

#include "TString.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <iostream>


MultiNest::MultiNest( ModelFactory& ModelF, ThObsFactory& ThObsF, 
		      const std::string& ModelConf_i,
		      const std::string& MultiNestConf_i
		      ) : myInputParser(ModelF, ThObsF), wSpace("TemporaryName") {
  ModelConf = ModelConf_i;
  MultiNestConf = MultiNestConf_i;
}

//MultiNest::~MultiNest() {}

RooStats::ModelConfig MultiNest::makeModelConfig(void){
  ModelName = myInputParser.ReadParameters(ModelConf, ModPars, Obs);
  wSpace.renameSet("TemporaryName", (const char*) ModelName);



  // char *argList
  //  for start to end of parametersList
  // print to a constrant string var String in the form "x$i[$lowerLimit$i, $upperLimit$i]"
  
  // wSpace.factory(String)   //   RooAbsArg* factory(const char* expr);
  // append argList with  in the form "x1,x2,x3,x4, ..., x$numberOfParameters"

  //  mc.SetParametersOfInterest( argList );  //  virtual void SetParametersOfInterest(const char *argList) { 

  // creat set of parameters, axes
  TString axes, factory_var;
  Int_t i = 0;
  RooArgSet pars("parameters");   // set of parameters of interest
  RooRealVar * pPars;
  for (std::vector<ModelParameter>::iterator it = ModPars.begin(); it < ModPars.end(); it++) {
    axes += Form("x_%s", it->getname());
    if( i + 1 != ModPars.size() ) axes += ", ";
    i++;

    factory_var = Form("%s[%f,%f]", it->getname(), it->getmin(), it->getmax());
    wSpace.factory(factory_var);

    pPars = wSpace.var( it->getname() );
    pars.add(*pPars); 

	
  }

  // creat set of observables and initilias all to zero
  RooArgSet obs("observables");
  RooRealVar * pObs;
  for (boost::ptr_vector<Observable>::iterator it = Obs.begin(); it < Obs.end(); it++) {
    factory_var = Form("%s[0]", it->getname());
    wSpace.factory( factory_var );
    pObs = wSpace.var( it->getname() );
    obs.add(*pObs); 
  }  

  // creat data set using RootFit data set as data container
  RooDataSet * data = new RooDataSet("data", "data", obs);
  //  later
  // pObs->setVal(somethingHere):
  // data->add( *pObs);

  // import data into work space
  wSpace.import( *data );
  
  


  
	      

return 
}


RooDataSet MultiNest::setData(void){


return 
}


void MultiNest::runMultiNest(ModelConfig& mConf, RooDataSet& theData) {
  try {

    /* set model parameters */
    ModelName = myInputParser.ReadParameters(ModelConf, ModPars, Obs);

    int buffsize = 0;
    std::map<std::string, double> DP;
    for (std::vector<ModelParameter>::iterator it = ModPars.begin(); it < ModPars.end(); it++) {
      if (it->geterrg() > 0. || it->geterrf() > 0.) buffsize++;    // @@@ what if negative values ??
      DP[it->getname()] = it->getave();
    }

    if (buffsize == 0){
      throw std::runtime_error("No parameters being varied. Aborting MCMC run.\n");
    }

    //@@@  make a workspace and parameters factory
    

    
    buffsize++;
    if (!myInputParser.getModel()->Init(DP)){
      throw std::runtime_error("\nERROR: Model cannot be initialised.\n");
    }

    std::cout << std::endl << "Running in Nested Sampling MonteCarlo mode...\n" << std::endl;


    //        MCEngine.SetName(ModelName.c_str());
    //        MCEngine.Initialize(myInputParser.getModel());
    
    //    if (rank != 0) {
    std::vector<double> pars;
    pars.assign(recvbuff + 1, recvbuff + buffsize);
    MCEngine.setDParsFromParameters(pars,DPars);
    myInputParser.getModel()->Update(DPars);
    int k = 0;
    for (boost::ptr_vector<Observable>::iterator it = Obs.begin(); it < Obs.end(); it++) {
      sbuff[k++] = it->computeTheoryValue();
    }
    double ll = MCEngine.LogEval(pars);
    //    } else {
    std::cout << ModPars.size() << " parameters defined." << std::endl;
    std::cout << Obs.size() << " observables defined." << std::endl;
    // }
  } catch (std::string message) {
    std::cerr << message << std::endl;
    exit(EXIT_FAILURE);
  }
}


// model parameters, observables, likelihoods, priors should all be in the workspace.root 
void MultiNest::runMultiNest(std::string filename = "workspace.root",
			     std::string wsName,
			     std::string mcName){

  // open workspace file
  TFile * wsFile = new TFile(filename.c_str(), "read");

  // load workspace
  RooWorkspace * pws = & wSpace;
  pws = (RooWorkspace *) wsFile -> Get(wsName.c_str());
  if(!pws){
    std::cout << "workspace " << wsName << "is not found." << std::endl;
    exit(EXIT_FAILURE);
  }
  pws->print();

  // load data
  data = * pws->data("data");
  data.print();

  // load model config
  mconfig = * (RooStats::ModelConfig *) pws -> obj(mcName.c_str());
  mconfig.print();

  // run MultiNest on the model
  MNCalculator.SetModel(mconfig);
  MNCalculator.SetData(data);

  // get interval and store result
  MultiNestInterval* interval = MNCalculator.GetInterval();
 
  
}

// DO example workspace: model fit
// DO a custom Loglike function
//    such the LogLikeEggbox function is an example

// plugin Multinest.h
// void LogLike(RooAbsReal *logLike, RooArgList& argList);
// over-writes TMultiNest.h
// void LogLike(void (*_LogLikePtr)(double *Cube, int &ndim, int &npars, double &lnew, void* context)) {
//   fLogLikePtr = _LogLikePtr;
// }


// for a given set of model parameters, compute the corresponding loglikelihood values
// and store it in RooAbsReal *logLike
				 
