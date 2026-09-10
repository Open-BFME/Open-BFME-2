// ?Add@?$SimpleDynVecClass@VVector3@@@@QAE_NABVVector3@@H@Z
// partial score=0.88 date=2026-09-10
// cl: /O1 /DNDEBUG /MD
//
// SimpleDynVecClass<Vector3>::Add, retail 0x001002C5, 65 bytes. Dedicated TU
// so segline.cpp cannot inline this into Add_Point.

class Vector3
{
public:
	float X, Y, Z;
};

template <class T>
class SimpleDynVecClass
{
	int unused;
	T *Vector;
	int VectorMax;
	int ActiveCount;

public:
	bool Resize(int extra);
	bool Add(const T &object, int extra);
};

template <class T>
bool SimpleDynVecClass<T>::Add(const T &object, int extra)
{
	SimpleDynVecClass *self = this;
	if (self->ActiveCount >= self->VectorMax)
	{
		if (!self->Resize(extra))
			return true;
	}
	int n = self->ActiveCount;
	T *slot = (T *)((char *)self->Vector + n * 12);
	self->ActiveCount = n + 1;
	slot->X = object.X;
	slot->Y = object.Y;
	slot->Z = object.Z;
	return true;
}

template class SimpleDynVecClass<Vector3>;
