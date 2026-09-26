// cl: /O1 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// Color-tree node eraser: retail 0x00380EB1, 53 bytes. Same 53B
// Destroy-and-free shape as the landed string-pair erase 0x2E44BD (recurse
// right, destroy the value at node+0x10, release the node via GameMemory
// free 0x30830, walk left). The value is pair<const int,
// MultiplayerColorDefinition>; MCD carries its AsciiString tooltip name at
// +0x00 (see MultiplayerColorDefinitionCtor.cpp), so the implicit pair
// destructor skips the int key and tears down the string, ICF-folded onto
// 0x29D7C2 (rowed as ??1CameraMarker). The key destructor stays
// declared-only so the pair keeps retail's out-of-line teardown call, per
// the list-pair precedent in stlport_string_list_pair_cleanup.cpp.
#include <map>

template <typename T> class StringBase
{
	void releaseBuffer();

public:
	~StringBase();

protected:
	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();
};

struct RGBColor
{
	float red;
	float green;
	float blue;
};

class MultiplayerColorDefinition
{
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

typedef char ColorMapValueMatchesRetail[(sizeof(MultiplayerColorDefinition) == 0x40) ? 1 : -1];

typedef _STL::pair<const int, MultiplayerColorDefinition> ColorMapValue;
typedef _STL::_Rb_tree<int, ColorMapValue, _STL::_Select1st<ColorMapValue>, _STL::less<int>, _STL::allocator<ColorMapValue> > ColorMapTree;

// ?_M_erase@?$_Rb_tree@HU?$pair@$$CBHVMultiplayerColorDefinition@@@_STL@@U?$_Select1st@U?$pair@$$CBHVMultiplayerColorDefinition@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHVMultiplayerColorDefinition@@@_STL@@@2@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@$$CBHVMultiplayerColorDefinition@@@_STL@@@2@@Z
template void ColorMapTree::_M_erase(ColorMapTree::_Link_type);
