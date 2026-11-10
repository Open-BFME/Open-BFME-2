// cl: /MD
// stlport
//
// Derived destructors tail-calling UserPreferences::~UserPreferences
// (rowed at 0x003B1F65 in UserPreferences.cpp). OptionPreferences::~OptionPreferences
// (0x002E4272) installs 0x00C04CE8 and tail-calls UserPreferences::~UserPreferences.
// Rva00535776 stays here until ProfilePreferences / stats views are reconciled.

#include "../../Include/Common/UserPreferences.h"
#include "../../Include/Common/OptionPreferences.h"

OptionPreferences::~OptionPreferences()
{
}

class Rva00535776 : public UserPreferences
{
public:
	virtual ~Rva00535776();
};

Rva00535776::~Rva00535776()
{
}


// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1RealTimeStatsPreferences@@UAE@XZ=??1Rva00535776@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1StrategicStatsPreferences@@UAE@XZ=??1Rva00535776@@UAE@XZ")
