// cl: /O1 /DNDEBUG /MD /EHs
//
// Opaque scalar deleting destructors, batch B05: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner. Each destructor is declared, not defined, so the call
// resolves to its pin in reverse/symbols.csv (address names unless the
// destructor already carried one); the dummy tag constructors (no retail
// counterpart) only make this TU emit each vtable and with it the deleting
// destructor. Owner identities are not recovered, and these declarations
// model no layout (docs/reconstruction/deleting-destructor-identity-audit.md)
// beyond the secondary-base offsets their adjustor thunks prove.
//
//   wrapper     dtor        vtable#slot
//   0x00246213  0x00243BA0  0x00BEE130#0
//   0x0025361E  0x0047A724  0x00C465F8#0
//   0x00254418  0x004905B0  0x00C4B6C8#0
//   0x002563B2  0x002563CE  0x00BF3AC0#0
//   0x002571DD  0x00256E96  0x00BF3FEC#0
//   0x0025E51D  0x0025E4CD  0x00BF6040#0
//   0x0026E81A  0x0026E7EA  0x00BFA3A4#0
//   0x0026F597  0x0026F445  0x00BFABB8#0
//   0x00279FFC  0x002793F0  0x00BFB0B4#7
//   0x002862AD  0x00285BEC  0x00BFB700#11
//   0x00287C05  0x00286F8F  0x00BFB7BC#0
//   0x002896EA  0x002894A2  0x00BFB840#0
//   0x0029A10F  0x00299CE4  0x00BFC300#7
//   0x002A6A11  0x002A5B30  0x00BFD410#0
//   0x002A93F5  0x002A921B  0x00BFDB94#0
//   0x002BAEE5  0x002B964F  0x00BFE2E4#0
//   0x002BFD53  0x002BFB2D  0x00BFE508#0
//   0x002C5590  0x002C5398  0x00BFF658#0
//   0x002C65EB  0x002C6354  0x00C004E4#0
//   0x002CD5E0  0x002CCD56  0x00C02114#0
//   0x002CE047  0x002CD4A6  0x00C02170#0
//   0x002D09F5  0x002D0588  0x00C0233C#0
//   0x002D2C9E  0x005248D0  0x00C02A80#0
//   0x002D579A  0x002D5333  0x00C02C1C#0

struct EmitVtableTag;

class Rva00243BA0Base0 { public: virtual ~Rva00243BA0Base0(); private: char m_unmodelled[0x8]; };
// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x00243EDF in its vtable is target evidence for it.
class Rva00243BA0BaseC { public: virtual ~Rva00243BA0BaseC(); };
class Rva00243BA0 : public Rva00243BA0Base0, public Rva00243BA0BaseC
{
public:
	Rva00243BA0(EmitVtableTag *);
public:
	virtual ~Rva00243BA0();
};

// ?<Rva00243BA0::Rva00243BA0> absent-from-retail
Rva00243BA0::Rva00243BA0(EmitVtableTag *)
{
}

class Rva0047A724
{
public:
	Rva0047A724(EmitVtableTag *);
public:
	virtual ~Rva0047A724();
};

// ?<Rva0047A724::Rva0047A724> absent-from-retail
Rva0047A724::Rva0047A724(EmitVtableTag *)
{
}

class Rva004905B0
{
public:
	Rva004905B0(EmitVtableTag *);
public:
	virtual ~Rva004905B0();
};

// ?<Rva004905B0::Rva004905B0> absent-from-retail
Rva004905B0::Rva004905B0(EmitVtableTag *)
{
}

class Rva002563CE
{
public:
	Rva002563CE(EmitVtableTag *);
public:
	virtual ~Rva002563CE();
};

// ?<Rva002563CE::Rva002563CE> absent-from-retail
Rva002563CE::Rva002563CE(EmitVtableTag *)
{
}

class Rva00256E96Base0
{
public:
	virtual ~Rva00256E96Base0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) in its vtable is target evidence for it.
class Rva00256E96BaseC
{
public:
	virtual ~Rva00256E96BaseC();
};
class Rva00256E96 : public Rva00256E96Base0, public Rva00256E96BaseC
{
public:
	Rva00256E96(EmitVtableTag *);
public:
	virtual ~Rva00256E96();
};

// ?<Rva00256E96::Rva00256E96> absent-from-retail
Rva00256E96::Rva00256E96(EmitVtableTag *)
{
}

class Rva0025E4CD
{
public:
	Rva0025E4CD(EmitVtableTag *);
public:
	virtual ~Rva0025E4CD();
};

// ?<Rva0025E4CD::Rva0025E4CD> absent-from-retail
Rva0025E4CD::Rva0025E4CD(EmitVtableTag *)
{
}

class Rva0026E7EA
{
public:
	Rva0026E7EA(EmitVtableTag *);
public:
	virtual ~Rva0026E7EA();
};

