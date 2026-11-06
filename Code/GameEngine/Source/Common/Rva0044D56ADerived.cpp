// cl: /MD
// stlport
//
// Single-inheritance destructors tail-calling the matched GameModePreferences
// base dtor at 0x0044D56A (vptr 0xC3EF60, AsciiString at +0x18, base dtor
// chain at 0x3B1F65). GameModePreferences.cpp establishes the base identity;
// Rva0054F508Ctor.cpp independently confirms that class's inheritance. Keep
// only the external base declaration here so calls resolve through the ledger
// address rather than a same-TU definition. LANPreferences is the class whose
// retail vftable 0x00C3EF04 this destructor installs; GameModePreferences.cpp
// defines its constructor on the same base view. Rva0054F508 remains opaque.

class AsciiString;
class UnicodeString;

// Virtual interface as Rva0054F508Ctor.cpp declares it (retail vftable 0x0086AA60:
// deleting dtor, then UserPreferences' load/write/get/set slots, GameModePreferences overrides).
#include "../../Include/Common/UserPreferences.h"
#include "../../Include/Common/GameModePreferences.h"


class LANPreferences : public GameModePreferences
{
public:
	virtual ~LANPreferences();
};

LANPreferences::~LANPreferences()
{
}

class Rva0054F508 : public GameModePreferences
{
public:
	virtual ~Rva0054F508();
};

Rva0054F508::~Rva0054F508()
{
}
