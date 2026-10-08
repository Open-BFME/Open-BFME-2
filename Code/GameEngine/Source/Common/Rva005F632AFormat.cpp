// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva005F632AFormat@@YA?AVUnicodeString@@H@Z retail 0x005F632A 194B
// Evidence: static APT:RankLabel via rowed StringBase ctor 0x37BA0 and atexit; TheGameText slot 0x38 fetch; Unicode format 0x6CB5D0; releaseBuffers 0x36E70; caller 0x005F6407; precedent Rva0052906BUpdate
#include "ascii_string.h"

#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual UnicodeString fetch(const char *label, int x);
	virtual UnicodeString fetch(const AsciiString &label, int x);
};

extern GameTextInterface *TheGameText;

UnicodeString __cdecl Rva005F632AFormat(int rank)
{
	UnicodeString tmp;
	if (rank >= 0) {
		static AsciiString s_rankLabel("APT:RankLabel");
		UnicodeString fetched = TheGameText->fetch(s_rankLabel, 0);
		tmp.format(fetched.str(), rank);
	}
	return tmp;
}
