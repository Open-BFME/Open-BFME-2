// cl: /O1 /MD /GX
// Address-derived visitor models: native base table C37E18 and three
// collectors C37E30/C685C8/C70F6C each have six callbacks in three pairs.
// WorldBuilder independently proves the base/derived lifetime and the
// eight-byte collector layout. Each collector replaces one even callback
// with a pointer store at +4. Original class identities remain unproven.
class Rva003FE20FBase
{
public:
	virtual void slot0(void *) {}
	virtual void slot1(void *p) { slot0(p); }
	virtual void slot2(void *) {}
	virtual void slot3(void *p) { slot2(p); }
	virtual void slot4(void *) {}
	virtual void slot5(void *p) { slot4(p); }
	~Rva003FE20FBase() {}
};
class Rva003FE20FVisitor : public Rva003FE20FBase
{
public:
	void *value;
	virtual void slot4(void *p) { value = p; }
};
class Rva003FE20FInput
{
public:
	virtual void slot0();
	virtual void slot1(Rva003FE20FBase *);
};
class Rva0052B1EFVisitor : public Rva003FE20FBase
{
public:
	void *value;
	virtual void slot2(void *p) { value = p; }
};
class Rva0059E0C1Visitor : public Rva003FE20FBase
{
public:
	void *value;
	virtual void slot0(void *p) { value = p; }
};
// Existing field-reader wrappers preserved.
// Three retail lookup-or-zero wrappers (21B each). Retail shape per member:
// push [esp+4], call <lookup>, test eax, eax, pop ecx, je +4,
// mov eax, [eax+off], ret, xor eax, eax, ret.
// Reads as: p = lookup(key); return p ? p->value : 0.
// /O1 keeps the push on the stack slot and cleans it with pop ecx;
// /O2 preloads eax and uses add esp, 4. Lookup identities unproven;
// pin names are address-derived. One ledger row per wrapper.

struct Rva003FE245Holder
{
	unsigned char pad[0x38];
	unsigned value;
};

struct Rva0052B1EFHolder
{
	unsigned char pad[0xBC];
	unsigned value;
};

struct Rva0059E0C1Holder
{
	unsigned char pad[0xBC];
	unsigned value;
};

extern "C" Rva003FE245Holder *__cdecl Rva003FE245Lookup(unsigned key);
extern "C" Rva0052B1EFHolder *__cdecl Rva0052B1EFLookup(unsigned key);
extern "C" Rva0059E0C1Holder *__cdecl Rva0059E0C1Lookup(unsigned key);

unsigned Rva00318D4E(unsigned key)
{
	Rva003FE245Holder *found = Rva003FE245Lookup(key);
	return found ? found->value : 0;
}

unsigned Rva0052B225(unsigned key)
{
	Rva0052B1EFHolder *found = Rva0052B1EFLookup(key);
	return found ? found->value : 0;
}

unsigned Rva0059E0F7(unsigned key)
{
	Rva0059E0C1Holder *found = Rva0059E0C1Lookup(key);
	return found ? found->value : 0;
}

void *Rva003FE20FGet(void *input)
{
	Rva003FE20FVisitor v;
	v.value = 0;
	static_cast<Rva003FE20FInput *>(input)->slot1(&v);
	return v.value;
}
struct Rva003FE245Result
{
	char pad[0xC4];
	Rva003FE245Holder *value;
};
extern "C" Rva003FE245Holder *Rva003FE245Lookup(unsigned key)
{
	Rva003FE245Result *p = static_cast<Rva003FE245Result *>(Rva003FE20FGet(reinterpret_cast<void *>(key)));
	return p ? p->value : 0;
}
extern "C" Rva0052B1EFHolder *Rva0052B1EFLookup(unsigned key)
{
	Rva0052B1EFVisitor v;
	v.value = 0;
	reinterpret_cast<Rva003FE20FInput *>(key)->slot1(&v);
	return static_cast<Rva0052B1EFHolder *>(v.value);
}
extern "C" Rva0059E0C1Holder *Rva0059E0C1Lookup(unsigned key)
{
	Rva0059E0C1Visitor v;
	v.value = 0;
	reinterpret_cast<Rva003FE20FInput *>(key)->slot1(&v);
	return static_cast<Rva0059E0C1Holder *>(v.value);
}
