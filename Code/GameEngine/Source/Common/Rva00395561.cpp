// cl: /O1 /G7 /arch:SSE /MD

// ?rva00395561@Rva00395561@@QAEXXZ @0x00395561 34B
// Chain: calls 0x000421FD; drains int at +0 while calling global counter.
// Global 0x00DFE78C is TheGameLogic counter owner. Prev stlport list, next disp8.

extern class GameLogic *TheGameLogic;

class Rva000421FD
{
public:
	void rva000421FD();
};

#define TheCounter (*(Rva000421FD **)&TheGameLogic)

class Rva00395561
{
	int m_00;
public:
	Rva00395561();
	void rva00395561();
};

void Rva00395561::rva00395561()
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
