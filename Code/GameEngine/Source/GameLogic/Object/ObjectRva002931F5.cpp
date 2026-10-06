// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002931F5@Object@@QAEPAV1@_N@Z, retail 0x002931F5, 84 bytes.
// Object helper: if own template dword +0x114 carries 0x2000 return this;
// else if containedBy (+0x274) template carries it return containedBy;
// else if bool arg set look up producerID (+0x78) via TheGameLogic
// findObjectByID (rowed 0x00049DC5) and return producer if its template
// carries it, else null. Evidence: Object offsets template +0x04
// (Object_isAbleToAttack/ObjectScriptStatus), producer +0x78
// (ObjectSetProducer), containedBy +0x274 (Object_isAbleToAttack),
// TheGameLogic at 0x00DFE78C; callers 0x002933CD (chain + testStatus
// 0x5F/0x60) and 0x00293926 (isKindOf gate) prove Object owner.

typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
};

enum KindOfType
{
	KINDOF_DUMMY = 0
};

enum ObjectStatusTypes
{
	STATUS_5F = 0x5F,
	STATUS_60 = 0x60
};

struct ThingTemplate
{
	unsigned char m_pad[0x114];
	unsigned int m_flags114;
};

class Object;

class GameLogic
{
public:
	class Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	Object *rva002931F5(Bool checkProducer);
	Bool rva00293926(KindOfType kind);
	int rva002933CD();
	void *rva0029439D();
	Bool isKindOf(KindOfType kind) const;
	Bool testStatus(ObjectStatusTypes bit) const;
	void *rva0028C197() const;

private:
	unsigned char m_pad00[4];
	ThingTemplate *m_template;
	unsigned char m_pad08[0x78 - 0x08];
	ObjectID m_producerID;
	unsigned char m_pad7C[0x274 - 0x7C];
	Object *m_containedBy;
};

Object *Object::rva002931F5(Bool checkProducer)
{
	if ((m_template->m_flags114 & 0x2000) != 0)
		return this;
	Object *contained = m_containedBy;
	if (contained != 0 && (contained->m_template->m_flags114 & 0x2000) != 0)
		return contained;
	if (checkProducer)
	{
		Object *producer = TheGameLogic->findObjectByID(m_producerID);
		if (producer != 0 && (producer->m_template->m_flags114 & 0x2000) != 0)
			return producer;
	}
	return 0;
}

Bool Object::rva00293926(KindOfType kind)
{
	if (isKindOf(kind))
		return true;
	Object *related = rva002931F5(false);
	if (related != 0)
		return related->isKindOf(kind);
	return false;
}

int Object::rva002933CD()
{
	Object *cur = this;
	for (;;)
	{
		Object *next = cur->rva002931F5(false);
		if (next == 0)
			break;
		if (next == cur)
			break;
		cur = next;
	}
	if (cur->testStatus(STATUS_60) || cur->testStatus(STATUS_5F))
		return 1;
	return 0;
}

// ?rva0029439D@Object@@QAEPAXXZ, retail 0x0029439D, 21 bytes.
// Object helper: related via rva002931F5(false); if non-null tail to
// rva0028C197 else null. Evidence: thiscall with no args proven by callers
// 0x002946AB (mov esi ecx then call) and 0x002957FC (mov ecx esi then call);
// callees rowed 0x002931F5 and 0x0028C197; sits after 0x00293926 in this TU.
void *Object::rva0029439D()
{
	Object *related = rva002931F5(false);
	if (related != 0)
		return related->rva0028C197();
	return 0;
}
