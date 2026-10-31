#pragma once

// Shared private view of retail's rts hash helpers: the order files in this
// directory each carried a private copy that cannot coexist in one TU. The
// primary identity operator is the existing MoveToFormationGroupOrder view.
// Explicit specializations stay beside the key types they name; their code
// is independent of this primary. Template spelling remains a donor lead,
// not recovered original target source identity.
#include <cstddef>

namespace rts
{

template <class _Key>
struct hash
{
	size_t operator()(const _Key &value) const
	{
		return (size_t)value;
	}
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
