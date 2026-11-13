// cl: /O1 /G7 /MD /EHsc
// Whole five-byte virtual forwarders retained after the native cursor and
// message handlers moved to their proven complete owner in Rva0042C5C3Dtor.cpp.
#include "../../Include/Common/Rva0042C083Param.h"
class GameMessage;
class Rva0042C0DBDelegate {public:
 virtual void slot0();virtual void slot1();virtual int slot2(GameMessage*);virtual int slot3(const Rva0042C083Param*,int);
 __declspec(noinline) int invokeMessage(GameMessage*);__declspec(noinline) int invokePoint(const Rva0042C083Param*,int);
};
int Rva0042C0DBDelegate::invokeMessage(GameMessage*gameMessage){return slot2(gameMessage);}
int Rva0042C0DBDelegate::invokePoint(const Rva0042C083Param*p,int value){return slot3(p,value);}
