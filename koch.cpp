#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

float kx1, ky1, kx2, ky2; // Koch curve endpoints
int depth; // Koch curve recursion depth

// Function to draw the Koch curve
void drawKoch(float x1, float y1, float x2, float y2, int depth) {
    if (depth == 0) {
        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0); // Red line color for the curve
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();

        glPointSize(5.0);
        glBegin(GL_POINTS);
        if ((x1 == kx1 && y1 == ky1) || (x2 == kx2 && y2 == ky2)) {
            glColor3f(0.0, 0.0, 0.5); // Navy blue for user-inserted points
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        }
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

// Function to display depth on the screen
void displayDepth() {
    glColor3f(0.0, 0.0, 1.0); // Blue color for text
    glRasterPos2f(10, 580); // Position text near the top-left corner
    std::string depthText = "Depth: " + std::to_string(depth);
    for (char c : depthText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawKoch(kx1, ky1, kx2, ky2, depth);
    displayDepth(); // Display the depth on the screen

    glFlush();
}

// Main function
int main(int argc, char** argv) {
    cout << "Enter endpoints for Koch curve (kx1, ky1, kx2, ky2):\n";
    cin >> kx1 >> ky1 >> kx2 >> ky2;
    cout << "Enter recursion depth for Koch curve: ";
    cin >> depth;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Koch Curve");
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600); // Set orthographic projection based on screen resolution (800x600)

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}