
/* Derived from scene.c in the The OpenGL Programming Guide */
#include "gl_setup.h"
#include "stdbool.h"

const bool SHOW_EXAMPLE = false;

/* flags used to control the appearance of the image */
int GLSetup_lineDrawing = 1;    // draw polygons as solid or lines
int GLSetup_lighting = 0;       // use diffuse and specular lighting
int GLSetup_smoothShading = 0;  // smooth or flat shading
int GLSetup_textures = 0;

GLuint GLSetup_textureID[1];

// Colors
GLfloat GLSetup_blue[] = {0.0, 0.0, 1.0, 1.0};
GLfloat GLSetup_red[] = {1.0, 0.0, 0.0, 1.0};
GLfloat GLSetup_green[] = {0.0, 1.0, 0.0, 1.0};
GLfloat GLSetup_white[] = {1.0, 1.0, 1.0, 1.0};

/*  Initialize material property and light source.
 */
void GlSetup_init(void) {
  GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
  GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_full_off[] = {0.0, 0.0, 0.0, 1.0};
  GLfloat light_full_on[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

  /* if lighting is turned on then use ambient, diffuse and specular
     lights, otherwise use ambient lighting only */
  if (GLSetup_lighting == 1) {
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  } else {
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_full_on);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_full_off);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_full_off);
  }
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
}

void GLSetup_display(void) {
  if (SHOW_EXAMPLE)
    GlSetup_displayExample();
  else
    GlSetup_displayLSystem();
}

void GlSetup_drawLSystem() {
  FileReader* fr = new_FileReader("./assets/sample1.txt");
  LSystem* ls = new_LSystem(fr->line[2], atoi(fr->line[1]), atof(fr->line[0]));
  /* set starting location of objects */
  glPushMatrix();
  glTranslatef(0.0, 0.0, -7.0);
  glRotatef(20.0, 1.0, 0.0, 0.0);
  GlSetup_LSystemCondition(ls->final, ls->angle);
  glPopMatrix();
  // Free
  LSystem_free(ls);
}

void GlSetup_setMaterial() {
  glMaterialf(GL_FRONT, GL_SHININESS, 30.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, GLSetup_red);
  glMaterialfv(GL_FRONT, GL_SPECULAR, GLSetup_white);
}

void GlSetup_LSystemCondition(char* start, double angle) {
  char* final = strdup(start);
  printf("Drawing: %s\n", final);
  GlSetup_setMaterial();
  for (int x = 0; x < strlen(final); x++) {
    char curState = final[x];
    if (curState == 'F') {
      printf("Draw solid sphere.\n");
      glutSolidSphere(0.1, 15, 15);
    } else if (curState == '+') {
      printf("Rotate z axis by %f degrees to the right.\n", angle);
      glRotatef(angle, 0, 0, 1);
      glTranslatef(0, 0.2, 0);
    } else if (curState == '-') {
      printf("Rotate z axis by %f degrees to the left.\n", angle);
      glRotatef(-angle, 0, 0, 1);
      glTranslatef(0, 0.2, 0);
    } else if (curState == '[') {
      printf("Push matrix.\n");
      glPushMatrix();
      glTranslatef(0, 0.2, 0);
    } else if (curState == ']') {
      printf("Pop matrix.\n");
      glPopMatrix();
      glTranslatef(0, 0.2, 0);
    }
  }
  free(final);
}

void GlSetup_displayExample(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

  /* set starting location of objects */
  glPushMatrix();
  glTranslatef(0.0, 0.0, -7.0);
  glRotatef(20.0, 1.0, 0.0, 0.0);

  /* give all objects the same shininess value */
  glMaterialf(GL_FRONT, GL_SHININESS, 30.0);

  /* set colour of cone */
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, GLSetup_red);
  glMaterialfv(GL_FRONT, GL_SPECULAR, GLSetup_white);
  /* move to location for object then draw it */
  glPushMatrix();
  glTranslatef(-0.75, -0.5, 0.0);
  glRotatef(270.0, 1.0, 0.0, 0.0);
  glutSolidCone(1.0, 2.0, 15, 15);
  glPopMatrix();

  /* set colour of sphere */
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, GLSetup_green);
  glMaterialfv(GL_FRONT, GL_SPECULAR, GLSetup_white);
  /* move to location for object then draw it */
  glPushMatrix();
  glTranslatef(0.75, 0.0, -1.0);

  /* turn texturing on */
  if (GLSetup_textures == 1) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, GLSetup_textureID[0]);
    /* if textured, then use GLSetup_white as base colour */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, GLSetup_white);
  }

  glutSolidSphere(1.0, 15, 15);

  if (GLSetup_textures == 1) glDisable(GL_TEXTURE_2D);
  glPopMatrix();

  /* set colour of torus */
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, GLSetup_blue);
  glMaterialfv(GL_FRONT, GL_SPECULAR, GLSetup_white);
  /* move to location for object then draw it */
  glPushMatrix();
  glTranslatef(-0.75, 0.5, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glutSolidTorus(0.275, 0.85, 15, 15);
  glPopMatrix();

  glPopMatrix();
  glFlush();
}

void GlSetup_displayLSystem() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

  GlSetup_drawLSystem();

  /* turn texturing on */
  if (GLSetup_textures == 1) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, GLSetup_textureID[0]);
    /* if textured, then use GLSetup_white as base colour */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, GLSetup_white);
  } else if (GLSetup_textures == 1)
    glDisable(GL_TEXTURE_2D);
  glFlush();
}

void GlSetup_reshape(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void GlSetup_keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27:
    case 'q':
      exit(0);
      break;

    case '1':  // draw polygons as outlines
      GLSetup_lineDrawing = 1;
      GLSetup_lighting = 0;
      GLSetup_smoothShading = 0;
      GLSetup_textures = 0;
      GlSetup_init();
      GLSetup_display();
      printf("1 is clicked.\n");
      break;

    case '2':  // draw polygons as filled
      GLSetup_lineDrawing = 0;
      GLSetup_lighting = 0;
      GLSetup_smoothShading = 0;
      GLSetup_textures = 0;
      GlSetup_init();
      GLSetup_display();
      printf("2 is clicked.\n");
      break;

    case '3':  // diffuse and specular lighting, flat shading
      GLSetup_lineDrawing = 0;
      GLSetup_lighting = 1;
      GLSetup_smoothShading = 0;
      GLSetup_textures = 0;
      GlSetup_init();
      GLSetup_display();
      printf("3 is clicked.\n");
      break;

    case '4':  // diffuse and specular lighting, smooth shading
      GLSetup_lineDrawing = 0;
      GLSetup_lighting = 1;
      GLSetup_smoothShading = 1;
      GLSetup_textures = 0;
      GlSetup_init();
      GLSetup_display();
      printf("4 is clicked.\n");
      break;

    case '5':  // texture with  smooth shading
      GLSetup_lineDrawing = 0;
      GLSetup_lighting = 1;
      GLSetup_smoothShading = 1;
      GLSetup_textures = 1;
      GlSetup_init();
      GLSetup_display();
      printf("5 is clicked.\n");
      break;
  }
}

void GlSetup_loadTexture(char* filePath) {
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

void GlSetup_run(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(1024, 768);
  glutCreateWindow(argv[0]);
  printf("Running OpenGL Version: %s\n", glGetString(GL_VERSION));

  // Draw
  GlSetup_init();
  GlSetup_loadTexture("./assets/image.txt");
  glutReshapeFunc(GlSetup_reshape);
  glutDisplayFunc(GLSetup_display);
  glutKeyboardFunc(GlSetup_keyboard);

  // Loop
  glutMainLoop();
}
