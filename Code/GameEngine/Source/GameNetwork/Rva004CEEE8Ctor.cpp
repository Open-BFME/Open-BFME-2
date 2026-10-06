// cl: /DNDEBUG /MD /EHsc
// ??0Rva004CEEE8@@QAE@XZ retail 0x004CEEE8 25B
// NetCommandMsg-derived ctor sharing vtable 0x00860244 via ICF fold with rowed NetKeepAlive 0x004D57C7; stamps type 0x17 at +0x14.
// Evidence: rowed base 0x004D5593 plus 2 callers 0x004D0C88 0x0058DD89; class unproven so honest Rva name.
extern "C" const void *const vtbl_00C60244[];  // folded, 7 classes; via ??_7NetDisconnectKeepAliveCommandMsg@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C60244=??_7NetDisconnectKeepAliveCommandMsg@@6B@")

class NetCommandMsg {
public:
    NetCommandMsg();
};
class Rva004CEEE8 : public NetCommandMsg {
public:
    Rva004CEEE8();
};
Rva004CEEE8::Rva004CEEE8() : NetCommandMsg()
{
    *(unsigned int *)this = ((unsigned int)vtbl_00C60244);
    *(unsigned int *)((char *)this + 0x14) = 0x17;
}
