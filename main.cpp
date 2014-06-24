#ifdef WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>  // This is located in the “GLUT” directory on MacOSX
#endif
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include <iostream>       // std::cout
#include <future>         // std::async, std::future
#include <chrono>         // std::chrono::milliseconds

#include "./raytracing.h"
#include "./config.h"
#include "./mesh.h"
#include "./traqueboule.h"

Vec3Df MyCameraPosition;

std::vector<Vec3Df> MyLightPositions;

//image class just dumped to hide...
class RGBValue
{
  public:
  RGBValue(float rI=0, float gI=0, float bI=0)
  : r(rI)
  , g(gI)
  , b(bI)
  {
    if (r>1)
      r=1.0;
    if (g>1)
      g=1.0;
    if (b>1)
      b=1.0;

    if (r<0)
      r=0.0;
    if (g<0)
      g=0.0;
    if (b<0)
      b=0.0;
  };

  float operator[](int i) const
  {
    switch(i)
    {
      case 0:
        return r;
      case 1:
        return g;
      case 2:
        return b;
      default:
        return r;
    }
  }
  float & operator[](int i)
  {
    switch(i)
    {
      case 0:
        return r;
      case 1:
        return g;
      case 2:
        return b;
      default:
        return r;
    }
  }
  float r, b,g;
};





class Image
{
  public:
  Image(int width, int height)
  : _width(width)
  , _height(height)
  {
    _image.resize(3*_width*_height);
  }
  void setPixel(int i, int j, const RGBValue & rgb)
  {
    _image[3*(_width*j+i)]=rgb[0];
    _image[3*(_width*j+i)+1]=rgb[1];
    _image[3*(_width*j+i)+2]=rgb[2];

  }
  std::vector<float> _image;
  int _width;
  int _height;

  bool writeImage(const char * filename);
};

bool Image::writeImage(const char * filename)
{
  FILE* file;
    file = fopen(filename, "wb");
  if (!file)
  {
    printf("dump file problem... file\n");
    return false;
  }

  fprintf(file, "P6\n%i %i\n255\n",_width, _height);


  std::vector<unsigned char> imageC(_image.size());

  for (unsigned int i=0; i<_image.size();++i)
    imageC[i]=(unsigned char)(_image[i]*255.0f);

  int t = fwrite(&(imageC[0]), _width * _height * 3, 1, file);
  if (t!=1)
  {
    printf("Dump file problem... fwrite\n");
    return false;
  }

  fclose(file);
  return true;
}










Mesh MyMesh; //Main mesh



// Utilisé pour essayer différents types de rendu
// Utilisé via le paramètre "-t" en ligne de commande
enum { TRIANGLE=0, MODEL=1, };
unsigned int type = MODEL;

void dessinerRepere(float length)
{
  glDisable(GL_LIGHTING);

  glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(length,0,0);

    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,length,0);

    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,length);
  glEnd();
  glEnable(GL_LIGHTING);

}

/**
 * Appel des différentes fonctions de dessin
*/
void dessiner( )
{
  switch( type )
  {
  case TRIANGLE:
    glutSolidSphere(1,10,10);
    dessinerRepere(1);
    break;
  case MODEL:
    {
      MyMesh.draw();
      //glBegin(GL_TRIANGLES);

      //for (unsigned int i=0;i<MyMesh.triangles.size();++i)
      //{
      //  glColor3f(MyMesh.materials[MyMesh.triangleMaterials[i]].Kd()[0], MyMesh.materials[MyMesh.triangleMaterials[i]].Kd()[1], MyMesh.materials[MyMesh.triangleMaterials[i]].Kd()[2]);
      //  glVertex3f(MyMesh.vertices[MyMesh.triangles[i].v[0]].p[0], MyMesh.vertices[MyMesh.triangles[i].v[0]].p[1], MyMesh.vertices[MyMesh.triangles[i].v[0]].p[2]);
      //  glVertex3f(MyMesh.vertices[MyMesh.triangles[i].v[1]].p[0], MyMesh.vertices[MyMesh.triangles[i].v[1]].p[1], MyMesh.vertices[MyMesh.triangles[i].v[1]].p[2]);
      //  glVertex3f(MyMesh.vertices[MyMesh.triangles[i].v[2]].p[0], MyMesh.vertices[MyMesh.triangles[i].v[2]].p[1], MyMesh.vertices[MyMesh.triangles[i].v[2]].p[2]);
      //}
      //glEnd();
    }
  default:
    dessinerRepere(1); // Par défaut
    break;
  }
  yourDebugDraw();
}

