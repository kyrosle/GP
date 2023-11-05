#pragma once

#include <string>
#include <memory>
#include <vector>

#include "runtime/function/framework/component/transform/transform_component.h"
#include "runtime/function/framework/component/mesh/mesh_component.h"

namespace Gp {
  class ComponentBase;

  class TransformComponent;

  class MeshComponent;

  class ComponentDefinitionRes {
  public:

    std::string m_type_name;
    std::string m_component;
  };

  class ObjectDefinitionRes {
  public:

    // components
    std::vector<std::shared_ptr<ComponentBase>> m_components;
  };

  class ObjectInstanceRes {
  public:
    typedef std::shared_ptr<ObjectInstanceRes> ptr;

    std::string m_name;
    std::string m_definition;

    // components
    std::vector<std::shared_ptr<ComponentBase>> m_instanced_components;
  };
}