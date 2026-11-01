// cl: /DNDEBUG /MD
// ?rva00206D91@Rva00206D91@@QAE?AUAudioCacheCursor@@XZ, retail 0x00206D91, 19B.
// Target evidence: RET4 hidden-result forwarder that adjusts this by +0xC and
// calls the ICF-shared STLport hashtable begin() 0x00427195, returning its
// iterator through the same hidden pointer: an owner with a hash container at
// +0xC exposing begin(). The owner and the container's element type are
// unresolved; the callee is bound through the ledger's neutral
// Rva000427195 spelling (AudioFileCacheDestructor.cpp), with the same
// two-word cursor result type. No direct callers were found.
struct AudioCacheCursor {
	struct { void *first, *second; } s;
	AudioCacheCursor(void *a, void *b) { s.first = a; s.second = b; }
	AudioCacheCursor(const AudioCacheCursor &audioCacheCursor) { s.first = audioCacheCursor.s.first; s.second = audioCacheCursor.s.second; }
};

#include "../../Include/GameLogic/Rva000427195.h"

class Rva00206D91
{
public:
	AudioCacheCursor rva00206D91();
private:
	char m_pad00[0xC];
	Rva000427195 m_table;
};

AudioCacheCursor Rva00206D91::rva00206D91()
{
	return m_table.rva00427195();
}

// ?rva001F87BF@Rva001F87BF@@QAE?AUAudioCacheCursor@@XZ, retail 0x001F87BF
// (22B): the same forwarder over a hash container at +0x88.
class Rva001F87BF
{
public:
	AudioCacheCursor rva001F87BF();
private:
	char m_pad00[0x88];
	Rva000427195 m_table;
};

AudioCacheCursor Rva001F87BF::rva001F87BF()
{
	return m_table.rva00427195();
}
