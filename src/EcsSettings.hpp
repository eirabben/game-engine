#pragma once

#include "Ecs/src/Manager.hpp"

#include "Components/CDirLight.hpp"
#include "Components/CMaterial.hpp"
#include "Components/CMesh.hpp"
#include "Components/CPointLight.hpp"
#include "Components/CPosition.hpp"

using Manager = ecs::Manager<CDirLight, CMaterial, CMesh, CPointLight, CPosition>;
using Entity = ecs::Entity;
