// cl: /O1 /DNDEBUG /MD
//
// _STL::__uninitialized_copy<WeaponTemplateSet*, WeaponTemplateSet*>, retail
// 0x004AE927, 38 bytes. Dedicated TU so WeaponTemplateSetConstruct.cpp cannot
// inline _Construct into this loop. Element stride is 0x54.

class WeaponTemplateSet
{
	char _m[0x54];

public:
	WeaponTemplateSet(const WeaponTemplateSet &that);
};

namespace _STL
{

struct __false_type {};

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);

template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last,
	ForwardIter result, const __false_type &)
{
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		_Construct(cur, *first);
	return cur;
}

}

template WeaponTemplateSet *_STL::__uninitialized_copy(WeaponTemplateSet *,
	WeaponTemplateSet *, WeaponTemplateSet *, const _STL::__false_type &);
