// cl: /Od
// stlport46
// ?rva00028C70@Rva00028C70@@QAEHDH@Z @0x00028C70 29B leaf forwarder to STLport 4.6 basic_string<char>::find(char, size_type) const at 0x000274D0; neighbours BfmeTwoHundredSixtySix/Seven /Od; ret 8 registers proven by call
#include <string>

// find's body is instantiated in BfmeConv1301.cpp; do not emit a second copy.
extern template _STL::string::size_type _STL::string::find(char, _STL::string::size_type) const;

class Rva00028C70
{
public:
	int rva00028C70(char a, int b);
};

int Rva00028C70::rva00028C70(char a, int b)
{
	return ((const _STL::string *)this)->find(a, b);
}
