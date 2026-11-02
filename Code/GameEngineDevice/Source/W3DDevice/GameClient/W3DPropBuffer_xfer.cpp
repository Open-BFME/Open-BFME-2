// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?xfer@W3DPropBuffer@@MAEXPAVXfer@@@Z, retail 0x000ee901, 758 bytes. Banked partial (score 0.95) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
//
// thiscall ret 4; slot 3 of the W3DPropBuffer snapshot vtable 0x007CEECC
// (beside the "W3DPropBuffer" name getter 0x000EEFE6 in slot 2).
//
// Donor: Open-BFME-1 game/GameEngineDevice/Source/W3DDevice/GameClient/
// W3DPropBufferXfer.cpp (BFME 1 W3DPropBuffer::xfer): skipped on CRC passes,
// version 1, the prop types (bounds centre and radius, model name, the render
// object recreated on load) then the props (type, id, location, visibility,
// the render object's transform and a scale; on load the clone, its transform
// and scale, and the bounds moved to the location), then the two flags and
// the trailing int. BFME 2 differences read from retail:
//   * the version is the rowed Xfer::Version1 helper 0x000053EE;
//   * Xfer slots +0x04 isLoading / +0x0C isCRC / +0x60 xferCoord3D / +0x6C
//     xferAsciiString / +0x70 xferReal / +0x7C xferInt / +0x90 xferBool;
//     the vector and matrix helpers are the rowed Rva0030612AXfer and
//     Rva003062FEXfer;
//   * Set_ObjectScale is render object slot 93 (+0x174);
//   * the type bounds copy is SphereClass::operator= (pinned at the folded
//     0x0004254E).
// Create_Render_Obj 0x00136175 rebuilds the type's render object on load.

typedef int Int;
typedef float Real;
typedef bool Bool;

#include "Coord3D.h"
#include "Coord3DBase.h"
#include "ascii_string.h"

struct Matrix3D
{
	Real row0[4];
	Real row1[4];
	Real row2[4];

	__declspec(dllimport) __forceinline Matrix3D(bool identity)
	{
		if (identity) {
			row0[0] = 1.0f;
			row0[1] = 0.0f;
			row0[2] = 0.0f;
			row0[3] = 0.0f;
			row1[0] = 0.0f;
			row1[1] = 1.0f;
			row1[2] = 0.0f;
			row1[3] = 0.0f;
			row2[0] = 0.0f;
			row2[1] = 0.0f;
			row2[2] = 1.0f;
			row2[3] = 0.0f;
		}
	}

	__forceinline Matrix3D &operator=(const Matrix3D &other)
	{
		row0[0] = other.row0[0];
		row0[1] = other.row0[1];
		row0[2] = other.row0[2];
		row0[3] = other.row0[3];
		row1[0] = other.row1[0];
		row1[1] = other.row1[1];
		row1[2] = other.row1[2];
		row1[3] = other.row1[3];
		row2[0] = other.row2[0];
		row2[1] = other.row2[1];
		row2[2] = other.row2[2];
		row2[3] = other.row2[3];
		return *this;
	}
};

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/SphereClass.h"

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;

#include "../../../../GameEngine/Include/Common/BfmeXfer.h"

void Rva0030612AXfer(Xfer *xfer, Real *value);
Xfer *Rva003062FEXfer(Xfer *xfer, Real *value);

#define PAD_VIRTUALS10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class RenderObjClass
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual RenderObjClass *Clone() const;		// slot 2
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	PAD_VIRTUALS10(s1)
	virtual void Validate_Transform() const;	// slot 20
	virtual void Set_Transform(const Matrix3D &transform);	// slot 21
	virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
	virtual void s27(); virtual void s28(); virtual void s29();
	PAD_VIRTUALS10(s3) PAD_VIRTUALS10(s4) PAD_VIRTUALS10(s5) PAD_VIRTUALS10(s6)
	PAD_VIRTUALS10(s7) PAD_VIRTUALS10(s8)
	virtual void s90(); virtual void s91(); virtual void s92();
	virtual void Set_ObjectScale(Real scale);	// slot 93

	const Matrix3D &Get_Transform() const
	{
		Validate_Transform();
		return m_transform;
	}

	char pad04[0x14];
	Matrix3D m_transform;				// +0x18
};


