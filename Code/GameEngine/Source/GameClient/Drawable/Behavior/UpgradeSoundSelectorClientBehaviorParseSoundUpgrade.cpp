// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Native 004CBB54..004CBBB4 constructs the 900-byte upgrade sound record,
// calls its rowed parser, and appends to the module-data vector at +8.
// BFME1 cee35b7d8 semantic lead: UpgradeSoundSelectorClientBehaviorParseSoundUpgrade.cpp;
// target ctor/copy/dtor establish 900B versus donor 528B. Existing record
// and vector names remain address/size-derived rather than claiming original types.
#include "../../../../../Libraries/Source/WWVegas/WWLib/OwnedRecord900.h"
class INI;
class Rva004CB572 { public: void parse(INI *); };
struct BfmePod900 { int a[225]; };
namespace _STL {
template<> void vector<BfmePod900, allocator<BfmePod900> >::push_back(const BfmePod900 &);
}
#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
// The +0x08 vector holds the 900-byte records; its element type stays the
// BfmeE16 placeholder the matched ctor's vector base 0x00211E58 is rowed with,
// and the append goes through the rowed BfmePod900 push_back 0x004CBB1A.
class UpgradeSoundSelectorClientBehaviorModuleData
{
public:
	UpgradeSoundSelectorClientBehaviorModuleData();
	static void parseVoicePriority(INI*,void*,void*,const void*);
	static void parseSoundUpgrade(INI *, void *, void *, const void *);
	virtual ~UpgradeSoundSelectorClientBehaviorModuleData();
	char m_pad04[0x4];
	_STL::vector<BfmeE16> m_vec08; // +0x08
};
void UpgradeSoundSelectorClientBehaviorModuleData::parseSoundUpgrade(INI *ini, void *instance, void *, const void *)
{
    UpgradeSoundSelectorClientBehaviorModuleData *self = static_cast<UpgradeSoundSelectorClientBehaviorModuleData *>(instance);
    if (!self) return;
    BfmeRecordOwner900 value;
    reinterpret_cast<Rva004CB572 *>(&value)->parse(ini);
    reinterpret_cast<_STL::vector<BfmePod900> &>(self->m_vec08).push_back(reinterpret_cast<const BfmePod900 &>(value));
}
