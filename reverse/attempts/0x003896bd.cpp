// ?rva003896BD@Rva003896BDOwner@@QAEPAXH@Z
// partial score=0.95 date=2026-10-06
// cl: /O1 /MD
//
// ?rva003896BD@Rva003896BDOwner@@QAEPAXH@Z @0x003896BD 42B
// Opaque map lookup with validation: finds the int key in the +0x278
// member (fresh pin 0x00388F63, REL32-read), returns the hit when it
// equals the member's cached first dword, else validates the hit's
// +0x14 link (null gives null) and that link's +0x18 flag (nonzero
// returns the link, zero returns null). Member and node identities
// unproven; address-derived views.

#define NULL 0

struct Rva003896BDX
{
	char m_pad[0x18];
	int m_18;
};

struct Rva003896BDRet
{
	char m_pad[0x14];
	Rva003896BDX *m_14;
};

struct Rva003896BDMap
{
	void *find(int *key);
	void *m_00;
};

class Rva003896BDOwner
{
public:
	void *rva003896BD(int arg);

private:
	char m_pad00[0x278];
	Rva003896BDMap m_map; // +0x278
};

// ?rva003896BD@Rva003896BDOwner@@QAEPAXH@Z, retail 0x003896BD, 42 bytes.
void *Rva003896BDOwner::rva003896BD(int arg)
{
	void *r = m_map.find(&arg);
	if (r == m_map.m_00)
		return NULL;
	r = ((Rva003896BDRet *)r)->m_14;
	if (r == NULL)
		return r;
	if (((Rva003896BDX *)r)->m_18 != 0)
		return r;
	return NULL;
}
