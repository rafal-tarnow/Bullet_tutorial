//http://www.youtube.com/user/thecplusplusguy
//bullet physics tutorial 2, adding more shapes
#include <iostream>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "camera.h"
#include <bullet/btBulletDynamicsCommon.h>
#include "physics_engine.hpp"

camera cam;
GLUquadricObj* quad;

PhysicsEngine *physics;

void renderSphere(btRigidBody* sphere)
{
    if(sphere->getCollisionShape()->getShapeType()!=SPHERE_SHAPE_PROXYTYPE)
        return;
    glColor3f(1,0,0);
    float r=((btSphereShape*)sphere->getCollisionShape())->getRadius();
    btTransform t;
    sphere->getMotionState()->getWorldTransform(t);
    float mat[16];
    t.getOpenGLMatrix(mat);
    glPushMatrix();
    glMultMatrixf(mat);	//translation,rotation
    gluSphere(quad,r,20,20);
    glPopMatrix();
}

void renderCylinder(btRigidBody* sphere)
{
    if(sphere->getCollisionShape()->getShapeType()!=CYLINDER_SHAPE_PROXYTYPE)
        return;
    glColor3f(1,0,0);
    btVector3 extent=((btCylinderShape*)sphere->getCollisionShape())->getHalfExtentsWithoutMargin();
    btTransform t;
    sphere->getMotionState()->getWorldTransform(t);
    float mat[16];
    t.getOpenGLMatrix(mat);
    glPushMatrix();
    glMultMatrixf(mat);	//translation,rotation
    glTranslatef(0,extent.y(),0);
    glRotatef(90,1,0,0);
    gluCylinder(quad,extent.x(),extent.x(),extent.y()*2.0,20,20);
    glPopMatrix();
}

void renderCone(btRigidBody* sphere)
{
    if(sphere->getCollisionShape()->getShapeType()!=CONE_SHAPE_PROXYTYPE)
        return;
    glColor3f(1,0,0);
    float r=((btConeShape*)sphere->getCollisionShape())->getRadius();
    float h=((btConeShape*)sphere->getCollisionShape())->getHeight();
    btTransform t;
    sphere->getMotionState()->getWorldTransform(t);
    float mat[16];
    t.getOpenGLMatrix(mat);
    glPushMatrix();
    glMultMatrixf(mat);	//translation,rotation
    glTranslatef(0,h/2.0,0);
    glRotatef(90,1,0,0);
    gluCylinder(quad,0,r,h,20,20);
    glPopMatrix();
}

void renderBox(btRigidBody* sphere)
{
    if(sphere->getCollisionShape()->getShapeType()!=BOX_SHAPE_PROXYTYPE)
        return;
    glColor3f(1,0,0);
    btVector3 extent=((btBoxShape*)sphere->getCollisionShape())->getHalfExtentsWithoutMargin();
    btTransform t;
    sphere->getMotionState()->getWorldTransform(t);
    float mat[16];
    t.getOpenGLMatrix(mat);
    glPushMatrix();
    {
        glMultMatrixf(mat);	//translation,rotation

        glBegin(GL_QUADS);
        {
            glVertex3f(-extent.x(),extent.y(),-extent.z());
            glVertex3f(-extent.x(),-extent.y(),-extent.z());
            glVertex3f(-extent.x(),-extent.y(),extent.z());
            glVertex3f(-extent.x(),extent.y(),extent.z());
        }
        glEnd();

        glBegin(GL_QUADS);
        {
            glVertex3f(extent.x(),extent.y(),-extent.z());
            glVertex3f(extent.x(),-extent.y(),-extent.z());
            glVertex3f(extent.x(),-extent.y(),extent.z());
            glVertex3f(extent.x(),extent.y(),extent.z());
        }
        glEnd();

        glBegin(GL_QUADS);
        {
            glVertex3f(-extent.x(),extent.y(),extent.z());
            glVertex3f(-extent.x(),-extent.y(),extent.z());
            glVertex3f(extent.x(),-extent.y(),extent.z());
            glVertex3f(extent.x(),extent.y(),extent.z());
        }
        glEnd();

        glBegin(GL_QUADS);
        {
            glVertex3f(-extent.x(),extent.y(),-extent.z());
            glVertex3f(-extent.x(),-extent.y(),-extent.z());
            glVertex3f(extent.x(),-extent.y(),-extent.z());
            glVertex3f(extent.x(),extent.y(),-extent.z());
        }
        glEnd();

        glBegin(GL_QUADS);
        {
            glVertex3f(-extent.x(),extent.y(),-extent.z());
            glVertex3f(-extent.x(),extent.y(),extent.z());
            glVertex3f(extent.x(),extent.y(),extent.z());
            glVertex3f(extent.x(),extent.y(),-extent.z());
        }
        glEnd();

        glBegin(GL_QUADS);
        {
            glVertex3f(-extent.x(),-extent.y(),-extent.z());
            glVertex3f(-extent.x(),-extent.y(),extent.z());
            glVertex3f(extent.x(),-extent.y(),extent.z());
            glVertex3f(extent.x(),-extent.y(),-extent.z());
        }
        glEnd();
    }
    glPopMatrix();
}

