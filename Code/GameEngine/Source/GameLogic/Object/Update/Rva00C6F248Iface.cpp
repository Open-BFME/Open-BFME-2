// cl: /O1 /DNDEBUG /MD
//
// ??0Rva00C6F248Iface@@QAE@XZ, retail 0x004A184C, 9 bytes. Outlined default
// ctor of the 4-byte second-base interface whose vtable lives at 0xC6F248
// (all eight slots read the shared 0x43B810 implementation). Retail installs
// that vtable at +0 of this 9-byte body, at +0 of the 0x57BCE2-body class,
// and at +0x20 of larger multi-base updates (0x44EF7E family and the
// BattlePlanUpdate ctor 0x497ED0, which overwrites the slot with its own
// vtable right after the base call). The address-derived name is honest:
// the interface behind the vtable is not identified beyond its slot.

class Rva00C6F248Iface
{
public:
	Rva00C6F248Iface();
	virtual void m_iface() = 0;
};

// ??0Rva00C6F248Iface@@QAE@XZ @0x4A184C
Rva00C6F248Iface::Rva00C6F248Iface()
{
}
