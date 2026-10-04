// cl: /O1 /DNDEBUG /MD
//
// Nine broadcast methods of the registry the Rva0056AC26 destructor reaches
// through its +0x10 owner (0x003F88A7 is the call it makes there): each hands
// a member-function pointer to a listener virtual, the registry itself and
// the one argument to the listener list at +4 (forEach 0x003F86D4). The
// member-function pointers are MSVC's generic vcall thunks ??_9@$B<slot>AE,
// pinned at the ICF-folded retail copies the bodies push.
//
//   body        listener slot   direct caller
//   0x003F87FF  +0x04           0x003F8D6B
//   0x003F8814  +0x08           0x003F8938
//   0x003F8829  +0x0C           0x003F89FF
//   0x003F883E  +0x10           0x003F8AA4
//   0x003F8853  +0x14           0x003F8B15
//   0x003F8868  +0x18           0x003F8BEC
//   0x003F887D  +0x1C           0x003F8C74
//   0x003F8892  +0x20           0x003F8B8F
//   0x003F88A7  +0x24           0x0056AC4F (Rva0056AC26 destructor)
//
// Owner, listener and list identities are not recovered (address names);
// the argument is typed as the Rva0056AC26 entry the 0x003F88A7 call passes
// (inferred for the other eight).

class Rva0056AC26;
class Rva0056AC26Owner;

class Rva003F87FFListener
{
public:
	virtual void notify00(Rva0056AC26Owner *owner, Rva0056AC26 *entry);
	virtual void notify04(Rva0056AC26Owner *owner, Rva0056AC26 *entry);
	virtual void notify08(Rva0056AC26Owner *owner, Rva0056AC26 *entry);
	virtual void notify0C(Rva0056AC26Owner *owner, Rva0056AC26 *entry);
	virtual void notify10(Rva0056AC26Owner *owner, Rva0056AC26 *entry);
	virtual void notify14(Rva0056AC26Owner *owner, Rva0056AC26 *entry);
	virtual void notify18(Rva0056AC26Owner *owner, Rva0056AC26 *entry);
	virtual void notify1C(Rva0056AC26Owner *owner, Rva0056AC26 *entry);
	virtual void notify20(Rva0056AC26Owner *owner, Rva0056AC26 *entry);
	virtual void notify24(Rva0056AC26Owner *owner, Rva0056AC26 *entry);
};

typedef void (Rva003F87FFListener::*Rva003F87FFNotify)(Rva0056AC26Owner *, Rva0056AC26 *);

class Rva003F86D4List
{
public:
	void forEach(Rva003F87FFNotify notify, Rva0056AC26Owner *owner, Rva0056AC26 *entry);
};

class Rva0056AC26Owner
{
public:
	void rva003F87FF(Rva0056AC26 *entry);
	void rva003F8814(Rva0056AC26 *entry);
	void rva003F8829(Rva0056AC26 *entry);
	void rva003F883E(Rva0056AC26 *entry);
	void rva003F8853(Rva0056AC26 *entry);
	void rva003F8868(Rva0056AC26 *entry);
	void rva003F887D(Rva0056AC26 *entry);
	void rva003F8892(Rva0056AC26 *entry);
	void rva003F88A7(Rva0056AC26 *entry);

private:
	char m_unmodelled_00[4];
	Rva003F86D4List m_listeners;		// +0x04
};

void Rva0056AC26Owner::rva003F87FF(Rva0056AC26 *entry)
{
	m_listeners.forEach(&Rva003F87FFListener::notify04, this, entry);
}

void Rva0056AC26Owner::rva003F8814(Rva0056AC26 *entry)
{
	m_listeners.forEach(&Rva003F87FFListener::notify08, this, entry);
}

void Rva0056AC26Owner::rva003F8829(Rva0056AC26 *entry)
{
	m_listeners.forEach(&Rva003F87FFListener::notify0C, this, entry);
}

void Rva0056AC26Owner::rva003F883E(Rva0056AC26 *entry)
{
	m_listeners.forEach(&Rva003F87FFListener::notify10, this, entry);
}

void Rva0056AC26Owner::rva003F8853(Rva0056AC26 *entry)
{
	m_listeners.forEach(&Rva003F87FFListener::notify14, this, entry);
}

void Rva0056AC26Owner::rva003F8868(Rva0056AC26 *entry)
{
	m_listeners.forEach(&Rva003F87FFListener::notify18, this, entry);
}

void Rva0056AC26Owner::rva003F887D(Rva0056AC26 *entry)
{
	m_listeners.forEach(&Rva003F87FFListener::notify1C, this, entry);
}

void Rva0056AC26Owner::rva003F8892(Rva0056AC26 *entry)
{
	m_listeners.forEach(&Rva003F87FFListener::notify20, this, entry);
}

void Rva0056AC26Owner::rva003F88A7(Rva0056AC26 *entry)
{
	m_listeners.forEach(&Rva003F87FFListener::notify24, this, entry);
}
