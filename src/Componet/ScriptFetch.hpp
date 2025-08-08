#pragma once
#include "ScriptComponet.hpp"

class ScriptFetch : public ScriptComponent {
public:
    ScriptFetch(const std::string& url, const std::string& callbackCode, const std::string& method = "GET")
        : ScriptComponent("") 
    {
        std::string js =
            "fetch('" + url + "', { method: '" + method + "' })\n"
            "  .then(response => response.json())\n"
            "  .then(data => {\n" + callbackCode + "\n});";
        setJS(js);
    }
};
