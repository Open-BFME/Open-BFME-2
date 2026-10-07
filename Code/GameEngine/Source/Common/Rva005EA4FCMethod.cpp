// cl: /O1 /MD
// Range-34 dump lane: 61B plain method at 0x005EA4FC (ret).
// Runs virtual slot 0x1C on the +8 member's +0x14 subobject; on true,
// creates message 0x6BE through Glo00A00950 slot 0x48, appends the +0xC
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

extern GlobalHolder* Glo00A00950;

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
	GameMessage *msg = Glo00A00950->newMessage(0x6BE);
	msg->appendIntegerArgument(m08->m0c->m34);
	m08->rva005EA136();
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?Glo00A00950@@3PAVGlobalHolder@@A=?MessageStreamSubsystem@@3PAVMessageStream@@A")
