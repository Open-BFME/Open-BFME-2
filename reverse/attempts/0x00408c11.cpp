// ?DoXfer@CreateAHeroHero@@QAEXAAVXfer@@@Z
// partial score=0.85 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// WB107D500 identifies CreateAHeroHero::DoXfer. Native408C11..4091E2
// supplies all offsets, version gates, helper ABI and tagged serialization.
// No clean BFME1 or ZH hero donor; layout corroborated by CreateAHeroData copy.
// UNMATCHED: 1484 compiled vs1489 native. Xfer/tag register and stack packing differ.
// WB107B660 CRC constructor clears byte0 then word0 then byte4; this view
// models final initialized state but does not yet reproduce that native sequence.
// Unresolved helper408A55 is444B file I/O;4074CF is pinned212B file writer
// without a rowed provider. These dependencies must be recovered before landing.
#include "ascii_string.h"
#include "unicode_string.h"
#include <map>
class Xfer { public:
virtual void slot00();
virtual bool load();
virtual bool save();
virtual bool checksum();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void version(void *);
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void text(AsciiString *);
virtual void slot28();
virtual void slot29();
virtual void word(unsigned *);
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
};
enum ObjectID { INVALID_ID=0 };
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString &); const AsciiString &keyToName(NameKeyType); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Rva00407137;
class Rva004071AAVirt;
class Rva00406FBF { public: unsigned crc; bool flag; Rva00406FBF() : crc(0),flag(false) {} };
void Rva00407099Update(Xfer *,ObjectID *,void *,Rva00406FBF *);
void Rva004071AAForward(Rva004071AAVirt *,const UnicodeString &,int,Rva00407137 *);
void Rva0040707EUpdate(void *,void *,void *,Rva00406FBF *);
void Rva004070B6Update(void *,void *,void *,Rva00406FBF *);
void Rva0040718FForward(void *,const AsciiString &,int,Rva00407137 *);
class Rva00407218 { public: void rva00407218(void *,void *); };
class Rva00407C6B { public: void rva00407C6B(); };
class Rva00407E28 { public: bool rva00407E53(int); bool rva00407DE0(int,int); };
class Rva00408A55 { public: void rva00408A55(); };
class CreateAHeroData { public: bool WriteNamedHeroAtRva004074CF(); };
class HeroTransferLog { public:
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
virtual HeroTransferLog *message(const char *);
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void severity(int);
};
class Debug { public:
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
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual HeroTransferLog *record(int,int,int);
};
extern Debug *theDebug;
void _bfme_debugRecordCallsite(int);
struct HeroButtonRecord { AsciiString name; unsigned level,index; };
class CreateAHeroHero {
public: void DoXfer(Xfer &);
private:
    void *vtable; ObjectID id; UnicodeString name;
    unsigned classIndex,subClassIndex;
    _STL::map<int,int> bling14,bling20;
    unsigned primaryColor,secondaryColor,tertiaryColor,state;
    char opaque3C[12]; bool systemHero; char pad49[3]; AsciiString filename;
    char opaque50[32]; bool flag70,flag71; char opaque72[14];
    HeroButtonRecord buttons[15]; unsigned savedCRC,word138,word13C;
};
typedef char HeroLayoutCheck[sizeof(CreateAHeroHero)==0x140?1:-1];
void CreateAHeroHero::DoXfer(Xfer &xfer)
{
    if(xfer.checksum())return;
    Rva00406FBF crc;
    struct Version { unsigned char minimum,current; } version={1,8};
    xfer.version(&version);
    { AsciiString tag("ID"); Rva00407099Update(&xfer,&id,&tag,&crc); }
    { AsciiString tag("Name"); Rva004071AAForward((Rva004071AAVirt*)&xfer,name,(int)&tag,(Rva00407137*)&crc); }
    { AsciiString tag("ClassIndex"); Rva0040707EUpdate(&xfer,&classIndex,&tag,&crc); }
    { AsciiString tag("SubClassIndex"); Rva0040707EUpdate(&xfer,&subClassIndex,&tag,&crc); }
    unsigned dummy=0;
    { AsciiString tag("Dummy"); Rva0040707EUpdate(&xfer,&dummy,&tag,&crc); }
    { AsciiString tag("Dummy"); Rva0040707EUpdate(&xfer,&dummy,&tag,&crc); }
    { AsciiString tag("PrimaryColor"); Rva0040707EUpdate(&xfer,&primaryColor,&tag,&crc); }
    { AsciiString tag("SecondaryColor"); Rva0040707EUpdate(&xfer,&secondaryColor,&tag,&crc); }
    { AsciiString tag("TertiaryColor"); Rva0040707EUpdate(&xfer,&tertiaryColor,&tag,&crc); }
    for(unsigned i=0;i<15;++i)((Rva00407218*)&buttons[i])->rva00407218(&xfer,&crc);
    if(xfer.load()) {
        ((Rva00407C6B*)this)->rva00407C6B();
        unsigned count=0;
        { AsciiString tag("BlingCount"); Rva0040707EUpdate(&xfer,&count,&tag,&crc); }
        for(unsigned i=0;i<count;++i) {
            AsciiString group;
            { AsciiString tag("GroupName"); Rva0040718FForward(&xfer,group,(int)&tag,(Rva00407137*)&crc); }
            if(group.isNone() || group.isEmpty()) {
                _bfme_debugRecordCallsite(1); theDebug->slot24();
                theDebug->record(0,0,0)->message("Fatal error in CreateAHeroHero::DoXfer(Xfer& xfer). Invalid or empty bling group name.")->severity(1);
            }
            NameKeyType key=TheNameKeyGenerator->nameToKey(group);
            unsigned index=0;
            { AsciiString tag("BlingIndex"); Rva0040707EUpdate(&xfer,&index,&tag,&crc); }
            ((Rva00407E28*)this)->rva00407E53(key);
            ((Rva00407E28*)this)->rva00407DE0(key,index);
        }
    } else {
        unsigned count=bling14.size();
        { AsciiString tag("BlingCount"); Rva0040707EUpdate(&xfer,&count,&tag,&crc); }
        for(_STL::map<int,int>::iterator i=bling14.begin();i!=bling14.end();++i) {
            AsciiString group(TheNameKeyGenerator->keyToName((NameKeyType)i->first));
            if(group.isNone() || group.isEmpty()) {
                _bfme_debugRecordCallsite(1); theDebug->slot24();
                theDebug->record(0,0,0)->message("Fatal error in CreateAHeroHero::DoXfer(Xfer& xfer). Invalid or empty bling group name.")->severity(1);
            }
            { AsciiString tag("GroupName"); Rva0040718FForward(&xfer,group,(int)&tag,(Rva00407137*)&crc); }
            unsigned index=i->second;
            { AsciiString tag("BlingIndex"); Rva0040707EUpdate(&xfer,&index,&tag,&crc); }
        }
    }
    if(version.current>6) {
        xfer.text(&filename);
        if(flag70 && !filename.isEmpty()) {
            if(xfer.load())((Rva00408A55*)this)->rva00408A55();
            else if(xfer.save())((CreateAHeroData*)this)->WriteNamedHeroAtRva004074CF();
        }
    }
    if(version.current>7) {
        { AsciiString tag("IsSystemHero"); Rva004070B6Update(&xfer,&systemHero,&tag,&crc); }
        if(xfer.load()) { xfer.word(&savedCRC); flag71=crc.crc==savedCRC; }
        else { savedCRC=crc.crc; xfer.word(&savedCRC); }
    } else { flag71=true; savedCRC=crc.crc; }
    if(xfer.load())state=0x2ff;
}
