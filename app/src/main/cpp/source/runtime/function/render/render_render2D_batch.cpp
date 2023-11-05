#include "render_render2D_batch.h"

#include <glm/gtc/matrix_transform.hpp>

#include "runtime/function/render/render_command.h"
#include "runtime/function/render/render_shader_library.h"
#include "runtime/function/render/render_buffer.h"

namespace Gp {
  struct SceneData {
    glm::mat4 ViewProjectionMatrix;
  };

  static SceneData *s_sceneData;

  struct Render2DBatchInstances {
    std::vector<VertexArray::ptr> m_rocks;
    std::vector<glm::vec2> m_offset;
    uint32_t m_instance_buffer;
  };

  static Render2DBatchInstances *s_batch_instances;

  struct Render2DBatchStorage {
    VertexArray::ptr quadVertexArray; // a Mesh represent Quad
    VertexArray::ptr circleVertexArray;
    Shader::ptr flatColorShader;
    Shader::ptr textureShader;
    Texture2D::ptr whiteTexture; // default texture, using in Blend
  };

  static Render2DBatchStorage *s_batch_data;

  void Renderer2DBatch::init() {
    s_sceneData = new SceneData();
    s_batch_data = new Render2DBatchStorage();
    s_batch_instances = new Render2DBatchInstances();

    s_batch_instances->m_offset.resize(4);
    int index = 0;
    float offset = 1.f;
    for (int x = -12; x < 12; x += 3) {
      glm::vec2 translation;
      translation.x = (float) x / 3.0f * offset;
      translation.y = index % 2 == 0 ? 1 : -1;
      s_batch_instances->m_offset[index++] = translation;
    }

    glGenBuffers(1, &s_batch_instances->m_instance_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, s_batch_instances->m_instance_buffer);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(glm::vec2) * s_batch_instances->m_offset.size(),
        s_batch_instances->m_offset.data(),
        GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    float quadVertices[] = {
        // position    |  texture uv
        -0.5f, -0.5f, 0, 0.0f, 0.0f,
        0.5f, -0.5f, 0, 1.0f, 0.0f,
        -0.5f, 0.5f, 0, 0.0f, 1.0f,
        0.5f, 0.5f, 0, 1.0f, 1.0f
    };

    s_batch_data->quadVertexArray.reset(VertexArray::Create());

    s_batch_data->quadVertexArray->Bind();

    auto quadVertexBuffer = VertexBuffer::ptr(
        VertexBuffer::Create(quadVertices, sizeof(quadVertices))
    );

    quadVertexBuffer->SetBufferLayout(
        {
            {ShaderDataType::Float3, "a_Pos"},
            {ShaderDataType::Float2, "a_Tex"},
            BufferElement::CreateInstancingBufferElement(
                ShaderDataType::Float2,
                "a_Offset", s_batch_instances->m_instance_buffer
            )
        }
    );

    uint32_t quadIndices[] = {0, 1, 2, 2, 1, 3};
    auto quadIndexBuffer = IndexBuffer::ptr(
        IndexBuffer::Create(quadIndices, sizeof(quadIndices)));

    quadVertexBuffer->Bind();

    quadIndexBuffer->Bind();

    s_batch_data->quadVertexArray->AddVertexBuffer(quadVertexBuffer);
    s_batch_data->quadVertexArray->SetIndexBuffer(quadIndexBuffer);

    s_batch_data->quadVertexArray->UnBind();

// -- shader --
    auto flat_color_batch_shader_name = "FlatColorShaderBatch";
    auto flat_color_shader_name = "FlatColorShader";
    RenderShaderLibrary::Load(flat_color_batch_shader_name, flat_color_shader_name);
    s_batch_data->flatColorShader = RenderShaderLibrary::Get(flat_color_batch_shader_name);
  }

  void Renderer2DBatch::shutdown() {
    free(s_batch_instances);
    free(s_sceneData);
    free(s_batch_data);
  }

  void Renderer2DBatch::beginScene(const RenderCamera &camera) {
    s_sceneData->ViewProjectionMatrix =
        camera.getViewProjectionMatrix();
  }

  void Renderer2DBatch::endScene() {}

  void Renderer2DBatch::drawQuad(
      const glm::vec3 &position,
      float rotatedAngle,
      const glm::vec2 &size,
      const glm::vec4 &color,
      const uint32_t instances_count) {
    s_batch_data->flatColorShader->Bind();
    s_batch_data->flatColorShader->UploadUniformMat4("u_ViewProjection",
                                                     s_sceneData->ViewProjectionMatrix);
    s_batch_data->flatColorShader->UploadUniformVec4("u_Color", color);
    glm::mat4 transform =
        glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
    transform = glm::translate(transform, position);
    transform = glm::rotate(transform, glm::radians(rotatedAngle), {0, 0, 1});
    s_batch_data->flatColorShader->UploadUniformMat4("u_Transform", transform);
    RenderCommand::DrawIndexedBatch(s_batch_data->quadVertexArray, instances_count);
    s_batch_data->flatColorShader->UnBind();
  }

  void Renderer2DBatch::drawQuad(
      const glm::vec3 &position,
      float rotatedAngle,
      const glm::vec2 &size,
      const Texture2D::ptr &texture,
      const uint32_t instances_count) {

  }

  void
  Renderer2DBatch::drawCircle(
      const glm::vec3 &position,
      const float radius,
      const glm::vec4 &color) {

  }

  void Renderer2DBatch::drawCircle(
      const glm::vec3 &position,
      const float radius,
      const Texture2D::ptr &texture,
      const uint32_t instances_count) {

  }

}