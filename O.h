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
