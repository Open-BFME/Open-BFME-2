// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0ProductionUpdateModuleData@@QAE@XZ, retail 0x0049F7DB, 178 bytes.
// ProductionUpdate data ctor over INI table 0x00C517F0 (MaxQueueEntries at
// +0x28, NumDoorAnimations at +8, the four door durations at +0xC..+0x18,
// QuantityModifier at +0x1C, DisabledTypesToProcess at +0x2C, GiveNoXP at
// +0x30, UnitInvulnerableTime at +0x34, SpecialPrepModelconditionTime at
// +0x38, BonusForType string at +0x44, SpeedBonusAudioLoop string at +0x48,
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
// call, 4 before erase). The two AsciiString members use the MissileUpdate
// idiom (inline zero ctor in the init list, declared-only dtor for
// unwindability, set through the alias pin at 0x55F5, empty literal at
// 0xBBAC1C). The class keeps an explicit vtable slot with no virtuals so
// nothing is emitted, and the +4 word is untouched padding.

#include <list>
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;

class AsciiString
{
public:
	AsciiString(int zero) : m_data(reinterpret_cast<void *>(zero)) {}
	~AsciiString();
	void set(const char *str);

private:
	void *m_data;
};

struct QuantityModifier
{
	AsciiString m_templateName;
	Int m_quantity;
};

template <int NUM_BITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags();
	BitFlags(BogusInitType init, Int bit);

private:
	UnsignedInt m_words[1];
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

// UpdateModuleData subobject: deliberately empty (EBO, so the derived class
// starts at +0) with an inline empty ctor (retail shows no base call) but a
// declared-only dtor, which makes the base unwindable: that arms trylevel 0
// (plus the homed this and the zeroed ebx) before the first member call
// instead of after it. The vtable lives in the derived class as an explicit
// slot (derived mem-init, which the scheduler sinks below the vector setup
// but above its call) with no virtuals so no vtable is emitted.
class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();
};

class ProductionUpdateModuleData : public UpdateModuleData
{
public:
	ProductionUpdateModuleData();

private:
	const void *m_vtable; // +0, retail 0x00C515F0
	int m_unused04; // +4, untouched padding
	Int m_numDoorAnimations; // +8
	UnsignedInt m_doorOpeningTime; // +0xC
	UnsignedInt m_doorWaitOpenTime; // +0x10
	UnsignedInt m_doorClosingTime; // +0x14
	UnsignedInt m_constructionCompleteDuration; // +0x18
	_STL::vector<QuantityModifier, _STL::allocator<QuantityModifier> > m_quantityModifiers; // +0x1C
	Int m_maxQueueEntries; // +0x28
	BitFlags<11> m_disabledTypesToProcess; // +0x2C
	bool m_giveNoXP; // +0x30
	UnsignedInt m_unitInvulnerableTime; // +0x34
	UnsignedInt m_specialPrepModelconditionTime; // +0x38
	_STL::list<int, _STL::allocator<int> > m_modifierList; // +0x3C, element type unproven; _List_base ctor is element-generic
	bool m_veteranUnitsFromVeteranFactory; // +0x40
	bool m_setBonusModelConditionOnSpeedBonus; // +0x41
	AsciiString m_bonusForType; // +0x44
	AsciiString m_speedBonusAudioLoop; // +0x48
	bool m_secondaryQueue; // +0x4C
};

// ??0ProductionUpdateModuleData@@QAE@XZ @0x49F7DB
ProductionUpdateModuleData::ProductionUpdateModuleData()
	: UpdateModuleData()
	, m_vtable(reinterpret_cast<const void *>(0x00C515F0))
	, m_bonusForType(0)
	, m_speedBonusAudioLoop(0)
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
