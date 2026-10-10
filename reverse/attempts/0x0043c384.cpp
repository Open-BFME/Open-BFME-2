// ?getPreferredMap@SkirmishPreferences@@QAE?AVAsciiString@@XZ
// partial score=0.9952869221 date=2026-10-10
// ?getPreferredMap@SkirmishPreferences@@QAE?AVAsciiString@@XZ
// partial score=0.977124183 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /EHs /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// Semantic donor: ZH SkirmishPreferences::getPreferredMap; twin lead
// GameModePreferences.cpp rva0044D986. Native43C384..43C4B6 owns the
// profile-key temporary from43BB6A and its preference map at this+4.
#include <map>
#include "ascii_string.h"
bool operator<(const AsciiString &,const AsciiString &);
namespace _STL {template<> struct less<AsciiString> {bool operator()(const AsciiString&a,const AsciiString&b)const{return a<b;}};}
typedef _STL::map<AsciiString,AsciiString> PreferenceMap;
class SkirmishPreferences : public PreferenceMap {
public:
 virtual ~SkirmishPreferences();
 AsciiString buildProfileKey(const char *);
 AsciiString formatProfileKey(const AsciiString*,const char*);
 AsciiString filename; int profileIndex; void *userNames; AsciiString currentUserName;
 AsciiString getPreferredMap();
};
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
 if(ret.isEmpty()||!isValidMap(ret,true)) {
  ret=getDefaultMap(true);
  return ret;
 }
 return ret;
}

inline __declspec(noinline) AsciiString SkirmishPreferences::buildProfileKey(const char*name){return formatProfileKey(&currentUserName,name);}
