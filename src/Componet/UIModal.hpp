#pragma once
#include "Componet.hpp"
#include "TextComponet.hpp"

class UIModal : public Comment::Component {
public:
    UIModal(const std::string& id, const std::string& title = "")
        : Component("div") {
        setAttr("id", id);
        setAttr("class", "ui-modal");
        setAttr("style", "display: none;");

        auto* content = new Comment::Component("div");
        content->setAttr("class", "ui-modal-content");

        if (!title.empty()) {
            auto* header = new Comment::Component("div");
            header->setAttr("class", "ui-modal-header");
            header->addChild(new TextComponent(title));
            content->addChild(header);
        }

        auto* body = new Comment::Component("div");
        body->setAttr("class", "ui-modal-body");

        content->addChild(body);
        addChild(content);
    }

    void addToBody(Comment::Component* c) {
        // Define a local friend subclass to access protected `children`
        struct Accessor : Comment::Component {
            using Comment::Component::children;
        };

        auto* content = static_cast<Accessor*>(children[0]); // ui-modal-content
        if (content->children.size() > 1) {
            auto* body = static_cast<Accessor*>(content->children[1]); // ui-modal-body
            body->addChild(c);
        }
    }
};
