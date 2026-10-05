// ?rva0039ACE3@Rva0039ACBD@@QAEHPBVObject@@@Z
// partial score=0.97 date=2026-10-04
// cl: /O1 /DNDEBUG /MD
// ?rva0039ACBD@Rva0039ACBD@@QAEHPBVObject@@_N@Z 0x0039ACBD 38B retail ALLIES-gated int field
// ?rva0039ACE3@Rva0039ACBD@@QAEHPBVObject@@@Z 0x0039ACE3 40B retail ALLIES-gated m_18-or-zero
// Evidence: retail calls pinned Object::getRelationship 0x0028D156 on first arg with this+0x34 then byte-tests second arg; callers at 0x00294C5A and 0x002AA691.

enum Relationship
{
	ENEMIES,
	NEUTRAL,
	ALLIES
};

class Object
{
public:
	Relationship getRelationship(Object const *that) const;
};

class Rva0039ACBD
{
public:
	int rva0039ACBD(Object const *other, bool flag);
	int rva0039ACE3(Object const *other);
	char m_pad00[0x14];
	int m_14;
	int m_18;
	char m_pad1C[0x34 - 0x1C];
	Object const *m_34;
};

int Rva0039ACBD::rva0039ACBD(Object const *other, bool flag)
{
	if (other->getRelationship(m_34) == ALLIES && !flag) {
		return 0;
	}
	return m_14;
}

// ?rva0039ACE3@Rva0039ACBD@@QAEHPBVObject@@@Z present-unmatched
int Rva0039ACBD::rva0039ACE3(Object const *other)
{
	if (other->getRelationship(m_34) == ALLIES) {
		return 0;
	}
	int probe = m_18;
	++probe;
	return probe ? m_18 : 0;
}
