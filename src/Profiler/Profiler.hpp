#pragma once

#include <chrono>
#include <cstdint>
#include <iostream>

namespace isim
{
class Profiler
{
public:
	Profiler(const char* name)
	{
		m_start = std::chrono::system_clock::now();
		m_name = name;
		m_count++;
	}
	Profiler()
	{
		m_start = std::chrono::system_clock::now();
		m_name = "";
		m_count++;
	}
	~Profiler()
	{
		std::cout << '[' << m_count << ']' << '[' << std::chrono::duration_cast<std::chrono::nanoseconds>((std::chrono::system_clock::now() - m_start)).count() << "ns]" << m_name << '\n';
		m_count--;
		if (!m_count)
		{
			std::cout << std::endl;
		}
	}
private:
	std::chrono::time_point<std::chrono::system_clock> m_start;
	const char* m_name;
	static std::uint32_t m_count;
};
};