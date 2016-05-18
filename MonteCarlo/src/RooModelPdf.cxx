// Class for generating the likelihood/PDF of a HEP Model in HEPfit
#include "RooModelPdf.h"
#include "RooRealVar.h" 
#include <iostream>
#include "Riostream.h"
#include "TString.h"

#include <stdio.h>
#include <stdexcept>
#include <math.h> 
#include "TMath.h" 

ClassImp(RooModelPdf)

class MultiNest;

RooModelPdf::RooModelPdf(RooWorkspace& wSpace,
			 ModelFactory& ModelF, ThObsFactory& ThObsF,
			 const std::string& ModelConf_i)
  : myInputParser(ModelF, ThObsF), mconfig("tempname", ws) {
  ws = &wSpace;
  ModelConf = ModelConf_i;
  setWorkSpace();
}

void RooModelPdf::setWorkSpace(void){

  const int rank = 0; // no MPI paralellisation for now

  try {

    if(ModelConf != NULL){
      ModelName = myInputParser.ReadParameters(ModelConf,
					       rank, ModPars, Obs, Obs2D, CGO, CGP);   
      Obs_ALL = Obs;
      Obs2D_ALL = Obs2D;
    } else {
      std::cout << "The HEPfit model configuration file should be given." << std::endl;
      exit(EXIT_FAILURE);
    }

    int buffsize = 0; // number of parameters varied as specified in HEPfit config file
    std::map<std::string, double> DP;
    
    ws -> renameSet("TemporaryName", ModelName.c_str());
    TString factory_var;
    RooRealVar * tmpPars;         // temporaty location for a real variable
    //    RooArgSet pars("parameters"); // collection of the parameters

    ws -> factory( "PROD::priorPdf(1.0)" ); //@@@ product of the priors

    for (std::vector<ModelParameter>::iterator it = ModPars.begin(); it < ModPars.end(); it++) {
      factory_var = TString::Format("%s[%f,%f]", it->getname().data(), it->getmin(), it->getmax());
      ws -> factory(factory_var);
      ws -> factory(factory_var);
      ws -> factory( "Uniform::prior(factory_var)" ); // define Bayesian prior PDF for POI
      ws -> factory( "PROD::priorPdf(priorPdf, prior)" ); //@@@ 
      tmpPars = ws -> var( it->getname().data() );
      Cube.add( *tmpPars );
    }
    //    Cube(pars);

    //    ws -> defineSet( "variedParameters", pars );
    ws -> defineSet( "variedParameters", Cube );


    // set of observables or theory values
    RooArgSet predict("ComputedPredictions");
    RooRealVar * tmpObs; 
    for (boost::ptr_vector<Observable>::iterator it = Obs.begin(); it < Obs.end(); it++) {
      factory_var = Form("%s", it->getName().data());
      ws -> factory( factory_var );
      tmpObs = ws -> var( it->getName().data() );
      predict.add( *tmpObs );
    }

    for (std::vector<Observable2D>::iterator it = Obs2D.begin(); it < Obs2D.end(); it++) {
      factory_var = Form("%s", it->getName().data());
      ws -> factory( factory_var );
      tmpObs = ws -> var( it->getName().data() );
      predict.add( *tmpObs );

      factory_var = Form("%s", it->getLabel2().data());
      ws -> factory( factory_var );
      tmpObs = ws -> var( it->getLabel2().data() );
      predict.add( *tmpObs );
    }

    for (std::vector<CorrelatedGaussianObservables>::iterator it1 = CGO.begin();
	 it1 < CGO.end(); it1++) {
      std::vector<Observable> pino(it1->getObs());
      for (std::vector<Observable>::iterator it = pino.begin(); it != pino.end(); ++it){
	factory_var = Form("%s", it->getName().data());
	ws -> factory( factory_var );
	tmpObs = ws -> var( it->getName().data() );
	predict.add( *tmpObs );
      }
    }
    
    ws -> defineSet( "ComputedPredictions", predict );
   
    // mconfig(ModelName.c_str(), &tmpWS);
    mconfig.SetName("myModelConfig");
    mconfig.SetWorkspace(*ws);
    
    //mconfig.SetPriorPdf( *ws -> pdf("priorPdf") );

    // mconfig.SetObservables( obs );
    // mconfig.SetGlobalObservables( globalObs );
    //    mconfig.SetParametersOfInterest( pars );
        mconfig.SetParametersOfInterest( Cube );

    ws -> import( mconfig );  // import into workspace
    //    ws -> import( data );
    ///  RooModelConfig is set, now run RUN MULTINEST

  } catch (std::string message) {
    std::cerr << message << std::endl;
    exit(EXIT_FAILURE);
  }
}

