// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0060CD16@Rva0060CD16@@QBEIABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z at retail 0x0060CD16 (32B).
// Hashtable bucket-number from string hash: hash key via rowed __stl_string_hash
// 0x0060C9F0 then mod bucket count ((end-start)>>2 from +4/+8). Callers 0x0060D1C8
// and jmp 0x0060CE3C; unblocks 0x0060D1B3. Sibling find 0x0060CAEA shares layout.

#include <string>

namespace _STL
{
size_t __stl_string_hash(const string &__s);
}

class Rva0060CD16
{
public:
	unsigned int rva0060CD16(const _STL::string &__key) const;

private:
	int m_00;
	void *m_04;
	void *m_08;
};

unsigned int Rva0060CD16::rva0060CD16(const _STL::string &__key) const
{
	unsigned int __h = _STL::__stl_string_hash(__key);
	int __count = (reinterpret_cast<int>(m_08) - reinterpret_cast<int>(m_04)) >> 2;
	return __h % __count;
}
