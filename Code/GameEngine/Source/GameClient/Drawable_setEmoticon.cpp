// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /G7
// ?setEmoticon@Drawable@@QAEXABV?$StringBase@D@@H@Z @0x002736BA 155B: Drawable find-or-create Anim2D at +0x354 slot 10 via container g_00DFF068 and TheGameLogic frame; neighbours Drawable_rva00273648 Drawable_rva00273755; callers 0x0036E1C3 0x003BC996.
#include "ascii_string.h"

struct Rva002D752DNode;
class Rva002D752D
{
public:
	Rva002D752DNode *rva002D752D(const StringBase<char> &name);
};

// TheAnim2DCollection is the native global at VA 0x00DFF068.
extern class Anim2DCollection *TheAnim2DCollection;

class Rva00270025
{
public:
	virtual ~Rva00270025();
	void *m_items[14];
	int m_vals[14];
};

class Rva00270BA8
{
public:
	Rva00270025 *rva00270BA8();
private:
	unsigned char m_pad[0x354];
	Rva00270025 *m_354;
};

#include "../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Anim2DTemplate;
class Anim2DCollection;
class Anim2D
{
public:
	Anim2D(Anim2DTemplate *tmpl, Anim2DCollection *coll);
private:
	unsigned char m_pad[0x34];
};

#include <new>

class Drawable
{
public:
	void rva002736A8();
	void setEmoticon(const StringBase<char> &name, int val);
};

void Drawable::setEmoticon(const StringBase<char> &name, int val)
{
	rva002736A8();
	Rva002D752DNode *found = ((Rva002D752D *)TheAnim2DCollection)->rva002D752D(name);
	if (found == 0)
		return;
	if (((Rva00270BA8 *)this)->rva00270BA8()->m_items[10] != 0)
		return;
	Anim2D *anim = new Anim2D((Anim2DTemplate *)found, TheAnim2DCollection);
	((Rva00270BA8 *)this)->rva00270BA8()->m_items[10] = anim;
	int v;
	if (val >= 0)
		v = TheGameLogic->getFrame() + val;
	else
		v = 0x3fffffff;
	((Rva00270BA8 *)this)->rva00270BA8()->m_vals[10] = v;
}
