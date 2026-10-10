// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0004CBC0@RvaSmartPtr12@@QAEXXZ, retail 0x0004CBC0, 55 bytes.
// Intrusive-list unlink spelt from Open-BFME-1
// (Code/GameEngine/Source/GameClient/System/ParticleSystemHandleListClear.cpp,
// whose 111B list-clear row documents the idiom): unlinks the handle from the
// ParticleSystem handle chain. BFME2 deltas (retail-measured): no outer
// m_system guard, and the chain head lives at ParticleSystem +0x9C/+0xA0
// (first/last).
//
// The handle DESTRUCTOR is not this body: it is the inline null test around
// it, `if (m_system) unlink()`, whose one out-of-line copy is the 11B
// cmp [ecx],0 / je / jmp 0x0004CBC0 at 0x002115C5 (90 jumps reach it,
// unwind funclets included). W3DTruckDraw's dtor 0x000CDE73 inlines that test
// three times around call 0x0004CBC0. So the unlink keeps the address-derived
// RvaSmartPtr12 spelling and the dtor is defined inline below.

class ParticleSystem;

// The 12-byte handle record (system, previous, next).
class RvaSmartPtr12
{
public:
	void rva0004CBC0();
	ParticleSystem *m_system;
	RvaSmartPtr12 *m_previous;
	RvaSmartPtr12 *m_next;
};

class ParticleSystem
{
public:
	unsigned char m_pad[0x9C];
	RvaSmartPtr12 *m_firstHandle;	// +0x9C
	RvaSmartPtr12 *m_lastHandle;	// +0xA0
};

struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle() throw() { if (m_system) reinterpret_cast<RvaSmartPtr12 *>(this)->rva0004CBC0(); }
	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

// ?rva002115C5@Rva002115C5@@QAEXXZ, RVA 0x002115C5, 11B: the inline handle
// dtor's out-of-line copy (cmp [ecx],0 / je / jmp 0x0004CBC0; the tail call
// with this already in ecx emits jmp, no reload). 40+ callers; unblocks
// 0x00211ED9/0x00212AD6. Owner unknown so honest address-derived struct (no
// vtable) holding the real handle first.
struct Rva002115C5 {
	BfmeParticleSystemHandle m_handle;
	void rva002115C5();
};

void Rva002115C5::rva002115C5()
{
	if (m_handle.m_system)
		reinterpret_cast<RvaSmartPtr12 *>(&m_handle)->rva0004CBC0();
}

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
        reinterpret_cast<RvaSmartPtr12 *>(&handle)->rva0004CBC0();
        handle.m_system=0;
    }
}

// Native 1FD016..1FD022 is a complete RET0 leaf after the prior RET8 at
// 1FD013, before independently rowed 1FD022. Its first word is returned
// when non-null; otherwise it tail-calls the actual null ParticleSystem
// factory 1FCBD7. BF1 9cbfb551fe20 LivingWorldManagerParticleSystem.cpp
// operator-> is a semantic source guide. The original handle identity
// and method name are not independently established for this address.
ParticleSystem *Make001FCBD7();
struct Rva001FD016HandlePrefix
{
    ParticleSystem *system;
    ParticleSystem *getOrNullSystem() const;
};
ParticleSystem *Rva001FD016HandlePrefix::getOrNullSystem() const
{
    return system ? system : Make001FCBD7();
}

// inline (a select-any copy): for a plain definition in this unit cl assumes
// the unlink preserves ecx in the callers above, where retail keeps the
// receiver in esi across the call.
inline void RvaSmartPtr12::rva0004CBC0()
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
