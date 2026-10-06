// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// stlport
// ??0Rva002AABEE@@QAE@VAsciiString@@IABV?$vector@IV?$allocator@I@_STL@@@_STL@@ABV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@3@@Z @0x002AF581 (110B): ctor builds level-value record.
// Evidence: StringBase copy at +0 from by-value AsciiString then level +4 then vector<unsigned int> copy at +8 then vector<AsciiString> copy at +0x14 then float 0 at +0x20 then refresh call 0x002AABEE; ret 0x10; Rva002AABEELevelValue.cpp names the record layout.
#include "ascii_string.h"
#include <vector>

class Rva002AABEE
{
public:
	Rva002AABEE(AsciiString name, unsigned int level, const _STL::vector<unsigned int, _STL::allocator<unsigned int> > &values, const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &list);
	void rva002AABEE() throw();
private:
	AsciiString m_name;
	unsigned int m_level;
	_STL::vector<unsigned int, _STL::allocator<unsigned int> > m_values;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_list;
	float m_value;
};

Rva002AABEE::Rva002AABEE(AsciiString name, unsigned int level, const _STL::vector<unsigned int, _STL::allocator<unsigned int> > &values, const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &list)
	: m_name(name), m_level(level), m_values(values), m_list(list), m_value(0.0f)
{
	rva002AABEE();
}
