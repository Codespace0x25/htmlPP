#pragma once
#include "Componet.hpp"

class UIAudio : public Comment::Component {
public:
    UIAudio(const std::string &URL, bool controls = true)
        : Component("audio"), controls(controls) 
    {
        setAttr("class", "ui-audio");  // Keep class safe
        setAttr("src", URL);
        if (controls) {
            setAttr("controls", "");
        }
    }

    bool controls;
};
