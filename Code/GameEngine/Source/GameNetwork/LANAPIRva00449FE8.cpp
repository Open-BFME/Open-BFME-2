// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs-c-
// ?rva00449FE8@LANAPI@@QAEXPAX@Z @0x00449FE8 231B evidence: vslot 17 of LANAPI vtable 0x0083E680; type-0x12 message via fillInLANMessage slot 0xe4 send via Rva004495A2; slots 0x88 0x100; wcsncpy game name; timeGetTime; state at +0x28
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

extern "C" __declspec(dllimport) WideChar *__cdecl wcsncpy(WideChar *, const WideChar *, unsigned int);
extern "C" __declspec(dllimport) unsigned int __stdcall timeGetTime();


class LANGameInfo2
{
public:
	virtual void s00();
};

struct LANMessage
{
	Int type;
	char pad04[0x1d8 - 4];
};

class LANAPI
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void v88(Int a, Int b, Int c);
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual void s43();
	virtual void s44();
	virtual void s45();
	virtual void s46();
	virtual void s47();
	virtual void s48();
	virtual void s49();
	virtual void s50();
	virtual void s51();
	virtual void s52();
	virtual void s53();
	virtual void s54();
	virtual void s55();
	virtual void s56();
	virtual void fillInLANMessage(LANMessage *msg);
	virtual void s58();
	virtual void s59();
	virtual void s60();
	virtual void s61();
	virtual void s62();
	virtual void s63();
	virtual LANGameInfo2 *v100();
	void Rva004495A2(LANMessage *msg, unsigned int addr);
	void rva00449FE8(void *arg);
private:
	char m_pad04[0x14 - 4];
	void *m_14;
	char m_pad18[0x28 - 0x18];
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
};

void LANAPI::rva00449FE8(void *arg)
{
	if (m_28 != 0)
	{
		v88(9, 0, 0);
		return;
	}
	volatile unsigned int *addr = (volatile unsigned int *)arg;
	if (*addr == 0 && *(unsigned short *)((char *)arg + 4) == 0)
	{
		v88(8, 0, 0);
		return;
	}
	m_34 = addr[0];
	m_38 = addr[1];
	LANMessage msg;
	msg.type = 0x12;
	fillInLANMessage(&msg);
	LANGameInfo2 *g1 = v100();
	*(int *)((char *)&msg + 0x1e) = *(int *)g1;
	LANGameInfo2 *g2 = v100();
	*(unsigned short *)((char *)&msg + 0x22) = *(unsigned short *)((char *)g2 + 4);
	const WideChar *name = (m_14 != 0) ? (const WideChar *)((char *)m_14 + 8) : (const WideChar *)L"";
	wcsncpy((WideChar *)((char *)&msg + 0x24), name, 0xa);
	((WideChar *)((char *)&msg + 0x24))[0xa] = 0;
	Rva004495A2(&msg, (unsigned int)arg);
	m_28 = 2;
	m_2c = timeGetTime() + m_30;
}
