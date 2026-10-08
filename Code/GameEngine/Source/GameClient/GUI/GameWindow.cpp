// cl: /DNDEBUG /MD
// Clean Open-BFME-1 6d9434269164392c5ba62aaa7c15a86b5b020d76 reference transfer.
// Native font dispatcher313D73 and helper boundaries establish target operation/ABI.
// Target field and call facts are distinct from donor names: row16/cell28/payload0C,
// instance display pointers19C/1A0, virtual slot18, font1B4 and style3C are measured.
// Font-sink pointer+04 / slot10 has an observed ABI; its original type remains unknown.

// Text-color family from clean Open-BFME-1 6d9434269164392c5ba62aaa7c15a86b5b020d76.
// Retail independently proves four distinct color-pair stores and the
// ComboBox style-bit dispatch at GameWindow +0x3C. The paired helpers call
// the rowed winGetUserData provider and then the same setter on optional
// child pointers at data +0x2C and +0x28. Donor supplies semantic names;
// native boundaries, stores and reciprocal calls establish target ABI/offsets.
// Disabled helper intentionally gets user data before its null test, as retail does.

// GameWindow small setters, retail 0x00313B87/0x00313CF2/0x00314147.
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// (BFME1 0x00478250/0x00478440/0x00478E70). BFME moves the window fields:
// status at +0x08, size at +0x0C/+0x10, region at +0x14..0x20, input callback
// at +0x1E0. The manager's winSendSystemMsg sits at vtable +0xE8 (slot 58),
// like GadgetListBoxReset's +0xE8 call.
// winGetScreenPosition/winGetSize/winGetPosition, winIsHidden and
// winSetPosition were folded in from split units with these exact flags, as
// was the address-named list link/unlink pair at 0x0031455E/0x00314581.

typedef int Int;
typedef unsigned char UnsignedByte;
class GameFont;
class DisplayString;
enum { GWS_SCROLL_LISTBOX=0x20, GWS_COMBO_BOX=0x8000, GWS_ENTRY_FIELD=0x40, GWS_STATIC_TEXT=0x80 };
struct WindowPickCoord { int x; int y; };
// Method-only declaration of the independently rowed child-search provider.
class Rva003141BCWindowView { public: Rva003141BCWindowView *winPointInChild(int, int, bool, bool = false); };
#define NULL 0
#define BitTest(value, mask) (((value) & (mask)) != 0)
enum { WIN_STATUS_TAB_STOP = 0x100, WIN_STATUS_HIDDEN = 0x10 };
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType
{
	MSG_IGNORED,
	MSG_HANDLED
};

enum
{
	WIN_ERR_OK = 0,
	WIN_ERR_INVALID_PARAMETER = -3,
	GGM_RESIZED = 16388
};

class GameWindow;
void GadgetComboBoxSetEnabledTextColors(GameWindow *, int, int);
void GadgetListBoxSetFont(GameWindow *, GameFont *);
void GadgetComboBoxSetFont(GameWindow *, GameFont *);
void GadgetTextEntrySetFont(GameWindow *, GameFont *);
void GadgetStaticTextSetFont(GameWindow *, GameFont *);
void GadgetComboBoxSetDisabledTextColors(GameWindow *, int, int);
void GadgetComboBoxSetHiliteTextColors(GameWindow *, int, int);
void GadgetComboBoxSetIMECompositeTextColors(GameWindow *, int, int);

typedef WindowMsgHandledType (*GameWinInputFunc)(GameWindow *, UnsignedInt, WindowMsgData, WindowMsgData);

class GameWindowChild
{
public:
	virtual void childAnchor0();
	virtual void childAnchor1();
	virtual void onChildPosition(int curX, int curY, int newX, int newY);
};
class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57)
#undef V
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2) = 0;
};

extern GameWindowManager *TheWindowManager;

