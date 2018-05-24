#include "PointMapper.h"

#include "CADFile.h"
#include "CADBezier.h"
#include "CADArc.h"

template <typename IterT>
struct Range {
   Range(IterT b, IterT e) : start_(b), end_(e) {}

   IterT begin() { return start_; }
   IterT end() { return end_; }

   IterT start_;
   IterT end_;
};

template <typename IterT>
Range<IterT> make_range(IterT b, IterT e)
{
   return Range<IterT>(b, e);
}

std::vector<CADShape*> PointMapper::transformShapes(CADFile& currentFile)
{
   std::vector<CADShape*> newShapes;

   newShapes.reserve(currentFile.shapesEnd() - currentFile.shapesBegin());

   for (auto shape : make_range(currentFile.shapesBegin(), currentFile.shapesEnd()))
   {
      newShapes.push_back(shape->clone());
   }

   for (auto shape : newShapes) {
      std::vector<Point> points;
      points.push_back(shape->firstPoint());
      points.push_back(shape->secondPoint());
      
      switch (shape->shapeType()) {
      case BEZIER: {
         auto bezier = dynamic_cast<CADBezier&>(*shape);
         points.push_back(bezier.thirdPoint());
         break;
      }
      case ARC: {
         auto arc= dynamic_cast<CADArc&>(*shape); 
         points.push_back(arc.thirdPoint());
         break;
      }
   }
      points= recalculateShapePoints(points);

      shape->setFirstPoint(points.at(0));
      shape->setSecondPoint(points.at(1));

      switch (shape->shapeType()) {
      case BEZIER: {
         auto bezier= dynamic_cast<CADBezier&>(*shape);
         bezier.setThirdPoint(points.at(2));
         break;
      }
      case ARC: {
         auto arc= dynamic_cast<CADArc&>(*shape);
         arc.setThirdPoint(points.at(2));
         break;
      }
      }
   }

   return newShapes;
}

std::vector<Point> PointMapper::recalculateShapePoints(std::vector<Point> points)
{
   std::vector<Point> recalculatedPoints;

   for (auto point : points)
      recalculatedPoints.push_back(Point(point + upperLeftPoint) * zFactor);
   
   return recalculatedPoints;
}

void PointMapper::recalculatePointDeltaPositive(Point& p)
{
   p= (p + (upperLeftPoint)) * zFactor;
}

void PointMapper::recalculatePointDeltaNegative(Point& p)
{
   p= (p - (upperLeftPoint * zFactor)) * zFactor;
}

void PointMapper::setZoomFactor()
{
   if (dFactor < 0) {
      if (zFactor > MINIMUM)
         zFactor--;
      return;
   }
   
   if (dFactor > 0) {
      if (zFactor < MAXIMUM)
         zFactor++;
      return;
   }

   return;
}
