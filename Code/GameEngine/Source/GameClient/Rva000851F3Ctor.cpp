// cl: /MD /EHsc /DNDEBUG
// ??0Rva000851F3@@QAE@XZ, retail 0x000851F3, 71 bytes.
// Ctor storing the real three-slot vtable BC745C at +0, then ParabolicEase
// at +0x10 via rowed 0x0008517E
// with (0 0 1) then zeroing +4 +8 +0x20 +0x24 +0x28 +0x18 +0x1c.
// Evidence: rowed ParabolicEase forward 0x0008517E; callers 0x0008990C 0x00312C95.
// BC745C = {scalar-delete 85241, purecall 3B810, purecall 3B810}; its
// first pointer incidentally spells "ARH". Plain cleanup 8523A restores
// the table; scalar-delete 85241 is 29B/RET4 and restores it before delete.
// Derived BC74F4 has matching RET4/RET24 slots. The first slot argument
// and final unused word of the second retain only their ABI word views.
// Original names, complete layout and historical class identity are unknown.
#include "../../Include/GameClient/Rva0008990CArrayOwner.h"

Rva000851F3::Rva000851F3()
{
	m_10.rva0008517E(0.0f, 0.0f, 1.0f);
	m_04 = 0;
	m_08 = 0;
	m_20 = 0;
	m_24 = false;
	m_28 = 0;
	m_18 = 0.0f;
	m_1C = 0.0f;
}
