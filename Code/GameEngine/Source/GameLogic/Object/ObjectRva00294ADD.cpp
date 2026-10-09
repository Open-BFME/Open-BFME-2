// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva00294ADD@Object@@QAEHH@Z retail 0x00294ADD..0x00294C1A (317 bytes
// ret 4). Upgrade production check called from AIUpgrade::canMake 0x00597426
// (pinned spelling; the int argument is the production entry's address).
// WorldBuilder twin 0x00CCC1A0 (callgraph evidence) has the same structure.
// Returns 9 when the entry has no upgrade (+0x24) when the 0x0028BC94 gate
// is missing or blocked (vtable +0x64) when a KindOf 0x96 object's body
// reports damage state 3 or when an object upgrade (type 1) is already
// present (0x00290D2B) or does not affect this object (0x002940B9 = WB
// Object::affectedByUpgrade). With a controlling player that passes the
// 0x002A8AB1 lookup and entry flag 0x40 it walks the prerequisite upgrades
// (+0x28 vector): player upgrades through 0x002AB87D object upgrades through
// 0x00290D2B with the +0x34 require-all flag; an unmet set returns 9 and
// everything else 0. As in WB the object branch of the any-of case keeps
// looping after marking the set blocked. Names are inferred.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class UpgradeTemplate
{
public:
	Int getUpgradeType() const { return m_type; }

private:
	void *m_vtbl;
	Int m_type; // +0x04
};

class ThingTemplate
{
public:
	__forceinline UnsignedInt isKindOf(Int t) const { return m_kindOf[t >> 5] & (1 << (t & 31)); }

private:
	char m_pad000[0x108];
	UnsignedInt m_kindOf[8]; // +0x108
};

class Player
{
public:
	Bool rva002AB87D(const UpgradeTemplate *upgrade) const;
	void *getPlayerListKey() const { return m_5C; }

private:
	char m_pad000[0x5C];
	void *m_5C; // +0x5C
};

struct Rva002A8AB1Record;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *player);
};

extern Rva002A8F24 *g_00DFEEF8;

class Rva00294ADDGate
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24();
	virtual Bool isBlocked(); // +0x64
};

class BodyModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual Int getDamageState() const; // +0x20
};

struct Rva00294ADDEntry
{
	char m_pad000[0x1C];
	UnsignedInt m_flags; // +0x1C
	char m_pad020[4];
	const UpgradeTemplate *m_upgrade; // +0x24
	const UpgradeTemplate **m_prereqBegin; // +0x28
	const UpgradeTemplate **m_prereqEnd; // +0x2C
	const UpgradeTemplate **m_prereqCapacity; // +0x30
	Bool m_requireAll; // +0x34
	UnsignedInt prereqCount() const { return m_prereqEnd - m_prereqBegin; }
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	void *rva0028BC94();
	Bool rva00290D2B(const UpgradeTemplate *upgrade) const;
	Bool rva002940B9(const UpgradeTemplate *upgrade);
	Player *getControllingPlayer() const;
	Int rva00294ADD(Int entry);

private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	char m_pad008[0x254 - 8];
	BodyModuleInterface *m_body; // +0x254
};

Int Object::rva00294ADD(Int entry)
{
	const Rva00294ADDEntry *rec = reinterpret_cast<const Rva00294ADDEntry *>(entry);
	const UpgradeTemplate *upgrade = rec->m_upgrade;
	if (upgrade == 0)
		return 9;
	Rva00294ADDGate *gate = static_cast<Rva00294ADDGate *>(rva0028BC94());
	if (gate == 0 || gate->isBlocked())
		return 9;
	if (getTemplate()->isKindOf(0x96) && m_body->getDamageState() == 3)
		return 9;
	if (upgrade->getUpgradeType() == 1)
	{
		if (rva00290D2B(upgrade) || !rva002940B9(upgrade))
			return 9;
	}
	if (getControllingPlayer() != 0)
	{
		if (getControllingPlayer()->getPlayerListKey() == 0
			|| g_00DFEEF8->rva002A8AB1(getControllingPlayer()) != 0)
		{
			if (rec->m_flags & 0x40)
			{
				Bool requireAll = rec->m_requireAll;
				Bool blocked = requireAll != 0;
				for (UnsignedInt i = 0; i < rec->prereqCount(); i++)
				{
					const UpgradeTemplate *prereq = rec->m_prereqBegin[i];
					if (prereq == 0)
						continue;
					if (prereq->getUpgradeType() == 0)
					{
						Bool has = getControllingPlayer()->rva002AB87D(prereq);
						if (requireAll)
						{
							if (has)
							{
								blocked = false;
								break;
							}
						}
						else if (!has)
						{
							blocked = true;
							break;
						}
					}
					else if (prereq->getUpgradeType() == 1)
					{
						Bool has = rva00290D2B(prereq);
						if (requireAll)
						{
							if (has)
							{
								blocked = false;
								break;
							}
						}
						else if (!has)
							blocked = true;
					}
				}
				if (blocked)
					return 9;
			}
		}
	}
	return 0;
}
