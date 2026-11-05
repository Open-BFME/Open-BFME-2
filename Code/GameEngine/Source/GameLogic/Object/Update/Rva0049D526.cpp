// cl: /DNDEBUG /MD
// ?rva0049D526@Rva0049D526@@QAEXPAX@Z retail 0x0049D526 89B
// ?rva0049D57F@Rva0049D526@@QAEXPAX@Z retail 0x0049D57F 152B
// List remove plus ExitInterface notify plus WeaponTemplateSetHead copy check.
// Evidence: callee 0x0028B445 Object::getObjectExitInterface row, copy ctor row
// 0x00045455 with 0x4C temp, ExitInterface slot 4 call with +0x2C arg.
// List push-front of new entry plus WeaponTemplateSetHead copy check for
// flag bits at +0xD1/+0x114. Head at +0x2C tail at +0x28 count at +0x34.
// Evidence: copy ctor row 0x00045455 with 0x4C temp; link through +0x48/+0x4C;
// callers at 0x0049D987 0x0049DC12. A _ReadWriteBarrier between the shift and
// the test keeps retail mov shr test al 1 shape (else folds to test byte 2).
#include "../../../../Include/Common/WeaponTemplateSetHead.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva0049D526Src
{
	char _pad[0x10C];
	WeaponTemplateSetHead m_head;
};

#include "../../../../Include/GameLogic/Module/ExitInterface.h"

#include "../object.h"

struct Rva0049D526Node
{
	char _pad0[0x04];
	int m_type;
	char _pad08[0x24];
	int m_2C;
	char _pad30[0x18];
	void *m_next;
	void *m_prev;
};

class Rva0049D526
{
public:
	void rva0049D526(void *entry);
	void rva0049D57F(void *entry);

private:
	char _p00[0x08];
	void *m_08;
	char _p0C[0x1C];
	void *m_28;
	void *m_2C;
	char _p30[0x04];
	int m_34;
	char _p38a[0x4D];
	unsigned char m_85;
	char _p86[0x4B];
	unsigned char m_D1;
	char _pD2[0x42];
	unsigned char m_114;
};

void Rva0049D526::rva0049D526(void *entry)
{
	if (m_28 == 0)
		m_28 = entry;
	if (m_2C != 0)
	{
		((Rva0049D526Node *)m_2C)->m_next = entry;
		((Rva0049D526Node *)entry)->m_prev = m_2C;
	}
	++m_34;
	m_2C = entry;
	Rva0049D526Src *src = *(Rva0049D526Src **)((char *)this + 0x08);
	WeaponTemplateSetHead tmp(src->m_head);
	unsigned flags = *(unsigned *)((char *)&tmp + 8);
	flags >>= 9;
	_ReadWriteBarrier();
	if ((flags & 1) == 0)
	{
		m_D1 |= 2;
		m_114 = 1;
	}
}

void Rva0049D526::rva0049D57F(void *entry)
{
	Rva0049D526Node *node = (Rva0049D526Node *)entry;
	if (node->m_type == 1 && node->m_2C != -1)
	{
		Object *obj = (Object *)m_08;
		ExitInterface *ei = obj->getObjectExitInterface();
		if (ei != 0)
			ei->unreserveDoorForExit((ExitDoorType)node->m_2C);
	}
	if (node->m_prev != 0)
		((Rva0049D526Node *)node->m_prev)->m_next = node->m_next;
	else
		m_28 = node->m_next;
	if (node->m_next != 0)
		((Rva0049D526Node *)node->m_next)->m_prev = node->m_prev;
	else
		m_2C = node->m_prev;
	Rva0049D526Src *src = (Rva0049D526Src *)m_08;
	--m_34;
	WeaponTemplateSetHead tmp(src->m_head);
	if (m_34 == 0)
	{
		unsigned v = *(unsigned *)((char *)&tmp + 8);
		v >>= 9;
		_ReadWriteBarrier();
		if ((v & 1) != 0)
		{
			m_85 |= 2;
			m_D1 &= 0xFD;
			m_114 = 1;
		}
	}
}
