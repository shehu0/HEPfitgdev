ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4 --install
AUTOMAKE_OPTIONS = subdir-objects

AM_CXXFLAGS = -I$(top_srcdir)/ComputeObservables/src \
 -I$(top_srcdir)/ComputeObservables/src \
 -I$(top_srcdir)/EventGeneration/src \
 -I$(top_srcdir)/gslpp/src \
 -I$(top_srcdir)/InputParser/src \
 -I$(top_srcdir)/LoopFunctions/src \
 -I$(top_srcdir)/Observables/src \
 -I$(top_srcdir)/StandardModel/src \
 -I$(top_srcdir)/EW/src

 # -I$(top_srcdir)/MonteCarlo/src 

# -I$(top_srcdir)/Flavour/src \
# -I$(top_srcdir)/FlavourWilsonCoefficient/src \
# -I$(top_srcdir)/EW/src 

bin_PROGRAMS = Analysis/analysis

pkginclude_HEADERS = ComputeObservables/src/InputParameters.h \
ComputeObservables/src/ComputeObservables.h \
EventGeneration/src/GenerateEvent.h \
gslpp/src/gslpp_vector_double.h \
gslpp/src/gslpp_vector_base.h \
gslpp/src/gslpp_complex.h \
gslpp/src/gslpp_matrix_base.h \
gslpp/src/gslpp_matrix_double.h \
gslpp/src/gslpp_vector_complex.h \
gslpp/src/gslpp_matrix_complex.h \
gslpp/src/gslpp.h \
InputParser/src/ModelFactory.h \
InputParser/src/ThObsFactory.h \
InputParser/src/InputParser.h \
LoopFunctions/src/LoopToolsWrapper.h \
LoopFunctions/src/BernoulliNumbers.h \
LoopFunctions/src/PVfunctions.h \
LoopFunctions/src/Polylogarithms.h \
LoopFunctions/src/ClausenFunctions.h \
Observables/src/HiggsObservable.h \
Observables/src/ThObservable.h \
Observables/src/ModelParameter.h \
Observables/src/ParamObs.h \
Observables/src/CorrelatedGaussianObservables.h \
Observables/src/Observable2D.h \
Observables/src/Observable.h \
Observables/src/CorrelatedGaussianParameters.h \
StandardModel/src/ModelMatching.h \
StandardModel/src/EWSMApproximateFormulae.h \
StandardModel/src/OrderScheme.h \
StandardModel/src/BParameter.h \
StandardModel/src/RGEvolutor.h \
StandardModel/src/EWSMThreeLoopQCD.h \
StandardModel/src/Model.h \
StandardModel/src/StandardModelMatching.h \
StandardModel/src/PMNS.h \
StandardModel/src/EWSMThreeLoopEW2QCD.h \
StandardModel/src/QCD.h \
StandardModel/src/Particle.h \
StandardModel/src/CKM.h \
StandardModel/src/EWSMTwoLoopEW.h \
StandardModel/src/EWSMOneLoopEW.h \
StandardModel/src/WilsonCoefficient.h \
StandardModel/src/EWSMcache.h \
StandardModel/src/EWSMTwoLoopQCD.h \
StandardModel/src/StandardModel.h \
StandardModel/src/Meson.h \
StandardModel/src/EWSMThreeLoopEW.h \
StandardModel/src/WilsonTemplate.h \
EW/src/Mw.h \
EW/src/GammaZ.h

# MonteCarlo/src/MonteCarlo.h \
# MonteCarlo/src/MonteCarloEngine.h

