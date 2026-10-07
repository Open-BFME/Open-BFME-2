// ?rva00427F14Text@VersionBlockParser@@QAE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@ABURva00427F14KeyPrefix@@@Z
// partial score=1.0 date=2026-10-07
// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Complete boundaries: 427F14..427F46 (50B), 427F46..427F75 (47B).
// The two complete retail returns call rowed VersionBlockParser lookup
// 427EDA, then construct the caller's return storage with rowed STLport
// narrow-string constructor 9100. Key/default arguments expose only word 0;
// their original C++ wrapper types and these method spellings are unknown.
// stlport
#include <string>
typedef std::string NarrowString;
struct Rva00427F14KeyPrefix {
    const char *first;
    const char *text() const { return first; }
};
class VersionBlockParser {
public:
    const char *lookupVersionValue(const char *, const char *);
    NarrowString rva00427F14Text(const Rva00427F14KeyPrefix &key);
    NarrowString rva00427F46Text(const Rva00427F14KeyPrefix &key,
                               const Rva00427F14KeyPrefix &fallback);
};
NarrowString VersionBlockParser::rva00427F14Text(const Rva00427F14KeyPrefix &key) {
    const char *text = lookupVersionValue(key.text(), 0);
    if (!text) text = "";
    return NarrowString(text);
}
NarrowString VersionBlockParser::rva00427F46Text(const Rva00427F14KeyPrefix &key,
                                               const Rva00427F14KeyPrefix &fallback) {
    return NarrowString(lookupVersionValue(key.text(), fallback.text()));
}
