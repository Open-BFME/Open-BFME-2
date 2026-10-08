// cl: /G7 /arch:SSE /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// BannerUI::ParseBannerTypeInfo, retail 0x00217194 (94B), from the WorldBuilder
// lead (BannerUI.cpp): an INI block parser that takes the banner type name
// token, finds or creates its info in the banner UI singleton's type table
// (g_00DFE32C +0x0C, 0x00216F91) and parses the block into it with the
// banner-type field table at 0x00BE5A50 (INI::initFromINI).
//
// Target facts: the type table, its lookup and the info record keep
// address-derived names; the field table is referenced by address.

#include "ascii_string.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const FieldParse *parseTable);
};

class Rva00217194Types
{
public:
	void *rva00216F91(const AsciiString &name);
};

class Rva00217194BannerUI
{
public:
	Rva00217194Types *getTypes() { return &m_types; }

private:
	unsigned char m_pad00[0x0C];
	Rva00217194Types m_types;
};
extern Rva00217194BannerUI *g_00DFE32C;

extern const FieldParse g_00BE5A50[];


struct Rva0041534BIter {void *m_node;void *m_table;};
class Rva00056F61 {
public:
 __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *);
 __declspec(nothrow) void *rva00056F61(const AsciiString *);
 void *unused;void **begin,**end,**capacity;unsigned count;
};

class BannerUI
{
public:
	static void ParseBannerTypeInfo(INI *ini);
 void init();
 const AsciiString &GetBannerIconImageName(const AsciiString &key);
private:
 unsigned char m_pad00[0x0C];
 Rva00056F61 m_types;
 unsigned char m_unmodelled20[4];
 int m_windowIndex;
};

void BannerUI::ParseBannerTypeInfo(INI *ini)
{
	void *info;
	{
		AsciiString name(ini->getNextToken());
		info = g_00DFE32C->getTypes()->rva00216F91(name);
	}
	ini->initFromINI(info, g_00BE5A50);
}

// WB B6E990 names GetBannerIconImageName. Native216F3B..216F91 RET4
// looks up the type table at+C, retries BannerMen, then returns string+10
// in the node or TheEmptyString. The reference interface is inferred from
// that stable returned string and pointer-equivalent native argument ABI.
const AsciiString &BannerUI::GetBannerIconImageName(const AsciiString &key) {
 Rva0041534BIter it=m_types.rva0041534B(&key);
 void *node=it.m_node;
 if(!node) {
  {
   AsciiString fallback("BannerMen");
   node=m_types.rva00056F61(&fallback);
   // Retail retains this owner update in the exposed iterator slot before
   // releasing the temporary fallback key; its node result stays separate.
   it.m_table=&m_types;
  }
  if(!node)return AsciiString::TheEmptyString;
 }
 return *(const AsciiString*)((char*)node+0x10);
}

// Native216F91..217031 constructs a12-byte three-string default value and
// a16-byte key/value record. Existing21613D copy and2160C4/216108 cleanup
// prove those layouts independently; application field names remain unknown.
class Rva002160C4 {public:~Rva002160C4();};
class Rva00216108 {public:~Rva00216108();};
class Gen_003A8BE0 {
 unsigned int m_words[3];
public:
 __forceinline Gen_003A8BE0(){m_words[0]=0;m_words[1]=0;m_words[2]=0;}
 Gen_003A8BE0(const Gen_003A8BE0 &);
 __forceinline ~Gen_003A8BE0(){((Rva002160C4*)this)->~Rva002160C4();}
};
namespace _STL {
template<class A,class B>struct pair;
template<>struct pair<const AsciiString,Gen_003A8BE0> {
 pair(const AsciiString &,const Gen_003A8BE0 &);
 __forceinline ~pair(){((Rva00216108*)this)->~Rva00216108();}
 union {unsigned int m_alignment;unsigned char m_native[16];};
};
}
typedef _STL::pair<const AsciiString,Gen_003A8BE0> BannerTypePair;
class Rva000427195 {public:BannerTypePair *rva00216D5C(const BannerTypePair &);};
void *Rva00217194Types::rva00216F91(const AsciiString &name) {
 void *node;
 {Rva0041534BIter it=((Rva00056F61 *)this)->rva0041534B(&name);node=it.m_node;}
 return !node ? (char*)((Rva000427195*)this)->rva00216D5C(
  BannerTypePair(name,Gen_003A8BE0()))+4 : (char*)node+8;
}

// BFME1 BannerUI::init at donor ba7ddda is the semantic lead. BFME2 WB
// B6D600 and native216035..216094 prove the guard, slot20, two by-value
// strings, two zero arguments, and returned window index at+24. BFME1's
// third argument and separate callback registration are absent in BFME2.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class BannerWindowLoader {
public:
 virtual void unusedSlot0()=0;
 virtual void unusedSlot1()=0;
 virtual void unusedSlot2()=0;
 virtual void unusedSlot3()=0;
 virtual void unusedSlot4()=0;
 virtual void unusedSlot5()=0;
 virtual void unusedSlot6()=0;
 virtual void unusedSlot7()=0;
 virtual void unusedSlot8()=0;
 virtual void unusedSlot9()=0;
 virtual void unusedSlot10()=0;
 virtual void unusedSlot11()=0;
 virtual void unusedSlot12()=0;
 virtual void unusedSlot13()=0;
 virtual void unusedSlot14()=0;
 virtual void unusedSlot15()=0;
 virtual void unusedSlot16()=0;
 virtual void unusedSlot17()=0;
 virtual void unusedSlot18()=0;
 virtual void unusedSlot19()=0;
 virtual int loadWindow(AsciiString directory,AsciiString movie,int arg1,int arg2)=0;
};
void BannerUI::init() {
 if(g_00DFE32C)
  m_windowIndex=((BannerWindowLoader*)g_bfmeAptWindowManager)->loadWindow("Apt\\","BannerUI.apt",0,0);
}
