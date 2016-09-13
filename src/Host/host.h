#ifndef HOST_H
#define HOST_H

#include <QtWidgets/QMainWindow>
#include "ui_host.h"

class Host : public QMainWindow
{
	Q_OBJECT

public:
	Host(QWidget *parent = 0);
	~Host();

private:
	Ui::HostClass ui;
};

#endif // HOST_H
