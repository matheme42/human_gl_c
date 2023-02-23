#include "animation.hpp"
#include "skeleton.hpp"


Animation<BONE_NUMDER> walking() {
    
    Animation<BONE_NUMDER> anim;

    AnimFrame<BONE_NUMDER> frame, start;

    return anim;
   /* start.Clean().SetTime(0)
        .Set(R_H_ARM,       rotation(25, vec3({ 1, 0, 0 })))
        .Set(R_L_ARM,       rotation(20, vec3({ 1, 0, 0 })))
        .Set(L_H_ARM,       rotation(-20, vec3({ 1, 0, 0 })))
        .Set(L_L_ARM,       rotation(10, vec3({ 1, 0, 0 })))
        .Set(L_H_LEG,       rotation(10, vec3({ 1, 0, 0 })))
        .Set(L_L_LEG,       rotation(-15, vec3({ 1, 0, 0 })))
        .Set(R_H_LEG,       rotation(-10, vec3({ 1, 0, 0 })))
        .Set(R_L_LEG,       rotation(-5, vec3({ 1, 0, 0 })));
    
    return anim.AddFrame(start)
    .AddFrame(frame.Clean().SetTime(1)
        .Set(R_H_ARM,       rotation(10, vec3({ 1, 0, 0 })))
        .Set(R_L_ARM,       rotation(10, vec3({ 1, 0, 0 })))
        .Set(L_H_LEG,       rotation(15, vec3({ 1, 0, 0 })))
        .Set(L_L_LEG,       rotation(-10, vec3({ 1, 0, 0 })))
        .Set(L_H_ARM,       rotation(10, vec3({ 1, 0, 0 })))
        .Set(L_L_ARM,       rotation(10, vec3({ 1, 0, 0 })))
        .Set(R_H_LEG,       rotation(15, vec3({ 1, 0, 0 })))
        .Set(R_L_LEG,       rotation(-10, vec3({ 1, 0, 0 })))
        .Set(HIP,       translate(vec3({ 0, -0.2f, 0 })))
    
    )
    .AddFrame(frame.Clean().SetTime(2)
        .Set(L_H_ARM,       rotation(25, vec3({ 1, 0, 0 })))
        .Set(L_L_ARM,       rotation(20, vec3({ 1, 0, 0 })))
        .Set(R_H_ARM,       rotation(-20, vec3({ 1, 0, 0 })))
        .Set(R_L_LEG,       rotation(10, vec3({ 1, 0, 0 })))
        .Set(R_H_LEG,       rotation(40, vec3({ 1, 0, 0 })))
        .Set(R_L_LEG,       rotation(-15, vec3({ 1, 0, 0 })))
        .Set(L_H_LEG,       rotation(-10, vec3({ 1, 0, 0 })))
        .Set(L_L_LEG,       rotation(-5, vec3({ 1, 0, 0 })))
    )
    .AddFrame(start.SetTime(4));*/
}

Animation<BONE_NUMDER> jump() {
    
    Animation<BONE_NUMDER> anim;

    AnimFrame<BONE_NUMDER> frame, start;

    start.Clean().SetTime(0);
    
    return anim.AddFrame(start)
    .AddFrame(frame.Clean().SetTime(1)
        .Set(L_H_LEG,       rotation(75, vec3({ 1, 0, 0 })))
        .Set(L_L_LEG,       rotation(-95, vec3({ 1, 0, 0 })))
        .Set(R_H_LEG,       rotation(75, vec3({ 1, 0, 0 })))
        .Set(R_L_LEG,       rotation(-95, vec3({ 1, 0, 0 })))
        .Set(HIP,       translate(vec3({ 0, -0.2f, 0 })))
    
    )
    .AddFrame(start.SetTime(4));
}