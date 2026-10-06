// cl: /O2 /MD
// Rva00709C10Cluster.cpp
//
// 0x00709D80 (113 bytes): virtual slot 13 (offset 0x34) of vtable 0x008EE8C8 and
// of three further vtables that inherit the same prefix (0x008EE93C, 0x008EE9A4,
// 0x008EEAEC) -- the vtable the rowed
// ?rva00709E00@Rva00709B80@@QAEXXZ (Rva00709B80Slot11.cpp) is itself slot 11 of.
// The receiver is the same Apt array/GC-mark owner class, which Rva00709B80Slot11.cpp
// proves carries three apt-value pointers at +0x20, +0x24 and +0x28; the order the
// body walks them in is that file's +0x28, +0x20, +0x24.
//
// Identity is carried by the retail body's own callees, not by the class name:
//   0x0070DFD0  link thunk -> ?rva006DCC00@Rva006D6360@@QAEXXZ @0x006DCC00 (rowed,
//               Rva006DCC00Forwarder.cpp): the Rva006D6360 slot-0x34 native-hash mark,
//               the same base forwarder the rowed array GC-mark body
//               ?rva006D94A0@BfmeAptValue006DCD20@@QAEXXZ (0x006D94A0) opens with.
//   0x006DBB40  ?get@Rva006DBB40ShrAndField@@QBE_NXZ (pinned, AptShrAndFieldBoolGetters.cpp):
//               bit 1 of the flag dword at +4, the GC-mark test.
//   0x006DBC50  ?setGCMark@AptValue@@QAEX_N@Z (rowed, AptValueDonorBitsBFME2.cpp).
//
// The looped sibling at 0x006D94A0 re-reads its element four times per iteration
// through At 0x006D8A50; this body has no index and no At call, so it reads each
// of its three members once into ecx and tests that. That difference is what makes
// it a separate body rather than an ICF alias of the rowed one.

// The Rva006D6360 base forwarder 0x006DCC00, whose own layout (Rva006DCC00Forwarder.cpp)
// is two dwords then an AptNativeHash beginning at +0x08. Only the forwarder call
// and the base's eight-byte extent reach this body; the member names are not used.
// Retail reaches the forwarder through the rowed link thunk 0x0070DFD0
// (?rva0070DFD0@Rva0070DFD0@@QAEXXZ in VslotSmallBodiesAJ.cpp), so call it by that
// row name (cast this; same address, thunk tail-jmps to the forwarder).
class Rva0070DFD0
{
public:
	void rva0070DFD0();
};
class Rva006D6360
{
public:
	void rva006DCC00();

private:
	int m_a;
	int m_b;
};

// The value-object GC views shared with Rva006D94A0AptCluster.cpp: the shr-and-field
// flag word at +4, and the AptValue vtable whose slot 13 (0x34) is the mark dispatch.
class Rva006DBB40ShrAndField
{
public:
	bool get() const;
};

class AptValue
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual void unused3();
	virtual void unused4();
	virtual void unused5();
	virtual void unused6();
	virtual void unused7();
	virtual void unused8();
	virtual void unused9();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	void setGCMark(bool value);
};

// The three apt-value members the Rva00709B80 layout places at +0x20, +0x24 and
// +0x28 (Rva00709B80Slot11.cpp). The eight bytes of Rva006D6360 base sit below
// them, so the derived pad runs from +0x08 to +0x20.
class Rva00709B80 : public Rva006D6360
{
public:
	void rva00709D80();

private:
	char m_pad08[0x18];
	AptValue *m_20;
	AptValue *m_24;
	AptValue *m_28;
};

// Rva00709B80::rva00709D80 @0x00709D80 (113 bytes). Slot-0x34 GC-mark traversal
// for a fixed three-member owner: mark the base native hash, then for each of
// +0x28, +0x20 and +0x24 in that order, if the member is present and its GC mark
// is clear, set the mark and recurse through the same slot. Each member is
// reloaded for the mark test and again for the set/recurse pair, matching
// retail's separate loads; the last block tail-jumps rather than falling through
// because its reload leaves `this` dead.
// Evidence: vtable slot 0x34 at 0x008EE8FC (plus 0x008EE96C, 0x008EE9D4,
// 0x008EEB1C); forwarder thunk 0x0070DFD0 -> 0x006DCC00; callees get 0x006DBB40
// and setGCMark 0x006DBC50; layout from Rva00709B80Slot11.cpp.
void Rva00709B80::rva00709D80()
{
	((Rva0070DFD0 *)this)->rva0070DFD0();

	if (m_28)
	{
		if (!((const Rva006DBB40ShrAndField *)m_28)->get())
		{
			((AptValue *)m_28)->setGCMark(true);
			((AptValue *)m_28)->unused13();
		}
	}

	if (m_20)
	{
		if (!((const Rva006DBB40ShrAndField *)m_20)->get())
		{
			((AptValue *)m_20)->setGCMark(true);
			((AptValue *)m_20)->unused13();
		}
	}

	if (m_24)
	{
		if (!((const Rva006DBB40ShrAndField *)m_24)->get())
		{
			((AptValue *)m_24)->setGCMark(true);
			((AptValue *)m_24)->unused13();
		}
	}
}
