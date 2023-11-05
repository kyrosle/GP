#include "render_render2D.h"

#include <glm/gtc/matrix_transform.hpp>

#include "runtime/function/render/render_command.h"
#include "runtime/function/render/render_shader_library.h"

namespace Gp {

  /*!
   * for each object, MVP matrix `M` is different,
   * but `VP` are same, so it belong to the scene data.
   */
  struct SceneData {
    glm::mat4 ViewProjectionMatrix;
  };

  static SceneData *s_sceneData;

  struct Renderer2DStorage {
    VertexArray::ptr quadVertexArray; // a Mesh represent Quad
    VertexArray::ptr circleVertexArray;
    Shader::ptr flatColorShader;
    Shader::ptr textureShader;
    Texture2D::ptr whiteTexture; // default texture, using in Blend
  };

  static Renderer2DStorage *s_data;

  void Renderer2D::init() {
    s_sceneData = new SceneData();
    s_data = new Renderer2DStorage();

    // -- quad --
    initQuad();

    // -- circle --
    initCircle();

    // -- shader --
    auto flat_color_shader_name = "FlatColorShader";
    auto texture_shader_name = "TextureShader";
    RenderShaderLibrary::Load(flat_color_shader_name);
    RenderShaderLibrary::Load(texture_shader_name);

    s_data->flatColorShader = RenderShaderLibrary::Get(flat_color_shader_name);

    s_data->textureShader = RenderShaderLibrary::Get(texture_shader_name);
  }

  void Renderer2D::shutdown() {
    delete s_sceneData;
    delete s_data;
  }

  void Renderer2D::beginScene(const RenderCamera &camera) {
    s_sceneData->ViewProjectionMatrix =
        camera.getViewProjectionMatrix();
  }

  void Renderer2D::endScene() {}

  void Renderer2D::drawQuad(const glm::vec2 &position,
                            float rotatedAngle,
                            const glm::vec2 &size,
                            const glm::vec4 &color) {
    drawQuad(glm::vec3(position.x, position.y, 0), rotatedAngle, size, color);
  }

  void Renderer2D::drawQuad(const glm::vec3 &position,
                            float rotatedAngle,
                            const glm::vec2 &size,
                            const glm::vec4 &color) {
    s_data->flatColorShader->Bind();
    s_data->flatColorShader->UploadUniformMat4("u_ViewProjection",
                                               s_sceneData->ViewProjectionMatrix);
    s_data->flatColorShader->UploadUniformVec4("u_Color", color);
    glm::mat4 transform =
        glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
    transform = glm::translate(transform, position);
    transform = glm::rotate(transform, glm::radians(rotatedAngle), {0, 0, 1});
    s_data->flatColorShader->UploadUniformMat4("u_Transform", transform);
    RenderCommand::DrawIndexed(s_data->quadVertexArray);
  }

  void Renderer2D::drawQuad(const glm::vec2 &position,
                            float rotatedAngle,
                            const glm::vec2 &size,
                            const Texture2D::ptr &texture) {
    drawQuad(glm::vec3(position.x, position.y, 0), rotatedAngle, size, texture);
  }

  void Renderer2D::drawQuad(const glm::vec3 &position,
                            float rotatedAngle,
                            const glm::vec2 &size,
                            const Texture2D::ptr &texture) {
    s_data->textureShader->Bind();

    s_data->textureShader->UploadUniformMat4("u_ViewProjection",
                                             s_sceneData->ViewProjectionMatrix);
    glm::mat4 transform =
        glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
    transform = glm::translate(transform, position);
    transform = glm::rotate(transform, glm::radians(rotatedAngle), {0, 0, 1});

    s_data->textureShader->UploadUniformMat4("u_Transform", transform);
    texture->Bind();
    RenderCommand::DrawIndexed(s_data->quadVertexArray);
  }

  void Renderer2D::drawCircle(
      const glm::vec3 &position,
      const float radius,
      const glm::vec4 &color) {
    s_data->flatColorShader->Bind();
    s_data->flatColorShader->UploadUniformMat4("u_ViewProjection",
                                               s_sceneData->ViewProjectionMatrix);
    s_data->flatColorShader->UploadUniformVec4("u_Color", color);
    glm::mat4 transform =
        glm::scale(glm::mat4(1.0f), glm::vec3(radius, radius, 1.0f));
    transform = glm::translate(transform, position);
    s_data->flatColorShader->UploadUniformMat4("u_Transform", transform);
    RenderCommand::DrawIndexed(s_data->circleVertexArray);
  }

