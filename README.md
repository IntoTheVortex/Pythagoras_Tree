## Pythagoras Tree
Using a basic graphics library, I wrote a program to recursively draw a modified version of a Pythagoras Tree using random angles.

---------------------------------------------------
![Random Angle Pythagoras Tree](https://github.com/IntoTheVortex/Pythagoras_Tree/blob/main/images/py_tree.png?raw=true)

Fractal Description:
The Pythagoras Tree is based on the Pythagorean Theorem: a2+b2 = c2. The squares of each side of a right triangle are related in this fashion, and the Pythagoras Tree simply shows these squares attached to their related triangle sides. As the hypotenuse is the largest side, the base square is also the largest square, with each succeeding square decreasing in size according to the theorem. 


Design Paradigm & Mathematical Description:
Though the Pythagorean Theorem applies to right triangles, the Pythagorean Tree can be modified using other triangles to create more varied tree-forms. 
For my implementation, the shape of the triangle is determined at random at each step. A side (line AC) of the root square is passed into a function, which randomly determines how far along the line will be the opposite point of the new triangle (point B):

![Finding point B](https://github.com/IntoTheVortex/Pythagoras_Tree/blob/main/images/im_2.png?raw=true)

This point delineates the bases of two right triangles, which share point B and help to mathematically determine point D:

![Finding point D](https://github.com/IntoTheVortex/Pythagoras_Tree/blob/main/images/im_3.png?raw=true)

Point D is determined by finding zx and zy using the random fraction f, and the points (x1,y1) and (x2,y2) from line AC:

```f = (random decimal between 0 and 1)
g = sqrt(f * (1-f))
dx = x2-x1
dy = y2-y1
nx1 = x1 + (dx * f) 
ny1 = y1 + (dy * f) 
zx = nx1 - (g * dy)
zy = ny1 + (g * dx)
```

After finding point D, the triangle ACD is drawn, and the two new sides (AD and DC) are sent into the square drawing function, which in turn calls the triangle drawing function again. This process repeats until the determined depth is reached.

For the rayburst star, I used the ellipse equation to create the radial points of the rayburst. The endpoint for each line is (xi,yi), and the center point (chosen by the user) is (x,y). The variables maj_incr and min_incr are used to elongate the lines that occur where t is equal to 0, pi/2, pi, and 3pi/2. Elsewhere these values are zero. The longer lines at these points indicate cardinal points (a, b, c, and d in the graphic). The variable phi is set to zero, and can be changed in order to tilt the ellipse. 
The equation used for each line is:

```
xi = x + ((maj_axis+maj_incr) * cos(t) * cos(phi)) - ((min_axis+min_incr) *  sin(t) * sin(phi))
yi = y + ((maj_axis+maj_incr) * cos(t) * sin(phi)) + ((min_axis+min_incr) * sin(t) * cos(phi))
```

The angle t proceeds by a defined radial interval, in this case pi/12.

![Angle t on the Unit Circle](https://github.com/IntoTheVortex/Pythagoras_Tree/blob/main/images/im_4.png?raw=true)

The graphical representation shows how a circle would be plotted. The ellipse equation achieves the varying radial lengths, instead of a constant radius as shown above. 


Artistic Description:
For artistic enhancements, I determined color line-by-line. One side of the trunk is cyan with the opposing side in red. The other two sides of the squares are drawn in blue, and this is overwritten by the triangle drawn in purple. This creates a darker trunk center and brighter sides, which creates a leaf effect at high depths. 
A user-chosen point is also taken interactively, and this point is used as the basis for the star. The star is created using an equation for an ellipse, with cardinal points elongated.
