#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include <vector>

class PhysicsEngine{
public:
    PhysicsEngine();
    ~PhysicsEngine();

    btRigidBody* addSphere(float rad,float x,float y,float z,float mass);
    btRigidBody* addCylinder(float d,float h,float x,float y,float z,float mass);
    btRigidBody* addCone(float d,float h,float x,float y,float z,float mass);
    btRigidBody* addBox(float width,float height,float depth,float x,float y,float z,float mass);

    void stepSimulation(btScalar timeStep);

public:
    std::vector<btRigidBody*> bodies;
private:
    btDynamicsWorld* world;
    btDispatcher* dispatcher;
    btCollisionConfiguration* collisionConfig;
    btBroadphaseInterface* broadphase;
    btConstraintSolver* solver;

};
