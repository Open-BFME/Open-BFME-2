// cl: /O1 /MD
// ?Rva0041BF47Get@@YG_NPAVObject@@0H@Z @0x0041BF47 91B. Free stdcall bool
// (Object *a, Object *b, int unused): a/b non-null, a template +0x109
// bit 0x40 set, a->getRelationship(b)==2 (ALLIES), b->testStatus(2),
// a+0x438 bit0 clear, and b->getSoleHealingBenefactor()==0 or ==a->m_id
// (+0x74). Evidence: caller 0x00488B36 in 81B body; prev/next
// Rva0041B94A/Rva0041C21BIsVisible share /O1 /MD and (Object*,Object*,int)
// shape with unused third arg; callees pinned getRelationship and rowed
// testStatus/getSoleHealingBenefactor.
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_0 = 0,
	OBJECT_STATUS_1 = 1,
	OBJECT_STATUS_2 = 2
};

enum ObjectID
{
	OBJECTID_INVALID = 0
};

class ThingTemplate
{
public:
	unsigned char m_pad00[0x109];
	unsigned char m_flags109;               // +0x109 bit 0x40
};

class Object
{
public:
	Relationship getRelationship(const Object *that) const;
	bool testStatus(ObjectStatusTypes s) const;
	ObjectID getSoleHealingBenefactor() const;

	unsigned char m_pad00[4];
	ThingTemplate *m_template;               // +0x04
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id;                           // +0x74
	unsigned char m_pad78[0x438 - 0x78];
	unsigned char m_flags438;                // +0x438 bit0
};

bool __stdcall Rva0041BF47Get(Object *a, Object *b, int)
{
	if (a == 0 || b == 0)
		return false;
	if ((a->m_template->m_flags109 & 0x40) == 0)
		return false;
	Relationship r = a->getRelationship(b);
	if (r != ALLIES)
		return false;
	if (!b->testStatus((ObjectStatusTypes)r))
		return false;
	if ((a->m_flags438 & 1) != 0)
		return false;
	ObjectID ben = b->getSoleHealingBenefactor();
	if (ben != 0 && ben != a->m_id)
		return false;
	return true;
}