class GameWindow
{
public:
	Int winSetSize(Int width, Int height);
	virtual void winSetFont(GameFont *);
	void winSetEnabledTextColors(int color, int borderColor);
	void winSetDisabledTextColors(int color, int borderColor);
	void winSetHiliteTextColors(int color, int borderColor);
	void winSetIMECompositeTextColors(int color, int borderColor);
	GameWindow *winPointInAnyChild(Int x, Int y, bool ignoreHidden, bool ignoreEnableCheck);
	UnsignedInt winClearStatus(UnsignedInt status);
	Int winSetInputFunc(GameWinInputFunc input);
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
	Int winGetPosition(Int *x, Int *y);
	bool winIsHidden(void);
	int winSetPosition(int x, int y);
	void orderPairs();

protected:
	GameWindow *findFirstLeaf();
	GameWindow *findLastLeaf();
	GameWindow *findPrevLeaf();
	GameWindow *findNextLeaf();

private:
	GameWindowChild *m_positionSink; // +0x04 notified by winSetPosition
	UnsignedInt m_status;
	Int m_sizeX;
	Int m_sizeY;
	Int m_regionLoX;
	Int m_regionLoY;
	Int m_regionHiX;
	Int m_regionHiY;
	unsigned char m_pad24[0x3C - 0x24];
	unsigned m_style;
	unsigned char m_pad40[0x18C - 0x40];
	int m_enabledColor;
	int m_enabledBorderColor;
	int m_disabledColor;
	int m_disabledBorderColor;
	int m_hiliteColor;
	int m_hiliteBorderColor;
	int m_imecompositeColor;
	int m_imecompositeBorderColor;
	unsigned char m_pad1AC[0x1E0 - 0x1AC];
	GameWinInputFunc m_inputFunc;
	unsigned char m_pad1E4[0x1F8 - 0x1E4];
	GameWindow *m_next;
	GameWindow *m_prev;
	GameWindow *m_parent;
	GameWindow *m_child;
};

// ?winSetSize@GameWindow@@QAEHHH@Z, retail 0x00313B87 (63B).
Int GameWindow::winSetSize(Int width, Int height)
{
	m_sizeX = width;
	m_sizeY = height;
	m_regionHiX = m_regionLoX + width;
	m_regionHiY = m_regionLoY + height;

	TheWindowManager->winSendSystemMsg(this, GGM_RESIZED, (WindowMsgData)width, (WindowMsgData)height);

	return WIN_ERR_OK;
}

// ?winClearStatus@GameWindow@@QAEII@Z, retail 0x00313CF2 (17B).
UnsignedInt GameWindow::winClearStatus(UnsignedInt status)
{
	UnsignedInt oldStatus;

	oldStatus = m_status;
	m_status &= ~status;

	return oldStatus;
}

// ?winSetInputFunc@GameWindow@@QAEHP6A?AW4WindowMsgHandledType@@PAV1@III@Z@Z, retail 0x00314147 (19B).
Int GameWindow::winSetInputFunc(GameWinInputFunc input)
{
	if (input)
		m_inputFunc = input;

	return WIN_ERR_OK;
}

// ?findFirstLeaf@GameWindow@@IAEPAV1@XZ
// Clean BFME1 GameWindow.cpp at revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, compiled under BFME2 /O1 /G7,
// emitted a unique 31-byte first-leaf walk at RVA 0x0031396B. Native boundary
// 0x0031396B-0x0031398A proves the parent (+0x200) and first-child (+0x204)
// chains; the native next-leaf body tail-calls it after ascending to the root.
// The donor's auxiliary layout emitted the bytes; this is the established
// GameWindow first-leaf operation, using the target-measured window offsets.
GameWindow *GameWindow::findFirstLeaf()
{
    GameWindow *leaf = this;
    while (leaf->m_parent)
        leaf = leaf->m_parent;
    while (leaf->m_child)
        leaf = leaf->m_child;
    return leaf;
}

// ?findNextLeaf@GameWindow@@IAEPAV1@XZ
// Same clean BFME1 donor revision as findFirstLeaf. Native boundary
// 0x00313A25-0x00313A9E proves next +0x1F8, parent +0x200, child +0x204,
// and the stop bit 0x100. Ascending to the root tail-calls the rowed
// first-leaf walk at 0x0031396B. Donor control flow and labels are retained;
// all member accesses use the independently measured target window layout.
GameWindow *GameWindow::findNextLeaf( void )
{
	GameWindow *leaf = (GameWindow *)this;

	if( leaf->m_next )
	{

		if( leaf->m_next->m_status & WIN_STATUS_TAB_STOP )
			return (GameWindow *)leaf->m_next;

		for( leaf = leaf->m_next; leaf; leaf = leaf->m_child )
			if( leaf->m_child == NULL || BitTest( leaf->m_status,
																						WIN_STATUS_TAB_STOP ) )
				return (GameWindow *)leaf;

	}  // end if
	else 
	{

		while( leaf->m_parent )
		{

			leaf = leaf->m_parent;

			if( leaf->m_parent && leaf->m_next )
			{

				for( leaf = leaf->m_next; leaf; leaf = leaf->m_child )
					if( leaf->m_child == NULL ||
							BitTest( leaf->m_status, WIN_STATUS_TAB_STOP ) )
						return (GameWindow *)leaf;

			}  // end if

		}  // end while

		if( leaf )
			return (GameWindow *)leaf->findFirstLeaf();
		else
			return NULL;

	}  // end else

	return NULL;

}  // end findNextLeav


