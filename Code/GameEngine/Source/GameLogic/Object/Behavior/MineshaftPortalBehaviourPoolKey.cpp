// cl: /DNDEBUG /MD /EHsc
// ?rva000373109@MineshaftPortalBehaviour@@SA?AW4NameKeyType@@XZ @0x373109
// (69B): cached pool-name key for MineshaftPortalBehaviour. The class
// identity comes from the pool-name string the body pushes
// ("MineshaftPortalBehaviour"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class MineshaftPortalBehaviour
{
public:
	static NameKeyType rva000373109();
};

// ?rva000373109@MineshaftPortalBehaviour@@SA?AW4NameKeyType@@XZ
NameKeyType MineshaftPortalBehaviour::rva000373109()
{
	static NameKeyType TheMineshaftPortalBehaviourPoolKey =
		TheNameKeyGenerator->nameToKey("MineshaftPortalBehaviour");
	return TheMineshaftPortalBehaviourPoolKey;
}

struct TreeOpaqueMapped00372FF4;
namespace _STL {
template <class T1, class T2> struct pair;
template <class T> struct _Select1st;
template <class T> struct less;
template <class T> class allocator;
template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
class _Rb_tree {
public:
	~_Rb_tree();
};
typedef pair<const float, TreeOpaqueMapped00372FF4> TreeValue00372FF4;
typedef _Rb_tree<float, TreeValue00372FF4, _Select1st<TreeValue00372FF4>, less<float>, allocator<TreeValue00372FF4> > Tree00372FF4;
}

class Rva0037314E
{
public:
	void rva0037314E();
};

void Rva0037314E::rva0037314E()
{
	((_STL::Tree00372FF4 *)this)->~_Rb_tree();
}

class Rva00372F00
{
public:
	~Rva00372F00();
};

class Rva00373153
{
public:
	void rva00373153();
};

void Rva00373153::rva00373153()
{
	((Rva00372F00 *)this)->~Rva00372F00();
}
