// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?rva00491C84@Rva00491C84@@QAEXPAUCoord3D@@PBVObject@@@Z @0x00491C84 171B:
// copies Object position at +0x38 to a local, filters through the +0x250
// provider null check plus flag at +0x115 bit 0x20 plus virtual slot 0x230
// bool test, then adjusts Z by GeometryInfo at +0xA8 when the ModuleData at
// this+4 has anchor at +0x21, and writes the local to the out Coord. Same
// AttachUpdate family as prev 0x00491AA0; callees are rowed
// Object::rva0028C197 0x0028C197 and GeometryInfo::getMaxHeight 0x006BD7C0.
// Caller at 0x00491D6E proves thiscall void(Coord3D* Object*); honest Rva
// owner since the caller class is unproven.
struct Coord3D
{
	float x, y, z;
};

class Object;

class Rva0028C197Provider
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
};

class Object
{
public:
	void *rva0028C197() const;

public:
	void *m_vtable00;
	void *m_unk04;
	char m_pad08[0x38 - 8];
	Coord3D m_pos38;
	char m_pad44[0xA8 - 0x44];
	void *m_geomA8[13];
	char m_padDC[0x115 - 0xDC];
	unsigned char m_flag115;
	char m_pad116[0x244 - 0x116];
	void **m_modules244;
	char m_pad248[0x250 - 0x248];
	Rva0028C197Provider *m_provider250;
};

class FilterObj
{
public:
	virtual void v000(); virtual void v001(); virtual void v002(); virtual void v003(); virtual void v004();
	virtual void v005(); virtual void v006(); virtual void v007(); virtual void v008(); virtual void v009();
	virtual void v010(); virtual void v011(); virtual void v012(); virtual void v013(); virtual void v014();
	virtual void v015(); virtual void v016(); virtual void v017(); virtual void v018(); virtual void v019();
	virtual void v020(); virtual void v021(); virtual void v022(); virtual void v023(); virtual void v024();
	virtual void v025(); virtual void v026(); virtual void v027(); virtual void v028(); virtual void v029();
	virtual void v030(); virtual void v031(); virtual void v032(); virtual void v033(); virtual void v034();
	virtual void v035(); virtual void v036(); virtual void v037(); virtual void v038(); virtual void v039();
	virtual void v040(); virtual void v041(); virtual void v042(); virtual void v043(); virtual void v044();
	virtual void v045(); virtual void v046(); virtual void v047(); virtual void v048(); virtual void v049();
	virtual void v050(); virtual void v051(); virtual void v052(); virtual void v053(); virtual void v054();
	virtual void v055(); virtual void v056(); virtual void v057(); virtual void v058(); virtual void v059();
	virtual void v060(); virtual void v061(); virtual void v062(); virtual void v063(); virtual void v064();
	virtual void v065(); virtual void v066(); virtual void v067(); virtual void v068(); virtual void v069();
	virtual void v070(); virtual void v071(); virtual void v072(); virtual void v073(); virtual void v074();
	virtual void v075(); virtual void v076(); virtual void v077(); virtual void v078(); virtual void v079();
	virtual void v080(); virtual void v081(); virtual void v082(); virtual void v083(); virtual void v084();
	virtual void v085(); virtual void v086(); virtual void v087(); virtual void v088(); virtual void v089();
	virtual void v090(); virtual void v091(); virtual void v092(); virtual void v093(); virtual void v094();
	virtual void v095(); virtual void v096(); virtual void v097(); virtual void v098(); virtual void v099();
	virtual void v100(); virtual void v101(); virtual void v102(); virtual void v103(); virtual void v104();
	virtual void v105(); virtual void v106(); virtual void v107(); virtual void v108(); virtual void v109();
	virtual void v110(); virtual void v111(); virtual void v112(); virtual void v113(); virtual void v114();
	virtual void v115(); virtual void v116(); virtual void v117(); virtual void v118(); virtual void v119();
	virtual void v120(); virtual void v121(); virtual void v122(); virtual void v123(); virtual void v124();
	virtual void v125(); virtual void v126(); virtual void v127(); virtual void v128(); virtual void v129();
	virtual void v130(); virtual void v131(); virtual void v132(); virtual void v133(); virtual void v134();
	virtual void v135(); virtual void v136(); virtual void v137(); virtual void v138(); virtual void v139();
	virtual bool check(Coord3D *p);
};

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
};

class AttachUpdateModuleData
{
public:
	char m_pad00[0x21];
	unsigned char m_anchor21;
};

class Rva00491C84
{
public:
	void rva00491C84(Coord3D *out, const Object *obj);

private:
	void *m_pad00;
	AttachUpdateModuleData *m_data04;
};

void Rva00491C84::rva00491C84(Coord3D *out, const Object *obj)
{
	const AttachUpdateModuleData *data = m_data04;
	const Coord3D *src = &obj->m_pos38;
	Coord3D tmp;
	tmp.x = src->x;
	tmp.y = src->y;
	tmp.z = src->z;
	unsigned char *flagBase = (unsigned char *)obj->m_unk04;
	if ((flagBase[0x115] & 0x20) != 0 && obj->m_provider250 != 0)
	{
		FilterObj *p = (FilterObj *)obj->rva0028C197();
		if (p != 0)
		{
			if (!p->check(&tmp))
			{
				tmp = *src;
			}
		}
	}
	if (data->m_anchor21 != 0)
	{
		const GeometryInfo *geom = (const GeometryInfo *)((const char *)obj + 0xA8);
		tmp.z += geom->getMaxHeightAbovePosition();
	}
	out->x = tmp.x;
	out->y = tmp.y;
	out->z = tmp.z;
}
