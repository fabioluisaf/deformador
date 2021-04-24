#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <string_view>
#include <random>

#include "abcg.hpp"

struct Vertex {
  glm::vec3 position{};
  glm::vec3 normal{};
  glm::vec2 texCoord{};
  glm::vec4 tangent{};
  glm::vec3 offset{};

  bool operator==(const Vertex& other) const noexcept {
    static const auto epsilon{std::numeric_limits<float>::epsilon()};
    return glm::all(glm::epsilonEqual(position, other.position, epsilon)) &&
           glm::all(glm::epsilonEqual(normal, other.normal, epsilon)) &&
           glm::all(glm::epsilonEqual(texCoord, other.texCoord, epsilon));
  }
};

class Model {
 public:
  Model() = default;
  virtual ~Model();

  Model(const Model&) = delete;
  Model(Model&&) = default;
  Model& operator=(const Model&) = delete;
  Model& operator=(Model&&) = default;

  void loadDiffuseTexture(std::string_view path);
  void loadNormalTexture(std::string_view path);
  void loadFromFile(std::string_view path, bool standardize = true);
  void render(int numTriangles = -1) const;
  void setupVAO(GLuint program);

  void limpaOffsets();

  void deformaOnda(float periodo);
  void deformaEspinho(float tamanho);
  void deformaAleatorio(float tamanho, float razao);

  std::default_random_engine m_rnjesus{};

  std::vector<Vertex> getVertices();
  int getVerticesSize();

  [[nodiscard]] int getNumTriangles() const {
    return static_cast<int>(m_indices.size()) / 3;
  }

  [[nodiscard]] glm::vec4 getKa() const { return m_Ka; }
  [[nodiscard]] glm::vec4 getKd() const { return m_Kd; }
  [[nodiscard]] glm::vec4 getKs() const { return m_Ks; }
  [[nodiscard]] float getShininess() const { return m_shininess; }

  [[nodiscard]] bool isUVMapped() const { return m_hasTexCoords; }

 private:
  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};

  glm::vec4 m_Ka{};
  glm::vec4 m_Kd{};
  glm::vec4 m_Ks{};
  float m_shininess{};
  GLuint m_diffuseTexture{};
  GLuint m_normalTexture{};

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;

  bool m_hasNormals{false};
  bool m_hasTexCoords{false};

  abcg::ElapsedTimer timerOnda{};

  void computeNormals();
  void deforma();
  void computeTangents();
  void createBuffers();
  void standardize();
};

#endif