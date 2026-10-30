// cl: /DNDEBUG /MD /GX /DBFME_ASCII_DTOR_DECL /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /ICode/Libraries/Include
// stlport
//
// ??0ProductionUpdateModuleData@@QAE@XZ, retail 0x0049F7DB, 178 bytes.
// ProductionUpdate data ctor over INI table 0x00C517F0 (MaxQueueEntries at
// +0x28, NumDoorAnimations at +8, the four door durations at +0xC..+0x18,
// QuantityModifier at +0x1C, DisabledTypesToProcess at +0x2C, GiveNoXP at
// +0x30, UnitInvulnerableTime at +0x34, SpecialPrepModelconditionTime at
// +0x38, BonusForType string at +0x44, SpeedBonusAudioLoop at +0x48 (a nullable pool reference),
// SecondaryQueue at +0x4C; factory 0x24E88F news 0x50, sole caller).
// Donor is ZH ProductionUpdate.cpp: five door/int zeroes, quantity-modifier
// clear, maxQueue default, MAKE_DISABLED_MASK(HELD). BFME2 changes maxQueue
// 9 -> 0x14 and adds the string/list/bool tail; the vector clear is spelled
// as an explicit erase(begin,end) through a named reference (which homes the
// list in edi for the [edi+4]/[edi] pushes, ProductionSpeedBonus precedent).
// The QuantityModifier vector (AsciiString plus int, 8 bytes) erases through
// the linker-folded 8-byte-pair erase at 0x00207F0D (FXBoneInfoVectorErase
// names our call site as one of the seven folded callers), and its empty
// base folds to 0x00211E58; both get twin pins. The two explicit
// specialization declarations below keep those calls external and throwing
// (a visible <vector> body would be locally analyzed nothrow and collapse
// the EH states; retail arms 0 before the base call, 1 before the flags
// call, 4 before erase). BonusForType uses an inline zero constructor,
// a declared-only destructor and the set alias at 0x55F5 (empty literal
// at 0xBBAC1C). The +0x48 SpeedBonusAudioLoop reference is zero-initialized. Snapshot
// supplies the +0 vptr; the +4 word is untouched padding.


#include <string.h>
class Xfer;
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}
#include <vector>

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

typedef int Int;
typedef unsigned int UnsignedInt;

#define BFME_ASCII_DTOR_DECL
#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct QuantityModifier
{
    AsciiString m_templateName;
    int m_quantity;
};

template<int NUMBITS> class BitFlags
{
public:
 enum BogusInitType { kInit = 0 };
 BitFlags();
 BitFlags(BogusInitType, int);
	void xfer(Xfer *xfer);
 unsigned int test(unsigned bit) const { return m_words[bit>>5] & (1u << (bit&31)); }
 void clear() { memset(m_words,0,sizeof(m_words)); }
 void set(unsigned bit,bool value=true) { if(value) m_words[bit>>5] |= 1u << (bit&31); else m_words[bit>>5] &= ~(1u << (bit&31)); }
private:
	unsigned int m_words[(NUMBITS+31)/32];
};

namespace _STL
{

// Declared-only explicit specializations: keep the calls external (resolved
// through twin pins to the folded bodies) and throwing (retail EH states).
template <>
_Vector_base<QuantityModifier, allocator<QuantityModifier> >::_Vector_base(
	const allocator<QuantityModifier> &storage);
template <>
vector<QuantityModifier, allocator<QuantityModifier> >::iterator
vector<QuantityModifier, allocator<QuantityModifier> >::erase(
	vector<QuantityModifier, allocator<QuantityModifier> >::iterator first,
	vector<QuantityModifier, allocator<QuantityModifier> >::iterator last);

}

// Snapshot is unwindable before the vector constructor at +0x1C;
// its destructor restores the base table after the members are destroyed.
struct PoolMember
{
	void Rva0050ED3();
};

struct NullablePoolRef
{
 NullablePoolRef() : m_ptr(0) {}
	~NullablePoolRef()
	{
		if (m_ptr != 0)
			m_ptr->Rva0050ED3();
	}

	PoolMember *m_ptr;
};

class ProductionUpdateModuleData : public Snapshot
{
public:
 ProductionUpdateModuleData();
	virtual ~ProductionUpdateModuleData();

private:
	// +0 is the base vptr (retail 0x00C515F0); no explicit slot follows, so
	// members land on the ctor TU's offsets.
	int m_unused04; // +4, untouched padding
	Int m_numDoorAnimations; // +8
	unsigned int m_doorOpeningTime; // +0xC
	unsigned int m_doorWaitOpenTime; // +0x10
	unsigned int m_doorClosingTime; // +0x14
	unsigned int m_constructionCompleteDuration; // +0x18
	_STL::vector<QuantityModifier, _STL::allocator<QuantityModifier> > m_quantityModifiers; // +0x1C
	Int m_maxQueueEntries; // +0x28
	BitFlags<11> m_disabledTypesToProcess; // +0x2C
	bool m_giveNoXP; // +0x30
	unsigned int m_unitInvulnerableTime; // +0x34
	unsigned int m_specialPrepModelconditionTime; // +0x38
	_STL::list<Int, _STL::allocator<Int> > m_modifierList; // +0x3C, element type unproven; storage only
	bool m_veteranUnitsFromVeteranFactory; // +0x40
	bool m_setBonusModelConditionOnSpeedBonus; // +0x41
	AsciiString m_bonusForType; // +0x44
	NullablePoolRef m_speedBonusAudioLoop; // +0x48, nullable Release_Ref holder (not a string)
	bool m_secondaryQueue; // +0x4C
};

// ??0ProductionUpdateModuleData@@QAE@XZ @0x49F7DB
// bfme link decl-only begin
namespace _STL { template <> vector<QuantityModifier,_STL::allocator<QuantityModifier> >::~vector(); }
// bfme link decl-only end
ProductionUpdateModuleData::ProductionUpdateModuleData()
	: Snapshot()
	, m_bonusForType()
	, m_speedBonusAudioLoop()
{
	m_numDoorAnimations = 0;
	m_doorOpeningTime = 0;
	m_doorWaitOpenTime = 0;
	m_doorClosingTime = 0;
	m_constructionCompleteDuration = 0;
	_STL::vector<QuantityModifier, _STL::allocator<QuantityModifier> > &modifiers = m_quantityModifiers;
	modifiers.erase(modifiers.begin(), modifiers.end());
	m_maxQueueEntries = 0x14;
	m_disabledTypesToProcess = BitFlags<11>(BitFlags<11>::kInit, 3);
	m_giveNoXP = false;
	m_unitInvulnerableTime = 0;
	m_specialPrepModelconditionTime = 0;
	m_veteranUnitsFromVeteranFactory = false;
	m_setBonusModelConditionOnSpeedBonus = false;
	m_bonusForType.set("");
	m_secondaryQueue = false;
}
