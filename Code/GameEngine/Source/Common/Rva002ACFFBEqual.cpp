// cl: /DNDEBUG /MD
// ?Rva002ACFFBEqual@@YA_NPAV?$StringBase@D@@00@Z @0x002ACFFB (44B): AsciiString range equal.
// Compares [first1,last1) against first2 element-wise via rowed StringBase<char>::compare
// 0x000069D6, returning false on first mismatch and true when the range is exhausted.
// Same shape as STL equal for 4-byte StringBase elements; caller at 0x002ADD9C checks
// sizes then delegates. Prev Rva002ACFD6NewNode stlport next SubsystemNameGetters2.

template <typename T>
class StringBase
{
public:
	int compare(const StringBase<T> &str) const;
private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
};

bool __cdecl Rva002ACFFBEqual(StringBase<char> *first1, StringBase<char> *last1, StringBase<char> *first2)
{
	for (; first1 != last1; ++first1, ++first2) {
		if (first1->compare(*first2) != 0)
			return false;
	}
	return true;
}
