// cl: /DNDEBUG /MD /EHsc
//
// ?rva004DEA70@Rva004DEA70@@QAEPAXPAUArg1_004DEA70@@PBUCoord3DBase@@@Z retail 0x004DEA70 64B
// Evidence: unlock lane; callee equals 0x00003702; caller jmp 0x0028BE7F (Object+0x240 tail);
// prev ModuleNameGetters next FiringTrackerPoolKey; members +0x20 ptr +0x24 id +0x28 Coord3D +0x34 flag.
// Retail layout (0x004DEA70): a1==0 falls through to the flag/coord tests with the
// success tail at +0x28 and a backward je into it; the a1!=0 arm sits at +0x2F and
// jumps forward to the shared `return 0` tail at +0x3C.
// The guards are separate `return 0` statements, NOT one `&&` chain. Measured in a
// 10-variant probe: every `&&` spelling (plus ternary, bool local, result local and
// the flipped else-first arm) makes MSVC lay the FAIL tail inline and jump to the
// success tail, inverting je/jne at +0x26 and +0x3A. Splitting the chain makes the
// failure paths the fall-through and `return m_ptr20` the single shared tail, which
// is retail byte-for-byte.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../Libraries/Include/Lib/Coord3DBase.h"

struct Arg1_004DEA70
{
	char m_pad[0x74];
	int m_74;
};
class Rva004DEA70
{
public:
	void *rva004DEA70(Arg1_004DEA70 *a1, const Coord3DBase *a2);
private:
	char m_pad00[0x20];
	void *m_ptr20;
	int m_24;
	Coord3D m_coord28;
	bool m_flag34;
};
void *Rva004DEA70::rva004DEA70(Arg1_004DEA70 *a1, const Coord3DBase *a2)
{
	if (a1 == 0) {
		if (m_flag34 == 0)
			return 0;
		if (a2 == 0)
			return 0;
		if (!m_coord28.equals(*a2))
			return 0;
	} else {
		if (m_flag34 != 0)
			return 0;
		if (a1->m_74 != m_24)
			return 0;
	}
	return m_ptr20;
}
