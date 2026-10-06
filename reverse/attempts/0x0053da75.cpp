// ?rva0053DA75@Rva0053DA75@@QAE_N_N@Z
// partial score=0.93 date=2026-10-06
// cl: /O1 /MD
// ?rva0053DA75@Rva0053DA75@@QAE_N_N@Z @0x0053DA75 91B ref: window message 0x4008/0x400B via manager slot 0xE8.
// Evidence: table slot 0x0086931C, callees rowed winGetInstanceData winGetWindowId, TheWindowManager, neighbours share flags.
class GameWindow;
struct WinInstanceData
{
	char m_pad[0x14];
	void *m_14;
};
class GameWindow
{
public:
	WinInstanceData *winGetInstanceData();
	int winGetWindowId();
};
class GameWindowManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57();
	virtual int v58(void *a, int b, GameWindow *c, int d);
};
extern GameWindowManager *TheWindowManager;
class Rva0053DA75
{
public:
	bool rva0053DA75(bool flag);
private:
	char m_pad[8];
	GameWindow *m_window;
};
bool Rva0053DA75::rva0053DA75(bool flag)
{
	WinInstanceData *inst = m_window->winGetInstanceData();
	if (inst)
	{
		GameWindowManager *mgr = TheWindowManager;
		void *sub = inst->m_14;
		int id = m_window->winGetWindowId();
		int msg = flag ? 0x400B : 0x4008;
		if (mgr->v58(sub, msg, m_window, id) || flag == 0)
			return true;
		return false;
	}
	return false;
}
