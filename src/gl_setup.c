
/* Derived from scene.c in the The OpenGL Programming Guide */
#include "gl_setup.h"

#include "stdbool.h"

/* flags used to control the appearance of the image */
int GLSetup_lineDrawing = 1;    // draw polygons as solid or lines
int GLSetup_lighting = 0;       // use diffuse and specular lighting
int GLSetup_smoothShading = 0;  // smooth or flat shading
int GLSetup_textures = 0;
GLuint GLSetup_textureID[1];

// Colors
const GLfloat BLUE[] = {0.0, 0.0, 1.0, 1.0};
const GLfloat RED[] = {1.0, 0.0, 0.0, 1.0};
const GLfloat GREEN[] = {0.0, 1.0, 0.0, 1.0};
const GLfloat WHITE[] = {1.0, 1.0, 1.0, 1.0};

// Points
Point GLSetup_cameraPos = {.x = 0, .y = 0, .z = 0};

/* -------------------------------------------------------------------------- */
/*                              penGL functions                              */
/* -------------------------------------------------------------------------- */

void runOpenGL(int argc, char** argv) {
  if (argc == 0 || argv[1] == NULL) {
    printf(
        "NO ARGUMENT FOUND! PLEASE SPECIFY ARGUMENT. Please read the README "
        "provided for more information.\n");
    return;
  }
  printf("Running with file: %s\n", argv[1]);
  LSystem_setGlobalFileName(argv[1]);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(1024, 768);
  glutCreateWindow(argv[0]);
  printf("Running OpenGL Version: %s\n", glGetString(GL_VERSION));

  // Draw
  initLightSource();
  loadTexture("./assets/image.txt");
  glutReshapeFunc(reshapeWindow);
  glutDisplayFunc(render);
  glutKeyboardFunc(keyboardControl);
  glutSpecialFunc(specialControl);
  glutMotionFunc(mouseControl);

  // Loop
  glutMainLoop();
  LSystem_freeGlobalFileName();
}

void reshapeWindow(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 256.0 * 64);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void loadTexture(char* filePath) {
  FILE* fp;
  int i, j;
  int GLSetup_red, GLSetup_green, GLSetup_blue;
  GLubyte Image[64][64][4];

  if ((fp = fopen(filePath, "r")) == 0) {
    printf("Error, failed to find the file named image.txt.\n");
    exit(0);
  }

  for (i = 0; i < 64; i++) {
    for (j = 0; j < 64; j++) {
      fscanf(fp, "%d %d %d", &GLSetup_red, &GLSetup_green, &GLSetup_blue);
      Image[i][j][0] = GLSetup_red;
      Image[i][j][1] = GLSetup_green;
      Image[i][j][2] = GLSetup_blue;
      Image[i][j][3] = 255;
    }
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(1, GLSetup_textureID);
  glBindTexture(GL_TEXTURE_2D, GLSetup_textureID[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               Image);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);

  fclose(fp);
}

/*  Initialize material property and light source. */
void initLightSource(void) {
  GLfloat lightAmbient[] = {0.0, 0.0, 0.0, 1.0};
  GLfloat lightDiffuse[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat lightSpecular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat lightFullOff[] = {0.0, 0.0, 0.0, 1.0};
  GLfloat lightFullOn[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat lightPosition[] = {1.0, 1.0, 1.0, 0.0};
  /* if lighting is turned on then use ambient, diffuse and specular
     lights, otherwise use ambient lighting only */
  if (GLSetup_lighting == 1) {
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
  } else {
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightFullOn);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightFullOff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightFullOff);
  }
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  // Enable the light and depth
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
}

void checkForVectorAndShaderCondition() {
  /* draw surfaces as either smooth or flat shaded */
  if (GLSetup_smoothShading == 1)
    glShadeModel(GL_SMOOTH);
  else
    glShadeModel(GL_FLAT);
  /* draw polygons as either solid or outlines */
  if (GLSetup_lineDrawing == 1)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void checkForTextureCondition(void (*draw)(void)) {
  /* turn texturing on */
  if (GLSetup_textures == 1) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, GLSetup_textureID[0]);
    /* if textured, then use GLSetup_white as base colour */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, WHITE);
  }
  if (draw != NULL) draw();
  if (GLSetup_textures == 1) glDisable(GL_TEXTURE_2D);
}

