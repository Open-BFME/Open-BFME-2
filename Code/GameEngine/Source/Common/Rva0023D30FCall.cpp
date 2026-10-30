// cl: /MD
// ?rva0023D30F@GameLogic@@QAEXHHPAVUnicodeString@@@Z, retail 0x0023D30F, 30
// bytes. Every caller spells it as the GameLogic member - the shared
// GameLogicObjectLookupView.h view and AptSaveLoadCallbacks.cpp's own view -
// and retail's caller at 0x0024098B loads ECX with the handler object before
// the call, which only the thiscall spelling emits. The body never reads
// `this` (it reaches the target through TheNetwork) and cleans the same
// twelve stack bytes, so only the symbol changed.
// cmp [flag],0 je; mov ecx,[target] test ecx je; mov eax,[ecx] jmp [eax+0x108]; ret 0xc.
// Evidence: unlock lane; ret 0xc means 3-arg stdcall forwarding to slot 0x108.
// The shared GameLogic view already spells the callee as this member.
#include "GameLogicObjectLookupView.h"
// The flag tested first is the owned global TheGameInfo at VA 0xE02EEC.
class GameInfo;
extern GameInfo *TheGameInfo;
class Rva0023D30FTarget
{
public:
	virtual void v00(int a1, int a2, int a3);
	virtual void v01(int a1, int a2, int a3);
	virtual void v02(int a1, int a2, int a3);
	virtual void v03(int a1, int a2, int a3);
	virtual void v04(int a1, int a2, int a3);
	virtual void v05(int a1, int a2, int a3);
	virtual void v06(int a1, int a2, int a3);
	virtual void v07(int a1, int a2, int a3);
	virtual void v08(int a1, int a2, int a3);
	virtual void v09(int a1, int a2, int a3);
	virtual void v10(int a1, int a2, int a3);
	virtual void v11(int a1, int a2, int a3);
	virtual void v12(int a1, int a2, int a3);
	virtual void v13(int a1, int a2, int a3);
	virtual void v14(int a1, int a2, int a3);
	virtual void v15(int a1, int a2, int a3);
	virtual void v16(int a1, int a2, int a3);
	virtual void v17(int a1, int a2, int a3);
	virtual void v18(int a1, int a2, int a3);
	virtual void v19(int a1, int a2, int a3);
	virtual void v20(int a1, int a2, int a3);
	virtual void v21(int a1, int a2, int a3);
	virtual void v22(int a1, int a2, int a3);
	virtual void v23(int a1, int a2, int a3);
	virtual void v24(int a1, int a2, int a3);
	virtual void v25(int a1, int a2, int a3);
	virtual void v26(int a1, int a2, int a3);
	virtual void v27(int a1, int a2, int a3);
	virtual void v28(int a1, int a2, int a3);
	virtual void v29(int a1, int a2, int a3);
	virtual void v30(int a1, int a2, int a3);
	virtual void v31(int a1, int a2, int a3);
	virtual void v32(int a1, int a2, int a3);
	virtual void v33(int a1, int a2, int a3);
	virtual void v34(int a1, int a2, int a3);
	virtual void v35(int a1, int a2, int a3);
	virtual void v36(int a1, int a2, int a3);
	virtual void v37(int a1, int a2, int a3);
	virtual void v38(int a1, int a2, int a3);
	virtual void v39(int a1, int a2, int a3);
	virtual void v40(int a1, int a2, int a3);
	virtual void v41(int a1, int a2, int a3);
	virtual void v42(int a1, int a2, int a3);
	virtual void v43(int a1, int a2, int a3);
	virtual void v44(int a1, int a2, int a3);
	virtual void v45(int a1, int a2, int a3);
	virtual void v46(int a1, int a2, int a3);
	virtual void v47(int a1, int a2, int a3);
	virtual void v48(int a1, int a2, int a3);
	virtual void v49(int a1, int a2, int a3);
	virtual void v50(int a1, int a2, int a3);
	virtual void v51(int a1, int a2, int a3);
	virtual void v52(int a1, int a2, int a3);
	virtual void v53(int a1, int a2, int a3);
	virtual void v54(int a1, int a2, int a3);
	virtual void v55(int a1, int a2, int a3);
	virtual void v56(int a1, int a2, int a3);
	virtual void v57(int a1, int a2, int a3);
	virtual void v58(int a1, int a2, int a3);
	virtual void v59(int a1, int a2, int a3);
	virtual void v60(int a1, int a2, int a3);
	virtual void v61(int a1, int a2, int a3);
	virtual void v62(int a1, int a2, int a3);
	virtual void v63(int a1, int a2, int a3);
	virtual void v64(int a1, int a2, int a3);
	virtual void v65(int a1, int a2, int a3);
	virtual void slot108(int a1, int a2, int a3);
};
extern class NetworkInterface *TheNetwork;
void GameLogic::rva0023D30F(int a1, int a2, UnicodeString *name)
{
	if (TheGameInfo == 0)
		return;
	Rva0023D30FTarget *network = (*(Rva0023D30FTarget **)&TheNetwork);
	if (network == 0)
		return;
	network->slot108(a1, a2, (int)name);
}
