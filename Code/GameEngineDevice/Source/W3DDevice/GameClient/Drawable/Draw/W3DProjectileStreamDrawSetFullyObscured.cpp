// cl: /O1 /DNDEBUG /MD /GX
//
// ?setFullyObscuredByShroud@W3DProjectileStreamDraw@@UAEX_N@Z, retail 0x000D1124, 130 bytes.
// Vslot 35 (offset 0x8C) of vtable 0x007CE010 (class of ??0W3DProjectileStreamDraw@@QAE@PAVThing@@PBVModuleData@@@Z).
// Donor: Zero Hour W3DProjectileStreamDraw::setFullyObscuredByShroud (W3DProjectileStreamDraw.cpp):
// true branch loops m_allLines[0..m_linesValid) calling Peek_Scene (+0x48) then Remove (+0x40);
// false branch loops calling Peek_Scene then W3DDisplay::m_3DScene->Add_Render_Object (+0x8).
// Layout from rowed ctor 0xD1370 (Rva000B19A1 base size 0xC, texture +0x0C, 0x14 lines +0x10, count +0x60).
// No direct callees (all virtual); scene global at data 0x009E1B34 via W3DDisplay::m_3DScene.

class Thing;
class ModuleData;

class Rva000B19A1
{
public:
	virtual ~Rva000B19A1();

protected:
	void *m_unk04;
	int m_unk08;
};

class SegmentedLineClass;

class SceneClass
{
public:
	virtual void v00();
	virtual void v01();
	virtual void Add_Render_Object(SegmentedLineClass *line);
	virtual void Remove_Render_Object(SegmentedLineClass *line);
};

class SegmentedLineClass
{
public:
	virtual void slot00();
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
	virtual SceneClass *Peek_Scene();
};

class W3DDisplay
{
public:
	static SceneClass *m_3DScene;
};

class W3DProjectileStreamDraw : public Rva000B19A1
{
public:
	virtual void setFullyObscuredByShroud(bool fullyObscured);

private:
	void *m_pad0C;
	SegmentedLineClass *m_allLines[0x14];
	int m_linesValid;
};

void W3DProjectileStreamDraw::setFullyObscuredByShroud(bool fullyObscured)
{
	if (fullyObscured) {
		for (int lineIndex = 0; lineIndex < m_linesValid; ++lineIndex) {
			SegmentedLineClass *deadLine = m_allLines[lineIndex];
			if (deadLine && deadLine->Peek_Scene())
				deadLine->Remove();
		}
	} else {
		for (int lineIndex = 0; lineIndex < m_linesValid; ++lineIndex) {
			SegmentedLineClass *deadLine = m_allLines[lineIndex];
			if (deadLine && !deadLine->Peek_Scene())
				W3DDisplay::m_3DScene->Add_Render_Object(deadLine);
		}
	}
}
