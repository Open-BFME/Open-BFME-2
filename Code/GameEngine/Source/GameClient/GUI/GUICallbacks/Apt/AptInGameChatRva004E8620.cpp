// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva004E8620@AptInGameChat@@UAEHXZ, retail 0x004E8620 (80 bytes): slot 5 of
// AptInGameChat's GameWindow vtable 0x00C62630, the chat screen's close for
// its receiver type (+0x27C, chosen by the opener in AptInGameChat.cpp). Type
// 2 closes through the rowed Rva004E855CClose; type 4 tells the window's
// +0x210 object (rowed getter 0x00314126) slot 3 with 0, destroys it with the
// global delete and then pokes TheIMEManager's slot 15. Always 1. Address
// name: class and slot proven, method identity not.
class Rva00314126DwordField
{
public:
	int get() const;
};

void __cdecl Rva004E855CClose();

class Rva004E8620Child
{
public:
	virtual void s0();
	virtual ~Rva004E8620Child();
	virtual void s2();
	virtual void s3(int value);
};

class IMEManagerInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15();
};
// WinMain owns the global at native VA 0x00DFE728 as IMEManager *.
// Retain this callback's slot-only view when accessing that existing owner.
class IMEManager;
extern IMEManager *TheIMEManager;

#include "../../../../../Include/GameClient/Bfme2GameWindow.h"

class AptInGameChat : public GameWindow
{
public:
	virtual int rva004E8620();
private:
	unsigned char m_pad218[0x27C - 0x218];
	int m_receiverType;		// +0x27C
};

int AptInGameChat::rva004E8620()
{
	if (m_receiverType == 2)
		Rva004E855CClose();
	else if (m_receiverType == 4)
	{
		Rva004E8620Child *child = (Rva004E8620Child *)((Rva00314126DwordField *)this)->get();
		if (child == 0)
			return 1;
		child->s3(0);
		::delete child;
		if (TheIMEManager)
			((IMEManagerInterface *)TheIMEManager)->s15();
	}
	return 1;
}
