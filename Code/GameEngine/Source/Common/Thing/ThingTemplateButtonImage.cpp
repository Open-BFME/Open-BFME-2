// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0033B580@ThingTemplate@@QAEPBVImage@@XZ @0x0033B580 56B.
// ThingTemplate button-image resolver (ButtonImage slot +0x78/+0x48c).
// BFME1 donor Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp resolveNames
// does TheMappedImageCollection->findImageByName(name) then name.clear() for
// portrait and button; retail splits them. Portrait sibling 0x0033BA46 uses
// +0x74/+0x488 with Portrait assert strings so this adjacent +0x78/+0x48c slot
// is ButtonImage. INI table has SelectPortrait then ButtonImage back to back
// and the ctor NULLs portrait then button. Caller 0x0033C2C2 (ThingTemplate
// resolveNames with prereq vec +0x324) calls 0x33BA46 then this with ecx=esi.
// Fallback tail-jmp caller 0x0033B634 and LivingWorld caller 0x002E1C2B agree.
// Callees rowed: isEmpty 0x1E2F findImageByName 0x2D92F6 releaseBuffer 0x36410.
// Global TheMappedImageCollection at 0x00DFF078.
#include "ascii_string.h"


class Image;

class ImageCollection
{
public:
    const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;


class ThingTemplate
{
public:
    const Image *rva0033B580();
private:
    char m_pad0[0x78];
    AsciiString m_buttonImageName;
    char m_pad7C[0x48c - 0x7c];
    const Image *m_buttonImage;
};

const Image *ThingTemplate::rva0033B580()
{
    if (!m_buttonImageName.isEmpty() && TheMappedImageCollection)
    {
        m_buttonImage = TheMappedImageCollection->findImageByName(m_buttonImageName);
        m_buttonImageName.clear();
    }
    return m_buttonImage;
}
