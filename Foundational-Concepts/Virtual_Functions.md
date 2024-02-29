# Virtual Functions

Compiler implements the virtual function defintions.

```cpp

public Shape
{
    virtual int area() = 0;
    virtual int perimeter() = 0;
    virtual int corners() { return 0; };
}

public Circle : public Shape
{
    int area() override { return pi*r*r;}
    int perimeter() override {return 2*pi*r;}
}

public Triangle : public Shape
{
    int area() override { return 1/2*b*h;}
    int perimeter() override {return b+hyp+prep;}
    int corners() { return 3; };
}
```
So what does the compiler do when it sees virtual keywords in the base class?

In every derived classes it adds a new hidden member variable called **vptr**, which is a pointer to a distinct **v-table** for each class.

V-table is a list/vector of function pointers. So for the example above it will contain 3 function pointers, one for each virtual function in the base .e.g.  {*area, *perimeter, *corner }

So for Traingle the V-table will look like: <p>
{&Triangle::area, &Triangle::perimeter, &Triangle::corners}

For Circle the V-table will look like: <p>
{&Circle::area, &Circle::perimeter, &Shape::corners}

So you see that there is cost associated with dynamically allocating vtable for each child class, and then the actual function call now incurs an overhead of indirection.

