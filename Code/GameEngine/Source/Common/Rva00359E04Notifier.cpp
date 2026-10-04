// cl: /O1 /DNDEBUG /MD
//
// 0x00359E04 (15 bytes, vtable slot 0x00C153E4): hands a member-function
// pointer to listener slot +0x0C and the owner to the listener list at +4
// (forEach 0x00359BE8). The member-function pointer is MSVC's generic vcall
// thunk ??_9@$BM@AE, pinned at the ICF-folded retail copy 0x005CB265.
// Owner, listener and list identities are not recovered (address names).

class Rva00359E04Owner;

class Rva00359E04Listener
{
public:
	virtual void notify00(Rva00359E04Owner *owner);
	virtual void notify04(Rva00359E04Owner *owner);
	virtual void notify08(Rva00359E04Owner *owner);
	virtual void notify0C(Rva00359E04Owner *owner);
};

class Rva00359BE8List
{
public:
	void forEach(void (Rva00359E04Listener::*notify)(Rva00359E04Owner *), Rva00359E04Owner *owner);
};

class Rva00359E04Owner
{
public:
	void rva00359E04();

private:
	char m_unmodelled_00[4];
	Rva00359BE8List m_listeners;		// +0x04
};

void Rva00359E04Owner::rva00359E04()
{
	m_listeners.forEach(&Rva00359E04Listener::notify0C, this);
}