// ?findLastLeaf@GameWindow@@IAEPAV1@XZ
// The 114-byte previous-leaf donor names an opaque walk callee. Native
// 0x0031398A-0x003139B3 proves that callee ascends parents at +0x200,
// then follows first children at +0x204 and their final siblings at +0x1F8.
// This independently matches the original donor's last-leaf operation.
GameWindow *GameWindow::findLastLeaf( void )
{
	GameWindow *leaf = this;

	// Find the root of this branch
	while( leaf->m_parent )
		leaf = leaf->m_parent;

	// Find the last leaf
	while( leaf->m_child ) 
	{

		leaf = leaf->m_child;

		while( leaf->m_next )
			leaf = leaf->m_next;

	}  // end while

	return leaf;

}  // end findLastLeaf


// ?findPrevLeaf@GameWindow@@IAEPAV1@XZ
// Clean BFME1 donor control flow, with its opaque fallback resolved to the
// native last-leaf walk at 0x0031398A. Native boundary 0x003139B3-0x00313A25
// independently proves previous sibling +0x1FC, next +0x1F8, parent +0x200,
// child +0x204, and status bit 0x100. The prior family members stay byte-exact.
GameWindow *GameWindow::findPrevLeaf( void )
{

	GameWindow *leaf = (GameWindow *)this;

	if( leaf->m_prev )
	{

		leaf = leaf->m_prev;

		while( leaf->m_child &&
						 BitTest( leaf->m_status, WIN_STATUS_TAB_STOP ) == false )
		{

			leaf = leaf->m_child;

			while( leaf->m_next )
				leaf = leaf->m_next;

		}  // end while

		return (GameWindow *)leaf;

	}   // end if
	else 
	{

		while( leaf->m_parent )
		{

			leaf = leaf->m_parent;

			if( leaf->m_parent && leaf->m_prev )
			{

				leaf = leaf->m_prev;

				while( leaf->m_child &&
							 BitTest( leaf->m_status, WIN_STATUS_TAB_STOP ) == false )
				{

					leaf = leaf->m_child;

					while( leaf->m_next )
						leaf = leaf->m_next;

				}  // end while

				return (GameWindow *)leaf;

			}  // end if

		}  // end while

		if( leaf )
			return leaf->findLastLeaf();
		else
			return NULL;

	}  // end else

	return NULL;

}  // end findPrevLeaf


// ?winPointInAnyChild@GameWindow@@QAEPAV1@HH_N0@Z
// Same clean BFME1 GameWindow donor revision as the leaf walkers. Native
// 0x003142E1-0x0031435A proves signed bounds, accumulated parent origins,
// hidden bit 0x10, and the call to the independently matched child-search
// provider at 0x003141BC. The method-only provider declaration preserves its
// measured four-argument ABI and makes no claim about its complete class size.
GameWindow *GameWindow::winPointInAnyChild( Int x, Int y, bool ignoreHidden, bool ignoreEnableCheck )
{
	GameWindow *parent;
	GameWindow *child;
	WindowPickCoord origin;

	for( child = ((GameWindow *)this)->m_child; child; child = child->m_next ) 
	{

		origin.x = child->m_regionLoX;
		origin.y = child->m_regionLoY;
		parent = child->m_parent;

		while( parent ) 
		{

			origin.x += parent->m_regionLoX;
			origin.y += parent->m_regionLoY;
			parent = parent->m_parent;

		}  // end while

		if( x >= origin.x && x <= origin.x + child->m_sizeX &&
				y >= origin.y && y <= origin.y + child->m_sizeY )
		{

			if( !(ignoreHidden == true &&	BitTest( child->m_status, WIN_STATUS_HIDDEN )) )
				return (GameWindow *)((Rva003141BCWindowView *)child)->winPointInChild( x, y, ignoreEnableCheck );

		}  // end if

	}  // end for child

	// not in any children, must be in parent
	return this;

}  // end WinPointInAnyChild

