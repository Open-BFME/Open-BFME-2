// ?d_00047f79@@YAXXZ
// partial score=0.9 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD
// Native 0x00047F79..0x0004802C / 179B, subtitle-start sibling of the
// independently matched update at 0x0004802C (same +0x184/+0x188 fields).
// The manager supplies an AsciiString font name at +0xC and signed font
// size at +0x10. FontLibrary::getFont and SubTitleManager::rva00046A27
// are independently recovered. Sink identity and trailing argument meanings
// remain unknown. The 0x00260865 constructor returns this with ret 0x1C,
// stores the GameFont at +4 and initializes through +0x68. It writes no
// vftable: this view uses a nonvirtual destructor and a 0x6C object, rather
// than the unrelated virtual view used to emit its deleting-dtor wrapper.

class AsciiString;
class GameFont;
class FontLibrary {
public:
    GameFont *getFont(const AsciiString *name, float size, bool bold);
};
extern FontLibrary *TheFontLibrary;

class SubTitleManager {
public:
    void rva00046A27();
    char m_pad[0xC];
    unsigned int m_fontName;
    int m_fontSize;
};

class Rva00260A3C {
public:
    Rva00260A3C(GameFont *font, float a, float b, int c, int d, int e, int f);
    ~Rva00260A3C();
private:
    char m_body[0x6C];
};

class Rva006EE520 {
public:
    bool rva00047F79(SubTitleManager *manager, float a, float b,
        int c, int d, int e, int f);
private:
    char m_pad[0x184];
    SubTitleManager *m_manager;
    Rva00260A3C *m_sink;
};

bool Rva006EE520::rva00047F79(SubTitleManager *manager, float a, float b,
    int c, int d, int e, int f)
{
    Rva00260A3C *old = m_sink;
    if (old) {
        old->Rva00260A3C::~Rva00260A3C();
        ::operator delete(old);
        m_sink = 0;
    }
    m_manager = manager;
    GameFont *font = TheFontLibrary->getFont(
        (const AsciiString *)&manager->m_fontName, (float)manager->m_fontSize, false);
    m_sink = new Rva00260A3C(font, a, b, c, d, e, f);
    m_manager->rva00046A27();
    return true;
}
