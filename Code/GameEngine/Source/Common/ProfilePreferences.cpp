// cl: /O1 /MD
//
// Player-profile preferences (vtable 0x00C68DD8, retail 0x00535762).
// A UserPreferences with no extra members: the constructor only runs the
// base constructor and installs its own vtable. It takes a four-byte
// argument its body ignores (both observed callers pass a constant, 0 or 1,
// and the 20-byte body never reads [esp+8]); the name for the parameter
// below only says what the call sites hand it. The class name itself is
// descriptive -- no retail spelling is known. Adjacent .rdata carries the
// profile stat keys (ProfileCreatedDate, Points, TimePlayed,
// LongestGameTime, ShortestGameTime), and the vtable keeps every
// UserPreferences slot except slot 0. The matching destructor is the
// opaque Rva00535776 row at 0x00535776 (tail-calls UserPreferences dtor).

class UserPreferences
{
public:
	UserPreferences();
	virtual ~UserPreferences();
};

class ProfilePreferences : public UserPreferences
{
public:
	ProfilePreferences(int profileKind);
};

// ??0ProfilePreferences@@QAE@H@Z
ProfilePreferences::ProfilePreferences(int profileKind)
{
	(void)profileKind;
}
