// cl: /DNDEBUG /MD
//
// _STL::_Construct<WeaponTemplateSet, WeaponTemplateSet>, retail 0x004AE915,
// 18 bytes. Dedicated TU so ThingTemplate.cpp cannot see this body.
// Null-checks the destination then thiscall-copy-constructs into it.

#include <stddef.h>

class WeaponTemplateSet
{
public:
	WeaponTemplateSet(const WeaponTemplateSet &that);
};

namespace _STL
{

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);

template <>
void _Construct<WeaponTemplateSet, WeaponTemplateSet>(WeaponTemplateSet *p, const WeaponTemplateSet &value)
{
	if (p)
		p->WeaponTemplateSet::WeaponTemplateSet(value);
}

}
