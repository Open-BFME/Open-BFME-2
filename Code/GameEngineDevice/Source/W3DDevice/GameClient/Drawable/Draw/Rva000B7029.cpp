// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?rva000B7029@Rva000B7029@@QAEPBVImage@@XZ retail 0x000B7029 75 bytes.
// Vslot 51 (0xCC) of Draw family sharing dirty flag at +0x2D9 with cached
// Image at +0x2DC recomputed via Sub at +0x14 AsciiString at +0x60 isEmpty
// plus rowed findImageByName through global TheMappedImageCollection. Evidence is 5
// Draw vtables plus rowed callees plus neighbour flags.

class Image;
class AsciiString;

#include "ascii_string.h"


class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

struct DrawSub
{
	char m_pad00[0x60];
	AsciiString m_str60;
};

class Rva000B7029
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
	virtual const Image *rva000B7029();
private:
	char m_pad04[0x14 - 4];
	DrawSub *m_14;
	char m_pad18[0x2D9 - 0x18];
	bool m_2D9;
	char m_pad2DA[0x2DC - 0x2DA];
	const Image *m_2DC;
};

const Image *Rva000B7029::rva000B7029()
{
	if (m_2D9) {
		m_2D9 = false;
		DrawSub *sub = m_14;
		if (sub != 0) {
			if (!sub->m_str60.isEmpty())
				m_2DC = TheMappedImageCollection->findImageByName(sub->m_str60);
			else
				m_2DC = 0;
		}
	}
	return m_2DC;
}
