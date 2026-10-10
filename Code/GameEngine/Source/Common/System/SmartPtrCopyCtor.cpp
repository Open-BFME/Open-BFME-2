// cl: /DNDEBUG /MD
//
// ??0RvaSmartPtr12@@QAE@ABV0@@Z, retail 0x0004CC19 (36 bytes).
// ??4RvaSmartPtr12@@QAEAAV0@ABV0@@Z, retail 0x0004CC3D (44 bytes).
//
// Frameless copy over the 12-byte reference-counted smart pointer at +0x15C
// of Rva003FDA90SmartField (see SmartPtrRvoGetter.cpp, which carries the
// rowed RVO getter): copy the raw pointer, attach through the intrusive-list
// helper at 0x4CB9A when non-null, otherwise zero the +4/+8 pads. Lives in
// its own shard because the getter TU builds with /Oy- (framed) while this
// body is frameless.
// Assignment over the same 12-byte handle: self-check, conditional release
// via the rowed BfmeParticleSystemHandle dtor at 0x4CBC0, raw copy, then
// conditional attach via 0x4CB9A. Callers include 0x4CCE9 0x4D064 0xC7DC2.

struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle();
	void *m_system;
	void *m_prev;
	void *m_next;
};

class RvaSmartPtr12
{
	public: void rva0004CBC0(); // 0x0004CBC0, the unlink the inline dtor null test calls
private:

public:
	RvaSmartPtr12(void *ptr);
	RvaSmartPtr12(const RvaSmartPtr12 &that);
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &that);
	void attach();

private:
	void *m_ptr; // +0x0
	int m_pad04; // +0x4
	int m_pad08; // +0x8
};

RvaSmartPtr12::RvaSmartPtr12(void *ptr)
{
	m_ptr = ptr;
	if (m_ptr != 0)
		attach();
	else
	{
		m_pad08 = 0;
		m_pad04 = 0;
	}
}

RvaSmartPtr12::RvaSmartPtr12(const RvaSmartPtr12 &that)
{
	m_ptr = that.m_ptr;
	if (m_ptr != 0)
		attach();
	else
	{
		m_pad08 = 0;
		m_pad04 = 0;
	}
}

RvaSmartPtr12 &RvaSmartPtr12::operator=(const RvaSmartPtr12 &that)
{
	if (this != &that)
	{
		if (m_ptr != 0)
			reinterpret_cast<RvaSmartPtr12 *>(this)->rva0004CBC0();
		m_ptr = that.m_ptr;
		if (m_ptr != 0)
			attach();
	}
	return *this;
}
