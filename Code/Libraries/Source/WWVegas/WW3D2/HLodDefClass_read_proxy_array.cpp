// cl: /G7 /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Include
#define Matrix4x4 Matrix4

// Donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/HLodDefClass_read_proxy_array.cpp
// Nothrow delete declarations preserve the target exception-state handling.
void __cdecl operator delete[](void *) throw();
void __cdecl operator delete(void *) throw();
#include "hlod.h"
#include "chunkio.h"

class ProxyRecordClass
{
public:
	ProxyRecordClass() : BoneIndex(0) { memset(Name, 0, sizeof(Name)); }
	bool operator==(const ProxyRecordClass &) { return false; }
	bool operator!=(const ProxyRecordClass &that) { return !(*this == that); }
	void Init(const W3dHLodSubObjectStruct &data)
	{
		BoneIndex = data.BoneIndex;
		strncpy(Name, data.Name, sizeof(Name));
	}
protected:
	int BoneIndex;
	char Name[2 * W3D_NAME_LEN];
};

class ProxyArrayClass : public VectorClass<ProxyRecordClass>, public RefCountClass
{
public:
	ProxyArrayClass(int size) : VectorClass<ProxyRecordClass>(size) {}
};

// Target Load_W3D dispatches chunk 0x706 here; record names and bone indices
// retain the donor representation.
bool HLodDefClass::read_proxy_array(ChunkLoadClass &cload)
{
	REF_PTR_RELEASE(ProxyArray);

	if (!cload.Open_Chunk())
		return false;
	if (cload.Cur_Chunk_ID() != W3D_CHUNK_HLOD_SUB_OBJECT_ARRAY_HEADER)
		return false;

	W3dHLodArrayHeaderStruct header;
	if (cload.Read(&header, sizeof(header)) != sizeof(header))
		return false;
	if (!cload.Close_Chunk())
		return false;

	ProxyArray = NEW_REF(ProxyArrayClass, (header.ModelCount));

	for (int imodel = 0; imodel < ProxyArray->Length(); ++imodel) {
		if (!cload.Open_Chunk())
			return false;
		if (cload.Cur_Chunk_ID() != W3D_CHUNK_HLOD_SUB_OBJECT)
			return false;

		W3dHLodSubObjectStruct subobjdef;
		if (cload.Read(&subobjdef, sizeof(subobjdef)) != sizeof(subobjdef))
			return false;
		if (!cload.Close_Chunk())
			return false;

		(*ProxyArray)[imodel].Init(subobjdef);
	}
	return true;
}
