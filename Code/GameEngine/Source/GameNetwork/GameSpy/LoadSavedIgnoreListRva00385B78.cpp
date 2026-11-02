// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// BFME1 clean donor GameSpyInfo_loadSavedIgnoreList_Thunk.cpp at
// 6583b3c1ff21db4a561285717028fdafc780b7db supplies clear / read / assign purpose.
// Native Ghidra [0x00385B78,0x00385BDC),100B independently calls the rowed
// IgnorePreferences constructor/getter/destructor and consumes tree storage
// at owner+0x1614. Original owner and virtual slot are not independently pinned.
// The address-derived owner and 12B call-only tree view preserve this uncertainty.
// Clear41/assign115/dtor56 providers are independently fully byte-verified.
// A normal map<int,AsciiString> trial also emits100B but binds clear/assignment
// to other tree variants; do not add these addresses to those general pins.
// UserPreferences/IgnorePreferences declarations match their current native
// Code/Common/UserPreferences.cpp view; added getter spelling changes only
// its return class view while retaining the witnessed hidden-retptr ABI.
#include "ascii_string.h"
#include "unicode_string.h"
#include <map>
typedef bool Bool;typedef int Int;typedef float Real;
typedef _STL::map<AsciiString,AsciiString> PreferenceMap;
#include "../../../Include/Common/UserPreferences.h"


typedef _STL::map<int,AsciiString> IgnorePrefMap;
class Rva00385B78SavedMap {public:
 ~Rva00385B78SavedMap();
 void clear();Rva00385B78SavedMap& operator=(const Rva00385B78SavedMap&);
 private:unsigned int storage[3];
};
class IgnorePreferences:public UserPreferences {
 public:IgnorePreferences();virtual ~IgnorePreferences();IgnorePrefMap getIgnores();Rva00385B78SavedMap rva003B224D();
};
class Rva00385B78 {public:void loadSavedIgnoreList();private:
 char unknown[0x1614];Rva00385B78SavedMap saved;
};
void Rva00385B78::loadSavedIgnoreList() {
 saved.clear();
 IgnorePreferences preferences;
 saved=preferences.rva003B224D();
}

#pragma comment(linker, "/alternatename:?clear@Rva00385B78SavedMap@@QAEXXZ=?rva00383A28@Rva00383A28@@QAEXXZ")

#pragma comment(linker, "/alternatename:??4Rva00385B78SavedMap@@QAEAAV0@ABV0@@Z=?rva0038407F@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@QAEAAV12@ABV12@@Z")

#pragma comment(linker, "/alternatename:??1Rva00385B78SavedMap@@QAE@XZ=??1Rva00383A28@@QAE@XZ")

#pragma comment(linker, "/alternatename:?rva003B224D@IgnorePreferences@@QAE?AVRva00385B78SavedMap@@XZ=?getIgnores@IgnorePreferences@@QAE?AV?$map@HVAsciiString@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@3@@_STL@@XZ")
