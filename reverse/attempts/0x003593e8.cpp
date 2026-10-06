// ?rva003593E8@Rva003593E8@@QAE_NABVAsciiString@@_N@Z
// partial score=0.6268 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /arch:SSE2 /MD /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
// ?rva003593E8@Rva003593E8@@QAE_NABVAsciiString@@_N@Z @0x003593E8 366B evidence: chain from 0x00358ACB; TheGameLogic isGamePaused plus TheInGameUI 0x15 0x16 plus vtable 0x17c gates; lower then upper map finds at +0xc +0x18 via rowed 0x1F8437; virtuals +4 +8 +0xc plus audio 0x358A53 0x358ACB
#include <map>
#include <stdlib.h>

#include "ascii_string.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

typedef _STL::map<AsciiString, AsciiString> AsciiMap;

class GameLogic
{
public:
	unsigned char isGamePaused();
};

extern GameLogic *TheGameLogic;

class InGameUI
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
	virtual void s34();
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
	virtual void s57();
	virtual void s58();
	virtual void s59();
	virtual void s60();
	virtual void s61();
	virtual void s62();
	virtual void s63();
	virtual void s64();
	virtual void s65();
	virtual void s66();
	virtual void s67();
	virtual void s68();
	virtual void s69();
	virtual void s70();
	virtual void s71();
	virtual void s72();
	virtual void s73();
	virtual void s74();
	virtual void s75();
	virtual void s76();
	virtual void s77();
	virtual void s78();
	virtual void s79();
	virtual void s80();
	virtual void s81();
	virtual void s82();
	virtual void s83();
	virtual void s84();
	virtual void s85();
	virtual void s86();
	virtual void s87();
	virtual void s88();
	virtual void s89();
	virtual void s90();
	virtual void s91();
	virtual void s92();
	virtual void s93();
	virtual void s94();
	virtual bool s95();
	char m_pad[0x11];
	unsigned char m_15;
	unsigned char m_16;
};

extern InGameUI *TheInGameUI;

class Entry
{
public:
	virtual ~Entry();
	virtual bool f1(bool v);
	virtual bool f2(bool v);
	virtual bool f3(bool v);
};

void Rva00358A53Play();
void Rva00358ACBPlay();

class Rva003593E8
{
public:
	bool rva003593E8(const AsciiString &key, bool val);
private:
	char m_00[12];
	AsciiMap m_0c;
	AsciiMap m_18;
};

// ?rva003593E8@Rva003593E8@@QAE_NABVAsciiString@@_N@Z present-unmatched
bool Rva003593E8::rva003593E8(const AsciiString &key, bool val)
{
	if (TheGameLogic->isGamePaused() || TheInGameUI->m_15 == 0 || TheInGameUI->m_16 == 0 || TheInGameUI->s95())
		return false;
	AsciiString tmp(key);
	tmp.toLower();
	Entry *obj = 0;
	bool needAcb = false;
	{
		AsciiMap::iterator it = m_0c.find(tmp);
		Entry *e1;
		if (it != m_0c.end()) {
			Entry *t = *(Entry **)&it->second;
			e1 = t;
		}
		else
			e1 = 0;
		if (e1 == 0) {
			_ReadWriteBarrier();
			AsciiMap::iterator it2 = m_18.find(tmp);
			Entry *e2;
			if (it2 == m_18.end())
				e2 = 0;
			else {
				Entry *t2 = *(Entry **)&it2->second;
				e2 = t2;
			}
			if (e2 == 0)
				goto upper;
			obj = e2;
		}
		else
			obj = e1;
	}
	if (obj->f1(val))
		goto upper;
	if (obj->f2(val))
		goto third;
	needAcb = true;
	goto upper;
upper:
	tmp.toUpper();
	{
		AsciiMap::iterator itu = m_0c.find(tmp);
		Entry *e3;
		if (itu == m_0c.end())
			e3 = 0;
		else {
			Entry *t3 = *(Entry **)&itu->second;
			e3 = t3;
		}
		if (e3 == 0) {
			AsciiMap::iterator itu2 = m_18.find(tmp);
			Entry *e4;
			if (itu2 == m_18.end())
				e4 = 0;
			else {
				Entry *t4 = *(Entry **)&itu2->second;
				e4 = t4;
			}
			if (e4 == 0)
				goto check;
			obj = e4;
		}
		else
			obj = e3;
	}
	if (obj->f1(val))
		goto check;
	if (!obj->f2(val))
		goto playAcb;
third:
	if (obj->f3(val)) {
		Rva00358A53Play();
		return true;
	}
	return true;
check:
	if (!needAcb)
		return false;
playAcb:
	Rva00358ACBPlay();
	return false;
}
