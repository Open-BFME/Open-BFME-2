// cl: /O1 /arch:SSE /EHsc /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva004AF531@Rva004AF531@@QAEHH@Z @0x004AF531 123B ret 4.
// Probe the unsigned-key map at +0x10C with the argument, then with key 1.
// Native find357180 compares keys unsigned; the signed argument preserves
// its 32-bit representation when constructing the lookup key.
// A miss returns 1000. A hit returns the dword at node+0x14.


// Constructor placement at 0x004AEF23 is bounded by the preceding setter's
// ret 4 and RespawnUpdate's next entry at 0x004AEF46. The 35-byte body
// independently establishes the argument at +0, zeros at +4/+8, float 1
// at +12, and byte zero at +16. This remains an opaque record identity.
struct Rva004AF531Rec
{
	unsigned m_key;
	int m_a;
	int m_b;
	float m_one;
	unsigned char m_flag;
	Rva004AF531Rec(unsigned key) : m_key(key), m_a(0), m_b(0), m_one(1.0f), m_flag(0) {}
};

struct RespawnRule
{
 unsigned level;
 unsigned cost;
 int time;
 float health;
 bool autoSpawn;
 RespawnRule(unsigned ruleLevel=1):level(ruleLevel),cost(0),time(0),health(1.0f),autoSpawn(false) {}
};
// The unsigned-keyed tree at +0x10C is looked up through the rowed STLport
// _Rb_tree<unsigned, pair<const unsigned, void *> >::_M_find<unsigned> at
// 0x00357180 (private; reached through this TU-local declaration, as
// RespawnUpdateParseRules.cpp does). The tree starts with its header node.
class Rva004AF531;
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
	friend class ::Rva004AF531;
};
}
typedef _STL::pair<const unsigned int, void *> Rva004AF531TreeValue;
typedef _STL::_Rb_tree<unsigned int, Rva004AF531TreeValue, _STL::_Select1st<Rva004AF531TreeValue>,
	_STL::less<unsigned int>, _STL::allocator<Rva004AF531TreeValue> > Rva004AF531Tree;
struct Rva004AF531TreeHeader
{
 void *sentinel;
 int count;
};
struct RespawnRuleNode
{
 char prefix[0x10];
 RespawnRule rule;
};
struct Rva004AF531Node
{
 char prefix[0x14];
 int value;
};
extern float g_parseDurationMsecScale;

class Rva004AF531
{
public:
	int rva004AF531(int key);
 int rva004AF5AC(unsigned level);
	char m_pad[0x10C];
	Rva004AF531TreeHeader m_map;
	const Rva004AF531Tree &tree() const { return *reinterpret_cast<const Rva004AF531Tree *>(&m_map); }
};

int Rva004AF531::rva004AF531(int key)
{
	Rva004AF531Rec rec(key);
	Rva004AF531Node *it = (Rva004AF531Node *)tree()._M_find<unsigned int>(rec.m_key);
	Rva004AF531Node *end = (Rva004AF531Node *)m_map.sentinel;
	if (it == end)
	{
		rec.Rva004AF531Rec::Rva004AF531Rec(1);
		it = (Rva004AF531Node *)tree()._M_find<unsigned int>(rec.m_key);
		if (it == end)
			return 1000;
	}
	return it->value;
}

// Native4AF5AC..4AF63E: rule lookup with level1 fallback, node time
// at18 divided by1000. The target uses the same20-byte rule construction
// as rowed RespawnUpdate::triggerDeathBeforeRespawn4AF63E. Native shared
// duration scale DBA4EC=0.005 and literal C556F0=30000 supply the miss.
// Receiver original identity remains unknown; respawn-family relation
// follows the shared tree at10C, rule layout and adjacent death handler.
int Rva004AF531::rva004AF5AC(unsigned level)
{
 RespawnRule rule(level);
 RespawnRuleNode *found=(RespawnRuleNode *)tree()._M_find<unsigned int>(rule.level);
 RespawnRuleNode *end=(RespawnRuleNode *)m_map.sentinel;
 if(found==end) {
  rule.RespawnRule::RespawnRule(1);
  found=(RespawnRuleNode *)tree()._M_find<unsigned int>(rule.level);
  if(found==end) return (int)(g_parseDurationMsecScale * 30000.0f);
 }
 return found->rule.time / 1000;
}
