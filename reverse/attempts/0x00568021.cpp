// ?rva00568021@Rva00568021@@QAEXXZ
// partial score=0.98 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// ?rva00568021@Rva00568021@@QAEXXZ @0x00568021 181B
// Evidence: chain from 0x00567B6D; virtual slot 4 on member +0xC; callees rowed/pinned; globals TheGameLogic ThePlayerList.
class Object;
enum ObjectID
{
	OBJECTID_INVALID = 0
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
class PlayerList;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
class Rva005C38EChecker
{
public:
	bool Check(void *obj);
};
class Rva00005C357FPtrChaseField
{
public:
	int get() const;
};
class Rva0057C22FByteChaseField
{
public:
	unsigned char get() const;
};
class Rva00005C39A3PtrChaseField
{
public:
	int get() const;
};
class Rva005C39AA
{
public:
	void rva005C39AA();
};
class Rva005C3EE0
{
public:
	void rva005C3EE0();
};
class Rva0035B6B8
{
public:
	int rva0035B6B8(int index);
};
class Rva005C3F02;
class Rva005677B9
{
public:
	struct Payload
	{
		int v[2];
	};
};
void __cdecl Rva00567B6DAdd(Rva005C3F02 *dst, const Rva005677B9::Payload *src);
class Rva00568021Fetcher
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual Rva005C3F02 *fetch();
};
class Rva00568021Holder
{
public:
	char m_pad[0x234];
	int m_beginVal;
	int m_endVal;
};
class Rva00568021
{
public:
	void rva00568021();
private:
	char m_pad00[8];
	Rva00005C357FPtrChaseField *m_p08;
	Rva00568021Fetcher *m_p0C;
	char m_pad10[4];
	Rva00568021Holder *m_p14;
};
void Rva00568021::rva00568021()
{
	Rva005C3F02 *dst = m_p0C->fetch();
	if (!dst)
		return;
	int id = m_p08->get();
	Object *obj = TheGameLogic->findObjectByID((ObjectID)id);
	if (obj) {
		if (!ThePlayerList)
			return;
		if (!((Rva005C38EChecker *)ThePlayerList)->Check(obj))
			return;
	}
	if (((Rva0057C22FByteChaseField *)dst)->get() == 0) {
		int endVal = m_p14->m_endVal;
		int *pBegin = (int *)((char *)m_p14 + 0x234);
		int count = (endVal - *pBegin) >> 2;
		for (int i = 0; i < count; ++i) {
			if (((Rva00005C39A3PtrChaseField *)dst)->get() >= 3)
				break;
			Rva005677B9::Payload payload;
			payload.v[0] = (int)this;
			int v = ((Rva0035B6B8 *)m_p14)->rva0035B6B8(i);
			payload.v[1] = v;
			Rva00567B6DAdd(dst, &payload);
		}
		((Rva005C3EE0 *)dst)->rva005C3EE0();
	}
	else {
		((Rva005C39AA *)dst)->rva005C39AA();
	}
}
