// cl: /DNDEBUG /MD /EHsc
// ?rva003FD6E0@Rva003FD6E0@@QAEXXZ @0x003FD6E0 54B: __thiscall void cleanup
// touching [+0x04] pointer and its [+0x08] sub-pointer with virtual calls.
// Evidence: retail loads [esi+4] twice; calls [[eax+8]] slot 0x40 then
// [[ecx]] slot 0 with arg 0; deletes result via rowed ??3@YAXPAX@Z and clears
// [esi+4]; caller at 0x002115A9 iterates array calling this; neighbours are
// Rva003FD789 xfer/ctor; callee row mem_ops.cpp.
void __cdecl operator delete(void *p);

class Rva003FD6E0Inner
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
};

class Rva003FD6E0Mid
{
public:
	virtual void *virt00(int arg);
	int m_04;
	Rva003FD6E0Inner *m_08;
};

class Rva003FD6E0
{
	char m_pad[4];
	Rva003FD6E0Mid *m_04; // +0x04
public:
	void rva003FD6E0();
};

void Rva003FD6E0::rva003FD6E0()
{
	if (!m_04)
		return;
	Rva003FD6E0Inner *inner = m_04->m_08;
	if (inner)
		inner->v16();
	void *toDelete = m_04 ? m_04->virt00(0) : 0;
	::operator delete(toDelete);
	m_04 = 0;
}
