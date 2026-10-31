// cl: /O1 /MD
//
// ??1Rva0020453CHolderBase@@QAE@XZ @0x00204C16 11B: non-virtual dtor storing
// vtable 0x00BE39F4 then tail-jumping to release 0x0020453C (pin).
// Evidence: deleting-dtor caller 0x00204D6B (push esi call ??1 test [esp+8],1
// call operator delete ret 4) calls this body; pin for release describes the
// inline dtor storing vtable 0xBE39F4 right before the release call; class
// layout follows ScriptEngine_dtor.cpp HolderBase.

class Rva0020453CHolderBase
{
public:
	~Rva0020453CHolderBase() { release(); }
	virtual void holderSlot0();
	void release();

protected:
	int m_systemID;		// +0x04
	bool m_flag;		// +0x08
};

extern const void *const g_00BE39F4[];

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeRva0020453CHolderBaseInlineAnchor@@YAXPAVRva0020453CHolderBase@@@Z absent-from-retail
void _bfmeRva0020453CHolderBaseInlineAnchor(Rva0020453CHolderBase *p)
{
    p->Rva0020453CHolderBase::~Rva0020453CHolderBase();
}
#pragma inline_depth()

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?holderSlot0@Rva0020453CHolderBase@@UAEXXZ=?rva00204316@Rva00204316@@QAEXPBDABVParticleSystemTemplate@FXParticleSystem@@@Z")
