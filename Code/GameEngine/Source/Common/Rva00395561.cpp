// cl: /O1 /G7 /arch:SSE /MD

// ??1Rva00395561@@QAE@XZ @0x00395561 34B (the guard's destructor: retail's EH unwind
// funclets in the map-load/EVA callers call it as the local's dtor)
// Chain: calls 0x000421FD; drains int at +0 while calling global counter.
// Global 0x00DFE78C is TheGameLogic counter owner. Prev stlport list, next disp8.

extern class GameLogic *TheGameLogic;

#include "../../Include/GameLogic/Rva000421FD.h"

#define TheCounter (*(Rva000421FD **)&TheGameLogic)

class Rva00395561
{
	int m_00;
public:
	Rva00395561();
	~Rva00395561();
};

Rva00395561::~Rva00395561()
{
	if (TheCounter)
	{
		while (m_00 > 0)
		{
			--m_00;
			TheCounter->rva000421FD();
		}
	}
}

// Native 0x00395534,45B: preserves the GameLogic +0x1B4 nesting count
// in this four-byte guard while temporarily draining it. Constructor pin
// and adjacent cleanup are paired by native map-load/EVA EH lifetimes;
// WB folds its constructor and cleanup mapping, so native bytes are primary.
Rva00395561::Rva00395561() : m_00(0) {
 if(TheGameLogic) {
  while(*(int*)((char*)TheGameLogic+0x1b4)>0) {
   --*(int*)((char*)TheGameLogic+0x1b4);
   ++m_00;
  }
 }
}
