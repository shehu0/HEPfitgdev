/*
 * Copyright (C) 2015 HEPfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef HEFFDLI3J_H
#define	HEFFDLI3J_H

#include "StandardModel.h"
#include "StandardModelMatching.h"
#include "WilsonCoefficient.h"

/**
 * @class HeffDLi3j
 * @ingroup LeptonFlavour
 * @brief A class for calculating all the Wilson coefficients for the process \f$ \ell_j \to \ell_i \ell_i \ell_i \f$. 
 * @author HEPfit Collaboration
 * @copyright GNU General Public License
 * @details The HeffDLi3j class aggregates the Wilson coefficients for the process \f$ \ell_j \to \ell_i \ell_i \ell_i \f$ generated by the model and sum them order by order.
 */

class HeffDLi3j {
public:
    /**
     * @brief The constructor of the class HeffDLi3j.
     * @param[in] Wilson coefficient responsible for the process \f$ \ell_j \to \ell_i \ell_i \ell_i \f$ in the SM 
     * @param[in] Wilson coefficient responsible for the process \f$ \ell_j \to \ell_i \ell_i \ell_i \f$ in the model analyzed
     */
    HeffDLi3j(const StandardModel & SM_i);
    
    /**
     * @brief destructor of the class HeffDLi3j.
     */
    virtual ~HeffDLi3j();
    
    /**
     * @brief Computes the Wilson coefficients for the process \f$ \ell_j \to \ell_i \ell_i \ell_i \f$.
     * @param li_lj determines the process, e.g., 1 = \f$ \mu \to eee \f$, 2 = \f$ \tau \to \mu \mu \mu \f$, 3 = \f$ \tau \to eee \f$
     * @return returns the Wilson coefficients for the process
     */
    gslpp::vector<gslpp::complex>** ComputeCoeffDLi3j(int li_lj);

    /**
     * @brief Calls the model analyzed to calculate Wilson coefficients for the process \f$ \ell_j \to \ell_i \ell_i \ell_i \f$.
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
     * @brief Variable which stores the Wilson coefficient for \f$ \mu \to eee \f$.
     */
    WilsonCoefficient coeffDLi3j_1;
    /**
     * @brief Variable which stores the Wilson coefficient for \f$ \tau \to \mu \mu \mu \f$.
     */
    WilsonCoefficient coeffDLi3j_2;
    /**
     * @brief Variable which stores the Wilson coefficient for \f$ \tau \to eee \f$.
     */
    WilsonCoefficient coeffDLi3j_3;
    
    WilsonCoefficient coeffDLi3j_4;

};

/**
 * @}
 */

#endif	/* HEFFDLI3J_H */
