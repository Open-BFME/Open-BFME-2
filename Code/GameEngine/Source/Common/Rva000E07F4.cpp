// cl: /O1 /DNDEBUG /MD
// ?rva000E07F4@@YAHPAVRva000E07F4Obj@@PAVRva000E07F4Host@@@Z @0x000E07F4 34B.
// cdecl. Null or kind-bit 0x80 on the inner object skips the thiscall.
// Always returns 1 via xor/inc. Callee 0x000E0584 cleans the one pointer.

class Rva000E07F4Inner
{
public:
	char m_pad[0x10D];
	unsigned char m_flags;
};

class Rva000E07F4Obj
{
public:
	int m_unk;
	Rva000E07F4Inner *m_inner;
};

class Rva000E07F4Host
{
public:
	void rva000E0584(Rva000E07F4Obj *obj);
};

int rva000E07F4(Rva000E07F4Obj *obj, Rva000E07F4Host *host)
{
	if (obj && (obj->m_inner->m_flags & 0x80) == 0)
		host->rva000E0584(obj);
	return 1;
}
