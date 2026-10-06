// cl: /MD
//
// SimpleDynVecClass<unsigned>::Add. Twin of the landed Vector3 body
// with a four-byte element.

template <class Type>
class SimpleDynVecClass
{
public:
	virtual ~SimpleDynVecClass();
	bool Add(const Type &object, int new_size_hint);
	bool Grow(int new_size_hint);

	Type *Vector;
	int VectorMax;
	int ActiveCount;
};

struct BfmePod4 { char m_data[4]; };
template <> class SimpleDynVecClass<BfmePod4>
{
protected:
	bool Grow(int new_size_hint);
	friend bool SimpleDynVecClass<unsigned>::Add(const unsigned &object, int new_size_hint);
};

template <class Type>
bool SimpleDynVecClass<Type>::Add(const Type &object, int new_size_hint)
{
	if (ActiveCount >= VectorMax) {
		if (!((SimpleDynVecClass<BfmePod4> *)(void *)this)->Grow(new_size_hint))
			return false;
	}
	int n = ActiveCount;
	ActiveCount = n + 1;
	n *= sizeof(Type);
	Type *slot = (Type *)((char *)Vector + n);
	*slot = object;
	return true;
}

template bool SimpleDynVecClass<unsigned>::Add(const unsigned &, int);
