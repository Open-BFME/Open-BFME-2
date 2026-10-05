// cl: /O1 /MD /EHs
// ??1Rva00523775@@UAE@XZ @0x00523775 137B: Apt-screen dtor with UI hide and free.
// Evidence: callers 0x0052380C; callees rowed _free 0x00030830 plus pin Shell hide 0x0035BF4C plus pin AptGameWindow 0x005126F5; members +0x218 second vptr +0x288 free; globals g_Va00A04934 TheInGameUI g_Va00A01E48; vtables 0x00867C34 0x00867C30; neighbours ConstIntGetters.
class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();
private:
	char m_pad[0x218 - 4];
};

class BfmeAptFunctorMarker
{
public:
	virtual void marker() = 0;
};

struct GlobalA04934;
extern GlobalA04934 *g_Va00A04934;

struct GlobalA01E48;
extern GlobalA01E48 *g_Va00A01E48;

class InGameUI
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
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
	virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
	virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87();
	virtual void v88(); virtual void v89(); virtual void v90(); virtual void v91();
	virtual void v92(); virtual void v93();
	virtual void rva0178(int a);
};
extern InGameUI *TheInGameUI;

class Shell
{
public:
	void hide(bool b);
};

extern "C" void __cdecl free(void *p);

struct AutoFreePtr
{
	void *p;
// ??1AutoFreePtr@@QAE@XZ present-unmatched
	~AutoFreePtr() { if (p) free(p); }
};

class __multiple_inheritance Rva00523775
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	virtual ~Rva00523775();
private:
	char m_pad21C[0x288 - 0x21C];
	AutoFreePtr m_288;
};

Rva00523775::~Rva00523775()
{
	if ((void *)this == (void *)g_Va00A04934) {
		g_Va00A04934 = (GlobalA04934 *)0;
		if (TheInGameUI)
			TheInGameUI->rva0178(0);
		if (g_Va00A01E48)
			((Shell *)g_Va00A01E48)->hide(false);
	}
}
