/* 
 * Copyright (C) 2012 HEPfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */
//09633 739 ir rome 1615
#include "MultiNest.h"
#include "RooModelPdf.h"
#include "TFile.h"
#include <iostream>

MultiNest::MultiNest( ModelFactory& ModelF_i, ThObsFactory& ThObsF_i, 
		      const std::string& ModelConf_i
		      ){
  ModelF = ModelF_i;
  ThObsF_i = ThObsF_i;
}

//MultiNest::~MultiNest() {}

//void MultiNest::makeModelConfig(void){
void MultiNest::run(void){

  wSpace.factory("RooModelPdf::myPdf(wSpace, ModelF, ThObsF, ModelConf)");  // ,Cube
  
  // load data
  RooAbsData * dtset_ptr = wSpace.data("data");
  //  data = *wSpace.data("data");
  //  data.print();

  // load model config
  mconfig = *(ModelConfig *) wSpace.genobj("myModelConfig");
  //  mconfig.print();

  // make sure ingredients are found
  //  RooAbsData * data_ptr = &data;
  ModelConfig * mc_ptr = & mconfig;
  if(!dtset_ptr || !mc_ptr){
    std::cout << "data or ModelConfig was not found" << std::endl;
    exit(EXIT_FAILURE);
  }

  mconfig.SetPdf( *wSpace.pdf("myPdf") );  // @@@ RooModelPdf myPdf; possible ???
  
  mnest.SetModel( mconfig );
  mnest.SetData( *dtset_ptr );
  mnest.Tol(0.01);
  
  interval = mnest.GetInterval();
}
  
void MultiNest::run(ModelConfig& mConf, RooDataSet& theData) {
  mnest.SetModel(mConf);
  mnest.SetData(theData);
  mnest.Tol(0.01);
  
  interval = mnest.GetInterval();
}

// model parameters, observables, likelihoods, priors should all be in the workspace.root 
// open root file with workspace
// here you have to know name of workspace
// you can get that by opening the file in root
// and typing ".ls"
//void MultiNest::run(std::string filename = "workspace.root",
void MultiNest::run(std::string filename,
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
  //  pws->print();

  // load data
  RooAbsData * dtset_ptr = pws->data("data");
  //  data = * pws->data("data");
  //  data.print();

  // load model config
  mconfig = * (RooStats::ModelConfig *) pws -> obj(mcName.c_str());
  //  mconfig.print();

  // make sure ingredients are found
  //  RooAbsData * data_ptr = &data;
  ModelConfig * mc_ptr = & mconfig;
  if(!dtset_ptr || !mc_ptr){
    // w->Print();
    std::cout << "data or ModelConfig was not found" << std::endl;
    exit(EXIT_FAILURE);
  }
  
  // run MultiNest on the model
  mnest.SetModel(mconfig);
  mnest.SetData( *dtset_ptr );

  // get interval and store result
  interval = mnest.GetInterval();
}
