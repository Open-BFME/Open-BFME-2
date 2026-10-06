// cl: /DNDEBUG /MD /GX-
//
// ?read_texcoords@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x001896D0 (167 bytes).
// BFME1 meshmdlio.cpp read_texcoords port (their 170B Open-BFME5 clean C++ row
// d_0096e330, object-symbol IAE_N bool). BFME2 adaptations (all retail-measured
// from the 0x1896D0 body):
// - VertexCount at this+0x28 (loop bound, signed compare).
// - DefMatDesc at this+0x8C (Install_UV_Array this).
// - MeshLoadContext CurPass/CurTexStage at +0x8C/+0x90.
// - TempUVArray (SimpleVecClass<Vector2>) at +0x23C: retail inlines
//   Get_Temporary_UV_Array as a virtual Uninitialised_Grow call (slot 2, +8)
//   on the member plus a direct read of its Vector word at +0x240.
// - Install_UV_Array resolves to the new pin at 0x15B960 (BFME1 mangling,
//   3 mesh-reader callers); Cur_Chunk_Length/Read resolve to matched rows.
// Dedicated TU: marker-less meshmdlio.cpp cannot take rows (PostProcess precedent).

#ifndef NULL
#define NULL 0
#endif

class Vector2
{
public:
	float X;
	float Y;
	void __forceinline Set(float x, float y) { X = x; Y = y; }
};

struct W3dTexCoordStruct
{
	float U;
	float V;
};

template <class T> class SimpleVecClass
{
public:
	virtual ~SimpleVecClass();
	virtual bool Resize(int newsize);
	virtual bool Uninitialised_Grow(int newsize);
	T & operator[](int index) { return Vector[index]; }

protected:
	T *Vector;
	int VectorMax;
};

class ChunkLoadClass
{
public:
	unsigned long Cur_Chunk_Length();
	unsigned long Read(void *dst, unsigned long size);
};

class MeshMatDescClass
{
public:
	void Install_UV_Array(int pass, int stage, Vector2 *uvs, int count);
	bool Has_UV(int pass, int stage) { return UVSource[pass][stage] != -1; }

private:
	char m_pad0[0x30];
	int UVSource[4][2];
	char m_pad1[0x118 - 0x50];
};

typedef char MeshMatDescSizeCheck[sizeof(MeshMatDescClass) == 0x118 ? 1 : -1];

class MeshLoadContextClass
{
public:
	Vector2 *__forceinline Get_Temporary_UV_Array(int elementcount)
	{
		TempUVArray.Uninitialised_Grow(elementcount);
		return &TempUVArray[0];
	}

private:
	virtual ~MeshLoadContextClass();
	char m_pad0[0x8C - 4];
public:
	int CurPass;
	int CurTexStage;
	char m_padA[0x124 - 0x94];
	MeshMatDescClass AlternateMatDesc;
public:
	SimpleVecClass<Vector2> TempUVArray;
};

class MeshModelClass
{
protected:
	virtual ~MeshModelClass();
	bool read_texcoords(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_stage_texcoords(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_Rva00189B50(ChunkLoadClass &cload, MeshLoadContextClass *context);

private:
	char m_pad0[0x28 - 4];
	int VertexCount;
	char m_pad1[0x8C - 0x2C];
	MeshMatDescClass *DefMatDesc;
};

// ?read_texcoords@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_texcoords(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	W3dTexCoordStruct texcoord;
	Vector2 *uvarray = 0;
	int elementcount = cload.Cur_Chunk_Length() / sizeof(W3dTexCoordStruct);

	context->TempUVArray.Uninitialised_Grow(elementcount);
	uvarray = &context->TempUVArray[0];

	if (uvarray != NULL) {
		for (int i = 0; i < VertexCount; i++) {
			if (cload.Read(&texcoord, sizeof(W3dTexCoordStruct)) != sizeof(W3dTexCoordStruct)) {
				return false;
			}
			uvarray[i].Set(texcoord.U, 1.0f - texcoord.V);
		}

		DefMatDesc->Install_UV_Array(context->CurPass, context->CurTexStage, uvarray, elementcount);
	}

	return true;
}

// ?read_stage_texcoords@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_stage_texcoords(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	unsigned elementcount;
	Vector2 *uvs;
	MeshMatDescClass *matdesc = DefMatDesc;

