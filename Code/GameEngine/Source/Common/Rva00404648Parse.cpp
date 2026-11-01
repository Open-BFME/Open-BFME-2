// cl: /O1 /G7 /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native00404648..00404715 and WB00E90D60 prove the attribute-name lookup,
// percent-or-real scan, appended string list and vector update. Method identity
// is unknown. The store pointer's type follows its registered initializer;
// its lookup is a receiver-ignoring member, established by this call site.
// Existing record ctor and update provider establish the 20B record layout.
// Retail imports strchr directly; retain CRT import linkage for string.h only.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include <vector>
#include "ascii_string.h"
#include "Common/INIException.h"

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}
class Rva0040394A {public:Rva0040394A();int m_id;float m_val;_STL::vector<AsciiString>m_strs;};
class Rva004045B4 {public:void rva004045B4(int,float,const _STL::vector<AsciiString>*);};
#include "../../Include/Common/INI/INI.h"
class Rva0022B46BSubsystem {public:int rva004030EF(const char*);};
class AttributeModifierStore;
extern AttributeModifierStore*TheAttributeModifierStore;
void Rva00404648Parse(INI*ini,Rva004045B4*store){
 const char*token=ini->getNextToken(0);Rva0040394A value;
 value.m_id=((Rva0022B46BSubsystem*)TheAttributeModifierStore)->rva004030EF(token);
 if(value.m_id==0)throw INIException(3,"Attribute '%s' not found",token);
 token=ini->rva0002DFE2(0,0);
 value.m_val=strchr(token,'%')?ini->dup_002EE10(token):ini->scanReal(token);
 INI::parseAsciiStringVectorAppend(ini,store,&value.m_strs,0);
 store->rva004045B4(value.m_id,value.m_val,&value.m_strs);
}
