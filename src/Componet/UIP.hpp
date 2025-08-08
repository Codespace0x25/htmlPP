// Componet/UILink.hpp
#pragma once
#include "Componet.hpp"
#include "TextComponet.hpp"

class UIP : public Comment::Component {
public:
    UIP(const std::string& label)
        : Component("p") {
        addChild(new TextComponent(label));
        setAttr("class", "ui-p");
    }
};
