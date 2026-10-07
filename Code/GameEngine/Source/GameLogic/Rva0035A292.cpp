// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include <list>

// Retail 0x0035A292..0x0035A2DC: the +14 list contains four-byte keys.
// The caller's first argument holds the searched key at +74. Erasure is
// the existing list<int> implementation, followed by a member callback.
namespace _STL
{
	template <> list<int>::iterator list<int>::erase(list<int>::iterator);
}

struct Rva0035A292Argument
{
	char unknown00[0x74];
	int key;
};

class Rva0035A292
{
public:
	void rva0035A292(int argument, float value);
	void rva0035A005(int argument, float value);
private:
	char unknown00[0x14];
	_STL::list<int> keys;
};

void Rva0035A292::rva0035A292(int argument, float value)
{
	for (_STL::list<int>::iterator item = keys.begin(); item != keys.end(); ++item)
	{
		if (*item == reinterpret_cast<Rva0035A292Argument *>(argument)->key)
		{
			keys.erase(item);
			rva0035A005(argument, value);
			return;
		}
	}
}
