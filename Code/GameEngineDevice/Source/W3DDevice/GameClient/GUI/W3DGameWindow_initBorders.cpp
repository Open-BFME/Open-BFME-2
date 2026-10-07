// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include
//
// ?initBorders@@YAXXZ
// retail 0x001052FF, 645 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DGameWindow.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). The initializer and border drawing method share their
// native static table here; unrelated donor definitions are omitted.
// class-gate: allow AsciiString the donor's own view; the placed body is byte-exact under it
// Open-BFME5: W3DGameWindow::~W3DGameWindow, retail 0x004655F0,
// zh_sweep packet 004655f0.

typedef int Int;
typedef float Real;
typedef int Color;
typedef bool Bool;
static const Bool FALSE = false;
class Image;
// The target uses the existing W3DDisplay image wrapper at 4D6B3. The
// reference Display virtual-slot view is unnecessary for this caller.
class Display;
class W3DDisplay
{
public:
    void rva0004D6B3(Image *image, Real startX, Real startY,
        Real endX, Real endY, Color color = -1, Int mode = 2);
};
extern Display *TheDisplay;
//
// The Zero Hour destructor body is empty; everything retail emits is the
// implicit epilogue -- stamp the W3DGameWindow vptr, destroy the one
// non-trivial member, then chain to ~GameWindow. Two facts come out of the
// bytes:
//
//  - the member is at [this+0x268] and its destructor is
//    Render2DSentenceClass::~Render2DSentenceClass (0x00887940), i.e. the
//    m_textRenderer the reference class declares. Retail destroys exactly one
//    member, so nothing else in W3DGameWindow needs destruction.
//  - ~GameWindow is a real call to 0x00013AF7, not inlined, and it runs with
//    the EH state already back at -1.
//
// The reference tree's W3DGameWindow.cpp is not ported, so both classes are
// spelled TU-locally. The split between GameWindow's own size and
// W3DGameWindow's leading members is not recovered here -- only the total
// distance to m_textRenderer is proven -- so it is carried as one opaque run
// rather than invented member names.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
class Render2DSentenceClass
{
public:
	~Render2DSentenceClass();								///< retail 0x00887940
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
protected:
	// Protected, as retail's mangling records: ??1GameWindow@@MAE@XZ.
	virtual ~GameWindow();									///< ILT 0x00013AF7 -> 0x00479CD0

	friend class W3DGameWindow;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DGameWindow.h
class W3DGameWindow : public GameWindow
{
protected:
	virtual ~W3DGameWindow( void );
	void blitBorderRect( Int x, Int y, Int width, Int height );

	// vptr at +0x00; m_textRenderer lands at +0x268.
	unsigned char m_unreconstructed_04[0x268 - 4];
	Render2DSentenceClass m_textRenderer;					///< +0x268
};

// Retail 0x0078D810 initializes the border images in this window TU.
// The enum order is the vendored Gadget.h order: right pieces precede top
// pieces in the static pointer array, despite the lookup-call order below.
class Image;
#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;

enum BorderPiece
{
	BORDER_CORNER_UL,
	BORDER_CORNER_UR,
	BORDER_CORNER_LL,
	BORDER_CORNER_LR,
	BORDER_VERTICAL_LEFT,
	BORDER_VERTICAL_LEFT_SHORT,
	BORDER_VERTICAL_RIGHT,
	BORDER_VERTICAL_RIGHT_SHORT,
	BORDER_HORIZONTAL_TOP,
	BORDER_HORIZONTAL_TOP_SHORT,
	BORDER_HORIZONTAL_BOTTOM,
	BORDER_HORIZONTAL_BOTTOM_SHORT,
	NUM_BORDER_PIECES
};

enum
{
	BORDER_CORNER_SIZE = 15,
	BORDER_LINE_SIZE = 20
};

static Bool bordersInit = false;
static const Image *borderPieces[NUM_BORDER_PIECES] = { 0 };

void initBorders(void)
{
	{
		AsciiString name("BorderCornerUL");
		borderPieces[BORDER_CORNER_UL] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderCornerUR");
		borderPieces[BORDER_CORNER_UR] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderCornerLL");
		borderPieces[BORDER_CORNER_LL] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderCornerLR");
		borderPieces[BORDER_CORNER_LR] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderLeft");
		borderPieces[BORDER_VERTICAL_LEFT] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderLeftShort");
		borderPieces[BORDER_VERTICAL_LEFT_SHORT] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderTop");
		borderPieces[BORDER_HORIZONTAL_TOP] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderTopShort");
		borderPieces[BORDER_HORIZONTAL_TOP_SHORT] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderRight");
		borderPieces[BORDER_VERTICAL_RIGHT] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderRightShort");
		borderPieces[BORDER_VERTICAL_RIGHT_SHORT] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderBottom");
		borderPieces[BORDER_HORIZONTAL_BOTTOM] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderBottomShort");
		borderPieces[BORDER_HORIZONTAL_BOTTOM_SHORT] = TheMappedImageCollection->findImageByName(name);
	}
	bordersInit = true;
}

