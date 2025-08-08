#pragma once
#include "../Componet/UI.hpp"
#include <cstdlib>
#include <ctime>

class Main: public Page{
  public:
  Main(): Page(){
    setTitle("Main");

  UINavbar* nav = new UINavbar("example"); 

  add(nav);
  nav->addItem("test", "https://google.com");
  nav->addItem("test2", "https://google.com");

  add(new UIHeader("Welcome to html++ this is a example "));
  add(
      new UIP("oo sorry. i did not mean to do this. here ill make you a door"));
  add(new UILink(" door.", "/next"));
  add(new UIP("go on enter the"));
  add(new UILink(" door.", "/next"));
  add(new UIP("I'm not that smart"));
  add(new UIAlert("I'm not that smart"));
  add(new CodeBlock(R"(#include <stdio.h>

int main(void){
  printf("hi");
  return 0;
})",
                          "c"));
  }
}; 
