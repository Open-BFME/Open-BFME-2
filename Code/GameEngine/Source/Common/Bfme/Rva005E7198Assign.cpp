// cl: /DNDEBUG /MD /EHsc
// ??4Rva005E7198@@QAEAAV0@ABV0@@Z @0x005E7198 46B
// Smart-pointer assign with self-check via rowed Release 0x0007DEEF plus +0x28 AddRef.
// Evidence: cmp esi edi je plus inc [eax+0x28] plus lea +0x24 fastcall Release plus
// callers @0x005E7277 @0x005E729E @0x005E830E; same +0x28 recipe as rowed
// Rva00427A70 assign 0x005E7184 and Rva005E71C6Assign 0x005E71C6.
#include "../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct Rva005E7198Object
{
	unsigned char m_pad[0x24];
	TargetRef00217D4C m_ref;
};
class Rva005E7198
{
public:
	Rva005E7198 &operator=(const Rva005E7198 &other);
private:
	Rva005E7198Object *m_object;
};
Rva005E7198 &Rva005E7198::operator=(const Rva005E7198 &other)
{
	if (this == &other)
		return *this;
	Rva005E7198Object *newObject = other.m_object;
	if (newObject)
		++newObject->m_ref.references;
	Rva005E7198Object *oldObject = m_object;
	if (oldObject)
		ReleaseTreeHintRef00217D4C(&oldObject->m_ref);
	m_object = other.m_object;
	return *this;
}
