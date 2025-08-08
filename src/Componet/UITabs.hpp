#pragma once
#include "Componet.hpp"
#include "ScriptBuilder.hpp" // for script helper
#include "TextComponet.hpp"
#include <cstdint>
#include <sstream>

class UITabItem : public Comment::Component {
public:
  UITabItem() : Component("div") { setAttr("class", "ui-tab-content"); }
};

class UITabs : public Comment::Component {
public:
  UITabs() : Component("div") {
    setAttr("class", "ui-tabs");

    buttonBar = new Component("div");
    buttonBar->setAttr("class", "ui-tab-buttons");
    addChild(buttonBar);

    content = new Component("div");
    content->setAttr("class", "ui-tab-views");
    addChild(content);

    // Build script with unique function name using this pointer
    std::string funcName =
        "switchTab_" + std::to_string(reinterpret_cast<uintptr_t>(this));
    scriptFunctionName = funcName;

    ScriptBuilder *script = new ScriptBuilder();
    script->raw("function " + funcName +
                "(id) {"
                "document.querySelectorAll('.ui-tab-content').forEach(e => "
                "e.classList.add('hidden'));"
                "document.getElementById(id).classList.remove('hidden');"
                "}");
    addChild(script);
  }

  void addTab(const std::string &label, Component *contentItem) {
    std::string id =
        "tab-" + std::to_string(reinterpret_cast<uintptr_t>(contentItem));

    // Button with onclick calling unique function
    auto *btn = new Component("button");
    btn->setAttr("class", "ui-tab-button");
    btn->setAttr("onclick", scriptFunctionName + "('" + id + "')");
    btn->addChild(new TextComponent(label));
    buttonBar->addChild(btn);

    // Content item with id and hidden by default except first
    contentItem->setAttr("id", id);
    // use addClass() now exists
    contentItem->addClass("ui-tab-content");

    // check child count safely:
    if (content->getChildCount() > 0)
      contentItem->addClass("hidden");
    content->addChild(contentItem);
  }

private:
  Component *buttonBar;
  Component *content;
  std::string scriptFunctionName;
};
