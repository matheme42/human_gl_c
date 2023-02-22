#ifndef SKELETON_HPP
#define SKELETON_HPP

#include "Vector.hpp"
#include "mat4.hpp"
#include <vector>

class Bone
{
    Bone *parent;
    std::vector<Bone*> childs;
    public:

    Bone() {
        parent = 0;
        localMatrix = mat4(1);
        finalMatrix = mat4(1);
    };

    vec3 Scale;
    vec3 rotation;
    mat4 localMatrix;
    mat4 finalMatrix;

    Bone &SetChilds(std::vector<Bone*> childs) {
        this->childs = childs;
        for (Bone* bone : childs)
            bone->SetParent(this);
        return (*this);
    }

    Bone &SetParent(Bone *parent) {
        this->parent = parent;
        return (*this);
    }

    Bone &SetLocalMatrix(mat4 localMatrix) {
        this->localMatrix = localMatrix;
        return (*this);
    }

    mat4 ModelMatrix() {
        return (finalMatrix * scale(Scale));
    }

    Bone &WithScale(vec3 scale) {
        this->Scale = scale;
        return (*this);
    }
    Bone &WithRotation(vec3 rotation) {
        this->rotation = rotation;
        return (*this);
    }

    void ComputeFinalMatrix() {     //use recursive or use a list in order from first parent to last childs if it is too slow
        finalMatrix = (parent != 0) ?  parent->finalMatrix * localMatrix : localMatrix;
        for (Bone* bone : childs)
            bone->ComputeFinalMatrix();
    }

};

std::ostream& operator<<(std::ostream& os, const Bone &bone);

enum BONEID { HIP, HEAD, TORSO, L_H_LEG, L_L_LEG, R_H_LEG, R_L_LEG, L_H_ARM, L_L_ARM, R_H_ARM, R_L_ARM, BONE_NUMDER};

class Skeleton
{
    std::array<Bone, BONE_NUMDER> bones;

    public:

    Skeleton();
    
    Bone GetBone(unsigned id);

    void ComputeLocalMatrix();

    private:
    void BuildSkeleton();
};

#endif