// cl: /O1 /DNDEBUG /MD
//
// ?findBestInfoSlow@?$SparseMatchFinder@UModelConditionInfo@@V?$BitFlags@$0HF@@@@@ABEPBUModelConditionInfo@@ABV?$vector@UModelConditionInfo@@V?$allocator@UModelConditionInfo@@@_STL@@@_STL@@ABV?$BitFlags@$0HF@@@@Z
// @0x0033BDF8 115B.
//
// SparseMatchFinder<ModelConditionInfo, BitFlags<117>>::findBestInfoSlow:
// linear best-match scan over the info vector, scoring each entry by
// intersection popcount (0x0033ADFC, pinned countIntersection) with the
// inverse-intersection popcount (0x0033AE53, rowed) breaking ties toward
// fewer extra bits. Initial best (0, 999) means an empty vector returns
// null. Called by findBestInfo 0x0033D46A when the map lookup misses.
//
// Evidence: the BitFlags117CountInverseIntersection TU names this address as
// the pinned caller; calls flow as thiscall on the flags arg with the entry
// flags at element+4 (the lea), stride 0x368 (sizeof the info record),
// cached vector end in [ebp-0x10], and the jg/jl/jge selection which the
// (a > b || (a >= b && c)) spelling reproduces exactly. The f reference
// promotes to the [ebp+8] cursor induction variable (reusing the dead vector
// slot); the end cache explains the end slot.
//
// ModelConditionInfo is mirrored minimally: only the +4 flags member and
// the 0x368 extent are target-proven; +0 and the tail pad carry no identity
// claim. The _STL vector mirror is layout-only (stlport start/finish/end);
// its begin/end emit 3-4B loads no other TU currently emits.
template <int Bits>
class BitFlags
{
public:
	int countIntersection(const BitFlags &that) const;
	int countInverseIntersection(const BitFlags &that) const;

private:
	unsigned m_words[(Bits + 31) / 32];
};

struct ModelConditionInfo
{
	void *m_00; // +0 (unread by this body; type unproven)
	BitFlags<117> m_flags; // +4
	char m_pad[0x368 - 4 - 16]; // extent to the 0x368 stride; content unproven
};

namespace _STL
{
	template <class T>
	class allocator
	{
	};
	template <class T, class Ax>
	class vector
	{
	public:
		const T *begin() const { return _M_start; }
		const T *end() const { return _M_finish; }

	private:
		T *_M_start;
		T *_M_finish;
		T *_M_end;
	};
}

template <class T, class F>
class SparseMatchFinder
{
private:
	const T *findBestInfoSlow(const _STL::vector<T, _STL::allocator<T> > &v, const F &flags) const;
};

template <class T, class F>
const T *SparseMatchFinder<T, F>::findBestInfoSlow(const _STL::vector<T, _STL::allocator<T> > &v, const F &flags) const
{
	const T *best = 0;
	int bestCount = 0;
	const T *info = v.begin();
	int bestInverse = 999;
	const T *end = v.end();
	for (; info != end; ++info) {
		const F &f = info->m_flags;
		int inter = flags.countIntersection(f);
		int inv = flags.countInverseIntersection(f);
		if (inter > bestCount || (inter >= bestCount && inv < bestInverse)) {
			best = info;
			bestCount = inter;
			bestInverse = inv;
		}
	}
	return best;
}

template class SparseMatchFinder<ModelConditionInfo, BitFlags<117> >;
