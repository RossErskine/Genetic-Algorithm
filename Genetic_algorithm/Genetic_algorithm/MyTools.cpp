#include "MyTools.h"

namespace MyLib
{
	void MyShape::draw_lines() const
	{
		if (color().visibility() && 1 < points.size())	// draw sole pixel?
			for (unsigned int i = 1; i < points.size(); ++i)
				fl_line(points[i - 1].x, points[i - 1].y, points[i].x, points[i].y);
	}

	void MyShape::draw() const
	{
		Fl_Color oldc = fl_color();
		// there is no good portable way of retrieving the current style
		fl_color(lcolor.as_int());
		fl_line_style(ls.style(), ls.width());

		draw_lines();
		fl_color(oldc);	// reset color (to pevious) and style (to default)
		fl_line_style(0);
	}

	
	void MyShape::move(int dx, int dy) //changed += to equals
	{
		for (unsigned int i = 0; i < points.size(); ++i) {
			points[i].x = dx;
			points[i].y = dy;
		}
	}

	void MyRectangle::draw_lines() const
	{
		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().red);
			fl_rectf(point(0).x, point(0).y, w, h);
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility()) {	// edge on top of fill
			fl_color(color().black);
			fl_rect(point(0).x, point(0).y, w, h);
		}
	}

	void MyCircle::draw_lines() const
	{
		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().yellow);
			fl_pie(point(0).x, point(0).y, r + r - 1, r + r - 1, 0, 360);
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility()) {
			fl_color(color().black);
			fl_arc(point(0).x, point(0).y, r + r, r + r, 0, 360);
		}
	}
}