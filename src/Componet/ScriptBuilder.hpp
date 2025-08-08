// ScriptBuilder.hpp
#pragma once
#include "ScriptComponet.hpp"
#include <sstream>
#include <vector>

class ScriptBuilder : public ScriptComponent {
public:
    ScriptBuilder() : ScriptComponent("") {}

    ScriptBuilder& onClick(const std::string& id, const std::string& code) {
        return onEvent(id, "click", code);
    }

    ScriptBuilder& onEvent(const std::string& id, const std::string& event, const std::string& code) {
        lines.push_back(
            "document.getElementById('" + id + "').addEventListener('" + event + "', function() {" + code + "});"
        );
        return *this;
    }

    ScriptBuilder& toggleDisplay(const std::string& id) {
        return onClick(id,
            "const el = document.getElementById('" + id + "');"
            "el.style.display = (el.style.display === 'none') ? 'block' : 'none';"
        );
    }

    ScriptBuilder& toggleClass(const std::string& id, const std::string& className) {
        return onClick(id,
            "document.getElementById('" + id + "').classList.toggle('" + className + "');"
        );
    }

    ScriptBuilder& addClass(const std::string& id, const std::string& className) {
        lines.push_back(
            "document.getElementById('" + id + "').classList.add('" + className + "');"
        );
        return *this;
    }

    ScriptBuilder& removeClass(const std::string& id, const std::string& className) {
        lines.push_back(
            "document.getElementById('" + id + "').classList.remove('" + className + "');"
        );
        return *this;
    }

    ScriptBuilder& setHTML(const std::string& id, const std::string& html) {
        lines.push_back(
            "document.getElementById('" + id + "').innerHTML = `" + html + "`;"
        );
        return *this;
    }

    ScriptBuilder& setStyle(const std::string& id, const std::string& style) {
        lines.push_back(
            "document.getElementById('" + id + "').style.cssText = `" + style + "`;"
        );
        return *this;
    }

    ScriptBuilder& delay(int ms, const std::string& code) {
        lines.push_back(
            "setTimeout(function() {" + code + "}, " + std::to_string(ms) + ");"
        );
        return *this;
    }

    ScriptBuilder& importScript(const std::string& url) {
        lines.push_back(
            "var s = document.createElement('script');"
            "s.src = '" + url + "';"
            "document.head.appendChild(s);"
        );
        return *this;
    }

    ScriptBuilder& onLoad(const std::string& code) {
        domLoadCode << code << "\n";
        return *this;
    }

    ScriptBuilder& raw(const std::string& code) {
        lines.push_back(code);
        return *this;
    }

    std::string render() const override {
        std::ostringstream out;
        out << "document.addEventListener('DOMContentLoaded', function() {\n";
        out << domLoadCode.str();
        for (const auto& line : lines) {
            out << line << "\n";
        }
        out << "});\n";
        const_cast<ScriptBuilder*>(this)->setJS(out.str());
        return Component::render();
    }

private:
    std::vector<std::string> lines;
    std::ostringstream domLoadCode;
};
