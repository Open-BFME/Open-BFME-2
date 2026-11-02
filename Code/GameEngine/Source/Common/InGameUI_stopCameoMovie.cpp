// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// InGameUI::stopCameoMovie, primary vtable slot 91.
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../Include/Common/NameKeyGenerator.h"

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

#include "../GameLogic/Object/object.h"

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

class InGameUI
{
public:
	virtual ~InGameUI();
#define SLOT(N) virtual void slot##N();
	SLOT(001) SLOT(002) SLOT(003) SLOT(004) SLOT(005) SLOT(006) SLOT(007) SLOT(008)
	SLOT(009) SLOT(010) SLOT(011) SLOT(012) SLOT(013) SLOT(014) SLOT(015) SLOT(016)
	SLOT(017) SLOT(018) SLOT(019) SLOT(020) SLOT(021) SLOT(022) SLOT(023) SLOT(024)
	SLOT(025) SLOT(026) SLOT(027) SLOT(028) SLOT(029) SLOT(030) SLOT(031) SLOT(032)
	SLOT(033) SLOT(034) SLOT(035) SLOT(036) SLOT(037) SLOT(038) SLOT(039) SLOT(040)
	SLOT(041) SLOT(042) SLOT(043) SLOT(044) SLOT(045) SLOT(046) SLOT(047) SLOT(048)
	SLOT(049) SLOT(050) SLOT(051) SLOT(052) SLOT(053) SLOT(054) SLOT(055) SLOT(056)
	SLOT(057) SLOT(058) SLOT(059) SLOT(060) SLOT(061) SLOT(062) SLOT(063) SLOT(064)
	SLOT(065) SLOT(066) SLOT(067) SLOT(068) SLOT(069) SLOT(070) SLOT(071) SLOT(072)
	SLOT(073) SLOT(074) SLOT(075) SLOT(076) SLOT(077) SLOT(078) SLOT(079) SLOT(080)
	SLOT(081) SLOT(082) SLOT(083) SLOT(084) SLOT(085) SLOT(086) SLOT(087) SLOT(088)
	SLOT(089) SLOT(090)
#undef SLOT
	virtual void stopCameoMovie();

private:
	char _pad[0x5CC - 4];
	Rva0029F4ABPeer *m_5CC;
};

// Resolve ControlBar.wnd:RightHUD through TheWindowManager and TheNameKeyGenerator.
// Clear its window data, then release and null the stream at +0x5CC through slot 7.
void InGameUI::stopCameoMovie()
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
