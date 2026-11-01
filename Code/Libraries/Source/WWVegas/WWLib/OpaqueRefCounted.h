// OpaqueRefCounted is a reference-counted object a unit only releases; Release_Ref is the out-of-line retail call.
#pragma once
#ifndef BFME_OPAQUE_REF_COUNTED_H
#define BFME_OPAQUE_REF_COUNTED_H

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

#endif
