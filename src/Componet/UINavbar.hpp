#pragma once
#include "Componet.hpp"
#include "TextComponet.hpp"

class UINavItem : public Comment::Component {
public:
    UINavItem(const std::string& name, const std::string& href)
        : Component("a") {
        setAttr("class", "ui-nav-item");
        setAttr("href", href);
        addChild(new TextComponent(name));
    }
};

class UINavbar : public Comment::Component {
public:
    UINavbar(const std::string& title) : Component("nav") {
        setAttr("class", "ui-navbar");

        auto* titleDiv = new Component("div");
        titleDiv->setAttr("class", "ui-navbar-title");
        titleDiv->addChild(new TextComponent(title));
        addChild(titleDiv);

        menu = new Component("div");
        menu->setAttr("class", "ui-navbar-menu");
        addChild(menu);

        avatar = nullptr;
    }

    void addItem(const std::string& name, const std::string& href) {
        menu->addChild(new UINavItem(name, href));
    }

    void setAvatar(const std::string& src) {
        avatar = new Component("img");
        avatar->setAttr("class", "ui-navbar-avatar");
        avatar->setAttr("src", src);
        addChild(avatar);
    }

private:
    Component* menu;
    Component* avatar;
};
