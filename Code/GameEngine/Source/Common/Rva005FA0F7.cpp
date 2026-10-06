// cl: /DNDEBUG /MD
// ?rva005FA0F7Init@@YIPAVRva005FA0F7@@PAV1@HPAURva005FA0F7A@@HH@Z @0x005FA0F7
// 46B evidence: fastcall init (this, fwd-passthrough-in-edx, a, b, c)
// chaining to pinned ?rva005F9DCB@@YIXPAVRva005F9DCBObj@@HHHHHH@Z @0x005F9DCB
// with (this, fwd, a->m_04, &a->m_08, 0x00C67D58, b, c); installs vtable
// 0x00C79D78 by literal store (fixed-base game.dat, no reloc needed);
// returns this; ret 0xC. Same shape as 0x005FA0C9 (pushed vtable const differs).
// TU-local view only.
struct Rva005FA0F7A
{
	int m_00;
	int m_04;
	int m_08;
};

class Rva005FA0F7
{
public:
	char m_pad[4];
};

class Rva005F9DCBObj;
void __fastcall rva005F9DCB(Rva005F9DCBObj *o, int fwd, int s1, int s2, int s3, int s4, int s5);

Rva005FA0F7 *__fastcall rva005FA0F7Init(Rva005FA0F7 *o, int fwd, Rva005FA0F7A *a, int b, int c)
{
	rva005F9DCB((Rva005F9DCBObj *)o, fwd, a->m_04, (int)&a->m_08, 0x00C67D58, b, c);
	((int *)o)[0] = 0x00C79D78;
	return o;
}
