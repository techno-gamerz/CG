#include <GL/glut.h>
#include <iostream>
#include <string>

using namespace std;

// Global variables
int windowWidth = 800, windowHeight = 600;
float fillColor[3] = {1.0, 0.0, 0.0}; // Default fill color: red
float boundaryColor[3] = {0.0, 0.0, 0.0}; // Default boundary color: black

void setPixel(int x, int y, float color[3]) {
    glBegin(GL_POINTS);
    glColor3fv(color);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void getPixelColor(int x, int y, float color[3]) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

void floodFill(int x, int y, float oldColor[3], float newColor[3]) {
    float currentColor[3];
    getPixelColor(x, y, currentColor);
    if (currentColor[0] == oldColor[0] && currentColor[1] == oldColor[1] && currentColor[2] == oldColor[2]) {
        setPixel(x, y, newColor);
        floodFill(x + 1, y, oldColor, newColor);
        floodFill(x - 1, y, oldColor, newColor);
        floodFill(x, y + 1, oldColor, newColor);
        floodFill(x, y - 1, oldColor, newColor);
    }
}

void boundaryFill(int x, int y, float boundaryColor[3], float newColor[3]) {
    float currentColor[3];
    getPixelColor(x, y, currentColor);
    if ((currentColor[0] != boundaryColor[0] || currentColor[1] != boundaryColor[1] || currentColor[2] != boundaryColor[2]) &&
        (currentColor[0] != newColor[0] || currentColor[1] != newColor[1] || currentColor[2] != newColor[2])) {
        setPixel(x, y, newColor);
        boundaryFill(x + 1, y, boundaryColor, newColor);
        boundaryFill(x - 1, y, boundaryColor, newColor);
        boundaryFill(x, y + 1, boundaryColor, newColor);
        boundaryFill(x, y - 1, boundaryColor, newColor);
    }
}

void scanLineFill() {
    int y, xLeft, xRight;
    for (y = 200; y <= 400; y++) { // Assuming polygon bounds
        xLeft = 200; // Left boundary of the polygon
        xRight = 400; // Right boundary of the polygon
        for (int x = xLeft; x <= xRight; x++) {
            float currentColor[3];
            getPixelColor(x, y, currentColor);
            if (currentColor[0] != 1.0 || currentColor[1] != 1.0 || currentColor[2] != 1.0) { // Not white
                setPixel(x, y, fillColor);
            }
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // White polygon color
    glBegin(GL_POLYGON);
    glVertex2i(200, 200);
    glVertex2i(400, 200);
    glVertex2i(400, 400);
    glVertex2i(200, 400);
    glEnd();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    gluOrtho2D(0, windowWidth, 0, windowHeight);
}

void askForNewColor() {
    cout << "Enter new fill color (R G B values between 0.0 and 1.0): ";
    cin >> fillColor[0] >> fillColor[1] >> fillColor[2];
    if (fillColor[0] < 0.0 || fillColor[0] > 1.0 ||
        fillColor[1] < 0.0 || fillColor[1] > 1.0 ||
        fillColor[2] < 0.0 || fillColor[2] > 1.0) {
        cout << "Invalid color values. Defaulting to red.\n";
        fillColor[0] = 1.0; fillColor[1] = 0.0; fillColor[2] = 0.0;
    }
}

void menu() {
    int choice;
    cout << "\nPolygon Filling Options:\n";
    cout << "1. Flood Fill\n";
    cout << "2. Boundary Fill\n";
    cout << "3. Scan Line Fill\n";
    cout << "4. Terminate\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            int x, y;
            cout << "Enter seed point (x y): ";
            cin >> x >> y;
            float oldColor[3] = {1.0, 1.0, 1.0}; // Assuming white background
            floodFill(x, y, oldColor, fillColor);
            askForNewColor();
            break;
        }
        case 2: {
            int x, y;
            cout << "Enter seed point (x y): ";
            cin >> x >> y;
            boundaryFill(x, y, boundaryColor, fillColor);
            askForNewColor();
            break;
        }
        case 3:
            scanLineFill();
            askForNewColor();
            break;
        case 4:
            exit(0);
        default:
            cout << "Invalid choice.\n";
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Polygon Filling");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(menu);
    glutMainLoop();
    return 0;
}
