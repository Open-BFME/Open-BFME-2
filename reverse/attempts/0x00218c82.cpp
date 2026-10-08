// ?ParseFontDefaultSettings@FontLibrary@@SAXPAVINI@@@Z
// partial score=0.88416 date=2026-10-08
// cl: /O1 /G7 /MD /EHsc /arch:SSE2 /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include "ascii_string.h"
#include <map>
struct FieldParse;
extern const FieldParse FontDefaultSettingsFieldParse[];
extern const void *FontDefaultSettingsVtable[];
class INIException {public:INIException(int,const char*,...);INIException(const INIException&);~INIException();private:char *message;int count;};
class INI {public:AsciiString getNextQuotedAsciiString();const char*getNextTokenOrNull(const char*);void initFromINI(void*,const FieldParse*);};
extern "C" double (__cdecl * const _imp__atof)(const char*);
struct TargetRef00217D4C {virtual void *destroy(unsigned);int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct TreeHintRef00217D4C {TargetRef00217D4C *m_ptr;TreeHintRef00217D4C(TargetRef00217D4C *p):m_ptr(p){if(p)++p->references;}TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C&);__forceinline ~TreeHintRef00217D4C(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}};
struct FontSettingsOwner {TargetRef00217D4C *m_ptr;FontSettingsOwner(TargetRef00217D4C *p):m_ptr(p){if(p)++p->references;}__forceinline ~FontSettingsOwner(){ReleaseTreeHintRef00217D4C(m_ptr);}};
struct TreeHintRef00218787 {TargetRef00217D4C *m_ptr;};
namespace _STL {template<> TreeHintRef00217D4C &map<AsciiString,TreeHintRef00217D4C>::operator[](const AsciiString&);template<> TreeHintRef00218787 &map<int,TreeHintRef00218787>::operator[](const int&);}
struct Rva002BED91 {TargetRef00217D4C *m_ptr;void set(TargetRef00217D4C*);};
class Rva002186EB {public:Rva002186EB();const void *vtable;int references;TreeHintRef00218787 defaults;_STL::map<int,TreeHintRef00218787> sizes;};
struct FontDefaultSettings {const void *vtable;int references;bool antialiased;FontDefaultSettings():references(0){vtable=FontDefaultSettingsVtable;}};
class FontLibrary {public:static void ParseFontDefaultSettings(INI*);char prefix[0x14];_STL::map<AsciiString,TreeHintRef00217D4C> names;};
extern FontLibrary *TheFontLibrary;
void FontLibrary::ParseFontDefaultSettings(INI *ini)
{
 AsciiString name=ini->getNextQuotedAsciiString();
 union{float pointSize;int size;};pointSize=-1.f;
 const char *token=ini->getNextTokenOrNull(0);
 if(token){pointSize=(float)_imp__atof(token);if(pointSize<=0.f)throw INIException(3,"Invalid font point size specified: %f.  Must be greater than or equal to 1",pointSize);}
 FontSettingsOwner settings((TargetRef00217D4C*)new FontDefaultSettings);
 ((FontDefaultSettings*)settings.m_ptr)->antialiased=true;
 ini->initFromINI(settings.m_ptr,FontDefaultSettingsFieldParse);
 TreeHintRef00217D4C &nameSlot=TheFontLibrary->names[name];
 if(!nameSlot.m_ptr)((Rva002BED91*)&nameSlot)->set((TargetRef00217D4C*)new Rva002186EB);
 Rva002186EB *table=(Rva002186EB*)nameSlot.m_ptr;
 if(pointSize>=0.f){size=(int)pointSize;*(TreeHintRef00217D4C*)&table->sizes[size]=*(const TreeHintRef00217D4C*)&settings;}
 else *(TreeHintRef00217D4C*)&table->defaults=*(const TreeHintRef00217D4C*)&settings;
}
