// cl: /MD /EHsc
// ??1Rva000F1B8F@@UAE@XZ @0x000F1B8F 54B
// Evidence: dtor lane calls rowed Free_String 0x00610A40 plus vptr stores; deleting dtor 0x000F1B73 rowed in OpaqueScalarDeletingDtorsB01; caller 0x000F1B76.
#include "../../../Libraries/Source/WWVegas/WWLib/StringClassData.h"

__forceinline StringClass::~StringClass() { Free_String(); }
struct Rva000F1B8FBase {
	virtual ~Rva000F1B8FBase() {}
	// Retail table 0x00BCEF94: 1 __purecall entry follows.
	virtual void slot1() = 0;
};
struct Rva000F1B8F : Rva000F1B8FBase {
	int m_04;
	StringClass m_08;
	virtual ~Rva000F1B8F();
};
Rva000F1B8F::~Rva000F1B8F() {}

// Inline public teardown calls Free_String directly; the standalone destructor is 0x00065F5B.
