#include <stdio.h>
#include <stdbool.h>

// For simplicity's sake both points and vectors
// are used with this struct
// point variable names start with a `p` 
typedef struct Vec2
{
    double x;
    double y;
} Vec2;

// returns a line vector from two points
Vec2 getLine(Vec2 p1, Vec2 p2)
{
    Vec2 ret = {
        .x = p2.x - p1.x,
        .y = p2.y - p1.y,
    };
    return ret;
}

// Shows if three points are on a line
// IMPORTANT: It is assumed that none of these vectors is a null vector
bool isLine(Vec2 p1, Vec2 p2, Vec2 p3)
{
    Vec2 line1 = getLine(p1, p2);
    Vec2 line2 = getLine(p2, p3);
    Vec2 line3 = getLine(p3, p1);

    double cof_x1 = line1.x / line2.x;
    double cof_y1 = line1.y / line2.y;

    double cof_x2 = line2.x / line3.x;
    double cof_y2 = line2.y / line3.y;

    double cof_x3 = line1.x / line3.x;
    double cof_y3 = line1.y / line3.y;

    if (cof_x1 != cof_y1)
        return false;
    if (cof_x2 != cof_y2)
        return false;
    if (cof_x3 != cof_y3)
        return false;

    return true;
}

void printPoint2(Vec2 p)
    { printf("P: %lf  %lf\n", p.x, p.y);}

// return dot product of two vectors
double vecDotProduct(Vec2 p1, Vec2 p2)
{
    return (p1.x * p2.x) + (p1.y * p2.y);
}

// Checks if three points connect up to a right-angled triangle 
bool isRATriangle(Vec2 p1, Vec2 p2, Vec2 p3)
{
    Vec2 line1 = getLine(p1, p2);
    Vec2 line2 = getLine(p2, p3);
    Vec2 line3 = getLine(p3, p1);

    if (vecDotProduct(line1, line2) == 0)
        return true;
    if (vecDotProduct(line2, line3) == 0)
        return true;
    if (vecDotProduct(line3, line1) == 0)
        return true;

    return false;
}

// demo
int main()
{
    Vec2 p1 = {0.0, 0.0};
    Vec2 p2 = {0.0, 4.0};
    Vec2 p3 = {3.0, 0.000001};

    printf("IsLine: %d\n", isLine(p1, p2, p3));
    printf("IsRightAngledTriangle: %d\n", isRATriangle(p1, p2, p3));
    puts("");

    Vec2 p4 = {0.0, 1.0};
    Vec2 p5 = {1.0, 3.0};
    Vec2 p6 = {2.0, 5.0};

    printf("IsLine: %d\n", isLine(p4, p5, p6));
    printf("IsRightAngledTriangle: %d\n", isRATriangle(p4, p5, p6));
    puts("");

    Vec2 p7 = { 1.0, 1.0 };
    Vec2 p8 = { 4.0, 2.0 };
    Vec2 p9 = { 7.0, 3.0 };
    
    printf("IsLine: %d\n", isLine(p7, p8, p9));
    printf("IsRightAngledTriangle: %d\n", isRATriangle(p7, p8, p9));
    puts("");

    Vec2 p10 = { 1.0, 12.0 };
    Vec2 p11 = { 02.0, 123123.0 };
    Vec2 p12 = { -5.0, -3.0 };
    
    printf("IsLine: %d\n", isLine(p10, p11, p12));
    printf("IsRightAngledTriangle: %d\n", isRATriangle(p10, p11, p12));
    puts("");

    Vec2 p13 = {  1.0, -4.0 };
    Vec2 p14 = { -4.0, -3.0 };
    Vec2 p15 = { -1.0, -1.0 };
    
    printf("IsLine: %d\n", isLine(p13, p14, p15));
    printf("IsRightAngledTriangle: %d\n", isRATriangle(p13, p14, p15));

    return 0;
}
