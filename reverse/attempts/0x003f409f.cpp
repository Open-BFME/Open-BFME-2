// ?rva003F409F@Rva003F409F@@QAEHH@Z
// partial score=0.9 date=2026-10-04
// cl: /O1 /DNDEBUG /MD
//
// ?rva003F409F@Rva003F409F@@QAEHH@Z @0x003F409F 28B. Lookup trampoline via
// global g_009FE1C8 plus rowed NameKeyType map 0x002120A4 with member key
// at +0x30 then tail virtual slot 12 or null return. Evidence: push [ecx+0x30]
// plus mov ecx [0x009FE1C8] plus call 0x002120A4 plus test eax eax plus
// mov edx [eax] plus mov ecx eax plus jmp [edx+0x30] plus ret 4; callers
// 0x0020E3A3 0x0020E78A 0x003F4400 0x003F8305 0x0056ACBB with int arg;
// honest address name.
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class Rva002120A4
{
public:
	int rva002120A4(NameKeyType key);
};

class Rva0021294A;
extern Rva0021294A *g_009FE1C8;

class LookupResult
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual int slot12(int x);
};

class Rva003F409F
{
public:
	int rva003F409F(int x);
private:
	char m_pad[0x30];
	NameKeyType m_key;
};

// ?rva003F409F@Rva003F409F@@QAEHH@Z present-unmatched
int Rva003F409F::rva003F409F(int x)
{
	int found = ((Rva002120A4 *)g_009FE1C8)->rva002120A4(m_key);
	if (found == 0) {
		return 0;
	} else {
		return ((LookupResult *)found)->slot12(x);
	}
}
