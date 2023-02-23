#include "animation.hpp"
#include "skeleton.hpp"


Animation<BONE_NUMDER> walking() {
    
    Animation<BONE_NUMDER> anim;

    AnimFrame<BONE_NUMDER> frame, start;

    start.Clean().SetTime(0)
        .Set(R_H_ARM,       vec3({ 25, 0, 0 }),     vec3(0))
        .Set(R_L_ARM,       vec3({ 20, 0, 0 }),     vec3(0))
        .Set(L_H_ARM,       vec3({ -20, 0, 0 }),     vec3(0))
        .Set(L_L_ARM,       vec3({ 10, 0, 0 }),     vec3(0))
        .Set(L_H_LEG,       vec3({ 10, 0, 0 }),     vec3(0))
        .Set(L_L_LEG,       vec3({ -15, 0, 0 }),     vec3(0))
        .Set(R_H_LEG,       vec3({ -10, 0, 0 }),     vec3(0))
        .Set(R_L_LEG,       vec3({ -5, 0, 0 }),     vec3(0));
    
    return anim.AddFrame(start)
    .AddFrame(frame.Clean().SetTime(1)
        .Set(R_H_ARM,       vec3({ 10, 0, 0 }),     vec3(0))
        .Set(R_L_ARM,       vec3({ 10, 0, 0 }),     vec3(0))
        .Set(L_H_LEG,       vec3({ 15, 0, 0 }),     vec3(0))
        .Set(L_L_LEG,       vec3({ -10, 0, 0 }),     vec3(0))
        .Set(L_H_ARM,       vec3({ 10, 0, 0 }),     vec3(0))
        .Set(L_L_ARM,       vec3({ 10, 0, 0 }),     vec3(0))
        .Set(R_H_LEG,       vec3({ -5, 0, 0 }),     vec3(0))
        .Set(R_L_LEG,       vec3({ -10, 0, 0 }),     vec3(0))
        .Set(HIP,       vec3(0),     vec3({ 0, -0.2f, 0 }))
    
    )
    .AddFrame(frame.Clean().SetTime(2)
        .Set(L_H_ARM,       vec3({ 25, 0, 0 }),     vec3(0))
        .Set(L_L_ARM,       vec3({ 20, 0, 0 }),     vec3(0))
        .Set(R_H_ARM,       vec3({ -20, 0, 0 }),     vec3(0))
        .Set(R_L_LEG,       vec3({ 10, 0, 0 }),     vec3(0))
        .Set(R_H_LEG,       vec3({ 40, 0, 0 }),     vec3(0))
        .Set(R_L_LEG,       vec3({ -15, 0, 0 }),     vec3(0))
        .Set(L_H_LEG,       vec3({ -10, 0, 0 }),     vec3(0))
        .Set(L_L_LEG,       vec3({ 5, 0, 0 }),     vec3(0))
    )
    .AddFrame(start.SetTime(4));
}

Animation<BONE_NUMDER> jump() {
    
    Animation<BONE_NUMDER> anim;

    AnimFrame<BONE_NUMDER> frame, start;

    start.Clean().SetTime(0);
    
    return anim.AddFrame(start)
    .AddFrame(frame.Clean().SetTime(1)
        .Set(TORSO,     vec3({ 30, 0, 0 }),     vec3(0))
        .Set(L_H_LEG,   vec3({ 75, 0, 0 }),     vec3(0))
        .Set(L_L_LEG,   vec3({ -95, 0, 0 }),    vec3(0))
        .Set(R_H_LEG,   vec3({ 75, 0, 0 }),     vec3(0))
        .Set(R_L_LEG,   vec3({ -95, 0, 0 }),    vec3(0))
        .Set(L_H_ARM,   vec3({ 20, 0, 0 }),     vec3(0))
        .Set(L_L_ARM,   vec3({ 30, 0, 0 }),    vec3(0))
        .Set(R_H_ARM,   vec3({ 20, 0, 0 }),     vec3(0))
        .Set(R_L_ARM,   vec3({ 30, 0, 0 }),    vec3(0))
        .Set(HIP,       vec3(0), vec3({ 0, -1.5f, 0 }))
    
    )

        .AddFrame(frame.Clean().SetTime(1.2)
        .Set(L_H_LEG,   vec3({ 20, 0, 0 }),     vec3(0))
        .Set(L_L_LEG,   vec3({ -30, 0, 0 }),    vec3(0))
        .Set(R_H_LEG,   vec3({ 20, 0, 0 }),     vec3(0))
        .Set(R_L_LEG,   vec3({ -20, 0, 0 }),    vec3(0))
        .Set(L_H_ARM,   vec3({ 170, 0, 0 }),     vec3(0))
        .Set(L_L_ARM,   vec3({ 20, 0, 0 }),    vec3(0))
        .Set(R_H_ARM,   vec3({ 170, 0, 0 }),     vec3(0))
        .Set(R_L_ARM,   vec3({ 20, 0, 0 }),    vec3(0))
        .Set(HIP,       vec3(0), vec3({ 0, 1.0f, 0 }))
    )
    .AddFrame(frame.Clean().SetTime(1.4)
        .Set(L_H_ARM,   vec3({ 20, 0, 0 }),     vec3(0))
        .Set(L_L_ARM,   vec3({ 30, 0, 0 }),    vec3(0))
        .Set(R_H_ARM,   vec3({ 20, 0, 0 }),     vec3(0))
        .Set(R_L_ARM,   vec3({ 30, 0, 0 }),    vec3(0))
        .Set(HIP,       vec3(0), vec3({ 0, 0.6f, 0 }))
    
    )
    .AddFrame(start.SetTime(1.6));
}

