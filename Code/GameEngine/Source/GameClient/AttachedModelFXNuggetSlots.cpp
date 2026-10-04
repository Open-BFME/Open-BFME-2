// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /DNDEBUG
//
// AttachedModelFXNugget slots (class and members as in
// AttachedModelFXNuggetCtor.cpp: model name +0x148, randomly-rotate flag
// +0x14C, expire timer +0x150), vtable 0x00BDD814:
//
// ?doFXObj@AttachedModelFXNugget@@UBEXPBVObject@@0@Z 97B @0x001E0878, slot 2:
//     hands the model name (by value), the rotate flag and the timer to the
//     primary's drawable through the rowed Drawable member 0x00276223 (its
//     flag is a bool: retail pushes the byte unextended, which /G7 emits).
// ?rva001E1709@AttachedModelFXNugget@@UBEXAAVAssetList@@H@Z 19B @0x001E1709,
//     slot 3 (purecall in the base, the shared empty 0x0050B238 in most
//     nuggets): appends the model name to an AssetList (operator<< 0x0006C950).
//     The slot's own name and its second argument are unknown.
#include "ascii_string.h"

struct Coord3D;
class Matrix3D;

class AssetList
{
public:
	AssetList &operator<<(const AsciiString &name);
};

// The rowed Drawable member the model attach goes through.
class Rva00276223
{
public:
	void rva00276223(AsciiString modelName, bool randomlyRotate, int expireTimer);
};

class Drawable;

class Object
{
public:
	Drawable *getDrawable() const;
};

class FXNugget
{
public:
	virtual ~FXNugget();
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const = 0;
	virtual void doFXObj(const Object *primary, const Object *secondary) const;

private:
	unsigned char m_pad04[0x148 - 4];
};

class AttachedModelFXNugget : public FXNugget
{
public:
	virtual void doFXObj(const Object *primary, const Object *secondary) const;
	virtual void rva001E1709(AssetList &assets, int) const;

private:
	AsciiString m_modelName; // +0x148
	bool m_randomlyRotate; // +0x14C
	int m_expireTimer; // +0x150
};

void AttachedModelFXNugget::doFXObj(const Object *primary, const Object *) const
{
	if (primary && primary->getDrawable())
	{
		((Rva00276223 *)primary->getDrawable())->rva00276223(m_modelName, m_randomlyRotate, m_expireTimer);
	}
}

void AttachedModelFXNugget::rva001E1709(AssetList &assets, int) const
{
	assets << m_modelName;
}
