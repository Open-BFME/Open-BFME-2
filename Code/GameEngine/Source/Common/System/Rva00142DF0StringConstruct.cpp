// cl: /DNDEBUG /MD
//
// _STL::_Construct<Rva00142DF0String, Rva00142DF0String>, retail 0x00142CC0,
// 25 bytes: the placement copy the vector helpers in Rva00142DF0StringVector.cpp
// call. Copy is a pointer plus add-1 of the buffer refcount at +4 (/G7 so that
// increment is add, not inc). Rva00142DF0String is the refcounted handle of
// Rva001431B0's member vector; this body was held as _Construct<AsciiString>
// until 2026-10-02 (see Rva00142DF0StringVector.cpp for why it is not).

typedef unsigned int size_t;

inline void *operator new(size_t, void *place)
{
	return place;
}

class Rva00142DF0String
{
	struct Rva00142DF0StringData
	{
		virtual void _M_slot_00();
		int m_refCount;
	};

	Rva00142DF0StringData *m_data;

public:
	Rva00142DF0String(const Rva00142DF0String &that)
	{
		m_data = that.m_data;
		if (m_data)
			m_data->m_refCount++;
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

template void _STL::_Construct(Rva00142DF0String *, const Rva00142DF0String &);
