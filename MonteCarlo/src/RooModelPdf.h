#ifndef HEPFIT_ROOMODELPDF_
#define HEPFIT_ROOMODELPDF_

#include "RooAbsPdf.h"
#include "RooWorkspace.h"
#include "RooArgList.h"
#include "RooDataSet.h"
#include "RooStats/ModelConfig.h"
#include "ModelFactory.h"
#include "ThObsFactory.h"
#include "InputParser.h"
#include "ModelParameter.h"
#include "Observable.h"
#include "Observable2D.h"
#include "CorrelatedGaussianObservables.h"
#include "CorrelatedGaussianParameters.h"

class RooModelPdf : public RooAbsPdf {
public:

  RooModelPdf(RooWorkspace& wSpace,
	      ModelFactory& ModelF, ThObsFactory& ThObsF,
	      const std::string& ModelConf_i);

  inline virtual ~RooModelPdf() { }

  void setWorkSpace(void);

  Double_t LogLikelihood(void);

 protected:

  Double_t evaluate();

 private:
  InputParser myInputParser; ///< An object of the InputParser class.
  RooWorkspace* ws;  
  std::string ModelConf; ///< String for the name of the SomeModel.conf file.

  RooArgList Cube;
  RooDataSet data;     
  RooStats::ModelConfig mconfig;  

  std::string ModelName; ///< The name of the model.
  std::vector<ModelParameter> ModPars; ///< Vector for the model parameters defined in SomeModel.conf.
  boost::ptr_vector<Observable> Obs; ///< Vector for the observables defined in SomeModel.conf.
  std::vector<Observable2D>& Obs2D; ///< Vector for the Observables2D defined in SomeModel.conf.
  boost::ptr_vector<Observable>& Obs_ALL; ///< A vector of all observables.
  std::vector<Observable2D>& Obs2D_ALL; ///< A vector of all pairs of observable for Observable2D.
  std::vector<CorrelatedGaussianObservables>& CGO; ///< Vector for the Correlated Gaussian Observables defined in SomeModel.conf.
  std::vector<CorrelatedGaussianParameters>& CGP; ///< Vector for the Correlated Gaussian Parameters defined in SomeModel.conf.
  std::map<std::string, double> DPars; ///< A map between parameter names and their values.
   
  ClassDef(RooModelPdf,1) // Class for generating the likelihood/PDF of a HEP Model in HEPfit
};
 
#endif /* HEPFIT_ROOMODELPDF_ */
