// Display: canonical BFME2 interface and constructor-owned storage.
// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x0025D489 calls SubsystemInterface at 0x0025D49B and installs 0x00BF5DA0 at 0x0025D4A5. Destructor 0x0025D686 restores the same table at 0x0025D697 and calls the parent destructor at 0x0025D6E3. The parent constructor/destructor 0x001B4E63/0x001B4E74 install 0x00BD77A0 for the base phase only; there is one primary vptr and no additional base call.
// Table 0x00BF5DA0 contains 100 slots, ending at the next destructor-owned table 0x00BF5F30 (Rva0025DB46). Slots 0-13 retain SubsystemInterface's order, with Display overriding 0 (0x0025DA57), 1 (empty 0x000B3FD0), 9 (0x0025D9E3), 10 (0x0025C4F3), and 12 (0x0025C25A). Slot 0 calls the rowed destructor 0x0025D686; lifetime methods are declared out of line.
// Slots 14/15 are ledger setHeight/setWidth (0x0025C378/0x0025C391), storing +0xC/+0x10 respectively. Slots 16/17 read those offsets (0x001DB0A8/0x001DB09D); retail callers 0x002B2466 and Drawable's drawImage users name them getWidth/getHeight. Neutral field names preserve this distinction from the setter row names.
// Slots 18-21 set/read dword +0x14 and byte +0x18 (0x002B22A5, 0x0057E556, 0x00049F2B, 0x004C9990); Zero Hour supplies setBitDepth/getBitDepth/setWindowed/getWindowed. Slots 22/26 are rowed setDisplayMode 0x0025C262 and testMinSpecRequirements 0x00049F35.
// Slot 35 is rowed rva0025C134 (0x0025C134); 36 reads +0x1C (0x0030F2C7); 37 follows the argument's slot 152 (0x00049F4F). The retail view walk 0x0008F0CA and Zero Hour establish getFirstView/getNextView. Slots 38-40 are rowed 0x0025C14D/0x0025C18B/0x0025C238.
// Slots 66/72/73/74 are rowed 0x0025C97E/0x0025DA8D/0x0025CF2A/0x0025C6BD. Slots 68/89 point to nonvirtual ledger rows 0x0025D19E/0x00049F94; slot 68 uses Zero Hour's stopMovie name. Slots 89-91 (0x00049F94/0x00049F66/0x00049F73 in both tables) store the AsciiString +0xF0, dword +0xF4 and dword +0xF8; ScriptActions::doDisplayCinematicText (0x003BFDAB) calls them with the localized text, the font from TheFontLibrary and a frame count, matching Zero Hour's setCinematicText/setCinematicFont/setCinematicTextFrames. Slots 69-71 read +0x38/+0x5D/+0x5C (0x0052D843/0x00049F27/0x00094AD8); 75 reads +0x30 (0x003F3FE8); 87 returns false; 88 reads +0xD8 (0x00044235); 90/91 set +0xF4/+0xF8 (0x00049F66/0x00049F73). Remaining entries have neutral names.
// Constructor writes 0x0025D4AB..0x0025D50C prove dwords +0xC..+0x58 and +0x60, bytes +0x18/+0x48/+0x5C/+0x5D/+0x64. 0x0025D4ED..0x0025D50F constructs three 0x18-byte elements at +0x68. 0x0025D514..0x0025D62A proves the scalar offsets through byte +0x141. Derived W3DDisplay constructor 0x00049DEA starts its own storage at +0x144, bounding Display to 0x144 bytes after alignment.
// Destructor 0x0025D6B0..0x0025D6D8 releases AsciiString storage at +0xF0/+0xD0 and UnicodeString storage at +0xB0. These four-byte string members and the image records remain opaque here. The parent owns +0x4 and +0x8. Callback 0x0025C6BD stores +0x30/+0x34; its ledger signature proves DebugDisplayCallback.
// Nonvirtual method declarations follow the ledger rows at 0x0025DA73, 0x0025D904, 0x0004B180, 0x002B2466, 0x0025C46E, 0x0025D9CB, 0x0025D10F, 0x0025D19E, 0x0025D358, 0x00049F94, 0x0025C6E2, 0x0025C72C, 0x0025C4A4, 0x0025C776, 0x0025D33B, 0x0025CC7A and 0x0025D3C8. No copy or assignment body is supplied.
// Zero Hour supplies setClipRegion/isClippingEnabled/enableClipping (42-44), createLightPulse (47), drawOpenRect/drawFillRect (56/57), drawImage (62), stopMovie/isMoviePlaying (68/69) and getAverageFPS (92). W3DDisplay table 0x00BC3C80 maps these to 0x00044FB9/0x00049F80/0x00049F87, 0x0004423C, 0x00044A1A/0x00044C9A, 0x0004776F, 0x0025D19E/0x0052D843 and 0x0055F4B5. Retail callers 0x001E041E, 0x00277D31/0x00277D7A and 0x004379A9 confirm the light-pulse, rectangle and FPS dispatches; row 0x0004776F proves the float-coordinate image ABI. Unnamed pure entries reserve their slots without claiming an argument signature. Exceptions: W3DDisplay slots 49/50 (0x0004450E/0x00044545) return with ret 16 and the fade caller 0x0004353C pushes an index and three floats; W3DDisplay slot 52 (0x0004488C) returns with ret 4 and ScriptActions 0x003BAA2D forwards one float to it. W3DDisplay slot 51 (0x0004481A) stores four floats and ScriptActions 0x003BA9FA forwards four floats to it; W3DDisplay slot 84 (0x0004538C) returns AL=1 with ret 8 and ScriptActions 0x003BCCA2 pushes 10000 and 1.
// The shared stub 0x001F01E8 at slots 24/25 returns with ret 16, fixing four argument words. Slots 23-25 take Zero Hour's getDisplayModeCount/getDisplayModeDescription/setGamma: the rowed AptOptions::InitGadgets 0x00519E1E and Save 0x005194F6 read a mode count from +0x5C and pass an index and three int pointers to +0x60, and 0x00519167, Save and 0x0051847B pass the global gamma and 0.0/1.0/false to +0x64; slot 30 at 0x00049F0F copies through one pointer and returns with ret 4. W3DDisplay rows at 0x00044D7F (slot 41), 0x00044E77 (65), 0x0025D6F5 (67) and 0x00047D04 (99) prove their parameter/return representations. Slot 75 reads the callback stored by 0x0025C6BD, and Zero Hour supplies getDebugDisplayCallback. Slot 65 retains a neutral name: its ledger calls it drawImage(Image*,float,float,float,float,int), while consumers call it drawVideoBuffer; this does not prove a second drawImage overload adjacent to slot 62.
#ifndef BFME2_DISPLAY_H
#define BFME2_DISPLAY_H

