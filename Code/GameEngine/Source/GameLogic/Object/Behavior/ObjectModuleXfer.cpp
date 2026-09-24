// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
// stlport
//
// ?xfer@ObjectModule@@QAEXPAVXfer@@@Z retail 0x00560AE1
// 18 bytes. ObjectModule base xfer terminating the behavior xfer chain
// (BehaviorModule::xfer rowed over its pin; row supersedes that pin here).
// Retail transfers two fixed 1/1 Version pairs back to back; both lower to
// the rowed Version1 helper. Version1 resolves via its row.

class Xfer
{
public:
	void Version1();
};

class ObjectModule
{
public:
	void xfer(Xfer *xfer);
};

// ?xfer@ObjectModule@@QAEXPAVXfer@@@Z @0x00560AE1
void ObjectModule::xfer(Xfer *xfer)
{
	xfer->Version1();
	xfer->Version1();
}
