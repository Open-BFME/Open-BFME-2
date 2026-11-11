#include "../../../Libraries/Source/Apt/AptPlayerClass.h"
// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva005EC46F@Rva005EC46F@@QAEXXZ @0x005EC46F 59B: unlocks 0x005EC4AF.
// State machine over +8 with cases 2 4 5. Case 4 releases owner via pinned
// ?rva0022277D@Rva00222A8BTarget@@QAEXPAX@Z through TheRva00222A8BTarget and
// zeroes state. Case 2 tests inline +0x10 via rowed
// ?rva005FA854@Rva005FA854@@QAE_NXZ and falls into case 5 which tail-runs
// rowed ?FadeOut@StrategicVeterancy@@QAEXXZ on the +0 member. Layout follows
// Rva005EC23EWindow (+0 ptr +4 owner +8 state) plus inline +0x10 object.

#include "../../Include/Common/Rva00222A8BTarget.h"
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

#include "../../Include/Common/Rva005FA854.h"

#include "../../Include/GameClient/StrategicVeterancy.h"

class Rva005EC46F
{
public:
	void rva005EC46F();
private:
	StrategicVeterancy *m_00;
	void *m_04;
	int m_08;
	char m_pad0C[4];
	Rva005FA854 m_10;
};

void Rva005EC46F::rva005EC46F()
{
	switch (m_08)
	{
	case 4:
		reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager)->HideLevel((int)m_04);
		m_08 = 0;
		break;
	case 2:
		if (!m_10.rva005FA854())
			return;
	case 5:
		return m_00->FadeOut();
	default:
		return;
	}
}
