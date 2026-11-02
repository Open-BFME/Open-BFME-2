// Target facts: retail RVAs below use image base 0x00400000; table addresses are VAs.
// Constructor 0x0035897D stores table 0x00C15338 at +0 and zeros four dwords at +4/+8/+0xC/+0x10; destructor 0x00358994 restores that same table, calls reset 0x00358946 and destroys the string at +4 through 0x00036E70. No parent constructor or pool virtual occurs; W3D constructor 0x00106088 calls this constructor, installs its own 0x00BCF900 table and constructs its first member at +0x14, bounding DisplayString to 0x14 bytes.
// Table 0x00C15338 has 24 slots before the next table at 0x00C15398: 0 deleting destructor (0x003589CD), 1 setText (0x00358A03), 2 getText (0x0022C4DF), 3 getTextLength (0x00106153), 4 notifyTextChanged (empty 0x000B3FD0), 5 reset (0x00358946), 6 setFont (0x0010670B), 7 getFont (0x0030F45F), 8-19 purecall (0x0003B810), 20 setClipRegion (empty ret 4 at 0x0047A69C), 21 removeLastChar (0x00358933), 22 appendChar (0x00358957), 23 appendString (0x003589E9).
// W3D table 0x00BCF900 proves slots 8/9 setWordWrap/setWordWrapCentered (0x00105F6E/0x00105FC6), 10-12 setColors/setTextColor/setDropColor (0x00105DC0/0x00105E05/0x00105E35), 13/14 draw(int,int)/draw(int,int,int,int) (0x00105E65/0x00106405), 15/16 getSize/getWidth (0x00105E79/0x0010657E), 17/18 unnamed two-float setters (0x00105FE4/0x00106036), 19 setUseHotkey (0x00105F94), 20 setClipRegion (0x00105E9C). VC7.1 reverses the declaration order of the draw overloads.
// getText copies UnicodeString at +4 through 0x00037050; getTextLength reads its buffer's 16-bit length at +4. setFont/getFont write/read the pointer at +8; manager link 0x00262027 writes next at +0xC and prev at +0x10. W3D destructor 0x00106162 calls the out-of-line base destructor at 0x001061AC. Names and protected member access follow Zero Hour DisplayString.h; no donor pool base or extra virtual is present in retail.

#pragma once

#ifndef __DISPLAYSTRING_H_
#define __DISPLAYSTRING_H_

class DisplayStringManager;
class GameFont;
class UnicodeString;
struct IRegion2D;

#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"

class DisplayString
{
    friend class DisplayStringManager;

public:
    DisplayString();
    virtual ~DisplayString();

    virtual void setText(UnicodeString text);
    virtual UnicodeString getText() { return m_textString; }
    virtual int getTextLength();
    virtual void notifyTextChanged() {}
    virtual void reset();
    virtual void setFont(GameFont *font) { m_font = font; }
    virtual GameFont *getFont() { return m_font; }
    virtual void setWordWrap(int wordWrap) = 0;
    virtual void setWordWrapCentered(bool isCentered) = 0;
    virtual void setColors(int textColor, int dropColor) = 0;
    virtual void setTextColor(int *colors) = 0;
    virtual void setDropColor(int *colors) = 0;
    virtual void draw(int x, int y, int xDrop, int yDrop) = 0;
    virtual void draw(int x, int y) = 0;
    virtual void getSize(int *width, int *height) = 0;
    virtual int getWidth(int charPos = -1) = 0;
    virtual void slot17(float a, float b) = 0;
    virtual void slot18(float a, float b) = 0;
    virtual void setUseHotkey(bool useHotkey, int hotKeyColor) = 0;
    virtual void setClipRegion(IRegion2D *region) {}
    virtual void removeLastChar();
    virtual void appendChar(unsigned short c);
    virtual void appendString(const UnicodeString &text);

    DisplayString *next() { return m_next; }

protected:
    UnicodeString m_textString;
    GameFont *m_font;
    DisplayString *m_next;
    DisplayString *m_prev;
};

#endif
