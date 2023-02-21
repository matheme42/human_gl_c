#ifndef SKELETON_HPP
#define SKELETON_HPP

#include "Vector.hpp"
#include "mat4.hpp"

class Bone
{
    Bone *parent;
    Bone *child;
    public:

    Bone() = default;

    vec3 offset;
    vec3 Scale;
    vec3 rotation;
    mat4 offsetM;

    Bone &ComputeOffsetMatrix() {
        offsetM = translate(offset) * scale(Scale);
        return (*this);
    }

    Bone &WithParent(Bone *parent) {
        this->parent = parent;
        return (*this);
    }

    Bone &WithChild(Bone *child) {
        this->child = child;
        return (*this);
    }
    Bone &WithOffset(vec3 offset) {
        this->offset = offset;
        return (*this);
    }

    Bone &WithScale(vec3 scale) {
        this->Scale = scale;
        return (*this);
    }
    Bone &WithRotation(vec3 rotation) {
        this->rotation = rotation;
        return (*this);
    }

    Bone &WithOffsetM(mat4 offsetM) {
        this->offsetM = offsetM;
        return (*this);
    }
};

std::ostream& operator<<(std::ostream& os, const Bone &bone);

enum BONEID { HEAD, TORSO, L_H_LEG, L_L_LEG, R_H_LEG, R_L_LEG, L_H_ARM, L_L_ARM, R_H_ARM, R_L_ARM, BONE_NUMDER};

class Skeleton
{
    std::array<Bone, BONE_NUMDER> bones;
    vec3 pos;

    public:

    Skeleton();
    
    Bone GetBone(unsigned id);

    void ComputeOffset();

    private:
    void BuildSkeleton();
};

#endif