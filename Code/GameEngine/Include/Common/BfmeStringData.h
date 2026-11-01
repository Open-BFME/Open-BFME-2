// BfmeStringData is the reference-counted buffer behind the engine string classes; T is the character type.
#pragma once
#ifndef BFME_STRING_DATA_H
#define BFME_STRING_DATA_H

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#endif
