// cl: /Ireference/shims/bfme2_ascii /MD
// ?Rva00506C82Find@@YAPAVGameSlot@@PBURva00506C82Arg@@@Z @0x00506C82 65B:
// search 8 GameSlots via TheGameInfo->getSlot(i) for slot whose m_ip key
// (NameKeyGenerator->nameToKey at +0x34) equals arg key at +0x50; return slot
// else 0. Callers 0x00506D41 0x00598CDE 0x005AA0FF 0x005AD967 0x005ADAC5
// 0x005ADD7E. Prev AIBaseBuilder /O1 /MD. Honest free-function Find plus Arg
// view; GameSlot m_ip +0x34 from GameSlotSetState, globals TheGameInfo
// and TheNameKeyGenerator DIR32 from retail.
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class GameSlot
{
public:
	char m_pad[0x34];
	AsciiString m_ip;
};

class GameInfo
{
public:
	GameSlot *getSlot(int slotNum);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
};

extern GameInfo *TheGameInfo;
extern NameKeyGenerator *TheNameKeyGenerator;

struct Rva00506C82Arg
{
	char m_pad[0x50];
	int m_50;
};

GameSlot *__cdecl Rva00506C82Find(const Rva00506C82Arg *arg)
{
	if (TheGameInfo != 0) {
		for (int i = 0; i < 8; ++i) {
			GameSlot *slot = TheGameInfo->getSlot(i);
			NameKeyType key = TheNameKeyGenerator->nameToKey(slot->m_ip);
			if (key == arg->m_50)
				return slot;
		}
	}
	return 0;
}
