#include <iostream>
#include <GL/glut.h>

int last = 0;
int width  = 800;
int height = 600;
float stretch = 1;

struct Normal {
  float nx;
  float ny;
  float nz;
};

bool d3 = false;
int iter = 1;
#define WATER_LEN 100
double** water1;
double** water;
struct Normal** normals;
int active = 0;
bool running = true;
int drag = 0;
float rot_x = 0;
float rot_y = 0;

bool flip = true;

void display_func ();

void mouse_func (int button, int button_state, int x, int y)
{
  std::cout << "MouseButton: " << button << " " << button_state << " " 
         << x << " " << y << std::endl;
  if (button == 2)
    active = !button_state;

  int i = x*WATER_LEN/800;
  int j = (y*WATER_LEN/600);

  if (button == 0)
    {
      std::cout << "Splash1" << std::endl;
      int size = 10;
      for(int y = -size; y <  size; ++y)
        for(int x = -size; x < size; ++x)
          {
            double r = sqrt(x*x + y*y);
            double q = size*size - r*r;

            double x1 = x + .1;
            double y1 = y + .1;
            double r1 = sqrt(x1*x1 + y1*y1);
            double q1 = size*size - r1*r1;

            if (q > 0 && q1 > 0
                && (i+x < WATER_LEN-1) && (i+x > 1)
                && (j+y < WATER_LEN-1) && (j+y > 1))
              {
                water [i+x][j+y] -= sqrt(q)*.3;
                water1[i+x][j+y] -= sqrt(q1)*.3;//= water [i+x][j+y]*-0.4f;
              }
          }
    }
  else if (button == 1)
    {
      for(int x = 0; x < 20; ++x)
        for(int y = 0; y < 20; ++y)
        {
          water1[i+x][j+y]  = 0;
            water[i+x][j+y]   = 0;
          }

      /*
      for(int x = 0; x < 20; ++x)
      for(int y = 0; y < 20; ++y)
        {
          float power = -(100 - ((x-10)*(x-10)))/5.0 + -(100 - ((y-10)*(y-10)))/5.0;; 
          water1[i+x][j+y]  = power*.3;
          water[i+x][j+y]   = power*.3;
          }*/
    }
  else if (button == 2)
    {
      drag = !button_state;
    }
}

void idle_func ()
{
  if (!running)
    {
      static double t = 0.0f;
  
      t += .1f;
      /*
        for(int j = 0; j < 5; ++j)
        for(int i = 0; i < 5; ++i)
        {
        water[i + 50][50+j]  += .1*(sin(.5*t)*25);
        water1[i + 50][50+j] += .1*(sin(.5*t)*25);
        }
      */
      /*
        int i = 50;
        int j = 50;
        int size = 10;
        if (int(t*10) % 100 == 0)
        {
        for(int y = -size; y <  size; ++y)
        for(int x = -size; x < size; ++x)
        {
        double r = sqrt(x*x + y*y);
        double q = size*size - r*r;
        if (q > 0 
        && (i+x < WATER_LEN-1) && (i+x > 1)
        && (j+y < WATER_LEN-1) && (j+y > 1))
        {
        water1 [i+x][j+y] -= sqrt(q)*.3;
        //water1[i+x][j+y] = water [i+x][j+y];
        }
        }
        }
      */
      for (int k = 0; k < iter; ++k)
        {

          double c = 1.0f;
          double h = 1.0f;
          double dt = 0.1f;

          double A = c*dt/h * c*dt/h;
          double B = 2 - 4*A;   // use 2*A for 2d

          for(int j = 1; j < WATER_LEN - 1; ++j)
            for(int i = 1; i < WATER_LEN - 1; ++i)
              {
                water1[i][j] = A*(water[i-1][j-1] + water[i+1][j-1] + water[i-1][j+1] + water[i+1][j+1])
                  + B*water[i][j] - water1[i][j];
                water1[i][j] *= .9999f;
              }

          std::swap(water, water1);
        }
    }

  display_func();
  
}

