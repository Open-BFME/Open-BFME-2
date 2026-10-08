// cl: /MD
// ?rva00271547@Rva002716Holder@@QAEXXZ retail 0x00271547 186 bytes.
// Holder+0x14c NULL-terminated module array shared with Rva002716Broadcast siblings.
// ThePlayerList local at +0x10 TheInGameUI slot 0x10C GameMessage 0x3ED.
// Evidence: caller 0x00271601 sets +0x43d then calls this; callees rowed getControllingPlayer appendObjectIDArgument.

extern class MessageStream *TheMessageStream;

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
public:
	unsigned char m_pre74[0x74];
	int m_objectID74;
};

enum ObjectID
{
	OBJECTID_Zero = 0
};

class GameMessage
{
public:
	void appendObjectIDArgument(ObjectID id);
};

class PlayerList;
extern PlayerList *ThePlayerList;

struct PlayerListView
{
	unsigned char m_pad[0x10];
	Player *m_local10;
};

struct MsgFactory
{
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *create(int id);
};

#define TheMsgFactory (*(MsgFactory **)&TheMessageStream)

struct Rva00271547Entry
{
	virtual void e00(); virtual void e01(); virtual void e02(); virtual void e03();
	virtual void e04(); virtual void e05(); virtual void e06(); virtual void e07();
	virtual void e08(); virtual void e09(); virtual void e10(); virtual void e11();
	virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15();
	virtual void apply(unsigned char flag);
	virtual void e17(); virtual void e18(); virtual void e19(); virtual void e20();
	virtual void e21(); virtual void e22(); virtual void e23(); virtual void e24();
	virtual void e25(); virtual void e26(); virtual void e27(); virtual void e28();
	virtual void e29(); virtual void e30(); virtual void e31(); virtual void e32();
	virtual void e33(); virtual void e34(); virtual void e35(); virtual void e36();
	virtual void e37(); virtual void e38(); virtual void e39(); virtual void e40();
	virtual void e41(); virtual void e42(); virtual void e43(); virtual void e44();
	virtual void e45(); virtual void e46(); virtual void e47(); virtual void e48();
	virtual void e49(); virtual void e50(); virtual void e51(); virtual void e52();
	virtual void e53(); virtual void e54(); virtual void e55(); virtual void e56();
	virtual void e57(); virtual void e58(); virtual void e59();
	virtual unsigned char check();
};

class Rva002716Holder;

struct InGameUIView
{
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66();
	virtual void dispatch(Rva002716Holder *holder);
};

class InGameUI;
extern InGameUI *TheInGameUI;

class Rva002716Holder
{
public:
	void rva00271547();
	void rva00271601(unsigned char val);
public:
	unsigned char m_preFC[0xFC];
	Object *m_objFC;
	unsigned char m_pad100[0x4C];
	Rva00271547Entry **m_array14C;
	unsigned char m_pad150[0x14];
	int m_164;
	unsigned char m_pad168[0x243];
	unsigned char m_3AB;
	unsigned char m_pad3AC[0x90];
	unsigned char m_43C;
	unsigned char m_43D;
	unsigned char m_43E;
};

void Rva002716Holder::rva00271547()
{
	unsigned char flag;
	if (m_43D == 0 && m_43E == 0)
		flag = 0;
	else {
		flag = 1;
		if (m_43C != 0) {
			if (m_objFC != 0) {
				Player *local = ((PlayerListView *)ThePlayerList)->m_local10;
				if (m_objFC->getControllingPlayer() == local) {
					MsgFactory *factory = TheMsgFactory;
					GameMessage *msg = factory->create(0x3ED);
					msg->appendObjectIDArgument((ObjectID)m_objFC->m_objectID74);
				((InGameUIView *)TheInGameUI)->dispatch(this);
				}
			}
		}
	}
	Rva00271547Entry **pp = m_array14C;
	while (*pp != 0) {
		if (m_3AB != 0 && m_164 == 5 && m_43E == 0)
			flag = (*pp)->check();
		(*pp)->apply(flag);
		++pp;
	}
}

void Rva002716Holder::rva00271601(unsigned char val)
{
	if (val == m_43D)
		return;
	m_43D = val;
	rva00271547();
}
