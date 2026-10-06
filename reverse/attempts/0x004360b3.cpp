// ?Rva004360B3@@YAPAUTreeHintOpaque0043671B@@VAsciiString@@@Z
// partial score=0.8 date=2026-10-06
// ?Rva004360B3@@YAPAUTreeHintOpaque0043671B@@VAsciiString@@@Z
// partial score=0.8 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// Retail 0x004360B3 (67 bytes): look up an AsciiString key in the saved-game
// TreeHint map at 0x00E032EC and return the mapped value, or null.
// Target evidence: the body passes its by-value string parameter to the
// generic AsciiString tree-find worker at 0x005F8437, compares the returned
// node with the header pointer stored at 0x00E032EC, and returns node+0x14.
// Its caller 0x004361B3 builds the key from the printed 16-byte game digest.
// The adjacent 0x00435CE0 constructor and 0x00436E3B insert chain support the
// AsciiString-to-TreeHint map specialization; the mapped object's semantic
// type remains opaque beyond the independently established 0xDF4-byte layout.

#include "ascii_string.h"

struct TreeHintOpaque0043671B;
struct SavedGameTreeHintNode004360B3;

// Local ABI view of the shared key-only tree-find worker. The synthetic shim
// name makes no claim about the retail map's application-level class name.
class SavedGameTreeHintMapFindShim
{
public:
	SavedGameTreeHintNode004360B3 *_M_find(const AsciiString &key) const;
	SavedGameTreeHintNode004360B3 *m_header;
};

TreeHintOpaque0043671B *Rva004360B3(AsciiString key)
{
	SavedGameTreeHintMapFindShim *games = (SavedGameTreeHintMapFindShim *)0x00E032EC;
	SavedGameTreeHintNode004360B3 *entry = games->_M_find(key);
	if (entry == games->m_header)
		return 0;
	return (TreeHintOpaque0043671B *)((char *)entry + 0x14);
}
