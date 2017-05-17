#ifndef SCENE_H
#define SCENE_H

#include "Model.h"

class Scene {
public:
    virtual void init() = 0;
    virtual void update() = 0;

private:
    void addChild(Model);
};

#endif // !SCENE_H
