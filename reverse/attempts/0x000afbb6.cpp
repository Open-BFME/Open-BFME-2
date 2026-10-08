// ?rva000afbb6@Rva000AF01A@@QAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z
// partial score=0.9 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??0Rva000AEFAA@@QAE@PAXPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z @0x000AEFAA 104B
// Evidence: unlock lane, BlendTileData literal, vtable g_00BC95D8, base pin 0x000ABB87, caller 0x000AF238.
#include "ascii_string.h"

class BfmeParserRegistryVE
{
public:
	void *bfmeRegister(void *a, void *b, void *c, void *d);
};

class BfmeParserBindingBaseVE
{
public:
	BfmeParserBindingBaseVE(BfmeParserRegistryVE *registry, void *label, void *parentLabel);
	virtual ~BfmeParserBindingBaseVE();
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();
private:
	BfmeParserRegistryVE *m_registry;
	void *m_token;
};

class Rva000AEFAA : public BfmeParserBindingBaseVE
{
public:
	Rva000AEFAA(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
private:
	void *m_owner;
};

Rva000AEFAA::Rva000AEFAA(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("BlendTileData"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString)),
	m_owner(owner)
{
}

// ??0Rva000AEF42@@QAE@PAXPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z @0x000AEF42 104B
// Evidence: unlock lane, HeightMapData literal, vtable g_00BC95D0, base pin 0x000ABB87, caller 0x000AF238.
class Rva000AEF42 : public BfmeParserBindingBaseVE
{
public:
	Rva000AEF42(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
private:
	void *m_owner;
};

Rva000AEF42::Rva000AEF42(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("HeightMapData"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString)),
	m_owner(owner)
{
}

// ?rva000AF01A@Rva000AF01A@@QAE@PAXPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z @0x000AF01A 104B
// Address-derived binding identity; "NamedCameras" and the common parser base are target evidence.
class Rva0008A234;
class DataChunkInput;
struct DataChunkInfo;

class Rva000AF01A : public BfmeParserBindingBaseVE
{
public:
	Rva000AF01A(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
	bool rva000afbb6(DataChunkInput &file, DataChunkInfo *info);
private:
	Rva0008A234 **m_owner;
};

Rva000AF01A::Rva000AF01A(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("NamedCameras"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString)),
	m_owner(static_cast<Rva0008A234 **>(owner))
{
}

// ??0Rva000AF0E4@@QAE@PAVBfmeParserRegistryVE@@PBVAsciiString@@@Z @0x000AF0E4 98B
// PostEffectsChunk binding, 2-arg (registry, parentLabel), no owner member.
// Evidence: same base pin 0x000ABB87 and caller 0x000AF238 as siblings; literal "PostEffectsChunk"; vtable g_00BC9600; ret 8.
class Rva000AF0E4 : public BfmeParserBindingBaseVE
{
public:
	Rva000AF0E4(BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
};

Rva000AF0E4::Rva000AF0E4(BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("PostEffectsChunk"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString))
{
}

// ??0Rva000AF082@@QAE@PAVBfmeParserRegistryVE@@PBVAsciiString@@@Z @0x000AF082 98B
// GlobalLighting binding, 2-arg (registry, parentLabel), no owner member.
// Evidence: same base pin 0x000ABB87 and caller 0x000AF238 as siblings; literal "GlobalLighting"; vtable g_00BC95F8; ret 8.
class Rva000AF082 : public BfmeParserBindingBaseVE
{
public:
	Rva000AF082(BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
};

Rva000AF082::Rva000AF082(BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("GlobalLighting"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString))
{
}

// Native 0x000AFBB6..0x000AFD85 (463B), including catch cleanup at AFD48.
// The old 402B inventory stopped before that cleanup; the next EH prologue
// starts at AFD85. The NamedCameras binding above owns this callback.
// Record ABI comes from the existing rowed ctor at 0x0008A234: 48 bytes,
// next link +0, string +4, coordinate bits +8..10 and six floats +14..28.
// The constructor's ThreeInts spelling denotes coordinate bits; no new pin
// or original camera class name is inferred. Version 2 adds the last value.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class DataChunkInput {
public:
 int readInt();
 float readReal();
 AsciiString readAsciiString();
};
struct DataChunkInfo { char labels[8]; unsigned short version; };
struct ThreeInts { int v00,v04,v08; };
struct NamedCameraPosition { float x,y,z; };
class Rva0008A234 {
public:
 Rva0008A234(const StringBase<char>&, const ThreeInts*,
  float,float,float,float,float,float);
 Rva0008A234 *m_00;
 AsciiString m_04;
 int m_08,m_0C,m_10;
 float m_14,m_18,m_1C,m_20,m_24,m_28;
 unsigned char m_2C;
};
// ?rva000afbb6@Rva000AF01A@@QAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z present-unmatched
bool Rva000AF01A::rva000afbb6(DataChunkInput &file, DataChunkInfo *info)
{
 _ReadWriteBarrier();
 int count=file.readInt();
 try {
  while(count!=0) {
   --count;
   AsciiString name;
   NamedCameraPosition position;
   position.x=file.readReal();
   position.y=file.readReal();
   position.z=file.readReal();
   name=file.readAsciiString();
   float value2=file.readReal();
   float value3=info->version>=2 ? file.readReal() : 0.0f;
   float value1=file.readReal();
   float value4=file.readReal();
   float value5=file.readReal();
   float value0=file.readReal();
   Rva0008A234 *camera=new Rva0008A234(
    *reinterpret_cast<const StringBase<char> *>(&name),
    reinterpret_cast<const ThreeInts *>(&position),
    value0,value1,value2,value4,value5,value3);
   camera->m_00=*m_owner;
   *m_owner=camera;
  }
 } catch(...) {
  while(Rva0008A234 *camera=*m_owner) {
   *m_owner=camera->m_00;
   camera->m_04.clear();
   ::operator delete(camera);
  }
  throw;
 }
 return true;
}
