// cl: /Ob1

struct BfmeElem440
{
	virtual ~BfmeElem440();
	char m[0x58];
	void copyFrom(const BfmeElem440 *src);
};

struct BfmeFalse440
{
};

class BfmeVec440
{
public:
	void push_back(const BfmeElem440 *value);
	void overflow(BfmeElem440 *pos, const BfmeElem440 &value,
		const BfmeFalse440 &, unsigned fill, bool atEnd);

	BfmeElem440 *_M_start;
	BfmeElem440 *_M_finish;
	BfmeElem440 *_M_end_of_storage;
};

void BfmeVec440::push_back(const BfmeElem440 *value)
{
	if (_M_finish != _M_end_of_storage)
	{
		if (_M_finish)
			_M_finish->copyFrom(value);
		++_M_finish;
	}
	else
	{
		overflow(_M_finish, *value, reinterpret_cast<const BfmeFalse440 &>(value), 1, true);
	}
}

// Retail 006BFD30..006BFE59: STLport false-type vector growth for the
// same 0x5C element as the rowed push_back. The native body constructs each
// element through 000929E8 and destroys it by virtual slot zero with flag zero.
// BfmeElem440 retains the donor view name; the constructor's real owner is
// GeometryInfo. Its private fields are outside this worker's observed ABI.
namespace _STL {
template<class T> class allocator;
template<> class allocator<char> {
public: static char *allocate(unsigned int, const void *);
};
}
void Rva00030830FreeAllocation(void *);
struct BfmeElemFC;
BfmeElemFC *bfmeCopyFC(BfmeElemFC *, BfmeElemFC *, BfmeElemFC *);

static inline BfmeElem440 *copy440(BfmeElem440 *first, BfmeElem440 *last, BfmeElem440 *dest)
{
    BfmeElem440 *cur = dest;
    for (; first != last; ++first, ++cur)
        if (cur) cur->copyFrom(first);
    return cur;
}
static inline BfmeElem440 *fill440(BfmeElem440 *first, unsigned int count, const BfmeElem440 &value)
{
    BfmeElem440 *cur = first;
    for (; count > 0; --count, ++cur)
        if (cur) cur->copyFrom(&value);
    return cur;
}
static inline void destroy440(BfmeElem440 *first, BfmeElem440 *last)
{
    for (; first != last; ++first) first->~BfmeElem440();
}
static inline BfmeElem440 *allocate440(unsigned int count)
{
    return count ? reinterpret_cast<BfmeElem440 *>(_STL::allocator<char>::allocate(count * sizeof(BfmeElem440), 0)) : 0;
}
void BfmeVec440::overflow(BfmeElem440 *pos, const BfmeElem440 &value,
    const BfmeFalse440 &tag, unsigned int fill, bool atEnd)
{
    const unsigned int oldSize = _M_finish - _M_start;
    const unsigned int &larger = oldSize < fill ? fill : oldSize;
    const unsigned int newSize = oldSize + larger;
    BfmeElem440 *newStart = allocate440(newSize);
    BfmeElem440 *newFinish = newStart;
    newFinish = copy440(_M_start, pos, newStart);
    if (fill == 1) {
        if (newFinish) newFinish->copyFrom(&value);
        ++newFinish;
    } else newFinish = fill440(newFinish, fill, value);
    if (!atEnd) {
        typedef BfmeElemFC *(*CopyWithTag)(BfmeElemFC *, BfmeElemFC *, BfmeElemFC *, const bool &);
        newFinish = reinterpret_cast<BfmeElem440 *>(reinterpret_cast<CopyWithTag>(&bfmeCopyFC)(
            reinterpret_cast<BfmeElemFC *>(pos), reinterpret_cast<BfmeElemFC *>(_M_finish),
            reinterpret_cast<BfmeElemFC *>(newFinish), atEnd));
    }
    destroy440(_M_start, _M_finish);
    if (_M_start) Rva00030830FreeAllocation(_M_start);
    _M_start = newStart;
    _M_finish = newFinish;
    _M_end_of_storage = newStart + newSize;
}
