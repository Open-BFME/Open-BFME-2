// cl: /DNDEBUG /MD /EHsc
// ??0NetFrameCommandMsg@@QAE@XZ retail 0x004CEEC3 37B
// NetCommandMsg-derived ctor with vtable 0x00860140 and type 3 plus members +0x1C=0 +0x20=0 +0x24=-1.
// Evidence: rowed base 0x004D5593 plus 4 callers 0x004D0434 0x004D0AD3 0x004D0C0A 0x0058DD10.
// Target facts: command type 3 and the three dwords at +0x1C/+0x20/+0x24 that
// NetPacket's frame-info reader (0x0058DCEB) fills. Donor: type 3 is Zero Hour's
// NETCOMMANDTYPE_FRAMEINFO, set by NetFrameCommandMsg's ctor, and a BFME 1 donor
// body compiled /O1 places its NetFrameCommandMsg ctor call at this address.
// Formerly rowed as Rva004CEEC3.
class NetCommandMsg {
public:
    NetCommandMsg();
};
class NetFrameCommandMsg : public NetCommandMsg {
public:
    NetFrameCommandMsg();
};
NetFrameCommandMsg::NetFrameCommandMsg() : NetCommandMsg()
{
    *(unsigned int *)((char *)this + 0x1C) = 0;
    *(unsigned int *)((char *)this + 0x20) = 0;
    *(unsigned int *)((char *)this + 0x24) = (unsigned int)-1;
    *(unsigned int *)this = 0x00C60140;
    *(unsigned int *)((char *)this + 0x14) = 3;
}
