// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// cl: /O1 /G7 /arch:SSE /EHs /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// ?getPreferredMap@SkirmishPreferences@@QAE?AVAsciiString@@XZ, retail 0x0043C384 (306 bytes): Zero Hour's body with the invalid-map
// fallback falling through to the final return (finishes the 0.995 bank).
// Semantic donor: ZH SkirmishPreferences::getPreferredMap; twin lead
// GameModePreferences.cpp rva0044D986. Native43C384..43C4B6 owns the
// profile-key temporary from43BB6A and its preference map at this+4.
#include <map>
#include "ascii_string.h"
bool operator<(const AsciiString &,const AsciiString &);
namespace _STL {template<> struct less<AsciiString> {bool operator()(const AsciiString&a,const AsciiString&b)const{return a<b;}};}
typedef _STL::map<AsciiString,AsciiString> PreferenceMap;
#include "../../../Include/GameClient/SkirmishPreferencesClass.h"
AsciiString getDefaultMap(bool);
bool isValidMap(AsciiString,bool);
AsciiString QuotedPrintableToAsciiString(AsciiString);
AsciiString SkirmishPreferences::getPreferredMap() {
 AsciiString ret;
 PreferenceMap::iterator it=find(buildProfileKey("Map"));
 if(it==end()) {
  ret=getDefaultMap(true);
  return ret;
 }
 ret=QuotedPrintableToAsciiString(it->second);
 ret.trim();
 if(ret.isEmpty()||!isValidMap(ret,true))
  ret=getDefaultMap(true);
 return ret;
}

// The verified 30-byte provider at 0x43BB6A lives in Common/SkirmishPreferences.cpp.
