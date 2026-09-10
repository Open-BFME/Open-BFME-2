// cl: /G7 /DNDEBUG /MD
//
// _STL::_Construct<AsciiString, AsciiString>, retail 0x00142CC0, 25 bytes.
// Dedicated TU so Upgrade.cpp cannot see this body. Copy is a pointer plus
// add-1 of the buffer refcount at +4. /G7 so that increment is add not inc.

typedef unsigned int size_t;

inline void *operator new(size_t, void *place)
{
	return place;
}

class AsciiString
{
	struct Buffer
	{
		int pad;
		int ref;
	};

	Buffer *p;

public:
	AsciiString(const AsciiString &that)
	{
		p = that.p;
		if (p)
			p->ref++;
	}
};

namespace _STL
{

template <class T1, class T2>
void _Construct(T1 *dest, const T2 &value)
{
	if (dest)
		new (dest) T1(value);
}

}

template void _STL::_Construct(AsciiString *, const AsciiString &);
