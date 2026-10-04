// cl: /O1 /MD
//
// ?rva002A9ACC@Rva002A9ACC@@QAEXPBVDict@@@Z retail 0x002A9ACC 105B
// Two Dict color reads via rowed NameKey caches at 0x00DBDE64 and 0x00DBDE6C
// plus rowed Dict getInt at 0x003131CA. First hit writes +0x280 and +0x284
// second hit overwrites +0x284 with alpha 0xFF000000 ORed. Caller 0x002AFCDF.
// Evidence: retail calls rowed get 0x00148F5E twice and rowed getInt twice.
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva00148F5ECache
{
public:
	NameKeyType get();
private:
	NameKeyType m_key;
	const char *m_name;
};

extern Rva00148F5ECache g_00DBDE64;
extern Rva00148F5ECache g_00DBDE6C;

class Dict
{
public:
	int getInt(int key, bool *exists) const;
private:
	void *m_data;
};

class Rva002A9ACC
{
public:
	void rva002A9ACC(const Dict *dict);
private:
	unsigned char m_pad[0x280];
	int m_color1;
	int m_color2;
};

void Rva002A9ACC::rva002A9ACC(const Dict *dict)
{
	if (!dict)
		return;
	bool exists;
	int v = dict->getInt(g_00DBDE64.get(), &exists);
	if (exists)
	{
		v |= 0xFF000000;
		m_color1 = v;
		m_color2 = v;
	}
	int v2 = dict->getInt(g_00DBDE6C.get(), &exists);
	if (exists)
	{
		v2 |= 0xFF000000;
		m_color2 = v2;
	}
}

// ?rva002A9B58@Rva002A9B58@@QAEXPAURva002A7588In@@@Z 35B @0x002A9B58: thiscall with one arg ret4 void.
// Evidence: add ecx 0x60 once then cmp [edx+0x61c] jle to choose rowed 0x002A7513 void vs rowed 0x002A75C9 int.
// Callers at 0x0028DB00 0x0028EB0E 0x0028EBB7 0x00290DD3. LINK BONUS via 0x0028EB42.
struct Rva002A7588In
{
	char m_pad[4];
	void *m_p4;
};

struct Rva002A9B58Mid
{
	char _pad[0x61c];
	int _61c;
};

class Rva002A7513
{
public:
	void rva002A7513(void *a);
};

class Rva002A75C9
{
public:
	int rva002A75C9(Rva002A7588In *p);
};

class Rva002A7500
{
public:
	void rva002A7500(void *a);
};

class Rva002A75B8
{
public:
	int rva002A75B8(Rva002A7588In *p);
};

class Rva002A9B58
{
public:
	void rva002A9B58(Rva002A7588In *p);
	void rva002A9B35(Rva002A7588In *p);
private:
	char m_pad00[0x60];
};

void Rva002A9B58::rva002A9B58(Rva002A7588In *p)
{
	Rva002A7513 *a = (Rva002A7513 *)((char *)this + 0x60);
	Rva002A75C9 *b = (Rva002A75C9 *)((char *)this + 0x60);
	Rva002A9B58Mid *mid = (Rva002A9B58Mid *)p->m_p4;
	if (mid->_61c > 0)
		a->rva002A7513(p);
	else
		b->rva002A75C9(p);
}

void Rva002A9B58::rva002A9B35(Rva002A7588In *p)
{
	Rva002A7500 *a = (Rva002A7500 *)((char *)this + 0x60);
	Rva002A75B8 *b = (Rva002A75B8 *)((char *)this + 0x60);
	Rva002A9B58Mid *mid = (Rva002A9B58Mid *)p->m_p4;
	if (mid->_61c > 0)
		a->rva002A7500(p);
	else
		b->rva002A75B8(p);
}
