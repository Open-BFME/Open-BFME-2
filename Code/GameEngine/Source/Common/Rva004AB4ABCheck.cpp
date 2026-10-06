// cl: /MD
// ?rva004AB4AB@Rva004AB4AB@@QBE_NXZ @0x004AB4AB 45B: returns false when TheGameLogic findObjectByID over m_28 misses or Object plus 0x438 bit0 set else inverted isKindOf 0x45. Callees rowed 0x00049DC5 and 0x0006F039. Caller at 0x004AB517. Prev Rva0024A797Grandchildren next LargeGroupAudioUpdateRandom share flags.

typedef bool Bool;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

enum KindOfType
{
	KIND_45 = 0x45
};

enum ObjectStatusTypes;

class Object
{
public:
	Bool isKindOf(KindOfType kind) const;

public:
	unsigned char m_pad00[0x438];
	unsigned char m_flag438;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Rva004AB4AB
{
public:
	Bool rva004AB4AB() const;

private:
	unsigned char m_pad00[0x28];
	ObjectID m_id28;
};

Bool Rva004AB4AB::rva004AB4AB() const
{
	Object *obj = TheGameLogic->findObjectByID(m_id28);
	if (!obj || (obj->m_flag438 & 1))
		return false;
	return !obj->isKindOf(KIND_45);
}