  void Renderer2D::drawCircle(
      const glm::vec3 &position,
      const float radius,
      const Texture2D::ptr &texture) {
    s_data->textureShader->Bind();

    s_data->textureShader->UploadUniformMat4("u_ViewProjection",
                                             s_sceneData->ViewProjectionMatrix);
    glm::mat4 transform =
        glm::scale(glm::mat4(1.0f), glm::vec3(radius, radius, 1.0f));
    transform = glm::translate(transform, position);

    s_data->textureShader->UploadUniformMat4("u_Transform", transform);
    texture->Bind();
    RenderCommand::DrawIndexed(s_data->circleVertexArray);
  }

  void Renderer2D::initQuad() {
    s_data->quadVertexArray.reset(VertexArray::Create());
    s_data->quadVertexArray->Bind();

    // vbo
    float quadVertices[] =
        {
            // position    |  texture uv
            -0.5f, -0.5f, 0, 0.0f, 0.0f,
            0.5f, -0.5f, 0, 1.0f, 0.0f,
            -0.5f, 0.5f, 0, 0.0f, 1.0f,
            0.5f, 0.5f, 0, 1.0f, 1.0f
        };

    auto quadVertexBuffer = VertexBuffer::ptr(
        VertexBuffer::Create(quadVertices,
                             sizeof(quadVertices))
    );

    // create layout
    quadVertexBuffer->SetBufferLayout(
        {
            {ShaderDataType::Float3, "a_Pos"},
            {ShaderDataType::Float2, "a_Tex"}
        }
    );

    // create ebo
    uint32_t quadIndices[] = {0, 1, 2, 2, 1, 3};
    auto quadIndexBuffer = IndexBuffer::ptr(
        IndexBuffer::Create(quadIndices, sizeof(quadIndices)));

    quadVertexBuffer->Bind();
    quadIndexBuffer->Bind();
    s_data->quadVertexArray->AddVertexBuffer(quadVertexBuffer);
    s_data->quadVertexArray->SetIndexBuffer(quadIndexBuffer);

//    quadIndexBuffer->UnBind();
//    quadVertexBuffer->UnBind();
    s_data->quadVertexArray->UnBind();
  }

  void Renderer2D::initCircle() {
    s_data->circleVertexArray.reset(VertexArray::Create());
    s_data->circleVertexArray->Bind();

    std::vector<float> circleVertices;
    std::vector<uint32_t> circleIndices;
    const int segments = 50;
    const float radius = 0.5f;
    const float angleIncrement = 2 * 3.14159f / segments;

    // add circle center
    circleVertices.push_back(0.f);
    circleVertices.push_back(0.f);
    circleVertices.push_back(0.f);

    circleVertices.push_back(0.f);
    circleVertices.push_back(0.f);

    // add circle point
    for (int i = 0; i <= segments; ++i) {
      float angle = static_cast<float>(i) * angleIncrement;
      float x = radius * std::cos(angle);
      float y = radius * std::sin(angle);
      circleVertices.push_back(x);
      circleVertices.push_back(y);
      circleVertices.push_back(0.f);

      float u = x / radius + .1f;
      float v = y / radius + .1f;
      circleVertices.push_back(u);
      circleVertices.push_back(v);
    }

    // set index data
    for (int i = 1; i <= segments; ++i) {
      circleIndices.push_back(0);
      circleIndices.push_back(i);
      circleIndices.push_back(i + 1);
    }

    auto circleVertexBuffer = VertexBuffer::ptr(
        VertexBuffer::Create(circleVertices.data(), sizeof(float) * circleVertices.size())
    );

    circleVertexBuffer->SetBufferLayout(
        {
            {ShaderDataType::Float3, "a_Pos"},
            {ShaderDataType::Float2, "a_Tex"}
        }
    );
    circleVertexBuffer->Bind();

    auto circleIndexBuffer = IndexBuffer::ptr(
        IndexBuffer::Create(circleIndices.data(), sizeof(uint32_t) * circleIndices.size())
    );
    circleIndexBuffer->Bind();

    s_data->circleVertexArray->AddVertexBuffer(circleVertexBuffer);
    s_data->circleVertexArray->SetIndexBuffer(circleIndexBuffer);
//    circleIndexBuffer->UnBind();
//    circleVertexBuffer->UnBind();
    s_data->circleVertexArray->UnBind();
  }

}
