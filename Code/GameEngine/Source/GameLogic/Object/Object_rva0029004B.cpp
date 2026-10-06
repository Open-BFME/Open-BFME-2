// cl: /O1 /DNDEBUG /MD
//
// ?rva0029004B@Object@@QAEXXZ @0x0029004B (74B).
// Object flag-or plus Drawable notify plus null-terminated array walk.
// Evidence: neighbours ?healCompletely@Object (0x0028FF9E) and
// ?rva002900E0@Object (0x002900E0) prove Object TU and /O1 flags; callee
// 0x00274401 is rowed ?setInaudible@Drawable@@QAEXXZ; retail offsets +0x9a
// flag 0x10, +0x84 Drawable, +0x435 gate, +0x244 array.

class Drawable
{
public:
	void setInaudible();
	void setAudible();
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class RetObj
{
public:
	virtual void slot0();
	virtual void slot1();
};

class MidObj
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
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual RetObj *slot36();
};

struct Elem0029004B
{
	char m_pad[12];
	MidObj m_midC;
};

class Object
{
public:
	void rva0029004B();
	void rva00290095();
	unsigned char *flagEscape();

private:
	char m_pad0[0x84];
	Drawable *m_drawable84;
	char m_pad1[0x9A - 0x88];
	unsigned char m_flags9A;
	char m_pad2[0x244 - 0x9B];
	Elem0029004B **m_arr244;
	char m_pad3[0x435 - 0x248];
	bool m_flag435;
};

void Object::rva0029004B()
{
	m_flags9A |= 0x10;
	_ReadWriteBarrier();
	if (m_drawable84 != 0)
		m_drawable84->setInaudible();
	if (!m_flag435)
		return;
	for (Elem0029004B **p = m_arr244; *p != 0; ++p) {
		Elem0029004B *e = *p;
		RetObj *r = e->m_midC.slot36();
		if (r != 0)
			r->slot0();
	}
}

// ?rva00290095@Object@@QAEXXZ @0x00290095 (75B).
// Object flag-and plus Drawable notify plus null-terminated array walk.
// Evidence: sibling ?rva0029004B@Object (0x0029004B) same TU same flags same offsets; callee
// 0x00278644 is rowed ?setAudible@Drawable@@QAEXXZ; retail and 0x9a flag 0xef, gate +0x435, array +0x244.
void Object::rva00290095()
{
	m_flags9A &= (unsigned char)~0x10;
	_ReadWriteBarrier();
	if (m_drawable84 != 0)
		m_drawable84->setAudible();
	if (!m_flag435)
		return;
	for (Elem0029004B **p = m_arr244; *p != 0; ++p) {
		Elem0029004B *e = *p;
		RetObj *r = e->m_midC.slot36();
		if (r != 0)
			r->slot1();
	}
}

// ?flagEscape@Object@@QAEPAEXZ absent-from-retail
unsigned char *Object::flagEscape()
{
	return &m_flags9A;
}
