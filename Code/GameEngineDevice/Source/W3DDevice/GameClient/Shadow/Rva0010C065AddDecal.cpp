// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /GX- /MD
// ?rva0010C065@W3DProjectedShadowManager@@UAEPAVW3DProjectedShadow@@PAURva0010C065Info@@@Z,
// retail 0x0010C065..0x0010C145 (224B): a Ghidra-unlisted table slot of the
// projected-shadow manager (Zero Hour's W3DProjectedShadowManager::addDecal
// role). It looks up the info's texture by name through the pinned
// 0x0010BC90 and builds the decal through the rowed factory 0x0010BB11
// (whose signature names every argument): type 0x1000 entries go on the +0x1C
// list with a second texture taken from the info's second name and the last
// flag set; all others go on the +0x08 list. Fields are named by offset.
#include "ascii_string.h"

class W3DShadowTexture;
class RenderObjClass;
class W3DProjectedShadow;
class Shadow
{
public:
	struct ShadowTypeInfo;
	void setOpacity(int value);
	virtual void vslot00(void);
	virtual void vslot04(void);
	virtual void release(void);
	char m_pad04[0x30];
	unsigned int m_type; // +0x34
	unsigned int m_value38; // +0x38
	unsigned int m_value3C; // +0x3C
	unsigned int m_value40; // +0x40
	unsigned int m_value44; // +0x44
	unsigned int m_value48; // +0x48
	unsigned int m_value4C; // +0x4C
	unsigned int m_value50; // +0x50
	unsigned int m_value54; // +0x54
};

class HAnimManagerClass;
#include "../../../../../GameEngine/Include/Common/Rva0010BC90ShadowManager.h"

#include "../../../../Include/W3DDevice/GameClient/Rva0010BB11ShadowFactory.h"

struct Rva0010C065Info
{
	AsciiString m_textureName;								// +0x00
	AsciiString m_secondTextureName;						// +0x04
	int m_type;												// +0x08
	float m_sizeX;											// +0x0C
	float m_sizeY;											// +0x10
	char m_pad14[0x20 - 0x14];
	float m_value;											// +0x20
	char m_pad24[2];
	unsigned char m_flag;									// +0x26
};

class W3DProjectedShadowManager
{
public:
 virtual ~W3DProjectedShadowManager();
 virtual void rva0010BE72();
 virtual W3DProjectedShadow *rva0010C065(Rva0010C065Info *);
 virtual W3DProjectedShadow *rva0010C145(RenderObjClass *,Shadow::ShadowTypeInfo *,bool,bool);
 virtual void forward(unsigned,unsigned,unsigned);
 virtual unsigned forwardIf(unsigned,void *,unsigned,unsigned);
 virtual W3DProjectedShadow *rva0010C2D5(int,RenderObjClass *,Shadow::ShadowTypeInfo *,Shadow::ShadowTypeInfo *);
private:
	Rva0010BC90ShadowManager *textures() { return (Rva0010BC90ShadowManager *)this; }
	Rva0010BB11ShadowFactory *factory() { return (Rva0010BB11ShadowFactory *)this; }
	int m_04;
	char m_list08[0x1C - 0x08];								// +0x08
	char m_list1C[4];										// +0x1C
};

W3DProjectedShadow *W3DProjectedShadowManager::rva0010C065(Rva0010C065Info *info)
{
	if (info == 0)
		return 0;
	if (info->m_type == 0x1000)
	{
		const char *secondName = info->m_secondTextureName.str();
		const char *name = info->m_textureName.str();
		return factory()->create(textures()->getTexture(name), 0, info->m_type, info->m_flag,
			info->m_sizeX, info->m_sizeY, info->m_value, 0.0f, 0.0f, m_list1C, 0,
			(int)textures()->getTexture(secondName), 1);
	}
	return factory()->create(textures()->getTexture(info->m_textureName.str()), 0, info->m_type, info->m_flag,
		info->m_sizeX, info->m_sizeY, info->m_value, 0.0f, 0.0f, m_list08, 0, 0, 0);
}
