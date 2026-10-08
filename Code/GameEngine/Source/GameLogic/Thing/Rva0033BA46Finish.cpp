// ?rva0033BA46@ThingTemplate@@QAEPBVImage@@XZ
// cl: /DNDEBUG /MD /EHsc
//
// ThingTemplate portrait-image resolver, retail 0x0033BA46, 190 bytes.
// BFME1 donor GameEngine/Source/Common/Thing/ThingTemplate.cpp resolveNames
// does TheMappedImageCollection->findImageByName(name) then name.clear() for
// portrait with DEBUG_ASSERTCRASH("%s is looking for Portrait %s but can't find
// it. Skipping..."); retail splits them: button sibling 0x0033B580
// (+0x78/+0x48c, 56B, no debug) and this portrait body with the
// SkipNext/CrashBegin/operator<</CrashDone debug expansion plus the empty string
// global at 0x00BBAC1C for the null data case. INI table has SelectPortrait
// then ButtonImage back to back and the ctor NULLs portrait then button. Callers
// 0x0031D6E1 0x0031D6EC 0x0033C385 0x005F0411 plus tail-jmps 0x0033BC53
// 0x005D234D 0x005D237D 0x005F030F agree. Callees rowed: isEmpty 0x00001E2F
// findImageByName 0x002D92F6 releaseBuffer 0x00036410 plus debug flag
// 0x000387C0 and recordCallsite 0x00038790. Global g_00DFF078.
//
// Recovered from the banked attempt reverse/attempts/0x0033ba46.cpp (score
// 0.93). Two changes over the bank, both fixing the Debug virtual-call ORDER:
// retail invokes CrashBegin (Debug vtable +0x6C) BEFORE it computes either
// string select, then streams both through operator<< (vtable +0x38) and
// finishes at CrashDone (vtable +0x4C), with SkipNext (+0x60) and
// recordCallsite ahead of all of them. The bank chained
// `theDebug->CrashBegin(...) << ...` with both selects hoisted above the call,
// which cl emitted as three pushes of the literal addresses after CrashDone.
// Naming the CrashBegin receiver and moving both selects behind it into the
// file-scope strOf helper restores the retail sequence and lands the body at
// the exact 190-byte size; the bank emitted 189 with the selects hoisted above
// the call (which needs a frame) and 186 with them inlined at the use.
//
// Remaining residue is the callee-saved register roles: retail keeps `this` in
// ESI and the portrait-name base in EDI across the whole debug block, while
// this toolchain keeps `this` in EBX and the portrait base in ESI, so every
// `[esi+...]` in the block becomes `[ebx+...]` and the two pops swap. See the
// re_log row for the spellings tried.
//
// class-gate: allow AsciiString retail rva0033BA46 tests only m_data and calls
// the releaseBuffer worker; the shared header's str() and isEmpty() inline a
// length check retail does not emit here, so folding it in changes the bytes
template <typename T>
class StringBase
{
public:
    bool isEmpty() const;
    void clear() { releaseBuffer(); }
    void *m_data;
private:
    void releaseBuffer();
};

class AsciiString : public StringBase<char>
{
};

class Image;

class ImageCollection
{
public:
    const Image *findImageByName(const AsciiString &name);
};

extern class ImageCollection *TheMappedImageCollection;

bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

class Debug
{
public:
    virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
    virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
    virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
    virtual void pad12(); virtual void pad13();
    virtual Debug &operator<<(const char *str);
    virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
    virtual bool CrashDone(int mode);
    virtual void pad20(); virtual void pad21(); virtual void pad22();
    virtual void SetCrashAddress(void *returnAddress, int set);
    virtual void SkipNext();
    virtual void pad25(); virtual void pad26();
    virtual Debug &CrashBegin(const char *file, int line, int reserved);
};

extern Debug *theDebug;

static const char *strOf(const AsciiString &s)
{
    return s.m_data != 0 ? (const char *)s.m_data + 8 : "";
}

class ThingTemplate
{
public:
    const Image *rva0033BA46();
private:
    char m_pad0[0x64];
    AsciiString m_name;
    char m_pad68[0x74 - 0x68];
    AsciiString m_portraitName;
    char m_pad78[0x488 - 0x78];
    const Image *m_portraitImage;
};

const Image *ThingTemplate::rva0033BA46()
{
    if (!m_portraitName.isEmpty() && TheMappedImageCollection != 0)
    {
        m_portraitImage = TheMappedImageCollection->findImageByName(m_portraitName);
        if (bfmeRva000387C0())
        {
            _bfme_debugRecordCallsite(1);
            theDebug->SkipNext();
            Debug &dbg = theDebug->CrashBegin(0, 0, 0);
            (dbg << strOf(m_name) << " is looking for Portrait " << strOf(m_portraitName) << " but can't find it. Skipping...").CrashDone(2);
        }
        m_portraitName.clear();
    }
    return m_portraitImage;
}