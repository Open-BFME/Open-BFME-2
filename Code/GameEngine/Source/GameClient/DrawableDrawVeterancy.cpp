// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?drawVeterancy@Drawable@@QAEX_NH@Z retail 0x00277DB4..0x00278064 (688 bytes, ret 8).
// WorldBuilder twin 0x00CAD200 is Drawable::drawVeterancy (BFME 2
// Drawable.cpp; assert "params.icon != NULL && params.dot != NULL" at line
// 5568). Draws a level as level/5 large icons above level%5 small dots,
// centred over the screen point of the drawable's icon anchor (0x002775C9,
// still a gen dump) projected by TheTacticalView (vtable +0x160; zero means
// on screen) and lifted by 7 pixels. Sizes follow the display (TheDisplay
// width/1024 and height/768, halved) over the view zoom (+0x124), with
// 2-unit spacing scaled the same way. The flag picks the second icon/dot
// image pair (0x009FEB90/0x009FEB94) over the first (0x009FEB88/0x009FEB8C).
// Images are drawn through Display +0xF8 (color -1 mode 2); an Image's
// width and height are the ints at +0x24/+0x28. The (bool int) signature
// is from retail's ret 8 and argument use; names of the flag and count are
// inferred.
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Libraries/Include/Lib/Coord2D.h"

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

class Image
{
public:
	Int getImageWidth() const { return m_width; }
	Int getImageHeight() const { return m_height; }

private:
	char m_pad00[0x24];
	Int m_width; // +0x24
	Int m_height; // +0x28
};

class Display
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual UnsignedInt getWidth(); // +0x40
	virtual UnsignedInt getHeight(); // +0x44
	virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21();
	virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25();
	virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45();
	virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
	virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57();
	virtual void slot58(); virtual void slot59(); virtual void slot60(); virtual void slot61();
	virtual void drawImage(const Image *image, Real startX, Real startY, Real endX, Real endY,
		UnsignedInt color, Int mode); // +0xF8
};

class View
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72();
	virtual Real getZoom(); // +0x124
	virtual void slot74(); virtual void slot75(); virtual void slot76(); virtual void slot77();
	virtual void slot78(); virtual void slot79(); virtual void slot80(); virtual void slot81();
	virtual void slot82(); virtual void slot83(); virtual void slot84(); virtual void slot85();
	virtual void slot86(); virtual void slot87();
	virtual Int worldToScreen(const Coord3D *world, ICoord2D *screen); // +0x160
};

extern Display *TheDisplay;
extern View *TheTacticalView;
extern const Image *const g_00DFEB88;
extern const Image *const g_00DFEB90;

class Drawable
{
public:
	void drawVeterancy(Bool flag, Int level);
	void rva002775C9(Coord3D *pos);
};

void Drawable::drawVeterancy(Bool flag, Int level)
{
	if (level <= 0)
		return;
	Real scaleX = ((Real)TheDisplay->getWidth() / 1024.0f) * 0.5f;
	Real scaleY = ((Real)TheDisplay->getHeight() / 768.0f) * 0.5f;
	Real zoom = 1.0f / TheTacticalView->getZoom();
	scaleX *= zoom;
	scaleY *= zoom;
	Real spacingY = 2.0f * scaleY;
	Real spacingX = 2.0f * scaleX;
	Coord3D pos;
	ICoord2D screen;
	rva002775C9(&pos);
	if (TheTacticalView->worldToScreen(&pos, &screen) != 0)
		return;
	Coord2D anchor;
	anchor.x = (Real)screen.x;
	anchor.y = (Real)screen.y;
	anchor.y -= 7.0f;
	const Image *const *params = flag ? &g_00DFEB90 : &g_00DFEB88;
	Int numIcons = level / 5;
	Int numDots = level % 5;
	Real dotHeight = params[1]->getImageHeight() * scaleY;
	anchor.y -= dotHeight;
	if (numDots > 0)
	{
		Real dotWidth = params[1]->getImageWidth() * scaleX;
		Real width = numDots * dotWidth + (numDots - 1) * spacingX;
		Real x = anchor.x - width * 0.5f;
		do
		{
			TheDisplay->drawImage(params[1], x, anchor.y, x + dotWidth, anchor.y + dotHeight, 0xFFFFFFFF, 2);
			x += dotWidth + spacingX;
		} while (--numDots > 0);
	}
	if (numIcons > 0)
	{
		Real iconHeight = params[0]->getImageHeight() * scaleY;
		anchor.y -= iconHeight + spacingY;
		Real iconWidth = params[0]->getImageWidth() * scaleX;
		Real width = numIcons * iconWidth + (numIcons - 1) * spacingX;
		Real x = anchor.x - width * 0.5f;
		do
		{
			TheDisplay->drawImage(params[0], x, anchor.y, x + iconWidth, anchor.y + iconHeight, 0xFFFFFFFF, 2);
			x += iconWidth + spacingX;
		} while (--numIcons > 0);
	}
}
