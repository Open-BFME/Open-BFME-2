// cl: /O2 /G7 /MD
//
// LineGroupClass::Set_Arrays, retail 0x001B3790, 268 bytes.
// Dedicated TU. Dword REF_PTR_SET; vslot 0 is a no-arg Destroy not a
// deleting destructor.

class Vector3 {};
class Vector4 {};

template <class T>
class ShareBufferClass
{
public:
	virtual void Destroy();
	int Refs;
	int Pad8;
	int PadC;
	int Count;
};

class LineGroupClass
{
public:
	virtual ~LineGroupClass();
	void Set_Arrays(
		ShareBufferClass<Vector3> *startlocs,
		ShareBufferClass<Vector3> *endlocs,
		ShareBufferClass<Vector4> *diffuse,
		ShareBufferClass<Vector4> *taildiffuse,
		ShareBufferClass<unsigned> *alt,
		ShareBufferClass<float> *sizes,
		ShareBufferClass<float> *ucoords,
		int active_line_count);

private:
	ShareBufferClass<Vector3> *StartLineLoc;
	ShareBufferClass<Vector3> *EndLineLoc;
	ShareBufferClass<Vector4> *LineDiffuse;
	ShareBufferClass<Vector4> *TailDiffuse;
	ShareBufferClass<unsigned> *ALT;
	ShareBufferClass<float> *LineSize;
	ShareBufferClass<float> *LineUCoord;
	int LineCount;
};

void LineGroupClass::Set_Arrays(
	ShareBufferClass<Vector3> *startlocs,
	ShareBufferClass<Vector3> *endlocs,
	ShareBufferClass<Vector4> *diffuse,
	ShareBufferClass<Vector4> *taildiffuse,
	ShareBufferClass<unsigned> *alt,
	ShareBufferClass<float> *sizes,
	ShareBufferClass<float> *ucoords,
	int active_line_count)
{
	if (startlocs)
		startlocs->Refs++;
	if (ShareBufferClass<Vector3> *p = StartLineLoc) {
		if (!(p->Refs += -1))
			p->Destroy();
	}
	StartLineLoc = startlocs;

	if (endlocs)
		endlocs->Refs++;
	if (ShareBufferClass<Vector3> *p = EndLineLoc) {
		if (!(p->Refs += -1))
			p->Destroy();
	}
	EndLineLoc = endlocs;

	if (diffuse)
		diffuse->Refs++;
	if (ShareBufferClass<Vector4> *p = LineDiffuse) {
		if (!(p->Refs += -1))
			p->Destroy();
	}
	LineDiffuse = diffuse;

	if (taildiffuse)
		taildiffuse->Refs++;
	if (ShareBufferClass<Vector4> *p = TailDiffuse) {
		if (!(p->Refs += -1))
			p->Destroy();
	}
	TailDiffuse = taildiffuse;

	if (alt)
		alt->Refs++;
	if (ShareBufferClass<unsigned> *p = ALT) {
		if (!(p->Refs += -1))
			p->Destroy();
	}
	ALT = alt;

	if (sizes)
		sizes->Refs++;
	if (ShareBufferClass<float> *p = LineSize) {
		if (!(p->Refs += -1))
			p->Destroy();
	}
	LineSize = sizes;

	if (ucoords)
		ucoords->Refs++;
	if (ShareBufferClass<float> *p = LineUCoord) {
		if (!(p->Refs += -1))
			p->Destroy();
	}
	LineUCoord = ucoords;

	if (ALT)
		LineCount = active_line_count;
	else
		LineCount = (active_line_count >= 0) ? active_line_count : StartLineLoc->Count;
}
