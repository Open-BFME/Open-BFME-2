// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
// stlport
//
// ?xfer@BehaviorModule@@QAEXPAVXfer@@@Z retail 0x004C9C7D
// 24 bytes. BehaviorModule base xfer used by the UpdateModule xfer chain
// (UpdateModule::xfer rowed over its pin; row supersedes that pin here).
//
// Transcribed from the Zero Hour donor
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/
// Code/GameEngine/Source/GameLogic/Object/Behavior/BehaviorModule.cpp):
// Version1 on the stream, then the ObjectModule base xfer (pinned).
// Version1 resolves via its row.

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

class BehaviorModule : public ObjectModule
{
public:
	void xfer(Xfer *xfer);
};

// ?xfer@BehaviorModule@@QAEXPAVXfer@@@Z @0x004C9C7D
void BehaviorModule::xfer(Xfer *xfer)
{
	xfer->Version1();

	ObjectModule::xfer(xfer);
}
