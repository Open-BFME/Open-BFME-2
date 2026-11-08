// Target facts (game.dat; method addresses are RVAs): constructor 0x00065815 and destructor 0x00610640 store VA 0x00BC5C70 at +0; its sole slot is scalar deleting destructor 0x0006583C, which calls 0x00610640 then conditionally operator delete 0x0002FD60. VA 0x00BC5C74 starts CameraShakerClass's separate table (0x000658BA stores it). There are no base constructor calls or secondary vptrs.
// The constructor writes five pointer words at +4/+8/+0xC/+0x10/+0x14, self-links +4/+8 and clears the others; DX8MeshRendererClass constructor 0x00145AA0 places consecutive lists at +0x1C/+0x34, bounding sizeof at 0x18. Contains 0x00610650 and Internal_Add 0x006107A0 prove node Prev/Next/NextList/Object/List at +0/+4/+8/+0xC/+0x10; Count 0x00610750 and Is_Empty 0x00065858 traverse the sentinel. BfmeRefSceneList constructor 0x0006E518 calls the constructor; its destructor 0x0006F29B inlines the emptiness test and calls the base destructor.
// Ledger methods: Internal_Add_Tail 0x00610820, Internal_Add_After 0x006108A0, Internal_Remove 0x00610930, Internal_Remove_List_Head 0x006109A0, Internal_Get_List_Head 0x00143DD0. Donor names and Is_In_List forwarding: Zero Hour GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h; the donor is not a BFME2 layout authority.
#pragma once

#ifndef BFME2_GENERIC_MULTILIST_CLASS_H
#define BFME2_GENERIC_MULTILIST_CLASS_H

// One definition for both header families: Zero Hour's multilist.h (which rendobj.h reaches) defines this class
// too, under MULTILIST_H; when it is already in, it wins and this header adds nothing. Include-order trade-off: a
// unit that needs both families must include the Zero Hour side (rendobj.h) first; reaching this header first and
// multilist.h later still defines the classes twice.
#ifndef MULTILIST_H

class GenericMultiListClass;
class MultiListObjectClass;

class MultiListNodeClass
{
public:
	MultiListNodeClass() { Prev = Next = NextList = 0; Object = 0; List = 0; }

	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	MultiListObjectClass *Object;
	GenericMultiListClass *List;
};

class GenericMultiListClass
{
public:
	GenericMultiListClass() { Head.Next = Head.Prev = &Head; Head.Object = 0; Head.NextList = 0; }
	virtual ~GenericMultiListClass();

	bool Is_In_List(MultiListObjectClass *obj) { return Contains(obj); }
	bool Contains(MultiListObjectClass *obj);
	bool Is_Empty() { return Head.Next == &Head; }
	int Count();

	MultiListNodeClass Head;

protected:
	bool Internal_Add(MultiListObjectClass *obj, bool onlyonce = true);
	bool Internal_Add_Tail(MultiListObjectClass *obj, bool onlyonce = true);
	bool Internal_Add_After(MultiListObjectClass *obj, const MultiListObjectClass *existing_list_member, bool onlyonce = true);
	bool Internal_Remove(MultiListObjectClass *obj);
	MultiListObjectClass *Internal_Get_List_Head();
	MultiListObjectClass *Internal_Remove_List_Head();

	friend class GenericMultiListIterator;
	friend class MultiListObjectClass;
};

#endif // MULTILIST_H
#endif
