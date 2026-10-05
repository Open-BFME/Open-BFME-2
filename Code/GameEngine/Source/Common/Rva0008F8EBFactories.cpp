// cl: /O1 /DNDEBUG /MD /EHsc
//
// Four more 58-byte __stdcall factories of the rowed
// ?Rva0008F6E1Create@@YGPAVRva000A0891@@PAX@Z shape (Rva0008F6E1Create.cpp):
// operator new 0x0002FDA0 of 0x2F0 bytes, then the constructor with the one
// argument.  Like their rowed siblings 0x0008F6E1, 0x0008FB69 and 0x0008FBA3
// they have no direct caller and no pointer in .rdata/.data.  Classes keep
// the names of their already-rowed constructors where those exist; the other
// two constructors are pinned under address names.  Identities are not
// recovered.
//
//   factory     ctor
//   0x0008F8EB  0x000A334F (rowed)
//   0x0008FA81  0x000A2137
//   0x0008FABB  0x000A217F
//   0x00104FD5  0x00104F8F (rowed)

void *__cdecl operator new(unsigned int size);

class Rva000A334F
{
public:
	Rva000A334F(void *context);
private:
	char m_pad[0x2F0];
};

Rva000A334F *__stdcall Rva0008F8EBCreate(void *context)
{
	return new Rva000A334F(context);
}

class Rva000A2137
{
public:
	Rva000A2137(void *context);
private:
	char m_pad[0x2F0];
};

Rva000A2137 *__stdcall Rva0008FA81Create(void *context)
{
	return new Rva000A2137(context);
}

class Rva000A217F
{
public:
	Rva000A217F(void *context);
private:
	char m_pad[0x2F0];
};

Rva000A217F *__stdcall Rva0008FABBCreate(void *context)
{
	return new Rva000A217F(context);
}

class Rva0078D310Host
{
public:
	Rva0078D310Host(void *context);
private:
	char m_pad[0x2F0];
};

Rva0078D310Host *__stdcall Rva00104FD5Create(void *context)
{
	return new Rva0078D310Host(context);
}
