// cl: /EHs /MD
//
// ?rva002130CF@Rva002130CF@@QAEXPAURva002130CFOwner@@@Z @0x002130CF 39B: an
// attach-style override: run the base step 0x00210D1D (unrowed, address-derived
// pin) on the owner, then append this object's Rva002BA8F1Listener base (+0x10,
// null-checked pointer conversion) to the owner's listener list at +0x7C via
// the rowed Rva005A0B4CList::append (0x005A0B4C). Caller 0x002B9612. Class and
// owner identities are not recovered.

struct Rva002BA8F1Listener
{
	int m_00;
};

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

struct Rva002130CFOwner
{
	char m_pad00[0x7C];
	Rva005A0B4CList m_listeners;
};

class Rva00210D1D
{
public:
	void rva00210D1D(Rva002130CFOwner *owner);

private:
	char m_pad00[0x10];
};

class Rva002130CF : public Rva00210D1D, public Rva002BA8F1Listener
{
public:
	void rva002130CF(Rva002130CFOwner *owner);
};

class Rva007FA6B4Target
{
	char m_storage[0x14];
public:
	Rva007FA6B4Target(Rva002130CFOwner *owner);
};

struct Rva00210D1DStateView
{
	char m_pad00[0x264];
	Rva007FA6B4Target *m_264;
};

// ?rva00210D1D@Rva00210D1D@@QAEXPAURva002130CFOwner@@@Z @ 0x00210D1D 75B.
// Target clears +0x264, allocates a 0x14-byte object and calls its
// address-derived constructor 0x003FA6B4 with the owner pointer; then stores
// the returned object pointer at +0x264. The class layout beyond this field
// remains unproven.
void Rva00210D1D::rva00210D1D(Rva002130CFOwner *owner)
{
	Rva00210D1DStateView *state = (Rva00210D1DStateView *)this;
	state->m_264 = 0;
	state->m_264 = new Rva007FA6B4Target(owner);
}

void Rva002130CF::rva002130CF(Rva002130CFOwner *owner)
{
	Rva00210D1D::rva00210D1D(owner);
	owner->m_listeners.append(this);
}
