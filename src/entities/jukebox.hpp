#ifndef JUKEBOX_HPP
#define JUKEBOX_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"

struct Jukebox{};


void CreateJukebox(entt::registry &registry);
entt::entity GetJukeboxEntity(entt::registry &registry);

#endif
