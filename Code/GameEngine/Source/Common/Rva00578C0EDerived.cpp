// cl: /MD
//
// Opaque single-inheritance destructor tail-calling Rva00578C0E::~
// Rva00578C0E at 0x00578C0E (row in FreeMemberDeleters.cpp: null-checked
// free of its member at +0x04). The class below stores its own vtable
// (0xC6EAC0, DIR32 auto-patch) and tail-calls the base destructor; the base itself is only declared here (defined once in
// FreeMemberDeleters.cpp), because a same-TU definition would capture the
// call locally instead of at the ledger address. Owner identity is unproven
// (opaque Rva name). One ledger row per destructor, landed one commit at a
// time.

class Rva00578C0E
{
public:
	Rva00578C0E();
	virtual ~Rva00578C0E();

private:
	void *m_ptr04;
};

class Rva00578C23 : public Rva00578C0E
{
public:
	Rva00578C23();
	virtual ~Rva00578C23();
};

// ??0Rva00578C23@@QAE@XZ, retail 0x00578D10 (18B): calls the base
// constructor at 0x00578C2E (rowed as ??0Rva00578C2E; it stores vtable
// 0x00BE2B78, the one ??1Rva00578C0E restores, so it is this base's
// constructor - pinned under the base's name) then stores vtable
// 0x00C6EAC0, the one the destructor below restores.
Rva00578C23::Rva00578C23()
{
}

Rva00578C23::~Rva00578C23()
{
}
