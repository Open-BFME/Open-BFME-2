// cl: /O1 /MD /EHsc
// Native 275F3F..27601B RET0; WB CAC950 and ZH Drawable::drawDisabled.
// Reference: Open-BFME-1 a7c38d3b2597121f178ab5190b3062478823257d,
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/Drawable.cpp.
// BFME2 keeps the health-bar bounds on the receiver and tests disabled bits 2/6.
// Retain the existing neutral method owner used by the 2796D9 dispatcher.
// The allocation is a normal new expression: retail homes the allocation for
// constructor-failure cleanup, not an empty catch around a stdcall factory.

class Anim2DTemplate;
class Anim2DCollection;
class Anim2D
{
public:
    Anim2D(Anim2DTemplate *, Anim2DCollection *);
    unsigned int getCurrentFrameWidth() const;
    unsigned int getCurrentFrameHeight() const;
private:
    // The owned constructor at 2D6D63 initializes this 52-byte object.
    unsigned char storage[0x34];
};

class Rva002D7127
{
public:
    void queue(int x, int y, int width, int height);
};

class Rva00270025
{
public:
    virtual ~Rva00270025();
    void rva0027006C(int icon);
    Anim2D *icons[14];
    int values[14];
};

class Rva00270BA8
{
public:
	Rva00270025 *rva00270BA8();
	char m_pad00[0x354];
private:
	Rva00270025 *m_354; // +0x354
};

struct DrawableDisabledObjectView
{
    unsigned char unreconstructed[0x1C8];
    unsigned char disabledFlags;
};

struct Rva002D752DNode;
class Drawable
{
    friend class Rva00275F3FHost;
    // Existing definition in Common/Rva00270190.cpp; no new data alias.
    // Private, as there and in the other Drawable units (ZH Drawable.h).
    static Rva002D752DNode **s_animationTemplates;
};
extern Anim2DCollection *TheAnim2DCollection;
#include <new>

class Rva00275F3FHost
{
public:
    void rva00275F3F();
private:
    unsigned char unreconstructed000[0xFC];
    DrawableDisabledObjectView *object;
    unsigned char unreconstructed100[0x354 - 0x100];
    Rva00270025 *iconInfo;
    unsigned char unreconstructed358[0x460 - 0x358];
    int screenLeft, screenTop, screenRight, screenBottom;
};

void Rva00275F3FHost::rva00275F3F()
{
    if ((object->disabledFlags & 0x44) == 0)
    {
        if (iconInfo)
            iconInfo->rva0027006C(6);
    }
    else
    {
        if (reinterpret_cast<Rva00270BA8 *>(this)->rva00270BA8()->icons[6] == 0)
        {
            Anim2D *anim = new Anim2D(
                reinterpret_cast<Anim2DTemplate *>(Drawable::s_animationTemplates[6]),
                TheAnim2DCollection);
            reinterpret_cast<Rva00270BA8 *>(this)->rva00270BA8()->icons[6] = anim;
        }

        int barHeight = screenBottom - screenTop;
        int width = reinterpret_cast<Rva00270BA8 *>(this)->rva00270BA8()->icons[6]->getCurrentFrameWidth();
        int height = reinterpret_cast<Rva00270BA8 *>(this)->rva00270BA8()->icons[6]->getCurrentFrameHeight();
        int x = screenLeft;
        int y = screenBottom - (height + barHeight);
        reinterpret_cast<Rva002D7127 *>(reinterpret_cast<Rva00270BA8 *>(this)->rva00270BA8()->icons[6])->queue(x, y, width, height);
    }
}
