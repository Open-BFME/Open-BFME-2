// cl: /GX- /MD /DNDEBUG
// ?rva004DF3B0@Rva004DF2E2@@QAEXPAX@Z @0x004DF3B0 72B: resolve m_20 via TheGameLogic::findObjectByID then guarded forward via rowed rva004DF2FC else clear; second phase forward m_08 via rowed Rva0028BC05::rva0028BC05 and clear status via rva004DF2E2; caller 0x0028BBEB unblocks 0x0028BBE1
#include "GameLogicObjectLookupView.h"

class Object;
class BfmeSubBEC;


extern GameLogic *TheGameLogic;

class Rva0028BC05
{
public:
	void rva0028BC05(void *p);
};

struct Rva004DF3B0Arg
{
	char m_pad00[0x74];
	ObjectID m_74;
};

class Rva004DF2E2
{
public:
	void rva004DF3B0(void *request);
	void rva004DF2FC(BfmeSubBEC *bec);
	void rva004DF2E2();
private:
	char m_pad00[8];
	void *m_08;
	char m_pad0C[0x20 - 0x0C];
	ObjectID m_20;
};

void Rva004DF2E2::rva004DF3B0(void *request)
{
	if (m_20 != INVALID_OBJECT_ID) {
		Object *obj = TheGameLogic->findObjectByID(m_20);
		if (obj == 0)
			m_20 = INVALID_OBJECT_ID;
		else
			rva004DF2FC((BfmeSubBEC *)obj);
	}
	if (request == 0)
		return;
	ObjectID nid = ((Rva004DF3B0Arg *)request)->m_74;
	void *slot = m_08;
	m_20 = nid;
	((Rva0028BC05 *)request)->rva0028BC05(slot);
	rva004DF2E2();
}
