// UIButton.hpp
#pragma once
#include "Componet.hpp"
#include "TextComponet.hpp"

class UIButton : public Comment::Component {
public:
    UIButton(const std::string& label, const std::string& action = "")
        : Component("button") {
      addChild(new TextComponent(label));
        if (!action.empty()) {
            setAttr("onclick", action);
        }
        setAttr("type", "button");
        setAttr("class","ui-button");
    }
};
