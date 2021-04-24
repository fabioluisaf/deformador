#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <string_view>

#include "abcg.hpp"
#include "model.hpp"
#include "trackball.hpp"

class OpenGLWindow : public abcg::OpenGLWindow {
 protected:
  void handleEvent(SDL_Event& ev) override;
  void initializeGL() override;
  void paintGL() override;
  void paintUI() override;
  void resizeGL(int width, int height) override;
  void terminateGL() override;

 private:
  int m_viewportWidth{};
  int m_viewportHeight{};

  Model m_model;
  int m_trianglesToDraw{};

  TrackBall m_trackBallModel;
  TrackBall m_trackBallLight;
  float m_zoom{};

  glm::vec3 m_eyePosition{};
  glm::mat4 m_modelMatrix{1.0f};
  glm::mat4 m_viewMatrix{1.0f};
  glm::mat4 m_projMatrix{1.0f};

  // Shaders
  const char* m_shader{"normalmapping"};
  GLuint m_program;
  int m_currentProgramIndex{};

  // Mapping mode
  // 0: triplanar; 1: cylindrical; 2: spherical; 3: from mesh
  int m_mappingMode{};

  // Light and material properties
  glm::vec4 m_lightDir{-1.0f, -1.0f, -1.0f, 0.0f};
  glm::vec4 m_Ia{1.0f};
  glm::vec4 m_Id{1.0f};
  glm::vec4 m_Is{1.0f};
  glm::vec4 m_Ka;
  glm::vec4 m_Kd;
  glm::vec4 m_Ks;
  float m_shininess{};

  // parametros da deformacao
  bool m_deformacaoLigada{false}; // diz se a transformacao esta ligada ou nao

  float m_periodoOnda{}; // velocidade da onda

  float m_tamanhoEspinhos{}; // usado na deformacao de espinhos e na aleatoria
  float m_razaoDeformacao{}; // usado na deformacao aleatoria

  float m_cooldownDeformacao{};         // cooldown das deformacoes
  abcg::ElapsedTimer timerDeformacao{}; // timer que controla o cooldown das deformacoes

  int m_tipoDeformacao{};               // indice que sera usado no vetor m_tiposDeformacao
  const std::vector<std::string> m_tiposDeformacao{
    "Ondular",
    "Espinhos",
    "Aleatorio"
  };

  void loadModel(std::string_view path);
  void update();
};

#endif