void animate()
{
  MyCameraPosition=getCameraPosition();
  glutPostRedisplay();
}



void display(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

/**
 * Programme principal
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    // couches du framebuffer utilisees par l'application
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

    // position et taille de la fenetre
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(config.viewportSize_X, config.viewportSize_Y);
    glutCreateWindow(argv[0]);

    // Initialisation du point de vue
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,0,-4);
    tbInitTransform();     // initialisation du point de vue
    tbHelp();                      // affiche l'aide sur la traqueboule
  MyCameraPosition=getCameraPosition();
    //
    // Active la lumière
    // Pour la partie
    // ECLAIRAGE

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable(GL_COLOR_MATERIAL);
    int LightPos[4] = {0,0,3,1};
    int MatSpec [4] = {1,1,1,1};
    glLightiv(GL_LIGHT0,GL_POSITION,LightPos);
    //glMaterialiv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
    //glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,10);

  glEnable(GL_NORMALIZE);
    glClearColor (0.0, 0.0, 0.0, 0.0);

  // Details sur le mode de tracé
    glEnable( GL_DEPTH_TEST );            // effectuer le test de profondeur
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glPolygonMode(GL_FRONT,GL_FILL);
    glPolygonMode(GL_BACK,GL_LINE);
    glShadeModel(GL_SMOOTH);


  // cablage des callback
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMouseFunc(tbMouseFunc);    // traqueboule utilise la souris
    glutMotionFunc(tbMotionFunc);  // traqueboule utilise la souris
    glutIdleFunc( animate);

  init();

  //imidiate render

    // lancement de la boucle principale
    glutMainLoop();


    return 0;  // instruction jamais exécutée
}

/**
 * Fonctions de gestion opengl à ne pas toucher
 */
// Actions d'affichage
// Ne pas changer
void display(void)
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);
    // Effacer tout
    glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT); // la couleur et le z

    glLoadIdentity();  // repere camera

    tbVisuTransform(); // origine et orientation de la scene

    dessiner( );

    glutSwapBuffers();
  glPopAttrib();
}
// pour changement de taille ou desiconification
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho (-1.1, 1.1, -1.1,1.1, -1000.0, 1000.0);
    gluPerspective (50, (float)w/h, 1, 10);
    glMatrixMode(GL_MODELVIEW);
}


//transformer le x, y en position 3D
void produceRay(int x_I, int y_I, Vec3Df * origin, Vec3Df * dest)
{
    int viewport[4];
    double modelview[16];
    double projection[16];
    //point sur near plane
    //double positionN[3];
    //point sur far plane
    //double positionF[3];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview); //recuperer matrices
    glGetDoublev(GL_PROJECTION_MATRIX, projection); //recuperer matrices
    glGetIntegerv(GL_VIEWPORT, viewport);//viewport
    int y_new = viewport[3] - y_I;

    double x, y, z;

    gluUnProject(x_I, y_new, 0, modelview, projection, viewport, &x, &y, &z);
    origin->p[0]=float(x);
    origin->p[1]=float(y);
    origin->p[2]=float(z);
    gluUnProject(x_I, y_new, 1, modelview, projection, viewport, &x, &y, &z);
    dest->p[0]=float(x);
    dest->p[1]=float(y);
    dest->p[2]=float(z);
}

