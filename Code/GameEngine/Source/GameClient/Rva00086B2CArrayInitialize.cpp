// cl: /MD /DNDEBUG
// Reference: clean BFME1 6d9434269164392c5ba62aaa7c15a86b5b020d76,
// game/GameEngineDevice/Source/W3DDevice/GameClient/Rva0073C700Configure.cpp.
// Target RVA 0x00086B2C is 153B/RET24; derived vtable VA BC74F4 slot 2
// points here. Retail independently uses float arguments and zero float
// stores at +18/+1C, unlike the donor's integer views and bit casts.
// The two cleared arrays have 257 and 255 DWORDs at +1864/+1C74; the
// latter is then filled up to the repeatedly read signed count at +2070.
// These offsets prove an accessed prefix, not a complete object size.
// Original owner/method names and the final unused parameter type remain
// unknown. The shared view follows the independently proven three-slot dispatch.
#include "../../Include/GameClient/Rva0008990CArrayOwner.h"

void Rva0089971::rva00086B2C(int value, int duration, Real first, Real second, int stored, int unused)
{
	int i = 0;
	while (i < 0x101)
	{
		m_values[i] = 0;
		++i;
	}
	i = 0;
	while (i < 0xFF)
	{
		m_filled[i] = 0;
		++i;
	}
	i = 0;
	if (m_numValues > 0)
	{
		do
		{
			m_filled[i] = value;
			++i;
		} while (i < m_numValues);
	}
	m_04 = duration > 1 ? duration : 1;
	m_08 = 0;
	m_18 = 0.0f;
	m_1C = 0.0f;
	m_20 = 0;
	m_28 = 1;
	m_10.rva0030E51F(first, second, (Real)duration);
	m_0C = stored;
	m_24 = 1;
}
