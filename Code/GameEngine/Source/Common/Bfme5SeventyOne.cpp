#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
// Two more: the twin of the owner unlink and a bounds update.

class Gen_003F6A20
{
public:
	void bfmeDetach(void);
};

class __declspec(novtable) Rva0059675ABase
{
public:
    virtual ~Rva0059675ABase();
};
class GameFont;
class Anim2D;
struct FadeInTextRender : Rva0059675ABase
{
    FadeInTextRender();
    virtual ~FadeInTextRender();
    virtual void LoadAssets();
    void bfmeExtend(int left, int top, int right, int bottom);

    GameFont* font;
    int m_bfmeLeft;
    int m_bfmeTop;
    int m_bfmeRight;
    int m_bfmeBottom;
    unsigned effectColor;
    Anim2D* anim;
    float scale;
    AsciiString fontName;
    unsigned color;
    int delay;
    unsigned fontSize;
    unsigned starts[3], ends[3];
    int width, height;
};

// ?bfmeExtend@FadeInTextRender@@QAEXHHHH@Z
void FadeInTextRender::bfmeExtend(int left, int top, int right, int bottom)
{
	if (m_bfmeLeft > left)
		m_bfmeLeft = left;

	if (m_bfmeRight < right)
		m_bfmeRight = right;

	if (m_bfmeTop > top)
		m_bfmeTop = top;

	if (m_bfmeBottom < bottom)
		m_bfmeBottom = bottom;
}
