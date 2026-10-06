// Reference: EA UnicodeString.cpp translate/buffer-lifetime family;
// BFME2's explicit exports prove the modernized StringBase API identities.
// Retail uses two-pass UTF-8 conversion through the independently recovered
// platform wrappers. Empty/failed input releases the buffer; success stores
// the written character count excluding the terminator in the 16-bit length.
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
#include "unicode_string.h"
typedef unsigned short Wide;
int BFME2Utf8ToWide(const char*,int,Wide*,int);
int BFME2WideToUtf8(const Wide*,int,char*,int);
template<class T> class CharSource;
void UnicodeString::translate(const char* text) {
    if(text && *text) {
        int length=BFME2Utf8ToWide(text,-1,0,0);
        ensureUniqueBufferOfSize(length-1,false,0,0);
        int written=BFME2Utf8ToWide(text,-1,m_data->data,length);
        if(written) {
            m_data->length=written-1;
            return;
        }
    }
    releaseBuffer();
}
class AsciiString:public StringBase<char> {
public: void translate(const Wide*);
};
void AsciiString::translate(const Wide* text) {
    if(text && *text) {
        int length=BFME2WideToUtf8(text,-1,0,0);
        ensureUniqueBufferOfSize(length-1,false,0,0);
        int written=BFME2WideToUtf8(text,-1,m_data->data,length);
        if(written) {
            m_data->length=written-1;
            return;
        }
    }
    releaseBuffer();
}
