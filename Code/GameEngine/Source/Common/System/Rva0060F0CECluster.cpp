// cl: /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// stlport
//
// XferSaveAsText (text-dumping Xfer, vtable 0x00C7B388) stream-attach worker
// at 0x0060F0CE, 43 bytes. Layout taken from BfmeRva00C7B388Xfer.cpp: +4 is
// the one-shot pending-label flag, +8 the stream sink, +0x0C the
// vector<basic_string<char>> open-block stack. The body refuses a second
// attach, stores the stream, clears the open-block vector with the STLport
// range erase (pinned 0x0007A7AA), clears the label flag and reports success.
// No source names the class or this method, so both keep address-derived
// names; the member meanings are target evidence from the sibling bodies.

class BfmeRva00C7B388Stream;

#include <vector>
#include <string>

namespace _STL
{
// Bind the range erase to the rowed 0x0007A7AA worker.
typedef basic_string<char, char_traits<char>, allocator<char> > BfmeNarrowString;
template <> BfmeNarrowString *vector<BfmeNarrowString, allocator<BfmeNarrowString> >::erase(BfmeNarrowString *first, BfmeNarrowString *last);
}

class XferSaveAsText
{
public:
	virtual ~XferSaveAsText();

	bool rva0060F0CE(BfmeRva00C7B388Stream *stream);

private:
	bool m_bfme04;					// +0x04
	BfmeRva00C7B388Stream *m_bfme08;	// +0x08
	char m_bfme0C[12];				// +0x0C: vector<basic_string<char>>
};

bool XferSaveAsText::rva0060F0CE(BfmeRva00C7B388Stream *stream)
{
	if (m_bfme08 != 0)
		return false;
	m_bfme08 = stream;
	typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > NarrowString;
	typedef _STL::vector<NarrowString, _STL::allocator<NarrowString> > NarrowStringVec;
	NarrowStringVec *vec = (NarrowStringVec *)&m_bfme0C;
	vec->erase(vec->begin(), vec->end());
	m_bfme04 = false;
	return true;
}
