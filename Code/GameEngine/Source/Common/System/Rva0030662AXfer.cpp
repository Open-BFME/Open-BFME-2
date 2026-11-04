// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// platformsdk
// Retail 0x0030662A 217B: Xfer-string plus audio-tag helper next to 0x3064CB.
// Evidence: Rva0036CA00Str copy row 0x000A8C7C, StringBase copy row 0x000365F0,
// Xfer AsciiString slot 0x6C plus IsLoading slot 0x04, TheAudio ?TheAudio,
// Opaque assign row 0x00239099 plus Release_Ref row 0x00050ED3,
// releaseBuffer row 0x00036410, AsciiString::TheEmptyString,
// the pooled "" literal, StringBase char* ctor row 0x00037BA0.
// Retail keeps the copied tag's referent in EDI from the copy through its
// inlined destructor: cl only proves the copy does not escape when the copy
// constructor (0x000A8C7C) body is visible, so it is defined here out of
// line, byte-identical to its retail body.
#include <windows.h>
#include "ascii_string.h"
class Xfer;
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
#include "../../../Include/Common/BfmeXfer.h"
#include "../../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"
struct OpaqueRefElement4

{
 OpaqueRefCounted *referent;
 OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
 
}
;
class Rva0036CA00Str : public OpaqueRefElement4

{
 public:
 __declspec(noinline) Rva0036CA00Str(const Rva0036CA00Str &other)
 {
  referent = other.referent;
  if (referent)
   InterlockedIncrement((long volatile *)((char *)referent + 4));
 }
 ~Rva0036CA00Str() 
 {
  if (referent) referent->Release_Ref();
  
 }
 
}
;
class AudioManager;
extern AudioManager *TheAudio;
class AudioManager

{
 public:
 virtual ~AudioManager();
 virtual void v01();
 virtual void v02();
 virtual void v03();
 virtual void v04();
 virtual void v05();
 virtual void v06();
 virtual void v07();
 virtual void v08();
 virtual void v09();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual void v19();
 virtual void v20();
 virtual void v21();
 virtual void v22();
 virtual void v23();
 virtual void v24();
 virtual void v25();
 virtual void v26();
 virtual void v27();
 virtual void v28();
 virtual void v29();
 virtual void v30();
 virtual void v31();
 virtual void v32();
 virtual void v33();
 virtual void v34();
 virtual void v35();
 virtual void v36();
 virtual void v37();
 virtual void v38();
 virtual void v39();
 virtual void v40();
 virtual void v41();
 virtual void v42();
 virtual void v43();
 virtual void v44();
 virtual void v45();
 virtual void v46();
 virtual void v47();
 virtual void v48();
 virtual void v49();
 virtual void v50();
 virtual void v51();
 virtual void v52();
 virtual void v53();
 virtual void v54();
 virtual void v55();
 virtual void v56();
 virtual void v57();
 virtual void v58();
 virtual void v59();
 virtual void v60();
 virtual void v61();
 virtual void v62();
 virtual void v63();
 virtual void v64();
 virtual void v65();
 virtual void v66();
 virtual void v67();
 virtual void v68();
 virtual void v69();
 virtual void v70();
 virtual void v71();
 virtual void v72();
 virtual void v73();
 virtual void v74();
 virtual Rva0036CA00Str getAudio(const AsciiString &name);
 
}
;
// ?Rva0030662AXfer@@YAXPAVXfer@@ABVRva0036CA00Str@@@Z
void __cdecl Rva0030662AXfer(Xfer *xfer, const Rva0036CA00Str &tag)

{
 Rva0036CA00Str tmp(tag);
 const AsciiString *namePtr;
{
 OpaqueRefCounted *item = tmp.referent;
 namePtr = item ? (const AsciiString *)((const char *)item + 8) : &AsciiString::TheEmptyString;
}
 AsciiString xferStr(*namePtr);
 *xfer == xferStr;
 if (!xfer->IsLoading())
 return;
{
 char *t = *(char **)(void *)&xferStr;
 const char *audioChars = t ? t + 8 : "";
 AsciiString audioStr(audioChars);
 ((OpaqueRefElement4 &)const_cast<Rva0036CA00Str &>(tag)) = (const OpaqueRefElement4 &)TheAudio->getAudio(audioStr);
}
 
}
