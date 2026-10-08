// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva00444240@BfmeAptScreenLanLobby@@QAE_NH@Z, retail 0x00444240 (57B):
// slot 3 of vftable 0x00C3E098, a client-side forwarder of its int argument
// to LANAPI slot 19 (TheLAN, 0x009FE958). It refuses (false) without a game
// from TheLAN slot 56 GetMyGame, when the rowed LANGameInfo::amIHost
// (0x004477C7) says we host, or without TheLAN; otherwise forwards and
// returns true. Three separate early-false guards give retail's block
// order (the false block between the guards and the call). The class and
// method names are address-derived; LANAPI is a slot-only view matching the
// lobby unit (BfmeAptScreenLanLobby.cpp).

class LANGameInfo
{
public:
	bool amIHost() const;
};

class LANAPI
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual void v17() = 0;
	virtual void v18() = 0;
	virtual void v19(int value) = 0;
	virtual void v20() = 0;
	virtual void v21() = 0;
	virtual void v22() = 0;
	virtual void v23() = 0;
	virtual void v24() = 0;
	virtual void v25() = 0;
	virtual void v26() = 0;
	virtual void v27() = 0;
	virtual void v28() = 0;
	virtual void v29() = 0;
	virtual void v30() = 0;
	virtual void v31() = 0;
	virtual void v32() = 0;
	virtual void v33() = 0;
	virtual void v34() = 0;
	virtual void v35() = 0;
	virtual void v36() = 0;
	virtual void v37() = 0;
	virtual void v38() = 0;
	virtual void v39() = 0;
	virtual void v40() = 0;
	virtual void v41() = 0;
	virtual void v42() = 0;
	virtual void v43() = 0;
	virtual void v44() = 0;
	virtual void v45() = 0;
	virtual void v46() = 0;
	virtual void v47() = 0;
	virtual void v48() = 0;
	virtual void v49() = 0;
	virtual void v50() = 0;
	virtual void v51() = 0;
	virtual void v52() = 0;
	virtual void v53() = 0;
	virtual void v54() = 0;
	virtual void v55() = 0;
	virtual LANGameInfo *GetMyGame() = 0;
};

class LANAPI; extern LANAPI *TheLAN;

class BfmeAptScreenLanLobby
{
public:
	bool rva00444240(int value);
};

bool BfmeAptScreenLanLobby::rva00444240(int value)
{
	LANGameInfo *game = TheLAN->GetMyGame();
	if (!game)
		return false;
	if (game->amIHost())
		return false;
	if (!TheLAN)
		return false;
	TheLAN->v19(value);
	return true;
}
