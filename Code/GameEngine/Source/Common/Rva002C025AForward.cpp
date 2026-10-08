// cl: /MD
// Native2C025A..2C027B is a thiscall pointer-returning forwarder: native
// caller576946 sets ECX from viewer+14 and consumes EAX as an object pointer.
// WB D28B80 independently preserves this across the pair construction.
// Native2C00E0 passes the same ECX to2BFDE6 and returns its EAX; WB D2A1D0
// confirms both receiver and return. The old void-stdcall declaration matched
// the bytes accidentally because this body never modifies ECX or EAX after
// the call. Names and the payload fields remain address-derived.
// ?rva002C025A@Rva002C025AViewer@@QAEPAXPAXI_N@Z @0x002C025A 33B.
struct Rva002C025APair { unsigned int m_00; unsigned char m_04; };
class Rva002C025AViewer {
public:
 void *rva002C00E0(void *, Rva002C025APair *);
 void *rva002C025A(void *, unsigned int, bool);
};
void *Rva002C025AViewer::rva002C025A(void *point, unsigned int mask, bool flag) {
 Rva002C025APair pair;
 pair.m_00=mask;
 pair.m_04=flag;
 return rva002C00E0(point,&pair);
}

