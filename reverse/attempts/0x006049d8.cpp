// ?rva006049D8Check@@YI_NPAVRva006049D8@@HPAD@Z
// partial score=0.85 date=2026-10-06
// cl: /O1 /Oy- /DNDEBUG /MD
// ?rva006049D8Check@@YI_NPAVRva006049D8@@HPAD@Z @0x006049D8 70B evidence:
// fastcall checker (this, fwd-dead-forwarded, s) returning bool: 0x208
// buffer; null or empty s returns false; pinned __cdecl-4
// ?rva0042FB60@@YAXHPADHH@Z @0x0042FB60(0x104, buf, -1, s); returns m_vtable
// slot 11 (+0x2C) on this with buf (fastcall dead-edx forwarded); ret 4.
// TU-local view only.
class Rva006049D8
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10();
	virtual bool __fastcall rva006049D8Slot(int fwd, char *buf);	// slot 11 (+0x2C)
};

void __cdecl rva0042FB60(int a, char *b, int c, const char *d);

// ?rva006049D8Check@@YI_NPAVRva006049D8@@HPAD@Z present-unmatched
bool __fastcall rva006049D8Check(Rva006049D8 *o, int fwd, char *s)
{
	char buf[0x208];
	if (!s)
		return false;
	if (*s == 0)
		return false;
	rva0042FB60(0x104, buf, -1, s);
	return o->rva006049D8Slot(fwd, buf);
}