  // end ~W3DGameWindow

// BFME 1 donor 1399ad37d42ea52a63829e417c46a1ba9ed2cd20, W3DGameWindow.cpp.
// Target 105584/1391 begins immediately after rowed initBorders 1052FF/645.
// The native init call and shared border-image slots tie this drawing method
// to the initializer above; retain one table and one initialized flag.
// Reference identity/algorithm: W3DGameWindow::blitBorderRect, 20-pixel lines
// with 10-pixel short pieces and four corner images. Native bounds, display
// virtual calls and full extent are verified independently for BFME 2.
void W3DGameWindow::blitBorderRect( Int x, Int y, Int width, Int height )
{
	Int Offset = 15;
	Int OffsetLower = 5;
	if( bordersInit == FALSE )
		initBorders();

	Int originalX = x;
	Int originalY = y;
	Int maxX = x + width;
	Int maxY = y + height;
	Int x2, y2;
	Int size = 20;
	Int halfSize = size / 2;

	y = originalY - Offset;
	y2 = maxY - OffsetLower;
	x2 = maxX - (OffsetLower + BORDER_LINE_SIZE);

	for( x=(originalX + OffsetLower); x <= x2; x += BORDER_LINE_SIZE )
	{
		reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3( const_cast<Image *>(borderPieces[ BORDER_HORIZONTAL_TOP ]),
															 x, y, x + size, y + size );
		reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3( const_cast<Image *>(borderPieces[ BORDER_HORIZONTAL_BOTTOM ]),
															 x, y2, x + size, y2 + size );
	}

	x2 = maxX - 5;
	if( (x2 - x) >= (BORDER_LINE_SIZE / 2) )
	{
		reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3( const_cast<Image *>(borderPieces[ BORDER_HORIZONTAL_TOP_SHORT ]),
															 x, y, x + halfSize, y + size );
		reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3( const_cast<Image *>(borderPieces[ BORDER_HORIZONTAL_BOTTOM_SHORT ]),
															 x, y2, x + halfSize, y2 + size );
		x += (BORDER_LINE_SIZE / 2);
	}

	if( x < x2 )
	{
		x -= ((BORDER_LINE_SIZE / 2) - (((x2 - x) + 1) & ~1));
		reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3( const_cast<Image *>(borderPieces[ BORDER_HORIZONTAL_TOP_SHORT ]),
															 x, y, x + halfSize, y + size );
		reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3( const_cast<Image *>(borderPieces[ BORDER_HORIZONTAL_BOTTOM_SHORT ]),
															 x, y2, x + halfSize, y2 + size );
	}

	x = originalX - Offset;
	x2 = maxX - OffsetLower;
	y2 = maxY - (OffsetLower + BORDER_LINE_SIZE);

	for( y=(originalY + OffsetLower); y <= y2; y += BORDER_LINE_SIZE )
	{
		reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3( const_cast<Image *>(borderPieces[ BORDER_VERTICAL_LEFT ]),
															 x, y, x + size, y + size );
		reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3( const_cast<Image *>(borderPieces[ BORDER_VERTICAL_RIGHT ]),
															 x2, y, x2 + size, y + size );
	}

	y2 = maxY - OffsetLower;
	if( (y2 - y) >= (BORDER_LINE_SIZE / 2) )
	{
		reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3( const_cast<Image *>(borderPieces[ BORDER_VERTICAL_LEFT_SHORT ]),
															 x, y, x + size, y + halfSize );
		reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3( const_cast<Image *>(borderPieces[ BORDER_VERTICAL_RIGHT_SHORT ]),
															 x2, y, x2 + size, y + halfSize );
		y += (BORDER_LINE_SIZE / 2);
	}

	if( y < y2 )
	{
		y -= ((BORDER_LINE_SIZE / 2) - (((y2 - y) + 1) & ~1));
		reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3( const_cast<Image *>(borderPieces[ BORDER_VERTICAL_LEFT_SHORT ]),
															 x, y, x + size, y + halfSize );
		reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3( const_cast<Image *>(borderPieces[ BORDER_VERTICAL_RIGHT_SHORT ]),
															 x2, y, x2 + size, y + halfSize );
	}

	x = originalX - BORDER_CORNER_SIZE;
	y = originalY - BORDER_CORNER_SIZE;
	reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3( const_cast<Image *>(borderPieces[ BORDER_CORNER_UL ]),
														 x, y, x + size, y + size );
	x = maxX - 5;
	y = originalY - BORDER_CORNER_SIZE;
	reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3( const_cast<Image *>(borderPieces[ BORDER_CORNER_UR ]),
														 x, y, x + size, y + size );
	x = originalX - BORDER_CORNER_SIZE;
	y = maxY - 5;
	reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3( const_cast<Image *>(borderPieces[ BORDER_CORNER_LL ]),
														 x, y, x + size, y + size );
	x = maxX - 5;
	y = maxY - 5;
	reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3( const_cast<Image *>(borderPieces[ BORDER_CORNER_LR ]),
														 x, y, x + size, y + size );
}
