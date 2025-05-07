#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

int x_1, y_1, x_2, y_2; // Coordinates for the line
int choice; // User's choice for the algorithm

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void DDA(int x_1, int y_1, int x_2, int y_2) {
    int dx = x_2 - x_1;
    int dy = y_2 - y_1;
    int steps = max(abs(dx), abs(dy));

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x_1;
    float y = y_1;
    for (int i = 0; i <= steps; i++) {
        setPixel(round(x), round(y));
        x += xInc;
        y += yInc;
    }
}

void Bresenham(int x_1, int y_1, int x_2, int y_2) {
    int dx = abs(x_2 - x_1);
    int dy = abs(y_2 - y_1);
    int sx = (x_1 < x_2) ? 1 : -1;
    int sy = (y_1 < y_2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        setPixel(x_1, y_1);

        if (x_1 == x_2 && y_1 == y_2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x_1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y_1 += sy;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0); // Set line color to red

    if (choice == 1) {
        DDA(x_1, y_1, x_2, y_2);
    } else if (choice == 2) {
        Bresenham(x_1, y_1, x_2, y_2);
    } else {
        cout << "Invalid choice! Please restart the program.\n";
    }

    glFlush();
}

int main(int argc, char** argv) {
    cout << "Select the line drawing algorithm:\n";
    cout << "1. DDA Algorithm\n";
    cout << "2. Bresenham Algorithm\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1 || choice == 2) {
        cout << "Enter the coordinates (x_1, y_1, x_2, y_2): ";
        cin >> x_1 >> y_1 >> x_2 >> y_2;
    } else {
        cout << "Invalid choice! Exiting program.\n";
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Line Drawing Algorithms: DDA and Bresenham");
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600); // Set orthographic projection
    // gluOrtho2D(-400, 400, -300, 300);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
