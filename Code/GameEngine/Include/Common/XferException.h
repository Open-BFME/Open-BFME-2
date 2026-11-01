// Target facts (code RVAs, metadata VAs): the throw at 0x00587347..0x00587358 calls the variadic constructor 0x0060C36E and uses ThrowInfo 0x00CFFD18. Its sole catchable type at 0x00CFFCF4 names .?AVXferException@@ (type descriptor 0x00DB3F80), size 8 and copy constructor 0x000588C5; ThrowInfo names destructor 0x0002BD30. XferException has no virtual functions or base subobject in retail.
// Constructor 0x0060C378 clears the pointer at +0, 0x0060C37F stores its int argument at +4, and 0x0060C3AC..0x0060C3B8 stores an allocated, terminated character buffer at +0. Copy constructor 0x000588C5 clears +0 and calls assignment 0x0002F6D6; assignment deep-copies +0 and copies the dword at +4 (0x0002F70F..0x0002F712). Destructor 0x0002BD30 deletes the array at +0. None stores a vptr.
// INIException's distinct ThrowInfo 0x00CFE2FC names its own type descriptor 0x00DA7554 but shares the copy, assignment and destructor bodies with XferException. These are exception metadata tables, not class vtables. ThrowInfo 0x00D00D44 names the nested .?AW4__unnamed@XferException@@ (type descriptor 0x00DB4154), a 4-byte enum thrown with value 2 at 0x000D2156..0x000D215D and 0x00068543..0x0006854A. Field and enumerator identifiers below are neutral because retail establishes storage and values, not their original names.

#pragma once

#ifndef BFME2_XFEREXCEPTION_H
#define BFME2_XFEREXCEPTION_H

class XferException
{
public:
	enum { XFER_EXCEPTION_BFME_2 = 2 };

	XferException(int, const char *, ...);
	XferException(const XferException &);
	~XferException();
	XferException &operator=(const XferException &);

	char *m_xferField00;
	int m_xferField04;
};

#endif