#if defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#error Include Display.h before the short SubsystemInterface definition.
#endif
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include <stdio.h>

class UnicodeString;
class View;
class VideoBuffer;
class DisplayString;
class DebugDisplayInterface;
class Image;
class GameFont;
struct IRegion2D;
struct Coord3D;
struct RGBColor;
struct Rva0025C18BCoord;
enum StaticGameLODLevel;

class Display : public SubsystemInterface {
public:
    typedef void DebugDisplayCallback(DebugDisplayInterface *, void *, FILE *);
    Display();
    virtual ~Display();
    virtual void init() {}
    virtual void reset();
    virtual void update();
    virtual void vslot12();
    virtual void setHeight(unsigned int height);
    virtual void setWidth(unsigned int width);
    virtual unsigned int getWidth() { return field0C; }
    virtual unsigned int getHeight() { return field10; }
    virtual void setBitDepth(unsigned int depth) { field14 = depth; }
    virtual unsigned int getBitDepth() { return field14; }
    virtual void setWindowed(bool windowed) { field18 = windowed; }
    virtual bool getWindowed() { return field18; }
    virtual bool setDisplayMode(unsigned int, unsigned int, unsigned int, bool);
    virtual int getDisplayModeCount();
    virtual void getDisplayModeDescription(int modeIndex, int *xres, int *yres, int *bitDepth);
    virtual void setGamma(float gamma, float bright, float contrast, bool calibrate);
    virtual bool testMinSpecRequirements(bool *, bool *, bool *, StaticGameLODLevel * = 0, float * = 0);
    virtual void slot27() = 0;
    virtual void slot28() = 0;
    virtual void slot29() = 0;
    virtual void slot30(const void *);
    virtual void slot31() = 0;
    virtual void slot32() = 0;
    virtual void slot33() = 0;
    virtual void slot34() = 0;
    virtual void rva0025C134(Display *);
    virtual View *getFirstView() { return field1C; }
    virtual View *getNextView(View *);
    virtual void rva0025C14D();
    virtual void rva0025C18B(Rva0025C18BCoord *, Rva0025C18BCoord *);
    virtual void rva0025C238();
    virtual VideoBuffer *createVideoBuffer(bool) = 0;
    virtual void setClipRegion(IRegion2D *) = 0;
    virtual bool isClippingEnabled() = 0;
    virtual void enableClipping(bool) = 0;
    virtual void slot45() = 0;
    virtual void slot46() = 0;
    virtual void createLightPulse(const Coord3D *, const RGBColor *, float, float, unsigned int, unsigned int) = 0;
    virtual void slot48() = 0;
    virtual void slot49(int, float, float, float) = 0;
    virtual void slot50(int, float, float, float) = 0;
    virtual void slot51(float, float, float, float) = 0;
    virtual void slot52(float) = 0;
    virtual void slot53() = 0;
    virtual void slot54() = 0;
    virtual void slot55() = 0;
    virtual void drawOpenRect(float, float, float, float, float, unsigned int) = 0;
    virtual void drawFillRect(float, float, float, float, unsigned int) = 0;
    virtual void slot58() = 0;
    virtual void slot59() = 0;
    virtual void slot60() = 0;
    virtual void slot61() = 0;
    virtual void drawImage(const Image *, float, float, float, float, unsigned int = 0xFFFFFFFF, int = 2) = 0;
    virtual void slot63() = 0;
    virtual void slot64() = 0;
    virtual void slot65(Image *, float, float, float, float, int) = 0;
    virtual bool rva0025C97E(AsciiString, int, int, int);
    virtual bool slot67(AsciiString, bool, int);
    virtual void stopMovie();
    virtual bool isMoviePlaying() { return field38 != 0; }
    virtual bool slot70();
    virtual bool slot71();
    virtual bool rva0025DA8D(AsciiString, int);
    virtual unsigned int rva0025CF2A(int);
    virtual void setDebugDisplayCallback(DebugDisplayCallback *, void * = 0);
    virtual DebugDisplayCallback *getDebugDisplayCallback() { return m_debugDisplayCallback; }
    virtual void slot76() = 0;
    virtual void slot77() = 0;
    virtual void slot78() = 0;
    virtual void slot79() = 0;
    virtual void slot80() = 0;
    virtual void slot81() = 0;
    virtual void slot82() = 0;
    virtual void slot83() = 0;
    virtual bool slot84(int, unsigned int) = 0;
    virtual void slot85() = 0;
    virtual void slot86() = 0;
    virtual bool slot87() { return false; }
    virtual bool slot88() { return fieldD8; }
    virtual void setCinematicText(AsciiString);
    virtual void setCinematicFont(GameFont *);
    virtual void setCinematicTextFrames(int);
    virtual float getAverageFPS() = 0;
    virtual void slot93() = 0;
    virtual void slot94() = 0;
    virtual void slot95() = 0;
    virtual void slot96() = 0;
    virtual void slot97();
    virtual void slot98();
    virtual void slot99(int) = 0;

