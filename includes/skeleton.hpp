#ifndef SKELETON_HPP
#define SKELETON_HPP

#include "Vector.hpp"
#include "mat4.hpp"
#include <vector>
#include "animation.hpp"

enum BONEID { HIP, HEAD, TORSO, L_H_LEG, L_L_LEG, R_H_LEG, R_L_LEG, L_H_ARM, L_L_ARM, R_H_ARM, R_L_ARM, BONE_NUMDER };

class Bone
{
    int                 ID;
    Bone                *parent;
    std::vector<Bone*>  childs;
    public:

    Bone() {
        ID = 0;
        parent = 0;
        size = vec3(1);
        localMatrix = mat4(1);
        finalMatrix = mat4(1);
        scaleMatrix = mat4(1);
    };

    vec3 size;
    mat4 scaleMatrix;
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

    Bone& SetID(int ID) {
        this->ID = ID;
        return (*this);
    }

    int GetID() const {
        return (ID);
    }

    Bone* GetParent() const {
        return (parent);
    }

    Bone &SetLocalMatrix(mat4 localMatrix) {
        this->localMatrix = localMatrix;
        return (*this);
    }

    mat4 ModelMatrix() {
        return (finalMatrix * scaleMatrix);
    }

    Bone &WithScale(vec3 size) {
        this->size = size;
        scaleMatrix = scale(size) * translate(vec3({-0.5f, 0, -0.5f}));
        return (*this);
    }

    void ComputeFinalMatrix() {     //use recursive or use a list in order from first parent to last childs if it is too slow
        finalMatrix = (parent != 0) ?  parent->finalMatrix * localMatrix  : localMatrix;
        for (Bone* bone : childs)
            bone->ComputeFinalMatrix();
    }

    template< size_t _size >
    void ComputeAnimFinalMatrix(AnimFrame<_size> &frame) {
        mat4 animMatrix;
        
        animMatrix = rotation(frame.rotation[ID][0], vec3({1, 0, 0})) *
                    rotation(frame.rotation[ID][1], vec3({0, 1, 0})) *
                    rotation(frame.rotation[ID][2], vec3({0, 0, 1})) * translate(frame.translation[ID]);
                    
        finalMatrix = (parent != 0) ? parent->finalMatrix * localMatrix * animMatrix : localMatrix * animMatrix;

       /* if (ID == 0) {
            std::cout << finalMatrix << std::endl;
            return ;
        }*/
        for (Bone* bone : childs)
            bone->ComputeAnimFinalMatrix(frame);
    }

};

std::ostream& operator<<(std::ostream& os, const Bone &bone);

class Skeleton
{
    std::array<Bone, BONE_NUMDER> bones;

    public:

    Skeleton();
    
    Bone &GetBone(unsigned id);

    void ComputeLocalMatrix();

    private:
    void BuildSkeleton();
};

#endif