#pragma once

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <gtest/gtest.h>

inline nlohmann::json TEST_JSON_OPEN(const std::string& path)
{
	std::fstream file(path);
	assert(file.is_open());
	return nlohmann::json::parse(file);
}