void produceRay(int x_I, int y_I, Vec3Df & origin, Vec3Df & dest)
{
  produceRay(x_I, y_I, &origin, &dest);
}
//transformer le x, y en position 3D
// void produceFrustrum(int viewportSize_X, int viewportSize_Y, Frustrum * f)
// {
    // int xMin = 0;
    // int xMax = viewportSize_X-1;
    // int yMin = 0;
    // int yMax = viewportSize_Y-1;

    // int viewport[4];
    // double modelview[16];
    // double projection[16];
    // //point sur near plane
    // //double positionN[3];
    // //point sur far plane
    // //double positionF[3];
    // glGetDoublev(GL_MODELVIEW_MATRIX, modelview); //recuperer matrices
    // glGetDoublev(GL_PROJECTION_MATRIX, projection); //recuperer matrices
    // glGetIntegerv(GL_VIEWPORT, viewport);//viewport


    // // Equiv of:
    // // produceRay(0, 0, &(f.origin00), &(f.dest00));

    // // produceRay(0, config.viewportSize_Y-1, &(f.origin01), &(f.dest01));
    // // produceRay(config.viewportSize_X-1, 0, &(f.origin10), &(f.dest10));
    // // produceRay(config.viewportSize_X-1, config.viewportSize_Y-1, &(f.origin11), &(f.dest11));

    // int x_I = 0;
    // int y_I = 0;
    // //

    // int y_new = viewport[3] - y_I;
    // double x, y, z;
    // gluUnProject(x_I, y_new, 0, modelview, projection, viewport, &x, &y, &z);
    // origin->p[0]=float(x);
    // origin->p[1]=float(y);
    // origin->p[2]=float(z);
    // gluUnProject(x_I, y_new, 1, modelview, projection, viewport, &x, &y, &z);
    // dest->p[0]=float(x);
    // dest->p[1]=float(y);
    // dest->p[2]=float(z);
// }










int pixelsTotal, pixelsRendered;
float fraction, previousFraction;

bool progressBar = true;
int barLength = 100;

bool timing = true;
clock_t t1, t2;

void progressBarStart() {
  pixelsTotal = config.renderSize_X * config.renderSize_Y;
  previousFraction = 0;

  cout << " 0%";
  for (unsigned int i = 0; i < barLength; ++i) cout << " ";
  cout << "100%" << endl;
  cout << "  |";
  for (unsigned int i = 0; i < barLength; ++i) cout << " ";
  cout << "|" << endl;
  cout << "   ";
}
void timingStart() {
  t1 = clock();
}
void timingEnd() {
  t2 = clock();
  float diffSeconds = ((static_cast<float>(t2) - static_cast<float>(t1)) / 1000000.0F);
  cout << endl;
  cout << "   Render time: " << diffSeconds << " seconds" << endl;
  cout << endl;
}
void progressBarUpdate(unsigned int x, unsigned int y) {
  pixelsRendered = (y * config.renderSize_X) + x;
  if (pixelsRendered > 0)
    fraction = static_cast<float>(pixelsRendered) / static_cast<float>(pixelsTotal);
  else
    fraction = 0;
  float fDelta = fraction - previousFraction;
  if (fDelta > 1.0f/barLength) {
    cout << "#";
    cout.flush();
    // Fraction plus residual
    previousFraction = fraction + (1.0f/barLength - fDelta);
  }
}
void progressBarEnd() {
  cout << "#" << endl;
}


RGBValue raytracePixel(Vec3Df origin, Vec3Df dest) {
  Vec3Df rgb = performRayTracing(origin, dest);
  return RGBValue(rgb[0], rgb[1], rgb[2]);
}





