#include "cubeVertex.hh"

namespace object3d {
  cubeVertex::cubeVertex(const char* texture) : _speed(10.f) {
    if (_texture.load(texture) == false) { 
      std::cerr << "Error : Failed to load texture" << std::endl; 
      return ;
    }		
    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5)); 
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5)); 
		
    _geometry.pushUv(glm::vec2(0.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 1.0f)); 
    _geometry.pushUv(glm::vec2(0.0f, 1.0f)); 
		
    _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5)); 
    _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5)); 
		
    _geometry.pushUv(glm::vec2(0.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 1.0f)); 
    _geometry.pushUv(glm::vec2(0.0f, 1.0f)); 
		
    _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5)); 
    _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5)); 
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5)); 
    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5)); 
		
    _geometry.pushUv(glm::vec2(0.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 1.0f)); 
    _geometry.pushUv(glm::vec2(0.0f, 1.0f)); 
		
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5)); 
		
    _geometry.pushUv(glm::vec2(0.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 1.0f)); 
    _geometry.pushUv(glm::vec2(0.0f, 1.0f)); 
		
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5)); 
    _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5)); 
		
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
		
    _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
		
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
		
    _geometry.build();
  };

  void	cubeVertex::setPosition(double x, double y, cubeVertex::Layer layer) {
    if (layer == cubeVertex::Ground)
      translate(glm::vec3(x, y, -1));
    else if (layer == cubeVertex::Up)
      translate(glm::vec3(x, y, -5));
    else
      translate(glm::vec3(x, y,0));
  }

  void	cubeVertex::draw(gdl::AShader& shader, gdl::Clock const&) {
    _texture.bind();
    _geometry.draw(shader, getTransformation(), GL_QUADS);
  }
};
