// cl: /O1 /EHsc /MD /G6 /arch:SSE
// Home-screen persistent-storage request. Native 5BD64D..5BD6A7 RET0.
// Its 0x598 local uses the already verified constructor/destructor, writes
// type 10, and sends it through TheGameSpyPSMessageQueue slot4 when present.
// OnOpened refresh5B977B calls this helper immediately before5B95B8.
struct BfmeOpaqueOwnedRecord1432 {
 BfmeOpaqueOwnedRecord1432();
 ~BfmeOpaqueOwnedRecord1432();
 int type;
 unsigned char fields[0x598-4];
};
typedef char RequestSize[sizeof(BfmeOpaqueOwnedRecord1432)==0x598 ? 1 : -1];
class GameSpyPSMessageQueueInterface { public:
 virtual ~GameSpyPSMessageQueueInterface();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void addRequest(const BfmeOpaqueOwnedRecord1432 &);
};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;
void rva005BD64D()
{
 BfmeOpaqueOwnedRecord1432 request;
 request.type=10;
 if(TheGameSpyPSMessageQueue)
  TheGameSpyPSMessageQueue->addRequest(request);
}
