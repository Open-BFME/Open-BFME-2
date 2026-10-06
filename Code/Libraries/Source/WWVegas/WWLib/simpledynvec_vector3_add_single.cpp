// cl: /MD
//
// ?rva00100354@?$SimpleDynVecClass@VVector3@@@@QAE_NABVVector3@@@Z, retail 0x00100354, 14 bytes.
// Forwards to 2-arg Add with hint 0: push 0; push arg; call Add; ret 4.
// Evidence: ecx passes through to ?Add@?$SimpleDynVecClass@VVector3@@@@QAE_NABVVector3@@H@Z (row 0x001002C5);
// callers at 0x0007FBD3 and 0x00100426/0x00100535 pass SimpleDynVecClass<Vector3>* in ecx and Vector3* on stack.

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

template <class Type>
class SimpleDynVecClass
{
public:
	virtual ~SimpleDynVecClass();
	bool Add(const Type &object, int new_size_hint);
	bool rva00100354(const Type &object);

	Type *Vector;
	int VectorMax;
	int ActiveCount;
};

bool SimpleDynVecClass<Vector3>::rva00100354(const Vector3 &object)
{
	return Add(object, 0);
}
