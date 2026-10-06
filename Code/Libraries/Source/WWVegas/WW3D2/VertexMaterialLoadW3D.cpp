// cl: /DNDEBUG /MD /GX-
//
// ?Load_W3D@VertexMaterialClass@@QAE_NAAVChunkLoadClass@@@Z,
// retail 0x0013E8B0 (274 bytes).
// BFME1 vertmaterial.cpp Load_W3D port with BFME2 rewrites (all
// retail-measured from the 0x0013E8B0 body):
// - bool (AL) returns, not WW3DErrorType; failures return false directly
//   with no buffer cleanup.
// - No EH frame (plain array-new is unchecked, unlike the EH-guarded
//   MeshModelReadVertexMaterials.cpp unit).
// - Name (StringClass) at this+0x1C assigned directly from the 256-byte
//   stack buffer when the name chunk was seen.
// - W3dVertexMaterialStruct is 0x20 bytes; mapper-arg buffers are plain
//   `new char[len]` / `delete[]`.
// Dedicated TU: vertmaterial.cpp carries the enum-typed ZH original.
// Parse callees resolve via harvested pins; new[]/delete[]/String-assign
// via matched rows.

#ifndef NULL
#define NULL 0
#endif

void *operator new[](unsigned int size);
void operator delete[](void *ptr);

class ChunkLoadClass
{
public:
	unsigned long Cur_Chunk_ID(void);
	unsigned long Cur_Chunk_Length(void);
	bool Open_Chunk(void);
	bool Close_Chunk(void);
	unsigned long Read(void *dst, unsigned long size);
};

struct W3dVertexMaterialStruct
{
	char data[0x20];
};

class StringClass
{
public:
	const StringClass &operator=(const char *text);
};

class VertexMaterialClass
{
public:
	virtual ~VertexMaterialClass();
	bool Load_W3D(ChunkLoadClass &cload);
	void Parse_W3dVertexMaterialStruct(const W3dVertexMaterialStruct &vmat);
	void Parse_Mapping_Args(const W3dVertexMaterialStruct &vmat, char *mapping0, char *mapping1);

private:
	int RefCount;
	char m_pad[0x1C - 8];

public:
	StringClass Name;
};

enum
{
	W3D_CHUNK_VERTEX_MATERIAL_NAME = 0x2C,
	W3D_CHUNK_VERTEX_MATERIAL_INFO = 0x2D,
	W3D_CHUNK_VERTEX_MAPPER_ARGS0 = 0x2E,
	W3D_CHUNK_VERTEX_MAPPER_ARGS1 = 0x2F
};

// ?Load_W3D@VertexMaterialClass@@QAE_NAAVChunkLoadClass@@@Z
bool VertexMaterialClass::Load_W3D(ChunkLoadClass &cload)
{
	char name[256];

	W3dVertexMaterialStruct vmat;
	bool hasname = false;

	char *mapping0_arg_buffer = NULL;
	char *mapping1_arg_buffer = NULL;
	unsigned int mapping0_arg_len = 0U;
	unsigned int mapping1_arg_len = 0U;

	while (cload.Open_Chunk()) {
		switch (cload.Cur_Chunk_ID()) {
		case W3D_CHUNK_VERTEX_MATERIAL_NAME:
			cload.Read(&name, cload.Cur_Chunk_Length());
			hasname = true;
			break;
		case W3D_CHUNK_VERTEX_MATERIAL_INFO:
			if (cload.Read(&vmat, sizeof(vmat)) != sizeof(vmat)) {
				return false;
			}
			break;
		case W3D_CHUNK_VERTEX_MAPPER_ARGS0:
			mapping0_arg_len = cload.Cur_Chunk_Length();
			mapping0_arg_buffer = (char*)::operator new[](mapping0_arg_len);
			if (cload.Read(mapping0_arg_buffer, mapping0_arg_len) != mapping0_arg_len) {
				return false;
			}
			break;
		case W3D_CHUNK_VERTEX_MAPPER_ARGS1:
			mapping1_arg_len = cload.Cur_Chunk_Length();
			mapping1_arg_buffer = (char*)::operator new[](mapping1_arg_len);
			if (cload.Read(mapping1_arg_buffer, mapping1_arg_len) != mapping1_arg_len) {
				return false;
			}
			break;
		}
		cload.Close_Chunk();
	}

	if (hasname) {
		Name = name;
	}

	Parse_W3dVertexMaterialStruct(vmat);
	Parse_Mapping_Args(vmat, mapping0_arg_buffer, mapping1_arg_buffer);

	::operator delete[](mapping0_arg_buffer);
	::operator delete[](mapping1_arg_buffer);

	return true;
}
