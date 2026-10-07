// Five null-checked member forwards with pass-through args: mov ecx,
// [ecx+off], test ecx, ecx, je ret-N, jmp <run>, ret N. Two members take
// two dwords (ret 8), three take one (ret 4); the tail-jumped run consumes
// them (thiscall, callee-cleanup).
// 0x00271BCC (+0x450 -> 0x003626AD, void(int,int); row keeps the peer pin,
//   called on the Object +0x84 pointer),
// 0x0029B16A (+0x7F4 -> 0x004E5EBE, void(int,int)),
// 0x002A9CDE (+0x2DC -> 0x004F2ABC, void(int,int)),
// 0x002A9CF0 (+0x2DC -> 0x004F0819, void(int)),
// 0x002A9DEC (+0x2DC -> 0x004F2C14, void(int); row keeps the peer
//   Rva002A9BF2 pin).
// Callee/member/owner identities otherwise unproven (opaque run pins);
// new names are address-derived. One ledger row per forward.

class Rva003626ADRun
{
public:
	void run(int a, int b);
};

class Rva004E5EBERun
{
public:
	void run(int a, int b);
};

class Rva004F2ABCRun
{
public:
	void run(int a, int b);
};

class Rva004F0819Run
{
public:
	void run(int value);
};

class Rva004F2C14Run
{
public:
	void run(int value);
};

class Rva00271BCC
{
public:
	void rva00271BCC(int a, int b);

private:
	char m_pad[0x450];
	Rva003626ADRun *m_ptr;
};

class Rva0029B16AOwner
{
public:
	void fwd(int a, int b);

private:
	char m_pad[0x7F4];
	Rva004E5EBERun *m_ptr;
};

class Rva002A9CDEOwner
{
public:
	void fwd(int a, int b);

private:
	char m_pad[0x2DC];
	Rva004F2ABCRun *m_ptr;
};

class Rva002A9CF0Owner
{
public:
	void fwd(int value);

private:
	char m_pad[0x2DC];
	Rva004F0819Run *m_ptr;
};

class Rva002A9BF2
{
public:
	void rva002A9DEC(int value);

private:
	char m_pad[0x2DC];
	Rva004F2C14Run *m_ptr;
};

// Rva00271BCC::rva00271BCC is defined with its retail-matched body in Code/GameEngine/Source/Common/RvaMixedMemberForwarders.cpp (0x00271BCC).

void Rva0029B16AOwner::fwd(int a, int b)
{
	Rva004E5EBERun *target = m_ptr;
	if (target)
		target->run(a, b);
}

void Rva002A9CDEOwner::fwd(int a, int b)
{
	Rva004F2ABCRun *target = m_ptr;
	if (target)
		target->run(a, b);
}

void Rva002A9CF0Owner::fwd(int value)
{
	Rva004F0819Run *target = m_ptr;
	if (target)
		target->run(value);
}

// Rva002A9BF2::rva002A9DEC is defined with its retail-matched body in Code/GameEngine/Source/Common/RvaMixedMemberForwarders.cpp (0x002A9DEC).
