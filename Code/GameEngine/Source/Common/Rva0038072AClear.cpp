// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
// ?Rva0038072AClear@@YAXXZ @0x0038072A 67B unlock between 0x00380724 and 0x003807AA.
// Clears tooltip via manager then Apt owner then Free then MessageBox tail.
// Evidence: TheTooltipString 0x00A022E4 via 0x009FEAD8 slot 0x3C then null;
// TheRva00222A8BOwner 0x009C06A0 cmp -1 then g_bfmeAptWindowManager 0x009FE4CC
// method 0x00224B7D then -1; rowed 0x00380705Free then tail rowed 0x0054C729;
// caller at 0x0023AE30; prev 0x00380724 next 0x003807AA share small-leaf shape.
class DisplayString;
class DisplayStringManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(DisplayString *s);
};

extern DisplayString *TheTooltipString;
extern DisplayStringManager *TheDisplayStringManager;
extern void *TheRva00222A8BOwner;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00224B7DTarget
{
public:
	bool method(int v);
};

void __cdecl Rva00380705Free();

class AptStrategicMessageBox
{
public:
	static void rva0054C729();
};

void Rva0038072AClear()
{
	if (TheTooltipString)
	{
		TheDisplayStringManager->slot15(TheTooltipString);
		TheTooltipString = 0;
	}
	if (TheRva00222A8BOwner != (void *)-1)
	{
		((Rva00224B7DTarget *)g_bfmeAptWindowManager)->method((int)TheRva00222A8BOwner);
		TheRva00222A8BOwner = (void *)-1;
	}
	Rva00380705Free();
	AptStrategicMessageBox::rva0054C729();
}
