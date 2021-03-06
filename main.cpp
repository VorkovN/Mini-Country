#include <QApplication>
#include <QPushButton>
#include <iostream>
#include <vector>
#include "mainwindow.h"

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
поезда можно продавать в любом городе за половину цены от покупки

реализовано:
Паттерны: Singleton, Commander, Factory
Шаблоны (создаются потоки из шаблонной функции для разных типов ресурсов)
Виртуальные методы и виртуальные деструкторы (для Train и TrainFactory)
Различные виды константности (везде)
Переопределение операторов
Разные контейнеры(map, unordered_map, list) изначально в vector хранились потоки, но valgrind ругался на закрытие потоков извне и смысл хранения потоков потерялся
Статические поля и методы ()
Умные указатели shared_ptr ()
Наслеование - реализовано только public. Private и Protected скрывают конструктор от других классов, что делает использование этх типов неуместным в рамках моей программы
Инкапсуляция - все поля и методы скрыты на максимум
Полиморфизм - следует из шаблона Factory, нет разницы в интерфейсе грузового и пассажирского поездов, но принцип работы различен
Библиотека Qt
Потоки для реализации изменения кол-ва ресурсов города параллельно работе ввода команд
Мьютексы для корректного обращения потоков к общим ресурсам города

Возникающие проблемы:
1)Выбрасывание ошибки в потоке
2)Невозможность корректо завершить программу из побочного потока
3)Наследование Enum
4)shared_ptr и приватные поля
5)Сильная связность класса City

**/

int main(int argc, char* argv[])
{
	srand(time(nullptr));
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return QApplication::exec();
}
