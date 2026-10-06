// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// INI::parseMiscAudio @0x001ED6EE (30B): Zero Hour INIMiscAudio.cpp's
// body. Identity from the INI block table: the "MiscAudio" token's entry
// names this address. TheAudio's friend_getMiscAudio is virtual in BFME 2
// (vtable slot +0x13C) where ZH had it non-virtual; the block fills it from
// MiscAudio's field-parse table 0x00BDF2D0.

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);

	static void parseMiscAudio(INI *ini);
};

struct MiscAudio
{
	static const FieldParse m_fieldParseTable[];
};

class AudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void
	v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual
	void v07(); virtual void v08(); virtual void v09(); virtual void v10();
	virtual void v11(); virtual void v12(); virtual void v13(); virtual void
	v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual
	void v18(); virtual void v19(); virtual void v20(); virtual void v21();
	virtual void v22(); virtual void v23(); virtual void v24(); virtual void
	v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual
	void v29(); virtual void v30(); virtual void v31(); virtual void v32();
	virtual void v33(); virtual void v34(); virtual void v35(); virtual void
	v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual
	void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void
	v47(); virtual void v48(); virtual void v49(); virtual void v50(); virtual
	void v51(); virtual void v52(); virtual void v53(); virtual void v54();
	virtual void v55(); virtual void v56(); virtual void v57(); virtual void
	v58(); virtual void v59(); virtual void v60(); virtual void v61(); virtual
	void v62(); virtual void v63(); virtual void v64(); virtual void v65();
	virtual void v66(); virtual void v67(); virtual void v68(); virtual void
	v69(); virtual void v70(); virtual void v71(); virtual void v72(); virtual
	void v73(); virtual void v74(); virtual void v75(); virtual void v76();
	virtual void v77(); virtual void v78();
	virtual MiscAudio *friend_getMiscAudio(void);   // +0x13C
};

extern AudioManager *TheAudio;

void INI::parseMiscAudio(INI *ini)
{
	ini->initFromINI(TheAudio->friend_getMiscAudio(), MiscAudio::m_fieldParseTable);
}
