// cl: /O1 /DNDEBUG /MD
//
// ?rva004A5B09@Rva004A5B09@@QAEXPAVPosHolder@@H@Z @0x004A5B09 88B.
// Virtual slot 15 on the object at +8. A null result, or a set bit in the
// holder dword at +0x4C, plays FXList::doFXPos. Then the sibling at
// 0x004A584B runs on the position.

#include "../../../Libraries/Include/Lib/Coord3D.h"

class Matrix3D;

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *mtx, float speed, const Coord3D *secondary);
};

class BitSource
{
public:
	char m_pad[0x10];
	int m_index;
};

class VTable15
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual BitSource *s15();
};

class Object
{
public:
	char m_pad[0x254];
	VTable15 *m_v;
};

class Holder
{
public:
	char m_pad[0x4C];
	unsigned m_bits;
	FXList *m_fx;
};

class PosHolder
{
public:
	char m_pad[0x38];
	Coord3D m_pos;
};

class Rva004A5B09
{
public:
	void rva004A5B09(PosHolder *pos, int unused);
	void rva004A584B(int zero, Coord3D *at);

private:
	char m_pad[4];
	Holder *m_holder;
	Object *m_obj;
};

void Rva004A5B09::rva004A5B09(PosHolder *pos, int)
{
	Holder *holder = m_holder;
	BitSource *src = m_obj->m_v->s15();
	if (src == 0 || (holder->m_bits & (1u << (src->m_index - 1))) != 0)
		FXList::doFXPos(holder->m_fx, &pos->m_pos, 0, 0.0f, 0);
	rva004A584B(0, &pos->m_pos);
}
