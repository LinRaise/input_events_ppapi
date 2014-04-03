#include <stdio.h>
#include <string.h>

#include "ppapi/cpp/input_event.h"
#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"

class MyInstance : public pp::Instance {
 public:
  explicit MyInstance(PP_Instance instance)
      : pp::Instance(instance),
        handle_events_(false) {
    RequestFilteringInputEvents(PP_INPUTEVENT_CLASS_KEYBOARD);
    // Logged when --no-sandbox is enabled on chrome for debugging.
    fprintf(stderr, "loaded\n");
  }

  virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]) {
    for (int i = 0; i < argc; i++) {
      if (strcmp(argn[i], "handle_events") == 0)
        handle_events_ = true;
    }
  }
  virtual ~MyInstance() {
  }

  virtual bool HandleInputEvent(const pp::InputEvent& event) {
    pp::KeyboardInputEvent k(event);
    // Logged when --no-sandbox is enabled on Chrome for debugging.
    fprintf(stderr, "key hit: %u\n", k.GetKeyCode());
    return handle_events_;
  }
 private:
  bool handle_events_;
};

// This object is the global object representing this plugin library as long
// as it is loaded.
class MyModule : public pp::Module {
 public:
  MyModule() : pp::Module() {}
  virtual ~MyModule() {}

  // Override CreateInstance to create your customized Instance object.
  virtual pp::Instance* CreateInstance(PP_Instance instance) {
    return new MyInstance(instance);
  }
};

namespace pp {

// Factory function for your specialization of the Module object.
Module* CreateModule() {
  return new MyModule();
}

}  // namespace
