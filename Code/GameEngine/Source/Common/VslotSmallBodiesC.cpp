// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra size (sized from
// their bytes), batch C: guarded forwards, flag and field logic. Each class
// and method is address-derived unless the ledger already names it, and
// models only what its body touches; the comment above each gives the vtable
// and slot. Types are what the bytes require; meanings are not recovered.

typedef int Int;
typedef bool Bool;
typedef float Real;

template <int N> class VslotPad : public VslotPad<N - 1>
{
public:
	virtual void pad(char (*)[N]);
};
template <> class VslotPad<0>
{
public:
	virtual void pad0();
};

// vtable 0x00BC6540#2-#6 and #9: forward to the same slot of the object at
// +8 when there is one (false or 0 without it).
class Rva00072A08Inner : public VslotPad<1>
{
public:
	virtual Bool slot2(Int a0, Int a1);
	virtual void slot3(Int a0);
	virtual void slot4(Int a0);
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual Int slot9();
};
class Rva00072A08
{
public:
	Bool rva00072A08(Int a0, Int a1);
	void rva00072A19(Int a0);
	void rva00072A28(Int a0);
	void rva00072A37();
	void rva00072A44();
	Int rva00072ADE();
private:
	char m_pad00[0x08];
	Rva00072A08Inner *m_08;
};
Bool Rva00072A08::rva00072A08(Int a0, Int a1)
{
	Rva00072A08Inner *inner = m_08;
	if (!inner)
		return false;
	return inner->slot2(a0, a1);
}
void Rva00072A08::rva00072A19(Int a0) { Rva00072A08Inner *inner = m_08; if (inner) inner->slot3(a0); }
void Rva00072A08::rva00072A28(Int a0) { Rva00072A08Inner *inner = m_08; if (inner) inner->slot4(a0); }
void Rva00072A08::rva00072A37() { Rva00072A08Inner *inner = m_08; if (inner) inner->slot5(); }
void Rva00072A08::rva00072A44() { Rva00072A08Inner *inner = m_08; if (inner) inner->slot6(); }
Int Rva00072A08::rva00072ADE()
{
	Rva00072A08Inner *inner = m_08;
	if (inner)
		return inner->slot9();
	return 0;
}

// vtable 0x00BC80A0#33 and #32: slots 143 and 142 of the object at +0x14,
// when there is one.
class Rva00091DB2Inner : public VslotPad<141>
{
public:
	virtual Bool slot142(Int a0);
	virtual void slot143();
};
class Rva00091DB2
{
public:
	void rva00091DB2();
	Bool rva00091F95(Int a0);
private:
	char m_pad00[0x14];
	Rva00091DB2Inner *m_14;
};
void Rva00091DB2::rva00091DB2()
{
	if (m_14 != 0)
		m_14->slot143();
}
Bool Rva00091DB2::rva00091F95(Int a0)
{
	if (m_14 != 0)
		return m_14->slot142(a0);
	return false;
}

// vtable 0x00C164F0#6: own slot 2 with 2 unless the byte at +8 is set.
class Rva0035D512 : public VslotPad<1>
{
public:
	virtual void slot2(Int value);
	void rva0035D512();
private:
	char m_pad04[0x08 - 0x04];
	Bool m_08;
};
void Rva0035D512::rva0035D512()
{
	if (!m_08)
		slot2(2);
}

// vtable 0x00BC6FF4#1: the cdecl function at +8 with both arguments.
class Rva00080256
{
public:
	void rva00080256(Int a0, Int a1);
private:
	char m_pad00[0x08];
	void (__cdecl *m_function08)(Int, Int);
};
void Rva00080256::rva00080256(Int a0, Int a1) { m_function08(a0, a1); }

class Rva0007E971
{
public:
	~Rva0007E971();
};

class Rva00080266
{
public:
	void rva00080266();
};

void Rva00080266::rva00080266()
{
	((Rva0007E971 *)this)->~Rva0007E971();
}


// vtable 0x00BE82B8#18: 1 when +0x14 is set and +0x1C is not.
class Rva00232E2F
{
public:
	Int rva00232E2F();
private:
	char m_pad00[0x14];
	Int m_14;
	char m_pad18[0x1C - 0x18];
	Int m_1C;
};
Int Rva00232E2F::rva00232E2F() { return m_14 != 0 && m_1C == 0; }