void GameWindow::winSetEnabledTextColors(int color, int borderColor)
{
	m_enabledColor = color;
	m_enabledBorderColor = borderColor;
	if (m_style & 0x8000)
		GadgetComboBoxSetEnabledTextColors(this, color, borderColor);
}

void GameWindow::winSetDisabledTextColors(int color, int borderColor)
{
	m_disabledColor = color;
	m_disabledBorderColor = borderColor;
	if (m_style & 0x8000)
		GadgetComboBoxSetDisabledTextColors(this, color, borderColor);
}

void GameWindow::winSetHiliteTextColors(int color, int borderColor)
{
	m_hiliteColor = color;
	m_hiliteBorderColor = borderColor;
	if (m_style & 0x8000)
		GadgetComboBoxSetHiliteTextColors(this, color, borderColor);
}

void GameWindow::winSetIMECompositeTextColors(int color, int borderColor)
{
	m_imecompositeColor = color;
	m_imecompositeBorderColor = borderColor;
	if (m_style & 0x8000)
		GadgetComboBoxSetIMECompositeTextColors(this, color, borderColor);
}

class BfmeWindowDisplayString
{
public:
	virtual void _pad0( void ) = 0;
	virtual void _pad1( void ) = 0;
	virtual void _pad2( void ) = 0;
	virtual void _pad3( void ) = 0;
	virtual void _pad4( void ) = 0;
	virtual void _pad5( void ) = 0;
	virtual void setFont( GameFont *font ) = 0;			///< vtable +0x18
};

// Shape only: whatever sits at GameWindow+0x04, BFME hands it the font through
// its own vtable slot +0x10 every time the font changes, after whichever branch
// ran. The reference makes no such call.
class BfmeWindowFontSink
{
public:
	virtual void _pad0( void ) = 0;
	virtual void _pad1( void ) = 0;
	virtual void _pad2( void ) = 0;
	virtual void _pad3( void ) = 0;
	virtual void setFont( GameFont *font ) = 0;			///< vtable +0x10
};

struct BfmeWindowFontLayout
{
	void *vtable;
	BfmeWindowFontSink *fontSink;						///< this+0x04
	UnsignedByte pad0[0x3c - 0x08];
	UnsignedInt style;									///< this+0x3C
	UnsignedByte pad1[0x1b4 - 0x40];
	GameFont *font;										///< this+0x1B4
	UnsignedByte pad2[0x1cc - 0x1b8];
	DisplayString *text;								///< this+0x1CC
	DisplayString *tooltip;								///< this+0x1D0
};

void GameWindow::winSetFont( GameFont *font )
{
	BfmeWindowFontLayout *self = (BfmeWindowFontLayout *)this;

	// set font in window member
	self->font = font;

	// set font for other display strings in special gadget window controls
	if( self->style & GWS_SCROLL_LISTBOX )
		GadgetListBoxSetFont( this, font );
	else if( self->style & GWS_COMBO_BOX )
		GadgetComboBoxSetFont( this, font );
	else if( self->style & GWS_ENTRY_FIELD )
		GadgetTextEntrySetFont( this, font );
	else if( self->style & GWS_STATIC_TEXT )
		GadgetStaticTextSetFont( this, font );
	else
	{
		BfmeWindowDisplayString *dString;

		// set the font for the display strings all windows have
		dString = (BfmeWindowDisplayString *)self->text;
		if( dString )
			dString->setFont( font );
		dString = (BfmeWindowDisplayString *)self->tooltip;
		if( dString )
			dString->setFont( font );

	}  // end else

	if( self->fontSink )
		self->fontSink->setFont( font );

}  // end WinSetFont

// ?winSetPosition@GameWindow@@QAEHHH@Z, retail 0x00313A9E, 70 bytes.
// GameWindow position setter: notifies the object at +0x4 through its third
// virtual (four int args: current region origin plus the new x/y), then stores
// the new position and orders the rect pairs through orderPairs (rowed at
// 0x31394A, shared-layout helper operating on +0x14/+0x1C/+0x18/+0x20).
// Shape: null-guarded virtual call (je skips), base-plus-arg stores for the
// far corners, direct stores for the near corners, then the orderPairs call.
int GameWindow::winSetPosition(int x, int y)
{
	if (m_positionSink != 0)
		m_positionSink->onChildPosition(m_regionLoX, m_regionLoY, x, y);
	m_regionHiX = m_sizeX + x;
	m_regionLoX = x;
	m_regionLoY = y;
	m_regionHiY = m_sizeY + y;
	orderPairs();
	return 0;
}

