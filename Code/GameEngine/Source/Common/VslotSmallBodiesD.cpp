// cl: /O1 /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch D. As in VslotSmallBodiesA-C, each class and method
// is address-derived and models only what its body touches; the comment above
// each gives the .rdata slot address(es) that reference it. Meanings are not
// recovered.

typedef int Int;
typedef bool Bool;

// slot at VA 0x00BFAF8C: true when the argument's +0x04 object has its
// +0x580 field equal to this +0x08.
struct Rva00271B3CInner
{
	char m_pad00[0x580];
	Int m_580;
};
struct Rva00271B3CArg
{
	char m_pad00[0x04];
	Rva00271B3CInner *m_04;
};
class Rva00271B3C
{
public:
	Int rva00271B3C(const Rva00271B3CArg *arg);
private:
	char m_pad00[0x08];
	Int m_08;
};
Int Rva00271B3C::rva00271B3C(const Rva00271B3CArg *arg)
{
	if (arg->m_04 && arg->m_04->m_580 == m_08)
		return 1;
	return 0;
}

// slots at VA 0x00BFD00C and 0x00BFD024: a function-local static id taken
// from the running counter at VA 0x00DFEE18 on first use.
extern Int g_rva0029B1EANextId;
class Rva0029B1EA
{
public:
	Int rva0029B1EA();
};
Int Rva0029B1EA::rva0029B1EA()
{
	static Int s_id = g_rva0029B1EANextId++;
	return s_id;
}


// slot at VA 0x00C04FE8: forwards (the argument string's text, the second
// argument) to this object's vslot 17. The string keeps its text 8 bytes into
// its buffer and falls back to the shared empty string at VA 0x00BBAC1C.
extern const char g_rva002E5770Empty[];
struct Rva002E5770Str
{
	struct Buffer
	{
		Int m_refCount;
		Int m_length;
		char m_text[1];
	};
	const char *str() const { return m_data ? m_data->m_text : g_rva002E5770Empty; }
	Buffer *m_data;
};
class Rva002E5770
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02();
	virtual void vslot03(); virtual void vslot04(); virtual void vslot05();
	virtual void vslot06(); virtual void vslot07(); virtual void vslot08();
	virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12(); virtual void vslot13(); virtual void vslot14();
	virtual void vslot15(); virtual void vslot16();
	virtual void vslot17(const char *text, Int value);
	void rva002E5770(const Rva002E5770Str &text, Int value);
};
void Rva002E5770::rva002E5770(const Rva002E5770Str &text, Int value)
{
	vslot17(text.str(), value);
}

// slot at VA 0x00C163DC: resets the bytes +0x08/+0x09/+0x24 (0, 1, 0) and
// hands the +0x10 field to its own vslot 2; the argument is unused.
class Rva0035D133
{
public:
	virtual void vslot00(); virtual void vslot01();
	virtual void vslot02(Int value);
	void rva0035D133(Int unused);
private:
	char m_pad04[0x08 - 0x04];
	Bool m_08;
	Bool m_09;
	char m_pad0A[0x10 - 0x0A];
	Int m_10;
	char m_pad14[0x24 - 0x14];
	Bool m_24;
};
void Rva0035D133::rva0035D133(Int unused)
{
	m_09 = true;
	m_08 = false;
	m_24 = false;
	vslot02(m_10);
}

// slots at VA 0x00C37E6C, 0x00C68604, 0x00C6924C and 0x00C70FAC: calls its
// own vslot 8 with the negated flag and the second argument.
class Rva003FE568
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02();
	virtual void vslot03(); virtual void vslot04(); virtual void vslot05();
	virtual void vslot06(); virtual void vslot07();
	virtual void vslot08(Bool flag, Int value);
	void rva003FE568(Bool flag, Int value);
};
void Rva003FE568::rva003FE568(Bool flag, Int value)
{
	vslot08(!flag, value);
}

// slot at VA 0x00C3A29C: consumes the +0x20 flag (true when it was set).
class Rva0041513D
{
public:
	Bool rva0041513D();
private:
	char m_pad00[0x20];
	Bool m_20;
};
Bool Rva0041513D::rva0041513D()
{
	if (m_20)
	{
		m_20 = false;
		return true;
	}
	return false;
}

// slot at VA 0x00C3AECC: calls vslot 2 on every element of the pointer
// array [+0x0C, +0x10).
class Rva0041E488Element
{
public:
	virtual void vslot00(); virtual void vslot01();
	virtual void vslot02();
};
class Rva0041E488
{
public:
	void rva0041E488();
private:
	char m_pad00[0x0C];
	Rva0041E488Element **m_begin;
	Rva0041E488Element **m_end;
};
void Rva0041E488::rva0041E488()
{
	for (Rva0041E488Element **it = m_begin; it != m_end; ++it)
		(*it)->vslot02();
}

// slot at VA 0x00C3BA78: false while the +0x86 byte is set, else the +0x84
// byte.
class Rva004200FD
{
public:
	Bool rva004200FD();
private:
	char m_pad00[0x84];
	Bool m_84;
	char m_pad85;
	Bool m_86;
};
Bool Rva004200FD::rva004200FD()
{
	if (m_86)
		return false;
	return m_84;
}

// slot at VA 0x00C3C364: consumes the global flag at VA 0x00E031E0.
extern Bool g_rva00426378Pending;
class Rva00426378
{
public:
	Bool rva00426378();
};
Bool Rva00426378::rva00426378()
{
	if (g_rva00426378Pending)
	{
		g_rva00426378Pending = false;
		return true;
	}
	return false;
}

// slot at VA 0x00C3D7EC: the +0x04 object's +0x24 field less this +0x14, or
// 0 without the object.
struct Rva0043C772Inner
{
	char m_pad00[0x24];
	Int m_24;
};
class Rva0043C772
{
public:
	Int rva0043C772();
private:
	char m_pad00[0x04];
	Rva0043C772Inner *m_04;
	char m_pad08[0x14 - 0x08];
	Int m_14;
};
Int Rva0043C772::rva0043C772()
{
	if (m_04)
		return m_04->m_24 - m_14;
	return 0;
}
