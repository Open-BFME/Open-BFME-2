// cl: /DNDEBUG /MD
// ?rva005FFAA7Parse@@YIXPAVRva005FFAA7@@HPAD@Z @0x005FFAA7 57B and
// ?rva005FFAE0Parse@@YIXPAVRva005FFAA7@@HPAD@Z @0x005FFAE0 57B evidence:
// fastcall bool-string parsers (this, fwd-dead-in-edx, s): null s returns;
// non-digit first char returns (msvcr71 isdigit); atoi outside [0,2)
// returns; else m_00 virtual slot 8 (AA7) or slot 0xC (AE0) takes the int.
// msvcr71 dllimport isdigit/atoi; virtuals need no pins. TU-local views.
extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *str);

class Rva005FFAA7Inner
{
public:
	virtual void v00();
	virtual void v01();
	virtual void rva005FFAA7Set(int v);	// slot 2 (+8)
	virtual void rva005FFAE0Set(int v);	// slot 3 (+0xC)
};

class Rva005FFAA7
{
public:
	Rva005FFAA7Inner *m_00;
};

void __fastcall rva005FFAA7Parse(Rva005FFAA7 *o, int fwd, char *s)
{
	if (!s)
		return;
	if (!isdigit(*s))
		return;
	int v = atoi(s);
	if (v < 0 || v >= 2)
		return;
	o->m_00->rva005FFAA7Set(v);
}

void __fastcall rva005FFAE0Parse(Rva005FFAA7 *o, int fwd, char *s)
{
	if (!s)
		return;
	if (!isdigit(*s))
		return;
	int v = atoi(s);
	if (v < 0 || v >= 2)
		return;
	o->m_00->rva005FFAE0Set(v);
}