// prise en compte du clavier
void keyboard(unsigned char key, int x, int y) {
  printf("key %d pressed at %d,%d\n",key,x,y);
  fflush(stdout);
  switch (key) {
    case 'L':
      MyLightPositions.push_back(getCameraPosition());
      break;
    case 'l':
      MyLightPositions[MyLightPositions.size()-1]=getCameraPosition();
      break;
    case 'r': {

      //C'est nouveau!!!
      //commencez ici et lancez vos propres fonctions par rayon.
      cout << config.toString() << endl;
      cout << "Starting raytracing ..." << endl;

      Image result(config.renderSize_X,config.renderSize_Y);
      Vec3Df origin00, dest00;
      Vec3Df origin01, dest01;
      Vec3Df origin10, dest10;
      Vec3Df origin11, dest11;

      produceRay(0, 0, origin00, dest00);
      produceRay(0, config.viewportSize_Y-1, origin01, dest01);
      produceRay(config.viewportSize_X-1, 0, origin10, dest10);
      produceRay(config.viewportSize_X-1, config.viewportSize_Y-1, origin11, dest11);

      if (config.threads == 1) {
        if (timing)
          timingStart();
        if (progressBar)
          progressBarStart();

        for (unsigned int y=0; y<config.renderSize_X;++y)
          for (unsigned int x=0; x<config.renderSize_Y;++x) {


            //svp, decidez vous memes quels parametres vous allez passer à la fonction
            //e.g., maillage, triangles, sphères etc.
            float xscale=1.0f-float(x)/(config.renderSize_X-1);
            float yscale=1.0f-float(y)/(config.renderSize_Y-1);

            Vec3Df origin, dest;
            origin=yscale*(xscale*origin00+(1-xscale)*origin10)+
              (1-yscale)*(xscale*origin01+(1-xscale)*origin11);
            dest=yscale*(xscale*dest00+(1-xscale)*dest10)+
              (1-yscale)*(xscale*dest01+(1-xscale)*dest11);

            RGBValue p = raytracePixel(origin, dest);
            result.setPixel(x, y, p);

          // Update progress bar in console output
          if (progressBar)
            progressBarUpdate(x, y);
        }
        if (progressBar)
          progressBarEnd();
        if (timing)
          timingEnd();
      } else if (config.threads > 1) {
        if (timing)
          timingStart();
        if (progressBar)
          progressBarStart();
        for (unsigned int y = 0; y < config.renderSize_X; ++y) {
          for (unsigned int x = 0; x < config.renderSize_Y; x += config.threads) {
            std::vector<std::future<RGBValue>> tracedPixel;
            // call function asynchronously:
            for (unsigned int thread = 0;
              thread < config.threads && x < config.renderSize_X;
              ++thread) {
              //svp, decidez vous memes quels parametres vous allez passer à la fonction
              //e.g., maillage, triangles, sphères etc.
              float xscale=1.0f-float(x)/(config.renderSize_X-1);
              float yscale=1.0f-float(y)/(config.renderSize_Y-1);

              Vec3Df origin, dest;
              origin=yscale*(xscale*origin00+(1-xscale)*origin10)+
                (1-yscale)*(xscale*origin01+(1-xscale)*origin11);
              dest=yscale*(xscale*dest00+(1-xscale)*dest10)+
                (1-yscale)*(xscale*dest01+(1-xscale)*dest11);

              tracedPixel.push_back(std::async(raytracePixel, origin, dest));
            }
            for (unsigned int thread = 0;
              thread < config.threads && x < config.renderSize_X;
              ++thread) {
              tracedPixel[thread].wait();
            }

            for (unsigned int thread = 0;
              thread < config.threads && x < config.renderSize_X;
              ++thread) {
              RGBValue p = tracedPixel[thread].get();
            }
            if (progressBar)
              progressBarUpdate(x, y);
          }
        }
        }
        if (progressBar)
          progressBarEnd();
        if (timing)
          timingEnd();
        result.writeImage("result.ppm");

        // return 0;
      }
      break;
    }
    case 27:     // touche ESC
      exit(0);
  }

  yourKeyboardFunc(key,x,y);
}

