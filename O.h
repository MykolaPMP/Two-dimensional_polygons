#pragma once

#ifdef O_EXPORTS   
#define O_API __declspec(dllexport)    
#else   
#define O_API __declspec(dllimport)    
#endif   

using namespace std;

namespace O
{

	class Functions
	{
	public:
		// Returns a + b  
		static O_API double Add(double a, double b);

		// Returns a * b  
		static O_API double Multiply(double a, double b);

		// Returns a + (a * b)  
		static O_API double AddMultiply(double a, double b);
	};
	
class Point { protected:  double x;  double y; public:
  Point()  {   x = INT_MIN;   y = INT_MIN;  }
  Point(const Point& _point)  {   x = _point.x;   y = _point.y;  }
  Point(double _x, double _y) :x(_x), y(_y)  {
  }
  double get_x()const  {   return x;  }
  double get_y()const  {   return y;  }
  void set_x(double _x)  {   x = _x;  }
  void set_y(double _y)  {   y = _y;  }
  Point& operator=(const Point& object)  {   x = object.x;   y = object.y;   return *this;  }
  Point& operator+=(const Point& delta)  {   x += delta.x;   y += delta.y;   return *this;  }
  Point operator+(const Point& delta)  {   Point result(x, y);   result += delta;   return result;;  }
  Point& operator-=(const Point& delta)  {   x -= delta.x;   y -= delta.y;   return *this;  }
  Point operator-(const Point& delta)  {   Point result(x, y);   result -= delta;   return result;  }    friend Point& operator * (double skalar, Point& delta)  {   delta.x *= skalar;   delta.y *= skalar;   return delta;  }
  ~Point()  {
  }
  void print()  {   if (x != INT_MIN && y != INT_MIN)   {    cout << '(' << x << "," << y << ") ";   }   else   {    cout << "NULL" << endl;   }  } };

	struct Vertex
	{
		Point point;
		Vertex *next;
		Vertex *previous;
		void print()
		{
			point.print();
		}
		Vertex(Point _point)
		{
			point.set_x(_point.get_x());
			point.set_y(_point.get_y());

			next = NULL;
			previous = NULL;
		}
		Point& get_point()
		{
			return point;
		}
	};





}