// ?<Rva0026E7EA::Rva0026E7EA> absent-from-retail
Rva0026E7EA::Rva0026E7EA(EmitVtableTag *)
{
}

class Rva0026F445
{
public:
	Rva0026F445(EmitVtableTag *);
public:
	virtual ~Rva0026F445();
};

// ?<Rva0026F445::Rva0026F445> absent-from-retail
Rva0026F445::Rva0026F445(EmitVtableTag *)
{
}

class Rva002793F0Base0
{
public:
	virtual ~Rva002793F0Base0();
private:
	char m_unmodelled_04[0x60 - 0x04];
};

// Secondary base at +0x60: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x60) at 0x0027966F in its vtable is target evidence for it.
class Rva002793F0Base60
{
public:
	virtual ~Rva002793F0Base60();
};
class Rva002793F0 : public Rva002793F0Base0, public Rva002793F0Base60
{
public:
	Rva002793F0(EmitVtableTag *);
public:
	virtual ~Rva002793F0();
};

// ?<Rva002793F0::Rva002793F0> absent-from-retail
Rva002793F0::Rva002793F0(EmitVtableTag *)
{
}

class Rva00285BECBase0
{
public:
	virtual ~Rva00285BECBase0();
};

// Secondary base at +0x4: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x4) at 0x00285BE4 in its vtable is target evidence for it.
class Rva00285BECBase4
{
public:
	virtual ~Rva00285BECBase4();
};
class Rva00285BEC : public Rva00285BECBase0, public Rva00285BECBase4
{
public:
	Rva00285BEC(EmitVtableTag *);
public:
	virtual ~Rva00285BEC();
};

// ?<Rva00285BEC::Rva00285BEC> absent-from-retail
Rva00285BEC::Rva00285BEC(EmitVtableTag *)
{
}

