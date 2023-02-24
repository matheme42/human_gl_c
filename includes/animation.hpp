#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "mat4.hpp"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <vector>


template< size_t _size >
struct AnimFrame {

    AnimFrame() {
        time = 0;
    };

    std::array<vec3, _size> rotation;
    std::array<vec3, _size> translation;
    float                   time;
    

    AnimFrame &Set(unsigned ID, vec3 rotation, vec3 translation) {
        this->rotation[ID] = rotation;
        this->translation[ID] = translation;
        return (*this);
    }

    AnimFrame &SetTime(float time) {
        this->time = time;
        return (*this);
    }

    AnimFrame &Clean() {
        vec3 tmp(0);

        for (unsigned n = 0; n < _size; n++) {
            rotation[n] = tmp;
            translation[n] = tmp;
        }
        return (*this);
    }
};

template< size_t _size >
AnimFrame<_size> lerp(AnimFrame<_size> &frame1, AnimFrame<_size> &frame2, float ratio) {
    AnimFrame<_size> result;

    for (unsigned n = 0; n < _size; n++) {
        result.rotation[n] = lerp(frame1.rotation[n], frame2.rotation[n], ratio);
        result.translation[n] = lerp(frame1.translation[n], frame2.translation[n], ratio);
    }
    result.time = frame1.time * ratio + frame2.time * (1.0f - ratio);
    return result;
}

template< size_t _size >
std::ostream& operator<<(std::ostream& os, const AnimFrame<_size> &frame) {
    os << "Time     : " << frame.time << std::endl;

    for (unsigned n = 0; n < _size; n++) {
        os << "translation  : " << n << std::endl << frame.translation[n] << std::endl;
        os << "rotation  : " << n << std::endl << frame.rotation[n] << std::endl;
    }
    return (os);
}

template< size_t _bone_number >
class Animation {
private:
    std::vector<AnimFrame<_bone_number>> frames;
    float   animationTime;
    float   startTime;
    bool    loop;

public:
    AnimFrame<_bone_number> currentFrame;

    Animation() {
        animationTime = 0;
        startTime = 0;
        loop = false;
    }

    Animation &AddFrame(AnimFrame<_bone_number> frame) {
        if (frame.time > animationTime)
            animationTime = frame.time;

        frames.push_back(frame);
        std::sort(frames.begin(), frames.end(), [](AnimFrame<_bone_number>& f1, AnimFrame<_bone_number>& f2) {
            return (f1.time < f2.time);
        });
        return(*this);
    }

    void Start() {
        if (frames.size() < 2)
            return ;
        startTime = glfwGetTime();
    }

    void Loop() {
        if (frames.size() < 2)
            return ;
        loop = true;
    }

    void Stop() {
        startTime = 0;
        loop = false;
    }

    void Uptdate() {
        unsigned n;
        float ratio;
        float time;

        time = (float)glfwGetTime() - startTime;
        if (time > animationTime) {
            if (!loop)
                return ;
            startTime = (float)glfwGetTime();
            time = 0;
        }

        n = 0;
        while (n < frames.size() - 2 && frames[n + 1].time < time)
            n++;

        ratio = (time - frames[n].time) / (frames[n + 1].time - frames[n].time);
        if (ratio < 0)
            ratio = 0;
        currentFrame = lerp(frames[n], frames[n + 1], ratio);
    }

    void Print() {
        for (auto frame : frames)
            std::cout << frame.time << std::endl;
    }
};

#endif