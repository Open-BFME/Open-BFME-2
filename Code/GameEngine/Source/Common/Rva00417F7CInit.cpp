// cl: /O1 /DNDEBUG /MD /EHsc
// ??0Rva00417F7C@@QAE@ABV?$StringBase@D@@@Z @0x00417F7C 62B.
// Ctor takes const StringBase<char>& at [ebp+8] for member
// at +0 via rowed private copy 0x000365F0, BitFlags<11> at +4 via rowed
// default 0x003B31AD, BfmeVNITree at +8 via pinned 0x005011C1. EH via /EHsc
// with StringBase dtor. Caller 0x004183E7, unblocks 0x004183AC.
template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	~StringBase();
private:
	StringBase(const StringBase &other);
	friend class Rva00417F7C;
	T *m_data;
};

template <int NUM_BITS>
class BitFlags
{
public:
	BitFlags();
private:
	unsigned int m_words[1];
};

class BfmeVNITree
{
public:
	BfmeVNITree();
};

class Rva00417F7C
{
public:
	Rva00417F7C(const StringBase<char> &src);
private:
	StringBase<char> m_0;
	BitFlags<11> m_4;
	BfmeVNITree m_8;
};

Rva00417F7C::Rva00417F7C(const StringBase<char> &src)
	: m_0(src)
	, m_4()
	, m_8()
{
}
