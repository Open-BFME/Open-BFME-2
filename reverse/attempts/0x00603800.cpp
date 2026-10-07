// ??0strstream@_STL@@QAE@PADHH@Z
// partial score=1.0 date=2026-10-07
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <strstream>
template <> void _STL::basic_ios<char,_STL::char_traits<char> >::init(_STL::basic_streambuf<char,_STL::char_traits<char> > *);
// Target 603800..6038D4: complete 212-byte buffer constructor with virtual
// basic_ios at+6C, strstreambuf at+C and strstream vtables C7A8C4/C8/D8.
// STLport 4.5.3 _strstream.h establishes this class and signature; target
// direct calls identify ios_base/basic_iostream/strstreambuf/basic_ios::init.
// The app bit0 uses the existing buffer end (strlen), otherwise its start.
// This constructor is reconstructed from target instructions and declarations;
// the BFME 1 stream-constructor lane was a lead, not a donor of this body.
#include <cstring>
namespace _STL {
strstream::strstream(char *s,int n,ios_base::openmode mode)
 : basic_iostream<char,char_traits<char> >(0),
   _M_buf(s,n,(mode & ios_base::app) ? s + strlen(s) : s)
{
 init(&_M_buf);
}
}
