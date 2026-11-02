// cl: /O1 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE /G7 /Oy-
//
// ?onContaining@HordeSiegeEngineContain@@UAEXPAVObject@@_N@Z @ 0x0047CF67 (75B).
// Slot 66 of vtable 0x008474A0 for HordeSiegeEngineContain: walk list at +0x108
// calling Object::defect then tail to TransportContain onContaining
// 0x00463191 with the same rider and flag. Evidence: VTABLE slot 66 plus REF
// neighbours at 0x00847430 plus prev/next HordeSiegeEngineContain units plus
// pin-only callees plus Rva0047CF38 sibling for +0x108 list layout.
#include "../object.h"
struct Rva0047CF67Mid
{
	char mPad00[8];
	Object *mObj08;
};
struct Rva0047CF67Node
{
	void *mHead00;
	Rva0047CF67Mid *mMid04;
};
class TransportContain
{
public:
	virtual void onContaining(Object *rider, bool flag);
};
class HordeSiegeEngineContain : public TransportContain
{
public:
	virtual void onContaining(Object *rider, bool flag);
private:
	char mPad04[0x108 - 4];
	Rva0047CF67Node *mList108;
};
void HordeSiegeEngineContain::onContaining(Object *rider, bool flag)
{
	Rva0047CF67Node *cur = mList108;
	if (cur == *(Rva0047CF67Node * *)cur)
		goto done;
	do {
		Object *receiver = cur->mMid04->mObj08;
		if (flag) {
			receiver->defect(rider, true);
		} else {
			receiver->defect(rider, false);
		}
		cur = (Rva0047CF67Node *)cur->mMid04;
	} while (cur != *(Rva0047CF67Node * *)mList108);
done:
	TransportContain::onContaining(rider, flag);
}
