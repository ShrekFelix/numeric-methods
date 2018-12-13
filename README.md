# Parsing functions

 The calculator takes one command line argument, which specifies the name of a file to read commands from. There are two basic commands: define and evaluate, which look like this:

```
define  (f x y z) = (+ (* x y) (- z 3))
evaluate (f 3 4.2 5)
evaluate (f -1 9.2 6)
```

 output:

```
defined  (f x y z)
(f 3 4.2 5) = 14.6
(f -1 9.2 6) = -6.2
```

  Specifically, define must be followed by (id id ...)


  An identifier (id) is a sequence of letters (uppercase and/or lowercase,
  case sensitive).  The first id is the name of the function being
  defined. Any remaining ids are the names of parameters to that function.
  In the first line above, we are defining a function called "f" which
  takes 3 parametesr: "x", "y", and "z".  All functions must take
  at least one parameter, but there is no upper limit on the number
  (so you could make a function that takes 100 or 1000 or 10000 parameters).


  Next must be an = sign, followed by an expression.  An expression is
  one of the following:

- A function call:  (fname expr ...)
  An fname is either an id (specifying a user-defined function), or
  +, -, *, %, or /, specifying a built-in math operation.
- A parameter name:  id
- A numeric constant:  a sequence of characters which strtod accepts
         as a valid double

  For example, (f 3 4 5.2) is an expression because 3, 4, and 5.2 are
  expressions, so (f 3 4 5.2) is (id expr expr expr).  

All function names (the first identifier in the parenthesis) must refer to a previously defined function , and all other identifiers must refer to parameters to this function or be numeric constants. It is an error to attempt to re-define a function which is already defined.

Note that an arbitrary amount of spaces may appear between (but not inside of) any tokens (id, fname, parens, numeric constants) without altering the meaning. For example:

```
(f 3 4 5)
```

and 

```
( f             3       4  5    )
```

are both legal and have the same meaning. However,

```
(fx yz)
```

and

```
(f x y z)
```

  both mean two different things (the former calls the function "fx" with one argument, "yz", the later calls the function "f" with three arguments: "x", "y", and "z"). Evaluate commands must have an expression with no variables---they may refer to functions, and have numeric constants for the parameters. However, the may call other functions.  The following are all valid (assuming appropriate definitions of f, g, and h exist):

```
(f 3 4.2 5)
(f (g 1 2) (g 3 4) (h 5 6 -7))
```

 The built-in math operations (+, -, *, /, %,sin, cos, sqrt, log, pow), have the same meaning as in C.

# Riemann integration

the numint command uses midpoint-rectangle method to compute numerical integration
input is like this:

```
define  (f x y) = (+ (* 2 x) y)
numint f 0.001 -1 1 4 5
```

This would compute the volume under the curve of f(x,y) = 2*x + y with x ranging from -1 to 1, and y ranging from 4 to 5. It would compute this by summing the volumes of 2,000,000 rectangular prisms, each of which has length 0.001, and width 0.001, and a height based on the value of f at the center of that particular rectangle.

# Monte Carlo Integration

This command approximates the area (or volume, etc...) under a curve, but instead of summing the volumes of many rectangles, it uses a Monte Carlo approach. In particular, it picks many random points within the bounds of the integration range. It then uses these to estimate the average value of the curve over this interval.  That is, if the function is y = f(x), then it computes
$$
\overline y	=	\frac{f(x_1)	+f(x_2)	+	...	+f(x_N)}	{N}
$$
$$
area	=	\overline y	\times	(x_{max}-x_{min})
$$
For a three dimensional curve (z = f(x,y)) it would be
$$
\overline z = \frac{f(x_1, y_1)	+	f(x_2, y_2)	+	...	+	f(x_N, y_N)}	{N}	\\
volume = \overline z \times (x_{max} - x_{min}) \times (y_{max} - y_{min})
$$
For higher dimensional curve, the same idea applies.

The arguments to "mcint" are the same as "numint" except that the second argument is the number of trials (the number of random points to pick) instead of the step size.  The first parameter is still the function name, and the remaining parmaters are still the ranges to integrate over.

# Gradient Ascent/Descent

The commands should take the following arguments:
  1. The name of the function
  2. gamma 
  3. convergedDistance
  4. The start point, which will have as many numbers as the function has
     parameters.
  5. The maximum number of steps to take before giving up and deciding
     that the ascent/descent does not converg.