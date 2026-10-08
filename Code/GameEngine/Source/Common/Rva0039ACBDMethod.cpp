// cl: /DNDEBUG /MD
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
	int rva0039ACE3(Object const *other);
	// WorldBuilder keeps this as its own 30-byte call (0xF9FAA0); retail
	// inlines it: the int at +0x18, with -1 reading as 0.
	int m18OrZero() const { if (m_18 == -1) return 0; return m_18; }
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

// ?rva0039ACE3@Rva0039ACBD@@QAEHPBVObject@@@Z 0x0039ACE3 40B: 0 for an ALLIES
// object (pinned Object::getRelationship 0x0028D156 against +0x34), else the
// inlined +0x18 value with -1 as 0. Caller 0x002AA71B; WorldBuilder's unnamed
// counterpart 0xFA04B0 (call graph) makes the same calls. Writing the -1 test
// inside the inline helper is what keeps retail's mov+inc (a bare expression
// becomes lea).
int Rva0039ACBD::rva0039ACE3(Object const *other)
{
	if (other->getRelationship(m_34) == ALLIES)
		return 0;
	return m18OrZero();
}
