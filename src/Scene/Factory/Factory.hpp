#pragma once

#include <nlohmann/json.hpp>
#include <cstdint>

#include "Dictionary.hpp"

namespace isim
{
class Transform;
class Factory
{
public:
	virtual ~Factory() = default;

	virtual Transform* New(const nlohmann::json& json) const = 0;

	virtual std::uint32_t size() const = 0;
};

template <typename T>
class ObjectFactory : public Factory
{
public:
	ObjectFactory(const std::string& name)
	{
		TheFactories.Register(name, this);
	}

	virtual Transform* New(const nlohmann::json& json) const override
	{
		return new T(json);
	}

	virtual std::uint32_t size() const override
	{
		return sizeof(T);
	}
};
};