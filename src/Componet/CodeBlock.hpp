#pragma once
#include "Componet.hpp"
#include "TextComponet.hpp"
#include "ScriptBuilder.hpp"
#include "UIButton.hpp"
#include <cstdint>

class CodeBlock : public Comment::Component {
public:
    CodeBlock(const std::string& code, const std::string& lang = "cpp")
        : Component("div") {
        setAttr("class", "code-block-wrapper");

        // unique ID for code block
        std::string codeId = "code-" + std::to_string(reinterpret_cast<uintptr_t>(this));

        // Top bar with language label + copy button
        auto* topBar = new Comment::Component("div");
        topBar->setAttr("class", "code-block-header");

        auto* langLabel = new Comment::Component("span");
        langLabel->setAttr("class", "code-lang-label");
        langLabel->addChild(new TextComponent(lang));

        auto* btn = new UIButton("Copy");
        btn->setAttr("class", "copy-btn");
        btn->setAttr("onclick",
            "navigator.clipboard.writeText(document.getElementById('" + codeId + "').innerText);"
        );

        topBar->addChild(langLabel);
        topBar->addChild(btn);

        auto* pre = new Component("pre");
        pre->setAttr("class", "code-block");

        auto* codeTag = new Component("code");
        codeTag->setAttr("class", "language-" + lang);
        codeTag->setAttr("id", codeId);
        codeTag->addChild(new TextComponent(code));

        pre->addChild(codeTag);

        addChild(topBar);
        addChild(pre);
    }
};
