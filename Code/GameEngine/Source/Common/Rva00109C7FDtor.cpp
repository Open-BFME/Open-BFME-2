// cl: /DNDEBUG /MD /EHsc -ICode/Libraries/Source/WWVegas/WW3D2 -ICode/Libraries/Source/WWVegas/WWLib -ICode/Libraries/Source/WWVegas/WWMath -ICode/Libraries/Source/WWVegas/WWSaveLoad -ICode/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/shims/sweep
// Complete54B destructor109C7F belongs to the60B constructor109C27:
// native BCFA0C is [deleting109C63, key30F45F]. Both use StringClass at+8
// above the8B HashableClass base. Its full8B BCEF94 table is deletingEF9D6
// then purecall; existing13B ctorEF9C2 and7B dtorEF9CF prove NextHash+4.
// The inherited Hashable layout/semantics follow WWLib hash.h at BFME1
// a7c38d3b2597121f178ab5190b3062478823257d; table and complete target
// lifetimes independently prove that relationship. Derived identity stays
// address-derived. Native key getter returns the buffer at+8 in4B.
// Owner bytes, both deleting callback bytes and native EH graph are exact.
#include "../../../Libraries/Source/WWVegas/WWLib/StringClassData.h"

__forceinline StringClass::~StringClass() { Free_String(); }
inline StringClass::operator const char *() const { return m_Buffer; }
#include "../../../Libraries/Source/WWVegas/WWLib/HashableClass.h"
class Rva00109C27 : public HashableClass
{
public:
	virtual ~Rva00109C27();
    virtual const char *Get_Key();
private:
	StringClass m_str;
};
Rva00109C27::~Rva00109C27()
{
}

// Inline public teardown calls Free_String directly; the standalone destructor is 0x00065F5B.

const char *Rva00109C27::Get_Key() { return m_str; }
