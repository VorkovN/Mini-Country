#include <iostream>
#include <vector>
#include "World.h"
#include "CommandExecuter.h"


int main()
{
	srand(time(nullptr));
	World* world = World::GetWorld();
	std::cout << "Input you command (command help can help you)" << std::endl;
	CommandExecuter commandExecuter;
	while (true)
	{
		std::string command_word, arg;
		std::vector<std::string> args_vector;
		std::cin >> command_word;

		const auto command = commandExecuter.getCommands().find(command_word);

		if (command != commandExecuter.getCommands().end())
		{
			while (std::cin.peek() != '\n')
			{
				std::cin >> arg;
				args_vector.push_back(arg);
			}

			if (args_vector.empty())
			{
				if (!command->second->execute())
					std::cout << "execute error" << std::endl;
			}

			else
			{
				if (!command->second->execute(args_vector))
					std::cout << "execute error" << std::endl;
			}

		}
		else
		{
			std::cout << "command type error" << std::endl;
		}
	}
	return 0;
}


/**
есть возможность строить города,
в каждом городе есть завод,
в каждом городе может быть только один завод,
завод автоматически генерируется при строительстве города,
заводы производят продукт,
потребитель запрашивает продукт на складе,
склад автоматически генерируется при строительстве города,
если есть, потребитель покупает продукт, если нет, то игра заканчивается,
 поэтому необходимо следить за наличием товара  на складе,
за покупку продукта у города увеличивается бюджет,
этот бюджет можно тратить на покупку товарных и пассажирских поездов,
товарные поезда распределяют ресурсы между городами,
пассажирские поезда перераспределяют население в городах
поезда можно покупать разных типов,
разные типы поездов перевозят разные типы ресурсов и разное кол-во людей,
также можно покупать поезда с разным кол-вом вагонов(изменится вместимость, изменится цена),
todo добавить способ продавать поезда за половину цены
todo сделать маломальский графон в qt

реализовано:
Паттерны: Singleton, Commander, Factory
Шаблоны (создаются потоки из шаблонной функции для разных типов ресурсов)
Виртуальные методы и виртуальные деструкторы (для Train и TrainFactory)//todo виртуальные деструкторы
Различные виды константности (везде)
Переопределение операторов //todo переопределить что-нибудь
Разные контейнеры(map, unordered_map, list) //todo еще чего запихнуть
Статические поля и методы ()//поискать в коде
Наслеование - различные типы приватности и наследования //todo различные типы наследования
Инкапсуляция - все поля и методы скрыты на максимум
Полиморфизм - следует из шаблона Factory, нет разницы в интерфейсе грузового и пассажирского поездов, но принцип работы различен
**/


