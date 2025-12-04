#ifndef MUSIC_CONTROLLER_HPP
#define MUSIC_CONTROLLER_HPP

#include "../entities/entities.hpp"
#include "../../include/entt.hpp"

void UpdateMusic(entt::registry &registry);
void StopAllMusic(entt::registry &registry);
void StartSong(entt::registry &registry, std::string song);

#endif
