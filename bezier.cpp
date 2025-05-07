#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Vector to store control points as pairs of (x, y)
vector<pair<float, float>> controlPoints;

// Function to calculate factorial
int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// Function to calculate binomial coefficient
int binomialCoeff(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

// Function to draw a generic Bezier curve
void drawBezier() {
    int n = controlPoints.size() - 1; // Degree of the curve
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= 1; t += 0.01) {
        float x = 0, y = 0;
        for (int i = 0; i <= n; i++) {
            float coeff = binomialCoeff(n, i) * pow(1 - t, n - i) * pow(t, i);
            x += coeff * controlPoints[i].first;
            y += coeff * controlPoints[i].second;
        }
        glVertex2f(x, y);
    }
    glEnd();
}

// Function to draw control points and connect them with dotted lines
void drawControlPoints() {
    glColor3f(0.0, 0.0, 0.5); // Set color to navy blue
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (const auto& point : controlPoints) {
        glVertex2f(point.first, point.second);
    }
    glEnd();

    glEnable(GL_LINE_STIPPLE);

    // Change the line pattern to dashed line
    glLineStipple(1, 0x00FF); // Dashed line pattern

    glBegin(GL_LINE_STRIP);
    for (const auto& point : controlPoints) {
        glVertex2f(point.first, point.second);
    }
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}

// Display function to render the Bezier curve and control points
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawControlPoints(); // Draw control points and dotted lines
    glColor3f(1.0, 0.0, 0.0); // Set line color to red
    drawBezier();
    glFlush();
}

// Main function
int main(int argc, char** argv) {
    int numPoints;
    cout << "Enter the number of control points: ";
    cin >> numPoints;

    // Input control points from the user
    cout << "Enter the control points (x, y) one by one:\n";
    for (int i = 0; i < numPoints; i++) {
        float x, y;
        cin >> x >> y;
        controlPoints.push_back({x, y});
    }

    // Initialize OpenGL and create a window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Generic Bezier Curve");
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600); // Use screen pixel coordinates

    // Register display callback function
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}