#ifndef _COLOR_H_
#define _COLOR_H_
struct Color
{
	unsigned int r, g, b, a;
	
	Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f)
	{}

	Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 1) : r(r), g(g), b(b), a(a)
	{}

	void Set(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 1.0f)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	unsigned int* operator & ()
	{
		return (unsigned int*)this;
	}
};


extern Color Red;
extern Color Pink;
extern Color Orange;
extern Color Yellow;
extern Color Green;
extern Color Blue;
extern Color Black;
extern Color Gray;
extern Color White;

#endif;