// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// platformsdk
#include <windows.h>

#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"

#include "../../Include/Common/BfmePoolRef10.h"


typedef long Long;

// Existing 0x00051971 assignment body from stlport_stringtailrecord144_dtor.cpp.
// Keep the complete noinline provider visible here: VC7.1 then proves the
// by-value holder remains unchanged across assignment and retains retail's
// EDI-held cleanup pointer in method_005C908B. The pointer-only local copy
// omitted reference counting and competed with the verified provider.
__declspec(noinline) BfmePoolRef10 &BfmePoolRef10::operator=(const BfmePoolRef10 &rhs)
{
	if (this != &rhs)
	{
		if (rhs.m_target)
			InterlockedIncrement((Long *)((char *)rhs.m_target + 0x8c));
		if (m_target)
			m_target->m_ref.Release_Ref();
		m_target = rhs.m_target;
	}
	return *this;
}

#include "../../Include/Common/LargeGroupAudioGridCell.h"

class TargetObj005C8DBF : public LargeGroupAudioGridCell
{
public:
	void method_005C8D6B();
};

class HostClass005C8E0A : public TargetObj005C8DBF
{
public:
	char pad00[8];
	BfmePoolRef10 m_ref08;
	char pad18[0x3a];
	unsigned char m_flag46;

	void rva005C8F17();
	void method_005C9069();

	void method_005C908B(BfmePoolRef10 holder, unsigned char flag);
};

void HostClass005C8E0A::method_005C908B(BfmePoolRef10 holder, unsigned char flag)
{
	rva005C8F17();
	if (!holder.m_target)
		return;
	m_ref08 = holder;
	m_flag46 = flag;
	method_005C8D6B();
	setOverlappedLocking(true);
	method_005C9069();
}
