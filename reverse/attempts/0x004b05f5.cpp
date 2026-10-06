// ?rva004B05F5@Rva004B05F5@@QAEX_N@Z
// partial score=0.82 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
//
// ?rva004B05F5@Rva004B05F5@@QAEX_N@Z @0x004B05F5 94B.
// Bit 12 of the dword at Object+0x130 gates the body. When that bit is set
// it is cleared and Object::rva0028AE6D runs. A zero byte argument then
// calls the sibling with 1 and FXList::doFXPos at the position.

#include "../../../Libraries/Include/Lib/Coord3D.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Matrix3D;

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *mtx, float speed, const Coord3D *secondary);
};

class Object
{
public:
	void rva0028AE6D();

	char m_pad[0x38];
	Coord3D m_pos;
	char m_mid[0x130 - 0x44];
	unsigned m_flags;
};

class ModuleData
{
public:
	char m_pad[0xD8];
	FXList *m_fx;
};

class Rva004B05F5
{
public:
	void rva004B05F5(bool skip);
	void rva004B04B2(int flag);

private:
	char m_pad[4];
	ModuleData *m_data;
	Object *m_obj;
};

void Rva004B05F5::rva004B05F5(bool skip)
{
	Object *obj = m_obj;
	unsigned flags = obj->m_flags;
	unsigned shifted = flags;
	shifted >>= 12;
	_ReadWriteBarrier();
	if ((shifted & 1) == 0)
		return;
	if ((flags & 0x1000) != 0)
	{
		((unsigned char *)&obj->m_flags)[1] &= 0xEF;
		obj->rva0028AE6D();
	}
	if (skip)
		return;
	rva004B04B2(1);
	FXList::doFXPos(m_data->m_fx, &obj->m_pos, 0, 0.0f, 0);
}
