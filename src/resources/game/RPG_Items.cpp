/*
	+-------------------------------------------------------------+
	|              OneLoneCoder RPG Game Engine                   |
	|     "The Legend of WittyBit, Fantasy Quest VI" - javidx9    |
	+-------------------------------------------------------------+

	What is this?
	~~~~~~~~~~~~~

	This is the code I created as part of my
	"Code-It-Yourself! Role Playing Game" series on YouTube. This is
	NOT a game. The project will compile and demonstrate several
	systems developed as part of that series. My original intention
	was to develop a small yet complete RPG, alas real life got in
	the way. After several months, I've decided to just open the source
	"as is", so it will contain bugs, be confusing and all round not
	up to the usual "quality" I strive for.

	Part 1: https://youtu.be/xXXt3htgDok
	Part 2: https://youtu.be/AWY_ITpldRk
	Part 3: https://youtu.be/UcNSb-m4YQU
	Part 4: https://youtu.be/AnyoUfeNZ1Y

	License (OLC-3)
	~~~~~~~~~~~~~~~

	Copyright 2018, 2019 OneLoneCoder.com

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:

	1. Redistributions or derivations of source code must retain the above
	copyright notice, this list of conditions and the following disclaimer.

	2. Redistributions or derivative works in binary form must reproduce
	the above copyright notice. This list of conditions and the following
	disclaimer must be reproduced in the documentation and/or other
	materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its
	contributors may be used to endorse or promote products derived
	from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	Links
	~~~~~
	YouTube:	https://www.youtube.com/javidx9
	Discord:	https://discord.gg/WhwHUMV
	Twitter:	https://www.twitter.com/javidx9
	Twitch:		https://www.twitch.tv/javidx9
	GitHub:		https://www.github.com/onelonecoder
	Homepage:	https://www.onelonecoder.com
	Patreon:	https://www.patreon.com/javidx9

	Author
	~~~~~~
	David Barr, aka javidx9, �OneLoneCoder 2018, 2019
*/

#include "RPG_Items.h"

#include <utility>

#include <utility>

#include <math.h>
#include "RPG_Engine.h"

RPG_Engine* cItem::g_engine = nullptr;

cItem::cItem(string name, olc::Sprite* sprite, string desc) : sName(std::move(std::move(name))), pSprite(sprite), sDescription(std::move(std::move(desc))) 
{ 
	
}


cItem_Health::cItem_Health() : cItem("Small Health", RPG_Assets::get().GetSprite("health"), "Restores 10 health")
{
}


auto cItem_Health::OnInteract(cDynamic *object) -> bool
{
	OnUse(object);
	return false; // Just absorb
}


auto cItem_Health::OnUse(cDynamic *object) -> bool
{
	if (object != nullptr)
	{
		auto* dyn = dynamic_cast<cDynamic_Creature*>(object);
		dyn->nHealth = min(dyn->nHealth + 10, dyn->nHealthMax);
	}
	return true;
}


cItem_HealthBoost::cItem_HealthBoost() :
	cItem("Health Boost", RPG_Assets::get().GetSprite("healthboost"), "Increases Max Health by 10")
{}

auto cItem_HealthBoost::OnInteract(cDynamic * /*object*/) -> bool
{
	return true; // Add to inventory
}

auto cItem_HealthBoost::OnUse(cDynamic *object) -> bool
{
	if (object != nullptr)
	{
		auto* dyn = dynamic_cast<cDynamic_Creature*>(object);
		dyn->nHealthMax += 10;
		dyn->nHealth = dyn->nHealthMax;
	}

	return true; // Remove from inventory
}

cWeapon::cWeapon(string name, olc::Sprite* sprite, string desc, int dmg) : cItem(std::move(name), sprite, std::move(desc)), nDamage(dmg)
{
	
}

auto cWeapon::OnInteract(cDynamic * /*object*/) -> bool
{
	return false;
}

auto cWeapon::OnUse(cDynamic * /*object*/) -> bool
{
	return false;
}


cWeapon_Sword::cWeapon_Sword() :
	cWeapon("Basic Sword", RPG_Assets::get().GetSprite("Basic Sword"), "A wooden sword, 5 dmg", 5)
{

}

auto cWeapon_Sword::OnUse(cDynamic *object) -> bool
{
	// When weapons are used, they are used on the object that owns the weapon, i.e.
	// the attacker. However this does not imply the attacker attacks themselves

	// Get direction of attacker
	auto* aggressor = dynamic_cast<cDynamic_Creature*>(object);

	// Determine attack origin
	float x = NAN;
	float y = NAN;
	float vx = NAN;
	float vy = NAN;
	if (aggressor->GetFacingDirection() == 0) // South
	{
		x = aggressor->px;
		y = aggressor->py + 1.0F;
		vx = 0.0F; vy = 1.0F;
	}

	if (aggressor->GetFacingDirection() == 1) // East
	{
		x = aggressor->px - 1.0F;
		y = aggressor->py;
		vx = -1.0F; vy = 0.0F;
	}

	if (aggressor->GetFacingDirection() == 2) // North
	{
		x = aggressor->px;
		y = aggressor->py - 1.0F;
		vx = 0.0F; vy = -1.0F;
	}

	if (aggressor->GetFacingDirection() == 3) // West
	{
		x = aggressor->px + 1.0F;
		y = aggressor->py;
		vx = 1.0F; vy = 0.0F;
	}

	if (aggressor->nHealth == aggressor->nHealthMax)
	{
		// Beam sword
		auto *p = new cDynamic_Projectile(x, y, aggressor->bFriendly, vx * 15.0F, vy * 15.0F, 1.0F, RPG_Assets::get().GetSprite("Basic Sword"), (aggressor->GetFacingDirection() + 3) % 4 + 1, 1.0F);
		p->bSolidVsMap = true;
		p->bSolidVsDyn = false;
		p->nDamage = 5;
		p->bOneHit = false;
		g_engine->AddProjectile(p);
	}

	auto *p = new cDynamic_Projectile(x, y, aggressor->bFriendly, aggressor->vx, aggressor->vy, 0.1F, RPG_Assets::get().GetSprite("Basic Sword"), (aggressor->GetFacingDirection() + 3) % 4 + 1, 0.0F);
	p->bSolidVsMap = false;
	p->bSolidVsDyn = false;
	p->nDamage = 5;
	p->bOneHit = true;

	g_engine->AddProjectile(p);

	return false;
}