// vtable 0x00BC7A88#20: toggle the byte at +0x811.
class Rva0008EF81
{
public:
	void rva0008EF81();
private:
	char m_pad00[0x811];
	Bool m_811;
};
void Rva0008EF81::rva0008EF81() { m_811 = 1 - m_811; }

// InGameUI::setSelecting: defined in InGameUIInputModes.cpp (its row's unit).

// vtable 0x00BC7568#122: 1 when neither +0x8C nor +0x90 is -1.
class Rva0008BBC7
{
public:
	Int rva0008BBC7();
private:
	char m_pad00[0x8C];
	Int m_8C;
	Int m_90;
};
Int Rva0008BBC7::rva0008BBC7()
{
	if (m_8C != -1 && m_90 != -1)
		return 1;
	return 0;
}

// The partition filter base (ctor 0x000421C8, vftable 0x00BC26E0).
class Object;
class Rva000421C8
{
public:
	virtual ~Rva000421C8();
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

// vtable 0x00BFAD28#2: the bit (+8)->+0x54 as a mask, complemented unless the
// byte at +0xC is set.
struct Rva00261368Source
{
	char m_pad00[0x54];
	Int m_54;
};
class Rva0026137EFilter : public Rva000421C8
{
public:
	virtual Int getPlayerMask();
private:
	Rva00261368Source *m_08;
	Bool m_0C;
};
Int Rva0026137EFilter::getPlayerMask()
{
	Int mask = 1 << m_08->m_54;
	return m_0C ? mask : ~mask;
}

// vtable 0x00BCE788#139: +0x3934 becomes 1 for true and 2 for false.
class Rva000E13A7
{
public:
	void rva000E13A7(Bool value);
	Int rva000E1657();
private:
	char m_pad00[0x3934];
	Int m_3934;
	struct Item { char m_pad00[0x1C]; Int m_1C; } *m_3938;
};
void Rva000E13A7::rva000E13A7(Bool value) { m_3934 = value ? 1 : 2; }

// vtable 0x00BCE788#147: +0x1C of the object at +0x3938, else 4.
Int Rva000E13A7::rva000E1657() { return m_3938 ? m_3938->m_1C : 4; }

// vtable 0x00BC7A88#75: +8 of the first node of the circular list at +0x20,
// 0 when the list is empty.
struct Rva0029C096Node
{
	Rva0029C096Node *m_next;
	void *m_04;
	Int m_08;
};
class Rva0029C096
{
public:
	Int rva0029C096();
private:
	Rva0029C096Node *begin() const { return m_20->m_next; }
	Rva0029C096Node *end() const { return m_20; }
	char m_pad00[0x20];
	Rva0029C096Node *m_20;
};
Int Rva0029C096::rva0029C096()
{
	if (begin() == end())
		return 0;
	return begin()->m_08;
}

// vtable 0x00BFDC60#0: the 16-bit field at +4 of **(+4), 0 without it.
struct Rva002AAD89Item
{
	void *m_00;
	unsigned short m_04;
};
class Rva002AAD89
{
public:
	Int rva002AAD89();
private:
	void *m_00;
	Rva002AAD89Item ***m_04;
};
Int Rva002AAD89::rva002AAD89()
{
	Rva002AAD89Item *item = **m_04;
	return item ? item->m_04 : 0;
}

// REF slots 0x007C7BBC 0x007FD544 neighbours rva0029C096/get: search the
// circular list at +0x20 for a node whose dword field matches the arg.
// ?rva0029C0A9@Rva0029C0A9@@QAE_NH@Z
class Rva0055A88BDwordField
{
public:
	int get() const;
};
struct Rva0029C0A9Node
{
	Rva0029C0A9Node *m_next;
	void *m_04;
	Rva0055A88BDwordField *m_08;
};
class Rva0029C0A9
{
public:
	bool rva0029C0A9(int value);
private:
	Rva0029C0A9Node *begin() const { return m_20->m_next; }
	Rva0029C0A9Node *end() const { return m_20; }
	char m_pad00[0x20];
	Rva0029C0A9Node *m_20;
};
bool Rva0029C0A9::rva0029C0A9(int value)
{
	for (Rva0029C0A9Node *it = begin(); it != end(); it = it->m_next)
		if (it->m_08->get() == value)
			return true;
	return false;
}
