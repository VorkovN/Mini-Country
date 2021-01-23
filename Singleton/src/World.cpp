#include "World.h"
#include <iostream>
#include <utility>

World* World::_world = nullptr;

World::World()
{
	std::cout << "World created" << std::endl;
}

bool World::buildCity(const std::string& city_name, const std::string& resources_factory_type)
{
	if (!_cities.contains(city_name))
		_cities.insert({ city_name, new City(city_name, resources_factory_type) });
	else
		return false;
	std::cout << "build_city " << city_name << " " << resources_factory_type << std::endl;
	return true;
}

bool World::buyTrain(const std::string& city_name, const std::string& cars_type, size_t cars_count)
{
	Train* train = new Train(Resources::getResourcesMap(cars_type), cars_count);
	if(_cities.find(city_name) == _cities.end())
		return false;
	City * city = _cities.at(city_name);
	city->getRailwayStation().push_back(train);

	std::cout << _cities.at(city_name)->getRailwayStation().back()->_cars_count
	   << " " << _cities.at(city_name)->getRailwayStation().back()->_cars_types;
	std::cout << "buy_train " << city_name << " " << cars_type << " " << cars_count << std::endl;
	return true;
}

World* World::GetWorld()
{
	if (_world == nullptr)
		_world = new World();
	return _world;
}
