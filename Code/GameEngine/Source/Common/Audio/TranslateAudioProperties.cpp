// cl: /O1 /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /Gy
// platformsdk
//
// ?TranslateAudioProperties@@YAXPAVDict@@PAVDrawable@@PAVThingTemplate@@PA_NPAVRva000A8C9B@@3@Z
// retail 0x00433796, 898 bytes.
//
// Target evidence: the map-object ambient-sound reader. Its caller
// GameClient::rva0023B383 (0x0023B383) passes the object's Dict, a null
// drawable, its ThingTemplate, a force-off flag, the custom-info reference and
// an enabled flag. Retail reads the key caches 0x00DBDDBC..0x00DBDDFC in the
// Zero Hour objectSoundAmbient* order (Enabled, the event name, Customized,
// Looping, MinVolume, Volume, MinRange, MaxRange, Priority), looks the name up
// through TheAudio's slot 75 (+0x12C), copies the found info into a 0xD0-byte
// Rva004333C0 (ctor 0x00433762) and applies each override through the setters
// 0x00433434..0x004334AF. With no customized info it falls back to the
// drawable's (0x0027682F) or template's (0x00239435, index 0x25) ambient slot.
//
// Donor: GeneralsMD Object.cpp / Drawable.cpp ambient customization, by way of
// Open-BFME-1's banked parseAmbientAudioProperties_000B6030 (control flow).
// The key and setter names are carried from that donor; retail proves only the
// order and the call targets. BFME 2 adds the +0xB0 != 5 guard before the
// overrides, which the donor lacks.

#include <windows.h>

#include "ascii_string.h"

#include "../../../Include/Common/Dict.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class StaticNameKey
{
public:
	NameKeyType key() const;
};

extern const StaticNameKey TheKey_objectSoundAmbient;			// retail 0x00DBDDBC
extern const StaticNameKey TheKey_objectSoundAmbientCustomized;	// retail 0x00DBDDC4
extern const StaticNameKey TheKey_objectSoundAmbientEnabled;		// retail 0x00DBDDCC
extern const StaticNameKey TheKey_objectSoundAmbientLooping;		// retail 0x00DBDDD4
extern const StaticNameKey TheKey_objectSoundAmbientMinVolume;	// retail 0x00DBDDDC
extern const StaticNameKey TheKey_objectSoundAmbientVolume;		// retail 0x00DBDDE4
extern const StaticNameKey TheKey_objectSoundAmbientMinRange;		// retail 0x00DBDDEC
extern const StaticNameKey TheKey_objectSoundAmbientMaxRange;		// retail 0x00DBDDF4
extern const StaticNameKey TheKey_objectSoundAmbientPriority;		// retail 0x00DBDDFC

#include "../../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"
class Rva001DA2D5;

struct OpaqueRefElement4
{
	OpaqueRefElement4() { referent = 0; }
	~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);
	Rva001DA2D5 *get() const { return (Rva001DA2D5 *)referent; }

	OpaqueRefCounted *referent;
};

// isPermanentSound-like query (0x001D9781); the caller stores al.
#include "../../../../GameEngineDevice/Include/Rva001D98BD.h"

// Override setters on the dynamic info; each ORs its bit into +0xC4.
class Rva00433434 { public: void rva00433434(bool value); };
class Rva0043346A { public: void rva0043346A(float value); };
class Rva00433453 { public: void rva00433453(float value); };
class Rva00433481 { public: void rva00433481(float value); };
class Rva00433498 { public: void rva00433498(float value); };
enum AudioPriority { AUDIOPRIORITY_LOWEST };
class Rva004334AF { public: void rva004334AF(AudioPriority value); };

// The shared audio event info; +0xB0 is the field compared against 5.
class Rva001DA2D5 : public OpaqueRefCounted
{
public:
	bool isPermanentSound() { return ((Rva001D98BD *)this)->rva001D9781(); }

