// Reference: EA BFME1 CommandLine.cpp ConvertShortMapPathToLongMapPath.
// BFME2 adds the .map guard, failed-token break and timestamped second output.
// Independently audited full retail extent 3BA06E..3BA232 (453 bytes), not
// the incomplete 10-byte inventory head. StringBase reference spelling names
// the existing audited pin; the label object uses AsciiString's format member.
// cl: /DNDEBUG /MD /EHs
#include <time.h>
template<class T> class StringBase;
void ConvertShortMapPathToLongMapPath(StringBase<char>& mapName,StringBase<char>& fileLabel);
template<class T> class StringBase {
    struct Header { int refs; unsigned short length,capacity; T data[1]; };
    Header *data;
private:
    StringBase(const StringBase&);
    friend void ConvertShortMapPathToLongMapPath(StringBase<char>& mapName,StringBase<char>& fileLabel);
public:
    StringBase():data(0){}
    ~StringBase();
    bool endsWithNoCase(const T*) const;
    const T* find(T) const;
    bool nextToken(StringBase*,const T*);
    int getLength() const { return data ? data->length : 0; }
    const T* str() const { return data ? data->data : ""; }
    void concat(const StringBase&);
    void concat(const T*);
    void concat(const T*,int);
    void concat(T c) { concat(&c,1); }
    void removeLastChar();
    void set(const StringBase&);
};
class AsciiString:public StringBase<char> {
public: void __cdecl format(const char*,...);
};
void ConvertShortMapPathToLongMapPath(StringBase<char>& mapName,StringBase<char>& fileLabel) {
    if(!mapName.endsWithNoCase(".map")) return;
    StringBase<char> path(mapName);
    StringBase<char> token;
    StringBase<char> actualpath;
    if(!path.find('\\') && !path.find('/')) return;
    path.nextToken(&token,"\\/");
    while(!token.endsWithNoCase(".map") && token.getLength()>0) {
        actualpath.concat(token);
        actualpath.concat('\\');
        if(!path.nextToken(&token,"\\/")) break;
    }
    token.removeLastChar(); token.removeLastChar();
    token.removeLastChar(); token.removeLastChar();
    actualpath.concat(token);
    actualpath.concat('\\');
    actualpath.concat(token);
    actualpath.concat(".map");
    mapName.set(actualpath);
    char timestamp[256]={0};
    time_t now;
    time(&now);
    strftime(timestamp,256,"_%Y%m%d-%H%M%S",localtime(&now));
    static_cast<AsciiString&>(fileLabel).format("_%s%s",token.str(),timestamp);
}
