// ?swapTextures@SubObjectsUpgrade@@QAE_NPAVDrawable@@H@Z
// Native 4B4F91 texture helper and4B5020 upgrade entry; fresh WB evidence.
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /GX /MD /DNDEBUG /arch:SSE /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB
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
	_STL::vector<AsciiString> m_excludeSubobjects;
	_STL::vector<Rva00B6CF1> m_textureSwaps;
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
	virtual void swapTextures(const _STL::vector<Rva00B6CF1> &models) = 0;
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
	void rva00272414(const _STL::vector<AsciiString> *arg);
};


class SubObjectsUpgrade : public UpgradeModule
{
public:
 bool swapTextures(Drawable*,int);
 bool rva004B4EC3(Drawable*,void*,float,float);
 bool rva004B4F11(Drawable*,void*,float,float);
protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();

private:
	unsigned char m_pad14[0x1C - 0x14];
	void *m_1C;
	unsigned char m_20;
};

// ?swapTextures@SubObjectsUpgrade@@QAE_NPAVDrawable@@H@Z
bool SubObjectsUpgrade::swapTextures(Drawable *drawable, int mode)
{
 const SubObjectsUpgradeModuleData *data=(const SubObjectsUpgradeModuleData*)m_moduleData;
 const _STL::vector<Rva00B6CF1> *textures=&data->m_textureSwaps;
 if (textures->empty()) return false;
 _STL::vector<Rva00B6CF1> empty;
 switch (mode) {
 case 0: break;
 case 1: textures=&empty;break;
 default: return false;
 }
 DrawModule **modules=drawable->getDrawModules();
 for (DrawModule **it=modules;*it;++it) {
  ObjectDrawInterface *objectDraw=(*it)->getObjectDrawInterface();
  if (objectDraw) objectDraw->swapTextures(*textures);
 }
 return true;
}

// ?upgradeImplementation@SubObjectsUpgrade@@MAEXXZ
void SubObjectsUpgrade::upgradeImplementation()
{
 SubObjectsUpgrade *base=this;
 if (reinterpret_cast<Rva004B4E56*>(base)->rva004B4E56()) {
  m_20=1;
  Drawable *drawable=getObject()->getDrawable();
  if (drawable) {
   const SubObjectsUpgradeModuleData *data=(const SubObjectsUpgradeModuleData*)m_moduleData;
   float first=0.0f;
   float second=0.0f;
   reinterpret_cast<Rva004B4DBF*>(base)->rva004B4DBF(&first,&second);
   bool changed=base->rva004B4F11(drawable,(void*)&data->m_hideSubObjects,first,second);
   bool showChanged=base->rva004B4EC3(drawable,(void*)&data->m_showSubObjects,first,second);
   changed=showChanged || changed;
   bool texturesChanged=base->swapTextures(drawable,0);
   if (changed) drawable->rva002723ED();
   if (texturesChanged && data->m_flag150) drawable->rva00272414(&data->m_excludeSubobjects);
  }
  base->rva004CE4A0();
 }
}

// Native4B5101..4B5209/264; same ctor/mux slot8 and WB123A2A0 remove effects.
// Primary base pointer lives only within the guarded block; retaining it through
// final reset reallocates this/drawable registers and loses9 bytes.
void SubObjectsUpgrade::upgradeRemovalImplementation()
{
 const SubObjectsUpgradeModuleData *data=(const SubObjectsUpgradeModuleData*)m_moduleData;
 Drawable *drawable=getObject()->getDrawable();
 float first=0.0f,second=0.0f;
 if(drawable && (data->m_flag152 || data->m_flag153)) {
  SubObjectsUpgrade *base=this;
  bool changed=false,texturesChanged=false;
  reinterpret_cast<Rva004B4DBF*>(base)->rva004B4DBF(&first,&second);
  if(data->m_flag152) {
   changed=base->rva004B4F11(drawable,(void*)&data->m_showSubObjects,first,second);
   texturesChanged=base->swapTextures(drawable,0);
  }
  if(data->m_flag153) {
   bool showChanged=base->rva004B4EC3(drawable,(void*)&data->m_hideSubObjects,first,second);
   changed=showChanged || changed;
  }
  if(changed) drawable->rva002723ED();
  if(texturesChanged && data->m_flag150) drawable->rva00272414(&data->m_excludeSubobjects);
 }
 rva004CE4A8();
}
