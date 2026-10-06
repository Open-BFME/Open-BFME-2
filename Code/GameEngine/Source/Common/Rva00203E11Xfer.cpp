// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00203E11Xfer@@YAXPAVRva00203E11A@@PAVRva00203E11B@@@Z at retail
// 0x00203E11 (27B). Free __cdecl helper: xfers the ObjectID at b+4 through
// the Xfer returned by virtual slot 0x6C (slot 27) on a.
// Target evidence: mov eax,[esp+8]; lea ecx,[eax+4]; push ecx;
// mov ecx,[esp+8]; mov edx,[ecx]; push eax; call [edx+0x6C];
// push eax; call rowed ?XferObjectID@@YAXPAVXfer@@PAW4ObjectID@@@Z;
// pop ecx; pop ecx; ret. Callers at 0x00208237/0x00208280 pass (esi,
// &field+8) as __cdecl args. Slot index and +4 ObjectID offset are target
// facts; host classes are honest address names.

class Xfer;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class Rva00203E11A
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26();
	virtual Xfer *s27(void *p);
};

class Rva00203E11B
{
public:
	char m_pad[4]; // +0x00..0x04
	ObjectID m_id; // +0x04
};

void Rva00203E11Xfer(Rva00203E11A *a, Rva00203E11B *b)
{
	XferObjectID(a->s27(b), &b->m_id);
}
