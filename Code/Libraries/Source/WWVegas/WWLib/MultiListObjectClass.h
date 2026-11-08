// Target facts (game.dat; method addresses are RVAs): ~MultiListObjectClass 0x006109C0 stores VA 0x00BC5C6C at +0 and removes every node through GenericMultiListClass::Internal_Remove 0x00610930. The table's sole slot is scalar deleting destructor 0x000657E6, which calls 0x006109C0 then conditionally operator delete 0x0002FD60; VA 0x00BC5C70 begins GenericMultiListClass's separate table, installed by constructor 0x00065815. There are no additional virtual slots or base subobjects in this layout.
// Target layout: destructor 0x006109C0 reads the node pointer at +4; Internal_Add_Tail 0x00610820 reads/writes that pointer and links it through the node's +8 NextList. CameraShakerClass constructor 0x00065A39 and DX8TextureCategoryClass constructor 0x00144A00 clear +4 inline, install their own tables (VA 0x00BC5C74 and 0x00BD3508) at +0 and start their own data at +8, bounding sizeof at 8. CameraShakerClass destructor 0x000658BA restores its own table then tail-calls 0x006109C0.
// Donor names and inline accessors: Zero Hour GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h names ListNode, Get_List_Node and Set_List_Node; their single-pointer operations agree with retail 0x00610820 and 0x00610930. The donor header is not included. The rowed virtual destructor is declared out of line.
#pragma once

#ifndef BFME2_MULTI_LIST_OBJECT_CLASS_H
#define BFME2_MULTI_LIST_OBJECT_CLASS_H

// One definition for both header families: Zero Hour's multilist.h (which rendobj.h reaches) defines this class
// too, under MULTILIST_H; when it is already in, it wins and this header adds nothing. Include-order trade-off: a
// unit that needs both families must include the Zero Hour side (rendobj.h) first; reaching this header first and
// multilist.h later still defines the classes twice.
#ifndef MULTILIST_H

class MultiListNodeClass;

class MultiListObjectClass
{
public:
	MultiListObjectClass() : ListNode(0) {}
	virtual ~MultiListObjectClass();

	MultiListNodeClass *Get_List_Node() const { return ListNode; }
	void Set_List_Node(MultiListNodeClass *node) { ListNode = node; }

private:
	MultiListNodeClass *ListNode;
};

#endif // MULTILIST_H
#endif
