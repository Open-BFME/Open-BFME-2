// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00206255@Rva00206255@@QAEPAXHABVAsciiString@@@Z, retail 0x00206255 83B leaf.
// Evidence: PlayerList::getNthPlayer 0x2A7A29 via ThePlayerList 0xDFEEE8,
// BfmeMemberRV::bfmeAskRV pin 0x2AA231, CRC Rva003ECA13Get 0x3ECA13,
// map<unsigned,void*>::_M_find 0x357180; this+0x1A164 array stride 0xC.
#include <map>

class AsciiString;
unsigned long Rva003ECA13Get(const AsciiString &s);

class Player
{
};

class PlayerList
{
public:
	Player *getNthPlayer(int i);
};
extern PlayerList *ThePlayerList;


class BfmeMemberRV
{
public:
	bool bfmeAskRV();
};

class Rva00206255
{
public:
	void *rva00206255(int playerIndex, const AsciiString &name);

private:
	char m_pad[0x1A164];
	_STL::map<unsigned int, void *> m_maps[8];
};

void *Rva00206255::rva00206255(int playerIndex, const AsciiString &name)
{
	Player *player = ThePlayerList->getNthPlayer(playerIndex);
	if (!((BfmeMemberRV *)player)->bfmeAskRV())
		return 0;
	_STL::map<unsigned int, void *> *mapPtr = &m_maps[playerIndex];
	unsigned long crc = Rva003ECA13Get(name);
	_STL::map<unsigned int, void *>::iterator it = mapPtr->find(crc);
	if (it == mapPtr->end())
		return 0;
	return it->second;
}