	if (DefMatDesc->Has_UV(context->CurPass, context->CurTexStage)) {
		matdesc = &context->AlternateMatDesc;
	}

	elementcount = cload.Cur_Chunk_Length() / sizeof(W3dTexCoordStruct);

	context->TempUVArray.Uninitialised_Grow(elementcount);
	uvs = &context->TempUVArray[0];

	if (uvs != NULL) {
		unsigned totalbytes = elementcount * sizeof(W3dTexCoordStruct);
		if (cload.Read(uvs, totalbytes) < totalbytes) {
			return false;
		}

		unsigned total = elementcount;
		unsigned done = 0;
		if ((int)total >= 4) {
			unsigned iters = (total - 4) / 4 + 1;
			float *yf = &uvs[1].Y;
			done = iters * 4;
			do {
				yf[-2] = 1.0f - yf[-2];
				yf[0] = 1.0f - yf[0];
				yf[2] = 1.0f - yf[2];
				yf[4] = 1.0f - yf[4];
				yf += 8;
			} while (--iters != 0);
		}
		if (done < total) {
			float *yf = &uvs[done].Y;
			unsigned left = total - done;
			do {
				*yf = 1.0f - *yf;
				yf += 2;
			} while (--left != 0);
		}
	}

	matdesc->Install_UV_Array(context->CurPass, context->CurTexStage, uvs, elementcount);
	return true;
}

// ?read_Rva00189B50@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
// Retail 0x00189B50 (260 bytes: ret C2 08 00 at 0x189C51): bulk UV reader with
// stage -1, no Has_UV select, DefMatDesc direct. Same V-flip skeleton as
// read_stage_texcoords. Called solely from read_material_pass (single E8 caller
// at 0x18B485) for W3D_CHUNK_STAGE_TEXCOORDS (0x4A) directly under MATERIAL_PASS
// (pass-level dispatch table at 0x18B4D4; SCG 0x3E ignored there, TEXTURE_STAGE
// 0x48 goes to read_texture_stage). Dispatcher evidence via co-lane E8 scan.
bool MeshModelClass::read_Rva00189B50(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	unsigned elementcount;
	Vector2 *uvs;
	MeshMatDescClass *matdesc = DefMatDesc;

	elementcount = cload.Cur_Chunk_Length() / sizeof(W3dTexCoordStruct);

	context->TempUVArray.Uninitialised_Grow(elementcount);
	uvs = &context->TempUVArray[0];

	if (uvs != NULL) {
		unsigned totalbytes = elementcount * sizeof(W3dTexCoordStruct);
		if (cload.Read(uvs, totalbytes) < totalbytes) {
			return false;
		}

		unsigned total = elementcount;
		unsigned done = 0;
		if ((int)total >= 4) {
			unsigned iters = (total - 4) / 4 + 1;
			float *yf = &uvs[1].Y;
			done = iters * 4;
			do {
				yf[-2] = 1.0f - yf[-2];
				yf[0] = 1.0f - yf[0];
				yf[2] = 1.0f - yf[2];
				yf[4] = 1.0f - yf[4];
				yf += 8;
			} while (--iters != 0);
		}
		if (done < total) {
			float *yf = &uvs[done].Y;
			unsigned left = total - done;
			do {
				*yf = 1.0f - *yf;
				yf += 2;
			} while (--left != 0);
		}
	}

	matdesc->Install_UV_Array(context->CurPass, -1, uvs, elementcount);
	return true;
}
