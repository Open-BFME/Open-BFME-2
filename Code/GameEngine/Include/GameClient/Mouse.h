// Mouse: canonical BFME2 interface. Code addresses are RVAs; table addresses are VAs.
// Target facts: constructor 0x001EEC97 calls SubsystemInterface 0x001B4E63 at 0x001EECAA and installs 0x00BE0358 at 0x001EECC6. Destructor 0x001EE3DE installs the same table at 0x001EE3F0 and calls parent destructor 0x001B4E74 at 0x001EE470. Table 0x00BD77A0 is the parent's construction/destruction table, not another Mouse layout.
// Table 0x00BE0358 contains 30 code pointers followed by "Data" at 0x00BE03D0. Slots 0-13 are SubsystemInterface's slots: 0=deleting destructor 0x001EEFB6, 1=init 0x001EE4DC, 2=0x001B5384, 9=0x001EDDBB, 10=update 0x001EDE3A; all remaining inherited slots equal the parent's table words. Mouse is polymorphic and its destructor is out of line.
// Own slots: 14=0x001EE483 (ledger parseIni is nonvirtual, so declared separately), 15/19/20/21/29=__purecall 0x0003B810, 16=createStreamMessages 0x001EE630, 17=setPosition 0x001EDE4C, 18=0x001EE035 (two output pointers, ret 8), 22=setMouseLimits 0x001EDE63, 23=0x0050B238 (ret 8), 24=0x001F01E8 (ret 16), 25=0x0047A69C (ret 4), 26=0x000419CF, 27=0x000419DC, 28=0x001EE5EE (byte and byte pointer, ret 8). Zero Hour names initCursorResources, setCursor, capture, releaseCapture, setRedrawMode, getRedrawMode and getMouseEvent; other slots retain neutral names.
// Constructor 0x001EECB9..0x001EECCC constructs 56 records of 0x54 bytes at +0xC; 0x001EECF0..0x001EED02 constructs 256 records of 0x3C bytes at +0x130C. It clears 0x3C-byte current/previous records at +0x4F0C/+0x4F48 (0x001EED7C..0x001EED95), and writes through dword +0x500C at 0x001EEE72. This proves extent >=0x5010; Win32Mouse's constructor 0x00041976 calls Mouse at 0x0004197B, then clears its own first member at +0x5010 (0x00041987..0x00041995). The constructor sets bytes +0x5008/+0x5009 at 0x001EEFA2/0x001EEF71. Unexposed member storage stays opaque.
// Redraw mode is the dword at +0x12DC (constructor 0x001EEDE8/0x001EEDF0, slot 26 setter 0x000419CF, slot 27 getter 0x000419DC); Zero Hour supplies its name and enum. The constructor writes the ortho flag +0x12E3 and zoom +0x12E4; Zero Hour supplies m_orthoCamera/m_orthoZoom. Cursor index +0x4FA4 is read and bounds-checked against 0x38 by setCursor 0x001EEFD2; Zero Hour supplies m_currentCursor and MouseCursor names.
// Out-of-line rows: parseIni 0x001EE483; getMouseStatus 0x000425A2 (returns this+0x4F0C); getCursorIndex 0x001EF291; setMouseText 0x001EEBD5; drawCursorText 0x001EDED7; drawTooltip 0x001EF06F; visibility setters 0x001EE5BE/0x001EE5D6; private commitPendingCursor 0x001EDDFF, which AptTimeLine::rva0051ED7E 0x0051ED7E calls directly, so AptTimeLine is a friend. No inline lifetime or accessor bodies are supplied for these rows.
// Other ledger spellings: rva001EEA6D 0x001EEA6D; rva001EDD80 0x001EDD80; rva001EDFE9 0x001EDFE9 (cursor-record hotspot at +0x40); rva001EDFF7 0x001EDFF7; rva001EDE26 0x001EDE26; rva001EE5EE 0x001EE5EE; rva000B3FD0 0x000B3FD0; rva001EDE9C 0x001EDE9C; protected moveMouse 0x001EDC41, updateMouseData 0x001EDCB1, checkForDrag 0x001EDD1C; private processMouseEvent 0x001EE069. Nonvirtual ledger identities are kept separately from neutral table slots.
// setPosition 0x001EDE4C stores the two position components at +0x4F0C/+0x4F10; Zero Hour's MouseIO::pos supplies the ICoord2D type. The rest of that record stays opaque. getCursorIndex 0x001EF291 indexes the name-pointer table at VA 0x00DB9058: None/Normal/Arrow/Scroll/Target/Move/AttackMove are indices 0-6, Select is 13. Zero Hour supplies the matching enum spellings and the inline getMouseCursor getter; there is no ledger row for that getter.
#ifndef BFME2_MOUSE_H
#define BFME2_MOUSE_H

