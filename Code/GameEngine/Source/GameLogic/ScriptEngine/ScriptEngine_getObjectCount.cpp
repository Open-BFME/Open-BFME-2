// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?getObjectCount@ScriptEngine@@QBEHHABVAsciiString@@@Z, retail 0x00206255 83B leaf.
// ZH ScriptEngine::getObjectCount; evaluatePlayerLostObjectType 0x003E9EB0 calls it so.
// Evidence: PlayerList::getNthPlayer 0x2A7A29 via ThePlayerList 0xDFEEE8,
// BfmeMemberRV::bfmeAskRV pin 0x2AA231, CRC Rva003ECA13Get 0x3ECA13,
// map<unsigned,void*>::_M_find 0x357180; this+0x1A164 array stride 0xC.
#include <map>
// Preserve the native inline unsigned comparison without an external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<unsigned int>::operator()(const unsigned int &left, const unsigned int &right) const
{ return left < right; }
}


class AsciiString;
unsigned long Rva003ECA13Get(const AsciiString &s);

#include "../../../Include/Common/Player.h"

#include "../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;


#include "../../../Include/Common/BfmeMemberRV.h"

class ScriptEngine
{
public:
	int getObjectCount(int playerIndex, const AsciiString &name) const;

private:
	char m_pad[0x1A164];
	_STL::map<unsigned int, void *> m_maps[8];
};

int ScriptEngine::getObjectCount(int playerIndex, const AsciiString &name) const
{
	Player *player = ThePlayerList->getNthPlayer(playerIndex);
	if (!((BfmeMemberRV *)player)->bfmeAskRV())
		return 0;
	_STL::map<unsigned int, void *> *mapPtr = const_cast<_STL::map<unsigned int, void *> *>(&m_maps[playerIndex]);
	unsigned long crc = Rva003ECA13Get(name);
	_STL::map<unsigned int, void *>::iterator it = mapPtr->find(crc);
	if (it == mapPtr->end())
		return 0;
	return (int)it->second;
}
