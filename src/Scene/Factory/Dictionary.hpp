#pragma once

#include <string>
#include <memory>
#include <map>

namespace isim
{
class Factory;
template <typename T>
class ObjectFactory;

class FactoryDictionary
{
	template <typename T> friend
	class ObjectFactory;

	void Register(const std::string& name, const Factory* factory);

	std::map<std::string, const Factory*> m_factories;

public:
	FactoryDictionary() = default;

	const Factory* operator[](const std::string& name);
};

extern FactoryDictionary TheFactories;
};