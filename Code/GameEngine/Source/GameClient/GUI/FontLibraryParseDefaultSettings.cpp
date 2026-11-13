// cl: /O1 /G7 /MD /EHsc /arch:SSE2 /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include "ascii_string.h"
#include <map>
class INI;
#include "../../../Include/Common/INI/FieldParse.h"
// The settings object is Rva00217497 (ctor 0x00217497, RvaSmallVtableCtors.cpp):
// the inline ctor stores that class's vftable 0x007E5AA8 (data ledger
// ??_7Rva00217497) and clears the count, as the rowed ctor does.
extern "C" const void *const __identifier("??_7Rva00217497@@6B@")[];
#include "../../../Include/Common/INI/INI.h"
// Retail's one-entry table at 0x007E5B30 (VA 0x00BE5B30) passed to initFromINI:
// "Antialiased" -> INI::parseBool (rowed 0x0002E850) at +8, then the null
// terminator.
extern const FieldParse FontDefaultSettingsFieldParse[2] = {
	{ "Antialiased", &INI::parseBool, 0, 8 },
	{ 0, 0, 0, 0 },
};
extern "C" double (__cdecl * const _imp__atof)(const char*);
#include "../../../../Libraries/Source/Apt/AptRefTarget.h"
__forceinline TreeHintRef00217D4C::~TreeHintRef00217D4C() {if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
inline __declspec(noinline) TreeHintRef00217D4C &TreeHintRef00217D4C::operator=(const TreeHintRef00217D4C &other) { if (this != &other) { if (other.m_ptr) ++other.m_ptr->references; if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); m_ptr = other.m_ptr; } return *this; }
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);

struct FontSettingsOwner {TargetRef00217D4C *m_ptr;FontSettingsOwner(TargetRef00217D4C *p):m_ptr(p){if(p)++p->references;}__forceinline ~FontSettingsOwner(){ReleaseTreeHintRef00217D4C(m_ptr);}};
struct TreeHintRef00218787 {TargetRef00217D4C *m_ptr;};
namespace _STL {template<> TreeHintRef00217D4C &map<AsciiString,TreeHintRef00217D4C>::operator[](const AsciiString&);template<> TreeHintRef00218787 &map<int,TreeHintRef00218787>::operator[](const int&);}
#include "../../../Include/Common/Rva002BED91.h"
class Rva002186EB {public:Rva002186EB();const void *vtable;int references;TreeHintRef00218787 defaults;_STL::map<int,TreeHintRef00218787> sizes;};
struct FontDefaultSettings {const void *vtable;int references;bool antialiased;FontDefaultSettings():references(0){vtable=__identifier("??_7Rva00217497@@6B@");}};
#include "../../../Include/GameClient/FontLibrary.h"
extern FontLibrary *TheFontLibrary;
void FontLibrary::ParseFontDefaultSettings(INI *ini)
{
 AsciiString name=ini->getNextQuotedAsciiString();
 union{float pointSize;int size;};pointSize=-1.f;
 const char *token=ini->getNextTokenOrNull(0);
 if(token){pointSize=(float)_imp__atof(token);if(pointSize<=0.f)throw INIException(3,"Invalid font point size specified: %f.  Must be greater than or equal to 1",pointSize);}
 TreeHintRef00217D4C settings((TargetRef00217D4C*)new FontDefaultSettings);
 ((FontDefaultSettings*)settings.m_ptr)->antialiased=true;
 ini->initFromINI(settings.m_ptr,FontDefaultSettingsFieldParse);
 TreeHintRef00217D4C &nameSlot=
  (*reinterpret_cast<_STL::map<AsciiString,TreeHintRef00217D4C> *>(TheFontLibrary->field14))[name];
 if(!nameSlot.m_ptr)((Rva002BED91*)&nameSlot)->set((TargetRef00217D4C*)new Rva002186EB);
 Rva002186EB *table=(Rva002186EB*)nameSlot.m_ptr;
 if((ini ? (pointSize>=0.f) : (pointSize>=0.f))){size=(int)pointSize;*(TreeHintRef00217D4C*)&table->sizes[size]=settings;}
 else *(TreeHintRef00217D4C*)&table->defaults=settings;
}