class Rva00286F8FBase0
{
public:
	virtual ~Rva00286F8FBase0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x00286F87 in its vtable is target evidence for it.
class Rva00286F8FBaseC
{
public:
	virtual ~Rva00286F8FBaseC();
};
class Rva00286F8F : public Rva00286F8FBase0, public Rva00286F8FBaseC
{
public:
	Rva00286F8F(EmitVtableTag *);
public:
	virtual ~Rva00286F8F();
};

// ?<Rva00286F8F::Rva00286F8F> absent-from-retail
Rva00286F8F::Rva00286F8F(EmitVtableTag *)
{
}

class Rva002894A2
{
public:
	Rva002894A2(EmitVtableTag *);
public:
	virtual ~Rva002894A2();
};

// ?<Rva002894A2::Rva002894A2> absent-from-retail
Rva002894A2::Rva002894A2(EmitVtableTag *)
{
}

class Rva00299CE4Base0
{
public:
	virtual ~Rva00299CE4Base0();
private:
	char m_unmodelled_04[0x60 - 0x04];
};

// Secondary base at +0x60: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x60) in its vtable is target evidence for it.
class Rva00299CE4Base60
{
public:
	virtual ~Rva00299CE4Base60();
};
class Rva00299CE4 : public Rva00299CE4Base0, public Rva00299CE4Base60
{
public:
	Rva00299CE4(EmitVtableTag *);
public:
	virtual ~Rva00299CE4();
};

// ?<Rva00299CE4::Rva00299CE4> absent-from-retail
Rva00299CE4::Rva00299CE4(EmitVtableTag *)
{
}

class Rva002A5B30Base0
{
public:
	virtual ~Rva002A5B30Base0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x002A5EDE in its vtable is target evidence for it.
class Rva002A5B30BaseC
{
public:
	virtual ~Rva002A5B30BaseC();
};
class Rva002A5B30 : public Rva002A5B30Base0, public Rva002A5B30BaseC
{
public:
	Rva002A5B30(EmitVtableTag *);
public:
	virtual ~Rva002A5B30();
};

// ?<Rva002A5B30::Rva002A5B30> absent-from-retail
Rva002A5B30::Rva002A5B30(EmitVtableTag *)
{
}

class Rva002A921BBase0
{
public:
	virtual ~Rva002A921BBase0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x002A92EA in its vtable is target evidence for it.
class Rva002A921BBaseC
{
public:
	virtual ~Rva002A921BBaseC();
};
class Rva002A921B : public Rva002A921BBase0, public Rva002A921BBaseC
{
public:
	Rva002A921B(EmitVtableTag *);
public:
	virtual ~Rva002A921B();
};

// ?<Rva002A921B::Rva002A921B> absent-from-retail
Rva002A921B::Rva002A921B(EmitVtableTag *)
{
}

class Rva002B964FBase0
{
public:
	virtual ~Rva002B964FBase0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) in its vtable is target evidence for it.
class Rva002B964FBaseC
{
public:
	virtual ~Rva002B964FBaseC();
};
class Rva002B964F : public Rva002B964FBase0, public Rva002B964FBaseC
{
public:
	Rva002B964F(EmitVtableTag *);
public:
	virtual ~Rva002B964F();
};

// ?<Rva002B964F::Rva002B964F> absent-from-retail
Rva002B964F::Rva002B964F(EmitVtableTag *)
{
}

class Rva002BFB2D
{
public:
	Rva002BFB2D(EmitVtableTag *);
public:
	virtual ~Rva002BFB2D();
};

// ?<Rva002BFB2D::Rva002BFB2D> absent-from-retail
Rva002BFB2D::Rva002BFB2D(EmitVtableTag *)
{
}

class Rva002C5398
{
public:
	Rva002C5398(EmitVtableTag *);
public:
	virtual ~Rva002C5398();
};

// ?<Rva002C5398::Rva002C5398> absent-from-retail
Rva002C5398::Rva002C5398(EmitVtableTag *)
{
}

// Target destructor proves cleanup on this, then free of the vector's first
// pointer and an external base destructor. Original owner identity is unknown.
extern "C" void __cdecl free(void *);
struct Rva002C6354Buffer
{
    void *begin, *end, *capacity;
    ~Rva002C6354Buffer() { if (begin != 0) free(begin); }
};
class Rva00506B1B
{
public:
    virtual ~Rva00506B1B();
private:
    char m_unmodelled04[4];
};
class Rva002C61AF { public: void rva002C61AF(); };

class Rva002C6354 : public Rva00506B1B
{
public:
	Rva002C6354(EmitVtableTag *);
public:
	virtual ~Rva002C6354();
private:
    char m_unmodelled[24];
    Rva002C6354Buffer m_buffer;
};

// ?<Rva002C6354::Rva002C6354> absent-from-retail
Rva002C6354::Rva002C6354(EmitVtableTag *)
{
}

class Rva002CCD56
{
public:
	Rva002CCD56(EmitVtableTag *);
public:
	virtual ~Rva002CCD56();
};

// ?<Rva002CCD56::Rva002CCD56> absent-from-retail
Rva002CCD56::Rva002CCD56(EmitVtableTag *)
{
}

class Rva002CD4A6
{
public:
	Rva002CD4A6(EmitVtableTag *);
public:
	virtual ~Rva002CD4A6();
};

// ?<Rva002CD4A6::Rva002CD4A6> absent-from-retail
Rva002CD4A6::Rva002CD4A6(EmitVtableTag *)
{
}

class Rva002D0588
{
public:
	Rva002D0588(EmitVtableTag *);
public:
	virtual ~Rva002D0588();
};

// ?<Rva002D0588::Rva002D0588> absent-from-retail
Rva002D0588::Rva002D0588(EmitVtableTag *)
{
}

class Rva005248D0
{
public:
	Rva005248D0(EmitVtableTag *);
public:
	virtual ~Rva005248D0();
};

// ?<Rva005248D0::Rva005248D0> absent-from-retail
Rva005248D0::Rva005248D0(EmitVtableTag *)
{
}

extern "C" const void *const vtbl_00C02A84[];
#pragma comment(linker, "/alternatename:_vtbl_00C02A84=??_7Rva002D3556@@6B@")

class __declspec(novtable) Rva002D5333Base
{
public:
	virtual __forceinline ~Rva002D5333Base() { *(const void **)this = vtbl_00C02A84; }

protected:
	unsigned char m_pad04[4];
	void *m_ptr08;
	unsigned char m_pad0C[4];
};

template <class T> class StringBase
{
public:
	~StringBase();

private:
	void *m_data;
};

#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
#pragma comment(linker, "/alternatename:?TheRva00222A8BTarget@@3PAVRva00222A8BTarget@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")
extern const char g_00C02CF8[];
int __cdecl Rva002D4531Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const int &arg);

struct Rva002D5333ObjectRef
{
	unsigned char m_pad00[0x5C];
	void *m_owner;
};

class Rva002D5333 : public Rva002D5333Base
{
public:
	Rva002D5333(EmitVtableTag *);
	virtual ~Rva002D5333();
	void rva002D4BA5();

private:
	StringBase<char> m_str10;
	unsigned char m_flag14;
	bool m_done15;
	int m_arg18;
};

// ?<Rva002D5333::Rva002D5333> absent-from-retail
Rva002D5333::Rva002D5333(EmitVtableTag *)
{
}

void Rva002D5333::rva002D4BA5()
{
	if (m_done15)
		return;

	if (m_flag14 != 0)
	{
		if (m_ptr08 != 0)
		{
			Rva002D4531Invoke(TheRva00222A8BTarget,
				((Rva002D5333ObjectRef *)m_ptr08)->m_owner,
				g_00C02CF8,
				m_arg18);
		}
	}

	m_done15 = true;
}

Rva002D5333::~Rva002D5333()
{
	if (!m_done15)
		rva002D4BA5();
}

Rva002C6354::~Rva002C6354()
{
    ((Rva002C61AF *)this)->rva002C61AF();
}