	char m_pad08[0xB0 - 0x08];														// +0x08, after the vptr and count
	int m_b0;															// +0xB0
};

// The 0xD0-byte dynamic copy that carries the overrides.
class Rva004333C0 : public Rva001DA2D5
{
public:
	Rva004333C0(const Rva001DA2D5 &info, int extra);

	void overrideLoopFlag(bool value) { ((Rva00433434 *)this)->rva00433434(value); }
	void overrideMinVolume(float value) { ((Rva0043346A *)this)->rva0043346A(value); }
	void overrideVolume(float value) { ((Rva00433453 *)this)->rva00433453(value); }
	void overrideMinRange(float value) { ((Rva00433481 *)this)->rva00433481(value); }
	void overrideMaxRange(float value) { ((Rva00433498 *)this)->rva00433498(value); }
	void overridePriority(int value) { ((Rva004334AF *)this)->rva004334AF((AudioPriority)value); }

	char m_padB4[0xD0 - 0xB4];
};

// The caller's custom-info reference.
class Rva000A8C9B
{
public:
	void clear();
	void rva000A8CE5(OpaqueRefCounted *info);

	Rva004333C0 *m_ptr;
};

typedef OpaqueRefElement4 AudioEventInfoRef;
inline __declspec(noinline) OpaqueRefElement4 &OpaqueRefElement4::operator=(const OpaqueRefElement4 &other)
{
	if (this != &other) {
		if (other.referent)
			other.referent->Add_Ref();
		if (referent)
			referent->Release_Ref();
		referent = other.referent;
	}
	return *this;
}

// 8-byte template audio slot, returned by value; the info reference is at +4.
class Rva002390CB
{
public:
	int m_00;
	OpaqueRefElement4 m_info;											// +0x04
};

#include "../../../Include/Common/Rva00239435.h"

#include "../../../Include/GameClient/Drawable.h"

class ThingTemplate;

class AudioManager
{
public:
	virtual void vf00(); virtual void vf01(); virtual void vf02(); virtual void vf03(); virtual void vf04();
	virtual void vf05(); virtual void vf06(); virtual void vf07(); virtual void vf08(); virtual void vf09();
	virtual void vf10(); virtual void vf11(); virtual void vf12(); virtual void vf13(); virtual void vf14();
	virtual void vf15(); virtual void vf16(); virtual void vf17(); virtual void vf18(); virtual void vf19();
	virtual void vf20(); virtual void vf21(); virtual void vf22(); virtual void vf23(); virtual void vf24();
	virtual void vf25(); virtual void vf26(); virtual void vf27(); virtual void vf28(); virtual void vf29();
	virtual void vf30(); virtual void vf31(); virtual void vf32(); virtual void vf33(); virtual void vf34();
	virtual void vf35(); virtual void vf36(); virtual void vf37(); virtual void vf38(); virtual void vf39();
	virtual void vf40(); virtual void vf41(); virtual void vf42(); virtual void vf43(); virtual void vf44();
	virtual void vf45(); virtual void vf46(); virtual void vf47(); virtual void vf48(); virtual void vf49();
	virtual void vf50(); virtual void vf51(); virtual void vf52(); virtual void vf53(); virtual void vf54();
	virtual void vf55(); virtual void vf56(); virtual void vf57(); virtual void vf58(); virtual void vf59();
	virtual void vf60(); virtual void vf61(); virtual void vf62(); virtual void vf63(); virtual void vf64();
	virtual void vf65(); virtual void vf66(); virtual void vf67(); virtual void vf68(); virtual void vf69();
	virtual void vf70(); virtual void vf71(); virtual void vf72(); virtual void vf73(); virtual void vf74();
	virtual AudioEventInfoRef findAudioEventInfo(const AsciiString &eventName);	// slot 75 (+0x12C)
};
extern AudioManager *TheAudio;

