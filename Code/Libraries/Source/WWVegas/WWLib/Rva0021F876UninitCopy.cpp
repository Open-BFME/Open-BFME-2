// cl: /DNDEBUG /MD
// ??$__uninitialized_copy@PAVRva0021F876@@PAV1@@_STL@@YAPAVRva0021F876@@PAV1@00ABU__false_type@0@@Z 0x0021FA47 38B evidence: copy stride 0x20 via rowed _Construct 0x0021FA1A; callers 0x00220143 0x0022018E in 0x00220105; sibling Rva002E0A0AUninitCopy same flags
#include "../../../../GameEngine/Include/GameLogic/CreateAHeroManager.h"
typedef CreateAHeroManager::CreateAHeroClass CreateAHeroClass;

class CreateAHeroManager::CreateAHeroClass
{
	char _m[0x20];
public:
	CreateAHeroClass(const CreateAHeroClass &that);
};
namespace _STL
{
struct __false_type {};
template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);
template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &)
{
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		_Construct(cur, *first);
	return cur;
}
}
template CreateAHeroClass *_STL::__uninitialized_copy(CreateAHeroClass *, CreateAHeroClass *, CreateAHeroClass *, const _STL::__false_type &);
