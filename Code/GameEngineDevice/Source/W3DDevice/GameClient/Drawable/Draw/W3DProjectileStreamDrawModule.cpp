// cl: /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// W3DProjectileStreamDraw::doDrawModule and makeOrUpdateLine, ported from
// Zero Hour's GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/
// W3DProjectileStreamDraw.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference) onto the BFME 2 layout.
//
// BFME 2 layout (constructor 0x000D1370): module data +0x04, drawable
// +0x08, texture RefCountPtr +0x0C, 20 line slots +0x10, m_linesValid +0x60.
// W3DProjectileStreamDrawModuleData: m_width +0x0C, m_tileFactor +0x10,
// m_scrollRate +0x14, m_maxSegments +0x18. The drawable's object sits at
// +0xFC. In BFME 2 SegmentedLineClass::Set_Texture takes the texture
// RefCountPtr by reference: its body (0x0015E250 -> 0x001911E0) reads the
// pointer through the argument and adds a reference.

#include "BfmeDrawXferPrefix.h"
#include "ascii_string.h"
#include "Common/Snapshot.h"
#include "../../../../../../GameEngine/Include/Common/ObjectModule.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

#include "../../../../../../../reference/shims/wwmath/Vector2.h"

class Vector3
{
public:
	Vector3() {}
	__declspec(dllimport) __forceinline Vector3( float x, float y, float z ) { X = x; Y = y; Z = z; }
	Vector3( const Vector3 &vec ) { X = vec.X; Y = vec.Y; Z = vec.Z; }
	Vector3 &operator = ( const Vector3 &vec ) { X = vec.X; Y = vec.Y; Z = vec.Z; return *this; }
	friend __forceinline bool operator != ( const Vector3 &lhs, const Vector3 &rhs )
	{
		return ( lhs.X != rhs.X || lhs.Y != rhs.Y || lhs.Z != rhs.Z );
	}
	float X;
	float Y;
	float Z;
};

class TextureClass;

class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
	int m_pad[2];
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : m_ptr(0) {}
	const RefCountPtr &operator=(const RefCountPtr &other);
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }

	T *m_ptr;
};

#pragma optimize("t", on)
class ShaderClass
{
public:
	ShaderClass( const ShaderClass &shader ) { ShaderBits = shader.ShaderBits; }
	static ShaderClass _PresetAdditiveSpriteShader;
private:
	unsigned int ShaderBits;
};
#pragma optimize("", on)

class SegLineRendererClass
{
public:
	enum TextureMapMode
	{
		UNIFORM_WIDTH_TEXTURE_MAP = 0,
		UNIFORM_LENGTH_TEXTURE_MAP,
		TILED_TEXTURE_MAP
	};
};

class SegmentedLineClass;

class SceneClass
{
public:
	virtual void v00();
	virtual void v01();
	virtual void Add_Render_Object(SegmentedLineClass *line); // slot 2
	virtual void Remove_Render_Object(SegmentedLineClass *line); // slot 3
};

class SegmentedLineClass
{
public:
	SegmentedLineClass( void );
	virtual void Delete_This( void );																					///< slot 0
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void Remove();
	virtual void slot17();
	virtual SceneClass *Peek_Scene( void );																					///< slot 18
	void Set_Points( unsigned int num_points, Vector3 *locs );
	void Set_Texture( TextureClass *texture );
	void Set_Shader( ShaderClass shader );
	void Set_Width( float width );
	void Set_Texture_Mapping_Mode( SegLineRendererClass::TextureMapMode mode );
	void Set_Texture_Tile_Factor( float factor );
	void Set_UV_Offset_Rate( const Vector2 &rate );
	void Release_Ref( void ) { NumRefs--; if (NumRefs == 0) Delete_This(); }
private:
	int NumRefs;																															///< 0x04
	char m_unrecovered08[ 0x12C - 0x08 ];
};

#define REF_PTR_RELEASE(x) { if (x) x->Release_Ref(); x = 0; }

class RTS3DScene : public SceneClass
{
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class ProjectileStreamUpdate
{
public:
	void getAllPoints( Vector3 *points, Int *count );
};

class Module;

class Object
{
public:
	ProjectileStreamUpdate *findUpdateModule( NameKeyType key ) const { return (ProjectileStreamUpdate *)findModule( key ); }
protected:
	Module *findModule( NameKeyType key ) const;
};

class Drawable
{
public:
	__declspec(dllimport) __forceinline Object *getObject( void ) { return m_object; }
private:
	char m_unrecovered00[ 0xFC ];
	Object *m_object;																													///< 0xFC
};

class MultiIniFieldParse;

class W3DProjectileStreamDrawModuleData : public Snapshot
{
public:
	W3DProjectileStreamDrawModuleData();
	virtual ~W3DProjectileStreamDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

	unsigned int m_unused04; // +0x04, following Snapshot's vptr
	AsciiString m_texture; // +0x08
	float m_width; // +0x0C
	float m_tileFactor; // +0x10
	float m_scrollRate; // +0x14
	int m_maxSegments; // +0x18
};

enum { MAX_PROJECTILE_STREAM = 20 };

template <class T> inline const T &max( const T &lhs, const T &rhs ) { return lhs > rhs ? lhs : rhs; }

class Matrix3D;

class DrawModule : public ObjectModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);
};

