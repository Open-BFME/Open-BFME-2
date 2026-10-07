// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native complete RET0 boundaries: 50F1DF..50F1F0 (17 bytes),
// 59B122..59B132 and 5D32C4..5D32D4 (16 bytes each).
// Each extends an independently rowed concat-length call with measured
// integer fields. 50F1DF adds word10 and1; 59B122 adds words18 then10;
// 5D32C4 adds words14 then0C. The first/third call the 2198C8 fold; the
// second calls2DBF50. Rva0059B355Write's rowed narrow materializer also
// consumes the 2DBF50 length plus10/18 fields, and its writers establish
// that layout. The other original receiver names and character widths
// remain unknown. Existing fold spellings below expose only receiver calls;
// none of these consumed-prefix views is allocated or claimed complete.
class AsciiStringPlusString {public:int length() const;};
class AsciiStringPlusText {public:int length() const;};
class Rva0050F1DFPrefix {
public: char unknown00[0x10];int extra;
 int total() const;
};
class Rva0059B122Prefix {
public: char unknown00[0x10];int first;char unknown14[4];int second;
 int total() const;
};
class Rva005D32C4Prefix {
public: char unknown00[0xC];int first;char unknown10[4];int second;
 int total() const;
};
int Rva0050F1DFPrefix::total() const
{
 return reinterpret_cast<const AsciiStringPlusString *>(this)->length()+extra+1;
}
int Rva0059B122Prefix::total() const
{
 return reinterpret_cast<const AsciiStringPlusText *>(this)->length()+second+first;
}
int Rva005D32C4Prefix::total() const
{
 return reinterpret_cast<const AsciiStringPlusString *>(this)->length()+second+first;
}
