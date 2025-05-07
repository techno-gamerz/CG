// Install and explore the OpenGL

#include <GL/glut.h>
using namespace std;

// Function to initialize OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glMatrixMode(GL_PROJECTION);      // Set the projection matrix
    gluOrtho2D(0, 800, 0, 600); // Set the orthographic view
}

// Function to display a simple house
void displayHouse() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    // Draw the base of the house (rectangle)
    glColor3f(0.6, 0.4, 0.2); // Brown color
    glBegin(GL_POLYGON);
        glVertex2i(150, 150);
        glVertex2i(350, 150);
        glVertex2i(350, 300);
        glVertex2i(150, 300);
    glEnd();

    // Draw the roof of the house (triangle)
    glColor3f(0.8, 0.0, 0.0); // Red color
    glBegin(GL_TRIANGLES);
        glVertex2i(150, 300);
        glVertex2i(350, 300);
        glVertex2i(250, 400);
    glEnd();

    // Draw the door (rectangle)
    glColor3f(0.4, 0.2, 0.0); // Dark brown color
    glBegin(GL_POLYGON);
        glVertex2i(220, 150);
        glVertex2i(280, 150);
        glVertex2i(280, 250);
        glVertex2i(220, 250);
    glEnd();

    glFlush(); // Render now
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                      // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode
    glutInitWindowSize(500, 500);               // Set window size
    glutInitWindowPosition(100, 100);           // Set window position
    glutCreateWindow("Simple House");          // Create window

    init(); // Initialize OpenGL settings

    glutDisplayFunc(displayHouse); // Register display callback function

    glutMainLoop(); // Enter the event-processing loop
    return 0;
}

