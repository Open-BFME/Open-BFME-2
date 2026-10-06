// cl: /O1 /EHs /MD
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

void Rva002130CF::rva002130CF(Rva002130CFOwner *owner)
{
	Rva00210D1D::rva00210D1D(owner);
	owner->m_listeners.append(this);
}
