#include "Component.h"
#include "GameObject.h"  // Agora podemos incluir GameObject.h aqui

Component::Component(GameObject& associated) : associated(associated) {}
Component::~Component() {}