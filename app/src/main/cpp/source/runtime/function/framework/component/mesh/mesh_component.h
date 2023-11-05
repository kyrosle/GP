#pragma once

#include <memory>
#include <vector>

#include "runtime/function/framework/component/transform/transform_component.h"
#include "runtime/function/framework/component/textrue/texture_component.h"
#include "runtime/function/framework/component/component.h"
#include "runtime/function/render/render_object.h"
#include "runtime/resource/res_type/components/mesh.h"

namespace Gp {

  /*
   * The mesh part of SpriteRenderComponent
   */
  class MeshComponent : public ComponentBase {
  public:
    typedef std::shared_ptr<MeshComponent> ptr;

    MeshComponent() : ComponentBase("MeshComponent") {};

    MeshComponent(MeshComponentRes mesh_res)
        : ComponentBase("MeshComponent"), m_mesh_res(mesh_res) {};

    void postLoadResource(std::weak_ptr<GObject> parent_object) override;

    const std::vector<GameObjectPartDesc> &getRawMeshes() const { return m_raw_meshes; }

    void tick(float deltaTime) override;

  private:
    MeshComponentRes m_mesh_res;

    std::vector<GameObjectPartDesc> m_raw_meshes;
  };

}

