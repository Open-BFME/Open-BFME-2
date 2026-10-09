// ?updateSubObjects@W3DModelDraw@@UAEXXZ
// partial score=0.87 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
//
// ?updateSubObjects@W3DModelDraw@@UAEXXZ, retail 0x000BAF7B (1116 bytes):
// slot 29 of the draw-interface vftable (this = W3DModelDraw+0x0C) shared by
// 0x007CBBEC, 0x007CBF6C and 0x007CC5FC.  Identity lead: Zero Hour
// W3DModelDraw::updateSubObjects (walk the hide/show sub-object list, look
// each name up with Get_Sub_Object_By_Name, report "*** ASSET ERROR:
// SubObject %s not found (%s)!" with the drawable template's name).  BFME2
// keeps two lists (+0x68 immediate, +0x74 fading), clears the +0x1C8/+0x1C9
// flags first, lets a name end in a '*' wildcard (prefix compared with
// _strnicmp against each sub-object name and against the part after its
// first '.'), and throttles the not-found report with the +0xC4 counter.
// Each match goes to the rowed per-sub-object workers 0x000B3885 / 0x000B38F9
// (W3DModelDrawBoneVisibility.cpp).  WorldBuilder twin 0x00941F70 (string
// lead) shows the same branches and both report strings.  Debug report
// shape follows W3DTruckDrawUpdateBones.cpp.
#include <string.h>
#include <vector>
#include "ascii_string.h"

typedef int Int;

class RenderObjClass
{
public:
	virtual void Delete_This();
	virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14();
	virtual const char *Get_Name() const;
	virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual int Get_Num_Sub_Objects() const;
	virtual void slot74();
	virtual RenderObjClass *Get_Sub_Object(int index) const;
	virtual void slot7C();
	virtual RenderObjClass *Get_Sub_Object_By_Name(const char *name, int *index) const;

	void Release_Ref()
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}

	int NumRefs;
};

class Debug
{
public:
	class Format
	{
	public:
		Format(const char *format, ...);
	private:
		char m_text[0x200];
	};
};

class SubObjectReport
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual SubObjectReport *setText(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void show(int mode);
	SubObjectReport &operator<<(const Debug::Format &value) { setText((const char *)&value); return *this; }
};

class SubObjectDebug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void beginReport();
	virtual void slot64(); virtual void slot68();
	virtual SubObjectReport *getReport(int, int, int);
};

extern Debug *theDebug;
#define TheSubObjectDebug (*(SubObjectDebug **)&theDebug)
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

static __forceinline void reportSubObject(const char *format, const char *name, const char *templateName)
{
	SubObjectReport *out = TheSubObjectDebug->getReport(0, 0, 0);
	(*out << Debug::Format(format, name, templateName)).show(2);
}

#define SUBOBJECT_CRASH(format, a, b) do { \
	if (bfmeRva000387C0()) { \
		_bfme_debugRecordCallsite(1); \
		TheSubObjectDebug->beginReport(); \
		reportSubObject(format, a, b); \
	} \
} while (0)

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
private:
	char m_pad00[0x64];
	AsciiString m_name;	// +0x64
};

class Drawable
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
private:
	char m_pad00[4];
	const ThingTemplate *m_template;	// +0x04
};

// Hide/show entry (0x18 bytes); the per-entry workers are rowed under the
// address-named W3DModelDraw view Rva000B3885.
struct Rva000B3885HideShowInfo
{
	AsciiString m_name;	// +0x00
	bool m_hide;	// +0x04
	float m_fadeRate;	// +0x08
	float m_alpha;	// +0x0C
	float m_delayStep;	// +0x10
	float m_delay;	// +0x14
};

class Rva000B3885
{
public:
	void rva000B3885(Rva000B3885HideShowInfo *info, RenderObjClass *subObject, Int subObjectIndex);
	void rva000B38F9(Rva000B3885HideShowInfo *info, RenderObjClass *subObject, Int subObjectIndex);
};

typedef std::vector<Rva000B3885HideShowInfo> HideShowVec;

class Rva000BAF7BDrawModule
{
public:
	virtual void slot00();
protected:
	const void *m_moduleData;	// +0x04
	Drawable *m_drawable;	// +0x08
};

template <int N> class Rva000BAF7BSlots : public Rva000BAF7BSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class Rva000BAF7BSlots<0>
{
};

class ObjectDrawInterface : public Rva000BAF7BSlots<29>
{
public:
	virtual void updateSubObjects() = 0;	// slot 29
};

