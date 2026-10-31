// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native000B0565..000B059B: 54B RET8 resize wrapper. The three vector
// words are byte pointers; the second by-value argument is passed by address
// to the existing unsigned-byte fill-insert provider at000AFE9F. Only that
// byte is consumed. The original wrapper class/method spelling is unknown.
// STLport4.5.3 _vector.h resize is the semantic guide; this native ABI takes
// the value directly rather than the library overload's const reference.
// Calls from WorldHeightMap parseBlendTileData000B1173 establish byte-array
// storage at owner offsets28/38/44/50/5C/68/74/80/8C and values0/255.
// The unsigned-byte erase instantiation is an exact34B relocation twin of
// retail's existing void-pointer erase31BD55. It is emitted for fold proof;
// this source does not assert an additional retail erase address.
#include <vector>
namespace _STL {
extern template void vector<unsigned char>::_M_fill_insert(unsigned char *,unsigned int,const unsigned char &);

}
class Rva000B0565 : public _STL::vector<unsigned char>
{
public:
	void rva000B0565(unsigned int,unsigned char);
};
void Rva000B0565::rva000B0565(unsigned int count,unsigned char value) {
    if(count<size()) erase(begin()+count,end());
    else insert(end(),count-size(),value);
}

template unsigned char *_STL::vector<unsigned char>::erase(unsigned char *,unsigned char *);
