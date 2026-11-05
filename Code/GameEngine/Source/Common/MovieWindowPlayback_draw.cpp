// cl: /MD
// ?draw@MovieWindowPlayback@@UAEXXZ @0x00524973 186B
// Slot 0x30 of vtable 0x00867DFC (class of ??0Rva00524B7A). Guards on
// +0x24 bit0 and +0x0C null, virtual slot15 result, TheDisplay slot 0x104
// with int+4 floats+int, then slot8 result to broadcast. Chain of ctor.
class Display;
extern Display *TheDisplay;

class Display
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65(int a, float b, float c, float d, float e, int f);
};

class Rva0081D520Owner
{
public:
	void broadcast(int value, float x0, float y0, float x1, float y1);
};

class SlotOwner
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual int s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual int s15();
};

struct InnerLink
{
	char m_pad[0x18];
	Rva0081D520Owner *m_owner;
};

class Rva00524A4CInterface;

class MovieWindowPlayback
{
public:
	void clear();
	void Rva00524A65(int arg);
	float rva00524A84();
	virtual void draw();

private:
	char m_basePad[8];
	Rva00524A4CInterface *m_ptr;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	unsigned char m_flags;
	char m_pad25[3];
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
};
void MovieWindowPlayback::draw()
{
	if ((m_flags & 1) == 0)
		return;
	if (m_ptr == 0)
		return;
	int r = ((SlotOwner *)m_ptr)->s15();
	if (r == 0)
		return;
	if (TheDisplay != 0)
		TheDisplay->v65(r, (float)m_10, (float)m_14, (float)m_18, (float)m_1C, m_28);
	InnerLink *link = *(InnerLink **)((char *)m_ptr + 8);
	Rva0081D520Owner *owner = link->m_owner;
	if (owner == 0)
		return;
	owner->broadcast(((SlotOwner *)m_ptr)->s08(), (float)m_10, (float)m_14, (float)m_18, (float)m_1C);
}

// MovieWindowPlayback::OpenMovie's complete native subtitle settings at
// VA BF63DC..BF63F8. These descriptive names retain the proven word types;
// the original identifiers and the meaning of the three draw words are unknown.
extern const int MovieSubtitleDrawWord0=8;
extern const int MovieSubtitleDrawWord1=0x61a8;
extern const int MovieSubtitleDrawWord2=0x3f3f3f3f;
extern const float MovieSubtitleXScale=0.52734375f;
extern const float MovieSubtitleYScale=0.4228515625f;
extern const float MovieSubtitleNormalWidth=0.813802063465118408203125f;
extern const float MovieSubtitleLockedWidth=0.9765625f;
