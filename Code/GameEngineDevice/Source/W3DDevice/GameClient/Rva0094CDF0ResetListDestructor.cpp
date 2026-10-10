// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient
// BFME reset-list member destructor at retail 0x0094CDF0.

class TextureBaseClass
{
public:
	void Release_Ref(void);
};

void b_0094cbf0(void);

class Rva0094CDF0Handle
{
public:
	~Rva0094CDF0Handle(void)
	{
		if (m_resource != 0)
			m_resource->Release_Ref();
	}

	TextureBaseClass *m_resource;
};

namespace _STL
{
	template <class First, class Second>
	struct pair
	{
		First first;
		Second second;
	};

	template <class T>
	struct _Select1st
	{
	};

	template <class T>
	struct less
	{
	};

	template <class T>
	class allocator
	{
	};

	template <class Key, class Value, class Select, class Compare,
		class Allocator>
	class _Rb_tree
	{
	public:
		~_Rb_tree(void);
	};
}

struct Gen_t_0094cbf0_p16cd
{
	int a[4];
};

typedef _STL::pair<const int, Gen_t_0094cbf0_p16cd>
	Rva0094CDF0Pair;
typedef _STL::_Rb_tree<int, Rva0094CDF0Pair,
	_STL::_Select1st<Rva0094CDF0Pair>, _STL::less<int>,
	_STL::allocator<Rva0094CDF0Pair> > Rva0094CDF0Tree;

// Retail 0x00170E82: the destructor of Rva00171024, whose rowed constructor
// 0x00171024 builds the same layout (map at +8, texture handle at +0x18);
// the Rva000E6AC0 owner destroys its two members through it.
class Rva00171024
{
public:
	~Rva00171024(void);

private:
	unsigned char m_prefix[8];
	Rva0094CDF0Tree m_tree;
	unsigned char m_gap[15];
	Rva0094CDF0Handle m_handle;
	unsigned char m_suffix[7];
};

Rva00171024::~Rva00171024(void)
{
}
