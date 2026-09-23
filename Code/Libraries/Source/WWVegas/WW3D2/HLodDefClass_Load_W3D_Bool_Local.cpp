// cl: /G7 /DNDEBUG /MD /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Include
// Donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/HLodDefClass_Load_W3D_Bool_Local.cpp
// BFME's HLodDefClass::Load_W3D returns bool in the retail ABI.  Keep this
// ABI view local: the shared ZH header still declares the method as
// WW3DErrorType, which gives a different decorated name and return shape.

#include "winbase_shim.h"
#include "chunkio.h"
#include "w3d_file.h"

// Donor HLodDef layout, corroborated by the target Free and Save methods.
// Target chunks 0x702, 0x705 and 0x706 select LODs, aggregates and proxies.
class HLodDefClass
{
private:
	class SubObjectArrayClass
	{
	public:
		bool Load_W3D(ChunkLoadClass &cload);

		float MaxScreenSize;
		int ModelCount;
		char **ModelName;
		int *BoneIndex;
	};

public:
	bool Load_W3D(ChunkLoadClass &cload);

private:
	char *Name;
	char *HierarchyTreeName;
	int LodCount;
	SubObjectArrayClass *Lod;
	SubObjectArrayClass Aggregates;
	void *ProxyArray;

	void Free(void);
	bool read_header(ChunkLoadClass &cload);
	bool read_proxy_array(ChunkLoadClass &cload);

};

bool HLodDefClass::Load_W3D(ChunkLoadClass &cload)
{
	Free();

	if (read_header(cload) == FALSE) {
		return false;
	}

	for (int iLOD = 0; iLOD < LodCount; iLOD++) {
		if (!cload.Open_Chunk()) return false;

		if (cload.Cur_Chunk_ID() != W3D_CHUNK_HLOD_LOD_ARRAY) {
			return false;
		}

		Lod[iLOD].Load_W3D(cload);
		cload.Close_Chunk();
	}

	while (cload.Open_Chunk()) {
		switch(cload.Cur_Chunk_ID())
		{
			case W3D_CHUNK_HLOD_AGGREGATE_ARRAY:
				Aggregates.Load_W3D(cload);
				break;
			case W3D_CHUNK_HLOD_PROXY_ARRAY:
				read_proxy_array(cload);
				break;
		}
		cload.Close_Chunk();
	}

	return true;
}
