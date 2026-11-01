// cl: /EHsc
// ??1Rva005D4EC6@@QAE@XZ @0x005D4EC6 72B
// Member dtor calling Holder dtor at +0xC via rowed 0x005F4AD7 then direct
// Release of TargetRef at +8 via rowed 0x0007DEEF then base dtor
// ??1AptLoadMovieFrame@@UAE@XZ at +0. Same Holder trio as Rva005F4AD7Dtor.
// Evidence: chain lane calls rowed Holder dtor; callers at 0x005D4F87 0x005D4FAC;
// unblocks 0x005D4FA0; base rowed in OpaqueScalarDeletingDtors; next row
// ??1Rva005D50D8@@UAE@XZ shares /O1 layout.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct AptLoadMovieFrame
{
	virtual ~AptLoadMovieFrame();
	int m_04;
};
struct Rva005F4AD7Inner;
struct Rva005F4AD7
{
	Rva005F4AD7Inner *m_ptr;
	~Rva005F4AD7();
};
struct Rva005D4EC6Holder08
{
	TargetRef00217D4C *m_ptr;
	~Rva005D4EC6Holder08() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
struct Rva005D4EC6
{
	AptLoadMovieFrame m_00;
	Rva005D4EC6Holder08 m_08;
	Rva005F4AD7 m_0C;
	~Rva005D4EC6();
};
Rva005D4EC6::~Rva005D4EC6()
{
}
