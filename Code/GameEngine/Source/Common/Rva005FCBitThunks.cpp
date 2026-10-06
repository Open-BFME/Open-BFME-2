// cl: /MD
// Member chase thunks to the +0x34 bit setters (8B each):
//  ?rva005FC6F7@Rva005FC6F7@@QAEXE@Z @0x005FC6F7 -> ?setBit0@Rva005FC64AOwner@@QAEXE@Z
//  ?rva005FC70A@Rva005FC70A@@QAEXE@Z @0x005FC70A -> ?setBit1@Rva005FC66BOwner@@QAEXE@Z
//  ?rva005FC71E@Rva005FC71E@@QAEXE@Z @0x005FC71E -> ?setBit2@Rva005FC690Owner@@QAEXE@Z
// Evidence: each body is mov ecx,[ecx+0x18] then jmp to the rowed setter;
// callers are 0x005F3F54/0x005F4102 (6F7), 0x005F432E/0x005F44C7 (70A),
// 0x005F4345/0x005F44DE (71E). Wrapper holds the target pointer at +0x18.
// Honest address names; shape follows Rva00758210Thunks (/O1 tail-jmp).
class Rva005FC64AOwner
{
public:
	void setBit0(unsigned char value);
};
class Rva005FC6F7
{
public:
	void rva005FC6F7(unsigned char value);
private:
	char m_pad[0x18];
	Rva005FC64AOwner *m_ptr;
};
void Rva005FC6F7::rva005FC6F7(unsigned char value)
{
	return m_ptr->setBit0(value);
}
class Rva005FC66BOwner
{
public:
	void setBit1(unsigned char value);
};
class Rva005FC70A
{
public:
	void rva005FC70A(unsigned char value);
private:
	char m_pad[0x18];
	Rva005FC66BOwner *m_ptr;
};
void Rva005FC70A::rva005FC70A(unsigned char value)
{
	return m_ptr->setBit1(value);
}
class Rva005FC690Owner
{
public:
	void setBit2(unsigned char value);
};
class Rva005FC71E
{
public:
	void rva005FC71E(unsigned char value);
private:
	char m_pad[0x18];
	Rva005FC690Owner *m_ptr;
};
void Rva005FC71E::rva005FC71E(unsigned char value)
{
	return m_ptr->setBit2(value);
}
