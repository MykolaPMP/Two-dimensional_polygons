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



	class Point
	{
	protected:
		double x;
		double y;
	public:

		Point()
		{
			x = INT_MIN;
			y = INT_MIN;
		}

		Point(const Point& _point)
		{
			x = _point.x;
			y = _point.y;
		}

		Point(double _x, double _y) :x(_x), y(_y)
		{

		}

		double get_x()const
		{
			return x;
		}

		double get_y()const
		{
			return y;
		}

		void set_x(double _x)
		{
			x = _x;
		}

		void set_y(double _y)
		{
			y = _y;
		}

		Point& operator=(const Point& object)
		{
			x = object.x;
			y = object.y;
			return *this;
		}

		Point& operator+=(const Point& delta)
		{
			x += delta.x;
			y += delta.y;
			return *this;
		}

		Point operator+(const Point& delta)
		{
			Point result(x, y);
			result += delta;
			return result;;
		}

		Point& operator-=(const Point& delta)
		{
			x -= delta.x;
			y -= delta.y;
			return *this;
		}

		Point operator-(const Point& delta)
		{
			Point result(x, y);
			result -= delta;
			return result;
		}
		
		friend Point& operator * (double skalar, Point& delta)
		{
			delta.x *= skalar;
			delta.y *= skalar;
			return delta;
		}

		~Point()
		{

		}

		void print()
		{
			if (x != INT_MIN && y != INT_MIN)
			{
				cout << '(' << x << "," << y << ") ";
			}
			else
			{
				cout << "NULL" << endl;
			}
		}
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

	class Polygon
	{
	protected:
		Vertex* head;
		Vertex* tail;
	public:
		Polygon()
		{
			head = NULL;
			tail = NULL;
		}

		Polygon(const Polygon& object)
		{
			Vertex* ptr = object.head;
			head = NULL;
			tail = NULL;
			while (ptr != NULL)
			{
				push_end(ptr->get_point());
				ptr = ptr->next;
			}
		}

		~Polygon()
		{
			if (head == NULL)
			{
				return;
			}

			Vertex* ptr = head;
			while (ptr != NULL)
			{
				head = head->next;
				delete ptr;
				ptr = head;
			}
		}

		Polygon& operator = (const Polygon& object)
		{
			Vertex* ptr = head;
			while (ptr != NULL)
			{
				head = head->next;
				delete ptr;
				ptr = head;
			}

			ptr = object.head;
			while (ptr != NULL)
			{
				push_end(ptr->get_point());
				ptr = ptr->next;
			}

			return *this;
		}

		Polygon& operator *= (double index)
		{
			if (index > 0)
			{
				Point center_of_mass(0, 0);
				int size = 0;
				Vertex* ptr = head;

				while (ptr != NULL)
				{

					center_of_mass += ptr->get_point();
					//center_of_mass.set_x(center_of_mass.get_x() + (ptr->get_point()).get_x());
					//center_of_mass.set_y(center_of_mass.get_y() + (ptr->get_point()).get_y());
					ptr = ptr->next;
					size++;
				}

				if (size != 0)//finding center
				{
					center_of_mass.set_x(center_of_mass.get_x() / size);
					center_of_mass.set_y(center_of_mass.get_y() / size);

					cout << "Center of mass ";
					center_of_mass.print();
					cout << endl;

					ptr = head;

					while (ptr != NULL)
					{
						ptr->get_point() = center_of_mass + index*(ptr->get_point() - center_of_mass);
						ptr = ptr->next;
					}

				}

			}
			return *this;
		}

		Polygon operator * (double index)
		{
			Polygon result(*this);
			result *= index;
			return result;
			
		}

		Polygon& operator +=(const Point& delta)
		{

			Vertex* ptr = head;
			while (ptr != NULL)
			{
				ptr->get_point() += delta;
				ptr = ptr->next;

			}

			return *this;
		}

		Polygon operator +(const Point& object)
		{
			Polygon result(*this);
			result += object;
			return result;
		}

		void  push_end(Point& _point)
		{
			if (head != NULL)
			{
				tail->next = new Vertex(_point);
				tail->next->previous = tail;
				tail = tail->next;
			}
			else
			{
				head = new Vertex(_point);
				tail = head;
			}
		}

		void  push_begin(Point& _point)
		{
			if (head != NULL)
			{
				Vertex* ptr = new Vertex(_point);
				ptr->next = head;
				head->previous = ptr;
				head = ptr;
			}
			else
			{
				head = new Vertex(_point);
				tail = head;
			}
		}

		void  pop_begin()
		{
			if (tail != NULL)
			{
				if (tail == head)
				{
					delete head;
					head = NULL;
					tail = NULL;
				}
				else
				{
					tail = tail->previous;
					delete tail->next;
					tail->next = NULL;
				}
			}
		}

		void  pop_end()
		{
			if (head != NULL)
			{
				if (head == tail)
				{
					delete head;
					head = NULL;
					tail = NULL;
				}
				else
				{
					head = head->next;
					delete head->previous;
					head->previous = NULL;
				}
			}
		}

		void clear()
		{
			while (head != NULL)
			{
				pop_begin();
			}
		}

		void  print()const
		{
			if (head == NULL)
			{
				cout << "Polygon is empty." << endl;
				return;
			}

			Vertex* ptr = head;
			while (ptr != NULL)
			{
				ptr->point.print();
				ptr = ptr->next;
			}
			cout << endl;
		}

	};


}
