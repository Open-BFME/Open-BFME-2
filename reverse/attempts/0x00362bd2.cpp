// ?rva00362BD2@Rva0040AD80ReferenceState@@QAEXHM@Z
// partial score=0.98 date=2026-10-08
// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// The runtime label is "GlowMaterial"; the original C++ class spelling is unknown.
// Preserve retail's second referent reload after registry erasure.

typedef int Int;
class Rva0040AD80ReferenceState;
class Image;

struct Gen_t_0040abb0_p12cd
{
	char m_bfmeBody[12];
};

namespace _STL
{

template <class _T1, class _T2> struct pair
{
	pair(const _T1& a, const _T2& b) : first(a), second(b) {}
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

template<class T> struct _Rb_tree_node { char links[16]; T value; };
template<class T> struct _Nonconst_traits {};
template<class T,class Traits> struct _Rb_tree_iterator { void* _M_node; };

template <class _Key, class _Value, class _KeyOfValue, class _Compare,
		class _Alloc> class _Rb_tree
{
public:
	unsigned int erase(const _Key &key);
	pair<_Rb_tree_iterator<_Value,_Nonconst_traits<_Value> >,bool> insert_unique(const _Value&);

private:
	template<class OtherKey> _Rb_tree_node<_Value>* _M_find(const OtherKey&) const;
	friend class ::Rva0040AD80ReferenceState;
	char m_bfmeBody[0x18];
};

}

typedef _STL::_Rb_tree<Int, _STL::pair<const Int, Gen_t_0040abb0_p12cd>,
		_STL::_Select1st<_STL::pair<const Int, Gen_t_0040abb0_p12cd> >,
		_STL::less<Int>,
		_STL::allocator<_STL::pair<const Int, Gen_t_0040abb0_p12cd> > >
	ReferenceStateTree;

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
	void rva00362BD2(int,float);

private:
	ReferenceStateReferent *m_firstReferent;				// +0x04
	ReferenceStateReferent *m_secondReferent;				// +0x08
	Int m_0c;
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

// Native 00362BD2..00362C9A, 200B, RET8. The registry at E01E7C and
// +4/+8 referents are independently shared with rowed releaseReferences.
// Both calls construct the already-rowed 72B MaterialPass-derived provider.
// Only the target's key, reference-count and +40 mode accesses are named;
// the receiver's original API spelling remains unknown.
class MaterialPassClass {
public:
 MaterialPassClass();
 virtual ~MaterialPassClass();
};
class Rva0073F96A : public MaterialPassClass {
public:
 Rva0073F96A(int,float);
 virtual ~Rva0073F96A();
 char pad34[0x34];
 int key;
 float value;
 int mode;
 float extra;
};
typedef _STL::pair<const unsigned,void*> GlowLookupPair;
typedef _STL::_Rb_tree<unsigned,GlowLookupPair,_STL::_Select1st<GlowLookupPair>,_STL::less<unsigned>,_STL::allocator<GlowLookupPair> > GlowLookupTree;
typedef _STL::pair<const unsigned,Image*> GlowInsertPair;
typedef _STL::_Rb_tree<unsigned,GlowInsertPair,_STL::_Select1st<GlowInsertPair>,_STL::less<unsigned>,_STL::allocator<GlowInsertPair> > GlowInsertTree;
void Rva0040AD80ReferenceState::rva00362BD2(volatile int key,float value) {
 GlowLookupTree* registry=(GlowLookupTree*)&g_Va00E01E7C;
 _STL::_Rb_tree_node<GlowLookupPair>* found=registry->_M_find(*(const unsigned*)&key);
 if(found==*(void**)registry) {
  m_secondReferent=(ReferenceStateReferent*)new Rva0073F96A(key,value);
  GlowInsertPair pair(key,(Image*)m_secondReferent);
  ((GlowInsertTree*)registry)->insert_unique(pair);
  ((Rva0073F96A*)m_secondReferent)->mode=1;
 } else {
  m_secondReferent=(ReferenceStateReferent*)found->value.second;
  ++m_secondReferent->m_referenceCount;
 }
 m_firstReferent=(ReferenceStateReferent*)new Rva0073F96A(key,value);
 ((Rva0073F96A*)m_firstReferent)->mode=0;
 m_0c=0;
}
