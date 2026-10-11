// cl: /O1 /G7 /arch:SSE /MD /EHs /Ireference/shims/bfme2_ascii
// Complete243B native317D89..317E7C RET0. The existing descriptive pin is
// supported by TerrainType::getNrmTexture and the floor/road normal-map callers.
// WB A90B20 is unnamed: it independently witnesses last-dot splitting and the
// exact _nrm literal, expression-node arguments and cleanup sequence.
// Non-POD concat-node defaults preserve the established hidden-result ABI,
// eliminating POD block copies; every callee already has a matched body.
// Rva00317C68Append's existing second-argument spelling is const char*, but
// native317DF7 and WB A90C0E pass the full text-plus-string node by reference.
// The call view below preserves that witnessed ABI without an alias or pin.
#include "ascii_string.h"
struct Rva000B3F84Pair { const char *text; int length; };
struct AsciiStringRef { const AsciiString *string; };
struct Rva002226E5TextPlusString { Rva000B3F84Pair left; AsciiStringRef right; Rva002226E5TextPlusString() {} };
struct AsciiStringPlusText {
    AsciiStringPlusText() {}
    AsciiStringRef left;
    Rva000B3F84Pair right;
    operator AsciiString();
};
Rva002226E5TextPlusString operator+(const char *,const AsciiString &);
AsciiStringPlusText operator+(const AsciiString &,const char *);
AsciiString &Rva00317C68Append(AsciiString &,const char *);
AsciiString makeNrmTextureName(const AsciiString &in)
{
    const char *dot=((const StringBase<char> &)in).reverseFind('.');
    if (dot) {
        AsciiString extension(dot);
        AsciiString base(in,0,dot-in.str());
        typedef AsciiString &(__cdecl *AppendNode)(AsciiString &,const Rva002226E5TextPlusString &);
        AppendNode append=reinterpret_cast<AppendNode>(&Rva00317C68Append);
        append(base,"_nrm"+extension);
        return base;
    }
    return in+"_nrm";
}
