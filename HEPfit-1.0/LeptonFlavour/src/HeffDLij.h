/*
 * Copyright (C) 2013 HEPfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef HEFFDLIJ_H
#define	HEFFDLIJ_H

#include "StandardModel.h"
#include "StandardModelMatching.h"
#include "WilsonCoefficient.h"

/**
 * @class HeffDLij
 * @ingroup LeptonFlavour
 * @brief A class for calculating all the Wilson coefficients for the process \f$ \ell_j \to \ell_i \gamma \f$. 
 * @author HEPfit Collaboration
 * @copyright GNU General Public License
 * @details The HeffDLij class aggregates the Wilson coefficients for the process \f$ \ell_j \to \ell_i \gamma \f$ generated by the model and sum them order by order.
 */
class HeffDLij {
public:
    /**
     * @brief The constructor of the class HeffDLij.
     * @param[in] Wilson coefficient responsible for the process \f$ \ell_j \to \ell_i \gamma \f$ in the SM 
     * @param[in] Wilson coefficient responsible for the process \f$ \ell_j \to \ell_i \gamma \f$ in the model analyzed
     */
    HeffDLij(const StandardModel & SM_i);
    
    /**
     * @brief destructor of the class HeffDLij.
     */
    virtual ~HeffDLij();
    
    /**
     * @brief Computes the Wilson coefficients for the process \f$ \ell_j \to \ell_i \gamma \f$.
     * @param li_lj determines the process, e.g., 1 = \f$ \mu \to e \gamma \f$, 2 = \f$ \tau \to \mu \gamma \f$, 3 = \f$ \tau \to e \gamma \f$
     * @return returns the Wilson coefficients for the process
     */
    gslpp::vector<gslpp::complex>** ComputeCoeffDLij(int li_lj);

    /**
     * @brief Calls the model analyzed to calculate Wilson coefficients for the process \f$ \ell_j \to \ell_i \gamma \f$.
     */   
    const StandardModel& GetModel() const {
        return model;
    }
    
private :
    /**
     * @brief Variable which stores the model information.
     */
    const StandardModel& model;

    /**
     * @brief Variable which stores the Wilson coefficient for \f$ \mu \to e \gamma \f$.
     */
    WilsonCoefficient coeffDLij_1;
    /**
     * @brief Variable which stores the Wilson coefficient for \f$ \tau \to \mu \gamma \f$.
     */
    WilsonCoefficient coeffDLij_2;
    /**
     * @brief Variable which stores the Wilson coefficient for \f$ \tau \to e \gamma \f$.
     */
    WilsonCoefficient coeffDLij_3;

    //gslpp::vector<gslpp::complex> nlep, nlep2, nlepCC;
};

#endif	/* HEFFDLIJ_H */
