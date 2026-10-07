// cl: /O1 /arch:SSE /G7 /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>

// The existing reserve provider at 30B96B proves the eight-byte vector
// elements at +0. The native constructor stores zero floats at +1C/+20,
// sets +24, and calls that provider with the initial capacity argument.
// Owner names remain address-derived; AreaPolygonBase is the existing
// reserve provider's name, rather than a new identity claim for the ctor.
struct BfmeE8 { int a[2]; };

class AreaPolygonBase
{
public:
	__forceinline AreaPolygonBase() {}
	void reserve(int count);
protected:
	_STL::vector<BfmeE8> vertices;
};

class Rva0030B980 : public AreaPolygonBase
{
public:
	Rva0030B980(int capacity);
private:
	char unknown0C[0x10];
	float unknown1C;
	float unknown20;
	bool dirty;
};

Rva0030B980::Rva0030B980(int capacity)
	: unknown1C(0.0f), unknown20(0.0f), dirty(true)
{
	reserve(capacity);
}

// Native 30B9DD..30B9F3: same receiver is passed to the base ctor and
// the additional field at +28 is zeroed. The caller at 330CA8 places
// this complete 2C-byte object at +8 inside its virtual-inheritance owner.
class Rva0030B9DD : public Rva0030B980
{
public:
	Rva0030B9DD(int capacity);
private:
	int unknown28;
};

Rva0030B9DD::Rva0030B9DD(int capacity)
	: Rva0030B980(capacity), unknown28(0)
{
}
