// cl: /O1 /DNDEBUG /MD
//
// _STL::_Construct<WeaponTemplateSet, WeaponTemplateSet>, retail 0x004AE915,
// 18 bytes. Dedicated TU so ThingTemplate.cpp cannot see this body.
// Null-checks the destination then thiscall-copy-constructs into it.

typedef unsigned int size_t;

inline void *operator new(size_t, void *place)
{
	return place;
}

class WeaponTemplateSet
{
public:
	WeaponTemplateSet(const WeaponTemplateSet &that);
};

namespace _STL
{

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value)
{
	if (p)
		new (p) T1(value);
}

}

template void _STL::_Construct(WeaponTemplateSet *, const WeaponTemplateSet &);