// ?winGetPosition@GameWindow@@QAEHPAH0@Z, retail 0x00313AE4 (38B). Twin of
// winGetSize over the region origin at +0x14/+0x18: null-checked position
// fetch with -3/0 codes. Called by the Slide/Spiral animate-window bodies.
Int GameWindow::winGetPosition(Int *x, Int *y)
{
	if (x == NULL || y == NULL) {
		return WIN_ERR_INVALID_PARAMETER;
	}

	*x = m_regionLoX;
	*y = m_regionLoY;

	return WIN_ERR_OK;
}

// ?winGetScreenPosition@GameWindow@@QAEHPAH0@Z, retail 0x00313B3C, 51 bytes.
// Ported from Open-BFME-1
// Code/GameEngine/Source/GameClient/GUI/GameWindowFields.cpp (which matches
// 58B there): walk the parent chain accumulating the region origin. The
// retail loop falls through with eax holding the null parent (which equals
// WIN_ERR_OK), so there is no explicit return-value setup.
Int GameWindow::winGetScreenPosition(Int *x, Int *y)
{
	GameWindow *parent = m_parent;

	*x = m_regionLoX;
	*y = m_regionLoY;

	while (parent) {
		*x += parent->m_regionLoX;
		*y += parent->m_regionLoY;
		parent = parent->m_parent;
	}

	return (Int)parent;
}

// ?winGetSize@GameWindow@@QAEHPAH0@Z, retail 0x00313BC6 (38B). Same BFME1
// file, verbatim port: null-checked size fetch with -3/0 codes.
Int GameWindow::winGetSize(Int *width, Int *height)
{
	if (width == NULL || height == NULL) {
		return WIN_ERR_INVALID_PARAMETER;
	}

	*width = m_sizeX;
	*height = m_sizeY;

	return WIN_ERR_OK;
}

// ?winIsHidden@GameWindow@@QAE_NXZ @0x00313CD9: status bit 4.
bool GameWindow::winIsHidden(void)
{
	return (m_status >> 4) & 1;
}

// ?Rva0031455ELink@Rva0031455E@@QAEXPAV1@@Z @ 0x0031455E (35B).
// Honest address-derived list link: virtual slot 2 then insert this into list headed at arg plus 0x1DC with next at plus 0x04 and owner at plus 0x08.
// Evidence: neighbors 0x0031450A plus 0x003145F0 plus twin unlink 0x00314581 sharing plus 0x04 plus 0x08 plus 0x1DC layout.
// Its vftable (0x0080BBF8) holds the deleting dtor, link and unlink in
// slots 0-2, and link reaches unlink through slot 2: all three are virtual.
class Rva0031455E
{
public:
    virtual ~Rva0031455E();
    virtual void Rva0031455ELink(Rva0031455E *arg);
    virtual void Rva00314581Unlink();
private:
    void *m_04;
    void *m_08;
    char m_pad[0x1DC - 0x0C];
    void *m_1DC;
};
void Rva0031455E::Rva0031455ELink(Rva0031455E *arg)
{
    Rva00314581Unlink();
    if (arg) {
        m_08 = arg;
        m_04 = arg->m_1DC;
        arg->m_1DC = this;
    }
}
// ?Rva00314581Unlink@Rva0031455E@@QAEXXZ @ 0x00314581 (21B).
// Honest address-derived list unlink: if owner at plus 0x08 then move next at plus 0x04 into owner plus 0x1DC and clear plus 0x08.
// Evidence: twin link 0x0031455E sharing plus 0x04 plus 0x08 plus 0x1DC layout.
void Rva0031455E::Rva00314581Unlink()
{
    Rva0031455E *owner = (Rva0031455E *)m_08;
    if (owner) {
        owner->m_1DC = m_04;
        m_08 = 0;
    }
}

Rva0031455E::~Rva0031455E()
{
    Rva00314581Unlink();
}

void Rva0031455EDelete(Rva0031455E *p) { delete p; }

