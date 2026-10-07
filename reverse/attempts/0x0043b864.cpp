// ?rva0043B864@Rva0043B2E2@@QAEAAVRva0043B196@@ABH@Z
// partial score=0.9 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Target facts: retail 0x0043B864 is 92 bytes. It lower-bounds the int key
// through the rowed int-key tree helper at 0x00382A92, returns the mapped
// field at node+0x14 when present, and on a miss initializes a 0x88-byte
// temporary through 0x0043B208, constructs the key/value pair through
// 0x0043B23E, then inserts through the rowed tree wrapper at 0x0043B6BA.
//
// Structural inference: the receiver uses the Rva0043B2E2 tree view shared
// with the rowed insert wrapper and neighboring call sites. Rva0043B196 is
// the mapped-value view established by the pair constructor. The exact owning
// class and template specialization are unresolved, so the method remains
// address-derived.

#include <map>

class Rva0043B196
{
public:
	Rva0043B196(const Rva0043B196 &source);
private:
	char m_data[0x88];
};

class Rva0043B208
{
public:
	Rva0043B208 *rva0043B208();
private:
	char m_data[0x88];
};

class Rva0043B23E
{
public:
	Rva0043B23E(const int &key, const Rva0043B196 &value);
private:
	int m_key;
	Rva0043B196 m_value;
};

struct Rva0043B2E2Node
{
	char m_pad00[0x10];
	int m_key;
};

class Rva0043B2E2
{
public:
	typedef _STL::pair<const int, void *> Value;
	typedef _STL::_Rb_tree_iterator<Value, _STL::_Nonconst_traits<Value> > Iterator;

	Iterator rva0043B6BA(Iterator position, const Value &value);
	Rva0043B196 &rva0043B864(const int &key);

private:
	void *m_header;
	unsigned int m_count;
	char m_pad08[16];
};

template <class T>
inline const Rva0043B2E2::Value &rva0043B864ValueView(const T &value)
{
	return reinterpret_cast<const Rva0043B2E2::Value &>(value);
}

Rva0043B196 &Rva0043B2E2::rva0043B864(const int &key)
{
	Iterator it;
	it._M_node = (::_STL::_Rb_tree_node_base *)((_STL::map<int, int> *)this)->lower_bound(key)._M_node;
	Rva0043B2E2Node *node = (Rva0043B2E2Node *)it._M_node;
	if (it._M_node == (::_STL::_Rb_tree_node_base *)m_header || key < node->m_key)
	{
	Rva0043B208 value;
	Rva0043B208 *initialized = value.rva0043B208();
	it = rva0043B6BA(it, rva0043B864ValueView(Rva0043B23E(key, (const Rva0043B196 &)*initialized)));
	}
	return *(Rva0043B196 *)((char *)it._M_node + 0x14);
}