struct TProp
{
	RenderObjClass *m_robj;
	Int id;
	Coord3D location;
	Int propType;
	Int ss;
	Bool visible;
	SphereClass bounds;
};

struct TPropType
{
	RenderObjClass *m_robj;
	AsciiString m_robjName;
	SphereClass m_bounds;
};

#include "Common/Snapshot.h"

class W3DPropBuffer : public Snapshot
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	TProp m_props[4000];		// +0x04
	Int m_numProps;			// +0x2EE04
	Bool m_anythingChanged;		// +0x2EE08
	Bool m_initialized;
	Bool m_doCull;			// +0x2EE0A
	char m_pad2ee0b[0x2EE18 - 0x2EE0B];
	TPropType m_propTypes[96];	// +0x2EE18
	Int m_numPropTypes;		// +0x2F718
	void *m_propShroudMaterialPass;
	Int m_bfmeExtraField;		// +0x2F720
};

RenderObjClass *Create_Render_Obj(const char *name);

void W3DPropBuffer::xfer(Xfer *xfer)
{
	if ((xfer?xfer:xfer)->IsCRC())
		return;

	xfer->Version1();

	(*xfer == m_numPropTypes);
	Int i;
	for (i = 0; i < m_numPropTypes; ++i) {
		Rva0030612AXfer(xfer, &m_propTypes[i].m_bounds.Center.X);
		(*xfer == m_propTypes[i].m_bounds.Radius);
		(*xfer == m_propTypes[i].m_robjName);
		if (xfer->IsLoading())
			m_propTypes[i].m_robj = Create_Render_Obj(m_propTypes[i].m_robjName.str());
	}

	(*xfer == m_numProps);
	for (i = 0; i < m_numProps; ++i) {
		(*xfer == m_props[i].propType);
		(*xfer == m_props[i].id);
		(*xfer == asBase(m_props[i].location));
		(*xfer == m_props[i].visible);
		Matrix3D transform(true);
		Real scale = 1.0f;

		if (!xfer->IsLoading()) {
			RenderObjClass *current = m_props[i].m_robj;
			if (current) {
				current->Get_Transform();
				transform = current->m_transform;
			}
		}
		Rva003062FEXfer(xfer, transform.row0);
		(*xfer == scale);

		if (xfer->IsLoading()) {
			m_props[i].ss = 0;
			RenderObjClass *source;
			if (m_props[i].propType < 0 || m_props[i].propType > m_numPropTypes ||
				(source = m_propTypes[m_props[i].propType].m_robj) == 0) {
				m_props[i].m_robj = 0;
			} else {
				m_props[i].m_robj = source->Clone();
				m_props[i].m_robj->Set_Transform(transform);
				m_props[i].m_robj->Set_ObjectScale(scale);
			}
			if (m_props[i].propType < 0 || m_props[i].propType > m_numPropTypes) {
				m_props[i].bounds.Center.X = 0.0f;
				m_props[i].bounds.Center.Y = 0.0f;
				m_props[i].bounds.Center.Z = 0.0f;
				m_props[i].bounds.Radius = 0.0f;
			} else {
				m_props[i].bounds = m_propTypes[m_props[i].propType].m_bounds;
			}
			m_props[i].bounds.Center += Vector3(m_props[i].location.x,
				m_props[i].location.y, m_props[i].location.z);
		}
	}

	(*xfer == m_anythingChanged);
	(*xfer == m_doCull);
	(*xfer == m_bfmeExtraField);
}
