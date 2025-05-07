// Implement following 2D transformations on the object with respect to axis : i) Scaling ii) Rotation about arbitrary point iii) Reflection

#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    float x, y;
};

void scale(Point &p, float sx, float sy) {
    p.x *= sx;
    p.y *= sy;
}

void rotate(Point &p, Point pivot, float angle) {
    float rad = angle * M_PI / 180.0;
    float cosA = cos(rad);
    float sinA = sin(rad);

    // Translate point to origin
    float xShifted = p.x - pivot.x;
    float yShifted = p.y - pivot.y;

    // Rotate point
    float xRotated = xShifted * cosA - yShifted * sinA;
    float yRotated = xShifted * sinA + yShifted * cosA;

    // Translate point back
    p.x = xRotated + pivot.x;
    p.y = yRotated + pivot.y;
}

void reflect(Point &p, char axis) {
    if (axis == 'x' || axis == 'X') {
        p.y = -p.y;
    } else if (axis == 'y' || axis == 'Y') {
        p.x = -p.x;
    }
}

int main() {
    Point p, pivot;
    float sx, sy, angle;
    char axis;

    cout << "Enter point coordinates (x y): ";
    cin >> p.x >> p.y;

    cout << "Enter scaling factors (sx sy): ";
    cin >> sx >> sy;
    scale(p, sx, sy);
    cout << "After scaling: (" << p.x << ", " << p.y << ")\n";

    cout << "Enter pivot point for rotation (x y): ";
    cin >> pivot.x >> pivot.y;
    cout << "Enter rotation angle (degrees): ";
    cin >> angle;
    rotate(p, pivot, angle);
    cout << "After rotation: (" << p.x << ", " << p.y << ")\n";

    cout << "Enter axis for reflection (x or y): ";
    cin >> axis;
    reflect(p, axis);
    cout << "After reflection: (" << p.x << ", " << p.y << ")\n";

    return 0;
}

