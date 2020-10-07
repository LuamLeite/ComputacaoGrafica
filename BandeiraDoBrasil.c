#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#define MAXIMUM 1.80
#define MINIMUM -1.80
#define MIDDLE 0.0
#define MAXIMUM_RADIUS 0.90
#define MINIMUM_RADIUS -0.90
#define TOTAL_SEGMENTS 360.0

void toLimitValue(GLfloat *value) {
    if (*value > MAXIMUM) {
        *value = MAXIMUM;
    } else if (*value < MINIMUM) {
        *value = MINIMUM;
    }
}

void toLimitRadius(GLfloat *radius) {
    if (*radius > MAXIMUM_RADIUS) {
        *radius = MAXIMUM_RADIUS;
    } else if(*radius < MINIMUM_RADIUS) {
        *radius = MINIMUM_RADIUS;
    }
}

void calculateCurrentPointsXYUsingAngle(GLfloat *x, GLfloat *y, GLfloat angle) {
    GLfloat height = GLfloat(glutGet(GLUT_WINDOW_HEIGHT));
    GLfloat width = GLfloat(glutGet(GLUT_WINDOW_WIDTH));
    GLfloat windowProportion;
    if (height == width) {
        *x *= cosf(angle);
        *y *= sinf(angle);
    } else if(height < width) {
        windowProportion = height / width;
        *x *= windowProportion * cosf(angle);
        *y *= sinf(angle);
    } else {
        windowProportion = width / height;
        *x *= cosf(angle);
        *y *= windowProportion * sinf(angle);
    }
}

void calculateWidthAndHeightProportion(GLfloat *widthProportion, GLfloat *heightProportion) {
    GLfloat height = GLfloat(glutGet(GLUT_WINDOW_HEIGHT));
    GLfloat width = GLfloat(glutGet(GLUT_WINDOW_WIDTH));
    *widthProportion = *heightProportion = 1;
    if(height < width) {
        *widthProportion = height / width;
    } else if(width < height) {
        *heightProportion = width / height;
    }
}

void drawRectangle(GLfloat width, GLfloat height) {
	glColor3f( 0.0, 0.8, 0.0 );
    toLimitValue(&width);
    toLimitValue(&height);
    GLfloat upperY = height/2, bottomY = -height/2;
    GLfloat rightX = width/2, leftX = -width/2;
    glBegin(GL_QUADS);
        glVertex2f(leftX, bottomY);
        glVertex2f(leftX, upperY);
        glVertex2f(rightX, upperY);
        glVertex2f(rightX, bottomY);
    glEnd();
    glFinish();
}

void drawRhombus(GLfloat width, GLfloat height) {
	glColor3f( 1.0, 1.0, 0.0 );
    toLimitValue(&width);
    toLimitValue(&height);
    GLfloat upperY = height/2, bottomY = -height/2;
    GLfloat rightX = width/2, leftX = -width/2;
	upperY = upperY/1.2;
	rightX = rightX/1.2;
	bottomY = bottomY/1.2;
	leftX = leftX/1.2;
    glBegin(GL_QUADS);
        glVertex2f(leftX, MIDDLE);
        glVertex2f(MIDDLE, upperY);
        glVertex2f(rightX, MIDDLE);
        glVertex2f(MIDDLE, bottomY);
    glEnd();
    glFinish();
}

void drawCircle(GLfloat radius) {
	glColor3f( 0.0, 0.0, 0.8 );
    toLimitRadius(&radius);
    glBegin(GL_POLYGON);
        for(GLint currentSegment = 0; currentSegment < TOTAL_SEGMENTS; currentSegment++) {
            GLfloat currentAngle = 2.0 * M_PI * GLfloat(currentSegment) / TOTAL_SEGMENTS;
            GLfloat x = radius/2, y = radius/2;
			
            calculateCurrentPointsXYUsingAngle(&x, &y, currentAngle);
            glVertex2f(x, y);
        }
    glEnd();
    glFinish();
}

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
	drawRectangle(100.0, 100.0);
	drawRhombus(5.0, 5.0);
	drawCircle(5.0);
    glEnd();
    glFlush();
}
 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glutCreateWindow("Hello world!");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}