void keyboard_func (unsigned char key, int x, int y)
{
  switch (key)
    {
    case 27: // Escape
      exit(0);
      break;

    case 'e':
      for(int j = 1; j < WATER_LEN - 1; ++j)
        for(int i = 1; i < WATER_LEN - 1; ++i)
          water1[i][j] = water[i][j];
      break;

    case 'o':
      last = !last;
      break;
      
    case 'a':
      d3 = !d3;
      break;

    case ' ':
      running = !running;
      break;

    case 'c':
      for (int y = 0; y < WATER_LEN; ++y)
        for (int x = 0; x < WATER_LEN; ++x)
          {
            water[x][y]  = 0;
            water1[x][y]  = 0;
          }
      break;
    }
}

void special_func (int key, int x, int y)
{
}

void mouse_motion_func (int x, int y)
{
  static int last_x = -1, last_y = -1;

  if (last_x == -1)
    {
      last_x = x;
      last_y = y;
    }

  int relative_x = last_x - x;
  int relative_y = last_y - y;

  last_x = x;
  last_y = y;

  if (drag)
    {
      rot_x += relative_x;
      rot_y += relative_y;
    }


  if (active && 0)
    {
      int i = x*WATER_LEN/800;
      int j = y*WATER_LEN/600;

      for(int y = -3; y < 3; ++y)
        for(int x = -3; x < 3; ++x)
          {
            water[i+x][j+y]  -= -.1;
            water1[i+x-1][j+y] -= -.1;
          }
    }
  /*
    if (active)
    {
    x -= 144;
    x /= 1;
    if (x > 0 && x < WATER_LEN)
    for(int i = x - 5; i < x + 5; ++i)
    water[x] += .3f;

    //std::cout << "x: " << x << std::endl;
    }*/
}

void crossProduct(float *c,float a[3], float b[3])  //finds the cross product of two vectors
{  
  c[0]=a[1]*b[2] - b[1]*a[2];
  c[1]=a[2]*b[0] - b[2]*a[0];
  c[2]=a[0]*b[1] - b[0]*a[1];
}

void 
getFaceNormal(float *norm,float pointa[3],float pointb[3],float pointc[3])
{
  float vect[2][3];
  int a,b;
  float point[3][3];

  for (a=0;a<3;++a)
    {
      point[0][a]=pointa[a];    //copies points into point[][]
      point[1][a]=pointb[a]; 
      point[2][a]=pointc[a];
    }


  for (a=0;a<2;++a)        //calculates vectors from point[0] to point[1]
    {                        //and point[0] to point[2]
      for (b=0;b<3;++b)
        {
          vect[a][b]=point[2-a][b]-point[0][b];      
        }
    }


  crossProduct(norm,vect[0],vect[1]);               //calculates vector at 90° to to 2 vectors
  //lnormalize(norm);                                  //makes the vector length 1
}


