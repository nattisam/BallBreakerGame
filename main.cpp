#include <stdlib.h>
#include <GL/glut.h>
#include<stdio.h>
#include<string.h>
#include <math.h>

// Arrays for different colors and parameters
GLfloat brickColors[][3] = {{1, 0, 0}, {0, 0, 1}, {0, 1, 0}, {1, 1, 1}};
GLfloat ballColors[][3] = {{1, 0, 0}, {0, 0, 1}, {0, 1, 0}, {1, 1, 1}};
GLfloat paddleColors[][3] = {{1, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1}};
GLfloat textColors[][4] = {{1, 0, 0, 1}, {0, 0, 1, 1}, {0, 1, 0, 1}, {1, 1, 0, 1}, {0.5, 0.5, 0.5, 1}};
GLfloat paddleSizes[] = {2, 4, 6};
int levels[] = {120, 80, 60};

// Variables to store game state
int playerScore = 0;
int brickColorIndex = 0, ballColorIndex = 2, gameLevel = 0, paddleColorIndex = 1, textColorIndex = 2, paddleSizeIndex = 1;
GLfloat paddleX, ballX = 0, ballY = -12.94, ballSpeed = 0, ballDirX = 0, ballDirY = 0, startGame = 0;
float speedRate = levels[gameLevel];

// Structure to store brick coordinates
struct brickCoords {
    GLfloat x;
    GLfloat y;
};

brickCoords brickArray[50][50];

// Function to draw the paddle
void drawPaddle() {
    glDisable(GL_LIGHTING);
    glColor3fv(paddleColors[paddleColorIndex]);
    glBegin(GL_POLYGON);
    glVertex3f(-paddleSizes[paddleSizeIndex] + paddleX, 0 - 15, 0);
    glVertex3f(paddleSizes[paddleSizeIndex] + paddleX, 0 - 15, 0);
    glVertex3f(paddleSizes[paddleSizeIndex] + paddleX, 1 - 15, 0);
    glVertex3f(-paddleSizes[paddleSizeIndex] + paddleX, 1 - 15, 0);
    glEnd();
    glEnable(GL_LIGHTING);
}

// Function to draw a single brick
void drawBrick(GLfloat x, GLfloat y, GLfloat z) {
    glDisable(GL_LIGHTING);
    glColor3fv(brickColors[brickColorIndex]);
    glBegin(GL_QUADS);
    glVertex3f(x, y, z);
    glVertex3f(x + 3, y, z);
    glVertex3f(x + 3, y + 1, z);
    glVertex3f(x, y + 1, z);
    glEnd();
    glEnable(GL_LIGHTING);
}

// Function to draw all the bricks
void drawBricks() {
    int i, j;
    if (startGame == 0) {
        for (i = 1; i <= 4; i++) {
            for (j = 1; j <= 10; j++) {
                brickArray[i][j].x = (GLfloat)(j * 4 * 0.84);
                brickArray[i][j].y = (GLfloat)(i * 2 * 0.6);
            }
        }
    }

    glPushMatrix();
    glTranslatef(-19.5, 5, 0);

    for (i = 1; i <= 4; i += 1) {
        for (j = 1; j <= 10; j += 1) {
            if (brickArray[i][j].x == 0 || brickArray[i][j].y == 0) {
                continue;
            }
            drawBrick(brickArray[i][j].x, brickArray[i][j].y, 0);
        }
    }
    glPopMatrix();
}

// Function to draw the ball
void drawBall() {
    // Ambient, diffuse, and specular properties for light 1
    GLfloat ambient1[] = {0.5, 0.5, 0.5};
    GLfloat diffuse1[] = {0.8, 0.8, 0.8};
    GLfloat specular1[] = {1.0, 1.0, 1.0};

    // Position and properties for light 2
    GLfloat position[] = {0, 0, -50, 1};
    GLfloat ambient2[] = {0.2, 0.2, 0.2};
    GLfloat diffuse2[] = {0.5, 0.5, 0.5};
    GLfloat specular2[] = {0.3, 0.3, 0.3};

    // Material properties
    GLfloat shininess[] = {500};
    float materialColours[][3] = {{1, 0, 0}, {0, 0, 1}, {0, 1, 1}};

    // Set light properties
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse1);

    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular2);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse2);

    // Set material properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialColours[ballColorIndex]);

    // Draw the ball
    glPushMatrix();
    glTranslatef(ballX, ballY, 0);
    glScalef(1.0, 1.0, 0.5);
    glutSolidSphere(1.0, 52, 52);
    glPopMatrix();
}

// Function to handle mouse motion
void mouseMotion(int x, int y) {
    if (startGame == 1) {
        paddleX = (x - glutGet(GLUT_WINDOW_WIDTH) / 2) / 20;
        if (paddleX > 15) {
            paddleX = 15;
        }
        if (paddleX < -15) {
            paddleX = -15;
        }
    } else
        glutSetCursor(GLUT_CURSOR_INHERIT);
}

// Function to change brick color
void changeBrickColor(int action) {
    brickColorIndex = action - 1;
}

// Function to change ball color
void changeBallColor(int action) {
    ballColorIndex = action - 1;
}

// Function to change game difficulty
void changeDifficulty(int action) {
    gameLevel = action - 1;
}

// Function to handle menu actions
void handleMenu(int action) {
}

// Function to change paddle color
void changePaddleColor(int action) {
    paddleColorIndex = action - 1;
}

// Function to change text color
void changeTextColor(int action) {
    textColorIndex = action - 1;
}

// Function to change paddle size
void changePaddleSize(int action) {
    paddleSizeIndex = action - 1;
}

