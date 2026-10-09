// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0009B0B7@Rva0008FF3E@@UAEXXZ, retail 0x0009B0B7..0x0009B254 (413 bytes).
// Slot 27 (+0x6C) of the vtable 0x007C7DC8 that the rowed constructor
// 0x0008FF3E stores. A per-frame update: nothing while the game is paused,
// then the rowed pause-gated step 0x002C021A, then by the state at +0x14:
//  - 2: the +0x198 fade value rises by g_00DE5E00 up to 1; past 1, once
//    TheTransitionHandler reports finished, slots 19 (1, 1), 10 (0) and 33
//    run with the value reset;
//  - 3: the fade value falls by g_00DE5E00; below zero it is clamped and
//    slot 34 runs;
//  - otherwise, while the +0x18 flag is set and the game is not paused, a
//    non-zero +0x138 velocity moves +0x134, decays by
//    TheLivingWorldManager's +0x1D4 factor (cleared under 0.001) and the
//    position is clamped to [g_00DE5E44, g_00DB4AA8] (rowed clamp<float>).
// The three globals are file statics the view's INI setup 0x0009D3A0 fills
// with atof results; they have no ledger names, so they are address-named.
// Class identity is address-derived from the constructor.

#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class GameWindowTransitionsHandler
{
public:
	bool isFinished();
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

struct Rva0009B0B7Manager
{
	char m_pad000[0x1D4];
	float m_decay1D4; // +0x1D4
};

class Rva002C021A
{
public:
	void rva002C021A();
};

template <class NUM>
NUM clamp(NUM lo, NUM val, NUM hi);

#include <math.h>

extern float g_00DE5E00;
extern float g_00DE5E44;
extern float g_00DB4AA8;


class Rva0008FF3E
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10(int);
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19(int, int);
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void rva0009B0B7();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();

private:
	char m_pad004[0x14 - 0x04];
	int m_state14;          // +0x14
	bool m_active18;        // +0x18
	char m_pad019[0x134 - 0x19];
	float m_position134;    // +0x134
	float m_velocity138;    // +0x138
	char m_pad13C[0x198 - 0x13C];
	float m_fade198;        // +0x198
};

void Rva0008FF3E::rva0009B0B7()
{
	if (TheGameLogic->isGamePaused())
		return;

	reinterpret_cast<Rva002C021A *>(this)->rva002C021A();

	switch (m_state14)
	{
	case 2:
		if (m_fade198 <= 1.0f)
			m_fade198 += g_00DE5E00;
		if (m_fade198 > 1.0f && TheTransitionHandler->isFinished())
		{
			v19(1, 1);
			m_fade198 = 0.0f;
			v10(0);
			v33();
		}
		break;

	case 3:
		m_fade198 -= g_00DE5E00;
		if (m_fade198 < 0.0f)
		{
			m_fade198 = 0.0f;
			v34();
		}
		break;

	default:
		if (!m_active18)
			return;
		if (TheGameLogic->isGamePaused())
			return;
		if (m_velocity138 != 0.0f)
		{
			m_position134 += m_velocity138;
			m_velocity138 = reinterpret_cast<Rva0009B0B7Manager *>(TheLivingWorldManager)->m_decay1D4 * m_velocity138;
			if (fabs(m_velocity138) < 0.001f)
				m_velocity138 = 0.0f;
			m_position134 = clamp(g_00DE5E44, m_position134, g_00DB4AA8);
		}
		break;
	}
}
