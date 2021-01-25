#include "Warehouse.h"

Warehouse::Warehouse(City* city) : _city(city)
{
	std::thread f1(&Warehouse::sellProduct<decltype(CarsTypes::ORE)>, this, CarsTypes::ORE);
	std::thread f2(&Warehouse::sellProduct<decltype(CarsTypes::WOOD)>, this, CarsTypes::WOOD);
	std::thread f3(&Warehouse::sellProduct<decltype(CarsTypes::LIQUID)>, this, CarsTypes::LIQUID);
	f1.detach();
	f2.detach();
	f3.detach();

	std::cout << "new warehouse" << std::endl;
}

template<class T>
void Warehouse::sellProduct(T resource)
{
	_city->_mu.lock();
	std::cout << "sellProduct" << std::endl;
	size_t resource_count = 0;
	_city->_mu.unlock();
	while (true)
	{
		_city->_mu.lock();
		resource_count = _city->getResources()[resource];
		if (SELL_PRODUCT/1000 > resource_count)
		resource_count -= SELL_PRODUCT++/1000;
		_city->_mu.unlock();
		sleep(rand() % 10 + 1);
	}
}

