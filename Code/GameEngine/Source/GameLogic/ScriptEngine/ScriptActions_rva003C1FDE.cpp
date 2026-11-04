// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
// ?rva003C1FDE@Rva003C1FDE@@QAEXABVAsciiString@@PAX@Z @0x003C1FDE 59B
// Display flag via rowed StringBase copy and virtuals.
// Evidence: caller 0x003CDC9C; neighbours 0x003C1FAD 0x003C2662; global TheDisplay.
#include "ascii_string.h"

#include "../../../Include/GameClient/Display.h"

// Display keeps +0x10C protected; this access view only names the byte store.
class Rva003C1FDEDisplayAccess : public Display {
public:
	__forceinline void setField10C(bool value) { field10C = value; }
};

class Rva003C1FDE {
public:
	virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
	virtual void w04(); virtual void w05(); virtual void w06(); virtual void w07();
	virtual void w08(); virtual void w09(); virtual void w10(); virtual void w11();
	virtual void w12(); virtual void w13(); virtual void w14();
	virtual void w15(int x);
	void rva003C1FDE(const AsciiString &a1, bool dead);
};

void Rva003C1FDE::rva003C1FDE(const AsciiString &asciiString, bool dead)
{
	(void)dead;
	w15(1);
	TheDisplay->slot67(asciiString, dead, 0x30);
	static_cast<Rva003C1FDEDisplayAccess *>(TheDisplay)->setField10C(true);
}
