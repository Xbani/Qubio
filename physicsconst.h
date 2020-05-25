#ifndef PHYSICSCONST_H
#define PHYSICSCONST_H


class PhysicsConst
{
public:
    PhysicsConst();
    constexpr static double G_FORCE  = 25;
    constexpr static double MAX_VITESSE_LATERAL = 6;
    constexpr static double MAX_VITESSE_VERTICAL = 10;
    constexpr static double ACC_LATERAL_MOUVEMENT  = 1;
    constexpr static double ACC_JUMP  = 1500;
    constexpr static double APPROX_COS_PI_4 = 0.707;
    constexpr static double INERTIA = 2;
    constexpr static double BLOCK_WIDTH = 80;
    constexpr static double BLOCK_HEIGHT = 80;
    constexpr static double CHARACTER_WIDTH = 80;
    constexpr static double CHARACTER_HEIGHT = 80;
};

#endif // PHYSICSCONST_H
