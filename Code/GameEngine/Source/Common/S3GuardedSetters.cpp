// Three guarded setters.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/S3GuardedSetters.cpp); trimmed to the three
// T1 bodies the sweep places.

typedef bool Bool;

struct Gen_00750550Impl
{
	char m_bfmeHead[0x4];
	Bool m_bfmeField;						// +0x4
};

class Gen_00750550
{
public:
	void bfmeSet(Bool value);

private:
	char m_bfmeHead[0x44];
	Gen_00750550Impl *m_bfmeImpl;					// +0x44
};

struct Gen_00750570Impl
{
	char m_bfmeHead[0x5];
	Bool m_bfmeField;						// +0x5
};

class Gen_00750570
{
public:
	void bfmeSet(Bool value);

private:
	char m_bfmeHead[0x44];
	Gen_00750570Impl *m_bfmeImpl;					// +0x44
};



// ?bfmeSet@Gen_00750550@@QAEX_N@Z
void Gen_00750550::bfmeSet(Bool value)
{
	if (m_bfmeImpl)
		m_bfmeImpl->m_bfmeField = value;
}

// ?bfmeSet@Gen_00750570@@QAEX_N@Z
void Gen_00750570::bfmeSet(Bool value)
{
	if (m_bfmeImpl)
		m_bfmeImpl->m_bfmeField = value;
}


// ?bfmeSet@Gen_006BD4E0@@QAEX_N@Z @0x006BD4E0 (10B). Target facts: it stores its byte argument at +0x20, and nothing in
// .text or .rdata refers to it. MeshClass slots 94 and 95 put MeshGeometryClass's sort level at +0x1C, so it is not that
// class's setter, whatever a Zero Hour-layout compile suggested. Owner unknown.
class Gen_006BD4E0
{
public:
	void bfmeSet(Bool value);

private:
	char m_bfmeHead[0x20];
	Bool m_bfmeField;								// +0x20
};

void Gen_006BD4E0::bfmeSet(Bool value)
{
	m_bfmeField = value;
}
