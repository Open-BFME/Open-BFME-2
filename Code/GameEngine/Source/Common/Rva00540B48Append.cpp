// cl: /O1 /Oy- /DNDEBUG /MD /EHsc /G7 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?append@Rva00540B48@@QAEXHABVRva0053FDE6@@@Z @0x0054098B 155B (ret 8):
// insert-or-update on the sorted key map the chunk reader 0x00540B48 fills.
// Negative keys are ignored. The banked 0x0054034A locator (pinned) finds
// the key and leaves its slot in the hint at +0x1C: a hit brackets the
// value assignment with listener slots 2 and 4, a miss brackets inserting a
// fresh entry after the hint (rowed 0x0054001B ctor, rowed vector insert
// 0x00540731) with slots 0 and 3. Each notification goes through the rowed
// forEach 0x005402DC on the listener list at +0x00 with this and the key;
// the four member pointers are the pinned VC7.1 vcall thunks. The vector's
// begin is read before the entry is built (kept across the call in the dead
// key slot), the hint after. The value assignment is the 9-dword
// Rva0053FDE6 operator= retail folds at 0x0053FFCE (called, not inlined).
// Identity is not recovered: names follow the existing pins and the
// neighbouring Rva0054034ALocate.cpp.

// Retail calls the 9-dword assignment at 0x0053FFCE, rowed as
// Render2DSentenceClass::SentenceDataStruct::operator= (render2dsentence.cpp);
// this /Oy- unit would emit a framed copy, so it calls the row by name.
#include "../../../Libraries/Source/WWVegas/WW3D2/Render2DSentenceClass.h"

class Rva0053FDE6
{
public:
	__declspec(dllimport) __forceinline Rva0053FDE6 &operator=(const Rva0053FDE6 &o)
	{
		*(Render2DSentenceClass::SentenceDataStruct *)this = *(const Render2DSentenceClass::SentenceDataStruct *)&o;
		return *this;
	}
	int m_00;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	float m_1c;
	float m_20;
};

#include "../../Include/Common/Rva0054000B.h"

namespace _STL
{
	template <class T>
	class allocator
	{
	};
	template <class T, class A>
	class vector
	{
	public:
		T *begin() { return m_start; }
		T *insert(T *position, const T &x);
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

class Rva005402DCListener
{
public:
	virtual void slot0(void *, int);
	virtual void slot1(void *, int);
	virtual void slot2(void *, int);
	virtual void slot3(void *, int);
	virtual void slot4(void *, int);
};

class Rva005402DCList
{
public:
	void forEach(void (Rva005402DCListener::*notify)(void *, int), void *arg, int value);
private:
	Rva005402DCListener **m_begin;
	Rva005402DCListener **m_end;
	Rva005402DCListener **m_capacity;
	unsigned int m_index;
};

#include "../../Include/Common/Rva0054034A.h"

class Rva00540B48
{
public:
	void append(int key, const Rva0053FDE6 &value);
private:
	Rva005402DCList m_listeners;										// +0x00
	_STL::vector<Rva0054000B, _STL::allocator<Rva0054000B> > m_entries;	// +0x10
	int m_hint;															// +0x1C
};

void Rva00540B48::append(int key, const Rva0053FDE6 &value)
{
	if (key < 0)
		return;
	if (reinterpret_cast<Rva0054034A *>(this)->rva0054034A(key))
	{
		m_listeners.forEach(&Rva005402DCListener::slot2, this, key);
		m_entries.begin()[m_hint].m_04 = value;
		m_listeners.forEach(&Rva005402DCListener::slot4, this, key);
	}
	else
	{
		m_listeners.forEach(&Rva005402DCListener::slot0, this, key);
		Rva0054000B *begin = m_entries.begin();
		m_entries.insert(begin + (m_hint + 1), Rva0054000B(key, value));
		m_listeners.forEach(&Rva005402DCListener::slot3, this, key);
	}
}
