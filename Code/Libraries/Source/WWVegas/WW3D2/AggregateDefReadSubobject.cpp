// cl: /DNDEBUG /MD /EHsc
//
// ?Read_Subobject@AggregateDefClass@@MAE_NAAVChunkLoadClass@@@Z, retail 0x001A34D0,
// 139 bytes. Dedicated TU: BFME2 keeps the aggregate Read family as plain
// success flags (retail returns mov al,1 / mov al,bl), while the Zero Hour
// reference header declares WW3DErrorType. Declared locally with bool returns
// in BFME1 virtual order so the Add_Subobject slot (+0x38) reproduces the
// retail virtual call; byte-identical to the BFME1 donor at 0x009804C0.

class ChunkLoadClass
{
public:
	unsigned long Read(void *buffer, unsigned long size);
};

struct W3dAggregateSubobjectStruct
{
	char SubobjectName[32];
	char BoneName[32];
};

class RenderObjClass;
class ChunkSaveClass;
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
};

// ?Read_Subobject@AggregateDefClass@@MAE_NAAVChunkLoadClass@@@Z
bool AggregateDefClass::Read_Subobject(ChunkLoadClass &chunk_load)
{
	// BFME returns a byte-sized success result.
	bool ret_val = false;

	// Read the subobject information from the file
	W3dAggregateSubobjectStruct subobj_info = { 0 };
	if (chunk_load.Read(&subobj_info, sizeof(subobj_info)) == sizeof(subobj_info)) {

		// Add this subobject to our list
		Add_Subobject(subobj_info);

		// Success!
		ret_val = true;
	}

	return ret_val;
}
