// ?rva0046CE9D@Rva0046CE9D@@QAE_NPAVObject@@@Z
// cl: /DNDEBUG /MD
// ?rva0046CE9D@Rva0046CE9D@@QAE_NPAVObject@@@Z
// retail 0x0046CE9D (132 bytes). Chain from 0x00263763: every callee rowed.
// Null param or null/expired tracker ID returns false; ID resolved via
// TheGameLogic findObjectByID (rowed 0x00049DC5); distance via Object
// rva00263763 (rowed) against the pointer stored at this-0x114 compared to
// float g_00BC8970; related owners via Object rva002931F5(false) (rowed):
// same owner returns true else the distance flag.
// Evidence: TheGameLogic frame at +0x40 vs expiry +0x170; ID at +0x16C;
// callers none; neighbours in HordeContainParseRankCollections.cpp.

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object
{
public:
	float rva00263763(const void *other) const;
	Object *rva002931F5(bool checkProducer);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

public:
	char m_pad00[0x40];
	unsigned int m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

class Rva0046CE9D
{
public:
	bool rva0046CE9D(Object *obj);

private:
	char m_pad00[0x16C];
	ObjectID m_id; // +0x16C
	unsigned int m_expiry; // +0x170
};

bool Rva0046CE9D::rva0046CE9D(Object *obj)
{
	if (obj == 0)
		return false;
	else {
		if (m_id == INVALID_OBJECT_ID)
			return false;
		if (TheGameLogic->m_frame >= m_expiry)
			return false;
		Object *found = TheGameLogic->findObjectByID(m_id);
		if (found == 0)
			return false;
		const void *other = *(const void *const *)((const char *)this - 0x114);
		unsigned char flag = (unsigned char)(obj->rva00263763(other) < 10000.0f);
		Object *a = found->rva002931F5(false);
		Object *b = obj->rva002931F5(false);
		if (b == a)
			return true;
		return flag;
	}
}
