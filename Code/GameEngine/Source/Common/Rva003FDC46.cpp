// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?rva003FDC46@Rva003FDC46@@QAEXXZ @0x003FDC46 165B: enable path twin of
// 0x003FDAEB (disable path). Holder has volatile SmartField* at +0x1C;
// two RVO gets via rowed 0x003FDA90, two rowed enables via 0x001F3852,
// four Make-or-null chases via rowed 0x001FCBD7, conditional Handle dtor
// via rowed 0x0004CBC0 through inline SmartPtr dtor (cf. W3DTruckDrawDtor).
// Evidence: callers 0x003FDD15/0x003FDB90/0x003FDCEB, same 165B size and
// flag/EH shape as 0x003FDAEB, volatile preserves dead Make chases like
// W3DTankTruckDrawTossEmitters.

class ParticleSystem;
ParticleSystem *Make001FCBD7();

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
	~RvaSmartPtr12()
	{
		BfmeParticleSystemHandle *h = (BfmeParticleSystemHandle *)this;
		if (h->m_system != 0)
			reinterpret_cast<RvaSmartPtr12 *>(h)->rva0004CBC0();
	}
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};

class Rva003FDA90SmartField
{
public:
	RvaSmartPtr12 get() const;
};

class Rva001F3852ByteOneSetter
{
public:
	void enable();
};

class Rva003FDC46
{
public:
	void rva003FDC46();
private:
	char m_pad00[0x1C];
	Rva003FDA90SmartField *volatile m_field;
};

void Rva003FDC46::rva003FDC46()
{
	if (!m_field)
		return;
	bool ok;
	{
		Rva003FDA90SmartField *f = m_field;
		if (!f)
			f = (Rva003FDA90SmartField *)Make001FCBD7();
		ok = f->get().m_ptr != 0;
	}
	if (ok)
	{
		Rva003FDA90SmartField *f2 = m_field;
		if (!f2)
			f2 = (Rva003FDA90SmartField *)Make001FCBD7();
		ParticleSystem *p;
		((Rva001F3852ByteOneSetter *)((p = (ParticleSystem *)f2->get().m_ptr) ? p : Make001FCBD7()))->enable();
	}
	{
		Rva003FDA90SmartField *f3 = m_field;
		if (!f3)
			f3 = (Rva003FDA90SmartField *)Make001FCBD7();
		((Rva001F3852ByteOneSetter *)f3)->enable();
	}
}
