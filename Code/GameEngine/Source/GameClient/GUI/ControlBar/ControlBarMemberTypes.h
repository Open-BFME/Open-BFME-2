#pragma once
// The two ControlBar members held by value whose types every ControlBar.cpp
// view needs complete (the TU's files share one ControlBar layout).
//
// +0x30: the ctor (0x0031E94C) builds it through hash_map<int, T>() rowed at
// 0x0031E92D, which calls the hashtable constructor rowed at 0x0031DBFC; reset
// (0x0031E09E) walks and clears it. The int key and the eight-byte mapped type
// are the STL sweep rows' spelling (structural); ControlBarReloadNotice views
// the same map keyed by AsciiString, so the real key is still open.
//
// +0x2A4: the holder reset and update release through clear (0x000AD6F4); the
// ctor nulls its pointer in member order (an inline default ctor). Its pointee
// type is unknown.
#include <hash_map>

struct Rva0031DBFCElement
{
	Rva0031DBFCElement();
	Rva0031DBFCElement(const Rva0031DBFCElement &);
	Rva0031DBFCElement &operator=(const Rva0031DBFCElement &);
	~Rva0031DBFCElement() {}
	char m_data[8];
};

class Rva000AD6F4
{
public:
	Rva000AD6F4() : m_ptr(0) {}
	~Rva000AD6F4();
	void clear();
private:
	void *m_ptr; // +0x00
};
