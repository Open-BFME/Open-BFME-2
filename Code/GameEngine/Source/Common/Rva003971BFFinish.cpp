// cl: /DNDEBUG /MD
//
// ?rva003971BF@Rva003971BF@@QAE_NPAUArg3971BF@@@Z, retail 0x003971BF, 121 bytes.
// Count loop over ObjectID ranges at +0x50/+0x74 via rowed findObjectByID,
// rowed rva0028BCF4 and slot-3 bool. Evidence: callers 0x003BE400 0x003C677C,
// TheGameLogic 0x009FE78C, GameLogic::findObjectByID 0x00049DC5.

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;
class GameLogic;
extern GameLogic *TheGameLogic; // ?TheGameLogic@@3PAVGameLogic@@A

class Iface3971BF
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual bool s3();
};

struct Tmpl3971BF
{
	char m_pad[0x11A];
	unsigned char m_flag11A;
};

class Object
{
public:
	void *rva0028BCF4() const;
	void *m_pad00;
	Tmpl3971BF *m_template04;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

struct Arg3971BF
{
	char m_pad[0x110];
	unsigned char m_flag110;
};

class Rva003971BF
{
public:
	bool rva003971BF(Arg3971BF *arg);
private:
	char m_pad00[0x34];
	int m_34;
	char m_pad38[0x50 - 0x38];
	ObjectID *m_begin50;
	ObjectID *m_end54;
	char m_pad58[0x74 - 0x58];
	ObjectID *m_begin74;
	ObjectID *m_end78;
};

bool Rva003971BF::rva003971BF(Arg3971BF *arg)
{
	if (m_34 != 4)
		return false;
	ObjectID **range = reinterpret_cast<ObjectID **>(&m_begin50);
	if (arg != 0 && (arg->m_flag110 & 1) != 0) {
		ObjectID **r = reinterpret_cast<ObjectID **>(&m_begin74);
		unsigned n = (unsigned)(r[1] - r[0]);
		if (n > 0)
			range = r;
	}
	for (ObjectID *p = range[0]; p != range[1]; ++p)
	{
		Object *obj = TheGameLogic->findObjectByID(*p);
		if (obj == 0)
			continue;
		if ((obj->m_template04->m_flag11A & 0x40) != 0)
			continue;
		void *iface = obj->rva0028BCF4();
		if (iface == 0)
			continue;
		if (!static_cast<Iface3971BF *>(iface)->s3())
			return true;
	}
	return false;
}
