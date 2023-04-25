#pragma once
inline int global ;
class Test {
	inline static int m_Data = 50 ; //static variable initialization in .h
	constexpr static int PATHSIZE=  255 ; //constexpr static member variable is implicitly inline
	int x = 5 ; //usual way to initialize a normal variable
};