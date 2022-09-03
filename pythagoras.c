/*
Amber Shore
Version 2022-07-02

Pythagoras Tree Generator
*/

#include "FPToolkit.c"

//prototypes
void draw_triangle(double* xy, double* rgb, int depth);
void draw_rayburst(double x, double y, double alpha);

//given a line xy, use it as the base to draw a square
void square_from_line(double* xy, double* rgb, int depth){
	double x1, y1, x2, y2, x3,y3, x4, y4;
	double dx, dy;
	double new_xy[4] = {0,0,0,0};
	
	x1 = xy[0];
	y1 = xy[1];
	x2 = xy[2];
	y2 = xy[3];
	
	//return if max depth is reached
	if (depth<=0)
		return;
		
  //create new line points using the x- and y-axis differences
	dx = x2 - x1;
	dy = y2 - y1;

	x3 = x2 - dy;
	y3 = y2 + dx;

	x4 = x1 - dy;
	y4 = y1 + dx;
		
  //draw the new lines, setting the rgb values first
	G_rgb(0,0,1);
	G_line(x1,y1, x2,y2);
	G_rgb(0,1,1);
	G_line(x3,y3, x2,y2);
	G_rgb(1,0,1);
	G_line(x3,y3, x4,y4);
	G_rgb(1,0,0);
	G_line(x1,y1, x4,y4);
		
  //choose the line that will create the base of the triangle
	new_xy[0] = x4;
	new_xy[1] = y4;
	new_xy[2] = x3;
	new_xy[3] = y3;

  //increment the triangle color
	rgb[0]+=.010;
	rgb[1]+=.002;
	rgb[2]+=.020;
	draw_triangle(new_xy, rgb, depth);
}
	
//triangle
void draw_triangle(double* xy, double* rgb, int depth){
	double x1 = xy[0];
	double y1 = xy[1];
	double x2 = xy[2];
	double y2 = xy[3];

	double f = (double)rand() / (double)RAND_MAX;
	double g = sqrt(f * (1-f));

	//find midpoints of each side
	double dx = x2-x1; 
	double dy = y2-y1;
			
	double nx1 = x1 + (dx * f) ;
 	double ny1 = y1 + (dy * f) ;

	double zx = nx1 - (g * dy);
	double zy = ny1 + (g * dx);
				
  //draw the new triangle
	G_rgb (.6, 0, .8);
	G_triangle(x1,y1, zx,zy, x2,y2);
	
	//recursive call using the top two sides of traingle as base for square
	double line[4] = {x1,y1, zx, zy};
	square_from_line(line, rgb, depth-1);
	double line2[4] = {zx,zy, x2,y2};
	square_from_line(line2, rgb, depth-1);
}

void draw_rayburst(double x, double y, double alpha){
	double xi, yi;
	double phi = 0;
	double two_pi = 2 * M_PI;
	double xs[1000];
	double ys[1000];
	double min_axis = 80;
	double maj_axis = 50;
	double maj_incr = 0;
	double min_incr = 0;
	
	G_rgb(1,1,1);
	G_fill_circle(x,y, 3);
	
	int i = 0;
	for(double t = 0; t <= two_pi; t+=alpha){
		if((int)(t*100) % (int)((M_PI/2.0)*100) == 0){
			maj_incr = 10;
			min_incr = 25;
		}
		else{
			maj_incr = 0;
			min_incr = 0;
		}
		xi = x + ((maj_axis+maj_incr) * cos(t) * cos(phi)) 
				- ((min_axis+min_incr) *  sin(t) * sin(phi));
		yi = y + ((maj_axis+maj_incr) * cos(t) * sin(phi)) 
				+ ((min_axis+min_incr) * sin(t) * cos(phi));
		
		xs[i] = xi;
		ys[i] = yi;
		++i;
	}
		G_wait_key();

	G_rgb(1,1,1);
	for( int j = 0; j < i; ++j){
		G_line(x,y, xs[j],ys[j]);
	}

	return;
}

int main(){
	double p[2]; 
  double q[2];
	double dx, dy;
	int swidth = 600 ;  
	int sheight = 600 ;

	G_init_graphics (swidth,sheight) ; 
  G_rgb (0, 0, 0);
  G_clear ();
	srand(time(0));

	p[0] = swidth/3;
	p[1] = 10;
	q[0] = swidth/3 + 0.5 * (swidth/3);
	q[1] = 10;

	G_wait_key();

	double rgb[3] = {0.03, 0.01, 0.05};
	double last_x,last_y;
	int num;

	double line[4] = {p[0], p[1], q[0], q[1]};
	int depth = 15;

	square_from_line(line, rgb, depth);

  //store the user click coordinates in p
	G_wait_click(p);
  //use p as the center of the rayburst
	draw_rayburst(p[0],p[1], M_PI/12.0);

  //save the image
	G_save_to_bmp_file("tree.bmp") ;
  
  //show the image until user quits
	while(G_wait_key()!= 'q') ;
	return 0;
}
