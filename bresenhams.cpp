#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

int x_1, y_1, x_2, y_2; // Coordinates for the line

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void Bresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        setPixel(x1, y1);

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0); // Set line color to red
    Bresenham(x_1, y_1, x_2, y_2);

    glFlush();
}

int main(int argc, char** argv) {
    cout << "Enter the coordinates (x1, y1, x2, y2): ";
    cin >> x_1 >> y_1 >> x_2 >> y_2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bresenham's Line Drawing Algorithm");
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600); // Set orthographic projection
    // gluOrtho2D(-400, 400, -300, 300);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}