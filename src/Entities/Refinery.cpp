﻿#include "Entities/Refinery.h"

namespace Motherload
{
    Refinery::Refinery(glm::vec2 position, glm::vec2 size)
    {
        this->transform = new Transform(this, position, size);
        this->name = "Refinery";

        /* Physics */
        this->collider = new Physics::Collider(this);
        this->collider->isTrigger = true;
        this->isDynamic = false;
    }

    void Refinery::activeUpdate()
    {
        if (InputSystem::getKeyDown(SDL_SCANCODE_SPACE))
        {
            sellMinerals();
        }
    }

    void Refinery::initialize()
    {
        this->texture = ResourceManager::getTexture("data/textures/refinery.png");
        uiPanel = UISystem::addPanel(Constants::centerScreen, buyStrings, true);
        uiPanel->wrapAfterPixels = uiPanel->size.x;
        uiPanel->setBackgroundPanel(ResourceManager::getTexture("data/textures/uipanel.png"), 30.0f);
        uiPanel->setActive(false);
        playerInventory = Game::instance->player->inventory;
    }

    void Refinery::resetUi()
    {
        buyStrings.clear();
        totalMoney = 0;
        for (int i = 0; i < MineralType::NUM_MINERALS; i++)
        {
            totalMoney += playerInventory->minerals[i] * Constants::mineralPrices[i];
        }

        this->buyStrings.push_back
        (
            "Granite: " +
            std::to_string(playerInventory->minerals[MineralType::Granite]) +
            " x $" + std::to_string(Constants::mineralPrices[MineralType::Granite])
        );
        this->buyStrings.push_back
        (
            "Iron:    " +
            std::to_string(playerInventory->minerals[MineralType::Iron]) +
                " x $" + std::to_string(Constants::mineralPrices[MineralType::Iron])
        );
        this->buyStrings.push_back
        (
            "Gold:    " +
            std::to_string(playerInventory->minerals[MineralType::Gold]) +
                " x $" + std::to_string(Constants::mineralPrices[MineralType::Gold])
        );
        this->buyStrings.push_back("----------------------------");
        this->buyStrings.push_back("Total:       $" + std::to_string(totalMoney));
        this->buyStrings.push_back("----------------------------");
        if (playerInventory->hasMinerals)
        {
            this->buyStrings.push_back("Press SPACE to sell minerals.");
        }
        else
        {
            this->buyStrings.push_back("No minerals in inventory.");
        }
        uiPanel->setText(buyStrings);
    }

    void Refinery::sellMinerals()
    {
        for (int& mineral: playerInventory->minerals)
        {
            mineral = 0;
        }
        playerInventory->addMoney(totalMoney);
        playerInventory->resetMinerals();
        resetUi();
    }


} // namespace Motherload
