// ?helper001DA770@@YAXPAVINI@@HPAVAsciiString@@PBD@Z
// partial score=0.93 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
//
// ?helper001DA770@@YAXPAVINI@@HPAVAsciiString@@PBD@Z @0x001DA770 528B.
// Shared cdecl audio-block parser for the five Default-name wrappers.
// Evidence: callers 0x001DA9AA/0x001DA9F4/0x001DAA3E/0x001DAA88/0x001DAAD2,
// strings "You cannot define or override a %s in map.ini",
// "Control flag 'RANDOMSTART' is not valid for ",
// ". Streaming sound types only, please.", TheAudio 0x009FE6E8,
// theDebug 0x009E0880, field table g_00BD9D68, float g_00BDA3E4.
#include "ascii_string.h"

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &that);
	~INIException();
};

struct FieldParse;

class INI
{
public:
	int getLoadType() { return m_loadType; }
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const struct FieldParse *table);
private:
	char m_pad00[8];
	int m_loadType;
};

extern const struct FieldParse g_00BD9D68[];
extern const float g_00BDA3E4;

class OpaqueRefCounted
{
public:
	virtual ~OpaqueRefCounted();
	void Release_Ref();
};

struct OpaqueRefElement4
{
	OpaqueRefCounted *referent;
	OpaqueRefElement4() : referent(0) {}
	~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

class Rva001DA379
{
public:
	Rva001DA379 *rva001DA379(const Rva001DA379 &other);
	AsciiString &getName() { return m_audioName; }
public:
	char m_pad00[8];
	AsciiString m_audioName;
	AsciiString m_filename;
	int m_10;
	float m_volumeShift;
	float m_volumeShift2;
	int m_1C;
	float m_pitchShiftMin;
	float m_pitchShiftMax;
	float m_pitchShift2Min;
	float m_pitchShift2Max;
	int m_30;
	int m_delayMin;
	int m_delayMax;
	int m_3C;
	int m_40;
	int m_44;
	unsigned int m_type;
	unsigned int m_control;
	char m_pad50[0xB0 - 0x50];
	int m_soundType;
};

class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72();
	virtual OpaqueRefElement4 newAudioEventInfo(const AsciiString &name, int create);
	virtual void slot74();
	virtual OpaqueRefElement4 findAudioEventInfo(const AsciiString &name) const;
};

extern AudioManager *TheAudio;

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual bool CrashDone(int mode);
	virtual void pad20(); virtual void pad21(); virtual void pad22();
	virtual void SetCrashAddress(void *returnAddress, int set);
	virtual void SkipNext();
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
};

extern Debug *theDebug;
void _bfme_debugRecordCallsite(int kind);
bool bfmeRva000387C0();

void __cdecl helper001DA770(INI *ini, int kind, AsciiString *defName, const char *typeName)
{
	int allow = 1;
	if (ini->getLoadType() == 2)
		throw INIException(3, "You cannot define or override a %s in map.ini", typeName);
	if (ini->getLoadType() == 5)
		allow = 0;
	AsciiString name;
	OpaqueRefElement4 track;
	((StringBase<char> *)&name)->set(ini->getNextToken(0));
	track = TheAudio->newAudioEventInfo(name, allow);
	Rva001DA379 *info = (Rva001DA379 *)track.referent;
	if (!info)
		return;
	OpaqueRefElement4 defInfo = TheAudio->findAudioEventInfo(*defName);
	if (defInfo.referent != 0) {
		info->rva001DA379((const Rva001DA379 &)*(Rva001DA379 *)defInfo.referent);
		info->m_type &= ~0x400;
	}
	info->m_audioName = name;
	info->m_soundType = kind;
	ini->initFromINI(info, g_00BD9D68);
	if (kind == 2 && (info->m_control & 4)) {
		if (bfmeRva000387C0()) {
			_bfme_debugRecordCallsite(1);
			theDebug->SkipNext();
			(theDebug->CrashBegin(0, 0, 0) << "Control flag 'RANDOMSTART' is not valid for " << typeName << ". Streaming sound types only, please.").CrashDone(2);
		}
		info->m_control &= ~4;
	}
	if (info->m_control & 0x80)
		info->m_control &= ~0x80;
	if (info->m_delayMin < 0) {
		info->m_delayMin = 0;
		if (info->m_delayMax < 0)
			info->m_delayMax = 0;
	}
	if (info->m_pitchShiftMin <= -100.0f) {
		info->m_pitchShiftMin = g_00BDA3E4;
		if (info->m_pitchShiftMax <= -100.0f)
			info->m_pitchShiftMax = g_00BDA3E4;
	}
	if (info->m_pitchShift2Min <= -100.0f) {
		info->m_pitchShift2Min = g_00BDA3E4;
		if (info->m_pitchShift2Max <= -100.0f)
			info->m_pitchShift2Max = g_00BDA3E4;
	}
	if (info->m_volumeShift < -100.0f || info->m_volumeShift > 0.0f)
		info->m_volumeShift = 0.0f;
	if (info->m_volumeShift2 < -100.0f || info->m_volumeShift2 > 0.0f)
		info->m_volumeShift2 = 0.0f;
}
