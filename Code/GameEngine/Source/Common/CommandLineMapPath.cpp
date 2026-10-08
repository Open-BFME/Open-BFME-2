// Reference: EA BFME1 CommandLine.cpp ConvertShortMapPathToLongMapPath.
// BFME2 adds the .map guard, failed-token break and timestamped second output.
// Independently audited full retail extent 3BA06E..3BA232 (453 bytes), not
// the incomplete 10-byte inventory head. StringBase reference spelling names
// the existing audited pin; the label object uses AsciiString's format member.
// cl: /DNDEBUG /MD /EHs
#include <time.h>
// Use the shared one-pointer AsciiString for local ownership; preserve the
// existing StringBase reference ABI at the independently verified entry.
// The one-character append uses retail's aligned four-byte argument home;
// the direct shared find call avoids emitting a non-retail AsciiString thunk.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
void ConvertShortMapPathToLongMapPath(StringBase<char>& mapName,StringBase<char>& fileLabel) {
    if(!mapName.endsWithNoCase(".map")) return;
    AsciiString path(reinterpret_cast<const AsciiString &>(mapName));
    AsciiString token;
    AsciiString actualpath;
    if(!reinterpret_cast<const StringBase<char> &>(path).find('\\') && !reinterpret_cast<const StringBase<char> &>(path).find('/')) return;
    path.nextToken(&token,"\\/");
    while(!token.endsWithNoCase(".map") && token.getLength()>0) {
        actualpath.concat(token);
        { __declspec(align(4)) char slash = '\\'; reinterpret_cast<StringBase<char> &>(actualpath).concat(&slash,1); }
        if(!path.nextToken(&token,"\\/")) break;
    }
    token.removeLastChar(); token.removeLastChar();
    token.removeLastChar(); token.removeLastChar();
    actualpath.concat(token);
    { __declspec(align(4)) char slash = '\\'; reinterpret_cast<StringBase<char> &>(actualpath).concat(&slash,1); }
    actualpath.concat(token);
    actualpath.concat(".map");
    mapName.set(reinterpret_cast<const StringBase<char> &>(actualpath));
    char timestamp[256]={0};
    time_t now;
    time(&now);
    strftime(timestamp,256,"_%Y%m%d-%H%M%S",localtime(&now));
    reinterpret_cast<AsciiString&>(fileLabel).format("_%s%s",token.str(),timestamp);
}
