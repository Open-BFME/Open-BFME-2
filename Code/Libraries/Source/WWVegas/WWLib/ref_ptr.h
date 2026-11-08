// Target facts (code addresses are RVAs): RefCountPtr<T> is one T* (Referent). Its destructor is
// 0x0017098D (`if (Referent) Referent->Release_Ref();`, a tail call to TextureClass::Release_Ref
// 0x0061ED10; about 50 holder destructors fold onto it) and, for a T whose Release_Ref is inline
// RefCountClass's, 0x0007B724. The copy constructor 0x000424BB stores rhs's referent, then Add_Refs it
// if it is not null. operator=(const RefCountPtr &) 0x000424D0 Add_Refs rhs first, Release_Refs the old
// referent, then assigns. ??_E 0x0004559C shows arrays of RefCountPtr<TextureClass>.
// Donor facts: the template is Zero Hour's WWLib/ref_ptr.h (GeneralsMD), whose bodies match every retail
// body above (reverse/attempt_support/p23_refcountptr/readme.md). Zero Hour's WWASSERT/G_ASSERT checks
// are release no-ops and are left out; its FAIL_IF tests are plain ifs. Nothing else is changed.
#pragma once

#ifndef BFME2_WWLIB_REF_PTR_H
#define BFME2_WWLIB_REF_PTR_H

class DummyPtrType;

template <class T>
class RefCountPtr
{
public:
	friend RefCountPtr<T> Create_NEW(T *t)
	{
		return RefCountPtr<T>(t, RefCountPtr<T>::GET);
	}

	friend RefCountPtr<T> Create_Get(T *t)
	{
		return RefCountPtr<T>(t, RefCountPtr<T>::GET);
	}

	friend RefCountPtr<T> Create_Peek(T *t)
	{
		return RefCountPtr<T>(t, RefCountPtr<T>::PEEK);
	}

	RefCountPtr(void)
		: Referent(0)
	{
	}

	RefCountPtr(DummyPtrType *)
		: Referent(0)
	{
	}

	template <class RHS>
	RefCountPtr(const RefCountPtr<RHS> &rhs)
		: Referent(rhs.Peek())
	{
		if (Referent) {
			Referent->Add_Ref();
		}
	}

	RefCountPtr(const RefCountPtr &rhs)
		: Referent(rhs.Referent)
	{
		if (Referent) {
			Referent->Add_Ref();
		}
	}

	const RefCountPtr<T> &operator =(DummyPtrType *)
	{
		if (Referent) {
			Referent->Release_Ref();
		}
		Referent = 0;
		return *this;
	}

	template <class RHS>
	const RefCountPtr<T> &operator =(const RefCountPtr<RHS> &rhs)
	{
		if (rhs.Peek()) {
			rhs.Peek()->Add_Ref();
		}
		if (Referent) {
			Referent->Release_Ref();
		}
		Referent = rhs.Peek();
		return *this;
	}

	const RefCountPtr<T> &operator =(const RefCountPtr &rhs)
	{
		if (rhs.Referent) {
			rhs.Referent->Add_Ref();
		}
		if (Referent) {
			Referent->Release_Ref();
		}
		Referent = rhs.Referent;
		return *this;
	}

	~RefCountPtr(void)
	{
		if (Referent) {
			Referent->Release_Ref();
		}
	}

	// Tests against null without a conversion to T *.
	operator const DummyPtrType *(void) const
	{
		return (DummyPtrType *)(Referent);
	}

	void Clear(void)
	{
		if (Referent) {
			Referent->Release_Ref();
			Referent = 0;
		}
	}

	T *operator ->(void) const
	{
		return Referent;
	}

	T &operator *(void) const
	{
		return *Referent;
	}

	T *Peek(void) const
	{
		return Referent;
	}

private:
	enum ReferenceHandling { GET, PEEK };

	RefCountPtr(T *referent, ReferenceHandling reference_handling)
		: Referent(referent)
	{
		if (reference_handling == PEEK && 0 != referent) {
			referent->Add_Ref();
		}
	}

	T *Referent;
};

template <class LHS, class RHS>
bool operator ==(const RefCountPtr<LHS> &lhs, const RefCountPtr<RHS> &rhs)
{
	return lhs.Peek() == rhs.Peek();
}

template <class LHS, class RHS>
bool operator <(const RefCountPtr<LHS> &lhs, const RefCountPtr<RHS> &rhs)
{
	return lhs.Peek() < rhs.Peek();
}

template <class RHS>
bool operator ==(DummyPtrType *dummy, const RefCountPtr<RHS> &rhs)
{
	if (0 != dummy) {
		return false;
	}
	return 0 == rhs.Peek();
}

template <class RHS>
bool operator !=(DummyPtrType *dummy, const RefCountPtr<RHS> &rhs)
{
	if (0 != dummy) {
		return true;
	}
	return 0 != rhs.Peek();
}

template <class Derived, class Base>
RefCountPtr<Derived> Static_Cast(const RefCountPtr<Base> &base)
{
	return Create_Peek((Derived *)base.Peek());
}

#endif
