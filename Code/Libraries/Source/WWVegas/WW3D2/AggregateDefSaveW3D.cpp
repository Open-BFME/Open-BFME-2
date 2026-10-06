// cl: /DNDEBUG /MD /EHsc
//
// ?Save_W3D@AggregateDefClass@@UAE_NAAVChunkSaveClass@@@Z, retail 0x001A35A0,
// 83 bytes. Dedicated TU: BFME2 keeps the aggregate Save family as plain
// success flags (retail checks cmp al,1 and returns mov al,bl), while the
// Zero Hour reference header declares WW3DErrorType. Declared locally with
// bool returns in BFME1 virtual order so the Save_Header/Info/Class_Info
// slots (+0x1C/+0x20/+0x28) reproduce the retail calls; byte-identical to the
// BFME1 donor at 0x00980590.

class ChunkLoadClass;
class ChunkSaveClass;
struct W3dAggregateSubobjectStruct;
struct RenderObjClassPlaceholder;
template <class T> class DynamicVectorPlaceholder;

class ChunkSaveClass
{
public:
	bool Begin_Chunk(unsigned long chunk_type);
	bool End_Chunk();
};

class AggregateDefClass
{
public:
	virtual ~AggregateDefClass();
	virtual int Load_W3D(ChunkLoadClass &chunk_load);
	virtual bool Save_W3D(ChunkSaveClass &chunk_save);
	virtual bool Read_Header(ChunkLoadClass &chunk_load);
	virtual int Read_Info(ChunkLoadClass &chunk_load);
	virtual bool Read_Subobject(ChunkLoadClass &chunk_load);
	virtual int Read_Class_Info(ChunkLoadClass &chunk_load);
	virtual bool Save_Header(ChunkSaveClass &chunk_save);
	virtual bool Save_Info(ChunkSaveClass &chunk_save);
	virtual bool Save_Subobject(ChunkSaveClass &chunk_save, void *subobject);
	virtual bool Save_Class_Info(ChunkSaveClass &chunk_save);
};

// ?Save_W3D@AggregateDefClass@@UAE_NAAVChunkSaveClass@@@Z
bool AggregateDefClass::Save_W3D(ChunkSaveClass &chunk_save)
{
	bool ret_val = false;

	if (chunk_save.Begin_Chunk(0x600) == true) {
		if (Save_Header(chunk_save) == true) {
			if (Save_Info(chunk_save) == true) {
				bool class_ok = Save_Class_Info(chunk_save);
				if (class_ok == true) {
					ret_val = class_ok;
				}
			}
		}
		chunk_save.End_Chunk();
	}

	return ret_val;
}
