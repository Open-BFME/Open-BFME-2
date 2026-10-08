// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva0052906BUpdate@@YAXH@Z @0x0052906B 197B
// Free Apt HeroRank updater: static "APT:RankLabel"/"APT:HeroRank" with guards,
// rank via TheGameText slot +0x40 into UnicodeString::format, then
// BfmeAptWindowManager::bfmeSetText through TheRva00222A8BTarget.
// Evidence: guard bits 1/2 with atexit, literals at 0x838988/0x86825C,
// rowed StringBase ctor 0x37BA0, rowed Unicode format 0x6CB660,
// pinned bfmeSetText 0x225301, rowed wide releaseBuffer 0x36E70,
// caller 0x00529130 passes one int and stores it at +0x10.
#include "ascii_string.h"

#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual const UnicodeString *fetchRank(const AsciiString &label, int a);
};

extern GameTextInterface *TheGameText;

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &value, bool b);
};

class Rva00222A8BTarget
{
	char m_pad;
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

void __cdecl Rva0052906BUpdate(int rank)
{
	static AsciiString s_rankLabel("APT:RankLabel");
	static AsciiString s_heroRank("APT:HeroRank");
	UnicodeString tmp;
	tmp.format(TheGameText->fetchRank(s_rankLabel, 0), rank);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(s_heroRank, tmp, false);
}
