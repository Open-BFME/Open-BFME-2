// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?Rva00211142Clone@@YGPAVRva00210F3D@@PAV1@@Z, retail 0x00211142 (89B).
// Clone: if src null return null else new Rva003FA776 copy-assign from src then link src+4 and flag +8.
// Evidence: callees ??2@YAPAXI@Z ??0Rva003FA776@@QAE@XZ ??4Rva00210F3D@@QAEAAV0@ABV0@@Z all rowed; caller 0x002137F1; ret 4 one pointer arg.

void *operator new(unsigned int);

class Rva00210F3D
{
public:
	virtual ~Rva00210F3D();
	Rva00210F3D &operator=(const Rva00210F3D &that);
	Rva00210F3D *m_04;
	unsigned char m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
};

class Rva003FA776 : public Rva00210F3D
{
public:
	Rva003FA776();
};

Rva00210F3D *__stdcall Rva00211142Clone(Rva00210F3D *src)
{
	if (src == 0)
		return 0;
	Rva003FA776 *n = new Rva003FA776;
	Rva00210F3D &dst = *n;
	dst = *src;
	src->m_04 = n;
	n->m_08 = 1;
	return n;
}
