#ifndef INTERMODFUNCTIONS_H
#define INTERMODFUNCTIONS_H


// Project
#include "IntermodSettings.h"

// RsaToolbox
#include <Vna.h>


void configureChannelForIntermod(RsaToolbox::Vna *vna, uint channel, IntermodSettings settings);


#endif // INTERMODFUNCTIONS_H
