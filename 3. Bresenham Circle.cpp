// Implement Bresenham circle drawing algorithm to draw any object. The object should be displayed in all the quadrants with respect to center and radius

#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

int centerX, centerY, radius;

void plotPoints(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(centerX + x, centerY + y);
    glVertex2i(centerX - x, centerY + y);
    glVertex2i(centerX + x, centerY - y);
    glVertex2i(centerX - x, centerY - y);
    glVertex2i(centerX + y, centerY + x);
    glVertex2i(centerX - y, centerY + x);
    glVertex2i(centerX + y, centerY - x);
    glVertex2i(centerX - y, centerY - x);
    glEnd();
}

void bresenhamCircle() {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y) {
        plotPoints(x, y);
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    bresenhamCircle();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glColor3f(1.0, 0.0, 0.0); // Set line color to red
    glPointSize(2.0);
    // gluOrtho2D(-400, 400, -300, 300); // Adjust for 800x600 resolution
    gluOrtho2D(0, 800, 0, 600); // Adjust for input range 0-800, 0-600
}

int main(int argc, char** argv) {
    std::cout << "Enter center coordinates (X Y): ";
    std::cin >> centerX >> centerY;
    std::cout << "Enter radius: ";
    std::cin >> radius;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600); // Set window size to 800x600
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Circle Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
