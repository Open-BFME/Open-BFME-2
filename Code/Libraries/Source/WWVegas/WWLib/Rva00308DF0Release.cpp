// cl: /MD /DNDEBUG
// ?rva00308DF0@Rva00308DF0@@QAEPAVRva00308DF0Ref@@XZ @0x00308DF0 60B.
// Releases the counted reference at +0x84 when the flag byte at +0x88 is set,
// clears the flag, then calls the unrowed member 0x00308C31 (pinned by its
// REL32 at 0x00308E1E). Returns the (now cleared) reference slot.
// Evidence: target only; identity of the owning class is unproven, so the
// names are address-derived. Refcount decrement is `dec [ecx+4]; jne`, and the
// last release is a virtual call through slot 0 with the object as `this`.
class Rva00308DF0Ref
{
public:
	virtual void rva00308DF0Free();

	int m_numRefs;
};

class Rva00308DF0
{
public:
	Rva00308DF0Ref *rva00308DF0();
	void rva00308C31();

private:
	char m_pad[0x84];
	Rva00308DF0Ref *m_ref;
	unsigned char m_flag;
};

Rva00308DF0Ref *Rva00308DF0::rva00308DF0()
{
	if (m_flag)
	{
		Rva00308DF0Ref **slot = &m_ref;
		Rva00308DF0Ref *ref = *slot;
		if (ref)
		{
			if (--ref->m_numRefs == 0)
				ref->rva00308DF0Free();
			*slot = 0;
		}
		m_flag = 0;
		rva00308C31();
	}
	return m_ref;
}
