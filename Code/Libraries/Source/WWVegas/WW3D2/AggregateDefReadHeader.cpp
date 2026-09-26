// cl: /DNDEBUG /MD /EHsc /G7
//
// ?Read_Header@AggregateDefClass@@MAE_NAAVChunkLoadClass@@@Z, retail 0x001A3400,
// 95 bytes. Dedicated TU: BFME2 keeps the aggregate Read family as plain
// success flags (retail returns mov al,1 / mov al,bl), while the Zero Hour
// reference header declares WW3DErrorType. Declared locally with bool returns
// in BFME1 virtual order so slot 3 (+0xC) reproduces the retail virtual call;
// byte-identical to the BFME1 donor at open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/agg_def.cpp.
// Vtable 0x007D6C70 slot 3; members mirror ZH layout: version +4, name +0x58.

extern "C" char * __cdecl strdup(const char *);

class ChunkLoadClass
{
public:
	unsigned long Read(void *buffer, unsigned long size);
};

struct W3dAggregateHeaderStruct
{
	unsigned Version;
	char Name[16];
};

class RenderObjClass;
class ChunkSaveClass;
struct W3dAggregateSubobjectStruct;
template <class T> class DynamicVectorClass;

class AggregateDefClass
{
public:
	virtual ~AggregateDefClass();
	virtual int Load_W3D(ChunkLoadClass &chunk_load);
	virtual bool Save_W3D(ChunkSaveClass &chunk_save);
protected:
	virtual bool Read_Header(ChunkLoadClass &chunk_load);
	virtual int Read_Info(ChunkLoadClass &chunk_load);
	virtual bool Read_Subobject(ChunkLoadClass &chunk_load);
	virtual int Read_Class_Info(ChunkLoadClass &chunk_load);
	virtual bool Save_Header(ChunkSaveClass &chunk_save);
	virtual bool Save_Info(ChunkSaveClass &chunk_save);
	virtual bool Save_Subobject(ChunkSaveClass &chunk_save, void *subobject);
	virtual bool Save_Class_Info(ChunkSaveClass &chunk_save);
	virtual void Attach_Subobjects(RenderObjClass &base_model);
	virtual RenderObjClass *Find_Subobject(RenderObjClass &model, const void *mesh_path, const void *bone_path);
	virtual void Free_Subobject_List(void);
	virtual void Add_Subobject(const W3dAggregateSubobjectStruct &subobj_info);
	virtual bool Is_Object_In_List(const char *passet_name, DynamicVectorClass<RenderObjClass *> &node_list);
	virtual void Build_Subobject_List(RenderObjClass &original_model, RenderObjClass &model);

private:
	int m_version; // +4
	unsigned char m_subobjectList[0x18]; // +8
	char m_infoBaseModelName[32]; // +0x20
	int m_infoSubobjectCount; // +0x40
	unsigned m_miscOriginalClassID; // +0x44
	unsigned m_miscFlags; // +0x48
	unsigned char m_miscReserved[12]; // +0x4C
	char *m_pName; // +0x58
};

bool AggregateDefClass::Read_Header(ChunkLoadClass &chunk_load)
{
	// BFME keeps the byte-sized success result in a callee-saved register.
	bool ret_val = false;

	// Is this the header chunk?
	W3dAggregateHeaderStruct header = { 0 };
	if (chunk_load.Read(&header, sizeof(header)) == sizeof(header)) {

		// Copy the name from the header structure
		m_pName = ::strdup(header.Name);
		m_version = header.Version;

		// Success!
		ret_val = true;
	}

	return ret_val;
}
