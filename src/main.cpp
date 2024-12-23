#include "Renderer.hpp"
#include "SceneObject.hpp"
#include <GLFW/glfw3.h>
#include <filesystem>
#include "GlbFile.hpp"
#include "WavefrontFile.hpp"
#include <memory>

using namespace small3d;

bool downkey, leftkey, rightkey, upkey, esckey;

void keyCallback(GLFWwindow* window, int key, int scancode, int action,
  int mods)
{
  if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    downkey = true;
  if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    upkey = true;
  if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    leftkey = true;
  if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    rightkey = true;
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    esckey = true;
  if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
    downkey = false;
  if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
    upkey = false;
  if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
    leftkey = false;
  if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
    rightkey = false;
  if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
    esckey = false;

};

struct Object {
  std::shared_ptr<SceneObject> so;
  std::string textureName = "";
};

int main(int argc, char** argv) {
  try {
    Renderer* renderer = &Renderer::getInstance("Serial renderer", 800, 600, 0.78f, 1.0f, 24.0f, "../small3d/bin/resources/shaders/", 500);
    renderer->cameraPosition = Vec3(0.0f, 0.0f, 0.9f);
    GLFWwindow* window = renderer->getWindow();
    glfwSetKeyCallback(window, keyCallback);

    for (const auto& entry : std::filesystem::directory_iterator("resources/models")) {
      auto path = entry.path().string();
      if (path.compare(path.length() - 4, 4, ".mtl") == 0) {
        continue;
      }
      std::vector<Object> objects;
      LOGINFO("Loading " + entry.path().string());

      float maxX = 0.0f;
      float minX = 0.0f;
      std::vector<std::string> names;

      try
      {
        names = GlbFile(entry.path().string()).getMeshNames();
      }
      catch (std::runtime_error&) {
        names = WavefrontFile(entry.path().string()).getMeshNames();
      }

      if (names.size() == 0) {
        names.push_back("");
      }

      for (auto& name : names) {
        Object ob;
        try {
          ob.so = std::make_shared<SceneObject>(name, Model(GlbFile(entry.path().string()), name));
          if (ob.so->getModel().defaultTextureImage != nullptr) {
            renderer->generateTexture(name, *ob.so->getModel().defaultTextureImage);
            ob.textureName = name;
          }
          
        }
        catch (std::exception& ex) {
          ob.so = std::make_shared<SceneObject>(name, Model(WavefrontFile(entry.path().string()), name));
        }

        if (ob.so->getBoundingBoxSetExtremes()[0].minX < minX) minX = ob.so->getBoundingBoxSetExtremes()[0].minX;
        if (ob.so->getBoundingBoxSetExtremes()[0].maxX > maxX) maxX = ob.so->getBoundingBoxSetExtremes()[0].maxX;
        
        objects.push_back(ob);

      }

      float scale = 2.0f / (maxX - minX);

      for (auto& ob : objects) {
        ob.so->getModel().scale = Vec3(scale);
        ob.so->position = Vec3(0.0f, -2.0f, -5.0f);
        ob.so->startAnimating();
      }

      bool done = false;

      double startSeconds = glfwGetTime();
      double seconds = glfwGetTime();
      double prevSeconds = seconds;
      const uint32_t framerate = 60;
      constexpr double secondsInterval = 1.0 / framerate;

      while (!glfwWindowShouldClose(window) && !done && seconds - startSeconds < 5.0) {

        glfwPollEvents();
        seconds = glfwGetTime();
        if (seconds - prevSeconds > secondsInterval) {
          prevSeconds = seconds;
          if (esckey)
            break;

          for (auto& ob : objects) {

            ob.so->animate();
            ob.so->rotate(Vec3(0.0f, 0.02f, 0.0f));

            ob.textureName != "" ?
              renderer->render(*ob.so, ob.textureName) :
              renderer->render(*ob.so, Vec4(ob.so->getModel().material.ambientColour, ob.so->getModel().material.alpha));
          }

          renderer->swapBuffers();
        }
        if (esckey) done = true;
      }

      for (auto& ob : objects) {
        renderer->deleteTexture(ob.textureName);
        renderer->clearBuffers(*ob.so);
      }
      if (done) break;
    }
  }
  catch (std::runtime_error& e) {
    LOGERROR(e.what());
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
