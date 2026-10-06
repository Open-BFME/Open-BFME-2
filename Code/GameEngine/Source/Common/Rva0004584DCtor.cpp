// cl: /MD /DNDEBUG
//
// ??0Rva0004584D@@QAE@ABVBfmeFixedStorage0004543D@@0@Z @0x0004584D 43B
// Two-storage holder ctor: vtable 0x00BC2908 (3 slots) at +0, int zero at +4
// via and, two 28B FixedStorage members at +8/+0x24 through the rowed copy
// at 0x0004543D, ret 8. Callers 0x0004AFC6 and 0x0010CE97 share one stack
// slot: they push 0x00DFEFA4 plus two ints for the BitSet ctor at 0x00045411
// (ret 8 leaves DFEFA4), then push eax (the BitSet at ebp-0x68/-0xD0) and call
// here; both params feed the same FixedStorage copy, sizes 28B each. Sibling
// tail at 0x004CCE67 stores the same vtable. Honest Rva class; virtual dummy
// carries the vptr without emitting a deleting dtor.
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();

private:
	unsigned char m_bytes[28];
};

class Rva0004584D
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	virtual void dummy();

private:
	int m_04;
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// ??0Rva0004584D@@QAE@ABVBfmeFixedStorage0004543D@@0@Z
Rva0004584D::Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b)
	: m_04(0)
	, m_08(a)
	, m_24(b)
{
}

// One more constructor of this shape, each installing its own vtable (the only
// differing operand): 0x002FDF47 (VA 0xc071d8). The virtual is declared inline and
// empty so the vtable the compiler emits resolves in this unit. Owners keep
// their addresses.

class Rva002FDF47
{
public:
	Rva002FDF47(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	virtual void dummy() {}
	bool rva00261102(class Object *obj);
private:
	int m_04;
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

Rva002FDF47::Rva002FDF47(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b)
	: m_04(0)
	, m_08(a)
	, m_24(b)
{
}

template<int N>
class BitFlags
{
public:
	unsigned int m_bits[(N + 31) / 32];
};

class Thing
{
public:
	bool isAnyKindOf(const BitFlags<69> &mask) const;
};

class Object : public Thing
{
};

// ?rva00261102@Rva002FDF47@@QAE_NPAVObject@@@Z @0x00261102 46B slot 1 of
// vtable VA 0xc071d8. First mask at +0x24, second at +0x08 via FixedStorage
// reinterpreted as BitFlags<69>. Callers none rowed. Donor is the same TU
// shape with two 28B storages. Identity beyond the slot and masks is unproven
// so the method name stays honest address-derived.

bool Rva002FDF47::rva00261102(Object *obj)
{
	const BitFlags<69> &mask1 = *(const BitFlags<69> *)&m_24;
	if (obj->isAnyKindOf(mask1))
		return true;
	const BitFlags<69> &mask2 = *(const BitFlags<69> *)&m_08;
	return !obj->isAnyKindOf(mask2);
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?dummy@Rva0004584D@@UAEXXZ=?rva00395A19@Rva00395A19@@QAEPAXI@Z")
