// ?createEmbeddedPortals@Drawable@@UAEXXZ
// partial score=0.7 date=2026-10-10
// at this+0x36C. Identity: WB Drawable::createEmbeddedPortals
// (Drawable.cpp:1210, string evidence).
#include "ascii_string.h"
#include "Lib/Coord3D.h"

class Matrix3D;

// CRT vector construct/destruct iterators (vendored msvc71 pattern: local
// stdcall spelling aliased to the CRT bodies, cf BfmeConv730.cpp).
typedef void (*Rva0027A018VecFn)(void *);
extern void __stdcall rva0027A018VecCtor(void *, unsigned, int, Rva0027A018VecFn, Rva0027A018VecFn);
extern void __stdcall rva0027A018VecDtor(void *, unsigned, int, Rva0027A018VecFn);
#pragma comment(linker, "/alternatename:?rva0027A018VecCtor@@YGXPAXIHP6AX0@Z1@Z=??_L@YGXPAXIHP6EX0@Z1@Z")
#pragma comment(linker, "/alternatename:?rva0027A018VecDtor@@YGXPAXIHP6AX0@Z@Z=??_M@YGXPAXIHP6EX0@Z@Z")

class Object
{
public:
	int getMultiLogicalBonePosition(const char *prefix, int maxBones, Coord3D *positions, Matrix3D *transforms, bool convertToWorld, int extra) const;
	char m_pad[0x25C];
	void *m_25C;
};

class Waypoint
{
public:
	Waypoint(unsigned id, AsciiString name, const Coord3D *loc, AsciiString label1, AsciiString label2, AsciiString label3, bool biDir, int extra, AsciiString extraLabel);
	void addLink(Waypoint *other);
	char m_pad[0xC0];
};

class Rva002E9042
{
public:
	void rva002E8FE5(void *p);
};

// Opaque portal-bone source: element exposes slot 0xA8, its product slot 0xB0.
class Rva0027A018Bones
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41();
	virtual Rva0027A018Bones *v_a8(); // slot 42
	virtual void v43();
	virtual bool v_b0(int index, int *out); // slot 44
};

class Rva0027A018PortalVec
{
public:
	Waypoint **m_start;
	Waypoint **m_finish;
	Waypoint **m_end;
	void push_back(Waypoint *const &wp);
};

class Drawable
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void createEmbeddedPortals(); // slot 32 (identity: WB; slot unproven)
	char m_pad04[0xFC - 4];
	Object *m_object; // +0xFC
	char m_pad100[0x14C - 0x100];
	void **m_portalSources; // +0x14C
	char m_pad150[0x36C - 0x150];
	Rva0027A018PortalVec m_embeddedPortals; // +0x36C
};

extern const char g_Rva0107301CEmptyString[];

void Drawable::createEmbeddedPortals()
{
	Object *obj = m_object;
	void **source = m_portalSources;
	Coord3D *pos;
	if (*source == 0)
		return;
	do
	{
		Rva0027A018Bones *bones = (*(Rva0027A018Bones **)source)->v_a8();
		if (bones != 0)
		{
			AsciiString boneName;
			int boneParam = 0;
			int boneIndex = 0;
			if (bones->v_b0(0, &boneParam))
			{
				do
				{
					Coord3D points[10];
					rva0027A018VecCtor(points, 12, 10, (Rva0027A018VecFn)0x87A6A9, (Rva0027A018VecFn)0x4B3FD0);
					int count = obj->getMultiLogicalBonePosition((*(const char **)&boneName) ? (*(const char **)&boneName) + 8 : g_Rva0107301CEmptyString, 10, points, 0, 1, 0);
					if (count >= 2)
					{
						Waypoint *prev = 0;
						if (count > 0)
						{
							pos = points;
							do
							{
								Waypoint *wp = new Waypoint(0x7ffffffe, AsciiString((const char *)0xBFB0F0), pos,
									AsciiString::TheEmptyString, AsciiString::TheEmptyString, AsciiString::TheEmptyString,
									false, boneParam, AsciiString::TheEmptyString);
								((Rva002E9042 *)((char *)*(void *const *)0xDFF0F8 + 0x10))->rva002E8FE5(wp);
								if (prev != 0)
								{
									prev->addLink(wp);
									wp->addLink(prev);
								}
								prev = wp;
								m_embeddedPortals.push_back(wp);
								pos++;
							} while (--count != 0);
						}
					}
					rva0027A018VecDtor(points, 12, 10, (Rva0027A018VecFn)0x4B3FD0);
					boneIndex++;
				} while (bones->v_b0(boneIndex, &boneParam));
			}
		}
		source++;
	} while (*source != 0);
}