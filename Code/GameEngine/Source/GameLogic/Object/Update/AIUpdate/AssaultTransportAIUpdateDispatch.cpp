// cl: /O1 /DNDEBUG /MD
//
// ?Rva0048F7A7Dispatch@AssaultTransportAIUpdateSecondary@@QAEXPAUBfmeBehaviorRequest@@@Z,
// retail 0x0048F7A7 (129 bytes). Request dispatcher on the behavior's
// secondary subobject at +0x20: mode 2 requests skip straight to the base
// tail delegate, otherwise the request ID selects helper work on the primary
// (this minus 0x20, reached by an explicit back-cast per call so every site
// keeps its own lea) before always delegating to the base. Request 5 zeroes
// the +0x410 word then runs both helpers; requests 0xB and 0x39 run the reset
// helper and raise the +0x421 flag; request 0xF runs the reset helper, copies
// the 12-byte payload into the +0x404 triple and raises the +0x420 flag; any
// other request just runs the reset helper. The +0x404/+0x410/+0x420 members
// are the secondary view of the primary's +0x424/+0x430/+0x440 tail proven by
// the rowed Rva0048F365Helper TU. Case order in source is load-bearing for
// the compiler's block layout.

struct BfmeFloatTriple
{
	float m_x;
	float m_y;
	float m_z;
};

struct BfmeBehaviorRequest
{
	int m_request;
	int m_mode;
	BfmeFloatTriple m_payload;
};

class Rva002673F6Base
{
public:
	void Rva002673F6Dispatch(BfmeBehaviorRequest *request);
};

class AssaultTransportAIUpdate
{
public:
	void Rva0048F690Helper();
	void Rva0048F365Helper();
};

class AssaultTransportAIUpdateSecondary : public Rva002673F6Base
{
public:
	void Rva0048F7A7Dispatch(BfmeBehaviorRequest *request);

private:
	unsigned char m_pad00[0x404];
	BfmeFloatTriple m_triple404;
	int m_int410;
	unsigned char m_pad414[0x420 - 0x414];
	unsigned char m_byte420;
	unsigned char m_byte421;
};

void AssaultTransportAIUpdateSecondary::Rva0048F7A7Dispatch(BfmeBehaviorRequest *request)
{
	if (request->m_mode != 2)
	{
		switch (request->m_request)
		{
		case 5:
			{
				m_int410 = 0;
				AssaultTransportAIUpdate *atBase = (AssaultTransportAIUpdate *)((char *)this - 0x20);
				atBase->Rva0048F690Helper();
				atBase->Rva0048F365Helper();
			}
			break;
		case 0xB:
		case 0x39:
			((AssaultTransportAIUpdate *)((char *)this - 0x20))->Rva0048F365Helper();
			m_byte421 = 1;
			break;
		case 0xF:
			((AssaultTransportAIUpdate *)((char *)this - 0x20))->Rva0048F365Helper();
			m_triple404 = request->m_payload;
			m_byte420 = 1;
			break;
		default:
			((AssaultTransportAIUpdate *)((char *)this - 0x20))->Rva0048F365Helper();
			break;
		}
	}
	Rva002673F6Base::Rva002673F6Dispatch(request);
}
