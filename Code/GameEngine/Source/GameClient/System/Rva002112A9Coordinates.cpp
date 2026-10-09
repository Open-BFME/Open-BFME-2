// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// Native 6112A9..611396 (237B); WB B5E7D0 repeats the coordinate display.
// Target bytes establish flag +2C8 and singleton screen position +8C.
// Original receiver and method names remain unknown.
class Mouse;
#include "ascii_string.h"
#include "unicode_string.h"
struct _MouseSixteen { int v[4]; };
class Mouse { public: void rva001EEBD5(UnicodeString,const _MouseSixteen*,const _MouseSixteen*); };
extern Mouse *TheMouse;
struct CoordinatePair2112 { int x,y; };
struct CoordinateVector2112 { float x,y,z; };
class Rva002D3627Host {
public:
 virtual void slot00(); virtual void slot01(); virtual void slot02();
 virtual void slot03(); virtual void slot04(); virtual void slot05();
 virtual void slot06(); virtual void slot07(); virtual void slot08();
 virtual void slot09(); virtual void slot10(); virtual void slot11();
 virtual void slot12(); virtual void slot13();
 virtual void project(const CoordinatePair2112*,CoordinateVector2112*);
 char pad04[0x88];
 CoordinatePair2112 screen8C;
};
extern Rva002D3627Host *g_00DFEF18;
class Rva002112A9 {
 char pad[0x2C8];
 bool showCoordinates;
public: void rva002112A9();
};
void Rva002112A9::rva002112A9()
{
 if (!showCoordinates) {
  TheMouse->rva001EEBD5(UnicodeString::TheEmptyString,0,0);
 } else {
  CoordinateVector2112 position;
  g_00DFEF18->project(&g_00DFEF18->screen8C,&position);
  AsciiString text;
  text.format("X:%d, Y:%d <<< World position coordinate >>",(int)position.x,(int)position.y);
  UnicodeString wide;
  wide.translate(text);
  _MouseSixteen foreground;
  foreground.v[0]=255; foreground.v[1]=32; foreground.v[2]=255; foreground.v[3]=255;
  _MouseSixteen background;
  background.v[0]=0; background.v[1]=0; background.v[2]=0; background.v[3]=255;
  TheMouse->rva001EEBD5(wide,&foreground,&background);
 }
}
