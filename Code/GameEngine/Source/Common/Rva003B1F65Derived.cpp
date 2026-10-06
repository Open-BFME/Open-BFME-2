// cl: /MD
//
// Opaque single-inheritance destructors tail-calling
// UserPreferences::~UserPreferences (rowed at 0x003B1F65 in
// UserPreferences.cpp). Each class below stores its own vtable and tail-calls
// the base destructor; the base is only declared here, because a same-TU
// definition would capture the call locally. The derived owners are still
// opaque here (Rva names); the IgnorePreferences, QuickMatchPreferences and
// GameSpyMiscPreferences destructors that used to sit here are now defined
// beside their constructors, where the vtables prove them.

class UserPreferences
{
public:
	virtual ~UserPreferences();
};

class Rva002E4272 : public UserPreferences
{
public:
	virtual ~Rva002E4272();
};

Rva002E4272::~Rva002E4272()
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
