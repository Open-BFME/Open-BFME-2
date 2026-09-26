// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Color-tree destructor (retail 0x0038103F, 56B): clears the int-keyed
// multiplayer-color tree through the rowed 0x00380F08 body, then frees the
// header node through _free when non-null. Same shell as the rowed int-int
// tree dtor 0x0021B775 and the faction-set dtor 0x00589BE: the explicit
// instantiation below emits the outline clear call plus the null-checked
// header free. The MultiplayerSettings destructor reaches it as the +0x34
// color-list member teardown.
#include <map>

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

struct RGBColor
{
	float red;
	float green;
	float blue;
};

class MultiplayerColorDefinition
{
public:
	MultiplayerColorDefinition();
	MultiplayerColorDefinition(const MultiplayerColorDefinition &other);

private:
	AsciiString m_tooltipName; // +0x00
	RGBColor m_rgbValue; // +0x04
	int m_color; // +0x10
	RGBColor m_rgbValueNight; // +0x14
	int m_colorNight; // +0x20
	RGBColor m_rgbExtra1; // +0x24
	RGBColor m_rgbExtra2; // +0x30
	bool m_extraFlag; // +0x3C
};

typedef _STL::pair<const int, MultiplayerColorDefinition> ColorMapValue;
typedef _STL::_Rb_tree<int, ColorMapValue, _STL::_Select1st<ColorMapValue>, _STL::less<int>, _STL::allocator<ColorMapValue> > ColorMapTree;

// ??1?$_Rb_tree@HU?$pair@$$CBHVMultiplayerColorDefinition@@@_STL@@U?$_Select1st@U?$pair@$$CBHVMultiplayerColorDefinition@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHVMultiplayerColorDefinition@@@_STL@@@2@@_STL@@QAE@XZ @0x38103F
template ColorMapTree::~_Rb_tree();
