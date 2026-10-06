// cl: /Ireference/shims/bfme2_ascii /EHsc

// ??0Rva00222719Temp@@QAE@ABVUnicodeString@@@Z, retail 0x00222719, 49 bytes.
// EH temp copy via wide set: m_data null then set from source. Stack temp for Apt text setters 0x225299 plus 0x225301 plus 24 other callers. No donor; honest address class.
#include "unicode_string.h"


class Rva00222719Temp
{
public:
	Rva00222719Temp(const UnicodeString &src);
private:
	UnicodeString m_str;
};

Rva00222719Temp::Rva00222719Temp(const UnicodeString &src) : m_str()
{
	m_str.set(src);
}
