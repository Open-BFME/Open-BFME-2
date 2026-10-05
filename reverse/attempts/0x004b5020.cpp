// ?upgradeImplementation@SubObjectsUpgrade@@MAEXXZ
// partial score=0.45 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /Oy- /GX /MD /DNDEBUG /arch:SSE /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB
// stlport
//
// The matched SubObjectsUpgrade ctor at 0x004B4D63 installs UpgradeMux vtable
// 0x00C57BF8 at +0x10. Its slots 10 and 8 point to 0x004B5020 and 0x004B5101.
// The target parse table at 0x00C57D38 and ModuleData ctor/dtor establish the
// four vectors at +0x118/+0x124/+0x130/+0x13C and the trailing fields. The
// BFME1 SubObjectsUpgrade donor at 0x002D8D90 supports the show/hide and
// replacement-model semantics; target offsets and callees below come from
// BFME2 bytes. The helper at 0x004B4F91 keeps an address-derived method name.

#include <vector>
#include "ascii_string.h"

class Drawable;
class DrawModule;
class ObjectDrawInterface;
class Object;
class ModuleData;

struct Rva00B6CF1
{
	~Rva00B6CF1();
	AsciiString m_source;
	AsciiString m_replacement;
};

class SubObjectsUpgradeModuleData
{
public:
	unsigned char m_pad[0x118];
	_STL::vector<AsciiString> m_showSubObjects;
	_STL::vector<AsciiString> m_hideSubObjects;
	_STL::vector<AsciiString> m_upgradeTexture;
	_STL::vector<Rva00B6CF1> m_replacementModels;
	float m_fadeTime;
	float m_waitBeforeFade;
	unsigned char m_flag150;
	unsigned char m_flag151;
	unsigned char m_flag152;
	unsigned char m_flag153;
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object : public Thing
{
};

class ObjectModuleBase
{
public:
	virtual ~ObjectModuleBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
	Object *getObject() const { return m_object; }
};

class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();
};

template <int N> class SubObjectsUpgradeMuxSlots : public SubObjectsUpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <> class SubObjectsUpgradeMuxSlots<0>
{
};

class UpgradeMuxIface : public SubObjectsUpgradeMuxSlots<8>
{
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(bool executed) = 0;
	virtual void upgradeImplementation() = 0;
};

class UpgradeModule : public ObjectModuleBase,
	public UpgradeModuleInterface,
	public UpgradeMuxIface
{
public:
	void rva004CE4A0();
	void rva004CE4A8();
	bool rva004B4F91(Drawable *drawable, int mode);
};

class Rva004B4E56
{
public:
	virtual void slot00();
	unsigned char rva004B4E56();
};

class Rva004B4DBF
{
public:
	void rva004B4DBF(float *first, float *second);
};

class Rva002B224BDwordField
{
public:
	int get() const;
};

template <int N> class SubObjectsDrawSlots : public SubObjectsDrawSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <> class SubObjectsDrawSlots<0>
{
};

class ObjectDrawInterface : public SubObjectsDrawSlots<33>
{
public:
	virtual void applyReplacementModels(const _STL::vector<Rva00B6CF1> &models) = 0;
};

template <int N> class DrawModuleSlots : public DrawModuleSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <> class DrawModuleSlots<0>
{
};

class DrawModule : public DrawModuleSlots<42>
{
public:
	virtual ObjectDrawInterface *getObjectDrawInterface() = 0;
};

class Drawable
{
public:
	DrawModule **getDrawModules();
	void rva002723ED();
	void rva00272414(int arg);
};

bool __stdcall Rva004B4EC3(Drawable *drawable, void *range, float first, float second);
bool __stdcall Rva004B4F11(Drawable *drawable, void *range, float first, float second);

class SubObjectsUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();

private:
	unsigned char m_pad14[0x1C - 0x14];
	void *m_1C;
	unsigned char m_20;
};

// ?rva004B4F91@UpgradeModule@@QAE_NPAVDrawable@@H@Z present-unmatched
bool UpgradeModule::rva004B4F91(Drawable *drawable, int mode)
{
	const SubObjectsUpgradeModuleData *data =
		(const SubObjectsUpgradeModuleData *)m_moduleData;
	const _STL::vector<Rva00B6CF1> *models = &data->m_replacementModels;
	if (models->begin() == models->end())
		return false;

	bool changed = false;
	_STL::vector<Rva00B6CF1> empty;
	if (mode == 0 || mode == 1)
		models = &empty;

	DrawModule **modules = drawable->getDrawModules();
	for (DrawModule **it = modules; *it; ++it) {
		ObjectDrawInterface *objectDraw = (*it)->getObjectDrawInterface();
		if (objectDraw) {
			objectDraw->applyReplacementModels(*models);
			changed = true;
		}
	}
	return changed;
}

// ?upgradeImplementation@SubObjectsUpgrade@@MAEXXZ present-unmatched
void SubObjectsUpgrade::upgradeImplementation()
{
	UpgradeModule *base = (UpgradeModule *)((char *)this - 0x10);
	if (((Rva004B4E56 *)base)->rva004B4E56()) {
		m_20 = 1;
		Drawable *drawable = getObject()->getDrawable();
		if (drawable) {
			const SubObjectsUpgradeModuleData *data =
				(const SubObjectsUpgradeModuleData *)m_moduleData;
			float first = 0.0f;
			float second = 0.0f;
			((Rva004B4DBF *)base)->rva004B4DBF(&first, &second);
			bool changed = Rva004B4F11(drawable, (void *)&data->m_hideSubObjects, first, second);
			if (Rva004B4EC3(drawable, (void *)&data->m_showSubObjects, first, second))
				changed = true;
			bool replacementModelsChanged = base->rva004B4F91(drawable, 0);
			if (changed)
				drawable->rva002723ED();
			if (replacementModelsChanged && data->m_flag150)
				drawable->rva00272414((int)&data->m_upgradeTexture);
		}
	}
	rva004CE4A0();
}

// ?upgradeRemovalImplementation@SubObjectsUpgrade@@MAEXXZ present-unmatched
void SubObjectsUpgrade::upgradeRemovalImplementation()
{
	SubObjectsUpgrade *self = this;
	UpgradeModule *base = (UpgradeModule *)((char *)this - 0x10);
	const SubObjectsUpgradeModuleData *data =
		(const SubObjectsUpgradeModuleData *)m_moduleData;
	Drawable *drawable = self->getObject()->getDrawable();
	float first = 0.0f;
	float second = 0.0f;
	if (drawable && (data->m_flag152 || data->m_flag153)) {
		bool changed = false;
		bool replacementModelsChanged = false;
		if (data->m_flag152) {
			changed = Rva004B4F11(drawable, (void *)&data->m_showSubObjects, first, second);
			replacementModelsChanged = base->rva004B4F91(drawable, 0);
		}
		if (data->m_flag153 &&
			Rva004B4EC3(drawable, (void *)&data->m_hideSubObjects, first, second))
			changed = true;
		if (changed)
			drawable->rva002723ED();
		if (replacementModelsChanged && data->m_flag150)
			drawable->rva00272414((int)&data->m_upgradeTexture);
	}
	self->rva004CE4A8();
}
