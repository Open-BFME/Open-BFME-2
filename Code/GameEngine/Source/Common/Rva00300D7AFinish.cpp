// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00300D7A@Rva00300D7A@@QAE?AVAsciiString@@XZ retail 0x00300D7A 200B
//
// Finish draft for the banked near miss reverse/attempts/0x00300d7a.cpp.
//
// Maps-directory getter: local "UserData\Maps" when GetRegistryUseLocalUserMaps,
// else GlobalData user dir plus the "Maps" virtual 0x00300489. Rowed format
// 0x38150, StringBase ctor 0x37BA0, set 0x55F5, copy ctor 0x365F0, concat
// 0x6987, releaseBuffer 0x36410, GlobalData::rva002360DE 0x2360DE,
// Rva00300489::rva00300489 0x300489, GetRegistryUseLocalUserMaps 0x235159;
// globals TheWritableGlobalData, empty literal 0x00BBAC1C; callers 0x002DC946
// 0x002DCAE4 0x00300E67 0x00303441.
//
// Retail reads m_data straight out of the hidden return slot of rva002360DE
// (`mov eax,[eax]`) because the string is consumed inside the same
// full-expression; materializing the returned AsciiString into a named local
// made the optimizer reload it from the stack (`mov eax,[ebp-0x14]`). `.str()`
// on the returned temporary keeps the read through the return pointer.
#include "ascii_string.h"

bool GetRegistryUseLocalUserMaps();

class GlobalData
{
public:
	AsciiString rva002360DE() const;
};
extern GlobalData *TheWritableGlobalData;


class Rva00300489
{
public:
	virtual AsciiString rva00300489() const;
};

class Rva00300D7A : public Rva00300489
{
public:
	AsciiString rva00300D7A();
};

static __forceinline void appendStringBase(AsciiString &dst, const AsciiString &src)
{
	((StringBase<char> *)&dst)->concat(*(const StringBase<char> *)&src);
}

AsciiString Rva00300D7A::rva00300D7A()
{
	AsciiString path;
	if (GetRegistryUseLocalUserMaps()) {
		path.format("%s", "UserData\\Maps");
	} else {
		((StringBase<char> *)&path)->set(TheWritableGlobalData->rva002360DE().str());
		appendStringBase(path, Rva00300489::rva00300489());
	}
	return path;
}
