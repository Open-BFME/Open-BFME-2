// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva002DA414@Rva002DA414@@QAEPAXXZ @0x002DA414 77B: this+0x38 selects GameLogic vs GameClient lookup of id at +0x34 then common getControllingPlayer +0x54 else +0x6c.
// Evidence: callees findObjectByID 0x00049DC5 getControllingPlayer 0x0028AFA9; data TheGameLogic 0x009FE78C TheGameClient 0x009FE77C; caller 0x00053C13.
enum ObjectID
{
	ObjectID_Invalid = -1
};

class Object;
class Player;
class GameLogic;
class ClientFrameSubsystem;

class Player
{
public:
	char m_pad[0x54];
	void *m_ptr54;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class ClientHolder
{
public:
	char m_padFC[0xFC];
	Object *m_objFC;
};

class ClientFrameSubsystem
{
public:
	virtual void _u000();
	virtual void _u001();
	virtual void _u002();
	virtual void _u003();
	virtual void _u004();
	virtual void _u005();
	virtual void _u006();
	virtual void _u007();
	virtual void _u008();
	virtual void _u009();
	virtual void _u010();
	virtual void _u011();
	virtual void _u012();
	virtual void _u013();
	virtual void _u014();
	virtual void _u015();
	virtual ClientHolder *rva040(ObjectID id);
};

extern GameLogic *TheGameLogic;
class ClientFrameSubsystem; extern class GameClient *TheGameClient;

class Rva002DA414
{
public:
	void *rva002DA414();
private:
	char m_pad00[0x34];
	ObjectID m_id34;
	int m_type38;
	char m_pad3C[0x30];
	void *m_ptr6C;
};

void *Rva002DA414::rva002DA414()
{
	Object *obj;
	if (m_type38 == 2) {
		obj = TheGameLogic->findObjectByID(m_id34);
	} else if (m_type38 == 1) {
		ClientHolder *holder = ((ClientFrameSubsystem *)TheGameClient)->rva040(m_id34);
		if (holder == 0)
			return m_ptr6C;
		obj = holder->m_objFC;
	} else {
		return m_ptr6C;
	}
	if (obj == 0)
		return m_ptr6C;
	Player *player = obj->getControllingPlayer();
	return player->m_ptr54;
}
