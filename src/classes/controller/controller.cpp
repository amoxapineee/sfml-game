#include <cmath>

#include "./controller.h"
#include "../player/player.h"

Controller* Controller::controller = nullptr;

Controller::~Controller() {
    delete controller;
}

Controller* Controller::getPlayerController() {
    if (!controller) {
        controller = new Controller();
    }
    return controller;
}

void Controller::controlPlayer(Player* player, const float& time) { // дизентегрировать отсюда
    sf::Vector2f vel;
    sf::Vector2f updated_pos = player->getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        vel.y -= player::PLAYER_SPEED * time;
        player->setState(State::RUN);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        vel.x -= player::PLAYER_SPEED * time;
        player->setDirection(Direction::LEFT);
        player->setState(State::RUN);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        vel.y += player::PLAYER_SPEED * time;
        player->setState(State::RUN);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        vel.x += player::PLAYER_SPEED * time;
        player->setDirection(Direction::RIGHT);
        player->setState(State::RUN);
    }

    auto speed = std::sqrt(vel.x * vel.x + vel.y * vel.y);

    if (speed > player::MAX_SPEED) {
        vel.x *= player::MAX_SPEED / speed;
        vel.y *= player::MAX_SPEED / speed;
    }
    updated_pos.x += vel.x;
    updated_pos.y += vel.y;
    

    sf::Vector2f borders = {
            static_cast<float>(sqrt(pow(speed, 2) - pow(velocity.x, 2))),
            static_cast<float>(sqrt(pow(speed, 2) - pow(velocity.y, 2)))

    };
    velocity = {
            clamp(velocity.x, -borders.x, borders.x),
            clamp(velocity.y, -borders.y, borders.y)
    };

    sf::Vector2f updated_pos = player->getPosition() + velocity;
    player->setPosition(updated_pos);
}