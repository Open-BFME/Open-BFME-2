// cl: /MD /EHsc
// ??1Rva000F1B8F@@UAE@XZ @0x000F1B8F 54B
// Native teardown frees the StringClass key at +8 above the shared eight-byte
// HashableClass. This TU also owns deleting destructor 0x000F1B73; its table's
// Get_Key slot points to the complete four-byte buffer getter at 0x0030F45F.
#include "../../../Libraries/Source/WWVegas/WWLib/StringClassData.h"

__forceinline StringClass::~StringClass() { Free_String(); }
#include "../../../Libraries/Source/WWVegas/WWLib/HashableClass.h"
inline StringClass::operator const char *() const { return m_Buffer; }
struct Rva000F1B8F : HashableClass {
	StringClass m_08;
	virtual ~Rva000F1B8F();
	virtual const char *Get_Key() { return m_08; }
};
Rva000F1B8F::~Rva000F1B8F() {}

// Inline public teardown calls Free_String directly; the standalone destructor is 0x00065F5B.
