#pragma once
#ifndef INCLUDED_CANVAS_H
#define INCLUDED_CANVAS_H

#include "qwidget.h"
#include "qpainter.h"
#include "qpixmap.h"
#include "qtransform.h"

class ViewMediator;
class CADShape;
class Manager;

class Canvas : public QWidget
{
	Q_OBJECT

	QPainter painter;
	QPixmap pixmap;

   ViewMediator* mediator;

	bool drawing;

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override; 

public:
	~Canvas()= default;
	Canvas(ViewMediator* _mediator, QWidget* parent);

	QPixmap& getPixmap() { return pixmap;}

   void setDrawing(bool flag) { drawing = flag; }

	void callLine() const;
	void callBezier() const;
	void callArc() const;

   void toggleTracking();
   void clearMap();
   void endPainter();

	void drawCanvas(CADShape& shape);
	void drawMap(CADShape& shape);

	QPainterPath getDrawPath(CADShape& shape);
};

#endif //  INCLUDED_CANVAS_H