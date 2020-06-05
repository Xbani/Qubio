#ifndef PHYSICSCONST_H
#define PHYSICSCONST_H


class QuPhysicsConst
{
public:
    QuPhysicsConst();
    constexpr static double G_FORCE  = 45;
    constexpr static double MAX_VITESSE_HORIZONTALE = 9;
    constexpr static double MAX_VITESSE_VERTICALE = 20;
    constexpr static double ACC_LATERAL_MOUVEMENT  = 45;
    constexpr static double ACC_JUMP  = 800;
    constexpr static double APPROX_COS_PI_4 = 0.707;
    constexpr static double INERTIA = 2;
    constexpr static double CHARACTER_WIDTH = 80;
    constexpr static double CHARACTER_HEIGHT = 80;
    constexpr static double QUANTUM = 0.005;
};

#endif // PHYSICSCONST_H
