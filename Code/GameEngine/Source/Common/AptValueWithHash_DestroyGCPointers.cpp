// cl: /MD
// AptValueWithHash slot 11 in retail vtable 0x008EA228 sets destroyed-GC bit 3.
// It then clears the native hash at +8 through AptNativeHash::DestroyGCPointers.
#include "../../../Libraries/Source/Apt/AptNativeHash.h"

class AptValueWithHash
{
public:
	virtual void DestroyGCPointers();
	unsigned int m_flags;
	AptNativeHash m_table;
};

void AptValueWithHash::DestroyGCPointers()
{
	m_flags |= 8;
	m_table.DestroyGCPointers();
}
