// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native5BA3AD..5BA3C0: same NAT receiver gate to member schema+28.
class NAT {public:bool rva005A6709();};
class PortNegotiationSchema {public:bool rva005DBA9C(bool);};
class Rva005BA3AD {public:char prefix[0x28];PortNegotiationSchema schema;bool rva005BA3AD();};
bool Rva005BA3AD::rva005BA3AD(){return schema.rva005DBA9C(((NAT *)this)->rva005A6709());}
