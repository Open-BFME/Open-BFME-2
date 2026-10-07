// cl: /DNDEBUG /MD /EHsc
// ?rva0003ECCD6@ThreatFinderUpdate@@SA?AW4NameKeyType@@XZ @0x3ECCD6
// (69B): cached pool-name key for ThreatFinderUpdate. The class
// identity comes from the pool-name string the body pushes
// ("ThreatFinderUpdate"); the body guards a function-local static
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

class ThreatFinderUpdate
{
public:
	static NameKeyType rva0003ECCD6();
};

// ?rva0003ECCD6@ThreatFinderUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType ThreatFinderUpdate::rva0003ECCD6()
{
	static NameKeyType TheThreatFinderUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("ThreatFinderUpdate");
	return TheThreatFinderUpdatePoolKey;
}

struct Rva003ECD1BVector
{
	__forceinline Rva003ECD1BVector(const Rva003ECD1BVector &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}
	float x, y, z;
};

struct Rva003ECD1BObject
{
	char m_pad00[0x38];
	Rva003ECD1BVector m_position;
};

struct Rva003ECD1BChild
{
	char m_pad00[0x554];
	Rva003ECD1BVector m_position;
};

struct Rva003ECD1BRoot
{
	Rva003ECD1BObject *m_object;
	char m_pad04[0x18 - 0x04];
	Rva003ECD1BChild *m_child;
};

class Rva003ECD1B
{
public:
	int rva003ECD1B();
};

// Native 3ECD1B..3ECD60: receiver is an interior view at root+8.
// Copy the owner's three-float position to child+554 when child exists;
// return 1. The enclosing class and update-method identity remain unknown.
int Rva003ECD1B::rva003ECD1B()
{
	Rva003ECD1BRoot *root = reinterpret_cast<Rva003ECD1BRoot *>(
		reinterpret_cast<char *>(this) - 8);
	if (root->m_child)
	{
		Rva003ECD1BVector position(root->m_object->m_position);
		root->m_child->m_position = position;
	}
	return 1;
}
