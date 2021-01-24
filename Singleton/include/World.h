#pragma once

#include <iostream>
#include <unordered_map>
#include "City.h"
#include "TrainFactory.h"
#include "PassengerTrainFactory.h"
#include "FreightTrainFactory.h"

class World
{
 public:

	TrainFactory* _freighTtrainFactory = new FreightTrainFactory;
	TrainFactory* _passengerTtrainFactory = new PassengerTrainFactory;

 private:
	std::unordered_map<std::string, City*> _cities;

 public:
	static World* GetWorld();

	World(World& other) = delete;//запрещает клониррование
	void operator=(const World&) = delete;//удаляет присваивание

	bool buildCity(const std::string& city_name, const std::string& resources_factory_type);

	bool buyFreightTrain(const std::string& city_name, const std::string& resources_factory_type, size_t cars_count);
	bool buyPassengerTrain(const std::string& city_name, const std::string& resources_factory_type, size_t cars_count);

 protected:
	static World* _world;

 protected:
	World();

};
