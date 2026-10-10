// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??1Rva00065288@@UAE@XZ, retail 0x00065288..0x000652CA (66 bytes, EH). A
// W3DModelDrawModuleData-derived module data (name address-derived) that adds
// four AsciiStrings at +0x188; its destructor destroys the array and then
// the W3DModelDrawModuleData base (rowed 0x000C8BE0).
#include "ascii_string.h"

class W3DModelDrawModuleData
{
public:
	virtual ~W3DModelDrawModuleData();
private:
	char m_pad04[0x188 - 4];
};

class __declspec(novtable) Rva00065288 : public W3DModelDrawModuleData
{
public:
	virtual ~Rva00065288();
private:
	AsciiString m_names[4]; // +0x188
};

Rva00065288::~Rva00065288()
{
}