// Function to create menu
void addMenu() {
    int submenu1 = glutCreateMenu(changeBrickColor);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Blue", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("White", 4);

    int submenu2 = glutCreateMenu(changeBallColor);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Blue", 2);
    glutAddMenuEntry("Cyan", 3);

    int submenu4 = glutCreateMenu(changePaddleColor);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Blue", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("Cyan", 4);

    int submenu3 = glutCreateMenu(changeDifficulty);
    glutAddMenuEntry("Easy", 1);
    glutAddMenuEntry("Medium", 2);
    glutAddMenuEntry("Hard", 3);

    int submenu5 = glutCreateMenu(changeTextColor);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Blue", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("Yellow", 4);

    int submenu6 = glutCreateMenu(changePaddleSize);
    glutAddMenuEntry("Small", 1);
    glutAddMenuEntry("Medium", 2);
    glutAddMenuEntry("Large", 3);

    glutCreateMenu(handleMenu);
    glutAddSubMenu("Bricks Color", submenu1);
    glutAddSubMenu("Ball Color", submenu2);
    glutAddSubMenu("Paddle Color", submenu4);
    glutAddSubMenu("Text Color", submenu5);
    glutAddSubMenu("Difficulty", submenu3);
    glutAddSubMenu("Paddle Size", submenu6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Function to display text
void displayText(int score) {
    glDisable(GL_LIGHTING);
    char displayText[40];
    char difficulty[10];
    if (gameLevel == 0) {
        sprintf(difficulty, "Easy");
    }

    if (gameLevel == 1) {
        sprintf(difficulty, "Medium");
    }

    if (gameLevel == 2) {
        sprintf(difficulty, "Hard");
    }
    if (score < 40)
        sprintf(displayText, "Difficulty: %s    Your Score: %d", difficulty, score);
    else {
        sprintf(displayText, "You have won!!");
        startGame = 0;
        ballY = -12.8;
        ballX = 0;
        ballDirX = 0;
        ballDirY = 0;
        paddleX = 0;
    }
    glColor4fv(textColors[textColorIndex]);
    glPushMatrix();
    glTranslatef(-1, 0, 0);
    glRasterPos3f(0, 0, 20);
    for (int i = 0; displayText[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, displayText[i]);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

// Function to display
void display(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 0, 0, 0, -25, 0, 1, 0);
    glTranslatef(0, 0, -25);
    drawPaddle();
    drawBricks();
    drawBall();
    displayText(playerScore);
    glutSwapBuffers();
}

// Function to enable lights
void lightsOn() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

// Function to reshape
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

// Function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'd': paddleX += 3; break;
        case 'a': paddleX -= 3; break;
        case 'q': exit(0); break;
        case 's':
            if (!startGame) {
                ballDirX = ballDirY = 1;
                speedRate = levels[gameLevel];
                startGame = 1;
                playerScore = 0;
                glutSetCursor(GLUT_CURSOR_NONE);
            }
            break;
    }
    if (paddleX > 15) {
        paddleX = 15;
    }
    if (paddleX < -15) {
        paddleX = -15;
    }
    if (startGame == 0) {
        paddleX = 0;
    }
    glutPostRedisplay();
}

// Function to check collision with bricks
void hitBrick() {
    int i, j;
    for (i = 1; i <= 4; i++)
        for (j = 1; j <= 10; j++) {
            if ((ballX >= brickArray[i][j].x - 19.5 - 0.1) && (ballX <= brickArray[i][j].x + 3 - 19.5 + 0.1)) {
                if (ballY >= brickArray[i][j].y + 5 - 0.1 && ballY <= brickArray[i][j].y + 5 + 1.2 + 0.1) {
                    brickArray[i][j].x = 0;
                    brickArray[i][j].y = 0;
                    ballDirY = ballDirY * -1;
                    playerScore++;
                }
            }
        }
}

// Function for idle operation
void idle() {
    hitBrick();
    if (ballX < -16 || ballX > 16 && startGame == 1) {
        ballDirX = ballDirX * -1;
    }
    if (ballY < -15 || ballY > 14 && startGame == 1) {
        ballDirY = ballDirY * -1;
    }
    ballX += ballDirX / (speedRate);
    ballY += ballDirY / (speedRate);
    speedRate -= 0.001;

    float x = paddleSizes[paddleSizeIndex];
    if (ballY <= -12.8 && ballX < (paddleX + x *

 2 / 3) && ballX > (paddleX + x / 3) && startGame == 1) {
        ballDirX = 1;
        ballDirY = 1;
    } else if (ballY <= -12.8 && ballX < (paddleX - x / 3) && ballX > (paddleX - x * 2 / 3) && startGame == 1) {
        ballDirX = -1;
        ballDirY = 1;
    } else if (ballY <= -12.8 && ballX < (paddleX + x / 3) && ballX > (paddleX - x / 3) && startGame == 1) {
        ballDirX = ballDirX;
        ballDirY = 1;
    } else if (ballY <= -12.8 && ballX < (paddleX - (x * 2 / 3)) && ballX > (paddleX - (x + 0.3)) && startGame == 1) {
        ballDirX = -1.5;
        ballDirY = 0.8;
    } else if (ballY <= -12.8 && ballX < (paddleX + (x + 0.3)) && ballX > (paddleX + x / 3) && startGame == 1) {
        ballDirX = 1.5;
        ballDirY = 0.8;
    } else if (ballY < -13) {
        startGame = 0;
        ballY = -12.8;
        ballX = 0;
        ballDirX = 0;
        ballDirY = 0;
        paddleX = 0;
    }
    glutPostRedisplay();
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Brick Breaker");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glEnable(GL_DEPTH_TEST);
    glutIdleFunc(idle);
    glutPassiveMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    lightsOn();
    addMenu();
    glutMainLoop();
    return 0;
}
