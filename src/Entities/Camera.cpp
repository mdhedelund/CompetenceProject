#include "Entities/Camera.h"
#include "Systems/InputSystem.h"
#include "Constants.h"
#include "Game.h"

namespace Motherload
{
    glm::vec2 Camera::positionWorldSpace;
    void Camera::initialize()
    {
        positionWorldSpace = glm::vec2(0);
    }

    void Camera::updatePosition(float deltaTime)
    {
        if (!DebugSystem::detachedCamera)
        {
            positionWorldSpace.y = Game::instance->player->transform->positionWorldSpace.y - Constants::midScreen.y;
            return;
        }
        if (InputSystem::getKey(SDL_SCANCODE_W))
        {
            positionWorldSpace.y -= Constants::cameraSpeed * deltaTime;
        }
        if (InputSystem::getKey(SDL_SCANCODE_A))
        {
            positionWorldSpace.x -= Constants::cameraSpeed * deltaTime;
        }
        if (InputSystem::getKey(SDL_SCANCODE_S))
        {
            positionWorldSpace.y += Constants::cameraSpeed * deltaTime;
        }
        if (InputSystem::getKey(SDL_SCANCODE_D))
        {
            positionWorldSpace.x += Constants::cameraSpeed * deltaTime;
        }
    }

    glm::vec2 Camera::toCameraSpace(glm::vec2 position)
    {
        return position - positionWorldSpace;
    }
} // namespace Motherload