    void bfmeTickVM0();
    void StartRenderThread(int);
    void Rva006F2890RegisterVideoBuffer(VideoBuffer *);
    void rva002B2466(float, float, float, float);
    void rva0025C46E();
    void rva0025D9CB(bool);
    void rva0025D10F();
    void rva0025D19E();
    void rva0025D358(UnicodeString, float, float, int, int, int);
    void rva00049F94(AsciiString);
    void SetMovieImage(int, int, float, float, float, float);
    void SetStaticImage(int, int, float, float, float, float);
    int rva0025C4A4(int);
    void rva0025C776(int, float, float, float, float, int, int);
    void DrawStaticImage(int, int);
    bool rva0025CC7A(bool);
    DisplayString *rva0025D3C8();

protected:
    unsigned int field0C;
    unsigned int field10;
    unsigned int field14;
    bool field18;
    unsigned char pad19[3];
    View * field1C;
    float field20;
    float field24;
    float field28;
    unsigned int field2C;
    DebugDisplayCallback * m_debugDisplayCallback;
    void * m_debugDisplayUserData;
    unsigned int field38;
    unsigned int field3C;
    unsigned int field40;
    unsigned int field44;
    bool field48;
    unsigned char pad49[3];
    unsigned int field4C;
    unsigned int field50;
    unsigned int field54;
    unsigned int field58;
    bool field5C;
    bool field5D;
    unsigned char pad5E[2];
    unsigned int field60;
    bool field64;
    unsigned char pad65[3];
    unsigned char field68[3][0x18];
    unsigned int fieldB0;
    unsigned int fieldB4;
    unsigned int fieldB8;
    unsigned int fieldBC;
    float fieldC0;
    float fieldC4;
    float fieldC8;
    float fieldCC;
    unsigned int fieldD0;
    float fieldD4;
    bool fieldD8;
    unsigned char padD9[3];
    unsigned int fieldDC;
    unsigned int fieldE0;
    unsigned int fieldE4;
    unsigned int fieldE8;
    unsigned int fieldEC;
    unsigned int fieldF0;
    unsigned int fieldF4;
    unsigned int fieldF8;
    float fieldFC;
    float field100;
    float field104;
    float field108;
    bool field10C;
    unsigned char pad10D[3];
    unsigned int field110;
    bool field114;
    bool field115;
    unsigned char pad116[2];
    unsigned int field118;
    float field11C;
    float field120;
    unsigned int field124;
    float field128;
    float field12C;
    float field130;
    float field134;
    unsigned int field138;
    unsigned int field13C;
    bool field140;
    bool field141;
    unsigned char pad142[2];
};

extern Display *TheDisplay;

#endif
