// Componet/UIAlert.hpp
#pragma once
#include "Componet.hpp"
#include "TextComponet.hpp"
#include <sstream>

class UIAlert : public Comment::Component {
public:
    UIAlert(const std::string& message, const std::string& type = "info")
        : Component("div") {
        setAttr("class", "ui-alert ui-alert-" + type);
	std::stringstream style;
        addChild(new TextComponent(message));
    }
};
