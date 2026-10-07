// cl: /O1 /DNDEBUG /MD /EHsc
// ??1BfmeParticleSystemHandle@@QAE@XZ, retail 0x0004CBC0, 55 bytes.
// Intrusive-list unlink spelt from Open-BFME-1
// (Code/GameEngine/Source/GameClient/System/ParticleSystemHandleListClear.cpp,
// whose 111B list-clear row documents the idiom): destroying the handle unlinks
// it from the ParticleSystem handle chain. BFME2 deltas (retail-measured): no
// outer m_system guard, and the chain head lives at ParticleSystem
// +0x9C/+0xA0 (first/last). Pin pre-existed; row joins it here.

class ParticleSystem;

struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle();
	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

class ParticleSystem
{
public:
	unsigned char m_pad[0x9C];
	BfmeParticleSystemHandle *m_firstHandle;	// +0x9C
	BfmeParticleSystemHandle *m_lastHandle;		// +0xA0
};

inline BfmeParticleSystemHandle::~BfmeParticleSystemHandle()
{
	if (m_previous)
		m_previous->m_next = m_next;
	else
		m_system->m_firstHandle = m_next;
	if (m_next)
		m_next->m_previous = m_previous;
	else
		m_system->m_lastHandle = m_previous;
	m_previous = 0;
	m_next = 0;
}

// ?rva002115C5@Rva002115C5@@QAEXXZ, RVA 0x002115C5, 11B. Unlock lane:
// conditionally destroys the handle at +0 in place through rowed
// ??1BfmeParticleSystemHandle@@QAE@XZ at 0x0004CBC0 when its m_system is
// set; tail-position explicit dtor call with this already in ecx emits jmp,
// no reload. 40+ callers; unblocks 0x00211ED9/0x00212AD6. Owner unknown so
// honest address-derived struct (no vtable) holding the real handle first.
struct Rva002115C5 {
	BfmeParticleSystemHandle m_handle;
	void rva002115C5();
};

void Rva002115C5::rva002115C5()
{
	if (m_handle.m_system)
		m_handle.~BfmeParticleSystemHandle();
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeBfmeParticleSystemHandleInlineAnchor@@YAXPAVBfmeParticleSystemHandle@@@Z absent-from-retail
void _bfmeBfmeParticleSystemHandleInlineAnchor(BfmeParticleSystemHandle *p)
{
    p->BfmeParticleSystemHandle::~BfmeParticleSystemHandle();
}
#pragma inline_depth()

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?rva0004CBC0@RvaSmartPtr12@@QAEXXZ=??1BfmeParticleSystemHandle@@QAE@XZ")

// Target985D2..985E4 is a complete18B RET leaf. It tests the handle's
// system word, calls the verified55B destructor4CBC0 with the unchanged
// receiver, then clears that word. The already established handle layout
// supplies the intrusive links consumed by the destructor. This wrapper's
// original identity and enclosing allocation remain unknown.
struct Rva000985D2HandlePrefix {
    BfmeParticleSystemHandle handle;
    void unlinkAndClear();
};
void Rva000985D2HandlePrefix::unlinkAndClear() {
    if (handle.m_system) {
        handle.~BfmeParticleSystemHandle();
        handle.m_system=0;
    }
}