void setStartingPos() {
  glTranslatef(0 + GLSetup_cameraPos.x, 0 + GLSetup_cameraPos.y,
               -100.0 + GLSetup_cameraPos.z);
  glRotatef(20.0, 1.0, 0.0, 0.0);
}

void setMaterial() {
  glMaterialf(GL_FRONT, GL_SHININESS, 30.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, GREEN);
  glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
}

void render(void) {
  initLightSource();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  setMaterial();
  setStartingPos();

  //  Draw the l-system
  checkForVectorAndShaderCondition();
  checkForTextureCondition(LSystem_draw);
  glPopMatrix();
  glFlush();
}

/* --------------------------------------------------------------------------*/
/*                             Function controller                            */
/* --------------------------------------------------------------------------*/

void specialControl(int key, int x, int y) {
  const double CAMERA_MOVEMENT = 25;
  if (key == 'q' || key == 27) {
    exit(0);
  } else if (key == 'w' || key == GLUT_KEY_UP) {
    GLSetup_cameraPos.y += CAMERA_MOVEMENT;
    render();
    printf("w key is pressed, y=%f.\n", GLSetup_cameraPos.y);
  } else if (key == 's' || key == GLUT_KEY_DOWN) {
    GLSetup_cameraPos.y -= CAMERA_MOVEMENT;
    render();
    printf("s key is pressed, y=%f.\n", GLSetup_cameraPos.y);
  } else if (key == 'a' || key == GLUT_KEY_LEFT) {
    GLSetup_cameraPos.x -= CAMERA_MOVEMENT;
    render();
    printf("a key is pressed, x=%f.\n", GLSetup_cameraPos.x);
  } else if (key == 'd' || key == GLUT_KEY_RIGHT) {
    GLSetup_cameraPos.x += CAMERA_MOVEMENT;
    render();
    printf("d key is pressed, x=%f.\n", GLSetup_cameraPos.x);
  }
}

void keyboardControl(unsigned char key, int x, int y) {
  if (key == '1') {  // draw polygons as outlines
    GLSetup_lineDrawing = 1;
    GLSetup_lighting = 0;
    GLSetup_smoothShading = 0;
    GLSetup_textures = 0;
    render();
    printf("1 is clicked.\n");
  } else if (key == '2') {  // draw polygons as filled
    GLSetup_lineDrawing = 0;
    GLSetup_lighting = 0;
    GLSetup_smoothShading = 0;
    GLSetup_textures = 0;
    render();
    printf("2 is clicked.\n");
  } else if (key == '3') {  // diffuse and specular lighting, flat shading
    GLSetup_lineDrawing = 0;
    GLSetup_lighting = 1;
    GLSetup_smoothShading = 0;
    GLSetup_textures = 0;
    render();
    printf("3 is clicked.\n");
  } else if (key == '4') {  // diffuse and specular lighting, smooth shading
    GLSetup_lineDrawing = 0;
    GLSetup_lighting = 1;
    GLSetup_smoothShading = 1;
    GLSetup_textures = 0;
    render();
    printf("4 is clicked.\n");
  } else if (key == '5') {  // texture with  smooth shading
    GLSetup_lineDrawing = 0;
    GLSetup_lighting = 1;
    GLSetup_smoothShading = 1;
    GLSetup_textures = 1;
    render();
    printf("5 is clicked.\n");
  }
}

void mouseControl(int x, int y) {
  const bool SHOW_DEBUG = false;
  const char DEBUG[] = "GLSetup_mouseControl():";
  GLSetup_cameraPos.z = (y * 10) - (1000 * 5);
  if (SHOW_DEBUG) printf("%s x value is %d.\n", DEBUG, x);
  if (SHOW_DEBUG) printf("%s y value is %d.\n", DEBUG, y);
  if (SHOW_DEBUG) printf("GLSetup_cameraPos.z: %f.\n", GLSetup_cameraPos.z);
  render();
}