Double_t RooModelPdf::LogLikelihood(void) {

  Double_t logprob = 0.;

  if (! myInputParser.getModel()->Update(DPars)) {
#ifdef _MCDEBUG
    std::cout << "event discarded" << std::endl;
    /* Debug */
    //for (int k = 0; k < parameters.size(); k++)
    //    std::cout << "  " << GetParameter(k)->GetName() << " = "
    //              << DPars[GetParameter(k)->GetName()] << std::endl;
#endif
    //        NumOfDiscardedEvents++;
    return (log(0.));
  }
#ifdef _MCDEBUG
  //std::cout << "event used in MC" << std::endl;
#endif

  // the total no. of obserbales to be kept
  Int_t obsbuffsize = Obs.size() + 2 * Obs2D.size();
  for (std::vector<CorrelatedGaussianObservables>::iterator it1 = CGO.begin(); it1 < CGO.end(); it1++)
    obsbuffsize += it1->getObs().size();

  TString factory_var;
  RooRealVar * tmpObs; 
  int k = 0;
  Double_t ObsComputed[obsbuffsize];
  
  for (boost::ptr_vector<Observable>::iterator it = Obs.begin(); it < Obs.end(); it++) {
    factory_var = Form("%s", it->getName().data());
    tmpObs = ws -> var( it->getName().data() );
    ObsComputed[k] = it->computeTheoryValue();
    tmpObs->setVal( ObsComputed[k] );
    data.add( *tmpObs );
    k++;
  }

  for (std::vector<Observable2D>::iterator it = Obs2D.begin(); it < Obs2D.end(); it++) {
    factory_var = Form("%s", it->getName().data());
    tmpObs = ws -> var( it->getName().data() );
    ObsComputed[k] = it->computeTheoryValue();
    tmpObs->setVal( ObsComputed[k] );
    data.add( *tmpObs );
    k++;

    factory_var = Form("%s", it->getLabel2().data());
    tmpObs = ws -> var( it->getLabel2().data() );
    ObsComputed[k] = it->computeTheoryValue2();
    tmpObs->setVal( ObsComputed[k] );
    data.add( *tmpObs );
    k++;
  }

  for (std::vector<CorrelatedGaussianObservables>::iterator it1 = CGO.begin();
       it1 < CGO.end(); it1++) {
    std::vector<Observable> pino(it1->getObs());
    for (std::vector<Observable>::iterator it = pino.begin(); it != pino.end(); ++it){
      factory_var = Form("%s", it->getName().data());
      tmpObs = ws -> var( it->getName().data() );
      ObsComputed[k] = it->computeTheoryValue();
      tmpObs->setVal( ObsComputed[k] );
      data.add( *tmpObs );
      k++;
    }
  }

  ws -> import( data );
  
  for (boost::ptr_vector<Observable>::iterator it = Obs_ALL.begin(); it != Obs_ALL.end(); it++) {
    if (it->isTMCMC())
      logprob += it->computeWeight();
  }

  for (std::vector<Observable2D>::iterator it = Obs2D_ALL.begin(); it != Obs2D_ALL.end(); it++) {
    if (it->isTMCMC())
      logprob += it->computeWeight();
  }

  for (std::vector<CorrelatedGaussianObservables>::iterator it = CGO.begin(); it < CGO.end(); it++) {
    logprob += it->computeWeight();
  }


  if (isnan(logprob)) {
    //        NumOfDiscardedEvents++;
    std::cout << "Event discarded since logprob evaluated to NAN.\n";
    return (log(0.));
  }
  //    NumOfUsedEvents++;
  return logprob;
}


// @@@@ in RooFit/RooStats fram: ? classify observables into Obs, Obs2D, CGO--
Double_t RooModelPdf::evaluate()
{

  Int_t buffsize = 0;
  Int_t rank = 0;
  std::map<std::string, double> DP;
  
  for (std::vector<ModelParameter>::const_iterator it = ModPars.begin(); it < ModPars.end(); it++){
    if (it->geterrg() > 0. || it->geterrf() > 0.)
      buffsize++;
    if (it->IsCorrelated()) {
      for (unsigned int i = 0; i < CGP.size(); i++) {
	if (CGP[i].getName().compare(it->getCgp_name()) == 0) {
	  std::string index = it->getname().substr(CGP[i].getName().size());
	  long int lindex = strtol(index.c_str(), NULL, 10);
	  if (lindex > 0){
	    DP[CGP[i].getPar(lindex - 1).getname()] = CGP[i].getPar(lindex - 1).getave();
	    std::string str = CGP[i].getPar(lindex - 1).getname();
	    const char * c = str.c_str();
	    Int_t dindex = Cube.index(c);
	    DPars[CGP[i].getPar(lindex - 1).getname()] = *(reinterpret_cast <Double_t *>( Cube.at(dindex) ));
	  }
	  else {
	    std::stringstream out;
	    out << it->getname();
	          throw
		    std::runtime_error("RooModelPdf: " + out.str() +
				       " seems to be part of a CorrelatedGaussianParameters object," +
				       " but I couldn't find the corresponding object");
	  }
	}
      }
    } else {
      DP[it->getname()] = it->getave();
      std::string str = it->getname();
      const char * c = str.c_str();
      Int_t dindex = Cube.index(c);
      DPars[it->getname()] = *(reinterpret_cast <Double_t *>( Cube.at(dindex) ));
    }
  }
  
  if (buffsize == 0){
    if (rank == 0) throw std::runtime_error("No parameters being varied. Aborting MCMC run.\n");
    else sleep(2);
  }
  buffsize++;
  if (!myInputParser.getModel()->Init(DP)){
    if (rank == 0) throw std::runtime_error("\nERROR: Model cannot be initialization.\n");
    else sleep(2);
  }

  return TMath::Exp( LogLikelihood() ); 
} 