void display_func ()
{
  double** dwater;
  if (last)
    dwater = water;
  else
    dwater = water1;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  
  if (d3)
    flip = !flip;

  gluLookAt(flip? -10 : 10, dwater[WATER_LEN/2][120]*stretch - 20, 500,
            0, 0, 0,
            0, 1, 0);

  //glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  GLfloat position[] = { 0, -500.0, 555.0, 1.0 };
  
  /*  GLfloat position2[] = { 0.0, 0.0, 0.0, 0.0 };
      glLightfv(GL_LIGHT1, GL_POSITION, position);*/

  //GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  //GLfloat mat_shininess[] = { 1.0 };

  //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_shininess);


  glPushMatrix();

  glColor3d(1, 0, 0);
  glPushMatrix();
  glTranslatef(0, dwater[WATER_LEN/2][WATER_LEN/2]*10, 0);
  glutSolidSphere(50.0, 20, 16);
  glTranslatef(0, 0, 0);
  glutSolidSphere(20.0, 20, 16);
  glPopMatrix();

  glPushMatrix();
  //glTranslatef(-256, 0, -256);
  glScaled(10, 10, 10);
  glRotatef(45, 1.0, 0.0, 0.0);
  glRotatef(rot_y, 1.0, 0.0, 0.0);
  glRotatef(rot_x, 0.0, 1.0, 0.0);
  //glRotatef(45, 0.0, 1.0, 0.0);
  glTranslatef(-WATER_LEN/2, 0, -WATER_LEN/2);
  //glBegin (GL_LINES);
  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glLightfv(GL_LIGHT0, GL_POSITION, position);

  int step = 1;
  for(int j = step; j < WATER_LEN; j+=step)
    {
      for(int i = step; i < WATER_LEN; i+=step)
        {
          float p1[] = { i, stretch*dwater[i][j], j };
          float p3[] = { i-step, stretch*dwater[i-step][j], j };
          float p2[] = { i, stretch*dwater[i][j-step], j-step };
          float n[3] = { 0, 0, 1 };

          getFaceNormal(n, p1, p2, p3);
          normals[i][j].nx = n[0];
          normals[i][j].ny = n[1];
          normals[i][j].nz = n[2];
        }
    }

  for(int j = step; j < WATER_LEN; j+=step)
    {
      for(int i = step; i < WATER_LEN; i+=step)
        {
          if (1)
            {
              glColor3d(0.5, 0.5, 1);
              glBegin (GL_LINES);
              float p1[] = { i, dwater[i][j]*stretch, j };
              float p2[] = { i, dwater[i][j-step]*stretch, (j-step) };
              float p3[] = { (i-step), dwater[i-step][j-step]*stretch, (j-step) };
              float p4[] = { (i-step), dwater[i-step][j]*stretch, j };
              
              glNormal3f(normals[i][j].nx, normals[i][j].ny, normals[i][j].nz);
              glVertex3fv(p1);

              glNormal3f(normals[i][j-step].nx, normals[i][j-step].ny, normals[i][j-step].nz);
              glVertex3fv(p2);

              glNormal3f(normals[i-step][j-step].nx, normals[i-step][j-step].ny, normals[i-step][j-step].nz);
              glVertex3fv(p3);



              glNormal3f(normals[i][j].nx, normals[i][j].ny, normals[i][j].nz);
              glVertex3fv(p1);

              glNormal3f(normals[i-step][j-step].nx, normals[i-step][j-step].ny, normals[i-step][j-step].nz);
              glVertex3fv(p3);

              glNormal3f(normals[i-step][j].nx, normals[i-step][j].ny, normals[i-step][j].nz);
              glVertex3fv(p4);

              glEnd ();
            }
          else
            {
              float p1[] = { i, dwater[i][j]*stretch, j };
              float p2[] = { i, dwater[i][j-step]*stretch, (j-step) };

              glColor3d(1.0, 1.0, 1);
              glBegin (GL_LINES);
              glVertex3fv (p1);
              glVertex3fv (p2);
              glEnd ();  
            }
        }
    }
  glPopMatrix();
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}

void reshape_func(int w, int h)
{
  glViewport (0,0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  gluPerspective(80,  // fov
                 (GLfloat)w/(GLfloat)h, // aspect
                 5, 10000); // zNear, zFar

  //glOrtho(-w/2, w/2, h/2, -h/2, -100000, 100000);


  //glOrtho(0, w, h, h, -100000, 100000);
  glMatrixMode(GL_MODELVIEW);
  width  = w;
  height = h;
}

int main(int argc, char** argv)
{
  water  = new double*[WATER_LEN];
  water1 = new double*[WATER_LEN];
  normals = new Normal*[WATER_LEN];
  
  for(int i = 0; i < WATER_LEN; ++i)
    {
      water[i]  = new double[WATER_LEN];
      water1[i] = new double[WATER_LEN];
      normals[i] = new Normal[WATER_LEN];

      for(int j = 0; j < WATER_LEN; ++j)
        {
          water[i][j] = 0;
          water1[i][j] = 0;

          normals[i][j].nx = 0;
          normals[i][j].ny = 0;
          normals[i][j].nz = 0;
        }
    }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  //glutInitWindowPosition(100, 100); don't care
  glutSetWindow(glutCreateWindow("Water Simulation"));

  glutDisplayFunc(::display_func);
  glutReshapeFunc(::reshape_func);
  glutMouseFunc(::mouse_func);

  glutMotionFunc (::mouse_motion_func);
  glutPassiveMotionFunc (::mouse_motion_func);

  glutIdleFunc (::idle_func);
  glutKeyboardFunc(::keyboard_func);
  glutSpecialFunc(::special_func);

  glClearColor (0.0, 0.0, 0.0, 0.1);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);

  //  glEnable(GL_LINE_SMOOTH);

  glutMainLoop(); 
}

/* EOF */

