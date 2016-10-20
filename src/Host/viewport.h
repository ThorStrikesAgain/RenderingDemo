#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QtWidgets/QOpenGlWidget>

class Viewport : public QOpenGLWidget
{
	Q_OBJECT

public:
	Viewport(QWidget *parent = 0);
	virtual ~Viewport();

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;
};

#endif VIEWPORT_H
