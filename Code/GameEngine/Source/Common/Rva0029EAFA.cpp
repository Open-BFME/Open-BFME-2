// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// ?rva0029EAFA@Rva0029EAFA@@QAEXPBVGameMessage@@@Z @0x0029EAFA 232B
// evidence: chain from 0x0029DE76; rowed GameMessage::getArgument plus Object::isMobile plus InGameUI::expireAllHints
#include "../../../Libraries/Include/Lib/Coord3D.h"

union GameMessageArgumentType
{
	int integer;
	float real;
	int boolean;
	int objectID;
	int drawableID;
	unsigned int teamID;
	struct Loc { float x; float y; float z; } location;
	struct Pix { int x; int y; } pixel;
	struct PixReg { int loX; int loY; int hiX; int hiY; } pixelRegion;
	unsigned int timestamp;
	unsigned short wChar;
};

#include "../../Include/Common/MessageStream.h"

struct ObjList;
class Rva0029DE76
{
public:
	bool rva0029DE76(const Coord3D *pos);
	virtual void dummy00();
	virtual void dummy01();
	virtual void dummy02();
	virtual void dummy03();
	virtual void dummy04();
	virtual void dummy05();
	virtual void dummy06();
	virtual void dummy07();
	virtual void dummy08();
	virtual void dummy09();
	virtual void dummy10();
	virtual void dummy11();
	virtual void dummy12();
	virtual void dummy13();
	virtual void dummy14();
	virtual void dummy15();
	virtual void dummy16();
	virtual void dummy17();
	virtual void dummy18();
	virtual void dummy19();
	virtual void dummy20();
	virtual void dummy21();
	virtual void dummy22();
	virtual void dummy23();
	virtual void dummy24();
	virtual void dummy25();
	virtual void dummy26();
	virtual void dummy27();
	virtual void dummy28();
	virtual void dummy29();
	virtual void dummy30();
	virtual void dummy31();
	virtual void dummy32();
	virtual void dummy33();
	virtual void dummy34();
	virtual void dummy35();
	virtual void dummy36();
	virtual void dummy37();
	virtual void dummy38();
	virtual void dummy39();
	virtual void dummy40();
	virtual void dummy41();
	virtual void dummy42();
	virtual void dummy43();
	virtual void dummy44();
	virtual void dummy45();
	virtual void dummy46();
	virtual void dummy47();
	virtual void dummy48();
	virtual void dummy49();
	virtual void dummy50();
	virtual void dummy51();
	virtual void dummy52();
	virtual void dummy53();
	virtual void dummy54();
	virtual void dummy55();
	virtual void dummy56();
	virtual void dummy57();
	virtual void dummy58();
	virtual void dummy59();
	virtual void dummy60();
	virtual void dummy61();
	virtual void dummy62();
	virtual void dummy63();
	virtual void dummy64();
	virtual void dummy65();
	virtual void dummy66();
	virtual void dummy67();
	virtual void dummy68();
	virtual void dummy69();
	virtual void dummy70();
	virtual void dummy71();
	virtual void dummy72();
	virtual ObjList *getObjList();
};

#include "../../Include/GameClient/InGameUI.h"

class Template108
{
public:
	char m_pad[0x108];
	unsigned char m_flags;
};

class Object
{
public:
	bool isMobile() const;
	void *m_vtable;
	Template108 *m_template;
	char m_pad08[0xfc - 8];
	Object *m_fc;
};

class ClientFrameSubsystem
{
public:
	virtual void c00();
	virtual void c01();
	virtual void c02();
	virtual void c03();
	virtual void c04();
	virtual void c05();
	virtual void c06();
	virtual void c07();
	virtual void c08();
	virtual void c09();
	virtual void c10();
	virtual void c11();
	virtual void c12();
	virtual void c13();
	virtual void c14();
	virtual void c15();
	virtual void c16();
	virtual void c17();
	virtual void c18();
	virtual void c19();
	virtual void c20();
	virtual void c21();
	virtual void c22();
	virtual void c23();
	virtual void c24();
	virtual void c25();
	virtual void c26();
	virtual void c27();
	virtual void c28();
	virtual void c29();
	virtual void c30();
	virtual int getValue();
};
class ClientFrameSubsystem; extern class GameClient *TheGameClient;

struct Elem0029
{
	Coord3D pos;
	int unk;
	unsigned char flag;
	char pad[3];
};

class Rva0029EAFA
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual void d16();
	virtual void d17();
	virtual void d18();
	virtual void d19();
	virtual void d20();
	virtual void d21();
	virtual void d22();
	virtual void d23();
	virtual void d24();
	virtual void d25();
	virtual void d26();
	virtual void d27();
	virtual void d28();
	virtual void d29();
	virtual void d30();
	virtual void d31();
	virtual void d32();
	virtual void d33();
	virtual void d34();
	virtual void d35();
	virtual void d36();
	virtual void d37();
	virtual void d38();
	virtual void d39();
	virtual void d40();
	virtual void d41();
	virtual void d42();
	virtual void d43();
	virtual void d44();
	virtual void d45();
	virtual void d46();
	virtual void d47();
	virtual void d48();
	virtual void d49();
	virtual void d50();
	virtual void d51();
	virtual void d52();
	virtual void d53();
	virtual void d54();
	virtual void d55();
	virtual void d56();
	virtual void d57();
	virtual void d58();
	virtual void d59();
	virtual void d60();
	virtual void d61();
	virtual void d62();
	virtual void d63();
	virtual void d64();
	virtual void d65();
	virtual void d66();
	virtual void d67();
	virtual void d68();
	virtual void d69();
	virtual int v118();
	virtual void e11c();
	virtual void e120();
	virtual void e124();
	virtual void e128();
	virtual Object *v12c();
	void rva0029EAFA(const GameMessage *msg);
private:
	char m_pad04[0x40 - 4];
	Elem0029 m_elems[25];
	int m_count;
};

void Rva0029EAFA::rva0029EAFA(const GameMessage *msg)
{
	if (v118() == 1)
	{
		Object *ret = v12c();
		Object *inner = ret ? ret->m_fc : (Object *)0;
		if (inner)
		{
			if ((inner->m_template->m_flags & 4) != 0)
				return;
			if (!inner->isMobile())
				return;
		}
	}
	const GameMessageArgumentType *gameMessageArgumentType = msg->getArgument(0);
	Coord3D pos;
	pos.x = gameMessageArgumentType->location.x;
	pos.y = gameMessageArgumentType->location.y;
	pos.z = gameMessageArgumentType->location.z;
	if (!((Rva0029DE76 *)this)->rva0029DE76(&pos))
		return;
	((InGameUI *)this)->expireAllHints(0);
	int v = ((ClientFrameSubsystem *)TheGameClient)->getValue();
	m_elems[m_count].unk = v;
	m_elems[m_count].pos = pos;
	m_elems[m_count].flag = 0;
	m_count++;
	if (m_count != 0x19)
		return;
	m_count = 0;
}
