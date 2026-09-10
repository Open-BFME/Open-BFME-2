// cl: /O2 /DNDEBUG /MD
//
// SegmentedLineClass::Render_Seg_Line, retail 0x0015EED0, 78 bytes.
// Dedicated TU. BFME2 adds one RenderObj vtable slot versus the BFME1 thunk
// and shortens the gap before PointLocations by four bytes.

class RenderInfoClass
{
};

class Matrix3D
{
	float Values[12];
};

class Vector3
{
};

class Vector4
{
};

class SphereClass
{
	float Values[4];
};

class SegLineRendererClass
{
public:
	void Render(RenderInfoClass &, const Matrix3D &, unsigned int, Vector3 *,
		const SphereClass &, Vector4 * = 0);
};

template <class Type>
class SimpleDynVecClass
{
public:
	virtual ~SimpleDynVecClass();

	Type *Vector;
	int VectorMax;
	int ActiveCount;
};

class SegmentedLineClass
{
public:
	virtual void reserved_0();
	virtual void reserved_1();
	virtual void reserved_2();
	virtual void reserved_3();
	virtual void reserved_4();
	virtual void reserved_5();
	virtual void reserved_6();
	virtual void reserved_7();
	virtual void reserved_8();
	virtual void reserved_9();
	virtual void reserved_10();
	virtual void reserved_11();
	virtual void reserved_12();
	virtual void reserved_13();
	virtual void reserved_14();
	virtual void reserved_15();
	virtual void reserved_16();
	virtual void reserved_17();
	virtual void reserved_18();
	virtual void reserved_19();
	virtual void reserved_20();
	virtual void reserved_21();
	virtual void reserved_22();
	virtual void reserved_23();
	virtual void reserved_24();
	virtual void reserved_25();
	virtual void reserved_26();
	virtual void reserved_27();
	virtual void reserved_28();
	virtual void reserved_29();
	virtual void reserved_30();
	virtual void reserved_31();
	virtual void reserved_32();
	virtual void reserved_33();
	virtual void reserved_34();
	virtual void reserved_35();
	virtual void reserved_36();
	virtual void reserved_37();
	virtual void reserved_38();
	virtual void reserved_39();
	virtual void reserved_40();
	virtual void reserved_41();
	virtual void reserved_42();
	virtual void reserved_43();
	virtual void reserved_44();
	virtual void reserved_45();
	virtual void reserved_46();
	virtual void reserved_47();
	virtual void reserved_48();
	virtual void reserved_49();
	virtual void reserved_50();
	virtual void reserved_51();
	virtual void reserved_52();
	virtual void reserved_53();
	virtual void reserved_54();
	virtual void reserved_55();
	virtual void reserved_56();
	virtual void reserved_57();
	virtual void reserved_58();
	virtual void reserved_59();
	virtual void reserved_60();
	virtual void reserved_61();
	virtual void reserved_62();
	virtual void reserved_63();
	virtual void reserved_64();
	virtual void reserved_65();
	virtual void reserved_66();
	virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &);

private:
	unsigned char Prefix[0x14];
	Matrix3D Transform;
	unsigned char BeforePointLocations[0x84];
	SimpleDynVecClass<Vector3> PointLocations;
	SegLineRendererClass LineRenderer;

protected:
	void Render_Seg_Line(RenderInfoClass &rinfo);
};

void SegmentedLineClass::Render_Seg_Line(RenderInfoClass &rinfo)
{
	if (PointLocations.ActiveCount < 2)
		return;

	SphereClass boundingSphere;
	Get_Obj_Space_Bounding_Sphere(boundingSphere);

	LineRenderer.Render(
		rinfo,
		Transform,
		PointLocations.ActiveCount,
		PointLocations.Vector,
		boundingSphere);
}
