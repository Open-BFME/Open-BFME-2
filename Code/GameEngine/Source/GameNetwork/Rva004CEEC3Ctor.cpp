// cl: /DNDEBUG /MD /EHsc
// ??0Rva004CEEC3@@QAE@XZ retail 0x004CEEC3 37B
// NetCommandMsg-derived ctor with vtable 0x00860140 and type 3 plus members +0x1C=0 +0x20=0 +0x24=-1.
// Evidence: rowed base 0x004D5593 plus 4 callers 0x004D0434 0x004D0AD3 0x004D0C0A 0x0058DD10; class unproven so honest Rva name.
class NetCommandMsg {
public:
    NetCommandMsg();
};
class Rva004CEEC3 : public NetCommandMsg {
public:
    Rva004CEEC3();
};
Rva004CEEC3::Rva004CEEC3() : NetCommandMsg()
{
    *(unsigned int *)((char *)this + 0x1C) = 0;
    *(unsigned int *)((char *)this + 0x20) = 0;
    *(unsigned int *)((char *)this + 0x24) = (unsigned int)-1;
    *(unsigned int *)this = 0x00C60140;
    *(unsigned int *)((char *)this + 0x14) = 3;
}
