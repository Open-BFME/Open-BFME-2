// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// The runtime label is "GlowMaterial"; the original C++ class spelling is unknown.
// Preserve retail's second referent reload after registry erasure.

typedef int Int;
class Image;
class Rva0040AD80ReferenceState;

struct Gen_t_0040abb0_p12cd
{
	char m_bfmeBody[12];
};

namespace _STL
{

template <class _T1, class _T2> struct pair
{
	pair(const _T1 &a, const _T2 &b) : first(a), second(b) {}
	_T1 first;
	_T2 second;
};

template <class _Pair> struct _Select1st
{
};

template <class _Tp> struct less
{
};

template <class _Tp> class allocator
{
};

template <class T> struct _Nonconst_traits {};
template <class T> struct _Rb_tree_node;
template <class T, class Traits> struct _Rb_tree_iterator
{
	_Rb_tree_node<T> *_M_node;
};
template <class T> struct _Rb_tree_node
{
	unsigned int color;
	_Rb_tree_node *parent;
	_Rb_tree_node *left;
	_Rb_tree_node *right;
	T value;
};

template <class _Key, class _Value, class _KeyOfValue, class _Compare,
		class _Alloc> class _Rb_tree
{
public:
	unsigned int erase(const _Key &key);
	typedef _Rb_tree_iterator<_Value, _Nonconst_traits<_Value> > iterator;
	pair<iterator, bool> insert_unique(const _Value &value);
	_Rb_tree_node<_Value> *header;

private:
	friend class ::Rva0040AD80ReferenceState;
	template <class K> _Rb_tree_node<_Value> *_M_find(const K &key) const;
	char m_bfmeBody[0x14];
};

}

typedef _STL::_Rb_tree<Int, _STL::pair<const Int, Gen_t_0040abb0_p12cd>,
		_STL::_Select1st<_STL::pair<const Int, Gen_t_0040abb0_p12cd> >,
		_STL::less<Int>,
		_STL::allocator<_STL::pair<const Int, Gen_t_0040abb0_p12cd> > >
	ReferenceStateTree;

// Declaration-only ABI view of the registry's unsigned-key pointer slots.
// Both native helpers have verified generic pointer-map providers: _M_find
// 357180 and insert_unique 4D795B. Image is their existing symbol spelling;
// the registry values are the materials constructed below, not Images.
typedef _STL::pair<const unsigned int, Image *> RegistryValue;
typedef _STL::_Rb_tree<unsigned int, RegistryValue,
	_STL::_Select1st<RegistryValue>, _STL::less<unsigned int>,
	_STL::allocator<RegistryValue> > RegistryTree;

// The tree's erase(const key &) at 0x00362B89 is rowed as Rva00362AB5::rva00362B89.
class Rva00362AB5
{
public:
	unsigned int rva00362B89(const Int &key);
};

// 0x012F10DC holds the tree instance; retail's dynamic initializer
// (retail 0x00C6B3D0) constructs it, so the one definition of the storage is
// the init struct in game/GameEngine/Source/Common/Rva00C6B390StaticInitializers.cpp.
extern unsigned int g_Va00E01E7C;				// tree object at 0x00E01E7C (Rva007B6880Thunks.cpp)

class ReferenceStateReferent
{
public:
	virtual void destroy(void);				// slot 0

	Int m_referenceCount;					// +0x04
	char m_bfmeBody[0x38 - 0x08];
	Int m_key;						// +0x38
};

// Layout and constructor are independently recovered at 73F85D. Allocation
// extent 48 and fields 38/3C/40 are also proved by native 362BD2. The +4
// reference count is read by the existing releaseReferences body.
class MaterialPassClass
{
public:
	MaterialPassClass();
	virtual ~MaterialPassClass();
};
class Rva0073F96A : public MaterialPassClass
{
public:
	Rva0073F96A(int color, float value);
	virtual ~Rva0073F96A();
	char m_pad04[0x34];
	int m_key;
	float m_value;
	int m_flag;
	float m_extra;
};

// PE exports identify the Snapshot base; only its used lifetime interface is declared here.
// class-gate: allow Snapshot releaseReferences reads only +0x04/+0x08; the base supplies the +0x00 vptr and its slots are unused.
class Xfer;
class Snapshot
{
public:
    virtual ~Snapshot() {}

protected:
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess(void) = 0;
};

class Rva0040AD80ReferenceState : public Snapshot
{
public:
	virtual ~Rva0040AD80ReferenceState();
	__declspec(noinline) void releaseReferences(void);
	void rva00362BD2(int key, float value);

private:
	ReferenceStateReferent *m_firstReferent;				// +0x04
	ReferenceStateReferent *m_secondReferent;				// +0x08
	int m_field0C;
};

// ?releaseReferences@Rva0040AD80ReferenceState@@QAEXXZ
void Rva0040AD80ReferenceState::releaseReferences(void)
{
	ReferenceStateReferent *second = m_secondReferent;

	if (second)
	{
		if (second->m_referenceCount == 1)
		{
			Int key = second->m_key;

			((Rva00362AB5 *)&g_Va00E01E7C)->rva00362B89(key);
		}

		ReferenceStateReferent *again = m_secondReferent;

		if (again)
		{
			if (--again->m_referenceCount == 0)
				again->destroy();

			m_secondReferent = 0;
		}
	}

	ReferenceStateReferent *first = m_firstReferent;

	if (first)
	{
		if (--first->m_referenceCount == 0)
			first->destroy();

		m_firstReferent = 0;
	}
}

// Target native 362BD2..362C9A/200B, RET8: acquire a registry material at
// receiver+8 (incrementing its refcount on a hit), then create the private
// material at +4. The existing BFME1-derived release body establishes these
// two ownership fields independently. The runtime label is GlowMaterial;
// method and original class names remain unknown. Registry and generic
// helper addresses are direct native relocations, not donor placements.
void Rva0040AD80ReferenceState::rva00362BD2(int key, float value)
{
	RegistryTree *registry = reinterpret_cast<RegistryTree *>(&g_Va00E01E7C);
	_STL::_Rb_tree_node<RegistryValue> *found = registry->_M_find(reinterpret_cast<const unsigned int &>(key));
	if (found == registry->header)
	{
		Rva0073F96A *material = new Rva0073F96A(key, value);
		m_secondReferent = reinterpret_cast<ReferenceStateReferent *>(material);
		registry->insert_unique(RegistryValue(static_cast<unsigned int>(key), reinterpret_cast<Image *>(material)));
		reinterpret_cast<Rva0073F96A *>(m_secondReferent)->m_flag = 1;
	}
	else
	{
		m_secondReferent = reinterpret_cast<ReferenceStateReferent *>(found->value.second);
		++m_secondReferent->m_referenceCount;
	}
	m_firstReferent = reinterpret_cast<ReferenceStateReferent *>(new Rva0073F96A(key, value));
	reinterpret_cast<Rva0073F96A *>(m_firstReferent)->m_flag = 0;
	m_field0C = 0;
}
