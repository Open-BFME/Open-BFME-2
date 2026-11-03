// Target facts (code addresses are RVAs; table addresses are VAs): constructor 0x002175BA stores 0x00BE5AAC at +0 and clears the four-byte string at +8. Destructor 0x00217537 restores that same table, adjusts this by +8 and tail-calls StringBase<char>::releaseBuffer at 0x00036410. Table 0x00BE5AAC contains one slot, deleting destructor 0x00217545, which calls 0x00217537 and conditionally operator delete at 0x0002FD60; the next word at 0x00BE5AB0 starts a string. GameFont is polymorphic with only the destructor slot, consistent with the registered MemoryPoolObject parent; its constructor and destructor contain no separate base-table store or base call.
// Styled font lookup 0x0021857E allocates 0x20 bytes at 0x0021861C/0x0021861E and installs 0x00BE5AAC at 0x00218628. It compares the float pointSize at +0x0C (0x002185E9), byte bold at +0x18 (0x002185FB), and four-byte m_1C (0x00218600), compares the AsciiString at +8 through 0x000069D6 (0x00218609/0x0021860C), and follows next at +4 (0x00218615). Stores at 0x00218653/0x00218657/0x0021865C/0x0021865F initialize fontData, pointSize, bold and field1C. FontLibrary's list helper 0x002173E3 writes next at +4 (0x002173EE), and unlinkFont 0x002173FA clears it at 0x0021743E.
// W3DFontLibrary::loadFontData 0x000902A6 reads nameString at +8 (0x000902C5), pointSize at +0x0C (0x000902B6), bold at +0x18 (0x000902D8), and m_1C at +0x1C (0x000902DF), stores the device pointer at +0x14 (0x000902FD), and copies its integer height from +0x2C to GameFont +0x10 (0x00090300/0x00090303). These accesses and the allocation establish sizeof 0x20. Zero Hour GameClient/GameFont.h supplies the class-key, MemoryPoolObject inheritance, and next/nameString/pointSize/height/fontData/bold names; BFME2's pointSize is float and the additional +0x1C field has no proven donor name. The rowed constructor and virtual destructor are declared out of line.
#ifndef BFME2_GAMEFONTCLASS_H
#define BFME2_GAMEFONTCLASS_H

#include "../Common/MemoryPoolObject.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class GameFont : public MemoryPoolObject
{
public:
    GameFont();
    virtual ~GameFont();

    GameFont *next;
    AsciiString nameString;
    float pointSize;
    int height;
    void *fontData;
    bool bold;
    int m_1C;
};

typedef char GameFontSizeIs0x20[(sizeof(GameFont) == 0x20) ? 1 : -1];

#endif
