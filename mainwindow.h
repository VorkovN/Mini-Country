#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include "World.h"
#include "CommandExecuter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	static bool flag;
    MainWindow(QWidget *parent = nullptr);
    bool loop();
    ~MainWindow();

private slots:
    void on_executeButton_clicked();
	void slotTimerAlarm();

private:
    Ui::MainWindow *ui;
	QTimer *timer;
	World* _world = World::getCreatedWorld();
	CommandExecuter _commandExecuter;

};
#endif // MAINWINDOW_H