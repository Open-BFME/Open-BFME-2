// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native5BA3AD..5BA3C0: same NAT receiver gate to member schema+28.
class Rva005A6709 {public:int rva005A6709() const;};
class PortNegotiationSchema {public:bool rva005DBA9C(bool);};
struct Rva005BA3AD
{
public:
	bool rva005BA3AD();
	char prefix[0x28]; // +0x00
	PortNegotiationSchema schema; // +0x28
};
bool Rva005BA3AD::rva005BA3AD(){return schema.rva005DBA9C((((Rva005A6709 *)this)->*reinterpret_cast<bool (Rva005A6709::*)() const>(&Rva005A6709::rva005A6709))());}
