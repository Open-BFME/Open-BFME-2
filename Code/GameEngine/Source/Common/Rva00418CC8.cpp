// cl: /DNDEBUG /MD /EHsc
// ?getHighestPriorityTarget@LivingWorldAutoResolveCombatChain@@QAE_NPAUOut00418CC8@@@Z @0x00418CC8 96B evidence: between Rva00418BFB inserts 0x00418C33 and 0x00418D3C; tree decrement via rowed 0x000242C0 plus BitFlags any via rowed 0x0023C58B; 8-bit scan over flags at +0x10; 1 stack arg ret 4

namespace _STL
{
	struct _Rb_tree_node_base {};
	template <typename D>
	class _Rb_global
	{
	public:
		static _Rb_tree_node_base *_M_decrement(_Rb_tree_node_base *x);
	};
}

template <int N>
class BitFlags
{
public:
	bool any() const;
private:
	unsigned m_words[1];
};

struct Node00418CC8
{
	char m_pad[0x10];
	int m_lo;
	int m_hi;
};

struct Out00418CC8
{
	int m_lo;
	int m_hi;
};

class LivingWorldAutoResolveCombatChain
{
public:
	bool getHighestPriorityTarget(Out00418CC8 *out);
private:
	char m_pad0[4];
	void *m_node;
	int m_flag;
	char m_padC[4];
	unsigned m_bits[8];
};

bool LivingWorldAutoResolveCombatChain::getHighestPriorityTarget(Out00418CC8 *out)
{
	if (m_flag != 0) {
		_STL::_Rb_tree_node_base *n = _STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)m_node);
		Node00418CC8 *node = (Node00418CC8 *)n;
		out->m_lo = node->m_lo;
		int hi = node->m_hi;
		out->m_hi = hi;
		if (hi >= 0)
			return true;
		if (!((const BitFlags<11> *)m_bits)->any())
			return true;
	}
	for (int i = 0; i < 8; ++i) {
		if (m_bits[((unsigned)i) >> 5] & (1u << (i & 31))) {
			out->m_hi = 0;
			out->m_lo = i;
			return true;
		}
	}
	return false;
}
