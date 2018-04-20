#include "physics_engine.hpp"

PhysicsEngine::PhysicsEngine()
{
    collisionConfig=new btDefaultCollisionConfiguration();
    dispatcher=new btCollisionDispatcher(collisionConfig);
    broadphase=new btDbvtBroadphase();
    solver=new btSequentialImpulseConstraintSolver();
    world=new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfig);
    world->setGravity(btVector3(0,-9.81,0));

    //ADD PLANE
    btTransform t;
    t.setIdentity();
    t.setOrigin(btVector3(0,0,0));
    btStaticPlaneShape* plane=new btStaticPlaneShape(btVector3(0,1,0),0);
    btMotionState* motion=new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo info(0.0,motion,plane);
    btRigidBody* body=new btRigidBody(info);
    world->addRigidBody(body);
    bodies.push_back(body);
}
PhysicsEngine::~PhysicsEngine()
{
    for(int i=0;i<bodies.size();i++)
    {
        world->removeCollisionObject(bodies[i]);
        btMotionState* motionState=bodies[i]->getMotionState();
        btCollisionShape* shape=bodies[i]->getCollisionShape();
        delete bodies[i];
        delete shape;
        delete motionState;
    }
    delete dispatcher;
    delete collisionConfig;
    delete solver;
    delete broadphase;
    delete world;
}

btRigidBody* PhysicsEngine::addSphere(float rad,float x,float y,float z,float mass)
{
    btTransform t;
    t.setIdentity();
    t.setOrigin(btVector3(x,y,z));
    btSphereShape* sphere=new btSphereShape(rad);
    btVector3 inertia(0,0,0);
    if(mass!=0.0)
        sphere->calculateLocalInertia(mass,inertia);

    btMotionState* motion=new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo info(mass,motion,sphere,inertia);
    btRigidBody* body=new btRigidBody(info);
    world->addRigidBody(body);
    bodies.push_back(body);
    return body;
}

btRigidBody* PhysicsEngine::addCylinder(float d,float h,float x,float y,float z,float mass)
{
    btTransform t;
    t.setIdentity();
    t.setOrigin(btVector3(x,y,z));
    btCylinderShape* sphere=new btCylinderShape(btVector3(d/2.0,h/2.0,d/2.0));
    btVector3 inertia(0,0,0);
    if(mass!=0.0)
        sphere->calculateLocalInertia(mass,inertia);

    btMotionState* motion=new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo info(mass,motion,sphere,inertia);
    btRigidBody* body=new btRigidBody(info);
    world->addRigidBody(body);
    bodies.push_back(body);
    return body;
}

btRigidBody* PhysicsEngine::addCone(float d,float h,float x,float y,float z,float mass)
{
    btTransform t;
    t.setIdentity();
    t.setOrigin(btVector3(x,y,z));
    btConeShape* sphere=new btConeShape(d,h);
    btVector3 inertia(0,0,0);
    if(mass!=0.0)
        sphere->calculateLocalInertia(mass,inertia);

    btMotionState* motion=new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo info(mass,motion,sphere,inertia);
    btRigidBody* body=new btRigidBody(info);
    world->addRigidBody(body);
    bodies.push_back(body);
    return body;
}

btRigidBody* PhysicsEngine::addBox(float width,float height,float depth,float x,float y,float z,float mass)
{
    btTransform t;
    t.setIdentity();
    t.setOrigin(btVector3(x,y,z));
    btBoxShape* sphere=new btBoxShape(btVector3(width/2.0,height/2.0,depth/2.0));
    btVector3 inertia(0,0,0);
    if(mass!=0.0)
        sphere->calculateLocalInertia(mass,inertia);

    btMotionState* motion=new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo info(mass,motion,sphere,inertia);
    btRigidBody* body=new btRigidBody(info);
    world->addRigidBody(body);
    bodies.push_back(body);
    return body;
}
void PhysicsEngine::stepSimulation(btScalar timeStep)
{
    world->stepSimulation(timeStep);
}
