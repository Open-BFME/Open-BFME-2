// cl: /O1 /MD
// ?rva002A8AE4@Rva002A8F24@@QAEPAURva002A8AE4Record@@PAX@Z @0x002A8AE4 64B.
// Lookup-or-fallback: look up the void* key via pin-only 0x002A8AB1, and when
// the record is non-null but its rowed disp8 bool getter 0x002C67CF is false
// (field +0x178 == -1 per Disp8CmpBoolGetters.cpp), resolve the +0x178
// player index via rowed PlayerList::getNthPlayer through ThePlayerList and
// look that player up again. Otherwise return the first record. Evidence:
// caller 0x005056C7, rowed get/getNthPlayer callees, pin-only lookup,
// ThePlayerList extern in use by 10 TUs. Honest pin-held names.
class Player;
class PlayerList
{
public:
	Player *getNthPlayer(int index);
};
extern PlayerList *ThePlayerList;

class Rva002C67CFCmpBoolField
{
public:
	bool get() const;
	char m_lead[0x178];
	int m_value;
};

struct Rva002A8AB1Record : public Rva002C67CFCmpBoolField
{
};

struct Rva002A8AE4Record : public Rva002C67CFCmpBoolField
{
};

struct Rva002A8B59Data;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *key);
	Rva002A8AE4Record *rva002A8AE4(void *key);
	Rva002A8B59Data *rva002A8B59(void *key);
};

Rva002A8AE4Record *Rva002A8F24::rva002A8AE4(void *key)
{
	Rva002A8AB1Record *r = rva002A8AB1(key);
	if (r != 0 && !r->get())
	{
		Player *p = ThePlayerList->getNthPlayer(r->m_value);
		return (Rva002A8AE4Record *)rva002A8AB1(p);
	}
	return (Rva002A8AE4Record *)r;
}

// ?rva002A8B59@Rva002A8F24@@QAEPAURva002A8B59Data@@PAX@Z, retail 0x002A8B59, 26 bytes.
// Lookup-or-field: look up void* key via pin-only 0x002A8AB1, and when non-null
// return the pointer at +0x160, else null. Evidence: packet disassembly,
// callers (2 matched rows show void* key), prev/next flags, pin-held name.
Rva002A8B59Data *Rva002A8F24::rva002A8B59(void *key)
{
	Rva002A8AB1Record *r = rva002A8AB1(key);
	return r ? *(Rva002A8B59Data **)((char *)r + 0x160) : 0;
}
