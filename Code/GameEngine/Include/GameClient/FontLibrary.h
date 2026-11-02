// Target facts (code addresses are RVAs; table addresses are VAs): FontLibrary is polymorphic. Constructor 0x00218942 calls SubsystemInterface's constructor 0x001B4E63 at 0x00218954 and stores its own table 0x00BE5AD0 at 0x00218960. Destructor 0x00218415 stores the same table at 0x00218426 and calls the parent destructor 0x001B4E74 at 0x00218456. The parent's constructor/destructor store 0x00BD77A0 for the base lifetime. Factory 0x0004C4F9 allocates 0x2C bytes at 0x0004C505, calls FontLibrary's constructor at 0x0004C51D, then installs W3DFontLibrary's table 0x00BC4818 at 0x0004C522.
// Table 0x00BE5AD0 has sixteen slots before the next table at 0x00BE5B10: 0=deleting destructor 0x002189A9 (calls 0x00218415), 1=init 0x00217561, 2=SubsystemInterface::loadIniFilesFromLegend 0x001B5384, 3/8/10/12=0x000B3FD0 (ret), 4/11=0x005CB9FF (false, ret 4), 5=0x0047A699 (false), 6=0x000D43D0 (zero), 7/13/15=0x0047A69C (ret 4), 9=reset 0x00218BEF, 14=__purecall 0x0003B810. Slots 0-13 retain the registered parent's order. Styled lookup 0x0021857E calls slot 14 at 0x00218667; deleteAllFonts 0x00217449 calls slot 15 at 0x0021745A. W3DFontLibrary overrides those slots with loadFontData 0x000902A6 and releaseFontData 0x00090000; Zero Hour GameFont.h supplies their names and the empty update/release defaults.
// The parent occupies +0..+0x0B: its constructor writes byte +4 at 0x001B4E6F and the four-byte string at +8 at 0x001B4E6B; its destructor destroys that string at 0x001B4E7A. FontLibrary's constructor clears list +0x0C and count +0x10 at 0x00218977/0x0021897B and constructs map members at +0x14/+0x20 through 0x0033C432 at 0x00218966/0x00218972. Destructor calls 0x00217FEA/0x00217FB2 on +0x20/+0x14 at 0x0021843F/0x0021844B. Allocation and these boundaries give sizeof 0x2C and two 12-byte map storage regions; their template identities remain unspecified. unlinkFont 0x002173FA and styled lookup 0x0021857E access the list/count at those offsets; Zero Hour supplies m_fontList/m_count names.
// Out-of-line declarations follow the ledger: constructor 0x00218942, destructor 0x00218415, init 0x00217561, reset 0x00218BEF, getFont 0x002189E1, rva0021857E 0x0021857E, rva002186A6 0x002186A6, rva00218468 0x00218468, unlinkFont 0x002173FA, deleteAllFonts 0x00217449, ParseFontDefaultSettings 0x00218C82 and parseFontSizeMapping 0x00218E96. getFont's ledger signature takes const AsciiString*, float and bool; no additional overload or copy body is supplied.
#ifndef BFME2_FONTLIBRARY_H
#define BFME2_FONTLIBRARY_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class GameFont;
class INI;

class FontLibrary : public SubsystemInterface
{
public:
    FontLibrary();
    virtual ~FontLibrary();
    virtual void init();
    virtual void reset();
    virtual void update() {}

    GameFont *getFont(const AsciiString *name, float pointSize, bool bold);
    GameFont *rva0021857E(const AsciiString *name, float pointSize, bool bold, int style);
    void *rva002186A6(const AsciiString *name, float pointSize);
    void rva00218468(const AsciiString *name, float *pointSize, bool *bold);
    static void ParseFontDefaultSettings(INI *ini);
    static void parseFontSizeMapping(INI *ini, void *instance, void *store, const void *userData);

protected:
    void unlinkFont(GameFont *font);
    void deleteAllFonts();
    virtual bool loadFontData(GameFont *font) = 0;
    virtual void releaseFontData(GameFont *font) {}

    GameFont *m_fontList;
    int m_count;
    unsigned char field14[0x0C];
    unsigned char field20[0x0C];
};

#endif
