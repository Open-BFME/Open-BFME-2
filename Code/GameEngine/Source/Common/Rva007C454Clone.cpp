// cl: /DNDEBUG /MD /EHsc
//
// ?Clone@Rva007C454@@UBEPAVRenderObjClass@@XZ @0x0007C4C6 58B: the clone
// slot of the CameraClass-derived Rva007C454: return new Rva007C454(*this).
// Evidence: slot 2 of the primary vtable 0x00BC6C58 (slot 1 the rowed
// ??_GRva007C454 0x0007C5B9, slot 3 CameraClass::Class_ID, the WW3D
// RenderObjClass order Clone/Class_ID); operator new 0x0002FDA0 of 0x408
// bytes (the size the ctor caller 0x0007C538 also allocates) and the rowed
// copy ctor 0x0007C404 under an EH state.

class RenderObjClass;

class Rva007C454
{
public:
	Rva007C454(const Rva007C454 &other);
	virtual RenderObjClass *Clone() const;
private:
	char m_unmodelled[0x408 - 4];
};

RenderObjClass *Rva007C454::Clone() const
{
	return (RenderObjClass *)new Rva007C454(*this);
}
