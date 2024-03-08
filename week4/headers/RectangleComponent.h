
#ifndef NUMBERCOMPONENT_H
#define NUMBERCOMPONENT_H

#include "Components.h"
#include <raylib.h>
struct RecatngleComponent : public Component {


    void draw_rectangle_component() override {

        DrawText("Rectangle", 1200/3, 1200/3, 20, Color(BLACK));
        DrawRectangle(1200 / 2, 800 / 2, 500, 500, Color(RED));
     

    };
};

#endif 
