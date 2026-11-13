// cl: /EHsc
// ??0Rva0055F197@@QAE@ABVRvaSmartPtr12@@H@Z, retail 0x0055F197, 129 bytes.

#include "../../Include/Common/RvaSmartPtr12.h"

class DefaultModuleSecondBase
{
public:
	virtual ~DefaultModuleSecondBase();
};

class DefaultModuleThirdBase
{
public:
	virtual ~DefaultModuleThirdBase();
};

#include "../../Include/GameClient/DefaultModuleHeadBase.h"

#include "../../Include/GameClient/Rva003AEEB3.h"

#include "../../Include/Common/Rva0055BF21.h"

namespace FXParticleSystem
{
class DefaultPhysicsModuleInfo
{
public:
	DefaultPhysicsModuleInfo();
	virtual ~DefaultPhysicsModuleInfo();
};
}

struct Block12
{
	int v0;
	int v1;
	int v2;
};

struct CopySource
{
	unsigned char pad[0x0c];
	int a0;
	int a1;
	int a2;
	int b;
	int c0;
	int c1;
	int c2;
	unsigned char d0;
	unsigned char d1;
};

class Rva0055F197 : public Rva0055BF21, public FXParticleSystem::DefaultPhysicsModuleInfo
{
public:
	Rva0055F197(const RvaSmartPtr12 &smart, int x);
	virtual ~Rva0055F197();
private:
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	unsigned char m_3c;
	unsigned char m_3d;
};

Rva0055F197::Rva0055F197(const RvaSmartPtr12 &smart, int x)
	: Rva0055BF21(smart, x), DefaultPhysicsModuleInfo()
{
	const CopySource *src = (const CopySource *)x;
	m_2c = src->b;
	*(Block12 *)((char *)this + 0x20) = *(const Block12 *)((const char *)src + 0x0c);
	*(Block12 *)((char *)this + 0x30) = *(const Block12 *)((const char *)src + 0x1c);
	m_3c = src->d0;
	m_3d = src->d1;
}