themySOURCES = ComputeObservables/src/ComputeObservables.cpp \
EventGeneration/src/GenerateEvent.cpp \
gslpp/src/gslpp_vector_complex.cpp \
gslpp/src/gslpp_matrix_double.cpp \
gslpp/src/gslpp_matrix_complex.cpp \
gslpp/src/gslpp_complex.cpp \
gslpp/src/gslpp_vector_double.cpp \
InputParser/src/ThObsFactory.cpp \
InputParser/src/InputParser.cpp \
InputParser/src/ModelFactory.cpp \
LoopFunctions/src/ClausenFunctions.cpp \
LoopFunctions/src/PVfunctions.cpp \
LoopFunctions/src/Polylogarithms.cpp \
LoopFunctions/src/BernoulliNumbers.cpp \
LoopFunctions/src/LoopToolsWrapper.cpp \
Observables/src/CorrelatedGaussianParameters.cpp \
Observables/src/CorrelatedGaussianObservables.cpp \
Observables/src/ModelParameter.cpp \
Observables/src/ParamObs.cpp \
Observables/src/HiggsObservable.cpp \
Observables/src/Observable2D.cpp \
Observables/src/Observable.cpp \
StandardModel/src/StandardModelMatching.cpp \
StandardModel/src/EWSMTwoLoopEW.cpp \
StandardModel/src/RGEvolutor.cpp \
StandardModel/src/EWSMcache.cpp \
StandardModel/src/QCD.cpp \
StandardModel/src/EWSMOneLoopEW.cpp \
StandardModel/src/EWSMThreeLoopEW.cpp \
StandardModel/src/WilsonCoefficient.cpp \
StandardModel/src/Meson.cpp \
StandardModel/src/PMNS.cpp \
StandardModel/src/Particle.cpp \
StandardModel/src/EWSMThreeLoopEW2QCD.cpp \
StandardModel/src/EWSMApproximateFormulae.cpp \
StandardModel/src/StandardModel.cpp \
StandardModel/src/CKM.cpp \
StandardModel/src/EWSMTwoLoopQCD.cpp \
StandardModel/src/EWSMThreeLoopQCD.cpp \
EW/src/Mw.cpp \
EW/src/GammaZ.cpp

# MonteCarlo/src/MonteCarlo.cpp \
# MonteCarlo/src/MonteCarloEngine.cpp 

Analysis_analysis_SOURCES =  $(themySOURCES) Analysis/main.cpp

Analysis_analysis_CPPFLAGS = $(SuF_CFLAGS) -I@ROOTINCDIR@  $(BOOST_CPPFLAGS) $(GSL_CFLAGS) 

Analysis_analysis_LDADD = $(SuF_LIBS) $(FLIBS) $(GSL_LIBS) -lgslcblas $(BOOST_PROGRAM_OPTIONS_LIBS) $(BOOST_PROGRAM_OPTIONS_LDFLAGS) -L@ROOTLIBDIR@ @ROOTGLIBS@ -lRooFitCore -lRooFit -lRooStats -lFoam -lMathMore -lMinuit @ROOTAUXLIBS@ 


pkglib_LTLIBRARIES = libHEPfit-@HEPfit_API_VERSION@.la
libHEPfit_@HEPfit_API_VERSION@_la_SOURCES = $(themySOURCES) 

libHEPfit_@HEPfit_API_VERSION@_la_LDFLAGS = -version-info $(HEPfit_SO_VERSION)
libHEPfit_@HEPfit_API_VERSION@_la_CPPFLAGS = $(SuF_CFLAGS) -I@ROOTINCDIR@  $(BOOST_CPPFLAGS)  $(GSL_CFLAGS)
libHEPfit_@HEPfit_API_VERSION@_la_LIBDADD = $(SuF_LIBS) $(FLIBS) $(GSL_LIBS) -lgslcblas $(BOOST_PROGRAM_OPTIONS_LIBS) $(BOOST_PROGRAM_OPTIONS_LDFLAGS) -L@ROOTLIBDIR@  @ROOTGLIBS@ -lRooFitCore -lRooFit -lRooStats -lFoam -lMathMore -lMinuit @ROOTAUXLIBS@  


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = HEPfit-$(HEPfit_API_VERSION).pc

bin_SCRIPTS = hepfit-config

m4datadir = $(datadir)/aclocal
m4data_DATA = m4/hepfit.m4

#dist_noinst_SCRIPTS = 

DISTCLEANFILES = config.hepfit
# CLEANFILES = hepfit.pc hepfit-config
# EXTRA_DIST =  hepfit.pc.in 

