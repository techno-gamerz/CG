// Generate fractal patterns using i) Bezier ii) Koch Curve

#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

int choice; // User's choice for the curve type
float x0, y_0, x1, y_1, x2, y_2, x3, y_3; // Bezier curve control points
float kx1, ky1, kx2, ky2; // Koch curve endpoints
int depth; // Koch curve recursion depth

// Function to draw a Bezier curve
void drawBezier(float x0, float y_0, float x1, float y_1, float x2, float y_2, float x3, float y_3) {
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= 1; t += 0.01) {
        float x = pow(1 - t, 3) * x0 + 3 * t * pow(1 - t, 2) * x1 + 3 * pow(t, 2) * (1 - t) * x2 + pow(t, 3) * x3;
        float y = pow(1 - t, 3) * y_0 + 3 * t * pow(1 - t, 2) * y_1 + 3 * pow(t, 2) * (1 - t) * y_2 + pow(t, 3) * y_3;
        glVertex2f(x, y);
    }
    glEnd();
}

// Function to draw the Koch curve
void drawKoch(float x1, float y1, float x2, float y2, int depth) {
    if (depth == 0) {
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
        return;
    }

    float dx = (x2 - x1) / 3.0;
    float dy = (y2 - y1) / 3.0;

    float xA = x1 + dx;
    float yA = y1 + dy;

    float xB = x1 + 2 * dx;
    float yB = y1 + 2 * dy;

    float xC = (x1 + x2) / 2 - sqrt(3) * (y2 - y1) / 6;
    float yC = (y1 + y2) / 2 + sqrt(3) * (x2 - x1) / 6;

    drawKoch(x1, y1, xA, yA, depth - 1);
    drawKoch(xA, yA, xC, yC, depth - 1);
    drawKoch(xC, yC, xB, yB, depth - 1);
    drawKoch(xB, yB, x2, y2, depth - 1);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0); // Set line color to red

    switch (choice) {
        case 1: // Bezier Curve
            drawBezier(x0, y_0, x1, y_1, x2, y_2, x3, y_3);
            break;

        case 2: // Koch Curve
            drawKoch(kx1, ky1, kx2, ky2, depth);
            break;

        default:
            cout << "Invalid choice! Please restart the program.\n";
            break;
    }

    glFlush();
}

// Main function
int main(int argc, char** argv) {
    cout << "Select the type of fractal curve to draw:\n";
    cout << "1. Bezier Curve\n";
    cout << "2. Koch Curve\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter control points for Bezier curve (x0, y_0, x1, y_1, x2, y_2, x3, y_3):\n";
        cin >> x0 >> y_0 >> x1 >> y_1 >> x2 >> y_2 >> x3 >> y_3;
        // Default: x0 = 100, y_0 = 100, x1 = 200, y_1 = 400, x2 = 600, y_2 = 400, x3 = 700, y_3 = 100;
    } else if (choice == 2) {
        cout << "Enter endpoints for Koch curve (kx1, ky1, kx2, ky2):\n";
        cin >> kx1 >> ky1 >> kx2 >> ky2;
        cout << "Enter recursion depth for Koch curve: ";
        cin >> depth;
        // Default: kx1 = 100, ky1 = 300, kx2 = 700, ky2 = 300, depth = 4;
    } else {
        cout << "Invalid choice! Exiting program.\n";
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Fractal Curves: Bezier and Koch");
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600); // Set orthographic projection based on screen resolution (800x600)

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

