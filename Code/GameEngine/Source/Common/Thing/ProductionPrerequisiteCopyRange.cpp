// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?Rva002D0F36CopyRange@@YAPAVProductionPrerequisite@@PAV1@00H@Z @0x002D0F36 29B: tag temp plus null distance forwarder to rowed __copy loop 0x0033E9DE. Evidence: same 29B shape as rowed ?Rva002915EBCopyRange at 0x002915EB and ?Rva004BA324CopyRange at 0x004BA324; caller 0x002D1033 pushes 3 pointers; callee stride 0x24.
namespace _STL {
struct random_access_iterator_tag {
};
template <class _InputIter, class _OutputIter, class _Distance>
_OutputIter __copy(_InputIter __first, _InputIter __last, _OutputIter __result, const random_access_iterator_tag &__tag, _Distance *__dist);
}
class ProductionPrerequisite;
ProductionPrerequisite *Rva002D0F36CopyRange(ProductionPrerequisite *first, ProductionPrerequisite *last, ProductionPrerequisite *result, int dummy)
{
	_STL::random_access_iterator_tag tag;
	(void)dummy;
	return _STL::__copy(first, last, result, tag, (int *)0);
}
