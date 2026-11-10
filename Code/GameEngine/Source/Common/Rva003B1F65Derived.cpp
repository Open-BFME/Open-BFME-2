// cl: /MD
// stlport
//
// Derived destructors tail-calling UserPreferences::~UserPreferences
// (rowed at 0x003B1F65 in UserPreferences.cpp). OptionPreferences::~OptionPreferences
// (0x002E4272) installs 0x00C04CE8 and tail-calls UserPreferences::~UserPreferences.

#include "../../Include/Common/UserPreferences.h"
#include "../../Include/Common/OptionPreferences.h"

OptionPreferences::~OptionPreferences()
{
}
