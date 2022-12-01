#include "Dictionary.hpp"

namespace isim
{
FactoryDictionary TheFactories;

void FactoryDictionary::Register(const std::string& name, const Factory* factory)
{
	m_factories[name] = factory;
}

const Factory* FactoryDictionary::operator[](const std::string& name)
{
	return m_factories[name];
}

};