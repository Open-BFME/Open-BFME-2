// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii
//
// ?Rva003BCE69Do@@YGXABVAsciiString@@0H@Z @0x003BCE69 146B: free stdcall best-object select over player mask then cache.
// Evidence: mov ecx,[TheScriptEngine] call ScriptEngine::rva00357475 0x00357475 with (first-AsciiString,0) mask in ebp-4 je; loop ThePlayerList 0x009FEEE8 getEachPlayerFromMask 0x002A7BC9 then Player::rva002ABCF0 0x002ABCF0 with flag and out ptr reusing first-arg slot then Rva002AA497Compare 0x002AA497 keep best; cmp mask jne loop test best je; ScriptEngine::rva00208968 pin 0x00208968 with (second-AsciiString,best) then addObjectToCache 0x0020A5FF with (best,second-AsciiString) ret 0xc; row rva002ABCF0 takes int out holding Object.

#include "ascii_string.h"

class Object;
class Player
{
public:
	int rva002ABCF0(unsigned char flag, int *out);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
	void rva00208968(const AsciiString &name, Object *obj);
	void addObjectToCache(Object *obj, const AsciiString &name);
};
extern class ScriptEngine *TheScriptEngine;

int Rva002AA497Compare(const Object *a, const Object *b);

void __stdcall Rva003BCE69Do(const AsciiString &maskName, const AsciiString &cacheName, int flag)
{
	int mask = TheScriptEngine->rva00357475(maskName, 0);
	Object *best = 0;
	Object *bestCmp = 0;
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player) {
			Object *cur;
			int res = player->rva002ABCF0((unsigned char)flag, (int *)&cur);
			if (cur) {
				if (!bestCmp || Rva002AA497Compare(bestCmp, cur) < 0) {
					bestCmp = cur;
					best = (Object *)res;
				}
			}
		}
	} while (mask != 0);
	if (!best)
		return;
	TheScriptEngine->rva00208968(cacheName, best);
	TheScriptEngine->addObjectToCache(best, cacheName);
}
