// cl: /O1 /MD
//
// Leaf guarded-delete helpers for the Rva003B4071 double helper (rowed
// ?clear@Rva003B4071@@QAEXXZ in OpaqueScalarDeletingDtors.cpp). Each leaf
// holds the head of its own chain at +0 and drops it recursively:
// if the head is present, clear it first, then free it. Shard TU on
// purpose: defining these bodies next to the double helper would give the
// compiler same-TU visibility into them and perturb its emission.

class Rva003B31DF
{
public:
	void clear();

private:
	Rva003B31DF *m_next;
};

void Rva003B31DF::clear()
{
	Rva003B31DF *next = m_next;
	if (next != 0) {
		next->clear();
		operator delete(next);
	}
}

class Rva003B3204
{
public:
	void clear();

private:
	Rva003B3204 *m_next;
};

void Rva003B3204::clear()
{
	Rva003B3204 *next = m_next;
	if (next != 0) {
		next->clear();
		operator delete(next);
	}
}
