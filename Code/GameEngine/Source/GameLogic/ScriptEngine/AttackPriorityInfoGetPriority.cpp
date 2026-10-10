// cl: /MD /DNDEBUG
//
// ?getPriority@AttackPriorityInfo@@QBEMPBVObject@@0_N@Z
// retail 0x00357CDE, 116 bytes (Ghidra FUN_00757cde).
//
// Target evidence: pinned from CommandButtonHuntUpdate::scanClosestTarget
// (REL32 at 0x0049569D), where Zero Hour calls info->getPriority. The body is
// the Open-BFME-1 donor AttackPriorityInfoGetPriority.cpp lookup (default
// priority +8, priority map behind the pointer at +0xC, node priority +0x14,
// the template resolved through its override chain), but BFME 2 takes the
// hunter and the target object, reads the target's template at +4, returns a
// Real and, when asked, hands the priority to 0x00357025 together with both
// objects. WB names that helper doModPriorityByCombatChain; its full172-byte body
// now lives in ScriptEngineSupport.cpp.
//
// The map lookup is the rowed unsigned-keyed STLport _M_find at 0x00357180,
// called by its row name through a TU-local _Rb_tree view; the override walk is
// the rowed getFinalOverride chain at 0x001E35DF.

typedef int Int;
typedef float Real;
typedef bool Bool;

class Overridable
{
public:
	Overridable *friend_getFinalOverride();

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	const ThingTemplate *getFinalOverride() const
	{
		if (m_nextOverride)
			return (const ThingTemplate *)m_nextOverride->friend_getFinalOverride();
		return this;
	}
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
private:
	void *m_vtable;
	const ThingTemplate *m_template;
};

struct AttackPriorityNode
{
	unsigned char m_pad00[0x14];
	Int m_priority;
};

// The rule tree's lookup is the rowed STLport _Rb_tree<unsigned, pair<const unsigned,
// void *> >::_M_find<unsigned> at 0x00357180 (private; reached through this TU-local
// declaration, as RespawnUpdateParseRules.cpp does).
class AttackPriorityInfo;
namespace _STL {
template <class _Key, class _Mapped> struct pair;
template <class _Pair> struct _Select1st;
template <class _Key> struct less;
template <class _Value> class allocator;
template <class _Value> struct _Rb_tree_node;
template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
class _Rb_tree {
	template <class _Key_arg>
	_Rb_tree_node<_Value> *_M_find(const _Key_arg &) const;
	friend class ::AttackPriorityInfo;
};
}
typedef _STL::pair<const unsigned int, void *> PriorityTreeValue;
typedef _STL::_Rb_tree<unsigned int, PriorityTreeValue, _STL::_Select1st<PriorityTreeValue>,
	_STL::less<unsigned int>, _STL::allocator<PriorityTreeValue> > PriorityTree;

// The STLport map<const ThingTemplate *, Int> header: end node at +0, size +4.
class AttackPriorityMapView
{
public:
	AttackPriorityNode *m_end;
	Int m_size;
};

class AttackPriorityInfo
{
public:
	Real getPriority(const Object *hunter, const Object *target, Bool adjust) const;
	Real doModPriorityByCombatChain(Real priority, const Object *hunter, const Object *target) const;

private:
	void *m_snapshotVtable;
	void *m_name;
	Int m_defaultPriority;
	AttackPriorityMapView *m_priorityMap;
};

Real AttackPriorityInfo::getPriority(const Object *hunter, const Object *target, Bool adjust) const
{
	Int priority = m_defaultPriority;
	const ThingTemplate *rawTemplate = target->getTemplate();
	if (rawTemplate == 0)
		return (Real)priority;

	const ThingTemplate *thingTemplate = rawTemplate->getFinalOverride();

	AttackPriorityMapView *priorityMap = m_priorityMap;
	if (priorityMap && priorityMap->m_size)
	{
		AttackPriorityNode *found = (AttackPriorityNode *)((const PriorityTree *)priorityMap)->_M_find<unsigned int>((const unsigned int &)thingTemplate);
		if (found != priorityMap->m_end)
			priority = found->m_priority;
	}

	if (adjust)
		return doModPriorityByCombatChain((Real)priority, hunter, target);

	return (Real)priority;
}
