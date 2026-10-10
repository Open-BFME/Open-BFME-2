// cl: /DNDEBUG /MD
//
// ?destroyDelete@Rva0004CCFF@@QAEPAXI@Z, retail 0x0004CCFF (33 bytes).
//
// Conditional destroy-plus-delete over the 12-byte handle: when the first
// dword is non-zero release via the rowed BfmeParticleSystemHandle dtor at
// 0x4CBC0, when flags&1 free via the rowed operator delete at 0x2FD60,
// return this. Callers at 0x4CD43 0x4CD54 0x1F63DE 0x1F65C5. Same flags as
// SmartPtrCopyCtor; honest RVA class (identity unproven).

// 0x0004CBC0 is the handle unlink (row ?rva0004CBC0@RvaSmartPtr12@@QAEXXZ); the dtor is the inline null test around it.
class RvaSmartPtr12 { public: void rva0004CBC0(); };
struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle();
	void *m_system;
	void *m_prev;
	void *m_next;
};

class Rva0004CCFF
{
public:
	void *destroyDelete(unsigned int flags);

private:
	void *m_ptr; // +0x0
	int m_pad04; // +0x4
	int m_pad08; // +0x8
};

void *Rva0004CCFF::destroyDelete(unsigned int flags)
{
	if (m_ptr != 0)
		reinterpret_cast<RvaSmartPtr12 *>(this)->rva0004CBC0();
	if (flags & 1)
		operator delete(this);
	return this;
}
