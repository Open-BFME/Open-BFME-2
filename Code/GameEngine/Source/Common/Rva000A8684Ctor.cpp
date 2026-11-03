// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native74B constructorA8684 belongs to the24B Miles audio request allocated
// at51107 and stack-built by55951. Request kind0, event holder4, handle8,
// audio-file handleC and flags10..14 agree with the established request users
// in MilesAudioManager.cpp. The original class identity remains unresolved.
// Native state0 action760CB3 loads the saved receiver, adds4 and jumps to the
// complete18B BfmePoolRef10 destructor519AB. Existing complete64B teardown
// A86CE releases the same event's+88 reference after the file handleA8A37.
// These target facts replace the former AsciiString/UnicodeString guesses.
// Both complete74B owner and native associative EH graph verify exact.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
class BfmePoolHolder88;
#include "../../Include/Common/BfmePoolRef10.h"
class Rva00690FF0Handle
{
public:
	Rva00690FF0Handle();
	~Rva00690FF0Handle();
private:
	void *m_handle;
};
class Rva000A8684
{
public:
	Rva000A8684();
private:
	int m_0;
	BfmePoolRef10 m_4;
	int m_8;
	Rva00690FF0Handle m_str;
	volatile unsigned char m_10;
	volatile unsigned char m_11;
	volatile unsigned char m_12;
	volatile unsigned char m_13;
	volatile unsigned char m_14;
	char m_pad15;
	char m_pad16;
	char m_pad17;
};

Rva000A8684::Rva000A8684()
	: m_0(0)
	, m_4()
	, m_8(1)
	, m_str()
	, m_10(0)
	, m_11(0)
	, m_12(0)
	, m_13(0)
	, m_14(0)
{
}
