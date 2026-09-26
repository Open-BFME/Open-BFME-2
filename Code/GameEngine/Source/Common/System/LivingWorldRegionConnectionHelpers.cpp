// cl: /O1 /DNDEBUG /MD /GX-
// LivingWorldRegionConnection vector helpers (hand-mirrored STLport
// shapes; the _Construct call stays out of line through the declared-only
// template below resolving to the rowed 0x003F2980).
//
// ?Rva003F29D2_CopyRange@@YAPAVLivingWorldRegionConnection@@PAV1@00@Z
// (retail 0x003F29D2, 38 bytes): uninitialized copy of an element range
// through _Construct, returning the result end.
// ?Rva003F29AD_FillRange@@YAPAVLivingWorldRegionConnection@@PAV1@IABV1@@Z
// (retail 0x003F29AD, 37 bytes): uninitialized fill of count elements
// through _Construct, returning the result end.
// ?Rva003F0CA1_DestroyRange@@YAXPAVLivingWorldRegionConnection@@0@Z
// (retail 0x003F0CA1, 24 bytes): forwards a range plus a tag temp to the
// tagged destroy below.
// ?Rva0052BF81_DestroyTagged@@YAXPAVLivingWorldRegionConnection@@0ABU__false_type@_STL@@@Z
// (retail 0x0052BF81, 26 bytes): destroys a range through each element's
// virtual dtor (scalar-deleting slot with a zero flag).
// ?Rva00565A24_ScrapStorage@ConnectionVec@@QAEXXZ (retail 0x00565A24,
// 30 bytes): destroys a vector's range then frees its storage through
// the pinned C++ free at 0x00030830. Serves the grow path at 0x003F2B0B.

namespace _STL
{
struct __false_type
{
};

template <class T1, class T2> void _Construct(T1 *dst, const T2 &src);
}

class LivingWorldRegionConnection
{
public:
	LivingWorldRegionConnection(const LivingWorldRegionConnection &other);
	virtual ~LivingWorldRegionConnection();

private:
	unsigned char m_pad04[0x14];
};

struct ConnectionVec
{
	void Rva00565A24_ScrapStorage();

	LivingWorldRegionConnection *m_start;
	LivingWorldRegionConnection *m_finish;
	LivingWorldRegionConnection *m_end_of_storage;
};

void free(void *block);

// ?Rva003F29D2_CopyRange@@YAPAVLivingWorldRegionConnection@@PAV1@00@Z @0x3F29D2
LivingWorldRegionConnection *Rva003F29D2_CopyRange(LivingWorldRegionConnection *first, LivingWorldRegionConnection *last, LivingWorldRegionConnection *result)
{
	LivingWorldRegionConnection *cur = result;
	for (; first != last; ++first, ++cur)
		_STL::_Construct(&*cur, *first);
	return cur;
}

// ?Rva003F29AD_FillRange@@YAPAVLivingWorldRegionConnection@@PAV1@IABV1@@Z @0x3F29AD
LivingWorldRegionConnection *Rva003F29AD_FillRange(LivingWorldRegionConnection *first, unsigned int count, const LivingWorldRegionConnection &value)
{
	LivingWorldRegionConnection *cur = first;
	for (; count > 0; --count, ++cur)
		_STL::_Construct(&*cur, value);
	return cur;
}

// ?Rva0052BF81_DestroyTagged@@YAXPAVLivingWorldRegionConnection@@0ABU__false_type@_STL@@@Z @0x52BF81
void Rva0052BF81_DestroyTagged(LivingWorldRegionConnection *first, LivingWorldRegionConnection *last, const _STL::__false_type &tag)
{
	for (; first != last; ++first)
		first->~LivingWorldRegionConnection();
}

// ?Rva003F0CA1_DestroyRange@@YAXPAVLivingWorldRegionConnection@@0@Z @0x3F0CA1
void Rva003F0CA1_DestroyRange(LivingWorldRegionConnection *first, LivingWorldRegionConnection *last)
{
	_STL::__false_type tag;
	Rva0052BF81_DestroyTagged(first, last, tag);
}

// ?Rva00565A24_ScrapStorage@ConnectionVec@@QAEXXZ @0x565A24
void ConnectionVec::Rva00565A24_ScrapStorage()
{
	Rva003F0CA1_DestroyRange(m_start, m_finish);
	LivingWorldRegionConnection *start = m_start;
	if (start != 0)
		free(start);
}