#if defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#error Include Mouse.h before the short SubsystemInterface definition.
#endif
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "../../../Libraries/Include/Lib/ICoord2D.h"

class UnicodeString;
struct RGBColor;
struct RGBAColorInt;
struct MouseIO;
struct Rva001EDD80Pair;

class Mouse : public SubsystemInterface {
public:
    enum MouseCursor {
        INVALID_MOUSE_CURSOR = -1, NONE = 0, FIRST_CURSOR = 1, NORMAL = 1,
        ARROW = 2, SCROLL = 3, CROSS = 4, MOVETO = 5, ATTACKMOVETO = 6,
        SELECTING = 13, NUM_MOUSE_CURSORS = 0x38
    };
    enum RedrawMode { RM_WINDOWS, RM_W3D, RM_POLYGON, RM_DX8, RM_MAX };
    enum { NUM_MOUSE_EVENTS = 256 };

    Mouse();
    virtual ~Mouse();
    virtual void init();
    virtual void reset();
    virtual void update();
    virtual void vslot14();
    virtual void initCursorResources() = 0;
    virtual void createStreamMessages();
    virtual void setPosition(int x, int y);
    virtual void vslot18(unsigned int *x, unsigned int *y) const;
    virtual void setCursor(MouseCursor cursor) = 0;
    virtual void capture() = 0;
    virtual void releaseCapture() = 0;
    virtual void setMouseLimits();
    virtual void vslot23(int, int);
    virtual void vslot24(int, int, int, int);
    virtual void vslot25(int);
    virtual void setRedrawMode(RedrawMode mode);
    virtual RedrawMode getRedrawMode();
    virtual void vslot28(unsigned char value, unsigned char *store);
    virtual unsigned char getMouseEvent(MouseIO *result, bool flush) = 0;

    void parseIni();
    const MouseIO *getMouseStatus();
    int getCursorIndex(const AsciiString &name);
    MouseCursor getMouseCursor() { return m_currentCursor; }
    void setMouseText(UnicodeString text, const RGBAColorInt *color, const RGBAColorInt *dropColor);
    void rva001EEA6D(UnicodeString tooltip, int delay = -1, const RGBColor *color = 0, float width = 1.0f);
    void drawCursorText();
    void drawTooltip();
    void _bfme_setEngineVisibility(bool visible);
    void setVisibility(bool visible);
    bool rva001EDD80(const Rva001EDD80Pair *lhs, const Rva001EDD80Pair *rhs);
    void *rva001EDFE9() const;
    void rva001EDFF7(float *out) const;
    bool rva001EDE26() const;
    void rva001EE5EE(unsigned char value, unsigned char *store);
    void rva000B3FD0();
    void rva001EDE9C();

protected:
    void moveMouse(int x, int y, int relOrAbs);
    void updateMouseData();
    void checkForDrag();

public:
    unsigned char field0C[0x12DC - 0xC];
    RedrawMode m_currentRedrawMode;
    unsigned char field12E0[3];
    bool m_orthoCamera;
    float m_orthoZoom;
    unsigned char field12E8[0x4F0C - 0x12E8];
    ICoord2D field4F0C;
    unsigned char field4F14[0x4FA4 - 0x4F14];
    MouseCursor m_currentCursor;
    unsigned char field4FA8[0x5008 - 0x4FA8];
    bool field5008;
    bool field5009;
    int field500C;

private:
    friend class AptTimeLine;
    void commitPendingCursor();
    void processMouseEvent(int eventToProcess);
};

extern Mouse *TheMouse;

#endif
