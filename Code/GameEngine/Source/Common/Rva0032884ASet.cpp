// cl: /Ireference/shims/bfme2_ascii /EHs /MD
// Rva0032884ASet, retail 0x0032884A (159B).
// Gadget sound helper: stores resolved audio ref into user data +0x1c.
// Evidence: rowed winGetUserData 0x005C4ACD, TheAudio 0x00DFE6E8 virtual
// slot 0x12c, StringBase compare 0x000069B1 with "NoSound" literal,
// OpaqueRef assign 0x00239099 and Release_Ref 0x00050ED3, EH_prolog frame.
// Retail's unwind map destroys the by-value sound name (state 0) and the
// ref handle that the audio slot returns by value into the window
// parameter's slot (state 1, dtor 0x0010F149); the handle's inline
// destructor releases it after the store. The banked attempt passed an out
// pointer and released by hand.

#include "ascii_string.h"

class GameWindow
{
public:
	void *winGetUserData();
};

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct OpaqueRefElement4
{
	OpaqueRefCounted *m_ptr;
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
	~OpaqueRefElement4() { if (m_ptr) m_ptr->Release_Ref(); }
};

class AudioManager
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
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
	virtual void v72(); virtual void v73(); virtual void v74();
	virtual OpaqueRefElement4 Unknown75(AsciiString *sound);
};

extern AudioManager *TheAudio;
struct Rva0032884AUserData
{
	unsigned char m_pad00[0x1c];
	OpaqueRefElement4 m_sound;
};

void Rva0032884ASet(GameWindow *window, AsciiString sound)
{
	if (window == 0)
		return;
	Rva0032884AUserData *userData = (Rva0032884AUserData *)window->winGetUserData();
	if (userData == 0)
		return;
	OpaqueRefElement4 tmp = TheAudio->Unknown75(&sound);
	if (tmp.m_ptr == 0 && !sound.isEmpty())
		sound.compare("NoSound");
	userData->m_sound = tmp;
}
