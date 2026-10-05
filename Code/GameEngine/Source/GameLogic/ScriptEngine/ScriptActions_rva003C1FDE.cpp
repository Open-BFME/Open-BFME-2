// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
// ?rva003C1FDE@Rva003C1FDE@@QAEXABVAsciiString@@PAX@Z @0x003C1FDE 59B
// Display flag via rowed StringBase copy and virtuals.
// Evidence: caller 0x003CDC9C; neighbours 0x003C1FAD 0x003C2662; global TheDisplay.
#include "ascii_string.h"

class Display {
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
	virtual void v64(); virtual void v65(); virtual void v66();
	virtual void v67(AsciiString s, void *a2, int n);
	char m_pad[0x10c - 4];
	unsigned char m_flag10c;
};

extern Display *TheDisplay;

class Rva003C1FDE {
public:
	virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
	virtual void w04(); virtual void w05(); virtual void w06(); virtual void w07();
	virtual void w08(); virtual void w09(); virtual void w10(); virtual void w11();
	virtual void w12(); virtual void w13(); virtual void w14();
	virtual void w15(int x);
	void rva003C1FDE(const AsciiString &a1, void *dead);
};

void Rva003C1FDE::rva003C1FDE(const AsciiString &a1, void *dead)
{
	(void)dead;
	w15(1);
	TheDisplay->v67((AsciiString &)a1, dead, 0x30);
	TheDisplay->m_flag10c = 1;
}
