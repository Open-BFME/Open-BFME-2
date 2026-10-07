// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00524306@Rva00524306@@QAEXABV?$StringBase@D@@@Z @0x00524306 67B.
// Vector erase guarded by TheRva00222A8BTarget: find via rowed
// Rva000BD22FFind then erase via rowed Gen_t vector erase after
// rowed rva00223A94 check. Sibling of 0x005241DF with different callee.
// Prev/next Rva005242D7Chain/Rva00524349Dtor share flags and STL setup.
#include "ascii_string.h"

struct Gen_t_001db910_p4cd;

namespace _STL
{
template <class T> class allocator;
template <class T, class A = allocator<T> > class vector
{
public:
	T *erase(T *pos);
	void push_back(const T &x);
	T *begin() { return _M_start; }
	T *end() { return _M_finish; }
private:
	T *_M_start;
	T *_M_finish;
	T *_M_end;
};
}

StringBase<char> *Rva000BD22FFind(StringBase<char> *first, StringBase<char> *last, const StringBase<char> &val);

class Rva00223A94
{
public:
	int rva00223A94(const AsciiString *key);
};

class Image;

// Native image-store calls use the same manager pointer and target 0x2239E2.
// The verified provider takes a string name and an image pointer.
class Rva002239B2
{
public:
	void rva002239E2(const AsciiString &key, const Image *image);
};

class Rva00222A8BTarget : public Rva00223A94
{
public:
	void rva002239FA(const AsciiString &key, const AsciiString &imageName);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

class Rva00524306
{
public:
	void rva00524306(const StringBase<char> &val);
	void rva00524725(const AsciiString &key, const Image *image);
	void rva00524767(const AsciiString &key, const AsciiString &imageName);
private:
	_STL::vector<Gen_t_001db910_p4cd, _STL::allocator<Gen_t_001db910_p4cd> > m_vec;
};

void Rva00524306::rva00524306(const StringBase<char> &val)
{
	if (TheRva00222A8BTarget == 0)
		return;
	StringBase<char> *found = Rva000BD22FFind((StringBase<char> *)m_vec.begin(), (StringBase<char> *)m_vec.end(), val);
	if (found == (StringBase<char> *)m_vec.end())
		return;
	((Rva00223A94 *)TheRva00222A8BTarget)->rva00223A94((const AsciiString *)&val);
	m_vec.erase((Gen_t_001db910_p4cd *)found);
}

// ?rva00524725@Rva00524306@@QAEXABVAsciiString@@PBVImage@@@Z @0x00524725 66B.
// Set counterpart of the clear above: hand key and image to the guarded
// verified rva002239E2 worker, then record the key once. The eight setters
// in AptImageKeySetters.cpp call it; push_back is the rowed
// vector<AsciiString> body at 0x0042DBE6.
void Rva00524306::rva00524725(const AsciiString &key, const Image *image)
{
	if (TheRva00222A8BTarget == 0)
		return;
	reinterpret_cast<Rva002239B2 *>(TheRva00222A8BTarget)->rva002239E2(key, image);
	if (Rva000BD22FFind((StringBase<char> *)m_vec.begin(), (StringBase<char> *)m_vec.end(), *(const StringBase<char> *)&key) == (StringBase<char> *)m_vec.end())
		((_STL::vector<AsciiString, _STL::allocator<AsciiString> > *)&m_vec)->push_back(key);
}

// ?rva00524767@Rva00524306@@QAEXABVAsciiString@@0@Z @0x00524767 66B.
// Same shape by image name: the target's rva002239FA (pinned) looks the name
// up through ImageCollection::findImageByName.
void Rva00524306::rva00524767(const AsciiString &key, const AsciiString &imageName)
{
	if (TheRva00222A8BTarget == 0)
		return;
	TheRva00222A8BTarget->rva002239FA(key, imageName);
	if (Rva000BD22FFind((StringBase<char> *)m_vec.begin(), (StringBase<char> *)m_vec.end(), *(const StringBase<char> *)&key) == (StringBase<char> *)m_vec.end())
		((_STL::vector<AsciiString, _STL::allocator<AsciiString> > *)&m_vec)->push_back(key);
}
