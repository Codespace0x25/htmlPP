#pragma once
#include "Componet.hpp"
#include <string>


class UISandBox: public Comment::Component{
  public:
  UISandBox(std::string website,std::string title): Component("iframe"){
    setAttr("src", website);
    setAttr("title", title);
    setAttr("Name", "UISandBox-"+title);
    setAttr("class", "UISandBox-"+title);
  }
  private:
};
