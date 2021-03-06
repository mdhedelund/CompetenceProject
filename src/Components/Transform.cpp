#include "Components/Transform.h"

namespace Motherload
{
    Transform::Transform(Entity* entity, glm::vec2 position, glm::vec2 size, glm::vec2 scale)
    {
        this->entity = entity;
        this->positionWorldSpace = position;
        this->sizeWorldSpace = size;
        this->scaleWorldSpace = scale;
    }

    glm::vec2 Transform::getPositionCameraSpace()
    {
        return positionWorldSpace - Camera::positionWorldSpace;
    }

    glm::vec2 Transform::getSizeCameraSpace()
    {
        // TODO: Maybe implement zoom if fitting
        return sizeWorldSpace * scaleWorldSpace;
    }

    glm::vec2 Transform::getPositionCoordinates()
    {
        return positionWorldSpace / Constants::cellSize;
    }

} // namespace Motherload
