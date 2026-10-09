// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva004AF25D@RespawnUpdate@@QAEPAXXZ, retail 0x004AF25D, 50 bytes.
// Lazy RespawnUpdate getter: cached void at +0x28 (init -1 per ctor
// 0x004AF096) else lookup ModuleData string at +0x11C through global
// 0x00DFF000 via rowed 0x002D06CA else Object+4 fallback. Caller at
// 0x0029111F finds RespawnUpdate module then adds 0x64 for AsciiString.
#include "ascii_string.h"

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern class ThingFactory *TheThingFactory;

struct RespawnUpdateModuleDataRef
{
	char m_pad[0x118];
	AsciiString m_deadImageName;
	AsciiString m_str11C;
};

class Image;
class ThingTemplate
{
public:
	unsigned char m_unknown[0x11F];
	unsigned char m_kindOfByte;
};
class Object
{
public:
	__forceinline ThingTemplate *getTemplate() const { return m_template; }
	unsigned char m_unknown00[4];
	ThingTemplate *m_template;
	unsigned char m_unknown08[0x74 - 8];
	int m_heroKey;
};
class CreateAHeroHero;
class CreateAHeroManager
{
public:
	void *rva002197A6(int);
	const AsciiString &GetButtonImageName(const CreateAHeroHero *);
};
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &);
};
extern CreateAHeroManager *TheCreateAHeroManager;
extern ImageCollection *TheMappedImageCollection;
const Image *getButtonImage(ThingTemplate *, Object *);

struct RespawnUpdateObjectRef
{
	char m_pad[4];
	void *m_unk04;
};

class RespawnUpdate
{
public:
	// Primary table 8556B0, installed by the verified constructor4AF096.
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual const Image *getDeadImage();
	void *rva004AF25D();

private:
	RespawnUpdateModuleDataRef *m_moduleData;
	RespawnUpdateObjectRef *m_object;
	unsigned char m_pad0C[0x24 - 0x0C];
	const Image *m_deadImage;
	void *m_cached;
};

// WorldBuilder RespawnUpdate::getDeadImage, source lines 851/868. Retail
// 4AF2DE..4AF3BD tests cached image +24, module-data string +118,
// template KindOf byte +11F bit40 and the object's hero key +74.
// Callees and both singleton globals retain their existing verified names.
const Image *RespawnUpdate::getDeadImage()
{
	if (m_deadImage)
		return m_deadImage;
	RespawnUpdateModuleDataRef *data = m_moduleData;
	Object *object = reinterpret_cast<Object *>(m_object);
	const AsciiString &name = data->m_deadImageName;
	if (!name.isEmpty()) {
		if (object->getTemplate()->m_kindOfByte & 0x40) {
			CreateAHeroHero *hero = static_cast<CreateAHeroHero *>(
				TheCreateAHeroManager->rva002197A6(object->m_heroKey));
			if (hero) {
				m_deadImage = TheMappedImageCollection->findImageByName(
					TheCreateAHeroManager->GetButtonImageName(hero));
				if (!m_deadImage)
					m_deadImage = TheMappedImageCollection->findImageByName(
						AsciiString("BuildingNoArt"));
			}
		} else {
			m_deadImage = TheMappedImageCollection->findImageByName(name);
		}
		if (m_deadImage)
			return m_deadImage;
		Object *current = reinterpret_cast<Object *>(m_object);
		ThingTemplate *currentTemplate = current->getTemplate();
		m_deadImage = getButtonImage(currentTemplate, current);
	} else {
		m_deadImage = getButtonImage(object->getTemplate(), object);
	}
	return m_deadImage;
}

void *RespawnUpdate::rva004AF25D()
{
	if (m_cached == (void *)-1) {
		void *found = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&m_moduleData->m_str11C);
		m_cached = found;
		if (found == 0)
			m_cached = m_object->m_unk04;
	}
	return m_cached;
}
