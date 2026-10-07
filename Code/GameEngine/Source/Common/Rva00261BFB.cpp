// cl: /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// ?rva00261BFB@Rva00261BFB@@UAE_NPAVObject@@@Z @ 0x00261BFB (93B).
// Identity evidence: stored callback table slot with neighbouring FileClass entries;
// those neighbours do not establish this callback's semantic class name.
// Layout evidence: target reads its object pointer at +8; remaining fields are address-named.
class ObjectTemplate
{
public:
	unsigned char m_pad00[0x108];
	unsigned char m_flags108;
	unsigned char m_pad109[0x113 - 0x109];
	unsigned char m_flags113;
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_8 = 8
};

enum Relationship
{
	RELATIONSHIP_NONE = 0
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	Relationship getRelationship(const Object *other) const;
	bool isAbleToAttack() const;
	int m_pad00;
	ObjectTemplate *m_template;
	unsigned char m_pad08[0x438 - 8];
	unsigned char m_flags438;
};

class Rva00261BFB
{
public:
	virtual void slot0() {}
	virtual bool rva00261BFB(Object *obj);
private:
	int m_pad04;
	Object *m_object;
};

bool Rva00261BFB::rva00261BFB(Object *obj)
{
	Object *filterObject = m_object;
	if (obj == filterObject)
		return false;
	if (obj->testStatus(OBJECT_STATUS_8))
		return true;
	if ((obj->m_flags438 & 1) != 0)
		return false;
	if (filterObject->getRelationship(obj) != RELATIONSHIP_NONE)
		return false;
	ObjectTemplate *objectTemplate = obj->m_template;
	if ((objectTemplate->m_flags108 & 0x80) == 0 &&
		(objectTemplate->m_flags113 & 2) != 0)
		return false;
	if (obj->isAbleToAttack())
		return true;
	return false;
}
