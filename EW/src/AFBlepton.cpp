/* 
 * Copyright (C) 2012 HEPfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "AFBlepton.h"

double AFBlepton::computeThValue()
{
    return SM.AFB(SM.getLeptons(SM.ELECTRON));
}


