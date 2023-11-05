# Cpp JNI

# resources:

hazel game engine: https://blog.csdn.net/alexhu2010q/category_10165311.html

games104

piccolo game engine

## opengl-es render part

- `Model.h`: model structure

```cpp
Model:
- vector<Vertex>
- vector<Index>
- TextureAsset
```

```cpp
struct Vertex{
  Vector3 position;
  Vector2 uv;
};
```

- `Shader.h`: opengl-es shader

```cpp
Shader:
- shader_program
- vertex
- uv
- projectionMatrix

loadShader(
  vertexSource,
  fragmentSource,
  positionAttributeName,
  uvAttributeName,
  // the uniform location of the projection matrix
  projectionMatrixUniformName
)
loadShader(shaderType, shaderSource) -> GLuint

activate()
deactivate()

drawModel()

setProjectionMatrix(float *)
```

- `TextureAsset.h`: texture asset

```cpp
TextureAsset:
- texture_id

- loadAsset(assertPath) -> TextureAsset
- getTextureID() -> GLuint
```

- `Renderer.h`: manager model render

```cpp
Renderer:
- Display
- Surface
- Context
- width
- height
- shaderNeedsNewProjectionMatrix

- m_shader
- m_models

initRenderer()

handleInput()
render()

updateRenderArea()
createModels()
```

## further package

- Vao - VertexArray

- Vbo - VertexBuffer

- Ebo - IndexBuffer

```cpp
BufferElement --> BufferLayout(begin() .. end())
    |                        |-> VertexBuffer
    |
    ^-> name, type, size, offset...
```

examples:

```cpp
members:
Shader::u_ptr m_shader;
VertexArray::ptr triangle;
codes:
auto triangle_buffer
      = VertexBuffer::ptr(VertexBuffer::Create(vertices, sizeof(vertices)));
triangle_buffer->Bind();
triangle_buffer->SetBufferLayout(
      {
        {ShaderDataType::Float3, "a_Pos"},
        {ShaderDataType::Float4, "a_Color"},
      }
);

triangle = VertexArray::ptr(VertexArray::Create());
triangle->Bind();
triangle->AddVertexBuffer(triangle_buffer);

auto triangle_index
  = IndexBuffer::ptr(IndexBuffer::Create(indices, sizeof(indices)));
triangle_index->Bind();
triangle->SetIndexBuffer(triangle_index);

```
