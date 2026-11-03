// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?setObjectCount@ScriptEngine@@QAEXHABVAsciiString@@H@Z, retail 0x00207DF4 50B.
// ZH ScriptEngine::setObjectCount; evaluatePlayerLostObjectType 0x003E9EB0 calls it so.
// Unlock lane: thiscall store of an Image* into the ImageSubscriptMap at
// this+0x1a164[index] under the CRC key of an AsciiString name. Evidence: rowed
// callee ?Rva003ECA13Get@@YAKABVAsciiString@@@Z at 0x003ECA13 and rowed
// ??AImageSubscriptMap@@QAEAAPAVImage@@ABI@Z at 0x002077D6; caller 0x003E9EB0.
#include "ascii_string.h"

class Image;

#include "../../../../GameEngine/Include/GameClient/ImageSubscriptMap.h"

unsigned long Rva003ECA13Get(const AsciiString &s);

class ScriptEngine
{
public:
	void setObjectCount(int index, const AsciiString &name, int newCount);
private:
	unsigned char m_pad[0x1a164];
	ImageSubscriptMap m_maps[1];
};

void ScriptEngine::setObjectCount(int index, const AsciiString &name, int newCount)
{
	unsigned int key = Rva003ECA13Get(name);
	m_maps[index][key] = (Image *)newCount;
}
