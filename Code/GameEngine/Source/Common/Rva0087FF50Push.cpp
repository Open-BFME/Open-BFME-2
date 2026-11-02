// cl: /Ob0

struct BfmeTail50
{
	void copyFrom(const BfmeTail50 *src);
};

struct BfmeElem50
{
	int m_00;
	int m_04;
	int m_08;
	BfmeTail50 m_0C;
};

struct BfmeFalse50
{
};

class BfmeVec50
{
public:
	void push_back(const BfmeElem50 *value);
	void overflow(BfmeElem50 *pos, const BfmeElem50 &value,
		const BfmeFalse50 &, unsigned fill, bool atEnd);

	BfmeElem50 *_M_start;
	BfmeElem50 *_M_finish;
	BfmeElem50 *_M_end_of_storage;
};

void BfmeVec50::push_back(const BfmeElem50 *value)
{
	if (_M_finish != _M_end_of_storage)
	{
		BfmeElem50 *newSlots = _M_finish;
		if (newSlots)
		{
			const BfmeElem50 *valueSource = value;
			newSlots->m_00 = valueSource->m_00;
			newSlots->m_04 = valueSource->m_04;
			newSlots->m_08 = valueSource->m_08;
			newSlots->m_0C.copyFrom(&valueSource->m_0C);
		}
		++_M_finish;
	}
	else
	{
		overflow(_M_finish, *value, reinterpret_cast<const BfmeFalse50 &>(value), 1, true);
	}
}
