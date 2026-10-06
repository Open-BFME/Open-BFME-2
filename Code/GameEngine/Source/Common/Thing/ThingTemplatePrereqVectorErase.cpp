// cl: /Oy- /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?erasePrereqVec@Rva0033EB77Vec@@QAEPAXPAX0@Z @0x0033EB77 51B: vector<ProductionPrerequisite> range erase.
// Retail shifts [last,finish) down via rowed CopyRange 0x002D0F36, destroys the vacated tail via rowed
// _Destroy range 0x002CFBAE (rowed as ?dup_002cfbae), stores the new finish and returns first.
// Evidence: caller ?parsePrerequisites@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z at 0x0033EBB5 calls
// vec->erasePrereqVec(begin,end) at instance+0x324; shape identical to rowed vector<AsciiString>::erase
// at 0x0002CCFC (51B, same push/call/frame sequence with lea tag at [ebp+0xb]).
class ProductionPrerequisite;

ProductionPrerequisite *Rva002D0F36CopyRange(ProductionPrerequisite *first, ProductionPrerequisite *last, ProductionPrerequisite *result, int dummy);

namespace _STL
{
template <class ForwardIter>
void _Destroy(ForwardIter first, ForwardIter last);
}

class Rva0033EB77Vec
{
public:
	void *erasePrereqVec(void *first, void *last);

private:
	void *m_begin;
	void *m_finish;
	void *m_endOfStorage;
};

void *Rva0033EB77Vec::erasePrereqVec(void *first, void *last)
{
	ProductionPrerequisite *result = Rva002D0F36CopyRange(
		(ProductionPrerequisite *)last,
		(ProductionPrerequisite *)m_finish,
		(ProductionPrerequisite *)first,
		(int)((char *)&first + 3));
	_STL::_Destroy(result, (ProductionPrerequisite *)m_finish);
	m_finish = result;
	return first;
}
