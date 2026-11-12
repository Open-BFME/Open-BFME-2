// cl: /O1 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ??4Rva0054000B@@QAEAAV0@ABV0@@Z @0x00540053 29B (ret 4): the camera-track
// key's copy assignment. Retail stores the int key at +0, then calls the
// 9-dword frame assignment at 0x0053FFCE on +4 and returns this. Its callers
// are the stride-0x28 __copy (0x00540082), __copy_backward (0x005400FF) and
// vector<Rva0054000B>::insert (0x00540731) bodies. The key class and its two
// constructors (0x0054001B, 0x00540036) are in WW3D2/Rva0053FDE6Init.cpp.
// Identity is not recovered: names follow those rows.

// Retail calls the 9-dword frame assignment at 0x0053FFCE, rowed as
// Render2DSentenceClass::SentenceDataStruct::operator= (render2dsentence.cpp),
// as GameEngine/Source/Common/Rva00540B48Append.cpp does.
#include "../WW3D2/Render2DSentenceClass.h"

class Rva0053FDE6
{
public:
	__declspec(dllimport) __forceinline Rva0053FDE6 &operator=(const Rva0053FDE6 &o)
	{
		*(Render2DSentenceClass::SentenceDataStruct *)this = *(const Render2DSentenceClass::SentenceDataStruct *)&o;
		return *this;
	}
	int m_00;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	float m_1c;
	float m_20;
};

#include "../../../../GameEngine/Include/Common/Rva0054000B.h"

Rva0054000B &Rva0054000B::operator=(const Rva0054000B &o)
{
	m_00 = o.m_00;
	m_04 = o.m_04;
	return *this;
}
