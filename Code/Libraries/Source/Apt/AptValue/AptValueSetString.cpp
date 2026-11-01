// cl: /MD /EHsc
// AptValue string member setter (retail 0x006CBF70). Assigns a C string
// into the EAStringC at +8 of its object through a guarded temp: build
// the temp with the rowed C-string constructor, copy it over with the
// rowed assignment, and release it with the rowed destructor. The SEH
// registration is the compiler's unwind for the temp under /EHsc.
// Identity note: only +8 is proven (EAStringC target of the assignment
// call); the low 8 bytes are opaque padding. Placed with AptValue
// because all 12 retail callers sit in AptValue construction flows.
#include "../EAStringC.h"

class AptValue
{
public:
	void SetString(const char *text);

	void *m_pad[2];
	EAStringC m_str;
};

// ?SetString@AptValue@@QAEXPBD@Z, retail 0x006CBF70 (94B).
void AptValue::SetString(const char *text)
{
	EAStringC temp(text);
	m_str = temp;
}