class W3DModelDraw : public Rva000BAF7BDrawModule, public ObjectDrawInterface
{
public:
	virtual void updateSubObjects();

private:
	const Drawable *getDrawable() const { return m_drawable; }

	char m_pad10[0x50 - 0x10];
	RenderObjClass *m_renderObject;	// +0x50
	char m_pad54[0x68 - 0x54];
	HideShowVec m_subObjectVec;	// +0x68
	HideShowVec m_fadeSubObjectVec;	// +0x74
	char m_pad80[0xC4 - 0x80];
	Int m_missingSubObjectReports;	// +0xC4
	char m_padC8[0x1C8 - 0xC8];
	bool m_bfme1C8;	// +0x1C8
	bool m_bfme1C9;	// +0x1C9
};

void W3DModelDraw::updateSubObjects()
{
	m_bfme1C8 = false;
	m_bfme1C9 = false;
	if (!m_renderObject)
		return;

	if (!m_subObjectVec.empty())
	{
		for (HideShowVec::iterator it = m_subObjectVec.begin(); it != m_subObjectVec.end(); ++it)
		{
			Int objIndex;
			const char *wildcard = it->m_name.find('*');
			if (wildcard)
			{
				Int len = wildcard - it->m_name.str();
				if (len < 1)
					SUBOBJECT_CRASH("*** ASSET ERROR: SubObject wildcard string %s must not have wildcard at beginning (%s)!\n",
						it->m_name.str(), getDrawable()->getTemplate()->getName().str());
				Int count = m_renderObject->Get_Num_Sub_Objects();
				for (objIndex = 0; objIndex < count; ++objIndex)
				{
					RenderObjClass *subObj = m_renderObject->Get_Sub_Object(objIndex);
					const char *subName = subObj->Get_Name();
					if (_strnicmp(it->m_name.str(), subName, len) == 0)
					{
						((Rva000B3885 *)this)->rva000B3885(it, subObj, objIndex);
					}
					else
					{
						const char *dot = strchr(subName, '.');
						if (dot && _strnicmp(it->m_name.str(), dot + 1, len) == 0)
							((Rva000B3885 *)this)->rva000B3885(it, subObj, objIndex);
					}
					subObj->Release_Ref();
				}
			}
			else
			{
				RenderObjClass *subObj = m_renderObject->Get_Sub_Object_By_Name(it->m_name.str(), &objIndex);
				if (subObj)
				{
					((Rva000B3885 *)this)->rva000B3885(it, subObj, objIndex);
					subObj->Release_Ref();
				}
				else if (m_missingSubObjectReports > 0)
				{
					--m_missingSubObjectReports;
					SUBOBJECT_CRASH("*** ASSET ERROR: SubObject %s not found (%s)!\n",
						it->m_name.str(), getDrawable()->getTemplate()->getName().str());
				}
			}
		}
	}

	if (!m_fadeSubObjectVec.empty())
	{
		for (HideShowVec::iterator it = m_fadeSubObjectVec.begin(); it != m_fadeSubObjectVec.end(); ++it)
		{
			Int objIndex;
			const char *wildcard = it->m_name.find('*');
			if (wildcard)
			{
				Int len = wildcard - it->m_name.str();
				if (len < 1)
					SUBOBJECT_CRASH("*** ASSET ERROR: SubObject wildcard string %s must not have wildcard at beginning (%s)!\n",
						it->m_name.str(), getDrawable()->getTemplate()->getName().str());
				Int count = m_renderObject->Get_Num_Sub_Objects();
				for (objIndex = 0; objIndex < count; ++objIndex)
				{
					RenderObjClass *subObj = m_renderObject->Get_Sub_Object(objIndex);
					const char *subName = subObj->Get_Name();
					if (_strnicmp(it->m_name.str(), subName, len) == 0)
					{
						((Rva000B3885 *)this)->rva000B38F9(it, subObj, objIndex);
					}
					else
					{
						const char *dot = strchr(subName, '.');
						if (dot && _strnicmp(it->m_name.str(), dot + 1, len) == 0)
							((Rva000B3885 *)this)->rva000B38F9(it, subObj, objIndex);
					}
					subObj->Release_Ref();
				}
			}
			else
			{
				RenderObjClass *subObj = m_renderObject->Get_Sub_Object_By_Name(it->m_name.str(), &objIndex);
				if (subObj)
				{
					((Rva000B3885 *)this)->rva000B38F9(it, subObj, objIndex);
					subObj->Release_Ref();
				}
			}
		}
	}
}
