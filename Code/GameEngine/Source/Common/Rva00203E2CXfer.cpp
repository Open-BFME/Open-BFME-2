// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00203E2CXfer@@YAXPAVRva00203E2CA@@PAVRva00203E2CB@@@Z at retail
// 0x00203E2C (27B). Sibling of Rva00203E11Xfer (0x00203E11): free __cdecl
// helper xferring the ObjectID at b+4 through the Xfer from virtual slot
// 0x78 (slot 30) on a.
// Target evidence: identical byte shape to 0x00203E11 except [edx+0x78];
// call rowed ?XferObjectID@@YAXPAVXfer@@PAW4ObjectID@@@Z. Callers at
// 0x00206B6B/0x00206BB1 in FUN_00606B02 pass __cdecl args.

class Xfer;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class Rva00203E2CA
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29();
	virtual Xfer *s30(void *p);
};

class Rva00203E2CB
{
public:
	char m_pad[4]; // +0x00..0x04
	ObjectID m_id; // +0x04
};

void Rva00203E2CXfer(Rva00203E2CA *a, Rva00203E2CB *b)
{
	XferObjectID(a->s30(b), &b->m_id);
}