class W3DProjectileStreamDraw : public DrawModule
{
public:
	W3DProjectileStreamDraw(Thing *thing, const ModuleData *moduleData);
	virtual ~W3DProjectileStreamDraw();
	virtual NameKeyType getModuleNameKey() const;
	virtual void setFullyObscuredByShroud(bool fullyObscured);
	virtual void doDrawModule(const Matrix3D *transformMtx);

protected:
	virtual void xfer(Xfer *xfer);
	void makeOrUpdateLine(Vector3 *points, unsigned int pointCount, int lineIndex);
	Drawable *getDrawable() const { return (Drawable *)m_object; }
	const W3DProjectileStreamDrawModuleData *getW3DProjectileStreamDrawModuleData() const { return (const W3DProjectileStreamDrawModuleData *)m_moduleData; }

private:
	RefCountPtr<TextureClass> m_texture; // +0x0C
	SegmentedLineClass *m_allLines[0x14]; // +0x10
	int m_linesValid; // +0x60
};

void W3DProjectileStreamDraw::doDrawModule(const Matrix3D* )
{
	// get object from logic
	Object *me = getDrawable()->getObject();
	if (me == 0)
		return;

	static NameKeyType key_ProjectileStreamUpdate = NAMEKEY("ProjectileStreamUpdate");
	ProjectileStreamUpdate* update = (ProjectileStreamUpdate*)me->findUpdateModule(key_ProjectileStreamUpdate);

	const W3DProjectileStreamDrawModuleData *data = getW3DProjectileStreamDrawModuleData();

	Vector3 allPoints[MAX_PROJECTILE_STREAM];
	Int pointsUsed;

	update->getAllPoints( allPoints, &pointsUsed );

	Vector3 stagingPoints[MAX_PROJECTILE_STREAM];
	const Vector3 zeroVector(0, 0, 0);

	Int linesMade = 0;
	Int currentMasterPoint = 0;
	UnsignedInt currentStagingPoint = 0;

	if( data->m_maxSegments )
	{
		// If I have a drawing cap, I need to increase the start point in the array.  The furthest (oldest)
		// point from the tank is in spot zero.
		currentMasterPoint = pointsUsed - data->m_maxSegments;
		currentMasterPoint = max( 0, currentMasterPoint ); // (but if they say to draw more than exists, draw all)
	}

	// Okay.  I have an array of ordered points that may have blanks in it.  I need to copy to the staging area
	// until I hit a blank or the end.  Then if I have a line made, I'll overwrite it, otherwise I'll make a new one.
	// I'll keep doing this until I run out of valid points.
	while( currentMasterPoint < pointsUsed )
	{
		while( currentMasterPoint < pointsUsed  &&  allPoints[currentMasterPoint] != zeroVector )
		{
			// While I am not looking at a bad point (off edge or zero)
			stagingPoints[currentStagingPoint] = allPoints[currentMasterPoint];// copy to the staging
			currentStagingPoint++;// increment how many I have
			currentMasterPoint++;// increment what I am looking at
		}
		// Use or reuse a line
		if( currentStagingPoint > 1 )
		{
			// Don't waste a line on a double hole (0) or a one point line (1)
			makeOrUpdateLine( stagingPoints, currentStagingPoint, linesMade );
			linesMade++;// keep track of how many are real this frame
		}
		currentMasterPoint++;//I am either pointed off the edge anyway, or I am pointed at a zero I want to skip
		currentStagingPoint = 0;//start over in the staging area
	}

	Int oldLinesValid = m_linesValid;
	for( Int lineIndex = linesMade; lineIndex < oldLinesValid; lineIndex++ )
	{
		// Delete any line we aren't using anymore.
		SegmentedLineClass *deadLine = m_allLines[lineIndex];
		if (deadLine->Peek_Scene())
			W3DDisplay::m_3DScene->Remove_Render_Object( deadLine );
		REF_PTR_RELEASE( deadLine );

		m_allLines[lineIndex] = 0;
		m_linesValid--;
	}
}

void W3DProjectileStreamDraw::makeOrUpdateLine( Vector3 *points, UnsignedInt pointCount, Int lineIndex )
{
	Bool newLine = false;

	if( m_allLines[lineIndex] == 0 )
	{
		//Need a new one if this is blank, otherwise I'll reset the existing one
		m_allLines[lineIndex] = new SegmentedLineClass;
		m_linesValid++;
		newLine = true;
	}

	SegmentedLineClass *line = m_allLines[lineIndex];

	line->Set_Points(pointCount, points);	//tell the line which points to use

	if( newLine )
	{
		// This is one time stuff we only need to do if this is a new and not a change
		const W3DProjectileStreamDrawModuleData *data = getW3DProjectileStreamDrawModuleData();
		line->Set_Texture((TextureClass *)&m_texture);	//set the texture
		line->Set_Shader(ShaderClass::_PresetAdditiveSpriteShader);	//pick the alpha blending mode you want - see shader.h for others.
		line->Set_Width(data->m_width);	//set line width in world units
		line->Set_Texture_Mapping_Mode(SegLineRendererClass::TILED_TEXTURE_MAP);	//this tiles the texture across the line
		line->Set_Texture_Tile_Factor(data->m_tileFactor);	//number of times to tile texture across each segment
		line->Set_UV_Offset_Rate(Vector2(0.0f,data->m_scrollRate));	//amount to scroll texture on each draw
		W3DDisplay::m_3DScene->Add_Render_Object( line);	//add it to our scene so it gets rendered with other objects.
	}
}
