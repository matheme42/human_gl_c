#include "skeleton.hpp"

std::ostream& operator<<(std::ostream& os, const Bone &bone) {
    os << "Bone     :" << std::endl;
    os << "offset   : " << bone.offset << std::endl;
    os << "scale    : " << bone.Scale << std::endl;
    os << "rotation : " << bone.rotation << std::endl;
    os << "offsetM  : " << std::endl << bone.offsetM << std::endl;
    return (os);
}

void Skeleton::BuildSkeleton() {
    bones[HEAD].WithParent(&bones[TORSO]).WithChild(0).WithScale(vec3(1));//.WithOffset(vec3(0)).WithScale(vec3(1)).WithRotation(vec3(0));
    bones[TORSO].WithParent(0).WithChild(&bones[HEAD]).WithScale(vec3({1.5, 2, 0.5}));
    bones[L_H_ARM].WithParent(&bones[TORSO]).WithChild(&bones[L_L_ARM]).WithScale(vec3({0.5, 1.5f, 0.5}));
    bones[R_H_ARM].WithParent(&bones[TORSO]).WithChild(&bones[R_L_ARM]).WithScale(vec3({0.5, 1.5f, 0.5}));
    bones[L_L_ARM].WithParent(&bones[L_H_ARM]).WithChild(0).WithScale(vec3({0.5, 1.5f, 0.5}));
    bones[R_L_ARM].WithParent(&bones[R_H_ARM]).WithChild(0).WithScale(vec3({0.5, 1.5f, 0.5}));
    bones[L_H_LEG].WithParent(0).WithChild(&bones[L_L_LEG]).WithScale(vec3({0.5, 1.5f, 0.5}));
    bones[R_H_LEG].WithParent(0).WithChild(&bones[R_L_LEG]).WithScale(vec3({0.5, 1.5f, 0.5}));
    bones[L_L_LEG].WithParent(&bones[L_H_LEG]).WithChild(0).WithScale(vec3({0.5, 1.5f, 0.5}));
    bones[R_L_LEG].WithParent(&bones[R_H_LEG]).WithChild(0).WithScale(vec3({0.5, 1.5f, 0.5}));
}

void Skeleton::ComputeOffset() {
    bones[HEAD].WithOffset(vec3({0, 6.5f, 0})).ComputeOffsetMatrix();
    bones[TORSO].WithOffset(vec3({0, 1.5f, 0})).ComputeOffsetMatrix();
    bones[L_H_ARM].WithOffset(vec3({-1.5, 3, 0})).ComputeOffsetMatrix();
    bones[R_H_ARM].WithOffset(vec3({1.5, 3, 0})).ComputeOffsetMatrix();
    bones[L_L_ARM].WithOffset(vec3({0, 0, 0})).ComputeOffsetMatrix();
    bones[R_L_ARM].WithOffset(vec3({0, 0, 0})).ComputeOffsetMatrix();
    bones[L_H_LEG].WithOffset(vec3({-0.5, 0, 0})).ComputeOffsetMatrix();
    bones[R_H_LEG].WithOffset(vec3({0.5, 0, 0})).ComputeOffsetMatrix();
    bones[L_L_LEG].WithOffset(bones[L_H_LEG].offset - bones[L_H_LEG].Scale * vec3({0, 1.0f, 0})).ComputeOffsetMatrix();
    bones[R_L_LEG].WithOffset(bones[R_H_LEG].offset - bones[R_H_LEG].Scale * vec3({0, 1.0f, 0})).ComputeOffsetMatrix();
    std::cout << bones[L_H_LEG] << std::endl;
    std::cout << bones[L_L_LEG] << std::endl;
}

Skeleton::Skeleton() {
    BuildSkeleton();
    ComputeOffset();
    pos = vec3(0);
};

Bone Skeleton::GetBone(unsigned id) {
    return bones[id];
}