// WorldBuilder TranslateAudioProperties, WB VA 0x00ED7010 (callgraph lead, score 5.0).
void TranslateAudioProperties(Dict *properties, Drawable *drawable, ThingTemplate *thingTemplate, bool *forceOff,
	Rva000A8C9B *customInfo, bool *soundEnabled)
{
	*forceOff = false;
	customInfo->clear();
	*soundEnabled = false;

	if (!TheAudio)
		return;
	if (!properties)
		return;

	bool soundEnabledExists;
	*soundEnabled = properties->getBool(TheKey_objectSoundAmbientEnabled.key(), &soundEnabledExists);

	bool propertyExists;
	AsciiString ambientSoundName = properties->getAsciiString(TheKey_objectSoundAmbient.key(), &propertyExists);
	if (propertyExists)
	{
		if (ambientSoundName.isEmpty())
		{
			*forceOff = true;
			*soundEnabled = false;
			return;
		}

		AudioEventInfoRef eventInfoRef = TheAudio->findAudioEventInfo(ambientSoundName);
		if (eventInfoRef.referent)
			customInfo->rva000A8CE5(new Rva004333C0(*eventInfoRef.get(), 0));
	}

	if (!*forceOff)
	{
		bool valBool = properties->getBool(TheKey_objectSoundAmbientCustomized.key(), &propertyExists);
		if (propertyExists && valBool)
		{
			if (!customInfo->m_ptr)
			{
				AudioEventInfoRef base;
				if (!drawable && !thingTemplate)
					return;
				if (drawable)
					base = drawable->rva0027682F().m_info;
				else
					base = ((Rva00239435 *)thingTemplate)->rva00239435(0x25).m_info;
				Rva001DA2D5 *baseEventInfo = base.get();
				if (baseEventInfo)
					customInfo->rva000A8CE5(new Rva004333C0(*baseEventInfo, 0));
			}

			if (customInfo->m_ptr && customInfo->m_ptr->m_b0 != 5)
			{
				valBool = properties->getBool(TheKey_objectSoundAmbientLooping.key(), &propertyExists);
				if (propertyExists)
					customInfo->m_ptr->overrideLoopFlag(valBool);

				float realProperty = properties->getReal(TheKey_objectSoundAmbientMinVolume.key(), &propertyExists);
				if (propertyExists)
					customInfo->m_ptr->overrideMinVolume(realProperty);

				realProperty = properties->getReal(TheKey_objectSoundAmbientVolume.key(), &propertyExists);
				if (propertyExists)
					customInfo->m_ptr->overrideVolume(realProperty);

				realProperty = properties->getReal(TheKey_objectSoundAmbientMinRange.key(), &propertyExists);
				if (propertyExists)
					customInfo->m_ptr->overrideMinRange(realProperty);

				realProperty = properties->getReal(TheKey_objectSoundAmbientMaxRange.key(), &propertyExists);
				if (propertyExists)
					customInfo->m_ptr->overrideMaxRange(realProperty);

				int priority = properties->getInt(TheKey_objectSoundAmbientPriority.key(), &propertyExists);
				if (propertyExists)
					customInfo->m_ptr->overridePriority(priority);
			}
		}
	}

	if (!soundEnabledExists)
	{
		if (customInfo->m_ptr)
		{
			*soundEnabled = customInfo->m_ptr->isPermanentSound();
		}
		else
		{
			AudioEventInfoRef base;
			if (drawable || thingTemplate)
			{
				if (drawable)
					base = drawable->rva0027682F().m_info;
				else
					base = ((Rva00239435 *)thingTemplate)->rva00239435(0x25).m_info;
			}
			if (base.referent)
				*soundEnabled = base.get()->isPermanentSound();
			else
				*soundEnabled = true;
		}
	}

	// layout lever: dead throw after the sibling blocks restores cl's slot merge
	// in this EH function (retail frame); emits no code.
	if (0)
		throw 1;
}
