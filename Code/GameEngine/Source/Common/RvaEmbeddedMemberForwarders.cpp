// cl: /O1 /DNDEBUG /MD
//
// add ecx N / jmp forwarders into a void method of an embedded member at +N,
// found by a .text byte scan of unowned starts whose jump target is a rowed
// void thiscall method (row spellings followed for the targets):
//   0x001F8203 +0x4 -> Rva001F5CF7::rva001F5CF7
//   0x001F8950 +0x8 -> Rva001F5CF7::rva001F5CF7
//   0x003F7D56 +0x1C -> Rva002BED91::clear
//   0x0050EAB9 +0x8 -> Rva000AD6F4::clear
//   0x0050EB02 +0x4 -> Rva000AD6F4::clear
//   0x0059EB5E +0x70 -> Rva0043DB47DoubleSetter::enable
//   0x00628D18 +0x30 -> Rva009F68C6PointerArray::RemoveAll
//   0x0005922D +0x1B8 -> Rva00056CF8::rva00057B74
//   0x00248D6C +0x288 -> Rva0043DB47DoubleSetter::enable
//   0x002BFC4E +0xAC -> Rva002BF75A::rva002BF7BE
// Forwarder classes are address-named; original names are unknown.

class Rva001F5CF7
{
public:
	void rva001F5CF7();
};

class Rva001F8203
{
public:
	void rva001F8203();
private:
	char m_lead[0x4];
	Rva001F5CF7 m_member;
};

void Rva001F8203::rva001F8203()
{
	m_member.rva001F5CF7();
}

class Rva001F8950
{
public:
	void rva001F8950();
private:
	char m_lead[0x8];
	Rva001F5CF7 m_member;
};

void Rva001F8950::rva001F8950()
{
	m_member.rva001F5CF7();
}

class Rva002BED91
{
public:
	void clear();
};

class Rva003F7D56
{
public:
	void rva003F7D56();
private:
	char m_lead[0x1C];
	Rva002BED91 m_member;
};

void Rva003F7D56::rva003F7D56()
{
	m_member.clear();
}

class Rva000AD6F4
{
public:
	void clear();
};

class Rva0050EAB9
{
public:
	void rva0050EAB9();
private:
	char m_lead[0x8];
	Rva000AD6F4 m_member;
};

void Rva0050EAB9::rva0050EAB9()
{
	m_member.clear();
}

class Rva0050EB02
{
public:
	void rva0050EB02();
private:
	char m_lead[0x4];
	Rva000AD6F4 m_member;
};

void Rva0050EB02::rva0050EB02()
{
	m_member.clear();
}

class Rva0043DB47DoubleSetter
{
public:
	void enable();
};

class Rva0059EB5E
{
public:
	void rva0059EB5E();
private:
	char m_lead[0x70];
	Rva0043DB47DoubleSetter m_member;
};

void Rva0059EB5E::rva0059EB5E()
{
	m_member.enable();
}

class Rva009F68C6PointerArray
{
public:
	void RemoveAll();
};

class Rva00628D18
{
public:
	void rva00628D18();
private:
	char m_lead[0x30];
	Rva009F68C6PointerArray m_member;
};

void Rva00628D18::rva00628D18()
{
	m_member.RemoveAll();
}

class Rva00056CF8
{
public:
	void rva00057B74();
};

class Rva0005922D
{
public:
	void rva0005922D();
private:
	char m_lead[0x1B8];
	Rva00056CF8 m_member;
};

void Rva0005922D::rva0005922D()
{
	m_member.rva00057B74();
}

class Rva00248D6C
{
public:
	void rva00248D6C();
private:
	char m_lead[0x288];
	Rva0043DB47DoubleSetter m_member;
};

void Rva00248D6C::rva00248D6C()
{
	m_member.enable();
}

class Rva002BF75A
{
public:
	void rva002BF7BE();
};

class Rva002BFC4E
{
public:
	void rva002BFC4E();
private:
	char m_lead[0xAC];
	Rva002BF75A m_member;
};

void Rva002BFC4E::rva002BFC4E()
{
	m_member.rva002BF7BE();
}

