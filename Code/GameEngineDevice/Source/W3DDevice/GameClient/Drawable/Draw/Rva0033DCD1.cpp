// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0033DCD1@Rva0033DCD1@@QBEPBUModelConditionInfo@@ABV?$BitFlags@$0HF@@@@Z, retail 0x0033DCD1, 25 bytes.
// Simple wrapper: return m_map.findBestInfo(m_vec, flags); m_vec at +0x358, m_map at +0x364.
// Evidence: callee rowed 0x0033D46A SparseMatchFinder ModelConditionInfo BitFlags 117; callers 0x0029091E 0x002C8872 0x002C8C97 0x0036DE17.
#include <vector>

struct ModelConditionInfo
{
	int m_dummy;
};

template <int Bits>
class BitFlags
{
public:
	unsigned int m_bits;
};

template <class A, class B>
class SparseMatchFinder
{
public:
	const A *findBestInfo(const _STL::vector<A> &v, const B &b) const;
};

typedef BitFlags<117> ModelConditionSetFlags;

struct Rva0033DCD1
{
	char m_pad[0x358];
	_STL::vector<ModelConditionInfo> m_vec;
	SparseMatchFinder<ModelConditionInfo, ModelConditionSetFlags> m_map;
	const ModelConditionInfo *rva0033DCD1(const ModelConditionSetFlags &flags) const;
};

const ModelConditionInfo *Rva0033DCD1::rva0033DCD1(const ModelConditionSetFlags &flags) const
{
	return m_map.findBestInfo(m_vec, flags);
}