void renderPlane(btRigidBody* plane)
{
    if(plane->getCollisionShape()->getShapeType()!=STATIC_PLANE_PROXYTYPE)
        return;
    glColor3f(0.8,0.8,0.8);
    btTransform t;
    plane->getMotionState()->getWorldTransform(t);
    float mat[16];
    t.getOpenGLMatrix(mat);
    glPushMatrix();
    {
        glMultMatrixf(mat);	//translation,rotation
        glBegin(GL_QUADS);
        {
            glVertex3f(-1000,0,1000);
            glVertex3f(-1000,0,-1000);
            glVertex3f(1000,0,-1000);
            glVertex3f(1000,0,1000);
        }
        glEnd();
    }
    glPopMatrix();
}


void init(float angle)
{
    quad=gluNewQuadric();

    physics = new PhysicsEngine();

    physics->addSphere(1.0,0,20,0,1.0);

    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle,640.0/480.0,1,1000);
    glMatrixMode(GL_MODELVIEW);
    //initskybox();
    glEnable(GL_DEPTH_TEST);
    cam.setLocation(vector3d(10,10,10));	//the player will be top of the terrain
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    cam.Control();
    //drawSkybox(50);
    cam.UpdateCamera();
    for(int i=0;i<physics->bodies.size();i++)
    {
        if(physics->bodies[i]->getCollisionShape()->getShapeType()==STATIC_PLANE_PROXYTYPE)
            renderPlane(physics->bodies[i]);
        else if(physics->bodies[i]->getCollisionShape()->getShapeType()==SPHERE_SHAPE_PROXYTYPE)
            renderSphere(physics->bodies[i]);
        else if(physics->bodies[i]->getCollisionShape()->getShapeType()==CYLINDER_SHAPE_PROXYTYPE)
            renderCylinder(physics->bodies[i]);
        else if(physics->bodies[i]->getCollisionShape()->getShapeType()==CONE_SHAPE_PROXYTYPE)
            renderCone(physics->bodies[i]);
        else if(physics->bodies[i]->getCollisionShape()->getShapeType()==BOX_SHAPE_PROXYTYPE)
            renderBox(physics->bodies[i]);
    }
}



int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(640,480,32,SDL_OPENGL);
    Uint32 start;
    SDL_Event event;
    bool running=true;
    float angle=50;
    init(angle);
    physics->addCylinder(2,5,0,30,0,1.0);
    physics->addCone(2,5,5,30,0,1.0);
    physics->addBox(10,2,3,0,40,0,1.0);
    while(running)
    {
        start=SDL_GetTicks();
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                running=false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    running=false;
                    break;
                case SDLK_y:
                    cam.mouseIn(false);
                    break;
                case SDLK_SPACE:
                    btRigidBody* sphere=physics->addSphere(1.0,cam.getLocation().x,cam.getLocation().y,cam.getLocation().z,1.0);
                    vector3d look=cam.getVector()*20;
                    sphere->setLinearVelocity(btVector3(look.x,look.y,look.z));
                    break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {

                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                cam.mouseIn(true);
                break;

            }
        }
        physics->stepSimulation(1/60.0);
        display();
        SDL_GL_SwapBuffers();
        if(1000.0/60>SDL_GetTicks()-start)
            SDL_Delay(1000.0/60-(SDL_GetTicks()-start));
    }

    //killskybox();
    delete physics;
    SDL_Quit();
    gluDeleteQuadric(quad);
}
