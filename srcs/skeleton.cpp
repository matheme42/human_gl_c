#include "skeleton.hpp"

std::ostream& operator<<(std::ostream& os, const Bone &bone) {
    os << "Bone     : " << bone.GetID() << std::endl;
    os << "Parent     : " << bone.GetParent() << std::endl;
    os << "scale    : " << bone.size << std::endl;
    os << "scaleMatrix  : " << std::endl << bone.scaleMatrix << std::endl;
    os << "localMatrix  : " << std::endl << bone.localMatrix << std::endl;
    os << "finalMatrix  : " << std::endl << bone.finalMatrix << std::endl;
    return (os);
}

void Skeleton::BuildSkeleton() {
    for (unsigned n = 0; n < BONE_NUMDER; n++)
        bones[n].SetID(n);

    bones[HIP].SetChilds({&bones[TORSO], &bones[L_H_LEG], &bones[R_H_LEG]});
    bones[HEAD]   .WithScale(vec3(1));//.WithOffset(vec3(0)).WithScale(vec3(1)).WithRotation(vec3(0));
    bones[TORSO]  .WithScale(vec3({1.5, 2, 0.5})).SetChilds({&bones[HEAD], &bones[L_H_ARM], &bones[R_H_ARM]});
    
    bones[L_H_ARM].WithScale(vec3({0.5, 1.2f, 0.5})).SetChilds({&bones[L_L_ARM]});
    bones[R_H_ARM].WithScale(vec3({0.5, 1.2f, 0.5})).SetChilds({&bones[R_L_ARM]});
    
    bones[L_L_ARM].WithScale(vec3({0.5, 1.1f, 0.5})).SetChilds({&bones[L_HAND]});
    bones[R_L_ARM].WithScale(vec3({0.5, 1.1f, 0.5})).SetChilds({&bones[R_HAND]});
    bones[L_HAND].WithScale(vec3({0.5, 0.5f, 0.5}));
    bones[R_HAND].WithScale(vec3({0.5, 0.5f, 0.5}));

    bones[L_H_LEG].WithScale(vec3({0.5, 1.5f, 0.5})).SetChilds({&bones[L_L_LEG]});
    bones[R_H_LEG].WithScale(vec3({0.5, 1.5f, 0.5})).SetChilds({&bones[R_L_LEG]});
    
    bones[L_L_LEG].WithScale(vec3({0.5, 1.5f, 0.5}));
    bones[R_L_LEG].WithScale(vec3({0.5, 1.5f, 0.5}));
}

void Skeleton::ComputeLocalMatrix() {
    bones[TORSO].SetLocalMatrix(mat4(1));
    bones[HEAD].SetLocalMatrix(translate(bones[TORSO].size * vec3({0, 1.0f, 0})));
    bones[L_H_LEG].SetLocalMatrix(rotate(mat4(translate(bones[TORSO].size * vec3({0.5f, 0, 0}) - bones[L_H_LEG].size * vec3({0.5f, 0, 0}))), 180, vec3({0, 0, 1})));
    bones[R_H_LEG].SetLocalMatrix(rotate(mat4(translate(bones[TORSO].size * vec3({-0.5f, 0, 0}) + bones[R_H_LEG].size * vec3({0.5f, 0, 0}))), 180, vec3({0, 0, 1})));
    bones[L_L_LEG].SetLocalMatrix(mat4(translate(bones[L_H_LEG].size * vec3({0, 1.0f, 0}))));
    bones[R_L_LEG].SetLocalMatrix(mat4(translate(bones[R_H_LEG].size * vec3({0, 1.0f, 0}))));

    bones[L_H_ARM].SetLocalMatrix(rotate(mat4(translate(bones[TORSO].size * vec3({0.5f, 1.0f, 0}) + bones[L_H_ARM].size * vec3({0.5f, 0, 0}))), 180, vec3({0, 0, 1})));
    bones[R_H_ARM].SetLocalMatrix(rotate(mat4(translate(bones[TORSO].size * vec3({-0.5f, 1.0f, 0}) - bones[R_H_ARM].size * vec3({0.5f, 0, 0}))), 180, vec3({0, 0, 1})));
    bones[L_L_ARM].SetLocalMatrix(mat4(translate(bones[L_H_ARM].size * vec3({0, 1.0f, 0}))));
    bones[R_L_ARM].SetLocalMatrix(mat4(translate(bones[R_H_ARM].size * vec3({0, 1.0f, 0}))));
    bones[L_HAND].SetLocalMatrix(mat4(translate(bones[L_L_ARM].size * vec3({0, 1.0f, 0}))));
    bones[R_HAND].SetLocalMatrix(mat4(translate(bones[R_L_ARM].size * vec3({0, 1.0f, 0}))));
    bones[HIP].ComputeFinalMatrix();
}

Skeleton::Skeleton() {
    BuildSkeleton();
    ComputeLocalMatrix();
};

Bone& Skeleton::GetBone(unsigned id) {
    return bones[id];
}
