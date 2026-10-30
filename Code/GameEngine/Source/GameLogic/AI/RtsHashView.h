#pragma once

// Shared private view of retail's rts hash helpers: the order files in this
// directory each carried a private copy that cannot coexist in one TU. The
// primary is empty (as in MoveToGroupOrder.cpp); specializations stay beside
// the private key types they name.
namespace rts
{

template <class _Key>
struct hash
{
};

template <class _Key>
struct equal_to
{
	bool operator()(const _Key &left, const _Key &right) const
	{
		return left == right;
	}
};

}
