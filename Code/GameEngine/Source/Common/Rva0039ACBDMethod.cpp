// cl: /O1 /DNDEBUG /MD
// ?rva0039ACBD@Rva0039ACBD@@QAEHPBVObject@@_N@Z 0x0039ACBD 38B retail ALLIES-gated int field
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
	char m_pad00[0x14];
	int m_14;
	char m_pad18[0x34 - 0x18];
	Object const *m_34;
};

int Rva0039ACBD::rva0039ACBD(Object const *other, bool flag)
{
	if (other->getRelationship(m_34) == ALLIES && !flag) {
		return 0;
	}
	return m_14;
}
