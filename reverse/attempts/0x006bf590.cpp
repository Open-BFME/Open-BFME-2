// ?erase@BfmeVec60@@QAEPAUBfmeElem60@@PAU2@0@Z
// partial score=0.7 date=2026-09-22
// cl: /O2 /Ob0 /G6

struct BfmeTail60
{
	char *m_p;
	void release();
};

struct BfmeElem60
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	BfmeTail60 m_1C;
	char m_20;
	char m_pad[3];
};

class BfmeVec60
{
public:
	void resize(unsigned n, BfmeElem60 value);
	BfmeElem60 *erase(BfmeElem60 *first, BfmeElem60 *last);
	void insert(BfmeElem60 *pos, unsigned count, const BfmeElem60 &value);

	BfmeElem60 *_M_start;
	BfmeElem60 *_M_finish;
	BfmeElem60 *_M_end_of_storage;
};

void BfmeVec60::resize(unsigned n, BfmeElem60 value)
{
	if (n < (unsigned)(_M_finish - _M_start))
	{
		erase(_M_start + n, _M_finish);
		value.m_1C.release();
	}
	else
	{
		insert(_M_finish, n - (unsigned)(_M_finish - _M_start), value);
		value.m_1C.release();
	}
}

BfmeElem60 *Rva006BE2E0Copy(BfmeElem60 *last, BfmeElem60 *finish, BfmeElem60 *first, void *temp, int flag);

// ?erase@BfmeVec60@@QAEPAUBfmeElem60@@PAU2@0@Z @0x006BF590
BfmeElem60 *BfmeVec60::erase(BfmeElem60 *first, BfmeElem60 *last)
{
	BfmeElem60 *temp;
	BfmeElem60 *i = Rva006BE2E0Copy(last, _M_finish, first, &temp, 0);
	for (; i != _M_finish; ++i)
		i->m_1C.release();
	_M_finish = i;
	return first;
}
