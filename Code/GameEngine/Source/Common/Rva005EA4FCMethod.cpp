// cl: /O1 /MD /EHsc
// Range-34 dump lane: 61B plain method at 0x005EA4FC (ret).
// Runs virtual slot 0x1C on the +8 member's +0x14 subobject; on true,
// creates message 0x6BE through ((GlobalHolder*)MessageStreamSubsystem) slot 0x48, appends the +0xC
// subobject's +0x34 word through the rowed 0x0030F936, then tail-jumps to
// the pinned 0x005EA136 member method. Same global recipe as
// Rva002B2E77Finish.cpp. All identities unproven (address-derived).
class GameMessage
{
public:
	void appendIntegerArgument(int v);
};

class GlobalHolder
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17();
	virtual GameMessage* newMessage(int type);
};

// Bind to the existing data-ledger owner; keep the retail access view local.
class MessageStream;
extern MessageStream *MessageStreamSubsystem;

class Rva005EA4FCM14
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06();
	virtual bool v07();
};

struct Rva005EA4FCM0C
{
	char m_pad[0x34];
	int m34;
};

struct Rva005EA4FCM08
{
	char m_pad[0x0C];
	Rva005EA4FCM0C *m0c;
	int m_pad10;
	Rva005EA4FCM14 *m14;
	void rva005EA136();
};

class Rva005EA4FC
{
public:
	int m00;
	int m04;
	Rva005EA4FCM08 *m08;
	void rva005EA4FC();
};

void Rva005EA4FC::rva005EA4FC()
{
	if (!m08->m14->v07())
		return;
	GameMessage *msg = ((GlobalHolder*)MessageStreamSubsystem)->newMessage(0x6BE);
	msg->appendIntegerArgument(m08->m0c->m34);
	m08->rva005EA136();
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.

// Target 5EA136..5EA183 is the complete 77-byte factory tail called by
// 5EA4FC. Native allocation size16 and rowed constructor5E9FC1 establish
// the temporary's extent; constructor's member8 explains the remaining8.
// The receiver pointer is passed to that constructor, then installed in
// the existing member14 through the rowed pooled setter575674, followed
// by member14 virtual slot4. The pointer field is the setter's one-word
// access view; original subsystem and method identity remain unproven.
class Object;
class Rva00575674 {public:void rva00575674(Object *);};
class Rva005E9FC1 {
public:
Rva005E9FC1(void *);
virtual ~Rva005E9FC1();
private:char m_rest[12];
};
void Rva005EA4FCM08::rva005EA136() {
Rva005E9FC1 *replacement=new Rva005E9FC1(this);
((Rva00575674*)&m14)->rva00575674((Object*)replacement);
m14->v01();
}
