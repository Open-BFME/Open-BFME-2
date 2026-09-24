// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// GlobalData's user-preference overrides, retail 0x0023576A (312 bytes):
// the tail of Zero Hour's GlobalData::parseGameDataDefinition, which BFME 2
// runs as a member on the global instance. It reads OptionPreferences and
// copies the scroll factor (into two fields), LAN IP, firewall settings,
// alternate-mouse flag, gamma and resolution; both replay-camera flags are
// simply cleared. The gamma curve keeps Zero Hour's shape with the
// constants folded (0.4/50 = 0.008, 1/50 = 0.02). Only the GlobalData
// members this body writes are modelled, at their retail offsets. The
// UserPreferences model is the one in Common/UserPreferences.cpp.

#include <map>
#include <stdlib.h>

typedef bool Bool;
typedef int Int;
typedef float Real;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();

public:
	StringBase() : m_data(0) {}
	~StringBase();
	Int compare(const char *other) const;
	Int compareNoCase(const char *other) const;

protected:
	BfmeStringData<T> *m_data;
};

template <> class StringBase<unsigned short>
{
	friend class UnicodeString;
	void releaseBuffer();

public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }

protected:
	BfmeStringData<unsigned short> *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	static const AsciiString TheEmptyString;

	AsciiString() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString &operator=(const AsciiString &other);

	const char *str() const { return m_data ? &m_data->text[0] : ""; }
	Bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	void format(const char *fmt, ...);
	void toLower();
	Bool operator==(const char *other) const { return compare(other) == 0; }
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	void translate(const char *text);
};

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

typedef _STL::map<AsciiString, AsciiString> PreferenceMap;

class UserPreferences : public PreferenceMap
{
public:
	UserPreferences();
	virtual ~UserPreferences();

	// MSVC lays overloaded virtuals out in reverse declaration order, so
	// load(UnicodeString) takes slot 1 and load(AsciiString) slot 2.
	virtual Bool load(const AsciiString &fname);
	virtual Bool load(const UnicodeString &fname);
	virtual Bool write(void);

	virtual Bool getBool(const AsciiString &key, Bool defaultValue) const;
	virtual Real getReal(const AsciiString &key, Real defaultValue) const;
	virtual Int getInt(const AsciiString &key, Int defaultValue) const;
	virtual Int getEnumIndex(const char *key, const char **names, Int count, Int defaultValue) const;
	virtual AsciiString getAsciiString(const AsciiString &key, const AsciiString &defaultValue) const;

	virtual void setBool(const AsciiString &key, Bool val);
	virtual void setReal(const AsciiString &key, Real val);
	virtual void setInt(const AsciiString &key, Int val);
	virtual void setAsciiString(const AsciiString &key, const AsciiString &val);

protected:
	UnicodeString m_filename;
};

typedef short Short;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;

class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();

	Bool getAlternateMouseSetup();
	Real getScrollFactor();
	UnsignedInt getLANIPAddress();
	Bool getSendDelay();
	Int getFirewallBehavior();
	Short getFirewallPortAllocationDelta();
	UnsignedShort getFirewallPortOverride();
	Real getBrightness();
	void getResolution(Int *xres, Int *yres);
};

class GlobalData
{
public:
	void applyOptionPreferences();

private:
	unsigned char m_unreconstructed_000[ 0x30 ];
	Int m_xResolution;
	Int m_yResolution;
	unsigned char m_unreconstructed_038[ 0x24 ];
	Bool m_useAlternateMouse;
	unsigned char m_unreconstructed_05d[ 0x9EB ];
	UnsignedInt m_defaultIP;
	Int m_firewallBehavior;
	Bool m_firewallSendDelay;
	UnsignedInt m_firewallPortOverride;
	Short m_firewallPortAllocationDelta;
	unsigned char m_unreconstructed_a5a[ 0x42 ];
	Real m_keyboardScrollFactor;
	// Written from the same preference; its reader is not identified here.
	Real m_secondaryScrollFactor;
	unsigned char m_unreconstructed_aa4[ 0xCC ];
	Bool m_saveCameraInReplay;
	Bool m_useCameraInReplay;
	unsigned char m_unreconstructed_b72[ 0x5A ];
	Real m_displayGamma;
};

// ?applyOptionPreferences@GlobalData@@QAEXXZ @0x23576A
void GlobalData::applyOptionPreferences()
{
	OptionPreferences optionPref;
	m_keyboardScrollFactor = optionPref.getScrollFactor();
	m_secondaryScrollFactor = optionPref.getScrollFactor();
	m_defaultIP = optionPref.getLANIPAddress();
	m_firewallSendDelay = optionPref.getSendDelay();
	m_firewallBehavior = optionPref.getFirewallBehavior();
	m_firewallPortAllocationDelta = optionPref.getFirewallPortAllocationDelta();
	m_firewallPortOverride = optionPref.getFirewallPortOverride();
	m_useAlternateMouse = optionPref.getAlternateMouseSetup();
	m_saveCameraInReplay = false;
	m_useCameraInReplay = false;

	Int val = (Int)optionPref.getBrightness();
	// generate a value between 0.6 and 2.0.
	if (val < 50)
	{	// darker gamma
		if (val <= 0)
			m_displayGamma = 0.6f;
		else
			m_displayGamma = 1.0f - (Real)(50 - val) * 0.008f;
	}
	else
	if (val > 50)
		m_displayGamma = 1.0f + (Real)(val - 50) * 0.02f;

	Int xres, yres;
	optionPref.getResolution(&xres, &yres);

	m_xResolution = xres;
	m_yResolution = yres;
}
