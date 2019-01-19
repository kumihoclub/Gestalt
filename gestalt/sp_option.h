#pragma once

#include "sp_common.h"

template <typename T> 
class opt {
public:
	opt(T val);
	bool valid() const { return m_valid; }
	const T& get() { if (m_valid) return m_value; throw; }
private:
	b32 m_valid; 
	T m_value; 
};