// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD
//
// ?rva000B508A@Rva000B508A@@QAEXPBVRadiusDecalTemplate@@@Z, retail 0x000B508A, 239 bytes.
// Sibling of Rva000B3271 (same vtable slot of the W3D draws): copies the decal template
// into the draw's decal at +0x1E0 via rowed 0x00330CDD, then reads the owning object
// (Drawable+0xFC) and, unless its template flags (+0x108) carry 0x80, refreshes through
// virtual slot 27 (+0x6C). With the global flag at +0x9A6 set it forwards the object's
// rowed 0x0028C173 and 0x00290FC9 results when the drawable flag +0x43C is set; otherwise
// when the object has no 0x0028C197 result it takes the 0x002931F5 object (drawable via the
// rowed 0x005508E2 getter, interface virtual +0x194 when that drawable flag is set) and
// calls slot 27 with 1 and the chosen value when either drawable flag is set.
// Evidence: target bytes and the rowed callees; the class and field names are neutral views.

class RadiusDecalTemplate
{
public:
	void rva00330CDD(const RadiusDecalTemplate &other);
private:
	char m_pad[0x34];
};

struct Rva000B508AGlobals
{
	char m_pad[0x9A6];
	unsigned char m_flag9A6;
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva000B508ATemplate
{
	char m_pad[0x108];
	unsigned int m_flags108;
};

class Drawable
{
public:
	char m_pad[0xFC];
	class Object *m_object;
	char m_pad100[0x43C - 0x100];
	unsigned char m_flag43C;
};

class BfmeSubBIC
{
public:
	int bfmeAskBIC();
};

class Rva000B508AInterface
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual void v17() = 0;
	virtual void v18() = 0;
	virtual void v19() = 0;
	virtual void v20() = 0;
	virtual void v21() = 0;
	virtual void v22() = 0;
	virtual void v23() = 0;
	virtual void v24() = 0;
	virtual void v25() = 0;
	virtual void v26() = 0;
	virtual void v27() = 0;
	virtual void v28() = 0;
	virtual void v29() = 0;
	virtual void v30() = 0;
	virtual void v31() = 0;
	virtual void v32() = 0;
	virtual void v33() = 0;
	virtual void v34() = 0;
	virtual void v35() = 0;
	virtual void v36() = 0;
	virtual void v37() = 0;
	virtual void v38() = 0;
	virtual void v39() = 0;
	virtual void v40() = 0;
	virtual void v41() = 0;
	virtual void v42() = 0;
	virtual void v43() = 0;
	virtual void v44() = 0;
	virtual void v45() = 0;
	virtual void v46() = 0;
	virtual void v47() = 0;
	virtual void v48() = 0;
	virtual void v49() = 0;
	virtual void v50() = 0;
	virtual void v51() = 0;
	virtual void v52() = 0;
	virtual void v53() = 0;
	virtual void v54() = 0;
	virtual void v55() = 0;
	virtual void v56() = 0;
	virtual void v57() = 0;
	virtual void v58() = 0;
	virtual void v59() = 0;
	virtual void v60() = 0;
	virtual void v61() = 0;
	virtual void v62() = 0;
	virtual void v63() = 0;
	virtual void v64() = 0;
	virtual void v65() = 0;
	virtual void v66() = 0;
	virtual void v67() = 0;
	virtual void v68() = 0;
	virtual void v69() = 0;
	virtual void v70() = 0;
	virtual void v71() = 0;
	virtual void v72() = 0;
	virtual void v73() = 0;
	virtual void v74() = 0;
	virtual void v75() = 0;
	virtual void v76() = 0;
	virtual void v77() = 0;
	virtual void v78() = 0;
	virtual void v79() = 0;
	virtual void v80() = 0;
	virtual void v81() = 0;
	virtual void v82() = 0;
	virtual void v83() = 0;
	virtual void v84() = 0;
	virtual void v85() = 0;
	virtual void v86() = 0;
	virtual void v87() = 0;
	virtual void v88() = 0;
	virtual void v89() = 0;
	virtual void v90() = 0;
	virtual void v91() = 0;
	virtual void v92() = 0;
	virtual void v93() = 0;
	virtual void v94() = 0;
	virtual void v95() = 0;
	virtual void v96() = 0;
	virtual void v97() = 0;
	virtual void v98() = 0;
	virtual void v99() = 0;
	virtual void v100() = 0;
	virtual int slot101(class Object *object) = 0;
};

class Object
{
public:
	int rva0028C173() const;
	void *rva0028C197() const;
	Object *rva002931F5(bool flag);
	Drawable *getDrawable() const;
	char m_pad0[4];
	Rva000B508ATemplate *m_template;
};

class Rva000B508A
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual void v17() = 0;
	virtual void v18() = 0;
	virtual void v19() = 0;
	virtual void v20() = 0;
	virtual void v21() = 0;
	virtual void v22() = 0;
	virtual void v23() = 0;
	virtual void v24() = 0;
	virtual void v25() = 0;
	virtual void v26() = 0;
	virtual void slot27(int first, int second) = 0;
	void rva000B508A(const RadiusDecalTemplate *tmpl);
private:
	int m_pad4;
	Drawable *m_drawable;
	char m_padC[0x1D4];
	RadiusDecalTemplate m_decal;
};

void Rva000B508A::rva000B508A(const RadiusDecalTemplate *tmpl)
{
	if (!tmpl)
		return;
	m_decal.rva00330CDD(*tmpl);
	Object *object = m_drawable->m_object;
	if (!object)
		return;
	if (object->m_template->m_flags108 & 0x80)
		return;
	if (((Rva000B508AGlobals *)TheWritableGlobalData)->m_flag9A6)
	{
		if (m_drawable->m_flag43C)
			slot27(object->rva0028C173(), ((BfmeSubBIC *)object)->bfmeAskBIC());
		return;
	}
	if (object->rva0028C197())
		return;
	Object *other = object->rva002931F5(false);
	bool usedOther = false;
	int value = ((BfmeSubBIC *)object)->bfmeAskBIC();
	if (other)
	{
		Drawable *otherDrawable = other->getDrawable();
		if (otherDrawable && otherDrawable->m_flag43C)
		{
			usedOther = true;
			Rva000B508AInterface *iface = (Rva000B508AInterface *)other->rva0028C197();
			if (iface)
				value = iface->slot101(other);
		}
	}
	if (m_drawable->m_flag43C || usedOther)
		slot27(1, value);
}
