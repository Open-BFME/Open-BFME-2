// Xfer::Version is the current and minimum version pair a snapshot transfers; BfmeXfer.h forward-declares it.
#pragma once
#ifndef BFME_XFER_VERSION_H
#define BFME_XFER_VERSION_H

#include "BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

#endif
