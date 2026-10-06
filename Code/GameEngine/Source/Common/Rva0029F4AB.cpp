// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// ?rva0029F4AB@Rva0029F4AB@@QAEXXZ retail 0x0029F4AB 133B
// Window lookup for ControlBar.wnd:RightHUD plus partition clear and +0x5CC peer
// release. Evidence: string literal; TheWindowManager slot 0xF0; TheNameKeyGenerator
// nameToKey row; get row 0x00314046; friend_setPartitionData row; slot 0x1C release.
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindowManager
{
public:
	virtual void u00();
	virtual void u01();
	virtual void u02();
	virtual void u03();
	virtual void u04();
	virtual void u05();
	virtual void u06();
	virtual void u07();
	virtual void u08();
	virtual void u09();
	virtual void u10();
	virtual void u11();
	virtual void u12();
	virtual void u13();
	virtual void u14();
	virtual void u15();
	virtual void u16();
	virtual void u17();
	virtual void u18();
	virtual void u19();
	virtual void u20();
	virtual void u21();
	virtual void u22();
	virtual void u23();
	virtual void u24();
	virtual void u25();
	virtual void u26();
	virtual void u27();
	virtual void u28();
	virtual void u29();
	virtual void u30();
	virtual void u31();
	virtual void u32();
	virtual void u33();
	virtual void u34();
	virtual void u35();
	virtual void u36();
	virtual void u37();
	virtual void u38();
	virtual void u39();
	virtual void u40();
	virtual void u41();
	virtual void u42();
	virtual void u43();
	virtual void u44();
	virtual void u45();
	virtual void u46();
	virtual void u47();
	virtual void u48();
	virtual void u49();
	virtual void u50();
	virtual void u51();
	virtual void u52();
	virtual void u53();
	virtual void u54();
	virtual void u55();
	virtual void u56();
	virtual void u57();
	virtual void u58();
	virtual void u59();
	virtual void *u60(int a, int b);
};

extern GameWindowManager *TheWindowManager;

class Rva00314046LeaField
{
public:
	void *get() const;
};

class PartitionData;

class Object
{
public:
	void friend_setPartitionData(PartitionData *partition);
};

class Rva0029F4ABPeer
{
public:
	virtual void p00();
	virtual void p01();
	virtual void p02();
	virtual void p03();
	virtual void p04();
	virtual void p05();
	virtual void p06();
	virtual void p07();
};

class Rva0029F4AB
{
public:
	void rva0029F4AB();

private:
	char _pad[0x5CC];
	Rva0029F4ABPeer *m_5CC;
};

void Rva0029F4AB::rva0029F4AB()
{
	void *win;
	{
		AsciiString tmp("ControlBar.wnd:RightHUD");
		win = TheWindowManager->u60(0, TheNameKeyGenerator->nameToKey(tmp));
	}
	Rva00314046LeaField *field = (Rva00314046LeaField *)win;
	Object *obj = (Object *)field->get();
	obj->friend_setPartitionData((PartitionData *)0);
	if (m_5CC != 0)
	{
		m_5CC->p07();
		m_5CC = 0;
	}
}