Animation<BONE_NUMDER> flip() {
    
    Animation<BONE_NUMDER> anim;

    AnimFrame<BONE_NUMDER> frame, start;

    start.Clean().SetTime(0);
    
    return anim.AddFrame(start)
    .AddFrame(frame.Clean().SetTime(1)
        .Set(TORSO,     vec3({ 30, 0, 0 }),     vec3(0))
        .Set(L_H_LEG,   vec3({ 75, 0, 0 }),     vec3(0))
        .Set(L_L_LEG,   vec3({ -95, 0, 0 }),    vec3(0))
        .Set(R_H_LEG,   vec3({ 75, 0, 0 }),     vec3(0))
        .Set(R_L_LEG,   vec3({ -95, 0, 0 }),    vec3(0))
        .Set(L_H_ARM,   vec3({ 20, 0, 0 }),     vec3(0))
        .Set(L_L_ARM,   vec3({ 30, 0, 0 }),    vec3(0))
        .Set(R_H_ARM,   vec3({ 20, 0, 0 }),     vec3(0))
        .Set(R_L_ARM,   vec3({ 30, 0, 0 }),    vec3(0))
        .Set(HIP,       vec3(0), vec3({ 0, -1.5f, 0 }))
    
    )

        .AddFrame(frame.Clean().SetTime(1.6)
        .Set(L_H_LEG,   vec3({ 20, 0, 0 }),     vec3(0))
        .Set(L_L_LEG,   vec3({ -30, 0, 0 }),    vec3(0))
        .Set(R_H_LEG,   vec3({ 20, 0, 0 }),     vec3(0))
        .Set(R_L_LEG,   vec3({ -20, 0, 0 }),    vec3(0))
        .Set(L_H_ARM,   vec3({ 60, 0, 0 }),     vec3(0))
        .Set(L_L_ARM,   vec3({ 20, 0, 0 }),    vec3(0))
        .Set(R_H_ARM,   vec3({ 60, 0, 0 }),     vec3(0))
        .Set(R_L_ARM,   vec3({ 20, 0, 0 }),    vec3(0))
        .Set(HIP,       vec3({220, 0, 0}), vec3({ 0, 1.0f, 0 }))
    )
    .AddFrame(frame.Clean().SetTime(2.0f)
        .Set(L_H_ARM,   vec3({ 20, 0, 0 }),     vec3(0))
        .Set(L_L_ARM,   vec3({ 30, 0, 0 }),    vec3(0))
        .Set(R_H_ARM,   vec3({ 20, 0, 0 }),     vec3(0))
        .Set(R_L_ARM,   vec3({ 30, 0, 0 }),    vec3(0))
        .Set(HIP,       vec3({359, 0, 0}), vec3({ 0, 0.6f, 0 }))
    
    )
    .AddFrame(frame.Clean().SetTime(2.0f)
        .Set(L_H_ARM,   vec3({ 20, 0, 0 }),     vec3(0))
        .Set(L_L_ARM,   vec3({ 30, 0, 0 }),    vec3(0))
        .Set(R_H_ARM,   vec3({ 20, 0, 0 }),     vec3(0))
        .Set(R_L_ARM,   vec3({ 30, 0, 0 }),    vec3(0))
        .Set(HIP,       vec3({0, 0, 0}), vec3({ 0, 0.6f, 0 }))
    
    )
    .AddFrame(start.SetTime(2.5));
}

Animation<BONE_NUMDER> put() {
    
    Animation<BONE_NUMDER> anim;

    AnimFrame<BONE_NUMDER> frame, start;

    start.Clean().SetTime(0)
        .Set(TORSO,       vec3({0, 0, 0}), vec3(0))
        .Set(L_H_ARM,       vec3({-30, 0, 0}), vec3(0))
        .Set(R_H_ARM,       vec3({20, 0, 0}), vec3(0))
        .Set(L_L_ARM,       vec3({30, 0, 0}), vec3(0))
        .Set(R_L_ARM,       vec3({20, 0, 0}), vec3(0));
    
    return anim.AddFrame(start)

        .AddFrame(frame.Clean().SetTime(2)
        .Set(TORSO,       vec3({0, 20, 0}), vec3(0))
        .Set(L_H_ARM,       vec3({20, 0, 0}), vec3(0))
        .Set(R_H_ARM,       vec3({-20, 0, 0}), vec3(0))
        .Set(L_L_ARM,       vec3({15, 0, 0}), vec3(0))
        .Set(R_L_ARM,       vec3({15, 0, 0}), vec3(0))
    )

    .AddFrame(frame.Clean().SetTime(4)
        .Set(TORSO,       vec3({0, 0, 0}), vec3(0))
        .Set(L_H_ARM,       vec3({-20, 0, 0}), vec3(0))
        .Set(R_H_ARM,       vec3({20, 0, 0}), vec3(0))
        .Set(L_L_ARM,       vec3({15, 0, 0}), vec3(0))
        .Set(R_L_ARM,       vec3({15, 0, 0}), vec3(0))
    )
    .AddFrame(frame.Clean().SetTime(6)
        .Set(TORSO,       vec3({0, -20, 0}), vec3(0))
        .Set(L_H_ARM,       vec3({20, 0, 0}), vec3(0))
        .Set(R_H_ARM,       vec3({-20, 0, 0}), vec3(0))
        .Set(L_L_ARM,       vec3({15, 0, 0}), vec3(0))
        .Set(R_L_ARM,       vec3({15, 0, 0}), vec3(0))
    )
    .AddFrame(start.SetTime(8));
}