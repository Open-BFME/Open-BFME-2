// cl: /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// HTreeClass::Init_Default at 0x001666D0.
//
// Zero Hour's default one-pivot tree, on BFME 2's 0x58-byte PivotClass: free
// whatever the tree held (the out-of-line Free at 0x00166510), allocate a
// single pivot through the array allocator and construct it, make both of its
// transform blocks identity, set it visible, reset its trailing float to 1.0
// and name it "RootTransform".  BFME also clears the tree's own name.
//
// Each transform block is an identity rotation (0,0,0,1) followed by a zero
// translation; retail's stray `add eax,0x14` / `add eax,0x30` are the `this`
// adjustments of the Make_Identity it inlined on each block, which is why the
// blocks are modelled as one struct with that member.  htree.cpp's shim keeps
// Zero Hour's pivot layout, so this unit carries a reduced model of its own.

extern "C" char *strcpy(char *destination, const char *source);
#pragma intrinsic(strcpy)

// Without this declaration MSVC routes `new T[n]` to the scalar ??2@YAPAXI@Z;
// retail allocates the pivot through the array form ??_U@YAPAXI@Z.
void *__cdecl operator new[](unsigned int size);

// One of the pivot's two transform blocks.
struct BfmePivotTransform
{
	void Make_Identity()
	{
		RotX = 0.0f; RotY = 0.0f; RotZ = 0.0f; RotW = 1.0f;
		PosX = 0.0f; PosY = 0.0f; PosZ = 0.0f;
	}
	float RotX, RotY, RotZ, RotW;
	float PosX, PosY, PosZ;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/htree.h
struct PivotClass
{
public:
	PivotClass();

	char Name[16];
	PivotClass *Parent;					// +0x10
	BfmePivotTransform BaseTransform;	// +0x14
	BfmePivotTransform Transform;		// +0x30
	int Index;							// +0x4C
	bool IsVisible;						// +0x50
	float m_bfme54;						// +0x54
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/htree.h
class HTreeClass
{
public:
	void Init_Default(void);
	void Free(void);

private:
	char Name[16];
	int NumPivots;						// +0x10
	PivotClass *Pivot;					// +0x14
	float ScaleFactor;					// +0x18
};

void HTreeClass::Init_Default(void)
{
	Free();

	NumPivots = 1;
	Pivot = new PivotClass[NumPivots];

	Pivot[0].Index = 0;
	Pivot[0].Parent = 0;
	Pivot[0].BaseTransform.Make_Identity();
	Pivot[0].Transform.Make_Identity();
	Pivot[0].IsVisible = true;
	Pivot[0].m_bfme54 = 1.0f;
	strcpy(Pivot[0].Name,"RootTransform");

	Name[0] = 0;
}
