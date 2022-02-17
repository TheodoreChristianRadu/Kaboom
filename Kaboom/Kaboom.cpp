#include "Game.h"
#include <glut.h>

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    
    glutInitWindowPosition(0,0);
    glutInitWindowSize(800,800);
    glutCreateWindow("Kaboom");
    
    glutReshapeFunc(Game::Reshape);
    glutDisplayFunc(Game::Render);

    glutKeyboardFunc(Game::Validate);
    glutSpecialFunc(Game::Move);
    
    Game::Initialize();

    glutMainLoop();
}
