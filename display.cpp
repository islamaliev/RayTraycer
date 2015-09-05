#include "Transform.h"
#include "variables.h"
#include "readfile.h"

void transformvec(const float input[4], float output[4])
{
    float modelview[16]; // in column major order
//  glGetFloatv(GL_MODELVIEW_MATRIX, modelview);

    for (int i = 0; i < 4; i++)
    {
        output[i] = 0;
        for (int j = 0; j < 4; j++)
        {
            output[i] += modelview[4 * j + i] * input[j];
        }
    }
}

void display()
{
//  glMatrixMode(GL_MODELVIEW);
    mat4 mv;

    mv = glm::lookAt(eye, center, up);

    /*glLoadMatrixf(&mv[0][0]);

    if (numused)
    {
      glUniform1i(enablelighting, true);

      for (int j = 0; j < numused; j++)
      {
        transformvec(&lightposn[j * 4], &lightransf[j * 4]);
      }

      glUniform4fv(lightpos, 10, lightransf);
      glUniform4fv(lightcol, 10, lightcolor);
      glUniform1i(numusedcol, numused);

    } else {
      glUniform1i(enablelighting,false);
    }

    mat4 sc(1.0) , tr(1.0), transf(1.0);
    sc = Transform::scale(sx,sy,1.0);
    tr = Transform::translate(tx,ty,0.0);
    mv = mv * tr * sc;

    glLoadMatrixf(&mv[0][0]);

    for (int i = 0 ; i < numobjects ; i++) {
  //  for (int i = 1 ; i < 2 ; i+=1) {
      object* obj = &(objects[i]); // Grabs an object struct.

      mat4 objM = mv * obj->transform;
      glLoadMatrixf(&objM[0][0]);

      glUniform4fv(ambientcol,1, obj->ambient);
      glUniform4fv(diffusecol,1, obj->diffuse);
      glUniform4fv(specularcol,1, obj->specular);
      glUniform4fv(emissioncol,1, obj->emission);
      glUniform1f(shininesscol, obj->shininess);

      if (obj->type == cube) {
        glutSolidCube(obj->size);
      }
      else if (obj->type == sphere) {
        const int tessel = 20;
        glutSolidSphere(obj->size, tessel, tessel);
      }
      else if (obj->type == teapot) {
        glutSolidTeapot(obj->size);
      }

    }

    glutSwapBuffers();*/
}
