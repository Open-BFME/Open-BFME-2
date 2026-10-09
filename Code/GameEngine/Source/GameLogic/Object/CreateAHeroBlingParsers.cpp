// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// Native block parsers21EAD3..21ECB1 (478B) and21ECB2..21EE36 (388B).
// Names remain address-derived: both blocks' messages mention the bling/binder
// role, but the separately owned4-argument binder callback21DEAD has that name.
// Reference sibling: Common/CreateAHeroParseBlingBinder.cpp (419B) establishes
// the shared AsciiString temporaries, cached NameKeyType and INIException idiom.
// Native tables DB9F18/DB9F68 establish labels, callback RVAs and all offsets;
// DB9D00 holds ATTRIBUTE/APPEARANCE/INVALID. The16B and20B record layouts and
// constructors are independently owned by StringRecordInlineCopyBFME2.cpp.
// StringBase::str() emits the target nullable-buffer+8 branch and a private
// zero character. AsciiString::str() instead keeps the empty literal in ESI,
// moving the pop and changing register allocation. End the two lookup outputs'
// lexical scope before throwing so their8B are reused by the exception.
// Static-key guards are emitted by the compiler; no address-bound aliases.
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class INI;
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
 static void parseStringAsNameKeyType(INI*,void*,void*,const void*);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class INI;
struct FieldParse {const char *name;void (*parse)(INI*,void*,void*,const void*);const void *user;unsigned offset;};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
 static void parseAsciiString(INI*,void*,void*,const void*);
 static void parseUnsignedInt(INI*,void*,void*,const void*);
 static void parseIndexList(INI*,void*,void*,const void*);
};

class INIException
{
public:
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &that);
	~INIException();
};

struct BfmeStringRecord00219A68 {
 unsigned word0;AsciiString text0,text1;unsigned word1,word2;
 BfmeStringRecord00219A68(unsigned,const AsciiString&,const AsciiString&,unsigned,unsigned);
 ~BfmeStringRecord00219A68();
};
class Rva0021EA74 {public:int rva0021EA74(const BfmeStringRecord00219A68&);};
class CreateAHeroManager;extern CreateAHeroManager *TheCreateAHeroManager;
static const char *BlingTypeNames[] = {"ATTRIBUTE","APPEARANCE","INVALID",0};
const FieldParse CreateAHeroBlingBinderFieldParse[] = {
 {"GroupName",NameKeyGenerator::parseStringAsNameKeyType,0,0},
 {"LabelTag",INI::parseAsciiString,0,4},
 {"DescriptionTag",INI::parseAsciiString,0,8},
 {"UISlot",INI::parseUnsignedInt,0,12},
 {"BlingType",INI::parseIndexList,BlingTypeNames,16},
 {0,0,0,0}
};
#define IS_EMPTY(s) (((const StringBase<char> *)&(s))->isEmpty())
void Rva0021ECB2Parse(INI *ini)
{
 BfmeStringRecord00219A68 binder(0,AsciiString("None"),AsciiString("None"),-1,2);
 ini->initFromINI(&binder,CreateAHeroBlingBinderFieldParse);
 unsigned groupKey=binder.word0;
 static NameKeyType noneKey=TheNameKeyGenerator->nameToKey("None");
 static NameKeyType emptyKey=TheNameKeyGenerator->nameToKey("");
 if(groupKey==NAMEKEY_INVALID || groupKey==(unsigned)noneKey || groupKey==(unsigned)emptyKey)
  throw INIException(3,"No group name specified  while parsing parseCreateAHeroBlingBinder.");
 if(binder.text0.isNone()||IS_EMPTY(binder.text0))
  throw INIException(3,"No LabelTag specified while parsing parseCreateAHeroBlingBinder.");
 if(binder.text1.isNone()||IS_EMPTY(binder.text1))
  throw INIException(3,"No DescTag specified while parsing parseCreateAHeroBlingBinder.");
 if(binder.word1==(unsigned)-1)
  throw INIException(3,"No UISlot specified while parsing parseCreateAHeroBlingBinder.");
 if(binder.word2==2)
  throw INIException(3,"No blingType specified while parsing parseCreateAHeroBlingBinder.");
 reinterpret_cast<Rva0021EA74*>(TheCreateAHeroManager)->rva0021EA74(binder);
}

struct BfmeStringRecord002199C8 {
 AsciiString text0,text1,text2;unsigned word;
 BfmeStringRecord002199C8(unsigned,const AsciiString&,const AsciiString&,const AsciiString&);
 ~BfmeStringRecord002199C8();
};
class UpgradeTemplate;
class UpgradeCenter {public:const UpgradeTemplate *findUpgrade(const AsciiString&)const;};
extern UpgradeCenter *TheUpgradeCenter;
class Rva0021E9D8Call {public:int rva0021EA59(void*);};
class CreateAHeroManager {
public:bool FindBlingByUpgradeName(const AsciiString&,int*,int*);
};
const FieldParse CreateAHeroBlingFieldParse[] = {
 {"BlingUpgradeName",INI::parseAsciiString,0,8},
 {"NameTag",INI::parseAsciiString,0,0},
 {"DescriptionTag",INI::parseAsciiString,0,4},
 {"GroupName",NameKeyGenerator::parseStringAsNameKeyType,0,12},
 {0,0,0,0}
};
void Rva0021EAD3Parse(INI *ini)
{
 BfmeStringRecord002199C8 bling(0,AsciiString("None"),AsciiString("None"),AsciiString("None"));
 ini->initFromINI(&bling,CreateAHeroBlingFieldParse);
 if(bling.text2.isNone()||IS_EMPTY(bling.text2))
  throw INIException(3,"No upgrade name specified while parsing CreateAHeroClass.");
 unsigned groupKey=bling.word;
 static NameKeyType noneKey=TheNameKeyGenerator->nameToKey("None");
 static NameKeyType emptyKey=TheNameKeyGenerator->nameToKey("");
 if(groupKey==NAMEKEY_INVALID||groupKey==(unsigned)noneKey||groupKey==(unsigned)emptyKey)
  throw INIException(3,"No group name specified  while parsing parseCreateAHeroBling.");
 if(!TheUpgradeCenter->findUpgrade(bling.text2))
  throw INIException(3,"Upgrade %s not found while parsing parseCreateAHeroBling.",reinterpret_cast<const StringBase<char>*>(&bling.text2)->str());
 bool found;
 {int index,key;found=TheCreateAHeroManager->FindBlingByUpgradeName(bling.text2,&index,&key);}
 if(found)
  throw INIException(3,"A Create-a-Hero Bling with the upgrade %s already exists.",reinterpret_cast<const StringBase<char>*>(&bling.text2)->str());
 reinterpret_cast<Rva0021E9D8Call*>(TheCreateAHeroManager)->rva0021EA59(&bling);
}
