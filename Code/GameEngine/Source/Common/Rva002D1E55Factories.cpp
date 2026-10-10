// cl: /DNDEBUG /MD /EHsc
//
// Factory entries: 58-byte __stdcall functions that allocate a fixed-size
// object through operator new 0x0002FDA0 and construct it from their one
// argument, the shape of the rowed ?Rva0008F6E1Create@@YGPAVRva000A0891@@PAX@Z
// (Rva0008F6E1Create.cpp).  Every entry here is referenced from a function
// pointer table in .rdata/.data and has no direct caller.  Each class is
// named after its constructor address (pinned) and carries only its size;
// identities are not recovered except AptLanLobby, whose complete constructor
// and native callback registrations now establish the existing6C4-byte view.
//
//   factory     size   ctor
//   0x002D1E55  0x27C  0x0051268C
//   0x002D1E8F  0x27C  0x00512AC8
//   0x002D1F03  0x438  0x005142B0
//   0x002D1F3D  0x288  0x004E8B38
//   0x002D1F77  0x6C4  0x00445EE3
//   0x002D1FB1  0x2AC  0x00516211
//   0x002D1FEB  0x2B4  0x004E4A45
//   0x002D2025  0x2BC  0x0051795C
//   0x002D205F  0x324  0x0051A78E
//   0x002D2099  0x284  0x0051BADF
//   0x002D210D  0x2C4  0x0051D1E6
//   0x002D2147  0x2F4  0x005202C8
//   0x002D2181  0x288  0x005212FC
//   0x002D21FB  0x294  0x00523825
//   0x0043DA1B  0x35C  0x0043D686
//   0x0051104D  0x28C  0x00510FDB

void *__cdecl operator new(unsigned int size);

class Rva0051268C
{
public:
	Rva0051268C(void *context);
private:
	char m_pad[0x27C];
};

Rva0051268C *__stdcall Rva002D1E55Create(void *context)
{
	return new Rva0051268C(context);
}

class Rva00512AC8
{
public:
	Rva00512AC8(void *context);
private:
	char m_pad[0x27C];
};

Rva00512AC8 *__stdcall Rva002D1E8FCreate(void *context)
{
	return new Rva00512AC8(context);
}

class Rva005142B0
{
public:
	Rva005142B0(void *context);
private:
	char m_pad[0x438];
};

Rva005142B0 *__stdcall Rva002D1F03Create(void *context)
{
	return new Rva005142B0(context);
}

class Rva004E8B38
{
public:
	Rva004E8B38(void *context);
private:
	char m_pad[0x288];
};

Rva004E8B38 *__stdcall Rva002D1F3DCreate(void *context)
{
	return new Rva004E8B38(context);
}

class AptLanLobby
{
public:
	AptLanLobby(void *context);
private:
	char m_pad[0x6C4];
};

AptLanLobby *__stdcall Rva002D1F77Create(void *context)
{
	return new AptLanLobby(context);
}

class Rva00516211
{
public:
	Rva00516211(void *context);
private:
	char m_pad[0x2AC];
};

Rva00516211 *__stdcall Rva002D1FB1Create(void *context)
{
	return new Rva00516211(context);
}

class Rva004E4A45
{
public:
	Rva004E4A45(void *context);
private:
	char m_pad[0x2B4];
};

Rva004E4A45 *__stdcall Rva002D1FEBCreate(void *context)
{
	return new Rva004E4A45(context);
}

class Rva005173F8
{
public:
	Rva005173F8(void *context);
private:
	char m_pad[0x2BC];
};

Rva005173F8 *__stdcall Rva002D2025Create(void *context)
{
	return new Rva005173F8(context);
}

class Rva0051A78E
{
public:
	Rva0051A78E(void *context);
private:
	char m_pad[0x324];
};

Rva0051A78E *__stdcall Rva002D205FCreate(void *context)
{
	return new Rva0051A78E(context);
}

class Rva0051BADF
{
public:
	Rva0051BADF(void *context);
private:
	char m_pad[0x284];
};

Rva0051BADF *__stdcall Rva002D2099Create(void *context)
{
	return new Rva0051BADF(context);
}

class Rva0051D1E6
{
public:
	Rva0051D1E6(void *context);
private:
	char m_pad[0x2C4];
};

Rva0051D1E6 *__stdcall Rva002D210DCreate(void *context)
{
	return new Rva0051D1E6(context);
}

class Rva005202C8
{
public:
	Rva005202C8(void *context);
private:
	char m_pad[0x2F4];
};

Rva005202C8 *__stdcall Rva002D2147Create(void *context)
{
	return new Rva005202C8(context);
}

class Rva005212FC
{
public:
	Rva005212FC(void *context);
private:
	char m_pad[0x288];
};

Rva005212FC *__stdcall Rva002D2181Create(void *context)
{
	return new Rva005212FC(context);
}

// Retail 0x002D21BB (64 bytes): the skirmish screen's factory takes the same
// one argument but passes the rowed AptSkirmish constructor (0x00522B0E,
// ret 8) a second word read from the global at VA 0x00DD179C.
class AptSkirmish
{
public:
	AptSkirmish(void *context, int mode);
private:
	char m_pad[0x6DC];
};

extern int g_00DD179C;

AptSkirmish *__stdcall Rva002D21BBCreate(void *context)
{
	return new AptSkirmish(context, g_00DD179C);
}

class Rva00523825
{
public:
	Rva00523825(void *context);
private:
	char m_pad[0x294];
};

Rva00523825 *__stdcall Rva002D21FBCreate(void *context)
{
	return new Rva00523825(context);
}

class Rva0043D686
{
public:
	Rva0043D686(void *context);
private:
	char m_pad[0x35C];
};

Rva0043D686 *__stdcall Rva0043DA1BCreate(void *context)
{
	return new Rva0043D686(context);
}

class Rva00510FDB
{
public:
	Rva00510FDB(void *context);
private:
	char m_pad[0x28C];
};

Rva00510FDB *__stdcall Rva0051104DCreate(void *context)
{
	return new Rva00510FDB(context);
}
