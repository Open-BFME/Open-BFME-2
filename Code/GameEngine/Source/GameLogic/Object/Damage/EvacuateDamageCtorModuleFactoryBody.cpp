// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// The registration-named ModuleFactory entry allocates the 0x18-byte BFME
// EvacuateDamage and reaches this constructor through ILT 0x0003BD40.

#include <list>
#include <functional>
#include <utility>

class Thing;
class ModuleData;

class PB_DeepBase
{
public:
    PB_DeepBase(Thing *, const ModuleData *);
    virtual ~PB_DeepBase();

private:
    const ModuleData *m_moduleData;
    void *m_object;
};

class PB_Iface1 { public: virtual void slot(); };
class EvacuateDamageInterface { public: virtual void slot() = 0; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h
class DamageModule : public PB_DeepBase,
                     public PB_Iface1,
                     public EvacuateDamageInterface
{
public:
    // Retail 0x004BAE1D calls the one linked base ctor, DamageModule's row at
    // 0x004B9704; an inline body here emitted a second, wrong copy first in
    // link order.
    DamageModule(Thing *thing, const ModuleData *moduleData);
};

struct EvacuationRecord
{
    unsigned int m_data[2];
};

class EvacuateDamage : public DamageModule
{
public:
    EvacuateDamage(Thing *, const ModuleData *);

private:
    std::list<EvacuationRecord> m_pendingEvacuations;
};

// ??0EvacuateDamage@@QAE@PAVThing@@PBVModuleData@@@Z
EvacuateDamage::EvacuateDamage(Thing *thing, const ModuleData *moduleData)
    : DamageModule(thing, moduleData)
{
    m_pendingEvacuations.clear();
}

// INIMacroTable's destructor, retail 0x0002CD7B (53 B). Its only caller is the
// atexit thunk 0x007B6A6E for BfmeINIMacroTableStorage (0x00DDF58C), which
// 0x007ABBB3 builds with ??0INIMacroTable 0x0002DC3C. It destroys the
// case-insensitive name set at +0x14 (0x0002CC38) and then the macro
// hashtable at +0 (0x0002CCC3), both rowed; declared here only to bind them.
// (This row was misidentified as ??1EvacuateDamage@@UAE@XZ by a masked search;
// EvacuateDamage's real destructor is ??1EvacuateDamage@@MAE@XZ, 0x004BAEC8.)
class AsciiString;
struct Rva0002C9E7Value;
struct BfmeStringNoCaseLess;
namespace rts { template <class T> struct hash; template <class T> struct equal_to; }

namespace _STL
{
template <class V, class K, class HF, class ExK, class EqK, class A> class hashtable;
template <class K, class V, class KoV, class Cmp, class A> class _Rb_tree;

typedef pair<const AsciiString, Rva0002C9E7Value> INIMacroPair;

template <>
class hashtable<INIMacroPair, AsciiString, rts::hash<AsciiString>, _Select1st<INIMacroPair>,
		rts::equal_to<AsciiString>, allocator<INIMacroPair> >
{
public:
	~hashtable();
private:
	void *m_words[5];
};

template <>
class _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, BfmeStringNoCaseLess, allocator<AsciiString> >
{
public:
	~_Rb_tree();
private:
	void *m_words[3];
};
}

class INIMacroTable
{
public:
	~INIMacroTable();

private:
	_STL::hashtable<_STL::INIMacroPair, AsciiString, rts::hash<AsciiString>, _STL::_Select1st<_STL::INIMacroPair>,
		rts::equal_to<AsciiString>, _STL::allocator<_STL::INIMacroPair> > m_macros;           // +0x00
	_STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>, BfmeStringNoCaseLess,
		_STL::allocator<AsciiString> > m_expanded;                                              // +0x14
};

// ??1INIMacroTable@@QAE@XZ
INIMacroTable::~INIMacroTable()
{
}
