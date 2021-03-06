#include "World.h"
#include <iostream>
#include <utility>

World* World::_world = nullptr;
bool  World::ALIVE_WORLD = true;

World::World()
{
}

bool World::buildCity(const std::string& city_name, CarsTypes::Types resources_factory_type)
{
	if (!_cities.contains(city_name))
	{
		_cities.insert({ city_name, new City(city_name, resources_factory_type) });
	}
	else
	{
		std::cerr << "city " << city_name <<" already exist" << std::endl;
		return false;
	}

	return true;
}

bool World::buyTrain(const std::string& city_name, CarsTypes::Types cars_type, size_t cars_count)
{
	if (!_cities.contains(city_name))
	{
		std::cerr << "city " << city_name <<" doesn't exist" << std::endl;
		return false;
	}

	City* city = _cities.at(city_name);

	const size_t required_budget = Train::car_price[cars_type] * cars_count;
	if(city->getBudget() < required_budget)
	{
		std::cerr << "Not enough money, city budget: " << city->getBudget() <<", required budget: " << required_budget << std::endl;
		return false;
	}


	city->setBudget(city->getBudget() - Train::car_price[cars_type] * cars_count);

	Train* train;
	if (cars_type < 0)
		train = _world->_passengerTtrainFactory->createTrain(cars_type, cars_count);
	else
		train = _world->_freighTtrainFactory->createTrain(cars_type, cars_count);
	city->getRailwayStation()[cars_type].push_back(train);

	return true;
}

bool World::sendTrain(const std::string& name_city_from, const std::string& name_city_to, CarsTypes::Types cars_type, size_t cars_count)
{
	if (!_cities.contains(name_city_from))
	{
		std::cerr << "city " << name_city_from <<" doesn't exist" << std::endl;
		return false;
	}

	if (!_cities.contains(name_city_to))
	{
		std::cerr << "city " << name_city_to <<" doesn't exist" << std::endl;
		return false;
	}

	City* city_from = _cities.at(name_city_from);
	City* city_to = _cities.at(name_city_to);

	if (city_from->getRailwayStation()[cars_type].empty())
	{
		std::cerr << "railway station hasn't any trains of this type" << std::endl;
		return false;
	}

	Train* train = city_from->getRailwayStation()[cars_type].front();

	for (Train* cur_train: city_from->getRailwayStation()[cars_type])
		if (cars_count <= cur_train->getCarsCount() && cur_train < train)
			train = cur_train;

	train->move(city_from, city_to, cars_count);
	return true;
}

bool World::sellTrain(const std::string& city_name, CarsTypes::Types cars_type, size_t cars_count)
{
	if (!_cities.contains(city_name))
	{
		std::cerr << "city " << city_name <<" doesn't exist" << std::endl;
		return false;
	}

	City* city = _cities.at(city_name);

	if (city->getRailwayStation()[cars_type].empty())
	{
		std::cerr << "railway station hasn't any trains of this type" << std::endl;
		return false;
	}

	for (Train* cur_train: city->getRailwayStation()[cars_type])
		if (cur_train->getCarsCount() == cars_count && cur_train->getCarsType() == cars_type){
			city->getRailwayStation()[cars_type].remove(cur_train);
			city->setBudget(city->getBudget() + (Train::car_price[cars_type] * cars_count) / 2);
			delete cur_train;
			std::cout << "train sold" << std::endl;
			return true;
		}
	std::cerr << "such train doesn't exist" << std::endl;
	return false;
}

bool World::showProducts(const std::string& city_name)
{
	if (!_cities.contains(city_name))
	{
		std::cerr << "city " << city_name <<" doesn't exist" << std::endl;
		return false;
	}

	City* city = _cities.at(city_name);

	std::cout << std::endl;
	std::cout << "ore: " << city->getResources()[CarsTypes::ORE] << std::endl;
	std::cout << "wood: " << city->getResources()[CarsTypes::WOOD] << std::endl;
	std::cout << "liquid: " << city->getResources()[CarsTypes::LIQUID] << std::endl;
	return true;
}

bool World::showTrains(const std::string& city_name)
{
	if (!_cities.contains(city_name))
	{
		std::cerr << "city " << city_name <<" doesn't exist" << std::endl;
		return false;
	}

	City* city = _cities.at(city_name);

	std::cout << std::endl;
	std::cout << "bilevel: " << city->getRailwayStation()[CarsTypes::BILEVEL].size() << std::endl;
	std::cout << "simple: " << city->getRailwayStation()[CarsTypes::SIMPLE].size() << std::endl;
	std::cout << "ore: " << city->getRailwayStation()[CarsTypes::ORE].size() << std::endl;
	std::cout << "wood: " << city->getRailwayStation()[CarsTypes::WOOD].size() << std::endl;
	std::cout << "liquid: " << city->getRailwayStation()[CarsTypes::LIQUID].size() << std::endl;
	return true;
}

bool World::showFactories()
{
	std::cout << std::endl;
	for (std::pair<std::string, City*> city: _world->getCities())
		std::cout << *city.second->getName() << ": " << city.second->getResourcefactory()->getResource() << std::endl;
	std::cout << std::endl;
	return true;
}

bool World::showPopulation()
{
	std::cout << std::endl;
	for (std::pair<std::string, City*> city: _world->getCities())
		std::cout << *city.second->getName() << ": " << city.second->getPopulation() << std::endl;
	std::cout << std::endl;
	return true;
}

bool World::showBudget()
{
	std::cout << std::endl;
	for (std::pair<std::string, City*> city: _world->getCities())
		std::cout << *city.second->getName() << ": " << city.second->getBudget() << std::endl;
	std::cout << std::endl;
	return true;
}

World* World::getCreatedWorld()
{
	if (_world == nullptr)
		_world = new World;
	return _world;
}

World::~World()
{
	delete _freighTtrainFactory;
	delete _passengerTtrainFactory;
	for (auto &[str, city]: _cities)// к сожалению есть только в с++ 20
		delete city;
	exit(0);
}

std::unordered_map<std::string, City*>& World::getCities()
{
	return _cities;
}




