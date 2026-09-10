// cl: /G7 /DNDEBUG /MD /EHsc
//
// ShareBufferClass<Vector2> copy constructor at 0x0015CD00.
//
// BFME's ShareBufferClass carries an Alignment member beside Zero Hour's Count:
// zero means a plain new[] with Array aliasing RawBuffer, anything else means a
// raw char buffer over-allocated by Alignment with Array rounded up inside it.
// Open-BFME-1 recovered the same constructor for Vector3; this is its Vector2
// instantiation, whose element copy moves the two floats as dwords.  /G7 is
// the unit's tell: it writes add reg,1 and add reg,-1 where /G6 writes inc and
// dec.

void *operator new[](unsigned int size);
inline void *operator new(unsigned int, void *place) { return place; }

class Vector2
{
public:
	Vector2();
	Vector2 &operator=(const Vector2 &that)
	{
		X = that.X;
		Y = that.Y;
		return *this;
	}

private:
	float X;
	float Y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}
	RefCountClass(const RefCountClass &) : NumRefs(1) {}
	virtual void Delete_This();

protected:
	virtual ~RefCountClass() {}

private:
	int NumRefs;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/sharebuf.h,
// with BFME's RawBuffer/Alignment pair around Zero Hour's Array and Count.
template <class Type>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(const ShareBufferClass &);

protected:
	Type *RawBuffer;
	Type *Array;
	int Count;
	int Alignment;
};

template <class Type>
ShareBufferClass<Type>::ShareBufferClass(const ShareBufferClass<Type> &that) :
	Count(that.Count)
{
	Alignment = that.Alignment;
	if (Alignment == 0) {
		RawBuffer = new Type[Count];
		Array = RawBuffer;
	} else {
		RawBuffer = (Type *)new char[Count * sizeof(Type) + Alignment];
		Array = (Type *)(((unsigned int)RawBuffer + Alignment - 1) &
			~(unsigned int)(Alignment - 1));
	}
	for (int index = 0; index < Count; ++index) {
		Array[index] = that.Array[index];
	}
}

template ShareBufferClass<Vector2>::ShareBufferClass(
	const ShareBufferClass<Vector2> &);
